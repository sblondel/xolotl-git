#Set the package name
SET(PACKAGE_NAME "xolotl.reactants")
#Set the description
SET(PACKAGE_DESCRIPTION "Xolotl Reactants")
#Set the library name
SET(LIBRARY_NAME "xolotlReactants")

#Collect all header filenames in this project 
#and glob them in HEADERS
<<<<<<< HEAD
file(GLOB HEADERS *.h psiclusters/*.h neclusters/*.h)

#Collect all of the cpp files in this folder 
#and the psiclusters folder and glob them in SRC
file(GLOB SRC *.cpp psiclusters/*.cpp neclusters/*.cpp)
=======
file(GLOB HEADERS *.h psiclusters/*.h)

#Collect all of the cpp files in this folder 
#and the psiclusters folder and glob them in SRC
file(GLOB SRC *.cpp psiclusters/*.cpp)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

#Include this directory so that the psiclusters can be built
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
<<<<<<< HEAD
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/neclusters)
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf/dummy)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf/standard)

#Add the library
<<<<<<< HEAD
add_library(${LIBRARY_NAME} STATIC ${SRC})
=======
add_library(${LIBRARY_NAME} SHARED ${SRC})
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
target_link_libraries(${LIBRARY_NAME} xolotlPerf xolotlIO)

#Install the xolotl header files
install(FILES ${HEADERS} DESTINATION include)
<<<<<<< HEAD
install(TARGETS ${LIBRARY_NAME} DESTINATION lib)
=======
install(TARGETS ${LIBRARY_NAME} DESTINATION lib)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
