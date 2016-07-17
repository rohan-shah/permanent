source("./generateScenarios.R")
SCENARIO_INDEX <- as.integer(Sys.getenv("SCENARIO_INDEX"))


outputFile <- file.path("results", scenarios[SCENARIO_INDEX, "file"])
tmpFile <- paste0(outputFile, ".tmp")
library(permanent)
library(stringr)

method <- scenarios[SCENARIO_INDEX, "method"]
n <- scenarios[SCENARIO_INDEX, "n"]
matrix <- scenarios[SCENARIO_INDEX, "matrix"]
nReps <- scenarios[SCENARIO_INDEX, "nReps"]
alpha <- scenarios[SCENARIO_INDEX, "alpha"]

cat("SCENARIO_INDEX=", SCENARIO_INDEX, "\n", sep="")
cat("method=", method, "\n", sep="")

source("./getMatrices.R")

if(method == "IS")
{
	counter <- 1
	if(file.exists(outputFile))
	{
		load(outputFile)
		counter <- length(results)+1
	} else results <- list()
	while(counter < nReps + 1)
	{
		results[[counter]] <- importanceSampling(matrix = squareMatrix, seed = SCENARIO_INDEX + counter * 100000L, n = n, alpha = alpha)
		save(results, file = tmpFile)
		file.rename(from = tmpFile, to = outputFile)
		counter <- counter + 1
	}
} else if(method == "WOR")
{
	counter <- 1
	if(file.exists(outputFile))
	{
		load(outputFile)
		counter <- length(results)+1
	} else results <- list()
	while(counter < nReps + 1)
	{
		results[[counter]] <- withoutReplacement(matrix = squareMatrix, seed = SCENARIO_INDEX + counter * 100000L, n = n, alpha = alpha)
		save(results, file = tmpFile)
		file.rename(from = tmpFile, to = outputFile)
		counter <- counter + 1
	}
} else if(method == "WOR2")
{
	counter <- 1
	if(file.exists(outputFile))
	{
		load(outputFile)
		counter <- length(results)+1
	} else results <- list()
	while(counter < nReps + 1)
	{
		results[[counter]] <- withoutReplacement2(matrix = squareMatrix, seed = SCENARIO_INDEX + counter * 100000L, n = n, alpha = alpha)
		save(results, file = tmpFile)
		file.rename(from = tmpFile, to = outputFile)
		counter <- counter + 1
	}
} else if(method == "WOR3")
{
	counter <- 1
	if(file.exists(outputFile))
	{
		load(outputFile)
		counter <- length(results)+1
	} else results <- list()
	while(counter < nReps + 1)
	{
		results[[counter]] <- withoutReplacement3(matrix = squareMatrix, seed = SCENARIO_INDEX + counter * 100000L, n = n, alpha = alpha)
		save(results, file = tmpFile)
		file.rename(from = tmpFile, to = outputFile)
		counter <- counter + 1
	}
} else if(method == "WOR4")
{
	counter <- 1
	if(file.exists(outputFile))
	{
		load(outputFile)
		counter <- length(results)+1
	} else results <- list()
	while(counter < nReps + 1)
	{
		results[[counter]] <- withoutReplacement4(matrix = squareMatrix, seed = SCENARIO_INDEX + counter * 100000L, n = n, alpha = alpha)
		save(results, file = tmpFile)
		file.rename(from = tmpFile, to = outputFile)
		counter <- counter + 1
	}
} else
{
	stop("Unrecognized method")
}
