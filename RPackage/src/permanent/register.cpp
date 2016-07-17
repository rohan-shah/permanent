#include <Rcpp.h>
#include <internal.h>
#ifdef _MSC_VER
	#undef RcppExport
	#define RcppExport extern "C" __declspec(dllexport)
#endif
#include "importanceSampling.h"
#include "withoutReplacement.h"
#include "withoutReplacement2.h"
#include "withoutReplacement3.h"
#include "withoutReplacement4.h"
#include "exact.h"
extern "C" const char* package_name = "permanent";
R_CallMethodDef callMethods[] = 
{
	{"importanceSampling", (DL_FUNC)&permanent::importanceSampling, 4},
	{"withoutReplacement", (DL_FUNC)&permanent::withoutReplacement, 4},
	{"withoutReplacement2", (DL_FUNC)&permanent::withoutReplacement2, 4},
	{"withoutReplacement3", (DL_FUNC)&permanent::withoutReplacement3, 4},
	{"withoutReplacement4", (DL_FUNC)&permanent::withoutReplacement4, 4},
	{"exact", (DL_FUNC)&permanent::exact, 2},
	{NULL, NULL, 0}
};
RcppExport void R_init_permanent(DllInfo *info)
{
	std::vector<R_CallMethodDef> callMethodsVector;
	R_CallMethodDef* packageCallMethods = callMethods;
	while(packageCallMethods->name != NULL) packageCallMethods++;
	callMethodsVector.insert(callMethodsVector.begin(), callMethods, packageCallMethods);

	R_CallMethodDef* RcppStartCallMethods = Rcpp_get_call();
	R_CallMethodDef* RcppEndCallMethods = RcppStartCallMethods;
	while(RcppEndCallMethods->name != NULL) RcppEndCallMethods++;
	callMethodsVector.insert(callMethodsVector.end(), RcppStartCallMethods, RcppEndCallMethods);
	R_CallMethodDef blank = {NULL, NULL, 0};
	callMethodsVector.push_back(blank);

	R_registerRoutines(info, NULL, &(callMethodsVector[0]), NULL, NULL);
	init_Rcpp_cache();
}
