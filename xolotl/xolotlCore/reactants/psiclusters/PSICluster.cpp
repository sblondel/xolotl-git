#include "PSICluster.h"
<<<<<<< HEAD
#include <xolotlPerf.h>
#include <Constants.h>
#include <MathUtils.h>

using namespace xolotlCore;

PSICluster::PSICluster() :
		Reactant() {
	// Set the reactant name appropriately
	name = "PSICluster";

	return;
}

PSICluster::PSICluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		Reactant(registry) {
	// Set the reactant name appropriately
	name = "PSICluster";

	return;
}

// The copy constructor
PSICluster::PSICluster(PSICluster &other) :
		Reactant(other), reactingPairs(other.reactingPairs), combiningReactants(
				other.combiningReactants), dissociatingPairs(
				other.dissociatingPairs), emissionPairs(other.emissionPairs) {
	// Recompute all of the temperature-dependent quantities
	setTemperature(other.getTemperature());

	return;
}

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

	return;
}

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

	return;
}

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

	return;
}

void PSICluster::createEmission(
		std::shared_ptr<DissociationReaction> reaction) {
	// Create the pair of emitted clusters
	ClusterPair pair((PSICluster *) reaction->first,
			(PSICluster *) reaction->second);
	// Add the pair to the emission pair vector
	emissionPairs.push_back(pair);

	// Setup the connectivity array to itself
	setReactionConnectivity(id);
=======
#include "xolotlPerf/HandlerRegistryFactory.h"
#include <Constants.h>
#include <iostream>

using namespace xolotlCore;

// Create the static map of binding energies
std::unordered_map<std::string, int> PSICluster::bindingEnergyIndexMap;

PSICluster::PSICluster() :
		Reactant() {
	// Set the size
	size = 1;
	// Zero out the binding energies
	bindingEnergies.resize(4);
	bindingEnergies[0] = 0.0;
	bindingEnergies[1] = 0.0;
	bindingEnergies[2] = 0.0;
	bindingEnergies[3] = 0.0;
	// Zero out the diffusion factor and migration energy
	diffusionFactor = 0.0;
	migrationEnergy = 0.0;
	// Set the reactant name appropriately
	name = "PSICluster";
	// Setup the composition map.
	compositionMap["He"] = 0;
	compositionMap["V"] = 0;
	compositionMap["I"] = 0;
	// Set the default reaction radius to 0. (Doesn't react.)
	reactionRadius = 0.0;
	// Setup the binding energy index map
	bindingEnergyIndexMap = { {"He", 0},
		{	"V", 1}, {"I", 2}};

}

PSICluster::PSICluster(const int clusterSize,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		Reactant(registry) {

	// Set the size
	size = (clusterSize > 0) ? clusterSize : 1;
	// Zero out the binding energies
	bindingEnergies.resize(4);
	bindingEnergies[0] = 0.0;
	bindingEnergies[1] = 0.0;
	bindingEnergies[2] = 0.0;
	bindingEnergies[3] = 0.0;
	// Zero out the diffusion factor and migration energy
	diffusionFactor = 0.0;
	migrationEnergy = 0.0;
	// Set the reactant name appropriately
	name = "PSICluster";
	// Setup the composition map.
	compositionMap["He"] = 0;
	compositionMap["V"] = 0;
	compositionMap["I"] = 0;
	// Set the default reaction radius to 0. (Doesn't react.)
	reactionRadius = 0.0;

	// Set up an event counter to count the number of times getDissociationFlux is called
	getDissociationFluxCounter = handlerRegistry->getEventCounter(
			"PSICluster_getDissociationFlux_Counter");

}

// The copy constructor with a huge initialization list!
PSICluster::PSICluster(const PSICluster &other) :
		Reactant(other), size(other.size), diffusionFactor(
				other.diffusionFactor), thisSharedPtr(other.thisSharedPtr), thisNetworkIndex(
				other.thisNetworkIndex), bindingEnergies(other.bindingEnergies), migrationEnergy(
				other.migrationEnergy), reactionRadius(other.reactionRadius), reactingPairs(
				other.reactingPairs), combiningReactants(
				other.combiningReactants), dissociatingClusters(
				other.dissociatingClusters), reactionConnectivitySet(
				other.reactionConnectivitySet), dissociationConnectivitySet(
				other.dissociationConnectivitySet) {

	// Set up an event counter to count the number of times getDissociationFlux is called
	getDissociationFluxCounter = handlerRegistry->getEventCounter(
			"getDissociationFlux_Counter");

}

std::shared_ptr<Reactant> PSICluster::clone() {
	std::shared_ptr<Reactant> reactant(new PSICluster(*this));
	return reactant;
}

std::shared_ptr<PSICluster> PSICluster::getThisSharedPtrFromNetwork() const {
	return std::dynamic_pointer_cast<PSICluster>(network->get(name, size));
}

PSICluster::~PSICluster() {

	std::cout << "PSICluster: Called getDissociationFlux "
			<< getDissociationFluxCounter->getValue() << " times" << std::endl;

}

/**
 * This operation prints a forward reaction given the three reactants in
 * A + B -> C.
 * @param firstReactant - The first reactant in the reaction, A.
 * @param secondReactant - The second reactant in the reaction, B.
 * @param thirdReactant - The third reactant in the reaction, C.
 */
void PSICluster::printReaction(const Reactant & firstReactant,
		const Reactant & secondReactant,
		const Reactant & productReactant) const {

	auto firstComp = firstReactant.getComposition();
	auto secondComp = secondReactant.getComposition();
	auto productComp = productReactant.getComposition();

	std::cout << firstReactant.getName() << "(" << firstComp["He"] << ", "
			<< firstComp["V"] << ", " << firstComp["I"] << ") + "
			<< secondReactant.getName() << "(" << secondComp["He"] << ", "
			<< secondComp["V"] << ", " << secondComp["I"] << ") -> "
			<< productReactant.getName() << "(" << productComp["He"] << ", "
			<< productComp["V"] << ", " << productComp["I"] << ")" << std::endl;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	return;
}

<<<<<<< HEAD
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
	}

	for (auto it = emissionPairs.begin(); it != emissionPairs.end(); it++) {
		// Create the corresponding dissociation reaction
		auto newReaction = std::make_shared<DissociationReaction>(this,
				(*it).first, (*it).second);
		// Add it to the network
		newReaction = network->addDissociationReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;
	}
=======
/**
 * This operation prints a backward reaction given the three reactants in
 * A -> B + C.
 * @param firstReactant - The first reactant in the reaction, A.
 * @param secondReactant - The second reactant in the reaction, B.
 * @param thirdReactant - The third reactant in the reaction, C.
 */
void PSICluster::printDissociation(const Reactant & firstReactant,
		const Reactant & secondReactant,
		const Reactant & productReactant) const {

	auto firstComp = firstReactant.getComposition();
	auto secondComp = secondReactant.getComposition();
	auto productComp = productReactant.getComposition();

	std::cout << firstReactant.getName() << "(" << firstComp["He"] << ", "
			<< firstComp["V"] << ", " << firstComp["I"] << ") -> "
			<< secondReactant.getName() << "(" << secondComp["He"] << ", "
			<< secondComp["V"] << ", " << secondComp["I"] << ") + "
			<< productReactant.getName() << "(" << productComp["He"] << ", "
			<< productComp["V"] << ", " << productComp["I"] << ")" << std::endl;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	return;
}

<<<<<<< HEAD
static std::vector<int> getFullConnectivityVector(std::set<int> connectivitySet,
		int size) {
=======
/**
 * This operation creates a full vector from the connectivity set. It expands
 * the set to fill an array of length size with ones and zeros based on whether
 * or not the cluster at index i is in the set.
 *
 * It is mostly a convenience function to reduce the amount of code between
 * getReactionConnectivity and getDissociationConnectivity, which do the same
 * thing but with different sets.
 *
 * @param connSet The set that should be expanded into the vector.
 * @return The connectivity vector.
 */
static std::vector<int> getFullConnectivityVector(std::set<int> connectivitySet, int size) {

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	// Create a vector of zeroes with size equal to the network size
	std::vector<int> connectivity(size);

	// Set the value of the connectivity array to one for each element that is
	// in the set.
<<<<<<< HEAD
	for (auto it = connectivitySet.begin(); it != connectivitySet.end(); ++it) {
		connectivity[*it - 1] = 1;
=======
	for (auto it = connectivitySet.begin();
			it != connectivitySet.end(); it++) {
		connectivity[*it-1] = 1;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	return connectivity;
}

<<<<<<< HEAD
std::vector<int> PSICluster::getReactionConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(reactionConnectivitySet, network->getDOF());
}

std::vector<int> PSICluster::getDissociationConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(dissociationConnectivitySet,
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

	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

	return;
}

double PSICluster::getDissociationFlux() const {
	// Initial declarations
	int nPairs = 0;
	double flux = 0.0;
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
	}

	// Return the flux
	return flux;
}

double PSICluster::getEmissionFlux() const {
	// Initial declarations
	int nPairs = 0;
	double flux = 0.0;

	// Set the total number of emission pairs
	nPairs = emissionPairs.size();
	// Loop over all the pairs
	for (int i = 0; i < nPairs; i++) {
		// Update the flux
		flux += emissionPairs[i].reaction->kConstant
				* (double) emissionPairs[i].multiplicity;
	}

	return flux * concentration;
}

double PSICluster::getProductionFlux() const {
	// Local declarations
	double flux = 0.0;
	int nPairs = 0;
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
=======
void PSICluster::setReactionConnectivity(int clusterId) {

	// Add the cluster to the set.
	reactionConnectivitySet.insert(clusterId);
	// Set the dissociation connectivity to 1 for the given cluster. The array
	// is zero-indexed.
	//reactionConnectivity[clusterId-1] = 1;
}

std::vector<int> PSICluster::getReactionConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(reactionConnectivitySet,network->size());
}

std::set<int> PSICluster::getReactionConnectivitySet() const {
	return std::set<int>(reactionConnectivitySet);
}

void PSICluster::setDissociationConnectivity(int clusterId) {

	// Add the cluster to the set.
	dissociationConnectivitySet.insert(clusterId);
	// Set the dissociation connectivity to 1 for the given cluster. The array
	// is zero-indexed.
//	dissociationConnectivity[clusterId - 1] = 1;
}

std::vector<int> PSICluster::getDissociationConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(dissociationConnectivitySet,network->size());
}

std::set<int> PSICluster::getDissociationConnectivitySet() const {
	return std::set<int>(dissociationConnectivitySet);
}

int PSICluster::getSize() const {
	// Return this cluster's size
	return size;
}

void PSICluster::setReactionNetwork(
		const std::shared_ptr<ReactionNetwork> reactionNetwork) {

	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);

	// ----- Handle the connectivty for PSIClusters -----

	// Extract properties from the network
	auto properties = network->getProperties();
	int connectivityLength = network->size();

	// Get the enabled reaction type flags
	bool reactionsEnabled = (properties["reactionsEnabled"] == "true");
	bool dissociationsEnabled = (properties["dissociationsEnabled"] == "true");

	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingClusters.clear();

	// Set the shared pointer to this cluster
	thisSharedPtr = getThisSharedPtrFromNetwork();

	// Get the index/id of this cluster in the reaction network.
	thisNetworkIndex = getId() - 1;

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
	dissociatingClusters.shrink_to_fit();

	// Print array size information
//	std::cout << "Array sizes for " << getName() << " (Id = " << getId() << ")" << std::endl;
//	std::cout << "reactionConnectivitySet: size = "
//			<< reactionConnectivitySet.size() << std::endl;
//	std::cout << "dissociationConnectivitySet: size = "
//			<< dissociationConnectivitySet.size() << std::endl;
//	std::cout << "reactingPairs: size = "
//			<< reactingPairs.size() << ", capacity = "
//			<< reactingPairs.capacity() << ", capacity/size = "
//			<< ((float) reactingPairs.capacity()/
//					(float) reactingPairs.size())
//			<< std::endl;
//	std::cout << "combiningReactants: size = "
//			<< combiningReactants.size() << ", capacity = "
//			<< combiningReactants.capacity() << ", capacity/size = "
//			<< ((float) combiningReactants.capacity()/
//					(float) combiningReactants.size())
//			<< std::endl;
//	std::cout << "dissociatingClusters: size = "
//			<< dissociatingClusters.size() << ", capacity = "
//			<< dissociatingClusters.capacity() << ", capacity/size = "
//			<< ((float) dissociatingClusters.capacity()/
//					(float) dissociatingClusters.size())
//			<< std::endl;

	return;
}

