methods <- c("IS", "WOR", "WOR2")
matrices <- c("A1", "A2", "A3", "A4", "A5", "A6")
scenarios <- expand.grid(method = methods, matrix = matrices, n = 20000, stringsAsFactors=FALSE)

scenarios$file <- apply(scenarios, 1, function(x) paste0(x["method"], "-", x["matrix"], "-", as.integer(x["n"]), ".RData", sep=""))
scenarios$nReps <- 100
scenarios$alpha <- sapply(scenarios$matrix, function(x)
		{
			if(x %in% c("A3", "A4")) return(0.5)
			return(1)
		})
