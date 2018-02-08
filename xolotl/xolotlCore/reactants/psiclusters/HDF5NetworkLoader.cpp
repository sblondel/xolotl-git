#include "HDF5NetworkLoader.h"
#include <stdio.h>
#include <limits>
#include <algorithm>
#include <vector>
#include "PSIClusterReactionNetwork.h"
#include <xolotlPerf.h>
#include <HDF5Utils.h>

using namespace xolotlCore;

<<<<<<< HEAD
std::shared_ptr<IReactionNetwork> HDF5NetworkLoader::load() {
=======
std::unique_ptr<IReactionNetwork> HDF5NetworkLoader::load(
		const IOptions& options) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Get the dataset from the HDF5 files
	auto networkVector = xolotlCore::HDF5Utils::readNetwork(fileName);

	// Initialization
	int numHe = 0, numV = 0, numI = 0;
	double formationEnergy = 0.0, migrationEnergy = 0.0;
	double diffusionFactor = 0.0;
<<<<<<< HEAD
	std::vector<std::shared_ptr<Reactant> > reactants;

	// Prepare the network
	std::shared_ptr<PSIClusterReactionNetwork> network = std::make_shared
			< PSIClusterReactionNetwork > (handlerRegistry);
=======
	std::vector<std::reference_wrapper<Reactant> > reactants;

	// Prepare the network
	std::unique_ptr<PSIClusterReactionNetwork> network(
			new PSIClusterReactionNetwork(handlerRegistry));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Loop on the networkVector
	for (auto lineIt = networkVector.begin(); lineIt != networkVector.end();
			lineIt++) {
		// Composition of the cluster
		numHe = (int) (*lineIt)[0];
		numV = (int) (*lineIt)[1];
		numI = (int) (*lineIt)[2];
<<<<<<< HEAD
		// Create the cluster
		auto nextCluster = createPSICluster(numHe, numV, numI);

		// Energies
		formationEnergy = (*lineIt)[3];
		migrationEnergy = (*lineIt)[4];
		diffusionFactor = (*lineIt)[5];

		// Set the formation energy
		nextCluster->setFormationEnergy(formationEnergy);
		// Set the diffusion factor and migration energy
		nextCluster->setMigrationEnergy(migrationEnergy);
		nextCluster->setDiffusionFactor(diffusionFactor);

		// Check if we want dummy reactions
		if (dummyReactions) {
			// Create a dummy cluster (Reactant) from the existing cluster
			auto dummyCluster = std::static_pointer_cast<Reactant> (nextCluster->Reactant::clone());
			// Add the cluster to the network
			network->add(dummyCluster);
			// Add it to the list so that we can set the network later
			reactants.push_back(dummyCluster);
		}
		else {
			// Add the cluster to the network
			network->add(nextCluster);
			// Add it to the list so that we can set the network later
			reactants.push_back(nextCluster);
		}
	}

	// Set the reaction network for each reactant
	for (auto reactantsIt = reactants.begin(); reactantsIt != reactants.end();
			++reactantsIt) {
		(*reactantsIt)->setReactionNetwork(network);
	}

	// Create the reactions
	network->createReactionConnectivity();

	// Check if we want dummy reactions
	if (!dummyReactions) {
		// Apply sectional grouping
		applySectionalGrouping(network);
	}

	return network;
=======

		// If the cluster is big enough to be grouped
		if (numV >= vMin && numHe > 0) {
			// Created the coordinates and store them
			auto pair = std::make_pair(numHe, numV);
			heVList.emplace(pair);
		} else {
			// Create the cluster
			auto nextCluster = createPSICluster(numHe, numV, numI, *network);

			// Energies
			formationEnergy = (*lineIt)[3];
			migrationEnergy = (*lineIt)[4];
			diffusionFactor = (*lineIt)[5];

			// Set the formation energy
			nextCluster->setFormationEnergy(formationEnergy);
			// Set the diffusion factor and migration energy
			nextCluster->setMigrationEnergy(migrationEnergy);
			nextCluster->setDiffusionFactor(diffusionFactor);

			// Save it in the network
			pushPSICluster(network, reactants, nextCluster);
		}
	}

	// Ask reactants to update now that they are in network.
	for (IReactant& currReactant : reactants) {
		currReactant.updateFromNetwork();
	}

	// Check if we want dummy reactions
	if (!dummyReactions) {
		// Apply sectional grouping
		applySectionalGrouping(*network);
	}

	// Create the reactions
	network->createReactionConnectivity();

	// Recompute Ids and network size
	network->reinitializeNetwork();

	// Need to use move() because return type uses smart pointer to base class,
	// not derived class that we created.
	// Some C++11 compilers accept it without the move, but apparently
	// that is not correct behavior until C++14.
	return std::move(network);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

