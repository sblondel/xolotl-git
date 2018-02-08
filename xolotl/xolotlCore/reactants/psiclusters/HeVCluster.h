#ifndef HEVCLUSTER_H
#define HEVCLUSTER_H

// Includes
#include "PSICluster.h"
#include <string>
#include <map>

namespace xolotlCore {

/**
 *  A cluster composed of helium and vacancies
 */
class HeVCluster: public PSICluster {

private:

<<<<<<< HEAD
=======
	//! The number of tritium atoms in this cluster.
	int numT;

	//! The number of deuterium atoms in this cluster.
	int numD;

>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	//! The number of helium atoms in this cluster.
	int numHe;

	//! The number of atomic vacancies in this cluster.
	int numV;

	/**
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size.
	 */
	HeVCluster() :
		PSICluster()
<<<<<<< HEAD
	{ numHe = 0; numV = 0; }
=======
	{ numT = 0; numD = 0; numHe = 0; numV = 0; }
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

public:

	/**
	 * The constructor. All HeVClusters must be initialized with a map
	 * that describes the species of which the cluster is composed. The map
	 * should contain as its keys the names of the species and the sizes of the
	 * species as its values. The names of the species must be one of
	 * {He,V}.
	 *
<<<<<<< HEAD
=======
	 * @param numT The number of tritium atoms in this cluster
	 * @param numD The number of deuterium atoms in this cluster
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	 * @param numHe The number of helium atoms in this cluster
	 * @param numV The number of vacancies in this cluster
	 * @param registry The performance handler registry
	 */
<<<<<<< HEAD
	HeVCluster(int numHe, int numV,
=======
	HeVCluster(int numT, int numD, int numHe, int numV,
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Copy constructor.
	 *
	 * @param other the reactant to be copied
	 */
	HeVCluster(HeVCluster &other);

	//! Destructor
	~HeVCluster() {}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant> (new HeVCluster(*this));
	}

	/**
	 * This operation returns true to signify that this cluster is a mixture of
	 * He and V.
	 *
	 * @return True if mixed
	 */
	virtual bool isMixed() const {return true;}

};
//end class HeVCluster

} /* end namespace xolotlCore */
#endif
