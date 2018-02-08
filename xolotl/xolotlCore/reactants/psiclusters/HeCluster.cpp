// Includes
#include "HeCluster.h"
#include "PSIClusterReactionNetwork.h"
#include <Constants.h>
#include <iostream>

using namespace xolotlCore;

<<<<<<< HEAD
HeCluster::HeCluster(int nHe,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(registry) {
	// Set the size
	size = nHe;
	// Update the composition map
	compositionMap[heType] = size;

	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "He_" << size;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = heType;

	// Compute the reaction radius
	double FourPi = 4.0 * xolotlCore::pi;
	double aCubed = pow(xolotlCore::tungstenLatticeConstant, 3);
=======
HeCluster::HeCluster(int nHe, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(nHe, registry) {
	// Set the reactant name appropriately
	name = "He";
	// Update the composition map
	compositionMap[name] = size;

	// Compute the reaction radius
	double FourPi = 4.0 * xolotlCore::pi;
	double aCubed = pow(xolotlCore::latticeConstant, 3);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	double termOne = pow((3.0 / FourPi) * (1.0 / 10.0) * aCubed * size,
			(1.0 / 3.0));
	double termTwo = pow((3.0 / FourPi) * (1.0 / 10.0) * aCubed, (1.0 / 3.0));
	reactionRadius = 0.3 + termOne - termTwo;

	return;
}
<<<<<<< HEAD
=======

HeCluster::~HeCluster() {
}

std::shared_ptr<Reactant> HeCluster::clone() {
	std::shared_ptr<Reactant> reactant(new HeCluster(*this));
	return reactant;
}

void HeCluster::createReactionConnectivity() {

	// Local Declarations - Note the reference to the properties map
	auto psiNetwork = std::dynamic_pointer_cast < PSIClusterReactionNetwork
			> (network);
	std::map<std::string, std::string> props = psiNetwork->getProperties();
	int maxHeClusterSize = std::stoi(props["maxHeClusterSize"]);
	int maxHeVClusterSize = std::stoi(props["maxHeVClusterSize"]);
	int maxHeIClusterSize = std::stoi(props["maxHeIClusterSize"]);
	int numHeVClusters = std::stoi(props["numHeVClusters"]);
	int numHeIClusters = std::stoi(props["numHeIClusters"]);
	int firstSize = 0, secondSize = 0;
	std::map<std::string, int> composition;
	std::shared_ptr<PSICluster> psiCluster, firstReactant, secondReactant,
			productReactant;

	// Connect this cluster to itself since any reaction will affect it
	setReactionConnectivity(getId());

	/*
	 * This section fills the array of reacting pairs that combine to produce
	 * this cluster. The only reactions that produce He clusters are those He
	 * clusters that are smaller than this one. Each cluster i combines with
	 * a second cluster of this size - i.size.
	 *
	 * Total size starts with a value of one so that clusters of size one are
	 * not considered in this loop.
	 */
	for (firstSize = 1; firstSize <= (int) size/2; firstSize++) {
		secondSize = size - firstSize;
		// Get the first and second reactants for the reaction
		// first + second = this.
		firstReactant = std::dynamic_pointer_cast < PSICluster
				> (psiNetwork->get("He", firstSize));
		secondReactant = std::dynamic_pointer_cast < PSICluster
				> (psiNetwork->get("He", secondSize));
		// Create a ReactingPair with the two reactants
		if (firstReactant && secondReactant) {
			ReactingPair pair;
			pair.first = firstReactant;
			pair.second = secondReactant;
			// Add the pair to the list
			reactingPairs.push_back(pair);
		}
	}

	/* ----- He_a + He_b --> He_(a+b) -----
	 * This cluster should interact with all other clusters of the same type up
	 * to the max size minus the size of this one to produce larger clusters.
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	auto reactants = psiNetwork->getAll("He");
	combineClusters(reactants,maxHeClusterSize,"He");

	/* -----  He_a + V_b --> (He_a)(V_b) -----
	 * Helium clusters can interact with any vacancy cluster so long as the sum
	 * of the number of helium atoms and vacancies does not produce a cluster
	 * with a size greater than the maximum mixed-species cluster size.
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	reactants = psiNetwork->getAll("V");
	combineClusters(reactants,maxHeVClusterSize,"HeV");

	/* ----- He_a + I_b --> (He_a)(I_b)
	 * Helium clusters can interact with any interstitial cluster so long as
	 * the sum of the number of helium atoms and interstitials does not produce
	 * a cluster with a size greater than the maximum mixed-species cluster
	 * size.

	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	reactants = psiNetwork->getAll("I");
	combineClusters(reactants,maxHeIClusterSize,"HeI");

	/* ----- He_a + (He_b)(V_c) --> [He_(a+b)](V_c) -----
	 * Helium can interact with a mixed-species cluster so long as the sum of
	 * the number of helium atoms and the size of the mixed-species cluster
	 * does not exceed the maximum mixed-species cluster size.
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 *
	 * Find the clusters by looping over all size combinations of HeV clusters.
	 */
	if (numHeVClusters > 0) {
		reactants = psiNetwork->getAll("HeV");
		combineClusters(reactants,maxHeVClusterSize,"HeV");
	}

	/* ----- He_a + (He_b)(I_c) --> [He_(a+b)](I_c) -----
	 * Helium-interstitial clusters can absorb single-species helium clusters
	 * so long as the maximum cluster size limit is not violated.
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 *
	 * Find the clusters by looping over all size combinations of HeI clusters.
	 */
	if (numHeIClusters > 0) {
		reactants = psiNetwork->getAll("HeI");
		combineClusters(reactants,maxHeIClusterSize,"HeI");
	}

	return;
}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
