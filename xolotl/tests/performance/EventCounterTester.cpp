#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
<<<<<<< HEAD
<<<<<<< HEAD
#include "xolotlPerf/standard/EventCounter.h"
=======
#include "EventCounter.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include "EventCounter.h"
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

using namespace std;
using namespace xolotlPerf;

/**
 * This suite is responsible for testing the EventCounter.
 */
BOOST_AUTO_TEST_SUITE (EventCounter_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

	EventCounter tester("test");

<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_TEST_MESSAGE(
			"\n" << "EventCounter Message: \n" << "tester.getName() " << tester.getName() << "\n");
=======
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getName() " << tester.getName() << "\n"
					  );
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getName() " << tester.getName() << "\n"
					  );
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Require that the name of this EventCounter is "test"
	BOOST_REQUIRE_EQUAL("test", tester.getName());
}

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
BOOST_AUTO_TEST_CASE(checkInitialValue) {

	EventCounter tester("test");

<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_TEST_MESSAGE(
			"\n" << "EventCounter Message: \n" << "tester.getValue() " << tester.getValue() << "\n");

	// Require that the value of this EventCounter is 0
	BOOST_REQUIRE_EQUAL(0U, tester.getValue());
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getValue() " << tester.getValue() << "\n" );

	// Require that the value of this EventCounter is 0
	BOOST_REQUIRE_EQUAL(0, tester.getValue());
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

}

BOOST_AUTO_TEST_CASE(checkCounting) {

	EventCounter tester("test");

<<<<<<< HEAD
<<<<<<< HEAD
	for (int i = 0; i < 3; i++) {
=======
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getValue() = " << tester.getValue() << "\n" );

	for(int i = 0; i < 3; i++){
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getValue() = " << tester.getValue() << "\n" );

	for(int i = 0; i < 3; i++){
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

		//increment the EventCounter
		tester.increment();
	}

<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_TEST_MESSAGE(
			"\n" << "EventCounter Message: \n" << "tester.getValue() = " << tester.getValue() << "\n");

	// Require that the value of this EventCounter is 3
	BOOST_REQUIRE_EQUAL(3U, tester.getValue());

}

=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getValue() = " << tester.getValue() << "\n" );

	// Require that the value of this EventCounter is 3
	BOOST_REQUIRE_EQUAL(3, tester.getValue());
}


<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
BOOST_AUTO_TEST_SUITE_END()

