library(permanent)
methods <- c("pathological16", "pathological16_2", "A1", "A2", "A3", "A4", "A5", "A6")
exact <- list()
for(method in methods)
{
	matrix <- method
	source("./getMatrices.R")
	exact[[method]] <- exact(squareMatrix, progress=TRUE)
}
save(exact, file = "./exact.RData")
