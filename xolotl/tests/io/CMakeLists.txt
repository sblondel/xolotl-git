#Set the package name
SET(PACKAGE_NAME "xolotl.tests.io")

#Set the description
SET(PACKAGE_DESCRIPTION "Xolotl I/O tests")

#include directories from the source and boost binaries
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
=======
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf/dummy)
include_directories(${Boost_BINARY_DIRS})
<<<<<<< HEAD
include_directories(${MPI_INCLUDE_PATH})
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
include_directories(${Boost_BINARY_DIRS})
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#link the directories
link_directories(${CMAKE_SOURCE_DIR}/src/xolotlCore/io)

#Get the test files
file(GLOB tests *.cpp)

#If boost was found, create tests
if(Boost_FOUND)
    #Make executables and link libraries for testers
    foreach(test ${tests})
        message(STATUS "Making test ${test}")
        get_filename_component(testName ${test} NAME_WE)
        add_executable(${testName} ${test})
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
        target_link_libraries(${testName} xolotlReactants ${HDF5_LIBRARIES} ${MPI_LIBRARIES})
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
        target_link_libraries(${testName} xolotlReactants testUtils xolotlPerf)
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
=======
        target_link_libraries(${testName} xolotlReactants testUtils xolotlPerf)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
        add_test(${testName} ${testName}) 
        #add a label so the tests can be run separately
        set_property(TEST ${testName} PROPERTY LABELS ${PACKAGE_NAME})   
    endforeach(test ${tests})
endif(Boost_FOUND)