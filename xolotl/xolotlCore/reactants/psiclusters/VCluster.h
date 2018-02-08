#ifndef VCLUSTER_H
#define VCLUSTER_H

// Includes
#include "PSICluster.h"
#include <xolotlPerf.h>

namespace xolotlCore {

/**
 * This class represents a cluster composed entirely of atomic vacancies.
 */
class VCluster: public PSICluster {

private:

	/**
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size.
	 */
	VCluster() :
<<<<<<< HEAD
		PSICluster(1)
=======
		PSICluster()
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	{ }

public:

	/**
	 * The constructor. All VClusters must be initialized with a size.
	 *
	 * @param nV the number of atomic vacancies in the cluster
	 * @param registry The performance handler registry
	 */
	VCluster(int nV, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! Destructor
	~VCluster() {}

	/**
<<<<<<< HEAD
	 * This operation returns a Reactant that is created using the copy
	 * constructor of VCluster.
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
		return std::shared_ptr<IReactant> (new VCluster(*this));
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

};
//end class VCluster

} /* end namespace xolotlCore */

#endif
