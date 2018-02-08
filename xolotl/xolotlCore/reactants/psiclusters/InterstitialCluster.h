#ifndef INTERSTITIALCLUSTER_H
#define INTERSTITIALCLUSTER_H

// Includes
#include "PSICluster.h"

namespace xolotlCore {

/**
 * This class represents a cluster composed entirely of interstitial defects.
 */
class InterstitialCluster: public PSICluster {

private:

	/**
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size.
	 */
	InterstitialCluster() :
<<<<<<< HEAD
		PSICluster(1) {}
=======
		PSICluster() {}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
	 * The constructor. All InterstitialClusters must be initialized with
	 * a size.
	 *
	 * @param nI The number of interstitial defect in this cluster
	 * @param registry The performance handler registry
	 */
	InterstitialCluster(int nI, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The Destructor
	 */
	~InterstitialCluster() {}

	/**
<<<<<<< HEAD
	 * This operation returns a Reactant that is created using the copy
	 * constructor of InterstitialCluster.
	 *
	 * @return A copy of this reactant
	 */
	virtual std::shared_ptr<Reactant> clone();

protected:

	/**
	 * Computes a row of the reaction connectivity matrix corresponding to
	 * this reactant.
	 *
	 * If two reactants alone can form a reaction, the element at the position
	 * of the second reactant is 1, otherwise 0.
	 */
	void createReactionConnectivity();

	/**
	 * Computes a row of the dissociation connectivity matrix
	 * corresponding to this cluster.
	 *
	 * Connections are made between this cluster and any clusters it affects
	 * in a dissociation reaction.
	 *
	 * The base-class implementation handles dissociation for regular clusters
	 * by processing the reaction.
	 *
	 */
	void createDissociationConnectivity();
=======
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant> (new InterstitialCluster(*this));
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

};
//end class InterstitialCluster

} /* end namespace xolotlCore */
#endif
