#ifndef SIMPLEREACTIONNETWORK_H_
#define SIMPLEREACTIONNETWORK_H_

#include <PSIClusterReactionNetwork.h>
#include <NEClusterReactionNetwork.h>
<<<<<<< HEAD
=======
#include <FeClusterReactionNetwork.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <xolotlPerf.h>
#include <DummyHandlerRegistry.h>

namespace testUtils {

/**
 * This class creates a simple reaction network used for testing. It contains
 * 10 each of He, V and I clusters and twenty HeV clusters. The HeV clusters are
 * stored in ascending order of He and then V, (1,1;2,1;2,2;3,2;3,3;etc.).
 *
 * It does not register itself as the ReactionNetwork for its clusters because
 * of limitations with shared_ptrs and "this." So, the
 * TestUtils::getSimplePSIReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimplePSIReactionNetwork: public xolotlCore::PSIClusterReactionNetwork {

public:
	/**
	 * Constructor
	 *
	 * @param maxClusterSize the maximal size of the clusters that will be in
	 * the network. Set to 10 by default.
	 * @param registry The dummy handler registry by default
	 */
	SimplePSIReactionNetwork(const int maxClusterSize = 10,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
					std::make_shared<xolotlPerf::DummyHandlerRegistry>());

	//! Destructor
	virtual ~SimplePSIReactionNetwork() {
	}

};

/**
 * This class creates a simple reaction network used for testing. It contains
 * 10 Xe.
 *
 * It does not register itself as the ReactionNetwork for its clusters because
 * of limitations with shared_ptrs and "this." So, the
 * TestUtils::getSimpleNEReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimpleNEReactionNetwork: public xolotlCore::NEClusterReactionNetwork {

public:
	/**
	 * Constructor
	 *
	 * @param maxClusterSize the maximal size of the clusters that will be in
	 * the network. Set to 10 by default.
	 * @param registry The dummy handler registry by default
	 */
	SimpleNEReactionNetwork(const int maxClusterSize = 10,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
					std::make_shared<xolotlPerf::DummyHandlerRegistry>());

	//! Destructor
	virtual ~SimpleNEReactionNetwork() {
	}

};

/**
<<<<<<< HEAD
=======
 * This class creates a simple reaction network used for testing. It contains
 * eight He, nine V, one I clusters and twenty five HeV clusters. The HeV clusters are
 * stored in ascending order of He and then V, (1,1;2,1;2,2;3,2;3,3;etc.).
 *
 * It does not register itself as the ReactionNetwork for its clusters because
 * of limitations with shared_ptrs and "this." So, the
 * TestUtils::getSimpleFeReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimpleFeReactionNetwork: public xolotlCore::FeClusterReactionNetwork {

public:
	/**
	 * Constructor
	 *
	 * @param maxClusterSize the maximal size of the clusters that will be in
	 * the network. Set to 5 by default.
	 * @param registry The dummy handler registry by default
	 */
	SimpleFeReactionNetwork(const int maxClusterSize = 5,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
					std::make_shared<xolotlPerf::DummyHandlerRegistry>());

	//! Destructor
	virtual ~SimpleFeReactionNetwork() {
	}

};

/**
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
 * This operation creates a SimplePSIReactionNetwork and makes sure that it is
 * properly registered with the clusters it contains. This operation should
 * always be called instead of constructing a SimpleReactionNetwork manually.
 *
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 10 by default.
 * @param registry The dummy handler registry by default
 * @return The reaction network.
 */
std::shared_ptr<xolotlCore::PSIClusterReactionNetwork> getSimplePSIReactionNetwork(
		const int maxClusterSize = 10,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
				std::make_shared<xolotlPerf::DummyHandlerRegistry>());

/**
 * This operation creates a SimpleNEReactionNetwork and makes sure that it is
 * properly registered with the clusters it contains. This operation should
 * always be called instead of constructing a SimpleReactionNetwork manually.
 *
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 10 by default.
 * @param registry The dummy handler registry by default
 * @return The reaction network.
 */
std::shared_ptr<xolotlCore::NEClusterReactionNetwork> getSimpleNEReactionNetwork(
		const int maxClusterSize = 10,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
				std::make_shared<xolotlPerf::DummyHandlerRegistry>());

<<<<<<< HEAD
=======
/**
 * This operation creates a SimpleFeReactionNetwork and makes sure that it is
 * properly registered with the clusters it contains. This operation should
 * always be called instead of constructing a SimpleReactionNetwork manually.
 *
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 5 by default.
 * @param registry The dummy handler registry by default
 * @return The reaction network.
 */
std::shared_ptr<xolotlCore::FeClusterReactionNetwork> getSimpleFeReactionNetwork(
		const int maxClusterSize = 5,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
				std::make_shared<xolotlPerf::DummyHandlerRegistry>());

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
} /* end namespace testUtils */
#endif
