#Set the package name
SET(PACKAGE_NAME "xolotl.tests.reactants")

#Set the description
SET(PACKAGE_DESCRIPTION "Tests for the Xolotl reactants package")

#Include directories from the source and boost binaries
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/io)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/commandline)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/psiclusters)
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/neclusters)
<<<<<<< HEAD
=======
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore/reactants/feclusters)
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
include_directories(${CMAKE_SOURCE_DIR}/xolotlCore)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf)
include_directories(${CMAKE_SOURCE_DIR}/xolotlPerf/dummy)
include_directories(${Boost_BINARY_DIRS})

#Link the directories
link_directories(${CMAKE_SOURCE_DIR}/src/xolotlCore/reactants)


#Get the test files
file(GLOB tests *Tester.cpp)

#Create the utility library
add_library(testUtils STATIC SimpleReactionNetwork.cpp)
target_link_libraries(testUtils xolotlReactants)

#If boost was found, create tests
if(Boost_FOUND)
    #Make executables and link libraries for testers
    foreach(test ${tests})
        message(STATUS "Making test ${test}")
        get_filename_component(testName ${test} NAME_WE)
        add_executable(${testName} ${test})
        target_link_libraries(${testName} xolotlReactants xolotlCL xolotlPerf testUtils)
        add_test(${testName} ${testName}) 
        #add a label so the tests can be run separately
        set_property(TEST ${testName} PROPERTY LABELS ${PACKAGE_NAME})   
    endforeach(test ${tests})
endif(Boost_FOUND)
