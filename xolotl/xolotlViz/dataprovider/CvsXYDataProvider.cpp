// Includes
#include "CvsXYDataProvider.h"
#include <algorithm>
<<<<<<< HEAD
<<<<<<< HEAD
#include <iostream>

using namespace xolotlViz;

CvsXYDataProvider::CvsXYDataProvider(const std::string& name) : DataProvider(name) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

using namespace xolotlViz;

CvsXYDataProvider::CvsXYDataProvider(std::string name) : DataProvider(name) {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

CvsXYDataProvider::~CvsXYDataProvider() {
}

std::vector<double> CvsXYDataProvider::getAxis1Vector() const {
	std::vector<double> xVector;

<<<<<<< HEAD
<<<<<<< HEAD
	// Needed to compute the correct last point for the mesh
	double max = 0.0, almostMax = 0.0;

	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
			it != dataPoints->end(); ++it) {
		// Find the max and almostMax
		if ((*it).x > max) {
			almostMax = max;
			max = (*it).x;
		}
=======
	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
			it != dataPoints->end(); it++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
			it != dataPoints->end(); it++) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

		// Fill the xVector
		addValue(xVector, (*it).x);
	}
<<<<<<< HEAD
<<<<<<< HEAD
	
	// Add the last point for the mesh (data are in cells, we need one more mesh points than cell points)
	xVector.push_back(2.0 * max - almostMax);
	
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	return xVector;
}

std::vector<double> CvsXYDataProvider::getAxis2Vector() const {
	std::vector<double> yVector;

<<<<<<< HEAD
<<<<<<< HEAD
	// Needed to compute the correct last point for the mesh
	double max = 0.0, almostMax = 0.0;

	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
			it != dataPoints->end(); ++it) {
		// Find the max and almostMax
		if ((*it).y > max) {
			almostMax = max;
			max = (*it).y;
		}
=======
	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
			it != dataPoints->end(); it++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
			it != dataPoints->end(); it++) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

		// Fill the yVector
		addValue(yVector, (*it).y);
	}

<<<<<<< HEAD
<<<<<<< HEAD
	// Add the last point for the mesh (data are in cells, we need one more mesh points than cell points)
	yVector.push_back(2.0 * max - almostMax);

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	return yVector;
}

std::vector<double> CvsXYDataProvider::getAxis3Vector() const {
	std::vector<double> concentrationVector;

	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
<<<<<<< HEAD
<<<<<<< HEAD
			it != dataPoints->end(); ++it) {
=======
			it != dataPoints->end(); it++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
			it != dataPoints->end(); it++) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

		// Fill the concentrationVector
		concentrationVector.push_back(std::max((*it).value, 1.0e-16));
	}

	return concentrationVector;
}

void CvsXYDataProvider::addValue(std::vector<double>& vector, double value) const {
<<<<<<< HEAD
<<<<<<< HEAD
	// Check if the value is already in the vector
	auto it = std::find (vector.begin(), vector.end(), value);
	// If it is not, add the value to the vector
=======
	auto it = std::find (vector.begin(), vector.end(), value);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	auto it = std::find (vector.begin(), vector.end(), value);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	if (it == vector.end()) vector.push_back(value);

	return;
}
