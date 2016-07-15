#ifndef WITHOUT_REPLACEMENT_IMPL_HEADER_GUARD
#define WITHOUT_REPLACEMENT_IMPL_HEADER_GUARD
#include "includeMPFR.h"
#include <boost/numeric/ublas/matrix.hpp>
namespace permanent
{
	struct withoutReplacementArgs
	{
		int n;
		int seed;
		double alpha;
		mpfr_class estimate;
		boost::numeric::ublas::matrix<double> matrix;
	};
	void withoutReplacementImpl(withoutReplacementArgs& args);
}
#endif
