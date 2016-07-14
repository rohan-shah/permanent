#include "importanceSampling.h"
#include "importanceSamplingImpl.h"
namespace permanent
{
	SEXP importanceSampling(SEXP n_sexp, SEXP matrix_sexp, SEXP seed_sexp, SEXP alpha_sexp)
	{
	BEGIN_RCPP
		int n = Rcpp::as<int>(n_sexp);
		Rcpp::NumericMatrix matrix = Rcpp::as<Rcpp::NumericMatrix>(matrix_sexp);
		double alpha = Rcpp::as<double>(alpha_sexp);
		int seed = Rcpp::as<int>(seed_sexp);
		importanceSamplingArgs args;
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

		importanceSamplingImpl(args);
		Rcpp::List retVal = Rcpp::List::create(Rcpp::Named("estimate") = args.estimate.str(), Rcpp::Named("estimatedVariance") = args.estimatedVariance.str());
		return retVal;
	END_RCPP
	}
}

