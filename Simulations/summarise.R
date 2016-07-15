source("./generateScenarios.R")
library(Rmpfr)
allResults <- list()
for(i in 1:nrow(scenarios))
{
	path <- file.path("results", scenarios[i, "file"])
	if(file.exists(path))
	{
		load(path)
		allResults[[i]] <- results
	}
}
secondsPerRun <- lapply(allResults, function(x) unlist(lapply(x, function(y) difftime(y@end, y@start, units = "secs"))))
averageSecondsPerRun <- unlist(lapply(secondsPerRun, function(x) if(is.null(x)) NA else mean(x)))
averageEstimatesFunc <- function(x)
{
	if(is.null(x) || length(x) == 0)
	{
		return(NA)
	}
	else 
	{
		return(as.numeric(mean(do.call(c, lapply(x, function(y) y@estimate)))))
	}
}
averageEstimates <- do.call(c, lapply(allResults, averageEstimatesFunc))

varianceFunc <- function(x)
{
	if(is.null(x) || length(x) == 0)
	{
		return(NA)
	}
	if(class(x[[1]]) == "withoutReplacementResult")
	{
		values <- do.call(c, lapply(x, function(y) y@estimate))
		firstMoment <- sum(values) / x[[1]]@n
		secondMoment <- sum(values * values) / x[[1]]@n
		return(as.numeric(secondMoment - firstMoment * firstMoment))
	}
	else 
	{
		return(as.numeric(mean(do.call(c, lapply(x, function(y) y@estimatedVariance)))))
	}
}
variances <- do.call(c, lapply(allResults, varianceFunc))
workNormalizedVariance <- as.numeric(variances * averageSecondsPerRun)

relativeErrors <- sqrt(variances) / averageEstimates
wnrv <- as.numeric(variances * averageSecondsPerRun / (averageEstimates^2))

save(allResults, averageEstimates, secondsPerRun, variances, workNormalizedVariance, wnrv, relativeErrors, file = "summarised.RData")
