#ifndef DUMMYADVECTIONHANDLER_H
#define DUMMYADVECTIONHANDLER_H

// Includes
#include "SurfaceAdvectionHandler.h"

namespace xolotlCore {

/**
 * This class realizes the IAdvectionHandler interface responsible for all
 * the physical parts for the advection of mobile cluster. Here it is a dummy
 * class which means that it is not actually doing anything.
 */
class DummyAdvectionHandler: public SurfaceAdvectionHandler {

public:

	//! The Constructor
<<<<<<< HEAD
	DummyAdvectionHandler() {}

	//! The Destructor
	~DummyAdvectionHandler() {}
=======
	DummyAdvectionHandler() :
			SurfaceAdvectionHandler() {
	}

	//! The Destructor
	~DummyAdvectionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This function initialize the list of clusters that will move through advection. For the
	 * dummy class we don't want any cluster to advect, so this class only clears the vector
	 * and doesn't fill them.
	 *
	 * @param network The network
	 * @param ofill The pointer to the array that will contain the value 1 at the indices
	 * of the advecting clusters
	 */
<<<<<<< HEAD
	void initialize(IReactionNetwork *network, int *ofill) {
		// Clear the index and sink strength vectors
		indexVector.clear();
=======
	void initialize(const IReactionNetwork& network, int *ofill) override {
		// Clear the index and sink strength vectors
		advectingClusters.clear();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		sinkStrengthVector.clear();

		// Return now to leave them empty
		return;
	}

};
//end class DummyAdvectionHandler

} /* end namespace xolotlCore */
#endif
