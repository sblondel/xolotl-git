#Set the package name
SET(PACKAGE_NAME "xolotl.commandline")
#Set the description
<<<<<<< HEAD
<<<<<<< HEAD
SET(PACKAGE_DESCRIPTION "Xolotl Command Line Option Handling")
#Set the library name
SET(LIBRARY_NAME "xolotlCL")

#Collect all header filenames in this project
#and glob them in HEADERS
file(GLOB HEADERS *.h optionhandlers/*.h)
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
SET(PACKAGE_DESCRIPTION "Xolotl Command Line Handling")
#Set the library name
SET(LIBRARY_NAME "xolotlCL")

#Collect all header filenames in this project 
#and glob them in HEADERS
file(GLOB HEADERS *.h)
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#Grab all of the source files
file(GLOB SRC *.cpp)

# Where to look for include files
include_directories(${CMAKE_SOURCE_DIR})
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline/optionhandlers)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf/)

#Add a library to hold the command line handling code
add_library(${LIBRARY_NAME} STATIC ${SRC})
target_link_libraries(${LIBRARY_NAME})
=======
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624

#Add a library to hold the command line handling code
add_library(${LIBRARY_NAME} STATIC ${SRC})
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)

#Add a library to hold the command line handling code
add_library(${LIBRARY_NAME} STATIC ${SRC})
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#Install the xolotl header files
install(FILES ${HEADERS} DESTINATION include)
