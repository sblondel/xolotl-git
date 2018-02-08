#ifndef TCLUSTER_H
#define TCLUSTER_H

// Includes
#include "HCluster.h"

namespace xolotlCore {

//! This class represents a cluster composed entirely of tritium.
<<<<<<< HEAD
class TCluster : public HCluster {

private:

public:

	//! The constructor. All TClusters must be initialized with a size.
	TCluster(int nT, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! Destructor
	~TCluster();
=======
class TCluster: public HCluster {

private:

	/**
	 * The default constructor is private because HClusters must always be
	 * initialized with a size and performance handler registry
	 */
	TCluster() :
			HCluster() {
	}

public:

	/**
	 * The constructor. All TClusters must be initialized with a size.
	 *
	 * @param nT the number of tritium atoms in the cluster
	 * @param registry The performance handler registry
	 */
	TCluster(int nT, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Destructor
	 */
	~TCluster() {
	}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant>(new TCluster(*this));
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

};
//end class TCluster

} /* end namespace xolotlCore */
#endif
