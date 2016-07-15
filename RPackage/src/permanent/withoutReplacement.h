#ifndef WITHOUT_REPLACEMENT_R_PACKAGE_HEADER_GUARD
#define WITHOUT_REPLACEMENT_R_PACKAGE_HEADER_GUARD
#include <Rcpp.h>
namespace permanent
{
	SEXP withoutReplacement(SEXP n, SEXP matrix, SEXP seed, SEXP alpha);
}
#endif
