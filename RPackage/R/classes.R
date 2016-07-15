setClass("importanceSamplingResult", slots = list(call = "call", start = "POSIXct", end = "POSIXct", n = "integer", matrix = "matrix", alpha = "numeric", seed = "integer", estimate = "mpfr", estimatedVariance = "mpfr"))
setClass("withoutReplacementResult", slots = list(call = "call", start = "POSIXct", end = "POSIXct", n = "integer", matrix = "matrix", alpha = "numeric", seed = "integer", estimate = "mpfr"))


