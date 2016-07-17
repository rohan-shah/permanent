#ifndef EXACT_R_PACKAGE_HEADER_GUARD
#define EXACT_R_PACKAGE_HEADER_GUARD
#include <Rcpp.h>
namespace permanent
{
	SEXP exact(SEXP matrix_sexp, SEXP progress_sexp);
}
#endif
