/*
 * PSIClusterNetworkLoader.h
 *
 *  Created on: Mar 30, 2013
 *      Author: jaybilly
 */

#ifndef PSICLUSTERNETWORKLOADER_H_
#define PSICLUSTERNETWORKLOADER_H_

//Includes
#include <PSICluster.h>
#include <NetworkLoader.h>
<<<<<<< HEAD
#include <PSIClusterReactionNetwork.h>
=======
#include "PSIClusterReactionNetwork.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlCore {

/**
 * This class will load a reaction network composed of PSIClusters from an
 * inputstream.
 *
 * The data in the stream should contain the information for a single cluster on
 * each line with the following quantities specified and separated by a single
 * space each:
 * > The number of He in the cluster
 * > The number of V in the cluster
 * > The number of I in the cluster
 * > The formation energy
 *
 * Lines of comments starting with a "#" will be ignored as will lines that do
 * not clearly provide the information above.
 *
 * The network will be returned as a ReactionNetwork of PSIClusters ordered with
 * single-species He, V and I clusters first and all mixed clusters coming
 * last. Each species is ordered from the smallest cluster size, (1), to the
 * maximum size for that cluster. Instances of the appropriate cluster type are
 * instantiated during the loading process, but returned as PSIClusters.
<<<<<<< HEAD
 *
 * The ReactionNetwork's map of properties will contains the following
 * information about the network with the following keys:
 * > maxHeClusterSize - The number of He atoms in the largest single-species
 *  He cluster.
 * > maxVClusterSize - The number of atomic vacancies in the largest
 * single-species V cluster.
 * > maxIClusterSize - The number of interstitials in the largest
 * single-species I cluster.
 * > maxMixedClusterSize - The number of species of all types in the largest
 * mixed species in the network. It is equal to the sum of the max single
 * species helium and vacancy cluster sizes by default.
 * > numHeClusters - The number of single-species He clusters of all sizes in
 * the network.
 * > numVClusters - The number of single-species V clusters of all sizes in the
 * network.
 * > numIClusters - The number of single-species I clusters of all sizes in the
 * network.
 * > numMixedClusters - The number of mixed-species clusters of all sizes in the
 * network.
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
 */
class PSIClusterNetworkLoader: public NetworkLoader {

protected:

	/**
	 * The vacancy size at which the grouping scheme starts
	 */
	int vMin;

	/**
<<<<<<< HEAD
=======
	 * The maximum size for helium clusters
	 */
	int maxHe;

	/**
	 * The maximum size for interstitial clusters
	 */
	int maxI;

	/**
	 * The maximum size for vacancy clusters
	 */
	int maxV;

	/**
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 * The width of the group in the helium direction.
	 */
	int heSectionWidth;

	/**
	 * The width of the group in the vacancy direction.
	 */
	int vSectionWidth;

	/**
<<<<<<< HEAD
	 * Private nullary constructor.
	 */
	PSIClusterNetworkLoader() :
			vMin(1000000), heSectionWidth(1), vSectionWidth(1) {
=======
	 * The list of clusters that will be grouped.
	 */
	std::set<std::pair<int, int> > heVList;

	/**
	 * Private nullary constructor.
	 */
	PSIClusterNetworkLoader() :
			NetworkLoader(), vMin(1000000), maxHe(0), maxI(0), maxV(0), heSectionWidth(
					1), vSectionWidth(1) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * This operation creates a singles-species cluster of helium, vacancies or
	 * interstitials. It adds the cluster to the appropriate internal list of
	 * clusters for that type.
	 *
	 * @param numHe The number of helium atoms
	 * @param numV The number of atomic vacancies
	 * @param numI The number of interstitial defects
	 * @return The new cluster
	 */
<<<<<<< HEAD
	std::shared_ptr<PSICluster> createPSICluster(int numHe, int numV, int numI);
=======
	std::unique_ptr<PSICluster> createPSICluster(int numHe, int numV, int numI,
			IReactionNetwork& network) const;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will add the given cluster to the network and reactants vector
	 * as a standard cluster or a dummy one if we do not want the reactions to happen.
	 *
	 * @param network The network
	 * @param reactants The vector of reactants kept by the loader
	 * @param cluster The cluster to add to them
	 */
	virtual void pushPSICluster(
<<<<<<< HEAD
			std::shared_ptr<PSIClusterReactionNetwork> & network,
			std::vector<std::shared_ptr<Reactant> > & reactants,
			std::shared_ptr<PSICluster> & cluster);
=======
			std::unique_ptr<PSIClusterReactionNetwork> & network,
			std::vector<std::reference_wrapper<Reactant> > & reactants,
			std::unique_ptr<PSICluster> & cluster);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the formation energy associated to the
	 * cluster of the given size.
	 *
	 * @param numHe The number of helium atoms
	 * @param numV The number of atomic vacancies
	 * @return The corresponding formation energy
	 */
	double getHeVFormationEnergy(int numHe, int numV);

public:

	/**
	 * The default constructor. The setInputstream() operation must be called
	 * if this constructor is used.
	 *
	 * @param registry The performance handler registry
	 */
	PSIClusterNetworkLoader(
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * An alternative constructor provided for convenience.
	 *
	 * @param stream The inputstream from which the cluster data should be
	 * loaded
	 * @param registry The performance handler registry
	 */
	PSIClusterNetworkLoader(const std::shared_ptr<std::istream> stream,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Destructor
	 */
	virtual ~PSIClusterNetworkLoader() {
	}

	/**
	 * This operation will load the reaction network from the inputstream in
	 * the format specified previously. The network will be empty if it can not
	 * be loaded.
	 *
	 * @return network The reaction network
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<IReactionNetwork> load();
=======
	virtual std::unique_ptr<IReactionNetwork> load(const IOptions& options)
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will generate the reaction network from options.
	 * The network will be empty if it can not be loaded.
	 *
	 * @param options The command line options
	 * @return network The reaction network
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<IReactionNetwork> generate(IOptions &options);
=======
	virtual std::unique_ptr<IReactionNetwork> generate(const IOptions &options)
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will apply a sectional grouping method to the network.
	 *
	 * @param The network to be modified.
	 */
<<<<<<< HEAD
	void applySectionalGrouping(std::shared_ptr<IReactionNetwork> network);
=======
	void applySectionalGrouping(PSIClusterReactionNetwork& network);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will set the helium size at which the grouping scheme starts.
	 *
	 * @param min The value for the size
	 */
	void setVMin(int min) {
		vMin = min;
	}

	/**
	 * This operation will set the helium width for the grouping scheme.
	 *
	 * @param w The value of the width
	 */
	void setHeWidth(int w) {
		heSectionWidth = w;
	}

	/**
	 * This operation will set the vacancy width for the grouping scheme.
	 *
	 * @param w The value of the width
	 */
	void setVWidth(int w) {
		vSectionWidth = w;
	}
};

} /* namespace xolotlCore */

#endif /* PSICLUSTERNETWORKLOADER_H_ */
