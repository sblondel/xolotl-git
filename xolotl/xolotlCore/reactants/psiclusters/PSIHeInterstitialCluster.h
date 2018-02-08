#ifndef PSIHEINTERSTITIALCLUSTER_H
#define PSIHEINTERSTITIALCLUSTER_H

// Includes
#include <sstream>
#include "PSICluster.h"
#include <string>
#include <map>

namespace xolotlCore {

/**
 *  A cluster composed of helium and intersititial.
 */
class PSIHeInterstitialCluster: public PSICluster {

private:

	//! The number of helium atoms in this cluster.
	int numHe;

	//! The number of interstitial defects in this cluster.
	int numI;

	static std::string buildName(IReactant::SizeType nHe,
			IReactant::SizeType nI) {
		std::stringstream nameStream;
		nameStream << "He_" << nHe << "I_" << nI;
		return nameStream.str();
	}

public:

	/**
	 * Default constructor, deleted because we require info to construct.
	 */
	PSIHeInterstitialCluster() = delete;

	/**
	 * The constructor. All PSIHeInterstitialClusters must be initialized with a map
	 * that describes the species of which the cluster is composed. The map
	 * should contain as its keys the names of the species and the sizes of the
	 * species as its values. The names of the species must be one of
	 * {He,I}.
	 *
	 * @param numHelium The number of helium atoms in this cluster
	 * @param numInterstitial The number of interstitial defect in this cluster
	 * @param _network The network the cluster will belong to.
	 * @param registry The performance handler registry
	 */
	PSIHeInterstitialCluster(int numHelium, int numInterstitial,
			IReactionNetwork& _network,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
			PSICluster(_network, registry,
					buildName(numHelium, numInterstitial)), numHe(numHelium), numI(
					numInterstitial) {
		// Set the cluster size as the sum of
		// the number of Helium and Interstitials
		size = numHe + numI;

		// Update the composition map
		composition[toCompIdx(Species::He)] = numHe;
		composition[toCompIdx(Species::I)] = numI;

		// Set the typename appropriately
		type = ReactantType::HeI;

		// Compute the reaction radius
		reactionRadius = (sqrt(3.0) / 4.0) * xolotlCore::tungstenLatticeConstant
				+ pow(
						(3.0 * pow(xolotlCore::tungstenLatticeConstant, 3.0)
								* numI) / (8.0 * xolotlCore::pi), (1.0 / 3.0))
				- pow(
						(3.0 * pow(xolotlCore::tungstenLatticeConstant, 3.0))
								/ (8.0 * xolotlCore::pi), (1.0 / 3.0));

		// Bounds on He and V
		heBounds = IntegerRange<IReactant::SizeType>(
				static_cast<IReactant::SizeType>(numHe),
				static_cast<IReactant::SizeType>(numHe + 1));
		vBounds = IntegerRange<IReactant::SizeType>(
				static_cast<IReactant::SizeType>(0),
				static_cast<IReactant::SizeType>(1));

		return;
	}

	/**
	 * Copy constructor, deleted to prevent use.
	 */
	PSIHeInterstitialCluster(PSIHeInterstitialCluster &other) = delete;

	//! Destructor
	~PSIHeInterstitialCluster() {
	}

	/**
	 * This operation returns true to signify that this cluster is a mixture of
	 * He and I.
	 *
	 * @return True if mixed
	 */
	virtual bool isMixed() const {
		return true;
	}
}
;
//end class PSIHeInterstitialCluster

} /* end namespace xolotlCore */
#endif
