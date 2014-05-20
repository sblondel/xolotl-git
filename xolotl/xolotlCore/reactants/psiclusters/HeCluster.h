#ifndef HECLUSTER_H
#define HECLUSTER_H

// Includes
#include "PSICluster.h"
<<<<<<< HEAD
#include <xolotlPerf.h>
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

namespace xolotlCore {

/**
 * This class represents a cluster composed entirely of helium.
 */
class HeCluster: public PSICluster {

private:

	/**
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size and performance handler registry
	 */
	HeCluster() :
<<<<<<< HEAD
		PSICluster() {}
=======
		PSICluster(1)
	{ }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
	 * The constructor. All HeClusters must be initialized with a size.
<<<<<<< HEAD
	 *
	 * @param nHe the number of helium atoms in the cluster
	 * @param registry The performance handler registry
=======
	 * @param nHe the number of helium atoms in the cluster
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 */
	HeCluster(int nHe, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Destructor
	 */
<<<<<<< HEAD
	~HeCluster() {}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant> (new HeCluster(*this));
	}
=======
	~HeCluster();

	/**
	 * This operation returns a Reactant that is created using the copy
	 * constructor of HeCluster.
	 * @return A copy of this HeCluster.
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

}; //end class HeCluster

} /* namespace xolotlCore */
#endif
