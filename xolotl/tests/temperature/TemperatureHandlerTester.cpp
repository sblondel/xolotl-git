#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <TemperatureHandler.h>

using namespace std;
using namespace xolotlCore;

/**
 * The test suite is responsible for testing the TemperatureHandler.
 */
BOOST_AUTO_TEST_SUITE (TemperatureHandlerTester_testSuite)

BOOST_AUTO_TEST_CASE(check_getTemperature) {
	// Create the temperature handler
<<<<<<< HEAD
	auto testTemp = make_shared<TemperatureHandler>(1000);
=======
	auto testTemp = make_shared<TemperatureHandler>(1000.0);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Create a time
	double currTime = 1.0;

<<<<<<< HEAD
	std::vector<double> x = {1.142857142857143, 0.0, 0.0};
	// x is a gridpoint in PetscSolver, RHSFunction
	//x=1.142857142857143=8/7 where x = xi * h with xi=1, h=1.142857142857143

	double temp = testTemp->getTemperature(x, 1);

	BOOST_TEST_MESSAGE( "\n" << "\nTemperatureHandlerTester Message: \n"
						<< "temperature = " << temp << " at "
						<< "(" << x[0] << "," << x[1] << "," << x[2] << ") "
						<< "at time = " << currTime << "\n");
	BOOST_REQUIRE_EQUAL(temp, 1000.0);
=======
	std::vector<double> x = {1.0, 0.0, 0.0};

	// Check the temperature
	double temp = testTemp->getTemperature(x, currTime);
	BOOST_REQUIRE_CLOSE(temp, 1000.0, 0.001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

BOOST_AUTO_TEST_SUITE_END()
