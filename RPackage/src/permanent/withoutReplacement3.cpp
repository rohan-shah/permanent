#include "withoutReplacement3.h"
#include "withoutReplacement3Impl.h"
namespace permanent
{
	SEXP withoutReplacement3(SEXP n_sexp, SEXP matrix_sexp, SEXP seed_sexp, SEXP alpha_sexp)
	{
	BEGIN_RCPP
		int n = Rcpp::as<int>(n_sexp);
		Rcpp::NumericMatrix matrix = Rcpp::as<Rcpp::NumericMatrix>(matrix_sexp);
		double alpha = Rcpp::as<double>(alpha_sexp);
		int seed = Rcpp::as<int>(seed_sexp);
		withoutReplacementArgs args;
		args.n = n;
		args.matrix.resize(matrix.nrow(), matrix.ncol());
		for(int i = 0; i < matrix.nrow(); i++)
		{
			for(int j = 0; j < matrix.ncol(); j++)
			{
				args.matrix(i, j) = matrix(i, j);
			}
		}
		args.seed = seed;
		args.alpha = alpha;

		withoutReplacement3Impl(args);
		return Rcpp::wrap(args.estimate.str());
	END_RCPP
	}
}

