cmake_minimum_required(VERSION 3.5)
project(creercontexte VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DOS_PER_INCLUSION "/home/daniel/GenonLogiciels/C++Natif/bibliodg/entete" CACHE PATH "")
set(BIB_DGDATE "/home/daniel/GenonLogiciels/C++Natif/bibliodg/libdgdiadate.so" CACHE PATH "")

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0>=4.1 )
if (GTKMM_FOUND)
    include_directories( ${GTKMM_INCLUDE_DIRS} )  
    link_directories( ${GTKMM_LIBRARY_DIRS} )
	add_compile_definitions( OKGTKMMSTRINGLIST )
else ()
  message(FATAL_ERROR "GTKmm introuvable")
endif ()

include_directories(${DOS_PER_INCLUSION})

set(SOURCE
    tbdcreercontexte.cpp
    creercontexte.cpp
    creercontexte.h
    )
set(AUTRE
	../../../tmpbibl/dgchaineliste.cpp
	../../../tmpbibl/dgchaineliste.h
)

add_executable(tbdcreercontexte ${SOURCE} ${AUTRE})

target_link_libraries(tbdcreercontexte ${GTKMM_LIBRARIES} ${BIB_DGDATE} )

