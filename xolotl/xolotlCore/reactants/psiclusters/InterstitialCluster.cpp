#include "InterstitialCluster.h"
#include <Constants.h>
#include <iostream>

using namespace xolotlCore;

<<<<<<< HEAD
InterstitialCluster::InterstitialCluster(int nI,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(registry) {
	// Set the size
	size = nI;
	// Update the composition map
	compositionMap[iType] = size;

	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "I_" << size;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = iType;

	// Compute the reaction radius
	double EightPi = 8.0 * xolotlCore::pi;
	double aCubed = pow(xolotlCore::tungstenLatticeConstant, 3.0);
	double termOne = 1.15 * (sqrt(3.0) / 4.0)
			* xolotlCore::tungstenLatticeConstant;
=======
InterstitialCluster::InterstitialCluster(int nI, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(nI, registry) {
	// Set the reactant name appropriately
	name = "I";
	// Update the composition map
	compositionMap[name] = size;

	// Compute the reaction radius
	double EightPi = 8.0 * xolotlCore::pi;
	double aCubed = pow(xolotlCore::latticeConstant, 3.0);
	double termOne = 1.15 * (sqrt(3.0) / 4.0) * xolotlCore::latticeConstant;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	double termTwo = pow((3.0 / EightPi) * aCubed * size, (1.0 / 3.0));
	double termThree = pow((3.0 / EightPi) * aCubed, (1.0 / 3.0));
	reactionRadius = termOne + termTwo - termThree;

<<<<<<< HEAD
=======
}

InterstitialCluster::~InterstitialCluster() {
}

std::shared_ptr<Reactant> InterstitialCluster::clone() {
	std::shared_ptr<Reactant> reactant(new InterstitialCluster(*this));
	return reactant;
}

void InterstitialCluster::createReactionConnectivity() {

	// Local Declarations - Note the reference to the properties map
	auto props = network->getProperties();
	int maxIClusterSize = std::stoi(props["maxIClusterSize"]);
	int maxHeIClusterSize = std::stoi(props["maxHeIClusterSize"]);
	int numHeVClusters = std::stoi(props["numHeVClusters"]);
	int numHeIClusters = std::stoi(props["numHeIClusters"]);
	int firstSize = 0, secondSize = 0, reactantsSize = 0;
	std::shared_ptr<PSICluster> firstReactant, secondReactant;

	// Connect this cluster to itself since any reaction will affect it
	setReactionConnectivity(getId());

	/*
	 * This section fills the array of reacting pairs that combine to produce
	 * this cluster from I clusters that are smaller than this.size. Each
	 * cluster i combines with a second cluster of size this.size - i.size.
	 *
	 * Total size starts with a value of one so that clusters of size one are
	 * not considered in this loop.
	 */
	for (firstSize = 1; firstSize <= (int) size/2; firstSize++) {
		secondSize = size - firstSize;
		// Get the first and second reactants for the reaction
		// first + second = this.
		firstReactant = std::dynamic_pointer_cast<PSICluster>(network->get("I", firstSize));
		secondReactant = std::dynamic_pointer_cast<PSICluster>(network->get("I", secondSize));
		// Create a ReactingPair with the two reactants
		if (firstReactant && secondReactant) {
			ReactingPair pair;
			pair.first = firstReactant;
			pair.second = secondReactant;
			// Add the pair to the list
			reactingPairs.push_back(pair);
		}
	}

	/* ----- I_a + I_b --> I_(a+b) -----
	 *	Interstitial absorption
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	auto reactants = network->getAll("I");
	combineClusters(reactants,maxIClusterSize,"I");

	/* ----- He_a + I_b --> (He_a)*(I_b)
	 * Interstitials can interact with clusters of He to form HeI clusters.
	 * They cannot cluster with He clusters that are so large that the
	 * combination of the two would produce an HeI cluster above the
	 * maximum size.
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	reactants = network->getAll("He");
	combineClusters(reactants,maxHeIClusterSize,"HeI");

	/* ----- I_a + V_b -----
	 * --> I_(a-b), if a > b
	 * --> V_(b-a), if a < b
	 * --> 0, if a = b
	 * Interstitial-Vacancy Annihilation
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	reactants = network->getAll("V");
	fillVWithI("V",reactants);
	// Mark the reaction connectivity for the cases where this cluster is
	// produced by the above reaction. This has to be checked for every
	// vacancy.
	reactantsSize = reactants->size();
	for (int i = 0; i < reactantsSize; i++) {
		firstReactant = std::dynamic_pointer_cast<PSICluster>(reactants->at(i));
		// Get the interstitial cluster that is bigger than the vacancy
		// and can form this cluster. I only results when it is bigger than V.
		secondReactant = std::dynamic_pointer_cast<PSICluster>(network->get(name,firstReactant->getSize() + size));
		// Update the connectivity
		if (secondReactant) {
			setReactionConnectivity(firstReactant->getId());
			setReactionConnectivity(secondReactant->getId());
		}
	}

	/* ----- (He_a)(V_b) + (I_c) --> (He_a)[V_(b-c)] -----
	 * Interstitials interact with all mixed-species clusters by
	 * annihilating vacancies.
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	if (numHeVClusters > 0) {
		reactants = network->getAll("HeV");
		replaceInCompound(reactants,"V","I");
	}

	/* ----- (He_a)*(I_b) + I --> (He_a)*[I_(b + 1)] -----
	 * Single interstitial absorption by a HeI cluster under the condition
	 * that (x + y + 1) <= maxSize
	 *
	 * All of these clusters are added to the set of combining reactants
	 * because they contribute to the flux due to combination reactions.
	 */
	if (size == 1 && numHeIClusters > 0) {
		reactants = network->getAll("HeI");
		combineClusters(reactants,maxHeIClusterSize,"HeI");
	}

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	return;
}
