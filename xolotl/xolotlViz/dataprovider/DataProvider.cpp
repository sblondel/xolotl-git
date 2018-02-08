// Includes
#include "DataProvider.h"

using namespace xolotlViz;

<<<<<<< HEAD
<<<<<<< HEAD
DataProvider::DataProvider(const std::string& name) : xolotlCore::Identifiable(name) {
=======
DataProvider::DataProvider(std::string name) : xolotlCore::Identifiable(name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
DataProvider::DataProvider(std::string name) : xolotlCore::Identifiable(name) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

DataProvider::~DataProvider() {
}

std::shared_ptr< std::vector<Point> > DataProvider::getDataPoints() const {
	return dataPoints;
}

void DataProvider::setPoints(std::shared_ptr< std::vector<Point> > points) {
	dataPoints = points;
	return;
}

double DataProvider::getDataMean() const {
	// The size of the data vector
	int size = dataPoints->size();

	// Use to add the value of each Point
	double valueSum = 0.0;

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

		// Add the current value to the sum
		valueSum += (*it).value;
	}

	// Result equals the sum divided by the size
	double result = (double) valueSum / size;

	return result;
}
