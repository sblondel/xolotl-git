#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <CvsXYDataProvider.h>

using namespace std;
using namespace xolotlViz;

/**
 * This suite is responsible for testing the CvsXYDataProvider.
 */
BOOST_AUTO_TEST_SUITE(CvsXYDataProvider_testSuite)

/**
 * Method checking the ability to use a name.
 */
BOOST_AUTO_TEST_CASE(checkName) {
	// Create myCvsXYDataProvider
	auto myCvsXYDataProvider = make_shared<CvsXYDataProvider>("myCvsXYDataProvider");

	BOOST_REQUIRE_EQUAL("myCvsXYDataProvider", myCvsXYDataProvider->getName());
}

/**
 * Method checking you can get the axis vectors.
 */
BOOST_AUTO_TEST_CASE(checkGetVector) {
	// Create myCvsXYDataProvider
	auto myCvsXYDataProvider = make_shared<CvsXYDataProvider>("myCvsXYDataProvider");

	// Create a Point vector
	auto myPoints = make_shared< vector <Point> >();

	// And fill it with some Point
	Point aPoint;
	aPoint.value = 3.0; aPoint.t = 1.0; aPoint.x = 1.0; aPoint.y = 1.0;
	myPoints->push_back(aPoint);
	aPoint.value = 2.0; aPoint.t = 3.0; aPoint.x = 2.0; aPoint.y = 1.0;
	myPoints->push_back(aPoint);
	aPoint.value = 5.0; aPoint.t = 6.0; aPoint.x = 3.0; aPoint.y = 1.0;
	myPoints->push_back(aPoint);
	aPoint.value = 8.0; aPoint.t = 8.0; aPoint.x = 1.0; aPoint.y = 2.0;
	myPoints->push_back(aPoint);
	aPoint.value = 1.0e-20; aPoint.t = 7.0; aPoint.x = 2.0; aPoint.y = 2.0;
	myPoints->push_back(aPoint);
	aPoint.value = -1.0; aPoint.t = 7.0; aPoint.x = 3.0; aPoint.y = 2.0;
	myPoints->push_back(aPoint);

	// Set these points in the myDataProvider
	myCvsXYDataProvider->setPoints(myPoints);

	// Get the vectors back
	auto axis1Vector = myCvsXYDataProvider->getAxis1Vector();
	auto axis2Vector = myCvsXYDataProvider->getAxis2Vector();
	auto axis3Vector = myCvsXYDataProvider->getAxis3Vector();

	// First check the size of the vectors
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(axis1Vector.size(), 4);
	BOOST_REQUIRE_EQUAL(axis2Vector.size(), 3);
	BOOST_REQUIRE_EQUAL(axis3Vector.size(), myPoints->size());

	// Loop on all the points in myPoints
	for (int i = 0; i < myPoints->size() - 2; i++) {
=======
	BOOST_REQUIRE_EQUAL(axis1Vector.size(), 4U);
	BOOST_REQUIRE_EQUAL(axis2Vector.size(), 3U);
	BOOST_REQUIRE_EQUAL(axis3Vector.size(), myPoints->size());

	// Loop on all the points in myPoints
	for (unsigned int i = 0; i < myPoints->size() - 2; i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		BOOST_REQUIRE_EQUAL(axis3Vector.at(i), myPoints->at(i).value);
	}

	// Check that the DataProvider returns 1.0e-16 for values
	// that are too small or negative
	BOOST_REQUIRE_EQUAL(axis3Vector.at(4), 1.0e-16);
	BOOST_REQUIRE_EQUAL(axis3Vector.at(5), 1.0e-16);

	return;
}

BOOST_AUTO_TEST_SUITE_END()
