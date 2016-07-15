project(permanent)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(Boost_USE_STATIC_LIBS	OFF)
set(Boost_USE_MULTITHREADED	ON)
set(Boost_USE_STATIC_RUNTIME	OFF)

if(CMAKE_COMPILER_IS_GNUCC)
	add_definitions("-Wall")
endif()

#Find boost packages
find_package(Boost 1.53.0 REQUIRED)
find_package(sampling REQUIRED)
if(WIN32)
	find_package(mpfr)
	find_package(mpir)

	#If we're on windows, Start copying dlls
	set(BUILD_TYPES Release Debug RelWithDebInfo MinSizeRel)
	set(BOOST_BUILD_TYPES Release Debug Release Release)
	foreach(val RANGE 3)
		list(GET BUILD_TYPES ${val} BUILD_TYPE)
		list(GET BOOST_BUILD_TYPES ${val} BOOST_BUILD_TYPE)
		string(TOUPPER ${BOOST_BUILD_TYPE} BOOST_BUILD_TYPE_UPPER)
		
		#Now for MPFR
		get_target_property(MPFR_LOCATION mpfr "LOCATION_${BOOST_BUILD_TYPE}")
		file(COPY "${MPFR_LOCATION}" DESTINATION "${CMAKE_BINARY_DIR}/${BUILD_TYPE}/")

		#Now for MPIR
		get_target_property(MPIR_LOCATION mpir "LOCATION_${BOOST_BUILD_TYPE}")
		file(COPY "${MPIR_LOCATION}" DESTINATION "${CMAKE_BINARY_DIR}/${BUILD_TYPE}/")
	endforeach()
else()
	#mpfr needs to be listed as an imported target so that we can use target_link_libraries later on. If we don't have this then it just adds a -lmpfr which probably picks up the wrong thing. 
	find_library(mpfr_LIBRARY mpfr)
	add_library(mpfr SHARED IMPORTED)
	set_target_properties(mpfr PROPERTIES IMPORTED_LOCATION ${mpfr_LIBRARY})
endif()
add_subdirectory(copyText)
add_subdirectory(common)
add_subdirectory(RPackage)
find_package(R REQUIRED)
if(WIN32)
	install(CODE "execute_process(COMMAND \"${R_COMMAND}\" CMD INSTALL --no-multiarch RPackage/\$\{CMAKE_INSTALL_CONFIG_NAME\} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})")
else()
	install(CODE "execute_process(COMMAND \"${R_COMMAND}\" CMD INSTALL RPackage/ WORKING_DIRECTORY ${CMAKE_BINARY_DIR})")
endif()
