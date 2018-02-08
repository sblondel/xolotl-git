#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <CvsXDataProvider.h>

using namespace std;
using namespace xolotlViz;

/**
 * This suite is responsible for testing the CvsXDataProvider.
 */
BOOST_AUTO_TEST_SUITE(CvsXDataProvider_testSuite)

/**
 * Method checking the ability to use a name.
 */
BOOST_AUTO_TEST_CASE(checkName) {
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	// Create myCvsXDataProvider
	auto myCvsXDataProvider = make_shared<CvsXDataProvider>("myCvsXDataProvider");

	BOOST_REQUIRE_EQUAL("myCvsXDataProvider", myCvsXDataProvider->getName());
<<<<<<< HEAD
<<<<<<< HEAD

	return;
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

/**
 * Method checking you can get the axis vectors.
 */
BOOST_AUTO_TEST_CASE(checkGetVector) {
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	// Create myCvsXDataProvider
	auto myCvsXDataProvider = make_shared<CvsXDataProvider>("myCvsXDataProvider");

	// Create a Point vector
	auto myPoints = make_shared< vector <Point> >();

	// And fill it with some Point
	Point aPoint;
	aPoint.value = 3.0; aPoint.t = 1.0; aPoint.x = 2.0;
	myPoints->push_back(aPoint);
	aPoint.value = 2.0; aPoint.t = 3.0; aPoint.x = 2.0;
	myPoints->push_back(aPoint);
	aPoint.value = 5.0; aPoint.t = 6.0; aPoint.x = -2.0;
	myPoints->push_back(aPoint);
	aPoint.value = 8.0; aPoint.t = 8.0; aPoint.x = 5.0;
	myPoints->push_back(aPoint);
	aPoint.value = 1.0e-20; aPoint.t = 7.0; aPoint.x = 7.0;
	myPoints->push_back(aPoint);
	aPoint.value = -1.0; aPoint.t = 7.0; aPoint.x = 7.0;
	myPoints->push_back(aPoint);

	// Set these points in the myDataProvider
	myCvsXDataProvider->setPoints(myPoints);

	// Get the vectors back
	auto axis1Vector = myCvsXDataProvider->getAxis1Vector();
	auto axis2Vector = myCvsXDataProvider->getAxis2Vector();

	// First check the size of the vectors
	BOOST_REQUIRE_EQUAL(axis1Vector.size(), myPoints->size());
	BOOST_REQUIRE_EQUAL(axis2Vector.size(), myPoints->size());

	// Loop on all the points in myPoints
<<<<<<< HEAD
<<<<<<< HEAD
	for (unsigned int i = 0; i < myPoints->size() - 2; i++) {
=======
	for (int i = 0; i < myPoints->size()-2; i++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	for (int i = 0; i < myPoints->size()-2; i++) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		BOOST_REQUIRE_EQUAL(axis1Vector.at(i), myPoints->at(i).x);
		BOOST_REQUIRE_EQUAL(axis2Vector.at(i), myPoints->at(i).value);
	}

	// Check that the DataProvider returns 1.0e-16 for values
	// that are too small or negative
	BOOST_REQUIRE_EQUAL(axis1Vector.at(4), myPoints->at(4).x);
	BOOST_REQUIRE_EQUAL(axis2Vector.at(4), 1.0e-16);
	BOOST_REQUIRE_EQUAL(axis1Vector.at(5), myPoints->at(5).x);
	BOOST_REQUIRE_EQUAL(axis2Vector.at(5), 1.0e-16);
<<<<<<< HEAD
<<<<<<< HEAD

	return;
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

BOOST_AUTO_TEST_SUITE_END()
