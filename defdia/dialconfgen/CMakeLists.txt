cmake_minimum_required(VERSION 3.5)
project(dialconfgen VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0>=4.1 )
if (GTKMM_FOUND)
    include_directories( ${GTKMM_INCLUDE_DIRS} )  
    link_directories( ${GTKMM_LIBRARY_DIRS} )
else ()
  message(FATAL_ERROR "GTKmm introuvable")
endif ()

set(SOURCE
    dialogconfiggenerale.h
    dialogconfiggenerale.cpp
    tbddialconfgen.cpp
)

add_executable(tbddialconfgen ${SOURCE})

target_link_libraries(tbddialconfgen ${GTKMM_LIBRARIES} )

