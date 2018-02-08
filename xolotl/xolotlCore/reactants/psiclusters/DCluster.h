#ifndef DCLUSTER_H
#define DCLUSTER_H

// Includes
#include "HCluster.h"

namespace xolotlCore {

//! This class represents a cluster composed entirely of deuterium.
<<<<<<< HEAD
class DCluster : public HCluster {

private:

public:

	//! The constructor. All DClusters must be initialized with a size.
	DCluster(int nD, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! Destructor
	~DCluster();

=======
class DCluster: public HCluster {

private:

	/**
	 * The default constructor is private because HClusters must always be
	 * initialized with a size and performance handler registry
	 */
	DCluster() :
			HCluster() {
	}

public:

	/**
	 * The constructor. All DClusters must be initialized with a size.
	 *
	 * @param nD the number of deuterium atoms in the cluster
	 * @param registry The performance handler registry
	 */
	DCluster(int nD, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Destructor
	 */
	~DCluster() {
	}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant>(new DCluster(*this));
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
};
//end class DCluster

} /* end namespace xolotlCore */
#endif
