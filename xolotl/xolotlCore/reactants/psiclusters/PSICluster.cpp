#include "PSICluster.h"
#include <xolotlPerf.h>
#include <Constants.h>
<<<<<<< HEAD
#include <iostream>
#include <limits>
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <MathUtils.h>

using namespace xolotlCore;

PSICluster::PSICluster() :
		Reactant() {
<<<<<<< HEAD
	// Set the size
	size = 1;
	// Zero out the formation energy
	formationEnergy = 0.0;
	// Zero out the diffusion factor and migration energy
	diffusionFactor = 0.0;
	diffusionCoefficient = 0.0;
	migrationEnergy = 0.0;
	// Set the reactant name appropriately
	name = "PSICluster";
	// No type name to set. Leave it empty.
	// Setup the composition map.
	compositionMap[heType] = 0;
	compositionMap[vType] = 0;
	compositionMap[iType] = 0;
	// Set the default reaction radius to 0. (Doesn't react.)
	reactionRadius = 0.0;
	// Set the initial index/id to -1
	thisNetworkIndex = -1;
=======
	// Set the reactant name appropriately
	name = "PSICluster";
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
PSICluster::PSICluster(const int clusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		Reactant(registry) {
	// Set the size
	size = (clusterSize > 0) ? clusterSize : 1;
	// Zero out the formation energy
	formationEnergy = 0.0;
	// Zero out the diffusion factor and migration energy
	diffusionFactor = 0.0;
	diffusionCoefficient = 0.0;
	migrationEnergy = 0.0;
	// Set the reactant name appropriately
	name = "PSICluster";
	// Setup the composition map.
	compositionMap[heType] = 0;
	compositionMap[vType] = 0;
	compositionMap[iType] = 0;
	// Set the default reaction radius to 0. (Doesn't react.)
	reactionRadius = 0.0;
	// Set the initial index/id to -1
	thisNetworkIndex = -1;
=======
PSICluster::PSICluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		Reactant(registry) {
	// Set the reactant name appropriately
	name = "PSICluster";
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
// The copy constructor with a huge initialization list!
PSICluster::PSICluster(const PSICluster &other) :
		Reactant(other),
		size(other.size),
		diffusionFactor(other.diffusionFactor),
		thisNetworkIndex(other.thisNetworkIndex),
		formationEnergy(other.formationEnergy),
		migrationEnergy(other.migrationEnergy),
		reactionRadius(other.reactionRadius),
		reactingPairs(other.reactingPairs),
		combiningReactants(other.combiningReactants),
		dissociatingPairs(other.dissociatingPairs),
		emissionPairs(other.emissionPairs),
		reactionConnectivitySet(other.reactionConnectivitySet),
		dissociationConnectivitySet(other.dissociationConnectivitySet) {
=======
// The copy constructor
PSICluster::PSICluster(PSICluster &other) :
		Reactant(other), reactingPairs(other.reactingPairs), combiningReactants(
				other.combiningReactants), dissociatingPairs(
				other.dissociatingPairs), emissionPairs(other.emissionPairs) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Recompute all of the temperature-dependent quantities
	setTemperature(other.getTemperature());

	return;
}

<<<<<<< HEAD
std::shared_ptr<Reactant> PSICluster::clone() {
	std::shared_ptr<Reactant> reactant(new PSICluster(*this));

	return reactant;
}

void PSICluster::createReactionConnectivity() {
	// Connect this cluster to itself since any reaction will affect it
	setReactionConnectivity(id);

	// This cluster is always X_a

	// Initial declarations
	int firstSize = 0, secondSize = 0;

	// Single species clustering producing this cluster
	// X_(a-i) + X_i --> X_a
	for (firstSize = 1; firstSize <= (int) size / 2; firstSize++) {
		// Set the size of the second reactant
		secondSize = size - firstSize;
		// Get the first and second reactants for the reaction
		auto firstReactant = (PSICluster *) network->get(typeName, firstSize);
		auto secondReactant = (PSICluster *) network->get(typeName, secondSize);
		// Create a ReactingPair with the two reactants
		if (firstReactant && secondReactant) {
			// The reaction constant will be computed later, it is set to 0.0 for now
			ClusterPair pair(firstReactant, secondReactant, 0.0);
			// Add the pair to the list
			reactingPairs.push_back(pair);
			// Setup the connectivity array
			setReactionConnectivity(firstReactant->id);
			setReactionConnectivity(secondReactant->id);
		}
	}

	// Single species clustering
	// X_a + X_b --> X_(a+b)
	auto reactants = network->getAll(typeName);
	// combineClusters handles everything for this type of reaction
	PSICluster::combineClusters(reactants, typeName);
=======
void PSICluster::createProduction(
		std::shared_ptr<ProductionReaction> reaction) {
	// Create a cluster pair from the given reaction
	ClusterPair pair((PSICluster *) reaction->first,
			(PSICluster *) reaction->second);
	// Add the pair to the list
	reactingPairs.push_back(pair);
	// Setup the connectivity array
	setReactionConnectivity(reaction->first->getId());
	setReactionConnectivity(reaction->second->getId());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PSICluster::createDissociationConnectivity() {
	// This cluster is always X_a

	// Single species dissociation
	// X_a --> X_(a-1) + X
	auto smallerReactant = (PSICluster *) network->get(typeName, size - 1);
	auto singleCluster = (PSICluster *) network->get(typeName, 1);
	emitClusters(singleCluster, smallerReactant);

	// Single species dissociation producing this cluster
	// X_(a+1) --> X_a + X
	auto biggerReactant = (PSICluster *) network->get(typeName, size + 1);
	dissociateCluster(biggerReactant, singleCluster);

	// Specific case for the single size cluster
	// for a = 1
	if (size == 1) {
		// all the cluster of the same type dissociate into it
		auto allSameTypeReactants = network->getAll(typeName);
		for (int i = 0; i < allSameTypeReactants.size(); i++) {
			auto cluster = (PSICluster *) allSameTypeReactants[i];
			// X_1 cannot dissociate and X_2 --> X + X was already
			// counted in the previous step
			if (cluster->size < 3)
				continue;
			// X_b is the dissociating one, X_(b-a) is the one
			// that is also emitted during the dissociation
			smallerReactant = (PSICluster *) network->get(typeName,
					cluster->size - 1);
			dissociateCluster(cluster, smallerReactant);
		}
	}
=======
void PSICluster::createCombination(
		std::shared_ptr<ProductionReaction> reaction) {
	setReactionConnectivity(id);
	// Look for the other cluster
	IReactant * secondCluster;
	if (reaction->first->getId() == id)
		secondCluster = reaction->second;
	else
		secondCluster = reaction->first;

	// Creates the combining cluster
	CombiningCluster combCluster((PSICluster *) secondCluster);
	// Push the product into the list of clusters that combine with this one
	combiningReactants.push_back(combCluster);

	// Setup the connectivity array
	setReactionConnectivity(id);
	setReactionConnectivity(secondCluster->getId());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
double PSICluster::calculateReactionRateConstant(
		const PSICluster & firstReactant, const PSICluster & secondReactant) const {
	// Get the reaction radii
	double r_first = firstReactant.reactionRadius;
	double r_second = secondReactant.reactionRadius;

	// Get the diffusion coefficients
	double firstDiffusion = firstReactant.diffusionCoefficient;
	double secondDiffusion = secondReactant.diffusionCoefficient;

	// Calculate and return
	double k_plus = 4.0 * xolotlCore::pi * (r_first + r_second)
					* (firstDiffusion + secondDiffusion);
	return k_plus;
} 

double PSICluster::calculateDissociationConstant(
		const PSICluster & dissociatingCluster,
		const PSICluster & singleCluster, const PSICluster & secondCluster) const {
	// The atomic volume is computed by considering the BCC structure of the
	// tungsten. In a given lattice cell in tungsten there are tungsten atoms
	// at each corner and a tungsten atom in the center. The tungsten atoms at
	// the corners are shared across a total of eight cells. The fraction of
	// the volume of the lattice cell that is filled with tungsten atoms is the
	// atomic volume and is a_0^3/(8*1/8 + 1) = 0.5*a_0^3.
	double atomicVolume = 0.5 * xolotlCore::latticeConstant
			* xolotlCore::latticeConstant * xolotlCore::latticeConstant;

	// Calculate the Reaction Rate Constant
	double kPlus = calculateReactionRateConstant(singleCluster, secondCluster);

	// Calculate and return
	double bindingEnergy = computeBindingEnergy(dissociatingCluster, singleCluster,
			secondCluster);
	double k_minus_exp = exp(
			-1.0 * bindingEnergy / (xolotlCore::kBoltzmann * temperature));
	double k_minus = (1.0 / atomicVolume) * kPlus * k_minus_exp;

	return k_minus;
}

double PSICluster::computeBindingEnergy(const PSICluster & dissociatingCluster,
		const PSICluster & singleCluster,
		const PSICluster & secondCluster) const {
	// for the dissociation A --> B + C we need A binding energy
	// E_b(A) = E_f(B) + E_f(C) - E_f(A) where E_f is the formation energy
	double bindingEnergy = singleCluster.formationEnergy
			+ secondCluster.formationEnergy
			- dissociatingCluster.formationEnergy;
	return bindingEnergy;
}

void PSICluster::dissociateCluster(PSICluster * dissociatingCluster,
		PSICluster * emittedCluster) {
	// Test if the dissociatingCluster and the emittedCluster exist
	if (dissociatingCluster && emittedCluster) {
		// Create the pair of them where it is important that the
		// dissociating cluster is the first one
		// The dissociating constant will be computed later, it is set to 0.0 for now
		ClusterPair pair(dissociatingCluster, emittedCluster, 0.0);
		// Add the pair to the dissociating pair vector
		// The connectivity is handled in emitCluster
		dissociatingPairs.push_back(pair);

		// Take care of the connectivity
		setDissociationConnectivity(dissociatingCluster->id);
	}
=======
void PSICluster::createDissociation(
		std::shared_ptr<DissociationReaction> reaction) {
	// Look for the other cluster
	IReactant * emittedCluster;
	if (reaction->first->getId() == id)
		emittedCluster = reaction->second;
	else
		emittedCluster = reaction->first;

	// Create the pair of them where it is important that the
	// dissociating cluster is the first one
	ClusterPair pair((PSICluster *) reaction->dissociating,
			(PSICluster *) emittedCluster);
	// Add the pair to the dissociating pair vector
	dissociatingPairs.push_back(pair);

	// Setup the connectivity array
	setDissociationConnectivity(reaction->dissociating->getId());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PSICluster::emitClusters(PSICluster * firstEmittedCluster,
		PSICluster * secondEmittedCluster) {
	// Test if the emitted clusters exist
	if (firstEmittedCluster && secondEmittedCluster) {
		// Connect this cluster to itself since any reaction will affect it
		setDissociationConnectivity(id);

		// Add the pair of emitted clusters to the vector of emissionPairs
		// The first cluster is the size one one
		// The dissociating constant will be computed later, it is set to 0.0 for now
		ClusterPair pair(firstEmittedCluster, secondEmittedCluster, 0.0);
		emissionPairs.push_back(pair);
	}
=======
void PSICluster::createEmission(
		std::shared_ptr<DissociationReaction> reaction) {
	// Create the pair of emitted clusters
	ClusterPair pair((PSICluster *) reaction->first,
			(PSICluster *) reaction->second);
	// Add the pair to the emission pair vector
	emissionPairs.push_back(pair);

	// Setup the connectivity array to itself
	setReactionConnectivity(id);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PSICluster::combineClusters(std::vector<Reactant *> & reactants,
		const std::string& productName) {
	// Initial declarations
	std::map<std::string, int> myComposition = getComposition(),
			secondComposition;
	int numHe, numV, numI, secondNumHe, secondNumV, secondNumI, productSize;
	std::vector<int> compositionSizes { 0, 0, 0 };
	PSICluster *productCluster, *secondCluster;
	// Setup the composition variables for this cluster
	numHe = myComposition[heType];
	numV = myComposition[vType];
	numI = myComposition[iType];

	int reactantVecSize = reactants.size();
	for (int i = 0; i < reactantVecSize; i++) {
		// Get the second reactant, its composition and its index
		secondCluster = (PSICluster *) reactants[i];
		secondComposition = secondCluster->getComposition();
		secondNumHe = secondComposition[heType];
		secondNumV = secondComposition[vType];
		secondNumI = secondComposition[iType];
		// Compute the product size
		productSize = size + secondCluster->size;
		// Get and handle product for compounds
		if (productName == heVType || productName == heIType) {
			// Modify the composition vector
			compositionSizes[0] = numHe + secondNumHe;
			compositionSizes[1] = numV + secondNumV;
			compositionSizes[2] = numI + secondNumI;
			// Get the product
			productCluster = (PSICluster *) network->getCompound(productName,
					compositionSizes);
		} else {
			// Just get the product if it is a single-species
			productCluster = (PSICluster *) network->get(productName,
					productSize);
		}

		// React if the product exists in the network
		if (productCluster) {
			// Setup the connectivity array for the second reactant
			setReactionConnectivity(secondCluster->id);
			// Creates the combining cluster
			// The reaction constant will be computed later and is set to 0.0 for now
			CombiningCluster combCluster(secondCluster, 0.0);
			// Push the product into the list of clusters that combine with this one
			combiningReactants.push_back(combCluster);
		}
	}

	return;
}

void PSICluster::replaceInCompound(std::vector<Reactant *> & reactants,
		const std::string& oldComponentName, const std::string& newComponentName) {
	// Local Declarations
	std::map<std::string, int> secondReactantComp, productReactantComp;
	int numReactants = reactants.size();
	std::vector<int> productCompositionVector { 0, 0, 0 };
	PSICluster *secondReactant, *productReactant;

	// Loop over all of the extra reactants in this reaction and handle the replacement
	for (int i = 0; i < numReactants; i++) {
		// Get the second reactant and its composition
		secondReactant = (PSICluster *) reactants[i];
		secondReactantComp = secondReactant->getComposition();
		// Create the composition vector
		productReactantComp = secondReactantComp;
		// Updated the modified components
		productReactantComp[oldComponentName] =
				secondReactantComp[oldComponentName] - size;
		// Create the composition vector -- FIXME! This should be general!
		productCompositionVector = {productReactantComp[heType],
				productReactantComp[vType],
				productReactantComp[iType] };
		// Get the product of the same type as the second reactant
		productReactant = (PSICluster *) network->getCompound(secondReactant->typeName,
				productCompositionVector);
		// If the product exists, mark the proper reaction arrays and add it to the list
		if (productReactant) {
			// Setup the connectivity array for the second reactant
			setReactionConnectivity(secondReactant->id);
			// Creates the combining cluster
			// The reaction constant will be computed later and is set to 0.0 for now
			CombiningCluster combCluster(secondReactant, 0.0);
			// Push the product onto the list of clusters that combine with this one
			combiningReactants.push_back(combCluster);
		}
	}

	return;
}

void PSICluster::fillVWithI(const std::string& secondClusterName,
		std::vector<Reactant *> & reactants) {
	// Local Declarations
	std::string productClusterName;
	int firstClusterSize = 0, secondClusterSize = 0, productClusterSize = 0,
			reactantVecSize = 0;
	PSICluster *secondCluster, *productCluster;

	// Get the number of V or I in this cluster (the "first")
	firstClusterSize = size;
	// Look at all of the second clusters, either V or I, and determine
	// if a connection exists.
	reactantVecSize = reactants.size();
	for (int i = 0; i < reactantVecSize; i++) {
		// Get the second cluster its size
		secondCluster = (PSICluster *) reactants[i];
		secondClusterSize = (secondCluster->size);
		// The only way this reaction is allowed is if the sizes are not equal.
		if (firstClusterSize != secondClusterSize) {
			// We have to switch on cluster type to make sure that the annihilation
			// is computed correctly.
			if (typeName == vType) {
				// Compute the product size and set the product name for the case
				// where I is the second cluster
				if (secondClusterSize > firstClusterSize) {
					productClusterSize = secondClusterSize - firstClusterSize;
					productClusterName = iType;
				} else if (secondClusterSize < firstClusterSize) {
					productClusterSize = firstClusterSize - secondClusterSize;
					productClusterName = vType;
				}
			} else if (typeName == iType) {
				// Compute the product size and set the product name for the case
				// where V is the second cluster
				if (firstClusterSize > secondClusterSize) {
					productClusterSize = firstClusterSize - secondClusterSize;
					productClusterName = iType;
				} else if (firstClusterSize < secondClusterSize) {
					productClusterSize = secondClusterSize - firstClusterSize;
					productClusterName = vType;
				}
			}
			// Get the product
			productCluster = (PSICluster *) network->get(
					productClusterName, productClusterSize);
			// Only deal with this reaction if the product exists. Otherwise the
			// whole reaction is forbidden.
			if (productCluster) {
				// Setup the connectivity array to handle the second reactant
				setReactionConnectivity(secondCluster->id);
				// Creates the combining cluster
				// The reaction constant will be computed later and is set to 0.0 for now
				CombiningCluster combCluster(secondCluster, 0.0);
				// Push the second cluster onto the list of clusters that combine
				// with this one
				combiningReactants.push_back(combCluster);
			}
		}
	}

	return;
}

void PSICluster::printReaction(const PSICluster & firstReactant,
		const PSICluster & secondReactant,
		const PSICluster & productReactant) const {
	auto firstComp = firstReactant.getComposition();
	auto secondComp = secondReactant.getComposition();
	auto productComp = productReactant.getComposition();

	std::cout << firstReactant.getName() << "(" << firstComp[heType] << ", "
			<< firstComp[vType] << ", " << firstComp[iType] << ") + "
			<< secondReactant.getName() << "(" << secondComp[heType] << ", "
			<< secondComp[vType] << ", " << secondComp[iType] << ") -> "
			<< productReactant.getName() << "(" << productComp[heType] << ", "
			<< productComp[vType] << ", " << productComp[iType] << ")"
			<< std::endl;

	return;
}

void PSICluster::printDissociation(const PSICluster & firstReactant,
		const PSICluster & secondReactant,
		const PSICluster & productReactant) const {
	auto firstComp = firstReactant.getComposition();
	auto secondComp = secondReactant.getComposition();
	auto productComp = productReactant.getComposition();

	std::cout << firstReactant.getName() << "(" << firstComp[heType] << ", "
			<< firstComp[vType] << ", " << firstComp[iType] << ") -> "
			<< secondReactant.getName() << "(" << secondComp[heType] << ", "
			<< secondComp[vType] << ", " << secondComp[iType] << ") + "
			<< productReactant.getName() << "(" << productComp[heType] << ", "
			<< productComp[vType] << ", " << productComp[iType] << ")"
			<< std::endl;
=======
void PSICluster::optimizeReactions() {
	// Loop on the pairs to add reactions to the network
	for (auto it = reactingPairs.begin(); it != reactingPairs.end(); it++) {
		// Create the corresponding production reaction
		auto newReaction = std::make_shared<ProductionReaction>((*it).first,
				(*it).second);
		// Add it to the network
		newReaction = network->addProductionReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;

		// Loop on all the reactions to see if the same reaction appears again
		for (auto itBis = it; itBis != reactingPairs.end();) {
			if (itBis == it) {
				itBis++;
				continue;
			}
			// Check if it is the same reaction
			if ((*it).first == (*itBis).first
					&& (*it).second == (*itBis).second) {
				// Increase the multiplicity of the reaction
				((*it).multiplicity)++;

				// Remove the reaction from the vector
				itBis = reactingPairs.erase(itBis);
			}
			else itBis++;
		}
	}

	for (auto it = combiningReactants.begin(); it != combiningReactants.end();
			it++) {
		// Create the corresponding production reaction
		auto newReaction = std::make_shared<ProductionReaction>((*it).combining,
				this);
		// Add it to the network
		newReaction = network->addProductionReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;

		// Loop on all the reactions to see if the same reaction appears again
		for (auto itBis = it; itBis != combiningReactants.end();) {
			if (itBis == it) {
				itBis++;
				continue;
			}
			// Check if it is the same reaction
			if ((*it).combining == (*itBis).combining) {
				// Increase the multiplicity of the reaction
				((*it).multiplicity)++;

				// Remove the reaction from the vector
				itBis = combiningReactants.erase(itBis);
			}
			else itBis++;
		}
	}

	for (auto it = dissociatingPairs.begin(); it != dissociatingPairs.end();
			it++) {
		// Create the corresponding dissociation reaction
		auto newReaction = std::make_shared<DissociationReaction>((*it).first,
				(*it).second, this);
		// Add it to the network
		newReaction = network->addDissociationReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;

		// Loop on all the reactions to see if the same reaction appears again
		for (auto itBis = it; itBis != dissociatingPairs.end();) {
			if (itBis == it) {
				itBis++;
				continue;
			}
			// Check if it is the same reaction
			if ((*it).first == (*itBis).first
					&& (*it).second == (*itBis).second) {
				// Increase the multiplicity of the reaction
				((*it).multiplicity)++;

				// Remove the reaction from the vector
				itBis = dissociatingPairs.erase(itBis);
			}
			else itBis++;
		}
	}

	for (auto it = emissionPairs.begin(); it != emissionPairs.end(); it++) {
		// Create the corresponding dissociation reaction
		auto newReaction = std::make_shared<DissociationReaction>(this,
				(*it).first, (*it).second);
		// Add it to the network
		newReaction = network->addDissociationReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;

		// Loop on all the reactions to see if the same reaction appears again
		for (auto itBis = it; itBis != emissionPairs.end();) {
			if (itBis == it) {
				itBis++;
				continue;
			}
			// Check if it is the same reaction
			if ((*it).first == (*itBis).first
					&& (*it).second == (*itBis).second) {
				// Increase the multiplicity of the reaction
				((*it).multiplicity)++;

				// Remove the reaction from the vector
				itBis = emissionPairs.erase(itBis);
			}
			else itBis++;
		}
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

static std::vector<int> getFullConnectivityVector(std::set<int> connectivitySet,
		int size) {
	// Create a vector of zeroes with size equal to the network size
	std::vector<int> connectivity(size);

	// Set the value of the connectivity array to one for each element that is
	// in the set.
	for (auto it = connectivitySet.begin(); it != connectivitySet.end(); ++it) {
		connectivity[*it - 1] = 1;
	}

	return connectivity;
}

<<<<<<< HEAD
void PSICluster::setReactionConnectivity(int clusterId) {
	// Add the cluster to the set.
	reactionConnectivitySet.insert(clusterId);

	return;
}

std::vector<int> PSICluster::getReactionConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(reactionConnectivitySet, network->size());
}

void PSICluster::setDissociationConnectivity(int clusterId) {
	// Add the cluster to the set.
	dissociationConnectivitySet.insert(clusterId);

	return;
=======
std::vector<int> PSICluster::getReactionConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(reactionConnectivitySet, network->getDOF());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

std::vector<int> PSICluster::getDissociationConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(dissociationConnectivitySet,
<<<<<<< HEAD
			network->size());
}

int PSICluster::getSize() const {
	// Return this cluster's size
	return size;
}

void PSICluster::setReactionNetwork(
		const std::shared_ptr<ReactionNetwork> reactionNetwork) {
	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);

	// Extract properties from the network
	auto properties = network->getProperties();

	// Get the enabled reaction type flags
	bool reactionsEnabled = (properties["reactionsEnabled"] == "true");
	bool dissociationsEnabled = (properties["dissociationsEnabled"] == "true");

=======
			network->getDOF());
}

void PSICluster::resetConnectivities() {
	// Shrink the arrays to save some space. (About 10% or so.)
	reactingPairs.shrink_to_fit();
	combiningReactants.shrink_to_fit();
	dissociatingPairs.shrink_to_fit();
	emissionPairs.shrink_to_fit();

	// Clear both sets
	reactionConnectivitySet.clear();
	dissociationConnectivitySet.clear();

	// Connect this cluster to itself since any reaction will affect it
	setReactionConnectivity(id);
	setDissociationConnectivity(id);
	setReactionConnectivity(heMomId);
	setDissociationConnectivity(heMomId);
	setReactionConnectivity(vMomId);
	setDissociationConnectivity(vMomId);

	// Loop on the effective reacting pairs
	for (auto it = reactingPairs.begin(); it != reactingPairs.end(); ++it) {
		// The cluster is connecting to both clusters in the pair
		setReactionConnectivity((*it).first->id);
		setReactionConnectivity((*it).second->id);
		setReactionConnectivity((*it).first->heMomId);
		setReactionConnectivity((*it).second->heMomId);
		setReactionConnectivity((*it).first->vMomId);
		setReactionConnectivity((*it).second->vMomId);
	}

	// Loop on the effective combining reactants
	for (auto it = combiningReactants.begin(); it != combiningReactants.end();
			++it) {
		// The cluster is connecting to the combining cluster
		setReactionConnectivity((*it).combining->id);
		setReactionConnectivity((*it).combining->heMomId);
		setReactionConnectivity((*it).combining->vMomId);
	}

	// Loop on the effective dissociating pairs
	for (auto it = dissociatingPairs.begin(); it != dissociatingPairs.end();
			++it) {
		// The cluster is connecting to the dissociating cluster which
		// is the first one by definition
		setDissociationConnectivity((*it).first->id);
		setDissociationConnectivity((*it).first->heMomId);
		setDissociationConnectivity((*it).first->vMomId);
	}

	// Don't loop on the effective emission pairs because
	// this cluster is not connected to them

	return;
}

void PSICluster::setReactionNetwork(
		const std::shared_ptr<IReactionNetwork> reactionNetwork) {
	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

<<<<<<< HEAD
	// Get the index/id of this cluster in the reaction network.
	thisNetworkIndex = id - 1;

	// ----- Handle the connectivity for PSIClusters -----

	// Generate the reactant and dissociation connectivity arrays.
	// This only must be done once since the arrays are stored as
	// member attributes. Only perform these tasks if the reaction
	// types are enabled.
	if (reactionsEnabled) {
		createReactionConnectivity();
	}
	if (dissociationsEnabled) {
		createDissociationConnectivity();
	}

	// Shrink the arrays to save some space. (About 10% or so.)
	reactingPairs.shrink_to_fit();
	combiningReactants.shrink_to_fit();
	dissociatingPairs.shrink_to_fit();
	emissionPairs.shrink_to_fit();

	return;
}

double PSICluster::getTotalFlux() {
	// Initialize the fluxes
	double prodFlux = 0.0, combFlux = 0.0, dissFlux = 0.0, emissFlux = 0.0;

	// Get the fluxes
	prodFlux = getProductionFlux();
	dissFlux = getDissociationFlux();

	// Don't compute the combination and emission flux if the
	// concentration is 0.0 because they are proportional to it
	if (!xolotlCore::equal(concentration, 0.0)) {
		combFlux = getCombinationFlux();
		emissFlux = getEmissionFlux();
	}
=======
	return;
}

double PSICluster::getHeMomentum() const {
	return 0.0;
}

double PSICluster::getVMomentum() const {
	return 0.0;
}

double PSICluster::getTotalFlux() {
	// Get the fluxes
	double prodFlux = getProductionFlux();
	double dissFlux = getDissociationFlux();
	double combFlux = getCombinationFlux();
	double emissFlux = getEmissionFlux();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return prodFlux - combFlux + dissFlux - emissFlux;
}

double PSICluster::getDissociationFlux() const {
	// Initial declarations
	int nPairs = 0;
	double flux = 0.0;
<<<<<<< HEAD
	PSICluster *dissociatingCluster;

	// Set the total number of reactants that dissociate to form this one
	nPairs = effDissociatingPairs.size();
	// Loop over all dissociating clusters that form this cluster
	for (int j = 0; j < nPairs; j++) {
		// Get the dissociating cluster
		dissociatingCluster = effDissociatingPairs[j]->first;
		// Calculate the Dissociation flux
		flux += effDissociatingPairs[j]->kConstant
				* dissociatingCluster->concentration;
=======
	PSICluster *dissociatingCluster = nullptr;

	// Set the total number of reactants that dissociate to form this one
	nPairs = dissociatingPairs.size();
	// Loop over all dissociating clusters that form this cluster
	for (int j = 0; j < nPairs; j++) {
		// Get the dissociating cluster
		dissociatingCluster = dissociatingPairs[j].first;
		// Calculate the Dissociation flux
		flux += dissociatingPairs[j].reaction->kConstant
				* (double) dissociatingPairs[j].multiplicity
				* dissociatingCluster->getConcentration(
						dissociatingPairs[j].firstHeDistance,
						dissociatingPairs[j].firstVDistance);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Return the flux
	return flux;
}

double PSICluster::getEmissionFlux() const {
	// Initial declarations
	int nPairs = 0;
	double flux = 0.0;

	// Set the total number of emission pairs
<<<<<<< HEAD
	nPairs = effEmissionPairs.size();
	// Loop over all the pairs
	for (int i = 0; i < nPairs; i++) {
		// Update the flux
		flux += effEmissionPairs[i]->kConstant;
=======
	nPairs = emissionPairs.size();
	// Loop over all the pairs
	for (int i = 0; i < nPairs; i++) {
		// Update the flux
		flux += emissionPairs[i].reaction->kConstant
				* (double) emissionPairs[i].multiplicity;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return flux * concentration;
}

double PSICluster::getProductionFlux() const {
	// Local declarations
	double flux = 0.0;
	int nPairs = 0;
<<<<<<< HEAD
	PSICluster *firstReactant, *secondReactant;
	
	// Set the total number of reacting pairs
	nPairs = effReactingPairs.size();
	// Loop over all the reacting pairs
	for (int i = 0; i < nPairs; i++) {
		// Get the two reacting clusters
		firstReactant = effReactingPairs[i]->first;
		secondReactant = effReactingPairs[i]->second;
		// Update the flux
		flux += effReactingPairs[i]->kConstant * firstReactant->concentration
				* secondReactant->concentration;
=======
	PSICluster *firstReactant = nullptr, *secondReactant = nullptr;

	// Set the total number of reacting pairs
	nPairs = reactingPairs.size();
	// Loop over all the reacting pairs
	for (int i = 0; i < nPairs; i++) {
		// Get the two reacting clusters
		firstReactant = reactingPairs[i].first;
		secondReactant = reactingPairs[i].second;
		// Update the flux
		flux += reactingPairs[i].reaction->kConstant
				* (double) reactingPairs[i].multiplicity
				* firstReactant->getConcentration(
						reactingPairs[i].firstHeDistance,
						reactingPairs[i].firstVDistance)
				* secondReactant->getConcentration(
						reactingPairs[i].secondHeDistance,
						reactingPairs[i].secondVDistance);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Return the production flux
	return flux;
}

double PSICluster::getCombinationFlux() const {
	// Local declarations
	double flux = 0.0;
	int nReactants = 0;
<<<<<<< HEAD
	PSICluster *combiningCluster;

	// Set the total number of reactants that combine to form this one
	nReactants = effCombiningReactants.size();
	// Loop over all possible clusters
	for (int j = 0; j < nReactants; j++) {
		// Get the cluster that combines with this one
		combiningCluster = effCombiningReactants[j]->combining;
		// Calculate Second term of production flux
		flux += effCombiningReactants[j]->kConstant
				* combiningCluster->concentration;
=======
	PSICluster *combiningCluster = nullptr;

	// Set the total number of reactants that combine to form this one
	nReactants = combiningReactants.size();
	// Loop over all possible clusters
	for (int j = 0; j < nReactants; j++) {
		// Get the cluster that combines with this one
		combiningCluster = combiningReactants[j].combining;
		// Calculate the combination flux
		flux += combiningReactants[j].reaction->kConstant
				* (double) combiningReactants[j].multiplicity
				* combiningCluster->getConcentration(
						combiningReactants[j].heDistance,
						combiningReactants[j].vDistance);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return flux * concentration;
}

std::vector<double> PSICluster::getPartialDerivatives() const {
	// Local Declarations
<<<<<<< HEAD
	std::vector<double> partials(network->size(), 0.0);
=======
	std::vector<double> partials(network->getDOF(), 0.0);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials);
	getCombinationPartialDerivatives(partials);
	getDissociationPartialDerivatives(partials);
	getEmissionPartialDerivatives(partials);

	return partials;
}

void PSICluster::getPartialDerivatives(std::vector<double> & partials) const {
	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials);
	getCombinationPartialDerivatives(partials);
	getDissociationPartialDerivatives(partials);
	getEmissionPartialDerivatives(partials);

	return;
}

<<<<<<< HEAD
void PSICluster::getProductionPartialDerivatives(std::vector<double> & partials) const {
	// Initial declarations
	int numReactants = 0, index = 0;
=======
void PSICluster::getProductionPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numReactants = 0, index = 0;
	double value = 0.0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Production
	// A + B --> D, D being this cluster
	// The flux for D is
	// F(C_D) = k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_D)/dC_A = k+_(A,B)*C_B
	// dF(C_D)/dC_B = k+_(A,B)*C_A
<<<<<<< HEAD
	numReactants = effReactingPairs.size();
	for (int i = 0; i < numReactants; i++) {
		// Compute the contribution from the first part of the reacting pair
		index = effReactingPairs[i]->first->id - 1;
		partials[index] += effReactingPairs[i]->kConstant
				* effReactingPairs[i]->second->concentration;
		// Compute the contribution from the second part of the reacting pair
		index = effReactingPairs[i]->second->id - 1;
		partials[index] += effReactingPairs[i]->kConstant
				* effReactingPairs[i]->first->concentration;
=======
	numReactants = reactingPairs.size();
	for (int i = 0; i < numReactants; i++) {
		// Compute the contribution from the first part of the reacting pair
		value = reactingPairs[i].reaction->kConstant
				* (double) reactingPairs[i].multiplicity
				* reactingPairs[i].second->getConcentration(
						reactingPairs[i].secondHeDistance,
						reactingPairs[i].secondVDistance);
		index = reactingPairs[i].first->id - 1;
		partials[index] += value;
		index = reactingPairs[i].first->heMomId - 1;
		partials[index] += value * reactingPairs[i].firstHeDistance;
		index = reactingPairs[i].first->vMomId - 1;
		partials[index] += value * reactingPairs[i].firstVDistance;
		// Compute the contribution from the second part of the reacting pair
		value = reactingPairs[i].reaction->kConstant
				* (double) reactingPairs[i].multiplicity
				* reactingPairs[i].first->getConcentration(
						reactingPairs[i].firstHeDistance,
						reactingPairs[i].firstVDistance);
		index = reactingPairs[i].second->id - 1;
		partials[index] += value;
		index = reactingPairs[i].second->heMomId - 1;
		partials[index] += value * reactingPairs[i].secondHeDistance;
		index = reactingPairs[i].second->vMomId - 1;
		partials[index] += value * reactingPairs[i].secondVDistance;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

void PSICluster::getCombinationPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numReactants = 0, otherIndex = 0;
<<<<<<< HEAD
	PSICluster *cluster;
=======
	PSICluster *cluster = nullptr;
	double value = 0.0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Combination
	// A + B --> D, A being this cluster
	// The flux for A is outgoing
	// F(C_A) = - k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k+_(A,B)*C_B
	// dF(C_A)/dC_B = - k+_(A,B)*C_A
<<<<<<< HEAD
	numReactants = effCombiningReactants.size();
	for (int i = 0; i < numReactants; i++) {
		cluster = (PSICluster *) effCombiningReactants[i]->combining;
		// Get the index of cluster
		otherIndex = cluster->id - 1;
		// Remember that the flux due to combinations is OUTGOING (-=)!
		// Compute the contribution from this cluster
		partials[thisNetworkIndex] -= effCombiningReactants[i]->kConstant
				* cluster->concentration;
		// Compute the contribution from the combining cluster
		partials[otherIndex] -= effCombiningReactants[i]->kConstant
				* concentration;
=======
	numReactants = combiningReactants.size();
	for (int i = 0; i < numReactants; i++) {
		cluster = (PSICluster *) combiningReactants[i].combining;
		// Remember that the flux due to combinations is OUTGOING (-=)!
		// Compute the contribution from this cluster
		partials[id - 1] -= combiningReactants[i].reaction->kConstant
				* (double) combiningReactants[i].multiplicity
				* cluster->getConcentration(combiningReactants[i].heDistance,
						combiningReactants[i].vDistance);
		// Compute the contribution from the combining cluster
		value = combiningReactants[i].reaction->kConstant
				* (double) combiningReactants[i].multiplicity * concentration;
		otherIndex = cluster->id - 1;
		partials[otherIndex] -= value;
		otherIndex = cluster->heMomId - 1;
		partials[otherIndex] -= value * combiningReactants[i].heDistance;
		otherIndex = cluster->vMomId - 1;
		partials[otherIndex] -= value * combiningReactants[i].vDistance;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

void PSICluster::getDissociationPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numPairs = 0, index = 0;
<<<<<<< HEAD
	PSICluster *cluster;
=======
	PSICluster *cluster = nullptr;
	double value = 0.0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Dissociation
	// A --> B + D, B being this cluster
	// The flux for B is
	// F(C_B) = k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_B)/dC_A = k-_(B,D)
<<<<<<< HEAD
	numPairs = effDissociatingPairs.size();
	for (int i = 0; i < numPairs; i++) {
		// Get the dissociating cluster
		cluster = effDissociatingPairs[i]->first;
		index = cluster->id - 1;
		partials[index] += effDissociatingPairs[i]->kConstant;
=======
	numPairs = dissociatingPairs.size();
	for (int i = 0; i < numPairs; i++) {
		// Get the dissociating cluster
		cluster = dissociatingPairs[i].first;
		value = dissociatingPairs[i].reaction->kConstant
				* (double) dissociatingPairs[i].multiplicity;
		index = cluster->id - 1;
		partials[index] += value;
		index = cluster->heMomId - 1;
		partials[index] += value * dissociatingPairs[i].firstHeDistance;
		index = cluster->vMomId - 1;
		partials[index] += value * dissociatingPairs[i].firstVDistance;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

<<<<<<< HEAD
void PSICluster::getEmissionPartialDerivatives(std::vector<double> & partials) const {
=======
void PSICluster::getEmissionPartialDerivatives(
		std::vector<double> & partials) const {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Initial declarations
	int numPairs = 0, index = 0;

	// Emission
	// A --> B + D, A being this cluster
	// The flux for A is
	// F(C_A) = - k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k-_(B,D)
<<<<<<< HEAD
	numPairs = effEmissionPairs.size();
=======
	numPairs = emissionPairs.size();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	for (int i = 0; i < numPairs; i++) {
		// Modify the partial derivative. Remember that the flux
		// due to emission is OUTGOING (-=)!
		index = id - 1;
<<<<<<< HEAD
		partials[index] -= effEmissionPairs[i]->kConstant;
=======
		partials[index] -= emissionPairs[i].reaction->kConstant
				* (double) emissionPairs[i].multiplicity;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

<<<<<<< HEAD
double PSICluster::getDiffusionFactor() const {
	// Return the diffusion factor
	return diffusionFactor;
}

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
void PSICluster::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

<<<<<<< HEAD
double PSICluster::getDiffusionCoefficient() const {
	return diffusionCoefficient;
}

double PSICluster::getFormationEnergy() const {
	return formationEnergy;
}

void PSICluster::setFormationEnergy(double energy) {
	// Set the formation energy
	formationEnergy = energy;
	return;
}

double PSICluster::getMigrationEnergy() const {
	// Return the migration energy
	return migrationEnergy;
}

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
void PSICluster::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

<<<<<<< HEAD
double PSICluster::getReactionRadius() const {
	return reactionRadius; // Computed by subclasses in constructors.
}

std::vector<int> PSICluster::getConnectivity() const {
	int connectivityLength = network->size();
=======
double PSICluster::getLeftSideRate() const {
	// Initialize the rate and the cluster pointer
	double totalRate = 0.0;
	PSICluster *cluster = nullptr;

	// Loop on the combining reactants
	for (int i = 0; i < combiningReactants.size(); i++) {
		cluster = (PSICluster *) combiningReactants[i].combining;
		// Add the rate to the total rate
		totalRate += combiningReactants[i].reaction->kConstant
				* (double) combiningReactants[i].multiplicity
				* cluster->concentration;
	}

	// Loop on the emission pairs
	for (int i = 0; i < emissionPairs.size(); i++) {
		// Add the rate to the total rate
		totalRate += emissionPairs[i].reaction->kConstant
				* (double) emissionPairs[i].multiplicity;
	}

	return totalRate;
}

std::vector<int> PSICluster::getConnectivity() const {
	int connectivityLength = network->getDOF();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);
	auto reactionConnVector = getReactionConnectivity();
	auto dissociationConnVector = getDissociationConnectivity();

	// The reaction and dissociation vectors must have a length equal to the
	// number of clusters
<<<<<<< HEAD
	if (reactionConnVector.size() != connectivityLength) {
		throw std::string("The reaction vector is an incorrect length");
	}
	if (dissociationConnVector.size() != connectivityLength) {
=======
	if (reactionConnVector.size() != (unsigned int) connectivityLength) {
		throw std::string("The reaction vector is an incorrect length");
	}
	if (dissociationConnVector.size() != (unsigned int) connectivityLength) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		throw std::string("The dissociation vector is an incorrect length");
	}

	// Merge the two vectors such that the final vector contains
	// a 1 at a position if either of the connectivity arrays
	// have a 1
	for (int i = 0; i < connectivityLength; i++) {
		// Consider each connectivity array only if its type is enabled
		connectivity[i] = reactionConnVector[i] || dissociationConnVector[i];
	}

	return connectivity;
}
<<<<<<< HEAD

void PSICluster::recomputeDiffusionCoefficient(double temp) {
	// Return zero if the diffusion factor is zero.
	if (xolotlCore::equal(diffusionFactor, 0.0)) {
		diffusionCoefficient = 0.0;
	} else {
		// Otherwise use the Arrhenius equation to compute the diffusion
		// coefficient
		double k_b = xolotlCore::kBoltzmann;
		double kernel = -1.0 * migrationEnergy / (k_b * temp);
		diffusionCoefficient = diffusionFactor * exp(kernel);
	}

	return;
}

void PSICluster::computeRateConstants() {
	// Initialize all the effective vectors
	effReactingPairs.clear();
	effCombiningReactants.clear();
	effDissociatingPairs.clear();
	effEmissionPairs.clear();

	// Local declarations
	PSICluster *firstReactant, *secondReactant, *combiningReactant,
		*dissociatingCluster, *otherEmittedCluster, *firstCluster,
		*secondCluster;
	double rate = 0.0;

	// Compute the reaction constant associated to the reacting pairs
	// Set the total number of reacting pairs
	int nPairs = reactingPairs.size();
	// Loop on them
	for (int i = 0; i < nPairs; i++) {
		// Get the reactants
		firstReactant = reactingPairs[i].first;
		secondReactant = reactingPairs[i].second;
		// Compute the reaction constant
		rate = calculateReactionRateConstant(*firstReactant,
				*secondReactant);
		// Set it in the pair
		reactingPairs[i].kConstant = rate;

		// Add the reacting pair to the effective vector
		// if the rate is not 0.0
		if (!xolotlCore::equal(rate, 0.0)) {
			effReactingPairs.push_back(&reactingPairs[i]);
		}
	}

	// Compute the reaction constant associated to the combining reactants
	// Set the total number of combining reactants
	int nReactants = combiningReactants.size();
	// Loop on them
	for (int i = 0; i < nReactants; i++) {
		// Get the reactants
		combiningReactant = combiningReactants[i].combining;
		// Compute the reaction constant
		rate = calculateReactionRateConstant(*this, *combiningReactant);
		// Set it in the combining cluster
		combiningReactants[i].kConstant = rate;

		// Add the combining reactant to the effective vector
		// if the rate is not 0.0
		if (!xolotlCore::equal(rate, 0.0)) {
			effCombiningReactants.push_back(&combiningReactants[i]);

			// Add itself to the list again to account for the correct rate
			if (id == combiningReactant->id)
				effCombiningReactants.push_back(&combiningReactants[i]);
		}
	}

	// Compute the dissociation constant associated to the dissociating clusters
	// Set the total number of dissociating clusters
	nPairs = dissociatingPairs.size();
	// Loop on them
	for (int i = 0; i < nPairs; i++) {
		dissociatingCluster = dissociatingPairs[i].first;
		// The second element of the pair is the cluster that is also
		// emitted by the dissociation
		otherEmittedCluster = dissociatingPairs[i].second;
		// Compute the dissociation constant
		// The order of the cluster is important here because of the binding
		// energy used in the computation. It is taken from the type of the first cluster
		// which must be the single one
		if (size == 1) {
			// "this" is the single size one
			rate = calculateDissociationConstant(*dissociatingCluster, *this,
					*otherEmittedCluster);
		} else {
			// otherEmittedCluster is the single size one
			rate = calculateDissociationConstant(*dissociatingCluster,
					*otherEmittedCluster, *this);

		}
		// Set it in the pair
		dissociatingPairs[i].kConstant = rate;

		// Add the dissociating pair to the effective vector
		// if the rate is not 0.0
		if (!xolotlCore::equal(rate, 0.0)) {
			effDissociatingPairs.push_back(&dissociatingPairs[i]);

			// Add itself to the list again to account for the correct rate
			if (id == otherEmittedCluster->id)
				effDissociatingPairs.push_back(&dissociatingPairs[i]);
		}
	}

	// Compute the dissociation constant associated to the emission of pairs of clusters
	// Set the total number of emission pairs
	nPairs = emissionPairs.size();
	// Loop on them
	for (int i = 0; i < nPairs; i++) {
		firstCluster = emissionPairs[i].first;
		secondCluster = emissionPairs[i].second;
		// Compute the dissociation rate
		rate = calculateDissociationConstant(*this, *firstCluster,
				*secondCluster);
		// Set it in the pair
		emissionPairs[i].kConstant = rate;

		// Add the emission pair to the effective vector
		// if the rate is not 0.0
		if (!xolotlCore::equal(rate, 0.0)) {
			effEmissionPairs.push_back(&emissionPairs[i]);
		}
	}

	// Shrink the arrays to save some space
	effReactingPairs.shrink_to_fit();
	effCombiningReactants.shrink_to_fit();
	effDissociatingPairs.shrink_to_fit();
	effEmissionPairs.shrink_to_fit();

	return;
}

void PSICluster::setTemperature(double temp) {
	// Set the temperature
	Reactant::setTemperature(temp);

	// Recompute the diffusion coefficient
	recomputeDiffusionCoefficient(temp);

	return;
}
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
