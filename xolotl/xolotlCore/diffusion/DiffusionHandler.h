#ifndef DIFFUSIONHANDLER_H
#define DIFFUSIONHANDLER_H

// Includes
#include "IDiffusionHandler.h"
#include <MathUtils.h>

namespace xolotlCore {

/**
 * This class realizes the IDiffusionHandler interface responsible for all
 * the physical parts for the diffusion of mobile clusters. It needs to have
 * subclasses implementing the compute diffusion methods.
 */
class DiffusionHandler: public IDiffusionHandler {
protected:

<<<<<<< HEAD
	//! The vector containing the indices of the diffusing clusters
	std::vector<int> indexVector;
=======
	//! Collection of diffusing clusters.
	IReactant::ConstRefVector diffusingClusters;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

public:

	//! The Constructor
<<<<<<< HEAD
	DiffusionHandler() {}

	//! The Destructor
	~DiffusionHandler() {}
=======
	DiffusionHandler() {
	}

	//! The Destructor
	~DiffusionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Initialize the off-diagonal part of the Jacobian. If this step is skipped it
	 * won't be possible to set the partial derivatives for the diffusion.
	 *
	 * The value 1 is set in ofill if a cluster has a non zero diffusion coefficient.
	 *
	 * @param network The network
	 * @param ofill The pointer to the array that will contain the value 1 at the indices
	 * of the diffusing clusters
	 */
<<<<<<< HEAD
	virtual void initializeOFill(IReactionNetwork *network, int *ofill) {
		// Get all the reactants
		auto reactants = network->getAll();
		int networkSize = reactants->size();
		int dof = network->getDOF();

		// Clear the index vector
		indexVector.clear();

		// Loop on the reactants
		for (int i = 0; i < networkSize; i++) {
			// Get the i-th cluster
			auto cluster = (PSICluster *) reactants->at(i);
			// Get its diffusion coefficient
			double diffFactor = cluster->getDiffusionFactor();

			// Don't do anything if the diffusion factor is 0.0
			if (xolotlCore::equal(diffFactor, 0.0)) continue;

			// Add its index (i) to the vector of indices
			indexVector.push_back(i);

			// Get its id
			int index = cluster->getId() - 1;
=======
	virtual void initializeOFill(const IReactionNetwork& network, int *ofill)
			override {

		int dof = network.getDOF();

		// Clear the index vector
		diffusingClusters.clear();

		// Consider each cluster.
		for (IReactant const& currReactant : network.getAll()) {

			auto const& cluster = static_cast<PSICluster const&>(currReactant);

			// Get its diffusion coefficient
			double diffFactor = cluster.getDiffusionFactor();

			// Don't do anything if the diffusion factor is 0.0
			if (xolotlCore::equal(diffFactor, 0.0))
				continue;

			// Note that cluster is diffusing.
			diffusingClusters.emplace_back(cluster);

			// Get its id
			int index = cluster.getId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Set the ofill value to 1 for this cluster
			ofill[index * dof + index] = 1;
		}

		return;
	}

	/**
	 * Get the total number of diffusing clusters in the network.
	 *
	 * @return The number of diffusing clusters
	 */
<<<<<<< HEAD
	int getNumberOfDiffusing() {return indexVector.size();}
=======
	int getNumberOfDiffusing() const override {
		return diffusingClusters.size();
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};
//end class DiffusionHandler

} /* end namespace xolotlCore */
#endif
