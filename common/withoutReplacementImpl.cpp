#include "withoutReplacementImpl.h"
#include "sampford.h"
namespace permanent
{
	struct possibility
	{
		int parent;
		int newEntry;
		int previousEntry;
	};
	void withoutReplacementImpl(withoutReplacementArgs& args)
	{
		boost::numeric::ublas::matrix<double>& matrix = args.matrix;
		int n = args.n;
		int seed = args.seed;
		double alpha = args.alpha;
		if(matrix.size1() != matrix.size2())
		{
			throw std::runtime_error("Matrix must be square");
		}
		if(n < 1)
		{
			throw std::runtime_error("Input n must be at least 1");
		}
		int dimension = matrix.size1();
		boost::mt19937 randomSource;
		randomSource.seed(seed);
		std::vector<double> columnSums(dimension,0);
		for(int row = 0; row < dimension; row++)
		{
			for(int column = 0; column < dimension; column++)
			{
				columnSums[column] += std::fabs(matrix(row, column));
			}
		}
		
		std::vector<double> currentColumnSums(dimension), newCurrentColumnSums;
		std::vector<int> availableColumns(dimension), newAvailableColumns;
		std::vector<int> availableRows(dimension), newAvailableRows;
		std::vector<int> previousEntry(1), newPreviousEntry;
		std::vector<bool> usedRows(dimension), newUsedRows;
		std::vector<mpfr_class> weights(1, 1), newWeights;
		//Get out the choices at the start. 
		std::vector<possibility> possibilities;
		for(int i = 0; i < dimension; i++)
		{
			for(int j = 0; j < dimension; j++)
			{
				possibility nextPos;
				nextPos.parent = 0;
				nextPos.previousEntry = i;
				nextPos.newEntry = j;
				possibilities.push_back(nextPos);
			}
		}
		//These choices are all derived from a single particle at the start
		std::copy(columnSums.begin(), columnSums.end(), currentColumnSums.begin());
		for(int i = 0; i < dimension; i++)
		{
			availableColumns[i] = i;
			availableRows[i] = i;
		}
		std::fill(usedRows.begin(), usedRows.end(), false);

		sampling::sampfordFromParetoNaiveArgs samplingArgs;
		samplingArgs.n = n;

		samplingArgs.weights.resize(dimension*dimension);
		for(int i = 0; i < (int)possibilities.size(); i++)
		{
			possibility& pos = possibilities[i];
			if(pos.previousEntry == pos.newEntry)
			{
				samplingArgs.weights[i] = alpha * std::fabs(matrix(pos.previousEntry, pos.newEntry));
			}
			else 
			{
				samplingArgs.weights[i] = std::fabs(matrix(pos.previousEntry, pos.newEntry));
			}
		}

		int currentSamples = 1;
		for(int permutationCounter = 0; permutationCounter < dimension; permutationCounter++)
		{
			//Draw sample
			if((int)possibilities.size() <= n)
			{
				newCurrentColumnSums.resize(possibilities.size()*dimension);
				newAvailableColumns.resize(possibilities.size()*(dimension - permutationCounter-1));
				newAvailableRows.resize(possibilities.size()*(dimension - permutationCounter-1));
				newUsedRows.resize(possibilities.size()*dimension);
				newPreviousEntry.resize(possibilities.size());
				int newAvailableColumnsIndex = 0;
				int newAvailableRowsIndex = 0;
				for(int i = 0; i < (int)possibilities.size(); i++)
				{
					possibility& pos = possibilities[i];
					std::copy(currentColumnSums.begin() + pos.parent * dimension, currentColumnSums.begin() + (pos.parent + 1) * dimension, newCurrentColumnSums.begin() + dimension * i);
					newCurrentColumnSums[dimension*i + pos.newEntry] -= std::fabs(matrix(pos.previousEntry, pos.newEntry));
					std::copy(usedRows.begin() + pos.parent*dimension, usedRows.begin() + (pos.parent + 1) * dimension, newUsedRows.begin() + dimension*i);
					newUsedRows[dimension*i + pos.previousEntry] = true;
					for(int j = 0; j < dimension - permutationCounter; j++)
					{
						if(availableColumns[j + pos.parent*(dimension - permutationCounter)] != pos.newEntry)
						{
							newAvailableColumns.at(newAvailableColumnsIndex) = availableColumns.at(j + pos.parent*(dimension - permutationCounter));
							newAvailableColumnsIndex++;
						}
						if(availableRows[j + pos.parent*(dimension - permutationCounter)] != pos.previousEntry)
						{
							newAvailableRows.at(newAvailableRowsIndex) = availableRows.at(j + pos.parent*(dimension - permutationCounter));
							newAvailableRowsIndex++;
						}
					}
					if(newUsedRows[i*dimension + pos.newEntry])
					{
						newPreviousEntry[i] = -1;
					}
					else
					{
						newPreviousEntry[i] = pos.newEntry;
					}
				}
				newWeights.swap(samplingArgs.weights);
				currentSamples = possibilities.size();
			}
			else
			{
				sampfordFromParetoNaive(samplingArgs, randomSource);
				newCurrentColumnSums.resize(n*dimension);
				newAvailableColumns.resize(n*(dimension - permutationCounter-1));
				newAvailableRows.resize(n*(dimension - permutationCounter-1));
				newUsedRows.resize(n*dimension);
				newWeights.resize(n);
				newPreviousEntry.resize(n);
				int newAvailableColumnsIndex = 0;
				int newAvailableRowsIndex = 0;
				for(int i = 0; i < n; i++)
				{
					possibility& pos = possibilities[samplingArgs.indices[i]];
					std::copy(currentColumnSums.begin() + pos.parent * dimension, currentColumnSums.begin() + (pos.parent + 1) * dimension, newCurrentColumnSums.begin() + dimension * i);
					newCurrentColumnSums[dimension*i + pos.newEntry] -= std::fabs(matrix(pos.previousEntry, pos.newEntry));
					std::copy(usedRows.begin() + pos.parent*dimension, usedRows.begin() + (pos.parent + 1) * dimension, newUsedRows.begin() + dimension*i);
					newUsedRows[dimension*i + pos.previousEntry] = true;
					for(int j = 0; j < dimension - permutationCounter; j++)
					{
						if(availableColumns[j + pos.parent*(dimension - permutationCounter)] != pos.newEntry)
						{
							newAvailableColumns.at(newAvailableColumnsIndex) = availableColumns.at(j + pos.parent*(dimension - permutationCounter));
							newAvailableColumnsIndex++;
						}
						if(availableRows[j + pos.parent*(dimension - permutationCounter)] != pos.previousEntry)
						{
							newAvailableRows.at(newAvailableRowsIndex) = availableRows.at(j + pos.parent*(dimension - permutationCounter));
							newAvailableRowsIndex++;
						}
					}
					if(newUsedRows[i*dimension + pos.newEntry])
					{
						newPreviousEntry[i] = -1;
					}
					else
					{
						newPreviousEntry[i] = pos.newEntry;
					}
					newWeights[i] = samplingArgs.weights[samplingArgs.indices[i]] / samplingArgs.rescaledWeights[samplingArgs.indices[i]];
				}
				currentSamples = n;
			}
			previousEntry.swap(newPreviousEntry);
			currentColumnSums.swap(newCurrentColumnSums);
			availableColumns.swap(newAvailableColumns);
			availableRows.swap(newAvailableRows);
			usedRows.swap(newUsedRows);
			weights.swap(newWeights);

			//If we're not at the end, get out the list of possibilities and also weights
			if(permutationCounter != dimension - 1)
			{
				possibilities.clear();
				samplingArgs.weights.clear();
				for(int i = 0; i < currentSamples; i++)
				{
					if(previousEntry[i] == -1)
					{
						for(int j = 0; j < dimension - permutationCounter - 1; j++)
						{
							for(int k = 0; k < dimension - permutationCounter - 1; k++)
							{
								possibility pos;
								pos.parent = i;
								pos.previousEntry = availableRows[(dimension - permutationCounter - 1) * i + j];
								pos.newEntry = availableColumns[(dimension - permutationCounter - 1) * i + k];
								possibilities.push_back(pos);
								if(j == k || usedRows[pos.newEntry + dimension * i])
								{
									samplingArgs.weights.push_back(weights[i] * alpha * std::fabs(matrix(pos.previousEntry, pos.newEntry)));
								}
								else
								{
									samplingArgs.weights.push_back(weights[i] * std::fabs(matrix(pos.previousEntry, pos.newEntry)));
								}
							}
						}

					}
					else
					{
						for(int j = 0; j < dimension - permutationCounter - 1; j++)
						{
							possibility pos;
							pos.parent = i;
							pos.previousEntry = previousEntry[i];
							pos.newEntry = availableColumns[(dimension - permutationCounter - 1) * i + j];
							possibilities.push_back(pos);
							if(j == previousEntry[i] || usedRows[pos.newEntry + dimension * i])
							{
								samplingArgs.weights.push_back(weights[i] * alpha * std::fabs(matrix(pos.previousEntry, pos.newEntry)));
							}
							else
							{
								samplingArgs.weights.push_back(weights[i] * std::fabs(matrix(pos.previousEntry, pos.newEntry)));
							}
						}
					}
				}
			}
		}
		args.estimate = 0;
		for(int i = 0; i < (int)weights.size(); i++)
		{
			args.estimate += weights[i];
		}
	}
}
