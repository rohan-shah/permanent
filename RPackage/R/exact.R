exact <- function(matrix, progress = TRUE)
{
	return(mpfr(.Call("exact", matrix, progress, PACKAGE="permanent")));
}
