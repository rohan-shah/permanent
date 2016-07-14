#ifndef IMPORTANCE_SAMPLING_R_PACKAGE_HEADER_GUARD
#define IMPORTANCE_SAMPLING_R_PACKAGE_HEADER_GUARD
#include <Rcpp.h>
namespace permanent
{
	SEXP importanceSampling(SEXP n, SEXP matrix, SEXP seed, SEXP alpha);
}
#endif