double PSICluster::getDissociationFlux(double temperature) const {

	// increment the getDissociationFlux counter
	getDissociationFluxCounter->increment();

	int nClusters = 0, smallerClusterSize = 0.0;
	double flux = 0.0, fluxMultiplier = 1.0;
	std::shared_ptr<PSICluster> dissociatingCluster, smallerCluster,
			singleSpeciesCluster;
	std::map<std::string, int> oneHe, oneV, oneI;

	// Only try this if the network is available
	if (network != NULL) {
		// Get this PSICluster or subclasses' cluster map
		auto composition = getComposition();
		// Get the number of species to determine if this
		// cluster is mixed or single
		int numSpecies = (composition["He"] > 0) + (composition["V"] > 0)
				+ (composition["I"] > 0);
		// If no species, throw error
		if (numSpecies == 0) {
			// Bad if we have no species
			throw std::string("Cluster map contains no species");
		} else if (numSpecies == 1) {

			// ----- This doesn't seem completely correct. REVIEW!!!!! -----

			// Set the total number of reactants that dissociate to form this one
			nClusters = dissociatingClusters.size();
			// Loop over all dissociating clusters that form this cluster
			for (int j = 0; j < nClusters; j++) {
				dissociatingCluster = dissociatingClusters[j];
				// Since we know that the other cluster has to be the same type as
				// this one, we can just pull the size from the composition.
				smallerClusterSize = dissociatingCluster->getComposition().at(
						name) - 1;
				// Get the cluster one size smaller than the dissociating cluster.
				smallerCluster = std::dynamic_pointer_cast<PSICluster>(
						network->get(name, smallerClusterSize));
				// Get the single species cluster that comes out with it
				singleSpeciesCluster = std::dynamic_pointer_cast<PSICluster>(
						network->get(name, 1));
				// Calculate Second term of Dissociation flux
				if (smallerCluster) {
					flux += fluxMultiplier
							* calculateDissociationConstant(*smallerCluster,
									*singleSpeciesCluster, temperature)
							* dissociatingCluster->getConcentration();
//				std::cout << "Adding dissociation flux for "
//						<< dissociatingCluster->getName() << "_"
//						<< dissociatingCluster->getSize() << " --> "
//						<< getName() << "_"
//						<< dissociatingCluster->getSize() - 1 << " + "
//						<< getName() << "_" << getSize() << " = "
//						<< calculateDissociationConstant(*smallerCluster,
//								temperature)
//								* dissociatingCluster->getConcentration()
//						<< std::endl;
				}
			}
		} else if (numSpecies == 2) {
			std::cout << "PSICluster Message: "
					<< "Caught invalid single-species composition! "
					<< composition["He"] << " " << composition["V"] << " "
					<< composition["I"] << std::endl;
			throw std::string(
					"Mixed Species dissociation flux must be implemented by subclass.");
		}

	}

	// Return the flux
	return flux;
}

