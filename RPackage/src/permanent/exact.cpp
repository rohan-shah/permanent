#include "exact.h"
#include "includeMPFR.h"
namespace permanent
{
	SEXP exact(SEXP matrix_sexp, SEXP progress_sexp)
	{
	BEGIN_RCPP
		mpz_class sum = 0;
		mpz_class rowsumprod, rowsum;
		Rcpp::IntegerMatrix matrix = Rcpp::as<Rcpp::IntegerMatrix>(matrix_sexp);
		if(matrix.ncol() != matrix.nrow())
		{
			throw std::runtime_error("Matrix must be square");
		}
		bool progress = Rcpp::as<bool>(progress_sexp);
		Rcpp::Function txtProgressBar("txtProgressBar"), setTxtProgressBar("setTxtProgressBar"), close("close");
		Rcpp::RObject barHandle;
		if(progress)
		{
			barHandle = txtProgressBar(Rcpp::Named("style") = 1, Rcpp::Named("min") = 0, Rcpp::Named("max") = 1000, Rcpp::Named("initial") = 0);
		}
		int dimension = matrix.nrow();
		unsigned long long C = (1ULL << dimension);
		for (unsigned long long k = 1ULL; k < C; k++)
		{
			rowsumprod = 1;
			int setBits = 0;
			for (int m = 0; m < dimension; m++)
			{
				if((k & (1ULL << m)) != 0ULL) setBits++;
			}
			// loop columns of submatrix #k
			for (int m = 0; m < dimension; m++)
			{
				rowsum = 0;
				// loop rows and compute rowsum
				for (int p = 0; p < dimension; p++)
				{
					if((k & (1ULL << p)) != 0ULL)
					{
						rowsum += matrix(m, p);
					}
				}
				// update product of rowsums
				rowsumprod *= rowsum;
				if (rowsumprod == 0) break;
			}
			if(setBits % 2 == 0) sum += rowsumprod;
			else sum -= rowsumprod;
			if(progress && k % 1000ULL == 0)
			{
				setTxtProgressBar.topLevelExec(barHandle, (int)((double)k*1000.0 / (double)C));
			}
		}
		if(progress)
		{
			close(barHandle);
		}
		if(dimension % 2 != 0) sum *= -1;
		return Rcpp::wrap(sum.str());
	END_RCPP
	}
}
