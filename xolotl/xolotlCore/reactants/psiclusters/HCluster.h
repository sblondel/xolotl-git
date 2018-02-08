#ifndef HCLUSTER_H
#define HCLUSTER_H

// Includes
#include "PSICluster.h"

namespace xolotlCore {

//! This class represents a cluster composed entirely of hydrogen.
class HCluster: public PSICluster {

<<<<<<< HEAD
private:

=======
protected:

	/**
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size and performance handler registry
	 */
	HCluster() :
			PSICluster() {
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

public:

	/**
	 * The constructor. All HClusters must be initialized with a size.
<<<<<<< HEAD
	 * @param nH the number of hydrogen atoms in the cluster
	 */
	HCluster(int nH, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! The destructor
	~HCluster();
=======
	 *
	 * @param registry The performance handler registry
	 */
	HCluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Destructor
	 */
	~HCluster() {
	}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant>(new HCluster(*this));
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

};
//end class HCluster

} /* end namespace xolotlCore */
#endif
