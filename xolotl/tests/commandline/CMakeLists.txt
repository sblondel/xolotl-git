#Set the package name
SET(PACKAGE_NAME "xolotl.tests.commandline")

#Set the description
SET(PACKAGE_DESCRIPTION "Tests for the Xolotl commandline package")

    
# Where to look for include files.
include_directories(${CMAKE_SOURCE_DIR})
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf)
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
include_directories(${Boost_BINARY_DIRS}) 

# Figure out which tests to build
file(GLOB tests *Tester.cpp)
    
#If boost was found, create tests
if(Boost_FOUND)

    #Make executables and link libraries for testers
    foreach(test ${tests})
        message(STATUS "Making test ${test}")
        get_filename_component(testName ${test} NAME_WE)
        add_executable(${testName} ${test})
        target_link_libraries(${testName} xolotlCL)
        add_test(${testName} ${testName}) 
        #add a label so the tests can be run separately
        set_property(TEST ${testName} PROPERTY LABELS ${PACKAGE_NAME})   
    endforeach(test ${tests})

endif(Boost_FOUND)

