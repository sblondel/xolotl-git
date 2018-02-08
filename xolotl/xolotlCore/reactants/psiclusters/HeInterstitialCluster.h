#ifndef HEINTERSTITIALCLUSTER_H
#define HEINTERSTITIALCLUSTER_H

// Includes
#include "PSICluster.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include <string>
#include <map>

namespace xolotlCore {

/**
<<<<<<< HEAD
<<<<<<< HEAD
 *  A cluster composed of helium and intersititial.
=======
 *  A cluster composed of helium and vacancies
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
 *  A cluster composed of helium and vacancies
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
 */
class HeInterstitialCluster : public PSICluster {

private:

	//! The number of helium atoms in this cluster.
	int numHe;

	//! The number of interstitial defects in this cluster.
	int numI;

<<<<<<< HEAD
<<<<<<< HEAD
	/**
<<<<<<< HEAD
=======
	 * A pointer to He_1 that is used for the dissociation flux calculation
	 */
	std::shared_ptr<PSICluster> heCluster;
=======
	//! The helium cluster of size 1
	PSICluster * heCluster;
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	//! The helium cluster of size 1
	PSICluster * heCluster;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	//! The vacancy cluster of size 1
	PSICluster * vCluster;

	//! The interstitial cluster of size 1
	PSICluster * iCluster;

	//! The HeI cluster with one less helium
	PSICluster * heIClusterLessHe;

	//! The HeI cluster with one less vacancy
	PSICluster * heIClusterLessI;

	//! The sum of the dissociation constants between this cluster and the
	//! clusters of size 1.
	double f4 = 0.0;

	/**
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size.
	 */
	HeInterstitialCluster() :
<<<<<<< HEAD
<<<<<<< HEAD
		PSICluster()
	{ numHe = 0; numI = 0; }
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		PSICluster(1)
	{ numHe = 1; numI = 1; }

protected:

	/**
	 * This operation computes the partial derivatives due to dissociation
	 * reactions. The partial derivatives due to dissociation for compound
	 * clusters are significantly different than those single-species clusters.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 * @param temperature The temperature at which the reactions are occurring.
	 */
	virtual void getDissociationPartialDerivatives(std::vector<double> & partials, double temperature) const;

<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
	 * The constructor. All HeInterstitialClusters must be initialized with a map
	 * that describes the species of which the cluster is composed. The map
	 * should contain as its keys the names of the species and the sizes of the
	 * species as its values. The names of the species must be one of
	 * {He,I}.
<<<<<<< HEAD
<<<<<<< HEAD
	 *
	 * @param numHe The number of helium atoms in this cluster
	 * @param numI The number of interstitial defect in this cluster
	 * @param registry The performance handler registry
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 */
	HeInterstitialCluster(int numHe, int numI,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Copy constructor
<<<<<<< HEAD
<<<<<<< HEAD
	 *
	 * @param other the reactant to be copied
	 */
	HeInterstitialCluster(HeInterstitialCluster &other);

	//! Destructor
	~HeInterstitialCluster() {}

	/**
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant> (new HeInterstitialCluster(*this));
	}

	/**
	 * This operation returns true to signify that this cluster is a mixture of
	 * He and I.
	 *
	 * @return True if mixed
	 */
	virtual bool isMixed() const {return true;}
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * @param other the reactant to be copied
	 */
	HeInterstitialCluster(const HeInterstitialCluster &other);

	//! Destructor
	~HeInterstitialCluster();

	/**
	 * This operation returns a Reactant that is created using the copy
	 * constructor of HeInterstitialCluster.
	 * @return A copy of this reactant.
	 */
	virtual std::shared_ptr<Reactant> clone();

	/**
	 * This operation returns the total generation rate due to emission for
	 * this cluster.
	 */
	double getGenByEm();

	/**
	 * This operation returns the total annihilation rate due to emission for
	 * this cluster.
	 */
	double getAnnByEm();

    /**
	 * This operation returns the total change in this cluster due to
	 * dissociation.
	 * @return The flux due to dissociation.
	 */
	virtual double getDissociationFlux(double temperature) const;

	/**
	 * This operation returns true to signify that this cluster is a mixture of
	 * He and I.
	 */
	virtual bool isMixed() const { return true; };

	/**
	 * This operation overrides Reactant's setTemperature operation to
	 * correctly recompute the diffusion coefficient and other
	 * temperature-dependent quantities when the temperature is set.
	 * @param temp
	 */
	virtual void setTemperature(double temp);

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
	 * Computes a row of the dissociation connectivity matrix corresponding to
	 * this reactant.
	 *
	 * If two reactants together can be produced by a single reaction,
	 * the element at the position of the second reactant is 1, otherwise 0.
	 */
	void createDissociationConnectivity();
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
};
//end class HeInterstitialCluster

} /* end namespace xolotlCore */
#endif
