/*
 * SimpleReactionNetwork.cpp
 *
 *  Created on: Jun 29, 2013
 *      Author: bkj
 */

#include "SimpleReactionNetwork.h"
#include <PSICluster.h>
#include <HeCluster.h>
#include <VCluster.h>
#include <InterstitialCluster.h>
#include <HeVCluster.h>
#include <HeInterstitialCluster.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <NECluster.h>
#include <XeCluster.h>
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include <memory>
#include <typeinfo>
#include <limits>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace xolotlCore;
using namespace testUtils;
using namespace xolotlPerf;

<<<<<<< HEAD
<<<<<<< HEAD
SimplePSIReactionNetwork::SimplePSIReactionNetwork(const int maxClusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSIClusterReactionNetwork(registry) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
/**
 * Constructor
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 10 by default.
 */
SimpleReactionNetwork::SimpleReactionNetwork(const int maxClusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
	PSIClusterReactionNetwork(registry){

<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	// Add He clusters
	for (int numHe = 1; numHe <= maxClusterSize; numHe++) {
		// Create a He cluster with cluster size numHe
		shared_ptr<HeCluster> cluster = make_shared<HeCluster>(numHe, registry);
<<<<<<< HEAD
<<<<<<< HEAD
		// Set the diffusion factor for some of them to 1.0 so that they can react
		if (numHe < 8) cluster->setDiffusionFactor(1.0);
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		// Add it to the network
		add(cluster);
	}

	// Add vacancy clusters
	for (int numV = 1; numV <= maxClusterSize; numV++) {
		// Create a V cluster with cluster size numV
		shared_ptr<VCluster> cluster = make_shared<VCluster>(numV, registry);
<<<<<<< HEAD
<<<<<<< HEAD
		// Set the diffusion factor for the first one so that it can react
		if (numV == 1) cluster->setDiffusionFactor(1.0);
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		// Add it to the network
		add(cluster);
	}

	// Add interstitial clusters
	for (int numI = 1; numI <= maxClusterSize; numI++) {
		// Create a He cluster with cluster size numI
<<<<<<< HEAD
<<<<<<< HEAD
		shared_ptr<InterstitialCluster> cluster = make_shared<
				InterstitialCluster>(numI, registry);
		// Set the diffusion factor for all of them to 1.0 so that they can react
		cluster->setDiffusionFactor(1.0);
=======
		shared_ptr<InterstitialCluster> cluster = make_shared<InterstitialCluster>(numI, registry);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
		shared_ptr<InterstitialCluster> cluster = make_shared<InterstitialCluster>(numI, registry);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		// Add it to the network
		add(cluster);
	}

	// Add HeV clusters, assuming that
	// numHe + numV <= maxMixedClusterSize
	for (int numV = 1; numV <= maxClusterSize; numV++) {
		for (int numHe = 1; numHe + numV <= maxClusterSize; numHe++) {
			// Create a HeVCluster with the current amount of He and V
<<<<<<< HEAD
<<<<<<< HEAD
			shared_ptr<HeVCluster> cluster = make_shared<HeVCluster>(numHe,
					numV, registry);
=======
			shared_ptr<HeVCluster> cluster = make_shared<HeVCluster>(numHe, numV, registry);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
			shared_ptr<HeVCluster> cluster = make_shared<HeVCluster>(numHe, numV, registry);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
			add(cluster);
		}
	}

	// Add HeI clusters
	// Create all possible combinations of numHe and numI
	// clusters with numHe, numI < maxClusterSize
	for (int numI = 1; numI <= maxClusterSize; numI++) {
		for (int numHe = 1; numHe + numI <= maxClusterSize; numHe++) {
			// Create the HeI cluster
<<<<<<< HEAD
<<<<<<< HEAD
			shared_ptr<HeInterstitialCluster> cluster = make_shared<
					HeInterstitialCluster>(numHe, numI, registry);
=======
			shared_ptr<HeInterstitialCluster> cluster = make_shared<HeInterstitialCluster>(numHe, numI, registry);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
			shared_ptr<HeInterstitialCluster> cluster = make_shared<HeInterstitialCluster>(numHe, numI, registry);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
			// Add it to the reactants vector
			add(cluster);
		}
	}

	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
SimpleNEReactionNetwork::SimpleNEReactionNetwork(const int maxClusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		NEClusterReactionNetwork(registry) {
	// Add Xe clusters
	for (int numXe = 1; numXe <= maxClusterSize; numXe++) {
		// Create a He cluster with cluster size numHe
		shared_ptr<XeCluster> cluster = make_shared<XeCluster>(numXe, registry);
		// Set the diffusion factor for the first one so that it can react
		if (numXe == 1) cluster->setDiffusionFactor(1.0);
		// Add it to the network
		add(cluster);
	}

	return;
}

shared_ptr<xolotlCore::PSIClusterReactionNetwork> testUtils::getSimplePSIReactionNetwork(
		const int maxClusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {
	// Create the network
	shared_ptr<xolotlCore::PSIClusterReactionNetwork> network(
			new SimplePSIReactionNetwork(maxClusterSize, registry));
	cout << "SimpleReactionNetwork Message: " << "Created network with size "
			<< network->size() << endl;
	// Register the reaction network with its clusters
	auto reactants = network->getAll();
	for (unsigned int i = 0; i < reactants->size(); i++) {
		reactants->at(i)->setReactionNetwork(network);
	}
	// Create the reactions
	network->createReactionConnectivity();

	// ----- TEMPORARY DEBUG OUTPUT!!!!! -----
	// Print the reaction connectivity matrix
	for (auto reactantIt = reactants->begin(); reactantIt != reactants->end();
			reactantIt++) {
		auto cluster = (PSICluster *) (*reactantIt);
		vector<int> conn = cluster->getConnectivity();

		for (auto connIt = conn.begin(); connIt != conn.end(); connIt++) {
			printf("%s", *connIt ? "* " : "' ");
		}
		printf("\n");
	}

	return network;
}

shared_ptr<xolotlCore::NEClusterReactionNetwork> testUtils::getSimpleNEReactionNetwork(
		const int maxClusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {
	// Create the network
	shared_ptr<xolotlCore::NEClusterReactionNetwork> network(
			new SimpleNEReactionNetwork(maxClusterSize, registry));
	cout << "SimpleReactionNetwork Message: " << "Created network with size "
			<< network->size() << endl;
	// Register the reaction network with its clusters
	auto reactants = network->getAll();
	for (unsigned int i = 0; i < reactants->size(); i++) {
		reactants->at(i)->setReactionNetwork(network);
	}
	// Create the reactions
	network->createReactionConnectivity();

	// ----- TEMPORARY DEBUG OUTPUT!!!!! -----
	// Print the reaction connectivity matrix
	for (auto reactantIt = reactants->begin(); reactantIt != reactants->end();
			reactantIt++) {
		auto cluster = (NECluster *) (*reactantIt);
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
SimpleReactionNetwork::~SimpleReactionNetwork() {
	// Nothing to do
}

/**
 * This operation creates a SimpleReactionNetwork and makes sure that it is
 * properly registered with the clusters it contains. This operation should
 * always be called instead of constructing a SimpleReactionNetwork manually.
 * @param maxClusterSize the maximal size of the clusters that will be in
 * the network. Set to 10 by default.
 * @return The reaction network.
 */
shared_ptr<xolotlCore::ReactionNetwork> testUtils::getSimpleReactionNetwork(const int maxClusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {

	// Create the network
	shared_ptr<xolotlCore::ReactionNetwork> network(
			new SimpleReactionNetwork(maxClusterSize, registry));
	cout << "SimpleReactionNetwork Message: "
			<< "Created network with size " << network->size() << endl;
	// Register the reaction network with its clusters
	auto reactants = network->getAll();
	for (int i = 0; i < reactants->size(); i++) {
		reactants->at(i)->setReactionNetwork(network);
	}

	// ----- TEMPORARY DEBUG OUTPUT!!!!! -----
	// Print the reaction connectivity matrix
	for (auto reactantIt = reactants->begin();
			reactantIt != reactants->end(); reactantIt++) {
<<<<<<< HEAD
<<<<<<< HEAD
		shared_ptr<PSICluster> cluster = dynamic_pointer_cast<
				PSICluster>(*reactantIt);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
		auto cluster = (PSICluster *) (*reactantIt);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
		auto cluster = (PSICluster *) (*reactantIt);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		vector<int> conn = cluster->getConnectivity();

		for (auto connIt = conn.begin(); connIt != conn.end(); connIt++) {
			printf("%s", *connIt ? "* " : "' ");
		}
		printf("\n");
	}

	return network;
}
