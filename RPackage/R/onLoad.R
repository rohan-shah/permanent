.onLoad <- function(libname, pkgname)
{
	library.dynam(package="permanent", chname="permanent", lib.loc = .libPaths())
}