double PSICluster::getProductionFlux(double temperature) const {

	// Local declarations
	double flux = 0.0;
	ReactingPair pair;
	std::shared_ptr<PSICluster> firstReactant, secondReactant;
	double conc1 = 0.0, conc2 = 0.0;
	int nPairs = 0;

	// Only try this if the network is available
	if (network != NULL) {
		// Set the total number of reacting pairs
		nPairs = reactingPairs.size();
		// Loop over all the reacting pairs
		for (int i = 0; i < nPairs; i++) {
			// Get the reactants
			pair = reactingPairs[i];
			firstReactant = pair.first;
			secondReactant = pair.second;
			// Update the flux
			conc1 = firstReactant->getConcentration();
			conc2 = secondReactant->getConcentration();
			flux += calculateReactionRateConstant(*firstReactant,
					*secondReactant, temperature) * conc1 * conc2;
			// Debug output.
			//printReaction(*firstReactant,*secondReactant,*this);
		}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Return the production flux
	return flux;
}

<<<<<<< HEAD
double PSICluster::getCombinationFlux() const {
	// Local declarations
	double flux = 0.0;
	int nReactants = 0;
	PSICluster *combiningCluster = nullptr;
=======
double PSICluster::getCombinationFlux(double temperature) const {

	// Local declarations
	double flux = 0.0, conc = 0.0;
	std::shared_ptr<PSICluster> otherCluster;
	int nReactants = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	// Set the total number of reactants that combine to form this one
	nReactants = combiningReactants.size();
	// Loop over all possible clusters
	for (int j = 0; j < nReactants; j++) {
<<<<<<< HEAD
		// Get the cluster that combines with this one
		combiningCluster = combiningReactants[j].combining;
		// Calculate the combination flux
		flux += combiningReactants[j].reaction->kConstant
				* (double) combiningReactants[j].multiplicity
				* combiningCluster->getConcentration(
						combiningReactants[j].heDistance,
						combiningReactants[j].vDistance);
	}

	return flux * concentration;
}

std::vector<double> PSICluster::getPartialDerivatives() const {
	// Local Declarations
	std::vector<double> partials(network->getDOF(), 0.0);

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

void PSICluster::getProductionPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numReactants = 0, index = 0;
	double value = 0.0;

	// Production
	// A + B --> D, D being this cluster
	// The flux for D is
	// F(C_D) = k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_D)/dC_A = k+_(A,B)*C_B
	// dF(C_D)/dC_B = k+_(A,B)*C_A
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
	}

	return;
}

void PSICluster::getCombinationPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numReactants = 0, otherIndex = 0;
	PSICluster *cluster = nullptr;
	double value = 0.0;

	// Combination
	// A + B --> D, A being this cluster
	// The flux for A is outgoing
	// F(C_A) = - k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k+_(A,B)*C_B
	// dF(C_A)/dC_B = - k+_(A,B)*C_A
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
	}

	return;
}

