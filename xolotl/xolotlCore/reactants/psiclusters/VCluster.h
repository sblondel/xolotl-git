#ifndef VCLUSTER_H
#define VCLUSTER_H

// Includes
#include "PSICluster.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include <xolotlPerf.h>
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

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
<<<<<<< HEAD
		PSICluster()
=======
		PSICluster(1)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
		PSICluster(1)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	{ }

public:

	/**
	 * The constructor. All VClusters must be initialized with a size.
<<<<<<< HEAD
<<<<<<< HEAD
	 *
	 * @param nV the number of atomic vacancies in the cluster
	 * @param registry The performance handler registry
=======
	 * @param nV the number of atomic vacancies in the cluster
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	 * @param nV the number of atomic vacancies in the cluster
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 */
	VCluster(int nV, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! Destructor
<<<<<<< HEAD
<<<<<<< HEAD
	~VCluster() {}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant> (new VCluster(*this));
	}
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	~VCluster();

	/**
	 * This operation returns a Reactant that is created using the copy
	 * constructor of VCluster.
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
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

};
//end class VCluster

} /* end namespace xolotlCore */

#endif
