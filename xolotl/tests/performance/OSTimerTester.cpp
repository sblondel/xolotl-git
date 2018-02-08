#define BOOST_TEST_MODULE Regression

#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/perfConfig.h"
#include "xolotlPerf/os/OSTimer.h"

<<<<<<< HEAD

using namespace std;
namespace xperf = xolotlPerf;


=======
using namespace std;
namespace xperf = xolotlPerf;

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
/**
 * This suite is responsible for testing the OSTimer.
 */
BOOST_AUTO_TEST_SUITE (OSTimer_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

	xperf::OSTimer tester("test");

<<<<<<< HEAD
	BOOST_TEST_MESSAGE( "\n" << "OSTimer Message: \n" << "tester.getName() = " << tester.getName() << "\n"
				  );
=======
	BOOST_TEST_MESSAGE(
			"\n" << "OSTimer Message: \n" << "tester.getName() = " << tester.getName() << "\n");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	//Require that the name of this Timer is "test"
	BOOST_REQUIRE_EQUAL("test", tester.getName());
}

<<<<<<< HEAD

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
BOOST_AUTO_TEST_CASE(checkTiming) {

	xperf::OSTimer tester("test");
	double sleepSeconds = 2.0;

<<<<<<< HEAD
    // Simulate some computation/communication with a sleep of known duration.
    // Time the duration of the operation.
=======
	// Simulate some computation/communication with a sleep of known duration.
	// Time the duration of the operation.
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	tester.start();
	sleep(sleepSeconds);
	tester.stop();

	//Output the difference between the wallclock timestamps when the timer was started and stopped
<<<<<<< HEAD
	BOOST_TEST_MESSAGE( "\n" << "OSTimer Message: \n" << "tester.getName() = " << tester.getName() << "\n"
			  << "tester.getValue() = " << tester.getValue() << "s" << "\n"
			  << "tester.getValue() - " << sleepSeconds << "s = " << tester.getValue()-sleepSeconds << "s");

	// Require that the value of this Timer is within 3% of the 
    // duration of the sleep.
	BOOST_REQUIRE_CLOSE(sleepSeconds, tester.getValue(),0.03);
	BOOST_REQUIRE_EQUAL("s", tester.getUnits());
}


BOOST_AUTO_TEST_CASE(accumulate)
{
    xperf::OSTimer tester("test");

    const unsigned int sleepSeconds = 2;

    tester.start();
    sleep(sleepSeconds);
    tester.stop();
    tester.start();
    sleep(sleepSeconds);
    tester.stop();
    
    double timerValue = tester.getValue();
    double expValue = 2*sleepSeconds;   // we had two sleep intervals
    BOOST_REQUIRE_CLOSE(expValue, timerValue, 0.03);
}


BOOST_AUTO_TEST_CASE(reset)
{
    xperf::OSTimer tester("test");

    const unsigned int sleepSeconds = 2;

    tester.start();
    sleep(sleepSeconds);
    tester.stop();
    tester.reset();
    BOOST_REQUIRE_EQUAL(tester.getValue(), 0.0);
    tester.start();
    sleep(sleepSeconds);
    tester.stop();

    double timerValue = tester.getValue();
    double expValue = sleepSeconds;     // should only represent last sleep interval
    BOOST_REQUIRE_CLOSE(expValue, timerValue, 0.03);
=======
	BOOST_TEST_MESSAGE(
			"\n" << "OSTimer Message: \n" << "tester.getName() = " << tester.getName() << "\n" << "tester.getValue() = " << tester.getValue() << "s" << "\n" << "tester.getValue() - " << sleepSeconds << "s = " << tester.getValue()-sleepSeconds << "s");

	// Require that the value of this Timer is within 3% of the 
	// duration of the sleep.
	BOOST_REQUIRE_CLOSE(sleepSeconds, tester.getValue(), 0.03);
	BOOST_REQUIRE_EQUAL("s", tester.getUnits());
}

BOOST_AUTO_TEST_CASE(accumulate) {
	xperf::OSTimer tester("test");

	const unsigned int sleepSeconds = 2;

	tester.start();
	sleep(sleepSeconds);
	tester.stop();
	tester.start();
	sleep(sleepSeconds);
	tester.stop();

	double timerValue = tester.getValue();
	double expValue = 2 * sleepSeconds;   // we had two sleep intervals
	BOOST_REQUIRE_CLOSE(expValue, timerValue, 0.03);
}

BOOST_AUTO_TEST_CASE(reset) {
	xperf::OSTimer tester("test");

	const unsigned int sleepSeconds = 2;

	tester.start();
	sleep(sleepSeconds);
	tester.stop();
	tester.reset();
	BOOST_REQUIRE_EQUAL(tester.getValue(), 0.0);
	tester.start();
	sleep(sleepSeconds);
	tester.stop();

	double timerValue = tester.getValue();
	double expValue = sleepSeconds; // should only represent last sleep interval
	BOOST_REQUIRE_CLOSE(expValue, timerValue, 0.03);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

BOOST_AUTO_TEST_SUITE_END()
