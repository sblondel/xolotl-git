<<<<<<< HEAD
=======
#include <algorithm>
#include <cassert>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include "PSICluster.h"
#include <xolotlPerf.h>
#include <Constants.h>
#include <MathUtils.h>

using namespace xolotlCore;

<<<<<<< HEAD
PSICluster::PSICluster() :
		Reactant() {
	// Set the reactant name appropriately
	name = "PSICluster";
=======
void PSICluster::resultFrom(ProductionReaction& reaction, int a, int b, int c,
		int d) {

	// Add a cluster pair for the given reaction.
	reactingPairs.emplace_back(reaction,
			static_cast<PSICluster&>(reaction.first),
			static_cast<PSICluster&>(reaction.second));
	auto& newPair = reactingPairs.back();

	// NB: newPair's reactants are same as reaction's.
	// So use newPair only from here on.
	// TODO Any way to enforce this beyond splitting it into two functions?

	// Update the coefficients
	double firstHeDistance = 0.0, firstVDistance = 0.0, secondHeDistance = 0.0,
			secondVDistance = 0.0;
	if (newPair.first.getType() == ReactantType::PSISuper) {
		auto const& super = static_cast<PSICluster const&>(newPair.first);
		firstHeDistance = super.getHeDistance(c);
		firstVDistance = super.getVDistance(d);
	}
	if (newPair.second.getType() == ReactantType::PSISuper) {
		auto const& super = static_cast<PSICluster const&>(newPair.second);
		secondHeDistance = super.getHeDistance(c);
		secondVDistance = super.getVDistance(d);
	}
	newPair.a00 += 1.0;
	newPair.a10 += firstHeDistance;
	newPair.a20 += firstVDistance;
	newPair.a01 += secondHeDistance;
	newPair.a02 += secondVDistance;
	newPair.a11 += firstHeDistance * secondHeDistance;
	newPair.a12 += firstHeDistance * secondVDistance;
	newPair.a21 += firstVDistance * secondHeDistance;
	newPair.a22 += firstVDistance * secondVDistance;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
PSICluster::PSICluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		Reactant(registry) {
	// Set the reactant name appropriately
	name = "PSICluster";
=======
void PSICluster::resultFrom(ProductionReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {

	// Add a cluster pair for the given reaction.
	reactingPairs.emplace_back(reaction,
			static_cast<PSICluster&>(reaction.first),
			static_cast<PSICluster&>(reaction.second));
	auto& newPair = reactingPairs.back();

	// NB: newPair's reactants are same as reaction's.
	// So use newPair only from here on.
	// TODO Any way to enforce this beyond splitting it into two functions?

	// Update the coefficients
	std::for_each(prInfos.begin(), prInfos.end(),
			[&newPair](const PendingProductionReactionInfo& currPRI) {

				// Use names that correspond to single version.
				int a = currPRI.numHe;
				int b = currPRI.numV;
				int c = currPRI.i;
				int d = currPRI.j;

				double firstHeDistance = 0.0, firstVDistance = 0.0, secondHeDistance = 0.0,
				secondVDistance = 0.0;
				if (newPair.first.getType() == ReactantType::PSISuper) {
					auto const& super = static_cast<PSICluster const&>(newPair.first);
					firstHeDistance = super.getHeDistance(c);
					firstVDistance = super.getVDistance(d);
				}
				if (newPair.second.getType() == ReactantType::PSISuper) {
					auto const& super = static_cast<PSICluster const&>(newPair.second);
					secondHeDistance = super.getHeDistance(c);
					secondVDistance = super.getVDistance(d);
				}
				newPair.a00 += 1.0;
				newPair.a10 += firstHeDistance;
				newPair.a20 += firstVDistance;
				newPair.a01 += secondHeDistance;
				newPair.a02 += secondVDistance;
				newPair.a11 += firstHeDistance * secondHeDistance;
				newPair.a12 += firstHeDistance * secondVDistance;
				newPair.a21 += firstVDistance * secondHeDistance;
				newPair.a22 += firstVDistance * secondVDistance;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
// The copy constructor
PSICluster::PSICluster(PSICluster &other) :
		Reactant(other), reactingPairs(other.reactingPairs), combiningReactants(
				other.combiningReactants), dissociatingPairs(
				other.dissociatingPairs), emissionPairs(other.emissionPairs) {
	// Recompute all of the temperature-dependent quantities
	setTemperature(other.getTemperature());
=======
void PSICluster::participateIn(ProductionReaction& reaction, int a, int b) {
	// Look for the other cluster
	auto& otherCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if the reaction was already added
	std::vector<CombiningCluster>::reverse_iterator it;
	for (it = combiningReactants.rbegin(); it != combiningReactants.rend();
			++it) {
		if (&otherCluster == &(it->combining)) {
			break;
		}
	}
	if (it == combiningReactants.rend()) {
		// We did not already know about this combination.
		// Note that we combine with the other cluster in this reaction.
		combiningReactants.emplace_back(reaction, otherCluster);
		it = combiningReactants.rbegin();
	}

	// Update the coefficients
	double heDistance = 0.0, vDistance = 0.0;
	if (otherCluster.getType() == ReactantType::PSISuper) {
		heDistance = otherCluster.getHeDistance(a);
		vDistance = otherCluster.getVDistance(b);
	}
	(*it).a0 += 1.0;
	(*it).a1 += heDistance;
	(*it).a2 += vDistance;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
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
=======
void PSICluster::participateIn(ProductionReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {
	// Look for the other cluster
	auto& otherCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if the reaction was already added
	std::vector<CombiningCluster>::reverse_iterator it;
	for (it = combiningReactants.rbegin(); it != combiningReactants.rend();
			++it) {
		if (&otherCluster == &(it->combining)) {
			break;
		}
	}
	if (it == combiningReactants.rend()) {
		// We did not already know about this combination.
		// Note that we combine with the other cluster in this reaction.
		combiningReactants.emplace_back(reaction, otherCluster);
		it = combiningReactants.rbegin();
	}
	assert(it != combiningReactants.rend());
	auto& combCluster = *it;

	// Update the coefficients
	std::for_each(prInfos.begin(), prInfos.end(),
			[&otherCluster,&combCluster](const PendingProductionReactionInfo& currPRInfo) {

				// Use names corresponding to the single-item version.
				int a = currPRInfo.i;
				int b = currPRInfo.j;

				double heDistance = 0.0, vDistance = 0.0;
				if (otherCluster.getType() == ReactantType::PSISuper) {
					heDistance = otherCluster.getHeDistance(a);
					vDistance = otherCluster.getVDistance(b);
				}
				combCluster.a0 += 1.0;
				combCluster.a1 += heDistance;
				combCluster.a2 += vDistance;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
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
=======
void PSICluster::participateIn(DissociationReaction& reaction, int a, int b,
		int c, int d) {
	// Look for the other cluster
	auto& emittedCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if the reaction was already added
	auto it =
			std::find_if(dissociatingPairs.rbegin(), dissociatingPairs.rend(),
					[&reaction,&emittedCluster](const ClusterPair& currPair) {
						return (&(reaction.dissociating) == &static_cast<PSICluster&>(currPair.first)) and
						(&emittedCluster == &static_cast<PSICluster&>(currPair.second));

					});
	if (it == dissociatingPairs.rend()) {

		// We did not already know about it.
		// Add the pair of them where it is important that the
		// dissociating cluster is the first one
		dissociatingPairs.emplace_back(reaction,
				static_cast<PSICluster&>(reaction.dissociating),
				static_cast<PSICluster&>(emittedCluster));
		it = dissociatingPairs.rbegin();
	}

	// Update the coefficients
	double firstHeDistance = 0.0, firstVDistance = 0.0;
	if (reaction.dissociating.getType() == ReactantType::PSISuper) {
		auto const& super = static_cast<PSICluster&>(reaction.dissociating);
		firstHeDistance = super.getHeDistance(a);
		firstVDistance = super.getVDistance(b);
	}
	(*it).a00 += 1.0;
	(*it).a10 += firstHeDistance;
	(*it).a20 += firstVDistance;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
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
=======
void PSICluster::participateIn(DissociationReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {
	// Look for the other cluster
	auto& emittedCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if the reaction was already added
	auto it =
			std::find_if(dissociatingPairs.rbegin(), dissociatingPairs.rend(),
					[&reaction,&emittedCluster](const ClusterPair& currPair) {
						return (&(reaction.dissociating) == &static_cast<PSICluster&>(currPair.first)) and
						(&emittedCluster == &static_cast<PSICluster&>(currPair.second));

					});
	if (it == dissociatingPairs.rend()) {

		// We did not already know about it.
		// Add the pair of them where it is important that the
		// dissociating cluster is the first one
		dissociatingPairs.emplace_back(reaction,
				static_cast<PSICluster&>(reaction.dissociating),
				static_cast<PSICluster&>(emittedCluster));
		it = dissociatingPairs.rbegin();
	}
	assert(it != dissociatingPairs.rend());
	auto& currPair = *it;

	// Update the coefficients
	std::for_each(prInfos.begin(), prInfos.end(),
			[&currPair,&reaction](const PendingProductionReactionInfo& currPRI) {

				// Use names corresponding to the single-item version.
				int a = currPRI.numHe;
				int b = currPRI.numV;

				double firstHeDistance = 0.0, firstVDistance = 0.0;
				if (reaction.dissociating.getType() == ReactantType::PSISuper) {
					auto const& super = static_cast<PSICluster&>(reaction.dissociating);
					firstHeDistance = super.getHeDistance(a);
					firstVDistance = super.getVDistance(b);
				}
				currPair.a00 += 1.0;
				currPair.a10 += firstHeDistance;
				currPair.a20 += firstVDistance;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
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
void PSICluster::emitFrom(DissociationReaction& reaction, int a, int b, int c,
		int d) {

	// Note that we emit from the reaction's reactants according to
	// the given reaction.
	// TODO do we need to check to see whether we already know about
	// this reaction?
	emissionPairs.emplace_back(reaction,
			static_cast<PSICluster&>(reaction.first),
			static_cast<PSICluster&>(reaction.second));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
<<<<<<< HEAD

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
<<<<<<< HEAD
			}
			else {
				// Check the distance
				if (std::distance(it, itBis) > 1) break;
=======
			} else {
				// Check the distance
				if (std::distance(it, itBis) > 1)
					break;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
				itBis++;
			}
		}
=======
>>>>>>> master
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
<<<<<<< HEAD

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
<<<<<<< HEAD
			}
			else {
				// Check the distance
				if (std::distance(it, itBis) > 1) break;
=======
			} else {
				// Check the distance
				if (std::distance(it, itBis) > 1)
					break;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
				itBis++;
			}
		}
=======
>>>>>>> master
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
<<<<<<< HEAD

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
<<<<<<< HEAD
			}
			else {
				// Check the distance
				if (std::distance(it, itBis) > 1) break;
=======
			} else {
				// Check the distance
				if (std::distance(it, itBis) > 1)
					break;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
				itBis++;
			}
		}
=======
>>>>>>> master
	}

	for (auto it = emissionPairs.begin(); it != emissionPairs.end(); it++) {
		// Create the corresponding dissociation reaction
		auto newReaction = std::make_shared<DissociationReaction>(this,
				(*it).first, (*it).second);
		// Add it to the network
		newReaction = network->addDissociationReaction(newReaction);
		// Link it to the pair
		(*it).reaction = newReaction;
<<<<<<< HEAD

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
<<<<<<< HEAD
			}
			else {
				// Check the distance
				if (std::distance(it, itBis) > 1) break;
=======
			} else {
				// Check the distance
				if (std::distance(it, itBis) > 1)
					break;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
				itBis++;
			}
		}
=======
>>>>>>> master
	}
=======
void PSICluster::emitFrom(DissociationReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {

	// Note that we emit from the reaction's reactants according to
	// the given reaction.
	// TODO do we need to check to see whether we already know about
	// this reaction?
	emissionPairs.emplace_back(reaction,
			static_cast<PSICluster&>(reaction.first),
			static_cast<PSICluster&>(reaction.second));
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
		connectivity[*it - 1] = 1;
	}

	return connectivity;
}

std::vector<int> PSICluster::getReactionConnectivity() const {
	// Create the full vector from the set and return it
<<<<<<< HEAD
	return getFullConnectivityVector(reactionConnectivitySet, network->getDOF());
=======
	return getFullConnectivityVector(reactionConnectivitySet, network.getDOF());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

std::vector<int> PSICluster::getDissociationConnectivity() const {
	// Create the full vector from the set and return it
	return getFullConnectivityVector(dissociationConnectivitySet,
<<<<<<< HEAD
			network->getDOF());
=======
			network.getDOF());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
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
<<<<<<< HEAD
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
=======
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[this](const ClusterPair& currPair) {
				// The cluster is connecting to both clusters in the pair
				setReactionConnectivity(currPair.first.id);
				setReactionConnectivity(currPair.second.id);
				setReactionConnectivity(currPair.first.heMomId);
				setReactionConnectivity(currPair.second.heMomId);
				setReactionConnectivity(currPair.first.vMomId);
				setReactionConnectivity(currPair.second.vMomId);
			});

	// Loop on the effective combining reactants
	std::for_each(combiningReactants.begin(), combiningReactants.end(),
			[this](const CombiningCluster& cc) {
				// The cluster is connecting to the combining cluster
				setReactionConnectivity(cc.combining.id);
				setReactionConnectivity(cc.combining.heMomId);
				setReactionConnectivity(cc.combining.vMomId);
			});

	// Loop on the effective dissociating pairs
	std::for_each(dissociatingPairs.begin(), dissociatingPairs.end(),
			[this](const ClusterPair& currPair) {
				// The cluster is connecting to the dissociating cluster which
				// is the first one by definition
				setDissociationConnectivity(currPair.first.id);
				setDissociationConnectivity(currPair.first.heMomId);
				setDissociationConnectivity(currPair.first.vMomId);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Don't loop on the effective emission pairs because
	// this cluster is not connected to them

	return;
}

<<<<<<< HEAD
void PSICluster::setReactionNetwork(
		const std::shared_ptr<IReactionNetwork> reactionNetwork) {
	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);
=======
void PSICluster::updateFromNetwork() {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
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

	return prodFlux - combFlux + dissFlux - emissFlux;
}

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
double PSICluster::getDissociationFlux() const {
<<<<<<< HEAD
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
=======

	// Sum dissociation flux over all our dissociating clusters.
	double flux = std::accumulate(dissociatingPairs.begin(),
			dissociatingPairs.end(), 0.0,
			[](double running, const ClusterPair& currPair) {
				auto const& dissCluster = currPair.first;
				double l0A = dissCluster.getConcentration(0.0, 0.0);
				double lHeA = dissCluster.getHeMomentum();
				double lVA = dissCluster.getVMomentum();

				// Calculate the Dissociation flux
				return running +
				(currPair.reaction.kConstant *
						(currPair.a00 * l0A +
								currPair.a10 * lHeA +
								currPair.a20 * lVA));
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Return the flux
	return flux;
}

double PSICluster::getEmissionFlux() const {
<<<<<<< HEAD
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
=======

	// Sum rate constants from all emission pair reactions.
	double flux = std::accumulate(emissionPairs.begin(), emissionPairs.end(),
			0.0, [](double running, const ClusterPair& currPair) {
				return running + currPair.reaction.kConstant;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return flux * concentration;
}

double PSICluster::getProductionFlux() const {
<<<<<<< HEAD
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
	}
=======

	// Sum production flux over all reacting pairs.
	double flux = std::accumulate(reactingPairs.begin(), reactingPairs.end(),
			0.0, [](double running, const ClusterPair& currPair) {

				// Get the two reacting clusters
			auto const& firstReactant = currPair.first;
			auto const& secondReactant = currPair.second;
			double l0A = firstReactant.getConcentration(0.0, 0.0);
			double l0B = secondReactant.getConcentration(0.0, 0.0);
			double lHeA = firstReactant.getHeMomentum();
			double lHeB = secondReactant.getHeMomentum();
			double lVA = firstReactant.getVMomentum();
			double lVB = secondReactant.getVMomentum();
			// Update the flux
			return running + currPair.reaction.kConstant *
			(currPair.a00 * l0A * l0B + currPair.a01 * l0A * lHeB +
					currPair.a02 * l0A * lVB + currPair.a10 * lHeA * l0B +
					currPair.a11 * lHeA * lHeB + currPair.a12 * lHeA * lVB +
					currPair.a20 * lVA * l0B + currPair.a21 * lVA * lHeB +
					currPair.a22 * lVA * lVB);
		});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Return the production flux
	return flux;
}

double PSICluster::getCombinationFlux() const {
<<<<<<< HEAD
	// Local declarations
	double flux = 0.0;
	int nReactants = 0;
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
	}
=======

	// Sum combination flux over all clusters that combine with us.
	double flux = std::accumulate(combiningReactants.begin(),
			combiningReactants.end(), 0.0,
			[](double running, const CombiningCluster& cc) {

				// Get the cluster that combines with this one
				auto const& combiningCluster = cc.combining;
				double l0B = combiningCluster.getConcentration(0.0, 0.0);
				double lHeB = combiningCluster.getHeMomentum();
				double lVB = combiningCluster.getVMomentum();
				// Calculate the combination flux
				return running + (cc.reaction.kConstant *
						(cc.a0 * l0B + cc.a1 * lHeB + cc.a2 * lVB));

			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return flux * concentration;
}

std::vector<double> PSICluster::getPartialDerivatives() const {
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
=======
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[&partials](const ClusterPair& currPair) {
				// Get the two reacting clusters
				auto const& firstReactant = currPair.first;
				auto const& secondReactant = currPair.second;
				double l0A = firstReactant.getConcentration(0.0, 0.0);
				double l0B = secondReactant.getConcentration(0.0, 0.0);
				double lHeA = firstReactant.getHeMomentum();
				double lHeB = secondReactant.getHeMomentum();
				double lVA = firstReactant.getVMomentum();
				double lVB = secondReactant.getVMomentum();

				// Compute contribution from the first part of the reacting pair
				double value = currPair.reaction.kConstant;

				partials[firstReactant.id - 1] += value *
				(currPair.a00 * l0B + currPair.a01 * lHeB + currPair.a02 * lVB);

				partials[firstReactant.heMomId - 1] += value *
				(currPair.a10 * l0B + currPair.a11 * lHeB + currPair.a12 * lVB);

				partials[firstReactant.vMomId - 1] += value *
				(currPair.a20 * l0B + currPair.a21 * lHeB + currPair.a22 * lVB);

				// Compute contribution from the second part of the reacting pair
				partials[secondReactant.id - 1] += value *
				(currPair.a00 * l0A + currPair.a10 * lHeA + currPair.a20 * lVA);

				partials[secondReactant.heMomId - 1] += value *
				(currPair.a01 * l0A + currPair.a11 * lHeA + currPair.a21 * lVA);

				partials[secondReactant.vMomId - 1] += value *
				(currPair.a02 * l0A + currPair.a12 * lHeA + currPair.a22 * lVA);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSICluster::getCombinationPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int numReactants = 0, otherIndex = 0;
	PSICluster *cluster = nullptr;
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
=======
	std::for_each(combiningReactants.begin(), combiningReactants.end(),
			[this,&partials](const CombiningCluster& cc) {
				auto const& cluster = cc.combining;
				double l0B = cluster.getConcentration(0.0, 0.0);
				double lHeB = cluster.getHeMomentum();
				double lVB = cluster.getVMomentum();

				// Remember that the flux due to combinations is OUTGOING (-=)!
				// Compute the contribution from this cluster
				partials[id - 1] -= cc.reaction.kConstant
				* (cc.a0 * l0B + cc.a1 * lHeB + cc.a2 * lVB);
				// Compute the contribution from the combining cluster
				double value = cc.reaction.kConstant * concentration;
				partials[cluster.id - 1] -= value * cc.a0;
				partials[cluster.heMomId - 1] -= value * cc.a1;
				partials[cluster.vMomId - 1] -= value * cc.a2;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSICluster::getDissociationPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int numPairs = 0, index = 0;
	PSICluster *cluster = nullptr;
	double value = 0.0;
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
		value = dissociatingPairs[i].reaction->kConstant
				* (double) dissociatingPairs[i].multiplicity;
		index = cluster->id - 1;
		partials[index] += value;
		index = cluster->heMomId - 1;
		partials[index] += value * dissociatingPairs[i].firstHeDistance;
		index = cluster->vMomId - 1;
		partials[index] += value * dissociatingPairs[i].firstVDistance;
	}
=======
	std::for_each(dissociatingPairs.begin(), dissociatingPairs.end(),
			[&partials](const ClusterPair& currPair) {
				// Get the dissociating cluster
				auto const& cluster = currPair.first;
				double value = currPair.reaction.kConstant;
				partials[cluster.id - 1] += value * currPair.a00;
				partials[cluster.heMomId - 1] += value * currPair.a10;
				partials[cluster.vMomId - 1] += value * currPair.a20;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSICluster::getEmissionPartialDerivatives(
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
		partials[index] -= emissionPairs[i].reaction->kConstant
				* (double) emissionPairs[i].multiplicity;
	}
=======
	double outgoingFlux = std::accumulate(emissionPairs.begin(),
			emissionPairs.end(), 0.0,
			[](double running, const ClusterPair& currPair) {
				return running + currPair.reaction.kConstant;
			});
	partials[id - 1] -= outgoingFlux;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSICluster::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

void PSICluster::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

double PSICluster::getLeftSideRate() const {
<<<<<<< HEAD
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

	// Sum rate constant-concentration product over combining reactants.
	double combiningRateTotal = std::accumulate(combiningReactants.begin(),
			combiningReactants.end(), 0.0,
			[](double running, const CombiningCluster& cc) {
				return running +
				(cc.reaction.kConstant * cc.combining.concentration);
			});

	// Sum rate constants over all emission pair reactions.
	double emissionRateTotal = std::accumulate(emissionPairs.begin(),
			emissionPairs.end(), 0.0,
			[](double running, const ClusterPair& currPair) {
				return running + currPair.reaction.kConstant;
			});

	return combiningRateTotal + emissionRateTotal;
}

std::vector<int> PSICluster::getConnectivity() const {
	int connectivityLength = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);
	auto reactionConnVector = getReactionConnectivity();
	auto dissociationConnVector = getDissociationConnectivity();

	// The reaction and dissociation vectors must have a length equal to the
	// number of clusters
	if (reactionConnVector.size() != (unsigned int) connectivityLength) {
		throw std::string("The reaction vector is an incorrect length");
	}
	if (dissociationConnVector.size() != (unsigned int) connectivityLength) {
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
=======

void PSICluster::dumpCoefficients(std::ostream& os,
		PSICluster::ClusterPair const& curr) const {

	os << "a[0-2][0-2]: " << ' ' << curr.a00 << ' ' << curr.a01 << ' '
			<< curr.a02 << ' ' << curr.a10 << ' ' << curr.a11 << ' ' << curr.a12
			<< ' ' << curr.a20 << ' ' << curr.a21 << ' ' << curr.a22;
}

void PSICluster::dumpCoefficients(std::ostream& os,
		PSICluster::CombiningCluster const& curr) const {

	os << "a[0-2]: " << curr.a0 << ' ' << curr.a1 << ' ' << curr.a2;
}

void PSICluster::outputCoefficientsTo(std::ostream& os) const {

	os << "id: " << id << '\n';
	os << "reacting: " << reactingPairs.size() << '\n';
	std::for_each(reactingPairs.begin(), reactingPairs.end(),
			[this,&os](ClusterPair const& currPair) {
				os << "first: " << currPair.first.getId()
				<< "; second: " << currPair.second.getId()
				<< "; ";
				dumpCoefficients(os, currPair);
				os << '\n';
			});

	os << "combining: " << combiningReactants.size() << '\n';
	std::for_each(combiningReactants.begin(), combiningReactants.end(),
			[this,&os](CombiningCluster const& currCluster) {
				os << "other: " << currCluster.combining.getId()
				<< "; ";
				dumpCoefficients(os, currCluster);
				os << '\n';
			});

	os << "dissociating: " << dissociatingPairs.size() << '\n';
	std::for_each(dissociatingPairs.begin(), dissociatingPairs.end(),
			[this,&os](ClusterPair const& currPair) {
				os << "first: " << currPair.first.getId()
				<< "; second: " << currPair.second.getId()
				<< "; ";
				dumpCoefficients(os, currPair);
				os << '\n';
			});

	os << "emitting: " << emissionPairs.size() << '\n';
	std::for_each(emissionPairs.begin(), emissionPairs.end(),
			[this,&os](ClusterPair const& currPair) {
				os << "first: " << currPair.first.getId()
				<< "; second: " << currPair.second.getId()
				<< "; ";
				dumpCoefficients(os, currPair);
				os << '\n';
			});
}

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
