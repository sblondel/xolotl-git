#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

<<<<<<< HEAD
<<<<<<< HEAD
#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/dummy/DummyTimer.h"
=======
#include <boost/test/included/unit_test.hpp>
#include <DummyTimer.h>
#include <string>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include <boost/test/included/unit_test.hpp>
#include <DummyTimer.h>
#include <string>
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

using namespace std;
using namespace xolotlPerf;

/**
 * This suite is responsible for testing the DummyTimer.
 */
BOOST_AUTO_TEST_SUITE (DummyTimer_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

	DummyTimer tester("test");

	BOOST_REQUIRE_EQUAL("unused", tester.getName());

}

BOOST_AUTO_TEST_CASE(checkInitialValue) {

	DummyTimer tester("test");

	BOOST_REQUIRE_EQUAL(0, tester.getValue());

}

BOOST_AUTO_TEST_CASE(checkTiming) {

	DummyTimer tester("test");

	tester.start();
	sleep(3);
	tester.stop();

	BOOST_REQUIRE_EQUAL(0, tester.getValue());
	BOOST_REQUIRE_EQUAL("", tester.getUnits());

}

<<<<<<< HEAD
<<<<<<< HEAD
BOOST_AUTO_TEST_SUITE_END()

=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

BOOST_AUTO_TEST_SUITE_END()




<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
