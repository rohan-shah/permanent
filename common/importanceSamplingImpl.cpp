#include "importanceSamplingImpl.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
namespace permanent
{
	void importanceSamplingImpl(importanceSamplingArgs& args)
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
		std::vector<double> rowSums(dimension, 0), columnSums(dimension,0);
		for(int row = 0; row < dimension; row++)
		{
			for(int column = 0; column < dimension; column++)
			{
				rowSums[row] += std::fabs(matrix(row, column));
				columnSums[column] += std::fabs(matrix(row, column));
			}
		}
		std::vector<double> currentColumnSums(dimension);
		std::vector<int> availableRows(dimension), availableColumns(dimension);
		std::vector<bool> usedRows(dimension);
		std::vector<double> probabilities;
		mpfr_class weight;
		mpfr_class sum = 0, sumSquared = 0;
		for(int sampleCounter = 0; sampleCounter < n; sampleCounter++)
		{
			weight = 1;
			std::copy(columnSums.begin(), columnSums.end(), currentColumnSums.begin());
			availableRows.resize(dimension);
			availableColumns.resize(dimension);
			usedRows.resize(dimension);
			for(int i = 0; i < dimension; i++) availableRows[i] = availableColumns[i] = i;
			std::fill(usedRows.begin(), usedRows.end(), false);
			int previous = -1;
			for(int coordinateCounter = 0; coordinateCounter < dimension; coordinateCounter++)
			{
				if(previous == -1)
				{
					boost::random::uniform_int_distribution<int> drawNextStart(0, availableRows.size()-1);
					int index  = drawNextStart(randomSource);
					previous = availableRows[index];
					std::swap(availableRows[index], availableRows.back());
					availableRows.pop_back();
				}
				else
				{
					std::vector<int>::iterator findPrevious = std::find(availableRows.begin(), availableRows.end(), previous);
					std::swap(*findPrevious, *availableRows.rbegin());
					availableRows.pop_back();
				}
				usedRows[previous] = true;
				probabilities.resize(availableColumns.size());
				double sum = 0;
				int infiniteCount = 0, infiniteIndex = -1;;
				for(int columnCounter = 0; columnCounter < (int)availableColumns.size(); columnCounter++)
				{
					double value = std::fabs(matrix(previous, availableColumns[columnCounter]));
					probabilities[columnCounter] = value / (columnSums[availableColumns[columnCounter]] - value);
					if(availableColumns[columnCounter] == previous) probabilities[columnCounter] *= alpha;
					if(probabilities[columnCounter] == std::numeric_limits<double>::infinity())
					{
						infiniteCount++;
						infiniteIndex = columnCounter;
					}
					sum += probabilities[columnCounter];
				}
				//Maybe we end up selecting a zero, which can happen at the last step. In which case the ratio is zero. 
				if(sum == 0 || infiniteCount > 1)
				{
					weight = 0;
					goto nextStep;
				}
				int sampledColumn = -1;
				int sampledIndexWithinAvailable = -1;
				double sampleProbability = -1;
				if(infiniteCount == 1)
				{
					sampleProbability = 1;
					sampledIndexWithinAvailable = infiniteIndex;
					sampledColumn = availableColumns[infiniteIndex];
				}
				else
				{
					boost::random::uniform_real_distribution<double> drawNext(0, sum);
					double sample = drawNext(randomSource);
					double accumulated = 0;
					for(int columnCounter = 0; columnCounter < (int)availableColumns.size(); columnCounter++)
					{
						if(sample <= accumulated + probabilities[columnCounter])
						{
							sampledColumn = availableColumns[columnCounter];
							sampleProbability = probabilities[columnCounter] / sum;
							sampledIndexWithinAvailable = columnCounter;
							break;
						}
						accumulated += probabilities[columnCounter];
					}
				}

				std::swap(availableColumns[sampledIndexWithinAvailable], availableColumns.back());
				availableColumns.pop_back();
				weight *= std::fabs(matrix(previous, sampledColumn)) / sampleProbability;
				currentColumnSums[sampledColumn] -= std::fabs(matrix(previous, sampledColumn));
				if(usedRows[sampledColumn])
				{
					weight *= alpha;
					previous = -1;
				}
				else
				{
					previous = sampledColumn;
				}
			}
		nextStep:
			sum += weight;
			sumSquared += weight*weight;
		}
		args.estimate = sum/n;
		args.estimatedVariance = sumSquared / n - args.estimate * args.estimate;
	}
}
