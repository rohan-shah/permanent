withoutReplacement3 <- function(matrix, n, seed, alpha)
{
	start <- Sys.time()
	result <- .Call("withoutReplacement3", n, matrix, seed, alpha, PACKAGE="permanent")
	end <- Sys.time();
	return(new("withoutReplacementResult", call = match.call(), n = as.integer(n), matrix = matrix, seed = as.integer(seed), alpha = as.numeric(alpha), estimate = mpfr(result), start = start, end = end))
}
