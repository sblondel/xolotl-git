#ifndef NECLUSTERNETWORKLOADER_H_
#define NECLUSTERNETWORKLOADER_H_

//Includes
#include <NECluster.h>
<<<<<<< HEAD
#include <NetworkLoader.h>
#include <NEClusterReactionNetwork.h>
=======
#include <NEClusterReactionNetwork.h>
#include <NetworkLoader.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlCore {

/**
 * This class will load a reaction network composed of NEClusters from an
 * HDF5 file.
 *
 * The data in the stream should contain the information for a single cluster on
 * each line with the following quantities specified and separated by a single
 * space each:
 * > The number of Xe in the cluster
 * > The number of V in the cluster
 * > The number of I in the cluster
 * > The formation energy
 *
 * Lines of comments starting with a "#" will be ignored as will lines that do
 * not clearly provide the information above.
 *
 * The network will be returned as a ReactionNetwork of NEClusters ordered with
 * single-species Xe, V and I clusters first and all mixed clusters coming
 * last. Each species is ordered from the smallest cluster size, (1), to the
 * maximum size for that cluster. Instances of the appropriate cluster type are
 * instantiated during the loading process, but returned as NEClusters.
<<<<<<< HEAD
 *
 * The ReactionNetwork's map of properties will contains the following
 * information about the network with the following keys:
 * > maxXeClusterSize - The number of Xe atoms in the largest single-species
 *  Xe cluster.
 * > maxVClusterSize - The number of atomic vacancies in the largest
 * single-species V cluster.
 * > maxIClusterSize - The number of interstitials in the largest
 * single-species I cluster.
 * > maxMixedClusterSize - The number of species of all types in the largest
 * mixed species in the network. It is equal to the sum of the max single
 * species helium and vacancy cluster sizes by default.
 * > numXeClusters - The number of single-species Xe clusters of all sizes in
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
class NEClusterNetworkLoader: public NetworkLoader {

protected:

	/**
	 * The xenon size at which the grouping scheme starts
	 */
	int xeMin;

	/**
	 * The width of the group in the xenon direction.
	 */
	int sectionWidth;

	/**
	 * Private nullary constructor.
	 */
	NEClusterNetworkLoader() :
<<<<<<< HEAD
			xeMin(1000000), sectionWidth(1) {
=======
			xeMin(-1), sectionWidth(-1) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * This operation creates a singles-species cluster of helium, vacancies or
	 * interstitials. It adds the cluster to the appropriate internal list of
	 * clusters for that type.
	 *
	 * @param numXe The number of helium atoms
	 * @param numV The number of atomic vacancies
	 * @param numI The number of interstitial defects
	 * @return The new cluster
	 */
<<<<<<< HEAD
	std::shared_ptr<NECluster> createNECluster(int numXe, int numV, int numI);
=======
	std::unique_ptr<NECluster> createNECluster(int numXe, int numV, int numI,
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
	virtual void pushNECluster(
<<<<<<< HEAD
			std::shared_ptr<NEClusterReactionNetwork> & network,
			std::vector<std::shared_ptr<Reactant> > & reactants,
			std::shared_ptr<NECluster> & cluster);
=======
			std::unique_ptr<NEClusterReactionNetwork> & network,
			std::vector<std::reference_wrapper<Reactant> > & reactants,
			std::unique_ptr<NECluster> & cluster);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

public:

	/**
	 * The default constructor. The setInputstream() operation must be called
	 * if this constructor is used.
	 *
	 * @param registry The performance handler registry
	 */
	NEClusterNetworkLoader(
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * An alternative constructor provided for convenience.
	 *
	 * @param stream The inputstream from which the cluster data should be
	 * loaded
	 * @param registry The performance handler registry
	 */
	NEClusterNetworkLoader(const std::shared_ptr<std::istream> stream,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Destructor
	 */
	virtual ~NEClusterNetworkLoader() {
	}

	/**
	 * This operation will load the reaction network from the inputstream in
	 * the format specified previously. The network will be empty if it can not
	 * be loaded.
	 *
<<<<<<< HEAD
	 * @return network The reaction network
	 */
	virtual std::shared_ptr<IReactionNetwork> load();
=======
	 * @param options The command line options.
	 * @return network The reaction network
	 */
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
	 * This operation will apply a grouping method to the network.
	 *
	 * @param The network to be modified.
	 */
<<<<<<< HEAD
	void applyGrouping(std::shared_ptr<IReactionNetwork> network);
=======
	void applyGrouping(IReactionNetwork& network) const;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will set the xenon size at which the grouping scheme starts.
	 *
	 * @param min The value for the size
	 */
	void setXeMin(int min) {
		xeMin = min;
	}

	/**
	 * This operation will set the xenon width for the grouping scheme.
	 *
	 * @param w The value of the width
	 */
	void setWidth(int w) {
		sectionWidth = w;
	}
};

} /* namespace xolotlCore */

#endif /* NECLUSTERNETWORKLOADER_H_ */
