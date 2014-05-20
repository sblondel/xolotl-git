#ifndef INTERSTITIALCLUSTER_H
#define INTERSTITIALCLUSTER_H

// Includes
#include "PSICluster.h"
<<<<<<< HEAD
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

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
		PSICluster() {}
=======
		PSICluster(1) {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
	 * The constructor. All InterstitialClusters must be initialized with
	 * a size.
<<<<<<< HEAD
	 *
	 * @param nI The number of interstitial defect in this cluster
	 * @param registry The performance handler registry
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 */
	InterstitialCluster(int nI, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The Destructor
	 */
<<<<<<< HEAD
	~InterstitialCluster() {}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant> (new InterstitialCluster(*this));
	}
=======
	~InterstitialCluster();

	/**
	 * This operation returns a Reactant that is created using the copy
	 * constructor of InterstitialCluster.
	 * @return A copy of this reactant.
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
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

};
//end class InterstitialCluster

} /* end namespace xolotlCore */
#endif
