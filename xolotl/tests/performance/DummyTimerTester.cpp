#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/dummy/DummyTimer.h"

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

BOOST_AUTO_TEST_SUITE_END()




=======
BOOST_AUTO_TEST_SUITE_END()

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