void PSICluster::getDissociationPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numPairs = 0, index = 0;
	PSICluster *cluster = nullptr;
	double value = 0.0;

	// Dissociation
	// A --> B + D, B being this cluster
	// The flux for B is
	// F(C_B) = k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_B)/dC_A = k-_(B,D)
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
	}

	return;
}

void PSICluster::getEmissionPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int numPairs = 0, index = 0;

	// Emission
	// A --> B + D, A being this cluster
	// The flux for A is
	// F(C_A) = - k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k-_(B,D)
	numPairs = emissionPairs.size();
	for (int i = 0; i < numPairs; i++) {
		// Modify the partial derivative. Remember that the flux
		// due to emission is OUTGOING (-=)!
		index = id - 1;
		partials[index] -= emissionPairs[i].reaction->kConstant
				* (double) emissionPairs[i].multiplicity;
	}

	return;
}

void PSICluster::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
=======
		otherCluster = std::dynamic_pointer_cast<PSICluster>(
				combiningReactants.at(j));
		conc = otherCluster->getConcentration();
		// Calculate Second term of production flux
		flux += calculateReactionRateConstant(*this, *otherCluster, temperature)
				* conc;
//		std::cout << "Adding combination flux for " << getName() << "_"
//				<< getSize() << " + " << otherCluster->getName() << "_"
//				<< otherCluster->getSize() << " --> " << getName() << "_"
//				<< size + otherCluster->getSize() << " = "
//				<< calculateReactionRateConstant(*this, *otherCluster,
//						temperature) * conc << std::endl;
	}

	// Return the production flux
//	std::cout << "PSICluster::getCF ----- cf = " << flux * getConcentration()
//			<< std::endl;
	return (flux * getConcentration());
}

double PSICluster::getTotalFlux(const double temperature) {

	// Get the fluxes
	double prodFlux, combFlux, dissFlux;
	prodFlux = getProductionFlux(temperature);
	combFlux = getCombinationFlux(temperature);
	dissFlux = getDissociationFlux(temperature);

//	std::cout << "----- Cluster " << name << "_" << size << " fluxes -----"
//			<< std::endl;
//	std::cout << "FINAL Production flux = " << getProductionFlux(temperature)
//			<< std::endl;
//	std::cout << "FINAL Combination flux = " << getCombinationFlux(temperature)
//			<< std::endl;
//	std::cout << "FINAL Dissociation flux = "
//			<< getDissociationFlux(temperature) << " for " << getName() << "_ "
//			<< getSize() << std::endl;

	return prodFlux - combFlux + dissFlux;
}

double PSICluster::getDiffusionFactor() const {
	// Return the diffusion factor
	return diffusionFactor;
}

void PSICluster::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	return;
}

double PSICluster::getDiffusionCoefficient(double temperature) const {
	// Use the Arrhenius equation to compute the diffusion coefficient
	double k_b = xolotlCore::kBoltzmann;
	double kernel = -1.0 * migrationEnergy / (k_b * temperature);
	return diffusionFactor * exp(kernel);
}

std::vector<double> PSICluster::getBindingEnergies() const {
	// Local Declarations
	std::vector<double> energyVector;

	// Set the return binding energies
	energyVector = bindingEnergies;

	// Return the energies
	return energyVector;
}

void PSICluster::setBindingEnergies(const std::vector<double> energies) {
	// Set the binding energies
	bindingEnergies = energies;
	return;
}

double PSICluster::getMigrationEnergy() const {
	// Return the migration energy
	return migrationEnergy;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

void PSICluster::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
<<<<<<< HEAD
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

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
=======
	return;
}

