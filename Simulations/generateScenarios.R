methods <- c("IS", "WOR", "WOR2", "WOR3", "WOR4")
matrices <- c("A1", "A2", "A3", "A4", "A5", "A6", "pathological16", "pathological16_2")
scenarios <- expand.grid(method = methods, matrix = matrices, n = 20000, stringsAsFactors=FALSE)

scenarios$file <- apply(scenarios, 1, function(x) paste0(x["method"], "-", x["matrix"], "-", as.integer(x["n"]), ".RData", sep=""))
scenarios$nReps <- 400
scenarios$alpha <- sapply(scenarios$matrix, function(x)
		{
			if(x %in% c("A3", "A4")) return(0.5)
			return(1)
		})
