#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "xolotlPerf/standard/EventCounter.h"

using namespace std;
using namespace xolotlPerf;

/**
 * This suite is responsible for testing the EventCounter.
 */
BOOST_AUTO_TEST_SUITE (EventCounter_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

	EventCounter tester("test");

<<<<<<< HEAD
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getName() "
						<< tester.getName() << "\n");
=======
	BOOST_TEST_MESSAGE(
			"\n" << "EventCounter Message: \n" << "tester.getName() " << tester.getName() << "\n");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Require that the name of this EventCounter is "test"
	BOOST_REQUIRE_EQUAL("test", tester.getName());
}

BOOST_AUTO_TEST_CASE(checkInitialValue) {

	EventCounter tester("test");

<<<<<<< HEAD
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getValue() "
						<< tester.getValue() << "\n" );

	// Require that the value of this EventCounter is 0
	BOOST_REQUIRE_EQUAL(0, tester.getValue());
=======
	BOOST_TEST_MESSAGE(
			"\n" << "EventCounter Message: \n" << "tester.getValue() " << tester.getValue() << "\n");

	// Require that the value of this EventCounter is 0
	BOOST_REQUIRE_EQUAL(0U, tester.getValue());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

}

BOOST_AUTO_TEST_CASE(checkCounting) {

	EventCounter tester("test");

<<<<<<< HEAD
	for(int i = 0; i < 3; i++){
=======
	for (int i = 0; i < 3; i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		//increment the EventCounter
		tester.increment();
	}

<<<<<<< HEAD
	BOOST_TEST_MESSAGE( "\n" << "EventCounter Message: \n" << "tester.getValue() = "
							 << tester.getValue() << "\n" );

	// Require that the value of this EventCounter is 3
	BOOST_REQUIRE_EQUAL(3, tester.getValue());

}


BOOST_AUTO_TEST_SUITE_END()





=======
	BOOST_TEST_MESSAGE(
			"\n" << "EventCounter Message: \n" << "tester.getValue() = " << tester.getValue() << "\n");

	// Require that the value of this EventCounter is 3
	BOOST_REQUIRE_EQUAL(3U, tester.getValue());

}

BOOST_AUTO_TEST_SUITE_END()

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