double PSICluster::calculateReactionRateConstant(
		const PSICluster & firstReactant, const PSICluster & secondReactant,
		double temperature) const {

	// Get the reaction radii
	double r_first = firstReactant.getReactionRadius();
	double r_second = secondReactant.getReactionRadius();

	// Get the diffusion coefficients
	double firstDiffusion = firstReactant.getDiffusionCoefficient(temperature);
	double secondDiffusion = secondReactant.getDiffusionCoefficient(
			temperature);

//	std::cout << "Handling reaction: " << firstReactant.getName() << "_"
//			<< firstReactant.getSize() << " + " << secondReactant.getName()
//			<< "_" << secondReactant.getSize() << std::endl;

	// Calculate and return
	double k_plus = 4.0 * xolotlCore::pi * (r_first + r_second)
			* (firstDiffusion + secondDiffusion);
	return k_plus;
}

double PSICluster::calculateDissociationConstant(
		const PSICluster & firstCluster, const PSICluster & secondCluster,
		double temperature) const {

	// Local Declarations
	int bindingEnergyIndex = -1;
	double atomicVolume = 1.0; // Currently calculated below for He and W only!
	double bindingEnergy = 0.0;
	std::vector<int> parentCompVector = { 0, 0, 0 };
	auto otherComposition = firstCluster.getComposition();

	// Get the binding energy index.
	bindingEnergyIndex = bindingEnergyIndexMap[firstCluster.getName()];
	// The atomic volume is computed by considering the BCC structure of the
	// tungsten. In a given lattice cell in tungsten there are tungsten atoms
	// at each corner and a tungsten atom in the center. The tungsten atoms at
	// the corners are shared across a total of eight cells. The fraction of
	// the volume of the lattice cell that is filled with tungsten atoms is the
	// atomic volume and is a_0^3/(8*1/8 + 1) = 0.5*a_0^3.
	atomicVolume = 0.5 * xolotlCore::latticeConstant
			* xolotlCore::latticeConstant * xolotlCore::latticeConstant;

	// Calculate the Reaction Rate Constant
	double kPlus = 0.0;
	kPlus = calculateReactionRateConstant(firstCluster, secondCluster,
			temperature);

	// Calculate and return
	bindingEnergy = firstCluster.getBindingEnergies()[bindingEnergyIndex];
	double k_minus_exp = exp(
			-1.0 * bindingEnergy / (xolotlCore::kBoltzmann * temperature));
	double k_minus = (1.0 / atomicVolume) * kPlus * k_minus_exp;

//	std::cout << "kPlus in " << name << "_" << size << " = " << kPlus
//			<< std::endl;
//	std::cout << "k_minus_exp in " << name << "_" << size << " = "
//			<< k_minus_exp << std::endl;
//	std::cout << "k_minus in " << name << "_" << size << " = " << k_minus
//			<< std::endl;
//	std::cout << "atomic volume in " << name << "_" << size << " = " << atomicVolume
//			<< std::endl;
//	std::cout << "E_b in " << name << "_" << size << " = "
//			<< firstCluster.getBindingEnergies()[bindingEnergyIndex]
//			<< " at index = " << bindingEnergyIndex << std::endl;

	return k_minus;
}

double PSICluster::getReactionRadius() const {
	return reactionRadius; // Computed by subclasses in constructors.
}

std::vector<int> PSICluster::getConnectivity() const {

	int connectivityLength = network->size();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);
	auto reactionConnVector = getReactionConnectivity();
	auto dissociationConnVector = getDissociationConnectivity();

	// The reaction and dissociation vectors must have a length equal to the
	// number of clusters
<<<<<<< HEAD
	if (reactionConnVector.size() != (unsigned int) connectivityLength) {
		throw std::string("The reaction vector is an incorrect length");
	}
	if (dissociationConnVector.size() != (unsigned int) connectivityLength) {
=======
	if (reactionConnVector.size() != connectivityLength) {
		throw std::string("The reaction vector is an incorrect length");
	}
	if (dissociationConnVector.size() != connectivityLength) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
		throw std::string("The dissociation vector is an incorrect length");
	}

	// Merge the two vectors such that the final vector contains
	// a 1 at a position if either of the connectivity arrays
	// have a 1
	for (int i = 0; i < connectivityLength; i++) {
		// Consider each connectivity array only if its type is enabled
		connectivity[i] = reactionConnVector[i] || dissociationConnVector[i];
	}

<<<<<<< HEAD
	return connectivity;
}
=======
//	// DEBUG
//	std::cout << std::endl << "Reactant Column: " << this->name << "_"
//			<< this->size << std::endl;
//
//	// DEBUG
//	for (int i = 0; i < connectivity.size(); i++) {
//		std::cout << connectivity[i] << " ";
//	}
//	std::cout << std::endl;

	return connectivity;
}

void PSICluster::createReactionConnectivity() {
	// Nothing to do.
}

void PSICluster::createDissociationConnectivity() {

	// Local Declarations
	std::shared_ptr<Reactant> smallerReactant, singleReactant;

	// ----- X_a --> X_(a-1) + X ------
	smallerReactant = network->get(name, size - 1);
	singleReactant = network->get(name, 1);
	dissociateClusters(singleReactant, smallerReactant);

	return;
}

/**
 * This operation creates the two dissociated clusters from this cluster.
 * It is called by createDissociationConnectivity to process the reaction
 * and handle the connectivity.
 * @param firstDissociatedCluster The first cluster removed by
 * dissociation.
 * @param secondDissociatedCluster The second cluster removed by
 * dissociation.
 */
