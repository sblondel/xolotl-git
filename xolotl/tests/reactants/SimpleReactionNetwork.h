#ifndef SIMPLEREACTIONNETWORK_H_
#define SIMPLEREACTIONNETWORK_H_

#include <PSIClusterReactionNetwork.h>
<<<<<<< HEAD
=======
#include <NEClusterReactionNetwork.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
<<<<<<< HEAD
 * TestUtils::getSimpleReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimpleReactionNetwork: public xolotlCore::PSIClusterReactionNetwork {
=======
 * TestUtils::getSimplePSIReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimplePSIReactionNetwork: public xolotlCore::PSIClusterReactionNetwork {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:
	/**
	 * Constructor
	 *
	 * @param maxClusterSize the maximal size of the clusters that will be in
	 * the network. Set to 10 by default.
	 * @param registry The dummy handler registry by default
	 */
<<<<<<< HEAD
	SimpleReactionNetwork(const int maxClusterSize = 10,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>());

	//! Destructor
	virtual ~SimpleReactionNetwork() {}
=======
	SimplePSIReactionNetwork(const int maxClusterSize = 10,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
					std::make_shared<xolotlPerf::DummyHandlerRegistry>());

	//! Destructor
	virtual ~SimplePSIReactionNetwork() {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

};

/**
<<<<<<< HEAD
 * This operation creates a SimpleReactionNetwork and makes sure that it is
=======
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
 * properly registered with the clusters it contains. This operation should
 * always be called instead of constructing a SimpleReactionNetwork manually.
 *
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 10 by default.
 * @param registry The dummy handler registry by default
 * @return The reaction network.
 */
<<<<<<< HEAD
std::shared_ptr<xolotlCore::ReactionNetwork> getSimpleReactionNetwork(const int maxClusterSize = 10,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>());
=======
std::shared_ptr<xolotlCore::NEClusterReactionNetwork> getSimpleNEReactionNetwork(
		const int maxClusterSize = 10,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
				std::make_shared<xolotlPerf::DummyHandlerRegistry>());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

} /* end namespace testUtils */
#endif
