<<<<<<< HEAD
#include "NEClusterNetworkLoader.h"
#include <XeCluster.h>
=======
#include <fstream>
#include <functional>
#include <cassert>
#include "NEClusterNetworkLoader.h"
#include <NEClusterReactionNetwork.h>
#include <NEXeCluster.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <NESuperCluster.h>
#include <HDF5Utils.h>
#include <xolotlPerf.h>

using namespace xolotlCore;

///**
// * This operation converts a string to a double, taking in to account the fact
// * that the input file may contain keys such as "infinite."
// *
// * @param inString the string to be converted
// * @return the string as a double
// */
//static inline double convertStrToDouble(const std::string& inString) {
//	return (inString.compare("infinite") == 0) ?
//			std::numeric_limits<double>::infinity() :
//			strtod(inString.c_str(), NULL);
//}

<<<<<<< HEAD
std::shared_ptr<NECluster> NEClusterNetworkLoader::createNECluster(int numXe,
		int numV, int numI) {
	// Local Declarations
	std::shared_ptr<NECluster> cluster;
=======
std::unique_ptr<NECluster> NEClusterNetworkLoader::createNECluster(int numXe,
		int numV, int numI, IReactionNetwork& network) const {

	// Local Declarations
	NECluster* cluster = nullptr;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Determine the type of the cluster given the number of each species.
	// Create a new cluster by that type and specify the names of the
	// property keys.
	if (numXe > 0) {
		// Create a new XeVCluster
<<<<<<< HEAD
		cluster = std::make_shared<XeCluster>(numXe, handlerRegistry);
	}

	return cluster;
}

void NEClusterNetworkLoader::pushNECluster(
		std::shared_ptr<NEClusterReactionNetwork> & network,
		std::vector<std::shared_ptr<Reactant> > & reactants,
		std::shared_ptr<NECluster> & cluster) {
	// Check if we want dummy reactions
	if (dummyReactions) {
		// Create a dummy cluster (Reactant) from the existing cluster
		auto dummyCluster = std::static_pointer_cast<Reactant>(
				cluster->Reactant::clone());
		// Add the cluster to the network
		network->add(dummyCluster);
		// Add it to the list so that we can set the network later
		reactants.push_back(dummyCluster);
	} else {
		// Add the cluster to the network
		network->add(cluster);
		// Add it to the list so that we can set the network later
		reactants.push_back(cluster);
=======
		cluster = new NEXeCluster(numXe, network, handlerRegistry);
	}
	assert(cluster != nullptr);

	// TODO when we have widespread C++14 support, use std::make_unique
	// and construct unique ptr and object pointed to in one memory operation.
	return std::unique_ptr<NECluster>(cluster);
}

void NEClusterNetworkLoader::pushNECluster(
		std::unique_ptr<NEClusterReactionNetwork> & network,
		std::vector<std::reference_wrapper<Reactant> > & reactants,
		std::unique_ptr<NECluster> & cluster) {
	// Check if we want dummy reactions
	if (dummyReactions) {
		// Create a dummy cluster (Reactant) from the existing cluster
		auto dummyCluster = std::unique_ptr<Reactant>(new Reactant(*cluster));
		// Save access to it so we can trigger updates after
		// we add all to the network.
		reactants.emplace_back(*dummyCluster);

		// Give the cluster to the network
		network->add(std::move(dummyCluster));
	} else {
		// Save access to it so we can trigger updates after
		// we add all to the network.
		reactants.emplace_back(*cluster);

		// Give the cluster to the network
		network->add(std::move(cluster));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

NEClusterNetworkLoader::NEClusterNetworkLoader(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {
	networkStream = nullptr;
	handlerRegistry = registry;
	fileName = "";
	dummyReactions = false;
	xeMin = 1000000;
	sectionWidth = 1;

	return;
}

NEClusterNetworkLoader::NEClusterNetworkLoader(
		const std::shared_ptr<std::istream> stream,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {
	networkStream = stream;
	handlerRegistry = registry;
	fileName = "";
	dummyReactions = false;
	xeMin = 1000000;
	sectionWidth = 1;

	return;
}

<<<<<<< HEAD
std::shared_ptr<IReactionNetwork> NEClusterNetworkLoader::load() {
=======
std::unique_ptr<IReactionNetwork> NEClusterNetworkLoader::load(
		const IOptions& options) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Get the dataset from the HDF5 files
	auto networkVector = xolotlCore::HDF5Utils::readNetwork(fileName);

	// Initialization
	int numXe = 0, numV = 0, numI = 0;
	double formationEnergy = 0.0, migrationEnergy = 0.0;
	double diffusionFactor = 0.0;
<<<<<<< HEAD
	std::vector<std::shared_ptr<Reactant> > reactants;

	// Prepare the network
	std::shared_ptr<NEClusterReactionNetwork> network = std::make_shared<
			NEClusterReactionNetwork>(handlerRegistry);
=======
	std::vector<std::reference_wrapper<Reactant> > reactants;

	// Prepare the network
	// Once we have C++14 support, use std::make_unique.
	std::unique_ptr<NEClusterReactionNetwork> network(
			new NEClusterReactionNetwork(handlerRegistry));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Loop on the networkVector
	for (auto lineIt = networkVector.begin(); lineIt != networkVector.end();
			lineIt++) {

		// Composition of the cluster
		numXe = (int) (*lineIt)[0];
		numV = (int) (*lineIt)[1];
		numI = (int) (*lineIt)[2];
		// Create the cluster
<<<<<<< HEAD
		auto nextCluster = createNECluster(numXe, numV, numI);
=======
		auto nextCluster = createNECluster(numXe, numV, numI, *network);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
		// Push the cluster to the network
=======
		// Save it in the network
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		pushNECluster(network, reactants, nextCluster);
	}

	// Set the reaction network for each reactant
<<<<<<< HEAD
	for (auto currCluster : reactants) {
		currCluster->setReactionNetwork(network);
=======
	for (Reactant& currCluster : reactants) {
		currCluster.updateFromNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Create the reactions
	network->createReactionConnectivity();

	// Check if we want dummy reactions
	if (!dummyReactions) {
		// Apply grouping
<<<<<<< HEAD
		applyGrouping(network);
	}

	return network;
}

std::shared_ptr<IReactionNetwork> NEClusterNetworkLoader::generate(
		IOptions &options) {
=======
		applyGrouping(*network);
	}

//	// Dump the network we've created, if desired.
//	int rank;
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	if (rank == 0) {
//		// Dump the network we've created for comparison with baseline.
//		std::ofstream networkStream(netDebugOpts.second);
//		network->dumpTo(networkStream);
//	}

	// Need to use move() because return type uses smart pointer to base class,
	// not derived class that we created.
	// Some C++11 compilers accept it without the move, but apparently
	// that is not correct behavior until C++14.
	return std::move(network);
}

std::unique_ptr<IReactionNetwork> NEClusterNetworkLoader::generate(
		const IOptions &options) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Initial declarations
	int maxXe = options.getMaxImpurity();
	int numXe = 0;
	double formationEnergy = 0.0, migrationEnergy = 0.0;
	double diffusionFactor = 0.0;
<<<<<<< HEAD
	std::shared_ptr<NEClusterReactionNetwork> network = std::make_shared<
			NEClusterReactionNetwork>(handlerRegistry);
	std::vector<std::shared_ptr<Reactant> > reactants;
=======
	// Once we have C++14 support, use std::make_unique.
	std::unique_ptr<NEClusterReactionNetwork> network(
			new NEClusterReactionNetwork(handlerRegistry));
	std::vector<std::reference_wrapper<Reactant> > reactants;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// The diffusion factor for a single xenon in nm^2/s
	double xeOneDiffusion = 7.6e8;

	// The migration energy for a single xenon in eV
	double xeOneMigration = 3.04;

	/**
	 * The set of xenon formation energies up to Xe_29 indexed by size. That is
	 * E_(f,Xe_1) = xeFormationEnergies[1]. The value at index zero is just
	 * padding to make the indexing easy.
	 */
	std::vector<double> xeFormationEnergies = { 7.0, 12.15, 17.15, 21.90, 26.50,
			31.05, 35.30, 39.45, 43.00, 46.90, 50.65, 53.90, 56.90, 59.80,
			62.55, 65.05, 67.45, 69.45, 71.20, 72.75, 74.15, 75.35, 76.40,
			77.25, 77.95, 78.45, 78.80, 78.95, 79.0 };

	// Generate the I clusters
	for (int i = 1; i <= maxXe; ++i) {
		// Set the composition
		numXe = i;
		// Create the cluster
<<<<<<< HEAD
		auto nextCluster = createNECluster(numXe, 0, 0);
=======
		auto nextCluster = createNECluster(numXe, 0, 0, *network);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Set the other attributes
		if (i <= xeFormationEnergies.size())
			nextCluster->setFormationEnergy(xeFormationEnergies[i - 1]);
		else
			nextCluster->setFormationEnergy(79.0);
		if (i <= 1) {
			nextCluster->setDiffusionFactor(xeOneDiffusion);
			nextCluster->setMigrationEnergy(xeOneMigration);
		} else {
			nextCluster->setDiffusionFactor(0.0);
			nextCluster->setMigrationEnergy(
					std::numeric_limits<double>::infinity());
		}

<<<<<<< HEAD
		// Push the cluster to the network
		pushNECluster(network, reactants, nextCluster);
	}

	std::cout << reactants.size() << std::endl;

	// Set the network for all of the reactants. This MUST be done manually.
	for (auto currCluster : reactants) {
		currCluster->setReactionNetwork(network);
=======
		// Save it in the network
		pushNECluster(network, reactants, nextCluster);
	}

	// Set the network for all of the reactants. This MUST be done manually.
	for (Reactant& currCluster : reactants) {
		currCluster.updateFromNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Create the reactions
	network->createReactionConnectivity();

	// Check if we want dummy reactions
	if (!dummyReactions) {
		// Apply sectional grouping
<<<<<<< HEAD
		applyGrouping(network);
	}

	return network;
}

void NEClusterNetworkLoader::applyGrouping(
		std::shared_ptr<IReactionNetwork> network) {
	// Get the xenon cluster map
	auto xeMap = network->getAll(xeType);
=======
		applyGrouping(*network);
	}

//	// Dump the network we've created, if desired.
//	int rank;
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	if (rank == 0) {
//		// Dump the network we've created for comparison with baseline.
//		std::ofstream networkStream(netDebugOpts.second);
//		network->dumpTo(networkStream);
//	}

	// Need to use move() because return type uses smart pointer to base class,
	// not derived class that we created.
	// Some C++11 compilers accept it without the move, but apparently
	// that is not correct behavior until C++14.
	return std::move(network);
}

void NEClusterNetworkLoader::applyGrouping(IReactionNetwork& network) const {
	// Get the xenon cluster map
	auto const& xeMap = network.getAll(ReactantType::Xe);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Create a temporary vector for the loop
	std::vector<NECluster *> tempVector;

	// Initialize variables for the loop
<<<<<<< HEAD
	NECluster * cluster;
	std::shared_ptr<NESuperCluster> superCluster;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	int count = 0, superCount = 0, width = sectionWidth;
	double size = 0.0, radius = 0.0, energy = 0.0;

	// Map to know which cluster is in which group
	std::map<int, int> clusterGroupMap;
	// Map to know which super cluster gathers which group
<<<<<<< HEAD
=======
	// TODO replace use of naked ptr with ref.  Requires fix to use
	// refs in reactions instead of naked ptrs.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	std::map<int, NESuperCluster *> superGroupMap;

	// Loop on the xenon groups
	for (int k = xeMin; k <= xeMap.size(); k++) {
		// Get the corresponding cluster
<<<<<<< HEAD
		cluster = (NECluster *) network->get(xeType, k);
=======
		auto cluster = (NECluster *) network.get(Species::Xe, k);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Verify if the cluster exists
		if (!cluster)
			continue;

		// Increment the counter
		count++;

		// Add this cluster to the temporary vector
		tempVector.push_back(cluster);
		size += (double) k;
		radius += cluster->getReactionRadius();
		energy += cluster->getFormationEnergy();

		// Save in which group it is
		clusterGroupMap[k] = superCount;

		// Check if there were clusters in this group
		if (count < width && k < xeMap.size())
			continue;

		// Average all values
		size = size / (double) count;
		radius = radius / (double) count;
		energy = energy / (double) count;
<<<<<<< HEAD
		// Create the cluster
		superCluster = std::make_shared<NESuperCluster>(size, count, count,
				radius, energy, handlerRegistry);
		// Set the HeV vector
		superCluster->setXeVector(tempVector);
		// Add this cluster to the network and clusters
		network->addSuper(superCluster);
		// Keep the information of the group
		superGroupMap[superCount] = superCluster.get();

//		std::cout << superCount << " " << count << " "
//				<< superCluster->getName() << std::endl;
=======

		// Create the cluster
		auto rawSuperCluster = new NESuperCluster(size, count, count, radius,
				energy, network, handlerRegistry);
		auto superCluster = std::unique_ptr<NESuperCluster>(rawSuperCluster);
		// Save access to the cluster so we can trigger updates
		// after we give it to the network.
		auto& scref = *superCluster;
		// Set the HeV vector
		scref.setXeVector(tempVector);
		// Give the cluster to the network.
		network.add(std::move(superCluster));

		// Keep the information of the group
		superGroupMap[superCount] = rawSuperCluster;

//		std::cout << superCount << " " << count << " "
//				<< rawSuperCluster->getName() << std::endl;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Reinitialize everything
		size = 0.0, radius = 0.0, energy = 0.0;
		count = 0;
		tempVector.clear();
		superCount++;
//		width = max(sectionWidth * (int) (superCount / 10), sectionWidth);
	}

<<<<<<< HEAD
	// Initialize variables for the loop
	NESuperCluster * newCluster;
	int nXe = 0;
	// Loop on all the reactants to update the pairs vector with super clusters
	auto reactants = network->getAll();
	for (int i = 0; i < reactants->size(); i++) {
		// Get the cluster
		cluster = (NECluster *) reactants->at(i);
		// Get their production and dissociation vectors
		auto react = cluster->reactingPairs;
		auto combi = cluster->combiningReactants;
		auto disso = cluster->dissociatingPairs;
		auto emi = cluster->emissionPairs;
=======
	// Tell each reactant to update the pairs vector with super clusters
	for (IReactant& currReactant : network.getAll()) {

		auto& cluster = static_cast<NECluster&>(currReactant);

		// Get their production and dissociation vectors
		// TODO can these be updated in place?
		auto react = cluster.reactingPairs;
		auto combi = cluster.combiningReactants;
		auto disso = cluster.dissociatingPairs;
		auto emi = cluster.emissionPairs;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Loop on its reacting pairs
		for (int l = 0; l < react.size(); l++) {
			// Test the first reactant
<<<<<<< HEAD
			if (react[l].first->getType() == xeType) {
				// Get its size
				nXe = react[l].first->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
=======
			if (react[l].first->getType() == ReactantType::Xe) {
				// Get its size
				auto nXe = react[l].first->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					auto newCluster = superGroupMap[clusterGroupMap[nXe]];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					react[l].first = newCluster;
					react[l].firstDistance = newCluster->getDistance(size);
				}
			}

			// Test the second reactant
<<<<<<< HEAD
			if (react[l].second->getType() == xeType) {
				// Get its size
				nXe = react[l].second->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
=======
			if (react[l].second->getType() == ReactantType::Xe) {
				// Get its size
				auto nXe = react[l].second->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					auto newCluster = superGroupMap[clusterGroupMap[nXe]];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					react[l].second = newCluster;
					react[l].secondDistance = newCluster->getDistance(nXe);
				}
			}
		}

<<<<<<< HEAD
		// Loop on its combining reactants
		for (int l = 0; l < combi.size(); l++) {
			// Test the combining reactant
			if (combi[l].combining->getType() == xeType) {
				// Get its size
				nXe = combi[l].combining->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
					combi[l].combining = newCluster;
					combi[l].distance = newCluster->getDistance(nXe);
				}
			}
		}
=======
		// Visit each combining reactant.
		std::for_each(combi.begin(), combi.end(),
				[this,&superGroupMap,&clusterGroupMap](NECluster::CombiningCluster& cc) {
					// Test the combining reactant
					NECluster& currCombining = cc.combining;
					if (currCombining.getType() == ReactantType::Xe) {
						// Get its size
						auto nXe = currCombining.getSize();
						// Test its size
						if (nXe >= xeMin) {
							// It has to be replaced by a super cluster
							auto newCluster = superGroupMap[clusterGroupMap[nXe]];
							cc.combining = *newCluster;
							cc.distance = newCluster->getDistance(nXe);
						}
					}
				});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Loop on its dissociating pairs
		for (int l = 0; l < disso.size(); l++) {
			// Test the first reactant
<<<<<<< HEAD
			if (disso[l].first->getType() == xeType) {
				// Get its size
				nXe = disso[l].first->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
=======
			if (disso[l].first->getType() == ReactantType::Xe) {
				// Get its size
				auto nXe = disso[l].first->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					auto newCluster = superGroupMap[clusterGroupMap[nXe]];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					disso[l].first = newCluster;
					disso[l].firstDistance = newCluster->getDistance(nXe);
				}
			}

			// Test the second reactant
<<<<<<< HEAD
			if (disso[l].second->getType() == xeType) {
				// Get its size
				nXe = disso[l].second->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
=======
			if (disso[l].second->getType() == ReactantType::Xe) {
				// Get its size
				auto nXe = disso[l].second->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					auto newCluster = superGroupMap[clusterGroupMap[nXe]];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					disso[l].second = newCluster;
					disso[l].secondDistance = newCluster->getDistance(nXe);
				}
			}
		}

		// Loop on its emission pairs
		for (int l = 0; l < emi.size(); l++) {
			// Test the first reactant
<<<<<<< HEAD
			if (emi[l].first->getType() == xeType) {
				// Get its size
				nXe = emi[l].first->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
=======
			if (emi[l].first->getType() == ReactantType::Xe) {
				// Get its size
				auto nXe = emi[l].first->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					auto newCluster = superGroupMap[clusterGroupMap[nXe]];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					emi[l].first = newCluster;
					emi[l].firstDistance = newCluster->getDistance(nXe);
				}
			}

			// Test the second reactant
<<<<<<< HEAD
			if (emi[l].second->getType() == xeType) {
				// Get its size
				nXe = emi[l].second->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					newCluster = superGroupMap[clusterGroupMap[nXe]];
=======
			if (emi[l].second->getType() == ReactantType::Xe) {
				// Get its size
				auto nXe = emi[l].second->getSize();
				// Test its size
				if (nXe >= xeMin) {
					// It has to be replaced by a super cluster
					auto newCluster = superGroupMap[clusterGroupMap[nXe]];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					emi[l].second = newCluster;
					emi[l].secondDistance = newCluster->getDistance(nXe);
				}
			}
		}

		// Set their production and dissociation vectors
<<<<<<< HEAD
		cluster->reactingPairs = react;
		cluster->combiningReactants = combi;
		cluster->dissociatingPairs = disso;
		cluster->emissionPairs = emi;
	}

	// Get the super cluster map
	auto superMap = network->getAll(NESuperType);
	// Set the reaction network for each super reactant
	for (auto currCluster : superMap) {
		currCluster->setReactionNetwork(network);
=======
		cluster.reactingPairs = react;
		cluster.combiningReactants = combi;
		cluster.dissociatingPairs = disso;
		cluster.emissionPairs = emi;
	}

	// Set the reaction network for each super reactant
	for (auto const& superMapItem : network.getAll(ReactantType::NESuper)) {
		auto& currCluster = static_cast<NESuperCluster&>(*(superMapItem.second));
		currCluster.updateFromNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Remove Xe clusters bigger than xeMin from the network
	// Loop on the Xe clusters
<<<<<<< HEAD
	std::vector<IReactant*> doomedReactants;
	for (auto currCluster : xeMap) {

		// Get the cluster's size.
		nXe = currCluster->getSize();
=======
	std::vector<std::reference_wrapper<IReactant> > doomedReactants;
	for (auto const& currMapItem : xeMap) {

		auto& currCluster = currMapItem.second;

		// Get the cluster's size.
		auto nXe = currCluster->getSize();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Check if the cluster is too large.
		if (nXe >= xeMin) {
			// The cluster is too large.  Add it to the ones we will remove.
<<<<<<< HEAD
			doomedReactants.push_back(currCluster);
		}
	}
	network->removeReactants(doomedReactants);

	// Recompute Ids and network size and redefine the connectivities
	network->reinitializeNetwork();
=======
			doomedReactants.push_back(*currCluster);
		}
	}
	network.removeReactants(doomedReactants);

	// Recompute Ids and network size
	network.reinitializeNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}
