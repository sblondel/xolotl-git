// Includes
#include "CvsXDataProvider.h"

using namespace xolotlViz;

<<<<<<< HEAD
CvsXDataProvider::CvsXDataProvider(const std::string& name) : DataProvider(name) {
=======
CvsXDataProvider::CvsXDataProvider(std::string name) : DataProvider(name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

CvsXDataProvider::~CvsXDataProvider() {
}

std::vector<double> CvsXDataProvider::getAxis1Vector() const {
	std::vector<double> xVector;

	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
<<<<<<< HEAD
			it != dataPoints->end(); ++it) {
=======
			it != dataPoints->end(); it++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

		// Fill the xVector
		xVector.push_back((*it).x);
	}

	return xVector;
}

std::vector<double> CvsXDataProvider::getAxis2Vector() const {
	std::vector<double> concentrationVector;

	// Loop on all the points in the data vector
	for (auto it = dataPoints->begin();
<<<<<<< HEAD
			it != dataPoints->end(); ++it) {
=======
			it != dataPoints->end(); it++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

		// Fill the concentrationVector
		concentrationVector.push_back(std::max((*it).value, 1.0e-16));
	}

	return concentrationVector;
}
