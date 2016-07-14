importanceSampling <- function(matrix, n, seed, alpha)
{
	start <- Sys.time()
	result <- .Call("importanceSampling", n, matrix, seed, alpha, PACKAGE="permanent")
	end <- Sys.time();
	return(new("importanceSamplingResult", call = match.call(), n = as.integer(n), matrix = matrix, seed = as.integer(seed), alpha = as.numeric(alpha), estimate = mpfr(result$estimate), estimatedVariance = mpfr(result$estimatedVariance), start = start, end = end))
}
