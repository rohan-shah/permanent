#ifndef WITHOUT_REPLACEMENT_2_R_PACKAGE_HEADER_GUARD
#define WITHOUT_REPLACEMENT_2_R_PACKAGE_HEADER_GUARD
#include <Rcpp.h>
namespace permanent
{
	SEXP withoutReplacement2(SEXP n, SEXP matrix, SEXP seed, SEXP alpha);
}
#endif
