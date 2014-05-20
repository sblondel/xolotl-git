#include "HDF5NetworkLoader.h"
#include <stdio.h>
#include <limits>
#include <algorithm>
#include <vector>
<<<<<<< HEAD
#include "PSIClusterReactionNetwork.h"
#include <xolotlPerf.h>
=======
#include "HeCluster.h"
#include "VCluster.h"
#include "InterstitialCluster.h"
#include "HeVCluster.h"
// #include "HeInterstitialCluster.h"
#include "PSIClusterReactionNetwork.h"
#include <HandlerRegistryFactory.h>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include <HDF5Utils.h>

using namespace xolotlCore;

<<<<<<< HEAD
std::shared_ptr<IReactionNetwork> HDF5NetworkLoader::load() {
	// Get the dataset from the HDF5 files
	auto networkVector = xolotlCore::HDF5Utils::readNetwork(fileName);

	// Initialization
	int numHe = 0, numV = 0, numI = 0;
	double formationEnergy = 0.0, migrationEnergy = 0.0;
	double diffusionFactor = 0.0;
=======
std::shared_ptr<PSIClusterReactionNetwork> HDF5NetworkLoader::load() {
	// Get the dataset from the HDF5 files
	auto networkVector = xolotlCore::HDF5Utils::readNetwork("xolotlStart.h5");

	// Initialization
	int numHe = 0, numV = 0, numI = 0;
	double heBindingE = 0.0, vBindingE = 0.0, iBindingE = 0.0, migrationEnergy =
			0.0;
	double diffusionFactor = 0.0;
	std::vector<double> bindingEnergies;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
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
=======
		auto nextCluster = createCluster(numHe, numV, numI);

		// Binding energies
		heBindingE = (*lineIt)[3];
		vBindingE = (*lineIt)[4];
		iBindingE = (*lineIt)[5];
		migrationEnergy = (*lineIt)[6];
		diffusionFactor = (*lineIt)[7];

		// Create the binding energies array and set it
		bindingEnergies.clear();
		bindingEnergies.push_back(heBindingE);
		bindingEnergies.push_back(vBindingE);
		bindingEnergies.push_back(iBindingE);
		nextCluster->setBindingEnergies(bindingEnergies);
		// Set the diffusion factor and migration energy
		nextCluster->setMigrationEnergy(migrationEnergy);
		nextCluster->setDiffusionFactor(diffusionFactor);
		// Add the cluster to the network
		network->add(nextCluster);
		// Add it to the list so that we can set the network later
		reactants.push_back(nextCluster);
	}

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	for (auto reactantsIt = reactants.begin(); reactantsIt != reactants.end();
			++reactantsIt) {
		(*reactantsIt)->setReactionNetwork(network);
	}

<<<<<<< HEAD
	// Create the reactions
	network->createReactionConnectivity();

	// Check if we want dummy reactions
	if (!dummyReactions) {
		// Apply sectional grouping
		applySectionalGrouping(network);
	}

	return network;
}

=======
	return network;
}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
