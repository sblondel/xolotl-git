<<<<<<< HEAD
=======
#include <algorithm>
#include <cassert>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include "NECluster.h"
#include <xolotlPerf.h>
#include <Constants.h>
#include <MathUtils.h>

using namespace xolotlCore;

<<<<<<< HEAD
NECluster::NECluster() :
		Reactant() {
	// Set the reactant name appropriately
	name = "NECluster";

	return;
}

NECluster::NECluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		Reactant(registry) {
	// Set the reactant name appropriately
	name = "NECluster";

	return;
}

// The copy constructor
NECluster::NECluster(NECluster &other) :
		Reactant(other), reactingPairs(other.reactingPairs), combiningReactants(
				other.combiningReactants), dissociatingPairs(
				other.dissociatingPairs), emissionPairs(other.emissionPairs) {
	// Recompute all of the temperature-dependent quantities
	setTemperature(other.getTemperature());

	return;
}

void NECluster::createProduction(std::shared_ptr<ProductionReaction> reaction) {
	// Create a cluster pair from the given reaction
	ClusterPair pair((NECluster *) reaction->first,
			(NECluster *) reaction->second);
	// Add the pair to the list
	reactingPairs.push_back(pair);
	// Setup the connectivity array
	setReactionConnectivity(reaction->first->getId());
	setReactionConnectivity(reaction->second->getId());
=======
void NECluster::resultFrom(ProductionReaction& reaction, int, int, int, int) {

	// Add a cluster pair for given reaction 
	reactingPairs.emplace_back(
			reaction,  // TODO verify this is correct
			&static_cast<NECluster&>(reaction.first),
			&static_cast<NECluster&>(reaction.second));
	// Setup the connectivity array
	setReactionConnectivity(reaction.first.getId());
	setReactionConnectivity(reaction.second.getId());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
void NECluster::createCombination(
		std::shared_ptr<ProductionReaction> reaction) {
	setReactionConnectivity(id);
	// Look for the other cluster
	IReactant * secondCluster;
	if (reaction->first->getId() == id)
		secondCluster = reaction->second;
	else
		secondCluster = reaction->first;

	// Creates the combining cluster
	CombiningCluster combCluster((NECluster *) secondCluster);
	// Push the product into the list of clusters that combine with this one
	combiningReactants.push_back(combCluster);

	// Setup the connectivity array
	setReactionConnectivity(id);
	setReactionConnectivity(secondCluster->getId());
=======
void NECluster::participateIn(ProductionReaction& reaction, int a, int b) {
	setReactionConnectivity(id);
	// Look for the other cluster
	auto& otherCluster = static_cast<NECluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);
//	// Build a production reaction for it
//	std::unique_ptr<ProductionReaction> newReaction(
//			new ProductionReaction(otherCluster, *this));
//	// Add it to the network
//	auto& prref = network.add(std::move(newReaction));

	// Add the combining cluster to list of clusters that combine with us
	combiningReactants.emplace_back(reaction, otherCluster);

	// Setup the connectivity array
	setReactionConnectivity(id);
	setReactionConnectivity(otherCluster.getId());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
void NECluster::createDissociation(
		std::shared_ptr<DissociationReaction> reaction) {
	// Look for the other cluster
	IReactant * emittedCluster;
	if (reaction->first->getId() == id)
		emittedCluster = reaction->second;
	else
		emittedCluster = reaction->first;

	// Create the pair of them where it is important that the
	// dissociating cluster is the first one
	ClusterPair pair((NECluster *) reaction->dissociating,
			(NECluster *) emittedCluster);
	// Add the pair to the dissociating pair vector
	dissociatingPairs.push_back(pair);

	// Setup the connectivity array
	setDissociationConnectivity(reaction->dissociating->getId());
=======
void NECluster::participateIn(DissociationReaction& reaction, int a, int b,
		int c, int d) {
	// Look for the other cluster
	auto& emittedCluster = static_cast<NECluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Add a pair where it is important that the
	// dissociating cluster is the first one
	dissociatingPairs.emplace_back(
			reaction,  // TODO is this correct?
			&static_cast<NECluster&>(reaction.dissociating),
			&static_cast<NECluster&>(emittedCluster));

	// Setup the connectivity array
	setDissociationConnectivity(reaction.dissociating.getId());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
void NECluster::createEmission(std::shared_ptr<DissociationReaction> reaction) {
	// Create the pair of emitted clusters
	ClusterPair pair((NECluster *) reaction->first,
			(NECluster *) reaction->second);
	// Add the pair to the emission pair vector
	emissionPairs.push_back(pair);
=======
void NECluster::emitFrom(DissociationReaction& reaction, int a, int b, int c,
		int d) {

	// Add the pair of emitted clusters.
	emissionPairs.emplace_back(
			reaction, // TODO is this correct?
			&static_cast<NECluster&>(reaction.first),
			&static_cast<NECluster&>(reaction.second));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Setup the connectivity array to itself
	setReactionConnectivity(id);

	return;
}

void NECluster::optimizeReactions() {
	// Loop on the pairs to add reactions to the network
<<<<<<< HEAD
	for (auto it = reactingPairs.begin(); it != reactingPairs.end(); it++) {
		// Create the corresponding production reaction
		auto newReaction = std::make_shared<ProductionReaction>((*it).first,
				(*it).second);
		// Add it to the network
		newReaction = network->addProductionReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;
	}
	for (auto it = combiningReactants.begin(); it != combiningReactants.end(); it++) {
		// Create the corresponding production reaction
		auto newReaction = std::make_shared<ProductionReaction>((*it).combining,
				this);
		// Add it to the network
		newReaction = network->addProductionReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;
	}
	for (auto it = dissociatingPairs.begin(); it != dissociatingPairs.end(); it++) {
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
		auto newReaction = std::make_shared<DissociationReaction>(this, (*it).first,
				(*it).second);
		// Add it to the network
		newReaction = network->addDissociationReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;
	}
=======
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[this](ClusterPair& currPair) {
				// Create the corresponding production reaction
				std::unique_ptr<ProductionReaction> newReaction(new ProductionReaction(*currPair.first, *currPair.second));
				// Add it to the network
				auto& prref = network.add(std::move(newReaction));
				// Link it to the pair
				currPair.reaction = prref;
			});

	std::for_each(combiningReactants.begin(), combiningReactants.end(),
			[this](CombiningCluster& cc) {
				// Create the corresponding production reaction
				std::unique_ptr<ProductionReaction> newReaction(new ProductionReaction(cc.combining, *this));
				// Add it to the network
				auto& prref = network.add(std::move(newReaction));
				// Link it to the pair
				cc.reaction = prref;
			});

	std::for_each(dissociatingPairs.begin(), dissociatingPairs.end(),
			[this](ClusterPair& currPair) {
				// Create the corresponding dissociation reaction
				std::unique_ptr<DissociationReaction> newReaction(new DissociationReaction(*currPair.first, *currPair.second, *this));
				// Add it to the network
				auto& drref = network.add(std::move(newReaction));
				// Create the corresponding reverse reaction
				std::unique_ptr<ProductionReaction> newReverseReaction(new ProductionReaction(*currPair.second, *this));
				// Add it to the network
				auto& prref = network.add(std::move(newReverseReaction));
				// Link it
				drref.reverseReaction = &prref;
				// Link it to the pair
				currPair.reaction = drref;
			});

	std::for_each(emissionPairs.begin(), emissionPairs.end(),
			[this](ClusterPair& currPair) {
				// Create the corresponding dissociation reaction
				std::unique_ptr<DissociationReaction> newReaction(new DissociationReaction(*this, *currPair.first, *currPair.second));
				// Add it to the network
				auto& drref = network.add(std::move(newReaction));
				// Create the corresponding reverse reaction
				std::unique_ptr<ProductionReaction> newReverseReaction(new ProductionReaction(*currPair.first, *currPair.second));
				// Add it to the network
				auto& prref = network.add(std::move(newReverseReaction));
				// Link it
				drref.reverseReaction = &prref;
				// Link it to the pair
				currPair.reaction = drref;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

static std::vector<int> getFullConnectivityVector(std::set<int> connectivitySet,
		int size) {
	// Create a vector of zeroes with size equal to the network size
	std::vector<int> connectivity(size);

	// Set the value of the connectivity array to one for each element that is
	// in the set.
	for (auto it = connectivitySet.begin(); it != connectivitySet.end(); ++it) {
		connectivity[(*it) - 1] = 1;
	}

	return connectivity;
}

std::vector<int> NECluster::getReactionConnectivity() const {
	// Create the full vector from the set and return it
<<<<<<< HEAD
	return getFullConnectivityVector(reactionConnectivitySet, network->getDOF());
=======
	return getFullConnectivityVector(reactionConnectivitySet, network.getDOF());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

std::vector<int> NECluster::getDissociationConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(dissociationConnectivitySet,
<<<<<<< HEAD
			network->getDOF());
=======
			network.getDOF());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

void NECluster::resetConnectivities() {
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
	setReactionConnectivity(xeMomId);
	setDissociationConnectivity(xeMomId);

<<<<<<< HEAD
	// Loop on the reacting pairs
	for (auto it = reactingPairs.begin(); it != reactingPairs.end(); ++it) {
		// The cluster is connecting to both clusters in the pair
		setReactionConnectivity((*it).first->id);
		setReactionConnectivity((*it).first->xeMomId);
		setReactionConnectivity((*it).second->id);
		setReactionConnectivity((*it).second->xeMomId);
	}

	// Loop on the combining reactants
	for (auto it = combiningReactants.begin(); it != combiningReactants.end();
			++it) {
		// The cluster is connecting to the combining cluster
		setReactionConnectivity((*it).combining->id);
		setReactionConnectivity((*it).combining->xeMomId);
	}

	// Loop on the effective dissociating pairs
	for (auto it = dissociatingPairs.begin(); it != dissociatingPairs.end();
			++it) {
		// The cluster is connecting to the dissociating cluster which
		// is the first one by definition
		setDissociationConnectivity((*it).first->id);
		setDissociationConnectivity((*it).first->xeMomId);
	}

	// Don't loop on the emission pairs because
=======
	// Apply to each reacting pair.
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[this](const ClusterPair& currPair) {
				// The cluster is connecting to both clusters in the pair
				setReactionConnectivity(currPair.first->id);
				setReactionConnectivity(currPair.first->xeMomId);
				setReactionConnectivity(currPair.second->id);
				setReactionConnectivity(currPair.second->xeMomId);
			});

	// Apply to each combining cluster.
	std::for_each(combiningReactants.begin(), combiningReactants.end(),
			[this](const CombiningCluster& cc) {
				// The cluster is connecting to the combining cluster
				NECluster const& combCluster = cc.combining;
				setReactionConnectivity(combCluster.id);
				setReactionConnectivity(combCluster.xeMomId);
			});

	// Apply to each effective dissociating pair
	std::for_each(dissociatingPairs.begin(), dissociatingPairs.end(),
			[this](const ClusterPair& currPair) {
				// The cluster is connecting to the dissociating cluster which
				// is the first one by definition
				setDissociationConnectivity(currPair.first->id);
				setDissociationConnectivity(currPair.first->xeMomId);
			});

	// Don't apply to the emission pairs because
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// this cluster is not connected to them

	return;
}

<<<<<<< HEAD
void NECluster::setReactionNetwork(
		const std::shared_ptr<IReactionNetwork> reactionNetwork) {
	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);
=======
void NECluster::updateFromNetwork() {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

	return;
}

double NECluster::getMomentum() const {
	return 0.0;
}

double NECluster::getTotalFlux() {
	// Get the fluxes
	double prodFlux = getProductionFlux();
	double dissFlux = getDissociationFlux();
	double combFlux = getCombinationFlux();
	double emissFlux = getEmissionFlux();

	return prodFlux - combFlux + dissFlux - emissFlux;
}

double NECluster::getDissociationFlux() const {
<<<<<<< HEAD
	// Initial declarations
	int nPairs = 0;
	double flux = 0.0;
	NECluster *dissociatingCluster = nullptr;

	// Set the total number of reactants that dissociate to form this one
	nPairs = dissociatingPairs.size();
	// Loop over all dissociating clusters that form this cluster
	for (int j = 0; j < nPairs; j++) {
		// Get the dissociating cluster
		dissociatingCluster = dissociatingPairs[j].first;
		// Calculate the Dissociation flux
		flux += dissociatingPairs[j].reaction->kConstant
				* dissociatingCluster->getConcentration(
						dissociatingPairs[j].firstDistance);
	}
=======

	// Sum dissociation flux over all pairs that dissociate to form this one.
	double flux =
			std::accumulate(dissociatingPairs.begin(), dissociatingPairs.end(),
					0.0, [](double running, const ClusterPair& currPair) {
						// Get the dissociating cluster
					auto& dissociatingCluster = currPair.first;
					// Calculate the Dissociation flux
					Reaction const& currReaction = currPair.reaction;
					return running + (currReaction.kConstant *
							dissociatingCluster->getConcentration(currPair.firstDistance));
				});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Return the flux
	return flux;
}

double NECluster::getEmissionFlux() const {
<<<<<<< HEAD
	// Initial declarations
	int nPairs = 0;
	double flux = 0.0;

	// Set the total number of emission pairs
	nPairs = emissionPairs.size();
	// Loop over all the pairs
	for (int i = 0; i < nPairs; i++) {
		// Update the flux
		flux += emissionPairs[i].reaction->kConstant;
	}
=======

	// Sum reaction rate constants over all emission pair reactions.
	double flux = std::accumulate(emissionPairs.begin(), emissionPairs.end(),
			0.0, [](double running, const ClusterPair& currPair) {
				Reaction const& currReaction = currPair.reaction;
				return running + currReaction.kConstant;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return flux * concentration;
}

double NECluster::getProductionFlux() const {
	// Local declarations
	double flux = 0.0;
<<<<<<< HEAD
	int nPairs = 0;
	NECluster *firstReactant = nullptr, *secondReactant = nullptr;

	// Set the total number of reacting pairs
	nPairs = reactingPairs.size();
	// Loop over all the reacting pairs
	for (int i = 0; i < nPairs; i++) {
		// Get the two reacting clusters
		firstReactant = reactingPairs[i].first;
		secondReactant = reactingPairs[i].second;
		// Update the flux
		flux += reactingPairs[i].reaction->kConstant
				* firstReactant->getConcentration(
						reactingPairs[i].firstDistance)
				* secondReactant->getConcentration(
						reactingPairs[i].secondDistance);
	}
=======

	// Sum over all the reacting pairs
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[&flux](ClusterPair const& currPair) {
				// Get the two reacting clusters
				NECluster* firstReactant = currPair.first;
				NECluster* secondReactant = currPair.second;
				// Update the flux
				Reaction const& currReaction = currPair.reaction;
				flux += currReaction.kConstant
				* firstReactant->getConcentration(
						currPair.firstDistance)
				* secondReactant->getConcentration(
						currPair.secondDistance);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Return the production flux
	return flux;
}

double NECluster::getCombinationFlux() const {
<<<<<<< HEAD
	// Local declarations
	double flux = 0.0;
	int nReactants = 0;
	NECluster *combiningCluster = nullptr;

	// Set the total number of reactants that combine to form this one
	nReactants = combiningReactants.size();
	// Loop over all possible clusters
	for (int j = 0; j < nReactants; j++) {
		// Get the cluster that combines with this one
		combiningCluster = combiningReactants[j].combining;
		// Calculate Second term of production flux
		flux += combiningReactants[j].reaction->kConstant
				* combiningCluster->getConcentration(
						combiningReactants[j].distance);
	}
=======

	double flux = std::accumulate(combiningReactants.begin(),
			combiningReactants.end(), 0.0,
			[](double running, const CombiningCluster& currPair) {
				// Get the cluster that combines with this one
				NECluster const& combiningCluster = currPair.combining;
				Reaction const& currReaction = currPair.reaction;

				// Calculate Second term of production flux
				return running +
				(currReaction.kConstant *
						combiningCluster.getConcentration(currPair.distance));

			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return flux * concentration;
}

std::vector<double> NECluster::getPartialDerivatives() const {
	// Local Declarations
<<<<<<< HEAD
	std::vector<double> partials(network->getDOF(), 0.0);
=======
	std::vector<double> partials(network.getDOF(), 0.0);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials);
	getCombinationPartialDerivatives(partials);
	getDissociationPartialDerivatives(partials);
	getEmissionPartialDerivatives(partials);

	return partials;
}

void NECluster::getPartialDerivatives(std::vector<double> & partials) const {
	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials);
	getCombinationPartialDerivatives(partials);
	getDissociationPartialDerivatives(partials);
	getEmissionPartialDerivatives(partials);

	return;
}

void NECluster::getProductionPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int numReactants = 0, index = 0;
	double value = 0.0;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Production
	// A + B --> D, D being this cluster
	// The flux for D is
	// F(C_D) = k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_D)/dC_A = k+_(A,B)*C_B
	// dF(C_D)/dC_B = k+_(A,B)*C_A
<<<<<<< HEAD
	numReactants = reactingPairs.size();
	for (int i = 0; i < numReactants; i++) {
		// Compute the contribution from the first part of the reacting pair
		value = reactingPairs[i].reaction->kConstant
				* reactingPairs[i].second->getConcentration(
						reactingPairs[i].secondDistance);
		index = reactingPairs[i].first->id - 1;
		partials[index] += value;
		index = reactingPairs[i].first->xeMomId - 1;
		partials[index] += value * reactingPairs[i].firstDistance;
		// Compute the contribution from the second part of the reacting pair
		value = reactingPairs[i].reaction->kConstant
				* reactingPairs[i].first->getConcentration(
						reactingPairs[i].firstDistance);
		index = reactingPairs[i].second->id - 1;
		partials[index] += value;
		index = reactingPairs[i].second->xeMomId - 1;
		partials[index] += value * reactingPairs[i].secondDistance;
	}
=======
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[&partials](ClusterPair const& currPair) {

				Reaction const& currReaction = currPair.reaction;

				// Compute the contribution from the first part of the reacting pair
				auto value = currReaction.kConstant
				* currPair.second->getConcentration(
						currPair.secondDistance);
				auto index = currPair.first->id - 1;
				partials[index] += value;
				index = currPair.first->xeMomId - 1;
				partials[index] += value * currPair.firstDistance;
				// Compute the contribution from the second part of the reacting pair
				value = currReaction.kConstant
				* currPair.first->getConcentration(
						currPair.firstDistance);
				index = currPair.second->id - 1;
				partials[index] += value;
				index = currPair.second->xeMomId - 1;
				partials[index] += value * currPair.secondDistance;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NECluster::getCombinationPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int numReactants = 0, otherIndex = 0;
	NECluster *cluster = nullptr;
	double value = 0.0;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Combination
	// A + B --> D, A being this cluster
	// The flux for A is outgoing
	// F(C_A) = - k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k+_(A,B)*C_B
	// dF(C_A)/dC_B = - k+_(A,B)*C_A
<<<<<<< HEAD
	numReactants = combiningReactants.size();
	for (int i = 0; i < numReactants; i++) {
		cluster = (NECluster *) combiningReactants[i].combining;
		// Remember that the flux due to combinations is OUTGOING (-=)!
		// Compute the contribution from this cluster
		partials[id - 1] -= combiningReactants[i].reaction->kConstant
				* cluster->getConcentration(combiningReactants[i].distance);
		// Compute the contribution from the combining cluster
		value = combiningReactants[i].reaction->kConstant * concentration;
		// Get the index of cluster
		otherIndex = cluster->id - 1;
		partials[otherIndex] -= value;
		otherIndex = cluster->xeMomId - 1;
		partials[otherIndex] -= value * combiningReactants[i].distance;
	}
=======
	std::for_each(combiningReactants.begin(), combiningReactants.end(),
			[this,&partials](const CombiningCluster& cc) {

				NECluster const& cluster = cc.combining;
				Reaction const& currReaction = cc.reaction;

				// Remember that the flux due to combinations is OUTGOING (-=)!
				// Compute the contribution from this cluster
				partials[id - 1] -= currReaction.kConstant *
				cluster.getConcentration(cc.distance);
				// Compute the contribution from the combining cluster
				double value = currReaction.kConstant * concentration;

				partials[cluster.id - 1] -= value;
				partials[cluster.xeMomId - 1] -= value * cc.distance;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NECluster::getDissociationPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int numPairs = 0, index = 0;
	NECluster *cluster = nullptr;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Dissociation
	// A --> B + D, B being this cluster
	// The flux for B is
	// F(C_B) = k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_B)/dC_A = k-_(B,D)
<<<<<<< HEAD
	numPairs = dissociatingPairs.size();
	for (int i = 0; i < numPairs; i++) {
		// Get the dissociating cluster
		cluster = dissociatingPairs[i].first;
		index = cluster->id - 1;
		partials[index] += dissociatingPairs[i].reaction->kConstant;
		index = cluster->xeMomId - 1;
		partials[index] += dissociatingPairs[i].reaction->kConstant
				* dissociatingPairs[i].firstDistance;
	}
=======
	std::for_each(dissociatingPairs.begin(), dissociatingPairs.end(),
			[&partials](const ClusterPair& currPair) {
				// Get the dissociating cluster
				NECluster* cluster = currPair.first;
				Reaction const& currReaction = currPair.reaction;
				partials[cluster->id - 1] += currReaction.kConstant;
				partials[cluster->xeMomId - 1] += currReaction.kConstant *
				currPair.firstDistance;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NECluster::getEmissionPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int numPairs = 0, index = 0;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Emission
	// A --> B + D, A being this cluster
	// The flux for A is
	// F(C_A) = - k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k-_(B,D)
<<<<<<< HEAD
	numPairs = emissionPairs.size();
	for (int i = 0; i < numPairs; i++) {
		// Modify the partial derivative. Remember that the flux
		// due to emission is OUTGOING (-=)!
		index = id - 1;
		partials[index] -= emissionPairs[i].reaction->kConstant;
	}
=======
	double emissionFlux = std::accumulate(emissionPairs.begin(),
			emissionPairs.end(), 0.0,
			[](double running, const ClusterPair& currPair) {
				Reaction const& currReaction = currPair.reaction;
				return running + currReaction.kConstant;
			});

	// Recall emission flux is OUTGOING
	partials[id - 1] -= emissionFlux;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NECluster::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

void NECluster::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

double NECluster::getLeftSideRate() const {
<<<<<<< HEAD
	// Initialize the rate and the cluster pointer
	double totalRate = 0.0;
	NECluster *cluster = nullptr;

	// Loop on the combining reactants
	for (int i = 0; i < combiningReactants.size(); i++) {
		cluster = (NECluster *) combiningReactants[i].combining;
		// Add the rate to the total rate
		totalRate += combiningReactants[i].reaction->kConstant
				* cluster->concentration;
	}

	// Loop on the emission pairs
	for (int i = 0; i < emissionPairs.size(); i++) {
		// Add the rate to the total rate
		totalRate += emissionPairs[i].reaction->kConstant;
	}

	return totalRate;
}

std::vector<int> NECluster::getConnectivity() const {
	int connectivityLength = network->getDOF();
=======

	// Sum reaction rate contributions over all combining clusters.
	double combiningRateTotal = std::accumulate(combiningReactants.begin(),
			combiningReactants.end(), 0.0,
			[](double running, const CombiningCluster& currPair) {
				NECluster const& cluster = currPair.combining;
				Reaction const& currReaction = currPair.reaction;

				return running + (currReaction.kConstant *
						cluster.concentration);
			});

	// Sum reaction rate constants over all emission pairs.
	double emissionRateTotal = std::accumulate(emissionPairs.begin(),
			emissionPairs.end(), 0.0,
			[](double running, const ClusterPair& currPair) {
				Reaction const& currReaction = currPair.reaction;
				return running + currReaction.kConstant;
			});

	return combiningRateTotal + emissionRateTotal;
}

std::vector<int> NECluster::getConnectivity() const {
	int connectivityLength = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);
	auto reactionConnVector = getReactionConnectivity();
	auto dissociationConnVector = getDissociationConnectivity();

	// The reaction and dissociation vectors must have a length equal to the
	// number of clusters
	if (reactionConnVector.size() != (unsigned int) connectivityLength) {
		throw std::string("The reaction vector has an incorrect length");
	}
	if (dissociationConnVector.size() != (unsigned int) connectivityLength) {
		throw std::string("The dissociation vector has an incorrect length");
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
