cmake_minimum_required(VERSION 3.5)
project(dgdemlog VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(DOS_PER_INCLUSION "/home/daniel/GenonLogiciels/C++Natif/bibliodg/entete" CACHE PATH "")
set(BIB_DGDIA "/home/daniel/GenonLogiciels/C++Natif/bibliodg/libdgbdial.so" CACHE PATH "")
#set(BIB_DGFIC "/home/daniel/GenonLogiciels/C++Natif/bibliodg/libdgfichier.so" CACHE PATH "")
#set(BIB_DGBLOC "/home/daniel/GenonLogiciels/C++Natif/bibliodg/libdgficbloc.so" CACHE PATH "")
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

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(FICRES_CPP resdgdemlog.cpp)
set(FICRES_XML dgdemlog.xml)

add_custom_command(
    OUTPUT ${FICRES_CPP}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --target=${CMAKE_CURRENT_BINARY_DIR}/${FICRES_CPP}
        --generate-source ${FICRES_XML}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ressource
	VERBATIM
	MAIN_DEPENDENCY ressource/${FICRES_XML}
	DEPENDS
	ressource/dgdemlog.css
)
set(SOURCE
    source/structureappli.h
    source/dgdemlog.cpp
    source/fenetre.h
    source/fenetre.cpp
    source/zonegraphique.h
    source/zonegraphique.cpp
    source/gerersession.h
    source/gerersession.cpp
    source/configurationobjet.h
    source/configurationobjet.cpp
    source/graphiquesurface.h
    source/graphiquesurface.cpp
    source/element.h
    source/element.cpp
    source/demarreobjet.h
    source/demarreobjet.cpp
    source/logiciel.h
    source/logiciel.cpp
    source/graphobjetactif.h
    source/graphobjetactif.cpp
    source/ancrage.h
    source/ancrage.cpp
    source/connexion.h
    source/connexion.cpp
#source/fichiertravail.h
#source/fichiertravail.cpp
#source/fichierconfiguration.h
#source/fichierconfiguration.cpp
    source/fichierlie.h
    source/fichierlie.cpp
)
set(ENRG
    enrg/enrgvariablemsa.h
    enrg/enrgvariablemsa.cpp
    enrg/enrgconfig.h
    enrg/enrgconfig.cpp
    enrg/enrgpolice.h
    enrg/enrgpolice.cpp
    enrg/enrgconnexion.h
    enrg/enrgconnexion.cpp
    enrg/enrgobjetctx.h
    enrg/enrgobjetctx.cpp
    enrg/enrgancre.h
    enrg/enrgancre.cpp
    enrg/enrggraph.h
    enrg/enrggraph.cpp
    enrg/enrglogiciel.h
    enrg/enrglogiciel.cpp
    enrg/enrgliaisonctx.h
    enrg/enrgliaisonctx.cpp
)
set(BLOC
	bloc/utilficbinbloc.cpp
	bloc/utilficbinbloc.h
	bloc/fblocsession.h
	bloc/fblocsession.cpp
	bloc/fbloccontexte.h
	bloc/fbloccontexte.cpp
	bloc/fblocobjetcontexte.h
	bloc/fblocobjetcontexte.cpp
	bloc/fblocprojet.h
	bloc/fblocprojet.cpp
	bloc/fblocconfig.h
	bloc/fblocconfig.cpp
)
set(TMPBIBL
	tmpbibl/dgpoint.h
	tmpbibl/dgchaineliste.h
	tmpbibl/dgpoint.cpp
	tmpbibl/dgchaineliste.cpp
	tmpbibl/dgfichier.h
	tmpbibl/dgfichier.cpp
	tmpbibl/dgficbloc.h
	tmpbibl/dgficbloc.cpp
)
set(DIALOG
	defdia/messagemsa.h
	defdia/infovariablemsa.h
	defdia/messagemsa.cpp
	defdia/infovariablemsa.cpp
	defdia/creerprojet/creerprojet.h
	defdia/creerprojet/creerprojet.cpp
	defdia/creercontexte/creercontexte.h
	defdia/creercontexte/creercontexte.cpp
	defdia/chargercontexte/chargercontexte.h
	defdia/chargercontexte/chargercontexte.cpp
	defdia/dialconfgen/dialogconfiggenerale.h
	defdia/dialconfgen/dialogconfiggenerale.cpp
	defdia/choisirpriorite/choisirpriorite.h
	defdia/choisirpriorite/choisirpriorite.cpp
	defdia/choisirfichierlie/choisirfichierlie.h
	defdia/choisirfichierlie/choisirfichierlie.cpp
	defdia/dialconfnouv/dialconfnouv.h
	defdia/dialconfnouv/dialconfnouv.cpp
)

add_executable(dgdemlog ${SOURCE} ${ENRG} ${BLOC} ${DIALOG} ${TMPBIBL} ${CMAKE_CURRENT_BINARY_DIR}/${FICRES_CPP} )

target_link_libraries(dgdemlog ${GTKMM_LIBRARIES} ${BIB_DGDIA} ${BIB_DGFIC} ${BIB_DGBLOC} ${BIB_DGDATE} )
#target_link_libraries(dgdemlog ${GTKMM_LIBRARIES} ${BIB_DGDIA} ${BIB_DGDATE} )

set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${FICRES_CPP}
    PROPERTIES GENERATED TRUE
)


