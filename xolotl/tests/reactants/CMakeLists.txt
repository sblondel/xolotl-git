#Set the package name
SET(PACKAGE_NAME "xolotl.tests.reactants")

#Set the description
SET(PACKAGE_DESCRIPTION "Tests for the Xolotl reactants package")

#Include directories from the source and boost binaries
include_directories(${CMAKE_SOURCE_DIR})
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/neclusters)
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf/dummy)
include_directories(${Boost_BINARY_DIRS})

#Link the directories
link_directories(${CMAKE_SOURCE_DIR}/src/xolotlCore/reactants)

#Get the test files
file(GLOB tests *Tester.cpp)

#Create the utility library
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
add_library(testUtils STATIC SimpleReactionNetwork.cpp)
target_link_libraries(testUtils xolotlReactants)
=======
add_library(testUtils SimpleReactionNetwork.cpp)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
add_library(testUtils STATIC SimpleReactionNetwork.cpp)
target_link_libraries(testUtils xolotlReactants)
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
add_library(testUtils STATIC SimpleReactionNetwork.cpp)
target_link_libraries(testUtils xolotlReactants)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#If boost was found, create tests
if(Boost_FOUND)
    #Make executables and link libraries for testers
    foreach(test ${tests})
        message(STATUS "Making test ${test}")
        get_filename_component(testName ${test} NAME_WE)
        add_executable(${testName} ${test})
<<<<<<< HEAD
<<<<<<< HEAD
        target_link_libraries(${testName} xolotlReactants xolotlCL xolotlPerf testUtils)
=======
        target_link_libraries(${testName} xolotlReactants testUtils xolotlPerf)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
        target_link_libraries(${testName} xolotlReactants testUtils xolotlPerf)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
        add_test(${testName} ${testName}) 
        #add a label so the tests can be run separately
        set_property(TEST ${testName} PROPERTY LABELS ${PACKAGE_NAME})   
    endforeach(test ${tests})
endif(Boost_FOUND)