void PSICluster::dissociateClusters(
		const std::shared_ptr<Reactant> & firstDissociatedCluster,
		const std::shared_ptr<Reactant> & secondDissociatedCluster) {

	std::shared_ptr<PSICluster> thisCluster = getThisSharedPtrFromNetwork(),
			castedFirstCluster, castedSecondCluster;

	if (firstDissociatedCluster && secondDissociatedCluster) {

		// Cast to PSICluster so that we can get the information we need
		castedFirstCluster = std::dynamic_pointer_cast<PSICluster>(
				firstDissociatedCluster);
		castedSecondCluster = std::dynamic_pointer_cast<PSICluster>(
				secondDissociatedCluster);

//		std::cout << "Configuring dissociation: " << name << "_" << size
//				<< " --> " << firstDissociatedCluster->getName() << "_"
//				<< firstDissociatedCluster->getComposition()[name] << " + "
//				<< secondDissociatedCluster->getName() << "_"
//				<< secondDissociatedCluster->getComposition()[name]
//				<< std::endl;

		// Add the two reactants to the set. Also add this cluster to
		// their lists of dissociating clusters. Handle the first one.
		setDissociationConnectivity(firstDissociatedCluster->getId());
		dissociatingClusters.push_back(castedFirstCluster);
		castedFirstCluster->dissociatingClusters.push_back(thisCluster);
		// Handle the second one.
		setDissociationConnectivity(secondDissociatedCluster->getId());
		dissociatingClusters.push_back(castedSecondCluster);
		castedSecondCluster->dissociatingClusters.push_back(thisCluster);
		// Connect this cluster to itself since any reaction will affect it
		setDissociationConnectivity(getId());
	}

	return;
}

/**
 * This operation computes the partial derivatives due to production
 * reactions.
 *
 * @param partials The vector into which the partial derivatives should be
 * inserted.
 */
void PSICluster::getProductionPartialDerivatives(std::vector<double> & partials,
		double temperature) const {

	// Create the array and fill it with zeros
	int numReactants = 0, index = 0;
	ReactingPair pair;
	double rateConstant = 0.0;

	// Load up everything from the reacting pairs array. The partial
	// derivative for production reactions is k+_(j,m)*C_m where j is the index
	// of the current cluster for which the derivative is being calculated
	// and m the loop index of a cluster that produces this one.
	//
	// Practically, this just means that we have to compute k+ between each
	// of reacting pair and multiply it separately by the population of each
	// cluster in the pair.
	numReactants = reactingPairs.size();
	for (int i = 0; i < numReactants; i++) {
		pair = reactingPairs[i];
		rateConstant = calculateReactionRateConstant(*(pair.first),
				*(pair.second), temperature);
		// Compute the contribution from the first part of the reacting pair
		index = pair.first->getId() - 1;
		partials[index] += rateConstant * pair.second->getConcentration();
//		std::cout << "RP1 - Partial Derivative = " << partialDerivatives[index]
//				<< " from " << pair.first->getName() << "_"
//				<< pair.first->getSize() << std::endl;
		// Compute the contribution from the second part of the reacting pair
		index = pair.second->getId() - 1;
		partials[index] += rateConstant * pair.first->getConcentration();
//		std::cout << "RP2 - Partial Derivative = " << partialDerivatives[index]
//				<< " from " << pair.second->getName() << "_"
//				<< pair.second->getSize() << std::endl;
	}

	return;
}

/**
 * This operation computes the partial derivatives due to combination
 * reactions.
 *
 * @param partials The vector into which the partial derivatives should be
 * inserted.
 */
void PSICluster::getCombinationPartialDerivatives(
		std::vector<double> & partials, double temperature) const {

	// Create the array and fill it with zeros
	int numReactants = 0, index = 0;
	std::shared_ptr<PSICluster> cluster, smallerCluster, singleSpeciesCluster;

	// Load up everything from the combining reactants.
	// Combination fluxes are an outgoing flux, so they only
	// affect this cluster (index = thisIndex). The partial derivative
	// for the combining flux for any cluster C_j is dF_(C_i)/dC_j =
	// k+_(i,j)*C_i.
	//
	// This means that we compute k+ and then multiply by the concentration
	// of this cluster.
	//
	// This only computes the partial derivatives with respect to the
	// combining reactants. The final term, df(C_i)/dC_i is computed below.
	numReactants = combiningReactants.size();
	for (int i = 0; i < numReactants; i++) {
		cluster = std::dynamic_pointer_cast<PSICluster>(combiningReactants[i]);
		// Get the index of cluster
		index = cluster->getId() - 1;
		// Compute the contribution from the cluster. Remember that the flux
		// due to combinations is OUTGOING (-=)!
		partials[index] -= calculateReactionRateConstant(*this, *cluster,
				temperature) * getConcentration();
//		std::cout << "Combining Partial Derivative = "
//				<< partialDerivatives[index] << ", c = " << getConcentration()
//				<< ", rc = "
//				<< calculateReactionRateConstant(*this, *cluster, temperature)
//				<< ", of " << name << "_" << size << ", with "
//				<< cluster->getName() << "_" << cluster->getSize() << std::endl;
	}

	// This section computes the partial derivative of the combining flux due
	// to changes in the concentration of this cluster.
	//
	// This is simply a loop over all of the combining clusters to compute
	// df(C_i)/dC_i = sum(k+_(i,j)*C_j).
	//
	// Loop over all of the clusters and compute the sum
	for (int i = 0; i < numReactants; i++) {
		cluster = std::dynamic_pointer_cast<PSICluster>(combiningReactants[i]);
		// Compute the contribution from the cluster. Remember that the flux
		// due to combinations is OUTGOING (-=)!
		partials[thisNetworkIndex] -= calculateReactionRateConstant(*this,
				*cluster, temperature) * cluster->getConcentration();
	}
//	std::cout << "Combining Partial Derivative for df(C_i)/dC_i) = "
//			<< partialDerivatives[index] << std::endl;

	return;
}

