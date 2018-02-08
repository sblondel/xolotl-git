#ifndef W100ADVECTIONHANDLER_H
#define W100ADVECTIONHANDLER_H

// Includes
#include "SurfaceAdvectionHandler.h"
#include <MathUtils.h>

namespace xolotlCore {

/**
 * This class realizes the IAdvectionHandler interface responsible for all
 * the physical parts for the advection of mobile helium cluster.
 */
class W100AdvectionHandler: public SurfaceAdvectionHandler {

public:

	//! The Constructor
<<<<<<< HEAD
	W100AdvectionHandler() {}

	//! The Destructor
	~W100AdvectionHandler() {}
=======
	W100AdvectionHandler() :
			SurfaceAdvectionHandler() {
	}

	//! The Destructor
	~W100AdvectionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This function initialize the list of clusters that will move through advection for a
	 * (100) tungsten material.
	 *
	 * @param network The network
	 * @param ofill The pointer to the array that will contain the value 1 at the indices
	 * of the advecting clusters
	 */
<<<<<<< HEAD
	void initialize(IReactionNetwork *network, int *ofill) {
		// Get all the reactants and their number
		auto reactants = network->getAll();
		int networkSize = reactants->size();
		int dof = network->getDOF();

		// Clear the index and sink strength vectors
		indexVector.clear();
		sinkStrengthVector.clear();

		// Loop on all the reactants
		for (int i = 0; i < networkSize; i++) {
			// Get the i-th cluster
			auto cluster = (PSICluster *) reactants->at(i);
			// Get its diffusion coefficient
			double diffFactor = cluster->getDiffusionFactor();

			// Don't do anything if the diffusion factor is 0.0
			if (xolotlCore::equal(diffFactor, 0.0)) continue;

			// Keep only the helium clusters
			if (cluster->getType() != heType) continue;

			// Get its size
			int heSize = cluster->getSize();
=======
	// TODO this is nearly identical for the W100, W110, W111, and W211
	// cases.  Factor the identical parts to a base class, and only
	// have these classes differ in the sinkStrength identification.
	void initialize(const IReactionNetwork& network, int *ofill) override {
		// Get all the reactants and their number
		int dof = network.getDOF();

		// Clear the index and sink strength vectors
		advectingClusters.clear();
		sinkStrengthVector.clear();

		// Consider each reactant.
		for (IReactant const& currReactant : network.getAll()) {

			auto const& cluster = static_cast<PSICluster const&>(currReactant);

			// Get its diffusion coefficient
			double diffFactor = cluster.getDiffusionFactor();

			// Don't do anything if the diffusion factor is 0.0
			if (xolotlCore::equal(diffFactor, 0.0))
				continue;

			// Keep only the helium clusters
			if (cluster.getType() != ReactantType::He)
				continue;

			// Get its size
			int heSize = cluster.getSize();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Switch on the size to get the sink strength (in eV.nm3)
			double sinkStrength = 0.0;
			switch (heSize) {
<<<<<<< HEAD
				case 1:
					sinkStrength = 2.28e-3;
					break;
				case 2:
					sinkStrength = 5.06e-3;
					break;
				case 3:
					sinkStrength = 7.26e-3;
					break;
				case 4:
					sinkStrength = 15.87e-3;
					break;
				case 5:
					sinkStrength = 16.95e-3;
					break;
				case 6:
					sinkStrength = 27.16e-3;
					break;
				case 7:
					sinkStrength = 35.56e-3;
					break;
			}

			// If the sink strength is still 0.0, this cluster is not advecting
			if (xolotlCore::equal(sinkStrength, 0.0)) continue;

			// Add its index (i) to the vector of indices
			indexVector.push_back(i);
=======
			case 1:
				sinkStrength = 2.28e-3;
				break;
			case 2:
				sinkStrength = 5.06e-3;
				break;
			case 3:
				sinkStrength = 7.26e-3;
				break;
			case 4:
				sinkStrength = 15.87e-3;
				break;
			case 5:
				sinkStrength = 16.95e-3;
				break;
			case 6:
				sinkStrength = 27.16e-3;
				break;
			case 7:
				sinkStrength = 35.56e-3;
				break;
			}

			// If the sink strength is still 0.0, this cluster is not advecting
			if (xolotlCore::equal(sinkStrength, 0.0))
				continue;

			// Add it to our collection of advecting clusters.
			advectingClusters.emplace_back(currReactant);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Add the sink strength to the vector
			sinkStrengthVector.push_back(sinkStrength);

			// Set the off-diagonal part for the Jacobian to 1
			// Get its id
<<<<<<< HEAD
			int index = cluster->getId() - 1;
=======
			int index = cluster.getId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Set the ofill value to 1 for this cluster
			ofill[index * dof + index] = 1;
		}

		return;
	}

};
//end class W100AdvectionHandler

} /* end namespace xolotlCore */
#endif
