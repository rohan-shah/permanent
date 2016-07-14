#ifndef IMPORTANCE_SAMPLING_IMPL_HEADER_GUARD
#define IMPORTANCE_SAMPLING_IMPL_HEADER_GUARD
#include "includeMPFR.h"
#include <boost/numeric/ublas/matrix.hpp>
namespace permanent
{
	struct importanceSamplingArgs
	{
		int n;
		int seed;
		double alpha;
		mpfr_class estimate, estimatedVariance;
		boost::numeric::ublas::matrix<double> matrix;
	};
	void importanceSamplingImpl(importanceSamplingArgs& args);
}
#endif