/**
 * This operation computes the partial derivatives due to dissociation
 * reactions.
 *
 * @param partials The vector into which the partial derivatives should be
 * inserted.
 */
void PSICluster::getDissociationPartialDerivatives(
		std::vector<double> & partials, double temperature) const {

	// Create the array and fill it with zeros
	int numReactants = 0, index = 0;
	int smallerClusterSize = 0;
	std::shared_ptr<PSICluster> cluster, smallerCluster, singleSpeciesCluster;
	// Get the single species cluster that comes out of this one during the
	// dissociation process.
	singleSpeciesCluster = std::dynamic_pointer_cast<PSICluster>(
			network->get(name, 1));

	// Load up everything from the dissociating reactants. The partial
	// derivative for dissociation is just the dissociation constant between
	// this cluster and the cluster one size smaller than the dissociating
	// cluster.
	numReactants = dissociatingClusters.size();
	for (int i = 0; i < numReactants; i++) {
		// Figure out if this cluster dissociates to another
		cluster = dissociatingClusters[i];
		// Since we know that the other cluster has to be the same type as
		// this one, we can just pull the size from the composition.
//		std::cout << name << "_" << size << " d_COMP = " << cluster->getName()
//				<< "_" << cluster->getComposition()[name] << std::endl;
		smallerClusterSize = cluster->getComposition().at(name) - 1;
		// Get the cluster one size smaller than the dissociating cluster.
		smallerCluster = std::dynamic_pointer_cast<PSICluster>(
				network->get(name, smallerClusterSize));
		// Compute the contribution from the smaller cluster
		index = cluster->getId() - 1;
		// Only modify the derivative if the smaller cluster exists
		if (smallerCluster && singleSpeciesCluster) {
			partials[index] += calculateDissociationConstant(*smallerCluster,
					*singleSpeciesCluster, temperature);
//		std::cout << name << "_" << size << " Dissociation Partial Derivative = "
//				<< partialDerivatives[index] << " with " << index << std::endl;
		}
	}

	return;
}

/**
 * This operation returns the list of partial derivatives of this Reactant
 * with respect to all other reactants in the network. The combined lists
 * of partial derivatives from all of the reactants in the network can be
 * used to form, for example, a Jacobian.
 *
 * @param the temperature at which the reactions are occurring
 * @return The partial derivatives for this reactant where index zero
 * corresponds to the first reactant in the list returned by the
 * ReactionNetwork::getAll() operation.
 */
std::vector<double> PSICluster::getPartialDerivatives(
		double temperature) const {

	// Local Declarations
	std::vector<double> partials(network->size(), 0.0);

	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials, temperature);
	getCombinationPartialDerivatives(partials, temperature);
	getDissociationPartialDerivatives(partials, temperature);

	return partials;
}

void PSICluster::combineClusters(
		std::shared_ptr<std::vector<std::shared_ptr<Reactant>>>reactants,
		int maxSize, std::string productName) {

			std::map<std::string,int> myComposition = getComposition(), secondComposition;
			int numHe, numV, numI, secondNumHe, secondNumV, secondNumI;
			int otherId, productId;
			std::vector<int> compositionSizes {0,0,0};
			std::shared_ptr<PSICluster> secondCluster, productCluster;
			// Setup the composition variables for this cluster
			numHe = myComposition["He"];
			numV = myComposition["V"];
			numI = myComposition["I"];

			int reactantVecSize = reactants->size();
			for (int i = 0; i < reactantVecSize; i++) {
				// Get the second reactant, its composition and its index
				secondCluster = std::dynamic_pointer_cast <PSICluster> (reactants->at(i));
				secondComposition = secondCluster->getComposition();
				secondNumHe = secondComposition["He"];
				secondNumV = secondComposition["V"];
				secondNumI = secondComposition["I"];
				otherId = secondCluster->getId();
				int productSize = size + secondCluster->getSize();
				// Get and handle product for compounds
				if (productName == "HeV" || productName == "HeI") {
					// Modify the composition vector
					compositionSizes[0] = numHe + secondNumHe;
					compositionSizes[1] = numV + secondNumV;
					compositionSizes[2] = numI + secondNumI;
					// Get the product
					productCluster = std::dynamic_pointer_cast < PSICluster
					> (network->getCompound(productName, compositionSizes));
				} else {
					// Just get the product if it is a single-species
					productCluster = std::dynamic_pointer_cast < PSICluster
					> (network->get(productName, productSize));
				}
				// React if the size of the product is valid and it exists in the network
				if (productSize <= maxSize && productCluster) {
					// Setup the connectivity array for the second reactant
					setReactionConnectivity(otherId);
					// FIXME! - Debug output
					//printReaction(*this,*secondCluster,*productCluster);
//			std::cout << "reactionConnectivity["<< otherIndex << "] = " << reactionConnectivity[otherIndex] << " " << getName() << std::endl;
					// Setup the connectivity array for the product
					productId = productCluster->getId();
					setReactionConnectivity(productId);
					// FIXME! - Debug output
//			std::cout << productSize << productName << ": " << "reactionConnectivity["<< productIndex << "] = "
//			<< reactionConnectivity[productIndex] << std::endl;
					// Push the product onto the list of clusters that combine with this one
					combiningReactants.push_back(secondCluster);
				}
			}

			return;
		}

