#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

<<<<<<< HEAD
<<<<<<< HEAD
#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/dummy/DummyEventCounter.h"
=======
#include <boost/test/included/unit_test.hpp>
#include <DummyEventCounter.h>
#include <string>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include <boost/test/included/unit_test.hpp>
#include <DummyEventCounter.h>
#include <string>
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

using namespace std;
using namespace xolotlPerf;

/**
 * This suite is responsible for testing the DummyEventCounter.
 */
BOOST_AUTO_TEST_SUITE (DummyEventCounter_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

	DummyEventCounter tester("test");

	BOOST_REQUIRE_EQUAL("unused", tester.getName());
}

BOOST_AUTO_TEST_CASE(checkInitialValue) {

	DummyEventCounter tester("test");

<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(0U, tester.getValue());
=======
	BOOST_REQUIRE_EQUAL(0, tester.getValue());
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE_EQUAL(0, tester.getValue());
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

}

BOOST_AUTO_TEST_CASE(checkCounting) {

	DummyEventCounter tester("test");

<<<<<<< HEAD
<<<<<<< HEAD
	for (int i = 0; i < 3; i++) {
		tester.increment();
	}

	BOOST_REQUIRE_EQUAL(0U, tester.getValue());

}

=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	long count = 3;

	for(int i = 0; i < 3; i++){
		tester.increment();
	}

	BOOST_REQUIRE_EQUAL(0, tester.getValue());

}


<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
BOOST_AUTO_TEST_SUITE_END()

