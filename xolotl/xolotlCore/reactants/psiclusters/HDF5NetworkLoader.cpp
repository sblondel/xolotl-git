#include "HDF5NetworkLoader.h"
#include <stdio.h>
#include <limits>
#include <algorithm>
#include <vector>
<<<<<<< HEAD
#include "HeCluster.h"
#include "VCluster.h"
#include "InterstitialCluster.h"
#include "HeVCluster.h"
// #include "HeInterstitialCluster.h"
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include "PSIClusterReactionNetwork.h"
#include <xolotlPerf.h>
#include <HDF5Utils.h>

using namespace xolotlCore;

<<<<<<< HEAD
std::shared_ptr<PSIClusterReactionNetwork> HDF5NetworkLoader::load() {
=======
std::shared_ptr<IReactionNetwork> HDF5NetworkLoader::load() {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get the dataset from the HDF5 files
	auto networkVector = xolotlCore::HDF5Utils::readNetwork(fileName);

	// Initialization
	int numHe = 0, numV = 0, numI = 0;
	double formationEnergy = 0.0, migrationEnergy = 0.0;
	double diffusionFactor = 0.0;
	std::vector<std::shared_ptr<Reactant> > reactants;

	// Prepare the network
	std::shared_ptr<PSIClusterReactionNetwork> network = std::make_shared
			< PSIClusterReactionNetwork > (handlerRegistry);

	// Loop on the networkVector
	for (auto lineIt = networkVector.begin(); lineIt != networkVector.end();
			lineIt++) {
		// Composition of the cluster
		numHe = (int) (*lineIt)[0];
		numV = (int) (*lineIt)[1];
		numI = (int) (*lineIt)[2];
		// Create the cluster
<<<<<<< HEAD
		auto nextCluster = createCluster(numHe, numV, numI);
=======
		auto nextCluster = createPSICluster(numHe, numV, numI);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Energies
		formationEnergy = (*lineIt)[3];
		migrationEnergy = (*lineIt)[4];
		diffusionFactor = (*lineIt)[5];

		// Set the formation energy
		nextCluster->setFormationEnergy(formationEnergy);
		// Set the diffusion factor and migration energy
		nextCluster->setMigrationEnergy(migrationEnergy);
		nextCluster->setDiffusionFactor(diffusionFactor);
<<<<<<< HEAD
		// Add the cluster to the network
		network->add(nextCluster);
		// Add it to the list so that we can set the network later
		reactants.push_back(nextCluster);
=======

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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Set the reaction network for each reactant
	for (auto reactantsIt = reactants.begin(); reactantsIt != reactants.end();
			++reactantsIt) {
		(*reactantsIt)->setReactionNetwork(network);
	}

<<<<<<< HEAD
	return network;
}

void HDF5NetworkLoader::setFilename (const std::string& name) {
	fileName = name;

	return;
}

std::string HDF5NetworkLoader::getFilename () const {
	return fileName;
=======
	// Create the reactions
	network->createReactionConnectivity();

	// Check if we want dummy reactions
	if (!dummyReactions) {
		// Apply sectional grouping
		applySectionalGrouping(network);
	}

	return network;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

