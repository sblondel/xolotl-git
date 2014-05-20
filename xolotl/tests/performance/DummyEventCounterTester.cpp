#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

<<<<<<< HEAD
#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/dummy/DummyEventCounter.h"
=======
#include <boost/test/included/unit_test.hpp>
#include <DummyEventCounter.h>
#include <string>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

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
	BOOST_REQUIRE_EQUAL(0U, tester.getValue());
=======
	BOOST_REQUIRE_EQUAL(0, tester.getValue());
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

}

BOOST_AUTO_TEST_CASE(checkCounting) {

	DummyEventCounter tester("test");

<<<<<<< HEAD
	for (int i = 0; i < 3; i++) {
		tester.increment();
	}

	BOOST_REQUIRE_EQUAL(0U, tester.getValue());

}

=======
	long count = 3;

	for(int i = 0; i < 3; i++){
		tester.increment();
	}

	BOOST_REQUIRE_EQUAL(0, tester.getValue());

}


>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
BOOST_AUTO_TEST_SUITE_END()

