#ifndef ADVECTIONHANDLER_H
#define ADVECTIONHANDLER_H

// Includes
#include "IAdvectionHandler.h"
#include <Constants.h>

namespace xolotlCore {

/**
 * This class realizes the IAdvectionHandler interface responsible for all
 * the physical parts for the advection of mobile helium clusters. It needs to have subclasses
 * that implement the initialize method.
 */
class AdvectionHandler: public IAdvectionHandler {
protected:

	//! The location of the sink
	double location;

<<<<<<< HEAD
	//! The vector containing the indices of the advecting clusters
	std::vector<int> indexVector;
=======
	//! The collection of advecting clusters.
	IReactant::ConstRefVector advectingClusters;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	//! The vector containing the value of the sink strength (called A) of the advecting clusters
	std::vector<double> sinkStrengthVector;

	//! The number of dimensions of the problem
	int dimension;

public:

	//! The Constructor
<<<<<<< HEAD
	AdvectionHandler() : location(0.0), dimension(0) {}

	//! The Destructor
	~AdvectionHandler() {}
=======
	AdvectionHandler() :
			location(0.0), dimension(0) {
	}

	//! The Destructor
	~AdvectionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Set the number of dimension.
	 *
	 * @param dim The number of dimensions of the problem
	 */
<<<<<<< HEAD
	void setDimension(int dim) {dimension = dim;}
=======
	void setDimension(int dim) override {
		dimension = dim;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Set the location of the sink.
	 *
	 * @param pos The location of the sink
	 */
<<<<<<< HEAD
	void setLocation(double pos) {location = pos;}
=======
	void setLocation(double pos) override {
		location = pos;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total number of advecting clusters in the network.
	 *
	 * @return The number of advecting clusters
	 */
<<<<<<< HEAD
	int getNumberOfAdvecting() {return indexVector.size();}
=======
	int getNumberOfAdvecting() const override {
		return advectingClusters.size();
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the vector of index of advecting clusters in the network.
	 *
	 * @return The vector of advecting clusters
	 */
<<<<<<< HEAD
	std::vector<int> getIndexVector() {return indexVector;}
=======
	const IReactant::ConstRefVector& getAdvectingClusters() override {
		return advectingClusters;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the location of the sink.
	 *
	 * @return The location
	 */
<<<<<<< HEAD
	double getLocation() {return location;}
=======
	double getLocation() const override {
		return location;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};
//end class AdvectionHandler

} /* end namespace xolotlCore */
#endif
