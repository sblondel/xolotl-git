#ifndef SIMPLEREACTIONNETWORK_H_
#define SIMPLEREACTIONNETWORK_H_

#include <PSIClusterReactionNetwork.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <NEClusterReactionNetwork.h>
#include <xolotlPerf.h>
#include <DummyHandlerRegistry.h>
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
#include "../../xolotlPerf/dummy/DummyHandlerRegistry.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
#include "../../xolotlPerf/dummy/DummyHandlerRegistry.h"
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

namespace testUtils {

/**
 * This class creates a simple reaction network used for testing. It contains
 * 10 each of He, V and I clusters and twenty HeV clusters. The HeV clusters are
 * stored in ascending order of He and then V, (1,1;2,1;2,2;3,2;3,3;etc.).
 *
 * It does not register itself as the ReactionNetwork for its clusters because
 * of limitations with shared_ptrs and "this." So, the
<<<<<<< HEAD
<<<<<<< HEAD
 * TestUtils::getSimplePSIReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimplePSIReactionNetwork: public xolotlCore::PSIClusterReactionNetwork {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
 * TestUtils::getSimpleReactionNetwork() operation should always be called to
 * insure that it is properly initialized.
 */
class SimpleReactionNetwork: public xolotlCore::PSIClusterReactionNetwork {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:
	/**
	 * Constructor
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * @param maxClusterSize the maximal size of the clusters that will be in
	 * the network. Set to 10 by default.
	 */
	SimpleReactionNetwork(const int maxClusterSize = 10,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>());

	//! Destructor
	virtual ~SimpleReactionNetwork();
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

};

/**
<<<<<<< HEAD
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
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

};

/**
<<<<<<< HEAD
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
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
 * This operation creates a SimpleReactionNetwork and makes sure that it is
 * properly registered with the clusters it contains. This operation should
 * always be called instead of constructing a SimpleReactionNetwork manually.
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 10 by default.
 * @return The reaction network.
 */
std::shared_ptr<xolotlCore::ReactionNetwork> getSimpleReactionNetwork(const int maxClusterSize = 10,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>());
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

} /* end namespace testUtils */
#endif