void PSICluster::replaceInCompound(
		std::shared_ptr<std::vector<std::shared_ptr<Reactant>>>reactants,
		std::string oldComponentName, std::string newComponentName) {

			// Local Declarations
			std::map<std::string, int> myComp = getComposition(),
			secondReactantComp, productReactantComp;
			int myComponentNumber = myComp[newComponentName];
			int numReactants = reactants->size();
			int secondId = 0, productId = 0;
			std::shared_ptr<Reactant> secondReactant, productReactant;
			std::vector<int> productCompositionVector(myComp.size());

			// Loop over all of the extra reactants in this reaction and handle the replacement
			for (int i = 0; i < numReactants; i++) {
				// Get the second reactant and its composition
				secondReactant = reactants->at(i);
				secondReactantComp = secondReactant->getComposition();
				// Create the composition vector
				productReactantComp = secondReactantComp;
				// Updated the modified components
				productReactantComp[oldComponentName] =
				secondReactantComp[oldComponentName] - myComponentNumber;
				// Create the composition vector -- FIXME! This should be general!
				productCompositionVector[0] = productReactantComp["He"];
				productCompositionVector[1] = productReactantComp["V"];
				productCompositionVector[2] = productReactantComp["I"];
				// Get the product
				productReactant = network->getCompound(secondReactant->getName(),
						productCompositionVector);
				// If the product exists, mark the proper reaction arrays and it it to the list
				if (productReactant) {
					// Setup the connectivity array for the second reactant
					secondId = secondReactant->getId();
					setReactionConnectivity(secondId);
					//std::cout << secondCluster->getSize()
					//<< secondCluster->getName() << ": "
					//<< "reactionConnectivity[" << otherIndex << "] = "
					//<< reactionConnectivity[otherIndex] << std::endl;
					// Setup the connectivity array for the product
					productId = productReactant->getId();
					setReactionConnectivity(productId);
					// FIXME! - Debug output
					//std::cout << productSize << compoundName << ": "
					//<< "reactionConnectivity[" << productIndex << "] = "
					//<< reactionConnectivity[productIndex] << std::endl;
					// Push the product onto the list of clusters that combine with this one
					combiningReactants.push_back(secondReactant);
				}
			}

			return;
		}

void PSICluster::fillVWithI(std::string secondClusterName,
		std::shared_ptr<std::vector<std::shared_ptr<Reactant> > > reactants) {
	// Local Declarations
	std::shared_ptr<PSICluster> secondCluster, productCluster, thisCluster;
	std::string firstClusterName = getName(), productClusterName;
	int firstClusterSize = 0, secondClusterSize = 0, productClusterSize = 0;
	int secondId = 0, productId = 0, reactantVecSize = 0;
	ReactingPair pair;

	// Get the number of V or I in this cluster (the "first")
	firstClusterSize = getSize();
	// Look at all of the second clusters, either V or I, and determine
	// if a connection exists.
	reactantVecSize = reactants->size();
	for (int i = 0; i < reactantVecSize; i++) {
		// Get the second cluster its size
		secondCluster = std::dynamic_pointer_cast<PSICluster>(reactants->at(i));
		secondClusterSize = (secondCluster->getSize());
		// The only way this reaction is allowed is if the sizes are not equal.
		if (firstClusterSize != secondClusterSize) {
			// We have to switch on cluster type to make sure that the annihilation
			// is computed correctly.
			if (firstClusterName == "V") {
				// Compute the product size and set the product name for the case
				// where I is the second cluster
				if (secondClusterSize > firstClusterSize) {
					productClusterSize = secondClusterSize - firstClusterSize;
					productClusterName = "I";
				} else if (secondClusterSize < firstClusterSize) {
					productClusterSize = firstClusterSize - secondClusterSize;
					productClusterName = "V";
				}
			} else if (firstClusterName == "I") {
				// Compute the product size and set the product name for the case
				// where V is the second cluster
				if (firstClusterSize > secondClusterSize) {
					productClusterSize = firstClusterSize - secondClusterSize;
					productClusterName = "I";
				} else if (firstClusterSize < secondClusterSize) {
					productClusterSize = secondClusterSize - firstClusterSize;
					productClusterName = "V";
				}
			}
			// Get the product
			productCluster = std::dynamic_pointer_cast<PSICluster>(
					network->get(productClusterName, productClusterSize));
			// Only deal with this reaction if the product exists. Otherwise the
			// whole reaction is forbidden.
			if (productCluster) {
//				std::cout << "Trap Mutation: " << name << size << " + "
//						<< secondCluster->getName() << secondCluster->getSize()
//						<< " = " << productCluster->getName()
//						<< productCluster->getSize() << " "
//						<< productClusterName << productClusterSize
//						<< std::endl;
				// Setup the connectivity array to handle the second reactant
				secondId = secondCluster->getId();
				setReactionConnectivity(secondId);
				// Push the second cluster onto the list of clusters that combine
				// with this one
				combiningReactants.push_back(secondCluster);
				// Setup the connectivity array to handle the product
				productId = productCluster->getId();
				setReactionConnectivity(productId);
				// Add the current cluster and the second cluster as a reacting
				// pair for the product. Start by getting the pointer for this
				// cluster.
				thisCluster = getThisSharedPtrFromNetwork();
				// Create the pair
				pair.first = std::dynamic_pointer_cast<PSICluster>(thisCluster);
				pair.second = std::dynamic_pointer_cast<PSICluster>(
						secondCluster);
				// Add the pair to the list
				productCluster->reactingPairs.push_back(pair);
			}
		}
	}
}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
