// Includes
#include "NESuperCluster.h"
#include "NEClusterReactionNetwork.h"
#include <Constants.h>
#include <MathUtils.h>

using namespace xolotlCore;

/**
 * The xenon momentum partials.
 */
std::vector<double> momentumPartials;

NESuperCluster::NESuperCluster(double num, int nTot, int width, double radius,
<<<<<<< HEAD
		double energy, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		NECluster(registry), numXe(num), nTot(nTot), l0(0.0), l1(0.0), dispersion(
				0.0), momentumFlux(0.0) {
=======
		double energy, IReactionNetwork& _network,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		NECluster(_network, registry, buildName(num)), numXe(num), nTot(nTot), l0(
				0.0), l1(0.0), dispersion(0.0), momentumFlux(0.0) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Set the cluster size
	size = (int) numXe;

	// Update the composition map
<<<<<<< HEAD
	compositionMap[xeType] = (int) (numXe * (double) nTot);
=======
	composition[toCompIdx(Species::Xe)] = (int) (numXe * (double) nTot);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Set the width
	sectionWidth = width;

	// Set the reaction radius and formation energy
	reactionRadius = radius;
	formationEnergy = energy;

	// Set the diffusion factor and the migration energy
	migrationEnergy = std::numeric_limits<double>::infinity();
	diffusionFactor = 0.0;

<<<<<<< HEAD
	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "Xe_" << numXe;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = "NESuper";
=======
	// Set the typename appropriately
	type = ReactantType::NESuper;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
NESuperCluster::NESuperCluster(NESuperCluster &other) :
		NECluster(other) {
	numXe = other.numXe;
	nTot = other.nTot;
	sectionWidth = other.sectionWidth;
	l0 = other.l0;
	l1 = other.l1;
	dispersion = other.dispersion;
	reactingMap = other.reactingMap;
	combiningMap = other.combiningMap;
	dissociatingMap = other.dissociatingMap;
	emissionMap = other.emissionMap;
	effReactingList = other.effReactingList;
	effCombiningList = other.effCombiningList;
	effDissociatingList = other.effDissociatingList;
	effEmissionList = other.effEmissionList;
	momentumFlux = other.momentumFlux;

	return;
}

std::shared_ptr<IReactant> NESuperCluster::clone() {
	std::shared_ptr<IReactant> reactant(new NESuperCluster(*this));

	return reactant;
}

void NESuperCluster::setReactionNetwork(
		const std::shared_ptr<IReactionNetwork> reactionNetwork) {
	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);
=======
void NESuperCluster::updateFromNetwork() {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

	// Aggregate the reacting pairs and combining reactants from the xeVector
	// Loop on the xeVector
	for (int i = 0; i < xeVector.size(); i++) {
		// Get the cluster size
		double size = xeVector[i]->getSize();
		// Get all vectors
		auto react = xeVector[i]->reactingPairs;
		auto combi = xeVector[i]->combiningReactants;
		auto disso = xeVector[i]->dissociatingPairs;
		auto emi = xeVector[i]->emissionPairs;

		// Set them in the super cluster map
		reactingMap[size] = react;
		combiningMap[size] = combi;
		dissociatingMap[size] = disso;
		emissionMap[size] = emi;
	}

	// Compute the dispersion
	computeDispersion();

	return;
}

double NESuperCluster::getConcentration(double distXe, double distB) const {
	return l0 + (distXe * l1);
}

double NESuperCluster::getMomentum() const {
	return l1;
}

double NESuperCluster::getTotalConcentration() const {
	// Initial declarations
	int index = 0;
	double distance = 0.0, conc = 0.0;

	// Loop on the xenon width
	for (int k = 0; k < sectionWidth; k++) {
		// Compute the xenon index
		index = (int) (numXe - (double) sectionWidth / 2.0) + k + 1;

		// Check if this cluster exists
		if (reactingMap.find(index) == reactingMap.end())
			continue;

		// Compute the distances
		distance = getDistance(index);

		// Add the concentration of each cluster in the group
		conc += getConcentration(distance);
	}

	return conc;
}

double NESuperCluster::getTotalXenonConcentration() const {
	// Initial declarations
	int index = 0;
	double distance = 0.0, conc = 0.0;

	// Loop on the xenon width
	for (int k = 0; k < sectionWidth; k++) {
		// Compute the xenon index
		index = (int) (numXe - (double) sectionWidth / 2.0) + k + 1;

		// Check if this cluster exists
		if (reactingMap.find(index) == reactingMap.end())
			continue;

		// Compute the distances
		distance = getDistance(index);

		// Add the concentration of each cluster in the group times the number of xenon atoms
		conc += getConcentration(distance) * (double) index;
	}

	return conc;
}

double NESuperCluster::getDistance(int xe) const {
	if (sectionWidth == 1)
		return 0.0;
	return 2.0 * (double) (xe - numXe) / ((double) sectionWidth - 1.0);
}

void NESuperCluster::computeDispersion() {
	// Local declarations
	NECluster *firstReactant, *secondReactant, *combiningReactant,
			*dissociatingCluster, *otherEmittedCluster, *firstCluster,
			*secondCluster;
	double rate = 0.0;
	int index = 0;
	// Initialize the dispersion sum
	double nXeSquare = 0.0;

	// Loop on the xenon width
	for (int k = 0; k < sectionWidth; k++) {
		// Compute the vacancy index
		index = (int) (numXe - (double) sectionWidth / 2.0) + k + 1;

		// Check if this cluster exists
		if (reactingMap.find(index) == reactingMap.end())
			continue;

		// Compute nSquare for the dispersion
		nXeSquare += (double) index * index;
	}

	// Compute the dispersion
	if (sectionWidth == 1)
		dispersion = 1.0;
	else {
		dispersion = 2.0
				* (nXeSquare
<<<<<<< HEAD
						- ((double) compositionMap[xeType]
								* ((double) compositionMap[xeType]
=======
						- ((double) composition[toCompIdx(Species::Xe)]
								* ((double) composition[toCompIdx(Species::Xe)]
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
										/ (double) sectionWidth)))
				/ ((double) (sectionWidth * (sectionWidth - 1)));
	}

	return;
}

void NESuperCluster::optimizeReactions() {
	// Local declarations
	double factor = 0.0, distance = 0.0;
<<<<<<< HEAD
	NECluster *firstReactant, *secondReactant, *combiningReactant,
			*dissociatingCluster, *otherEmittedCluster, *firstCluster,
			*secondCluster;
=======
	NECluster *firstReactant, *secondReactant, *dissociatingCluster,
			*otherEmittedCluster, *firstCluster, *secondCluster;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	int index = 0;

	// Loop on the reacting map
	for (auto mapIt = reactingMap.begin(); mapIt != reactingMap.end();
			++mapIt) {
		// Get the pairs
		auto pairs = mapIt->second;
		// Loop over all the reacting pairs
		for (auto it = pairs.begin(); it != pairs.end();) {
			// Get the two reacting clusters
			firstReactant = (*it).first;
			secondReactant = (*it).second;

			// Create the corresponding production reaction
<<<<<<< HEAD
			auto reaction = std::make_shared<ProductionReaction>(firstReactant,
					secondReactant);
			// Add it to the network
			reaction = network->addProductionReaction(reaction);

			// Create a new SuperClusterProductionPair
			SuperClusterProductionPair superPair(firstReactant, secondReactant,
					reaction.get());
=======
			std::unique_ptr<ProductionReaction> reaction(
					new ProductionReaction(*firstReactant, *secondReactant));
			// Add it to the network
			auto& prref = network.add(std::move(reaction));

			// Create a new SuperClusterProductionPair
			SuperClusterProductionPair superPair(firstReactant, secondReactant,
					&prref);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != reactingMap.end();
					++mapItBis) {
				// Compute the xenon index
				index = mapItBis->first;
				factor = (double) (index - numXe) / dispersion;

				// Get the pairs
				auto pairsBis = mapItBis->second;
				// Set the total number of reactants that produce to form this one
				// Loop over all the reacting pairs
				for (auto itBis = pairsBis.begin(); itBis != pairsBis.end();) {
					// Get the two reacting clusters
					auto firstReactantBis = (*itBis).first;
					auto secondReactantBis = (*itBis).second;

					// Check if it is the same reaction
					if (firstReactantBis == firstReactant
							&& secondReactantBis == secondReactant) {
						superPair.a000 += 1.0;
						superPair.a001 += factor;
						superPair.a100 += (*itBis).firstDistance;
						superPair.a101 += (*itBis).firstDistance * factor;
						superPair.a010 += (*itBis).secondDistance;
						superPair.a011 += (*itBis).secondDistance * factor;
						superPair.a110 += (*itBis).firstDistance
								* (*itBis).secondDistance;
						superPair.a111 += (*itBis).firstDistance
								* (*itBis).secondDistance * factor;

						// Do not delete the element if it is the original one
						if (itBis == it) {
							++itBis;
							continue;
						}

						// Remove the reaction from the vector
						itBis = pairsBis.erase(itBis);
					}
					// Go to the next element
					else
						++itBis;
				}

				// Give back the pairs
				mapItBis->second = pairsBis;
			}

			// Add the super pair
			effReactingList.push_front(superPair);

			// Remove the reaction from the vector
			it = pairs.erase(it);
		}
	}

	// Loop on the combining map
	for (auto mapIt = combiningMap.begin(); mapIt != combiningMap.end();
			++mapIt) {
		// Get the pairs
		auto clusters = mapIt->second;
<<<<<<< HEAD
		// Loop over all the reacting pairs
		for (auto it = clusters.begin(); it != clusters.end();) {
			// Get the combining cluster
			combiningReactant = (*it).combining;

			// Create the corresponding production reaction
			auto reaction = std::make_shared<ProductionReaction>(this,
					combiningReactant);
			// Add it to the network
			reaction = network->addProductionReaction(reaction);

			// Create a new SuperClusterProductionPair with NULL as the second cluster because
			// we do not need it
			SuperClusterProductionPair superPair(combiningReactant, NULL,
					reaction.get());
=======

		// Loop over all the reacting pairs
		for (auto it = clusters.begin(); it != clusters.end();) {
			// Get the combining cluster
			NECluster& combiningReactant = (*it).combining;

			// Create the corresponding production reaction
			std::unique_ptr<ProductionReaction> reaction(
					new ProductionReaction(*this, combiningReactant));
			// Add it to the network
			auto& prref = network.add(std::move(reaction));

			// Create a new SuperClusterProductionPair with NULL as the second cluster because
			// we do not need it
			SuperClusterProductionPair superPair(&combiningReactant, nullptr,
					&prref);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != combiningMap.end();
					++mapItBis) {
				// Compute the xenon index
				index = mapItBis->first;
				distance = getDistance(index);
				factor = (double) (index - numXe) / dispersion;

<<<<<<< HEAD
				// Get the pairs
				auto clustersBis = mapItBis->second;
				// Set the total number of reactants that produce to form this one
				// Loop over all the reacting pairs
				for (auto itBis = clustersBis.begin();
						itBis != clustersBis.end();) {
					// Get the two reacting clusters
					auto combiningReactantBis = (*itBis).combining;

					// Check if it is the same reaction
					if (combiningReactantBis == combiningReactant) {
=======
				// Access the combining pairs
				auto& clustersBis = mapItBis->second;

				// Set the total number of reactants that produce to 
				// form this one.
				// May involve removing items from the vector of
				// combining cluster objects (clusersBis).
				// To avoid invalidating iterators into this vector,
				// we use the idiom of noting which need to get deleted,
				// a std::remove_if to move the doomed ones to the end
				// of the vector, and then erase to remove them.
				std::set<CombiningCluster*> doomedCombining;
				for (auto itBis = clustersBis.begin();
						itBis != clustersBis.end(); ++itBis) {

					// Access the current combining cluster
					NECluster& combiningReactantBis = (*itBis).combining;

					// Check if it is the same reaction
					if (&combiningReactantBis == &combiningReactant) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
						superPair.a000 += 1.0;
						superPair.a001 += factor;
						superPair.a010 += (*itBis).distance;
						superPair.a011 += (*itBis).distance * factor;
						superPair.a100 += distance;
						superPair.a101 += distance * factor;
						superPair.a110 += (*itBis).distance * distance;
						superPair.a111 += (*itBis).distance * distance * factor;

<<<<<<< HEAD
						// Do not delete the element if it is the original one
						if (itBis == it) {
							++itBis;
							continue;
						}

						// Remove the reaction from the vector
						itBis = clustersBis.erase(itBis);
					}
					// Go to the next element
					else
						++itBis;
				}

				// Give back the pairs
				mapItBis->second = clustersBis;
=======
						// Determine if we need to delete this item.
						// Do not delete if it is the original one.
						if (itBis != it) {
							// It is not the original one, so indicate it
							// needs to be removed.
							// NB: The expression with &(*iter) seems odd -
							// why not just use itBis?  We want the
							// address of the object, and itBis is an
							// iterator, not the address of the object itself.
							// So we dereference the iterator to access
							// the object, then take its address.
							doomedCombining.emplace(&(*itBis));
						}
					}
				}

				// Now that we know which combining clusters to delete,
				// Move them all to the end of the vector.
				auto firstToRemoveIter = std::remove_if(clustersBis.begin(),
						clustersBis.end(),
						[&doomedCombining](CombiningCluster& currCombining) {
							// See if currCombiningPair is in our set
							// of doomed items.
							auto diter = doomedCombining.find(&currCombining);
							return (diter != doomedCombining.end());
						});
				// Now that the doomed are all moved to be contiguous
				// and at the end of the vector, erase them.
				clustersBis.erase(firstToRemoveIter, clustersBis.end());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			}

			// Add the super pair
			effCombiningList.push_front(superPair);

			// Remove the reaction from the vector
			it = clusters.erase(it);
		}
	}

	// Loop on the dissociating map
	for (auto mapIt = dissociatingMap.begin(); mapIt != dissociatingMap.end();
			++mapIt) {
		// Get the pairs
		auto pairs = mapIt->second;
		// Loop over all the reacting pairs
		for (auto it = pairs.begin(); it != pairs.end();) {
			// Get the two reacting clusters
			dissociatingCluster = (*it).first;
			otherEmittedCluster = (*it).second;

			// Create a dissociation reaction
<<<<<<< HEAD
			auto reaction = std::make_shared<DissociationReaction>(
					dissociatingCluster, this, otherEmittedCluster);
			// Add it to the network
			reaction = network->addDissociationReaction(reaction);

			// Create a new SuperClusterProductionPair
			SuperClusterDissociationPair superPair(dissociatingCluster,
					otherEmittedCluster, reaction.get());
=======
			std::unique_ptr<DissociationReaction> reaction(
					new DissociationReaction(*dissociatingCluster, *this,
							*otherEmittedCluster));
			// Add it to the network
			auto& drref = network.add(std::move(reaction));

			// Create a new SuperClusterProductionPair
			SuperClusterDissociationPair superPair(dissociatingCluster,
					otherEmittedCluster, &drref);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != dissociatingMap.end();
					++mapItBis) {
				// Compute the xenon index
				index = mapItBis->first;
				factor = (double) (index - numXe) / dispersion;

				// Get the pairs
				auto pairsBis = mapItBis->second;
				// Set the total number of reactants that produce to form this one
				// Loop over all the reacting pairs
				for (auto itBis = pairsBis.begin(); itBis != pairsBis.end();) {
					// Get the two reacting clusters
					auto dissociatingClusterBis = (*itBis).first;
					auto otherEmittedClusterBis = (*itBis).second;

					// Check if it is the same reaction
					if (dissociatingClusterBis == dissociatingCluster
							&& otherEmittedClusterBis == otherEmittedCluster) {
						superPair.a00 += 1.0;
						superPair.a01 += factor;
						superPair.a10 += (*itBis).firstDistance;
						superPair.a11 += (*itBis).firstDistance * factor;

						// Do not delete the element if it is the original one
						if (itBis == it) {
							++itBis;
							continue;
						}

						// Remove the reaction from the vector
						itBis = pairsBis.erase(itBis);
					}
					// Go to the next element
					else
						++itBis;
				}

				// Give back the pairs
				mapItBis->second = pairsBis;
			}

			// Add the super pair
			effDissociatingList.push_front(superPair);

			// Remove the reaction from the vector
			it = pairs.erase(it);
		}
	}

	// Loop on the emission map
	for (auto mapIt = emissionMap.begin(); mapIt != emissionMap.end();
			++mapIt) {
		// Get the pairs
		auto pairs = mapIt->second;
		// Loop over all the reacting pairs
		for (auto it = pairs.begin(); it != pairs.end();) {
			// Get the two reacting clusters
			firstCluster = (*it).first;
			secondCluster = (*it).second;

			// Create a dissociation reaction
<<<<<<< HEAD
			auto reaction = std::make_shared<DissociationReaction>(this,
					firstCluster, secondCluster);
			// Add it to the network
			reaction = network->addDissociationReaction(reaction);

			// Create a new SuperClusterProductionPair
			SuperClusterDissociationPair superPair(firstCluster, secondCluster,
					reaction.get());
=======
			std::unique_ptr<DissociationReaction> reaction(
					new DissociationReaction(*this, *firstCluster,
							*secondCluster));
			// Add it to the network
			auto& drref = network.add(std::move(reaction));

			// Create a new SuperClusterProductionPair
			SuperClusterDissociationPair superPair(firstCluster, secondCluster,
					&drref);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != emissionMap.end();
					++mapItBis) {
				// Compute the xenon index
				index = mapItBis->first;
				distance = getDistance(index);
				factor = (double) (index - numXe) / dispersion;

				// Get the pairs
				auto pairsBis = mapItBis->second;
				// Set the total number of reactants that produce to form this one
				// Loop over all the reacting pairs
				for (auto itBis = pairsBis.begin(); itBis != pairsBis.end();) {
					// Get the two reacting clusters
					auto firstClusterBis = (*itBis).first;
					auto secondClusterBis = (*itBis).second;

					// Check if it is the same reaction
					if (firstClusterBis == firstCluster
							&& secondClusterBis == secondCluster) {
						superPair.a00 += 1.0;
						superPair.a01 += factor;
						superPair.a10 += distance;
						superPair.a11 += distance * factor;

						// Do not delete the element if it is the original one
						if (itBis == it) {
							++itBis;
							continue;
						}

						// Remove the reaction from the vector
						itBis = pairsBis.erase(itBis);
					}
					// Go to the next element
					else
						++itBis;
				}

				// Give back the pairs
				mapItBis->second = pairsBis;
			}

			// Add the super pair
			effEmissionList.push_front(superPair);

			// Remove the reaction from the vector
			it = pairs.erase(it);
		}
	}

	// Clear the maps because they won't be used anymore
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

	return;
}

void NESuperCluster::resetConnectivities() {
	// Clear both sets
	reactionConnectivitySet.clear();
	dissociationConnectivitySet.clear();

	// Connect this cluster to itself since any reaction will affect it
	setReactionConnectivity(id);
	setDissociationConnectivity(id);
	setReactionConnectivity(xeMomId);
	setDissociationConnectivity(xeMomId);

	// Loop over all the reacting pairs
	for (auto it = effReactingList.begin(); it != effReactingList.end(); ++it) {
		// The cluster is connecting to both clusters in the pair
		setReactionConnectivity((*it).first->getId());
		setReactionConnectivity((*it).first->getXeMomentumId());
		setReactionConnectivity((*it).second->getId());
		setReactionConnectivity((*it).second->getXeMomentumId());
	}

	// Loop over all the combining pairs
	for (auto it = effCombiningList.begin(); it != effCombiningList.end();
			++it) {
		// The cluster is connecting to the combining cluster
		setReactionConnectivity((*it).first->getId());
		setReactionConnectivity((*it).first->getXeMomentumId());
	}

	// Loop over all the dissociating pairs
	for (auto it = effDissociatingList.begin(); it != effDissociatingList.end();
			++it) {
		// The cluster is connecting to the combining cluster
		setDissociationConnectivity((*it).first->getId());
		setDissociationConnectivity((*it).first->getXeMomentumId());
	}

	// Don't loop on the effective emission pairs because
	// this cluster is not connected to them

	// Initialize the partial vector for the momentum
<<<<<<< HEAD
	int dof = network->getDOF();
=======
	int dof = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	momentumPartials.resize(dof, 0.0);

	return;
}

double NESuperCluster::getTotalFlux() {
	// Initialize the momentum flux
	momentumFlux = 0.0;

	// Get the fluxes
	double prodFlux = getProductionFlux();
	double dissFlux = getDissociationFlux();
	double combFlux = getCombinationFlux();
	double emissFlux = getEmissionFlux();

	return prodFlux - combFlux + dissFlux - emissFlux;
}

double NESuperCluster::getDissociationFlux() {
	// Initial declarations
	double flux = 0.0, value = 0.0;
	NECluster *dissociatingCluster = nullptr;

	// Loop over all the dissociating pairs
	for (auto it = effDissociatingList.begin(); it != effDissociatingList.end();
			++it) {
		// Get the dissociating clusters
		dissociatingCluster = (*it).first;
		double l0A = dissociatingCluster->getConcentration(0.0);
		double l1A = dissociatingCluster->getMomentum();
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value * ((*it).a00 * l0A + (*it).a10 * l1A);
		// Compute the momentum fluxes
		momentumFlux += value * ((*it).a01 * l0A + (*it).a11 * l1A);
	}

	// Return the flux
	return flux;
}

double NESuperCluster::getEmissionFlux() {
	// Initial declarations
	double flux = 0.0, value = 0.0;

	// Loop over all the emission pairs
	for (auto it = effEmissionList.begin(); it != effEmissionList.end(); ++it) {
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value * ((*it).a00 * l0 + (*it).a10 * l1);
		// Compute the momentum fluxes
		momentumFlux -= value * ((*it).a01 * l0 + (*it).a11 * l1);
	}

	return flux;
}

double NESuperCluster::getProductionFlux() {
	// Local declarations
	double flux = 0.0, value = 0.0;
	NECluster *firstReactant = nullptr, *secondReactant = nullptr;

	// Loop over all the reacting pairs
	for (auto it = effReactingList.begin(); it != effReactingList.end(); ++it) {
		// Get the two reacting clusters
		firstReactant = (*it).first;
		secondReactant = (*it).second;
		double l0A = firstReactant->getConcentration();
		double l0B = secondReactant->getConcentration();
		double l1A = firstReactant->getMomentum();
		double l1B = secondReactant->getMomentum();
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value
				* ((*it).a000 * l0A * l0B + (*it).a010 * l0A * l1B
						+ (*it).a100 * l1A * l0B + (*it).a110 * l1A);
		// Compute the momentum flux
		momentumFlux += value
				* ((*it).a001 * l0A * l0B + (*it).a011 * l0A * l1B
						+ (*it).a101 * l1A * l0B + (*it).a111 * l1A);
	}

	// Return the production flux
	return flux;
}

double NESuperCluster::getCombinationFlux() {
	// Local declarations
	double flux = 0.0, value = 0.0;
	NECluster *combiningCluster = nullptr;

	// Loop over all the combining clusters
	for (auto it = effCombiningList.begin(); it != effCombiningList.end();
			++it) {
		// Get the two reacting clusters
		combiningCluster = (*it).first;
		double l0A = combiningCluster->getConcentration();
		double l1A = combiningCluster->getMomentum();
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value
				* ((*it).a000 * l0A * l0 + (*it).a100 * l0A * l1
						+ (*it).a010 * l1A * l0 + (*it).a110 * l1A * l1);
		// Compute the momentum flux
		momentumFlux -= value
				* ((*it).a001 * l0A * l0 + (*it).a101 * l0A * l1
						+ (*it).a011 * l1A * l0 + (*it).a111 * l1A * l1);
	}

	return flux;
}

void NESuperCluster::getPartialDerivatives(
		std::vector<double> & partials) const {
	// Reinitialize the momentum partial derivatives vector
	std::fill(momentumPartials.begin(), momentumPartials.end(), 0.0);

	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials);
	getCombinationPartialDerivatives(partials);
	getDissociationPartialDerivatives(partials);
	getEmissionPartialDerivatives(partials);

	return;
}

void NESuperCluster::getProductionPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	double value = 0.0;
	int index = 0;
	NECluster *firstReactant = nullptr, *secondReactant = nullptr;

	// Production
	// A + B --> D, D being this cluster
	// The flux for D is
	// F(C_D) = k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_D)/dC_A = k+_(A,B)*C_B
	// dF(C_D)/dC_B = k+_(A,B)*C_A

	// Loop over all the reacting pairs
	for (auto it = effReactingList.begin(); it != effReactingList.end(); ++it) {
		// Get the two reacting clusters
		firstReactant = (*it).first;
		secondReactant = (*it).second;
		double l0A = firstReactant->getConcentration();
		double l0B = secondReactant->getConcentration();
		double l1A = firstReactant->getMomentum();
		double l1B = secondReactant->getMomentum();

		// Compute the contribution from the first part of the reacting pair
		value = *((*it).kConstant) / (double) nTot;
<<<<<<< HEAD

//		std::cout << name << " : " << firstReactant->getName() << " + " << secondReactant->getName() << " " << l0A << " " << l0B << std::endl;

=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		index = firstReactant->getId() - 1;
		partials[index] += value * ((*it).a000 * l0B + (*it).a010 * l1B);
		momentumPartials[index] += value
				* ((*it).a001 * l0B + (*it).a011 * l1B);
		index = firstReactant->getXeMomentumId() - 1;
		partials[index] += value * ((*it).a100 * l0B + (*it).a110 * l1B);
		momentumPartials[index] += value
				* ((*it).a101 * l0B + (*it).a111 * l1B);
		// Compute the contribution from the second part of the reacting pair
		index = secondReactant->getId() - 1;
		partials[index] += value * ((*it).a000 * l0A + (*it).a100 * l1A);
		momentumPartials[index] += value
				* ((*it).a001 * l0A + (*it).a101 * l1A);
		index = secondReactant->getXeMomentumId() - 1;
		partials[index] += value * ((*it).a010 * l0A + (*it).a110 * l1A);
		momentumPartials[index] += value
				* ((*it).a011 * l0A + (*it).a111 * l1A);
	}

	return;
}

void NESuperCluster::getCombinationPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int index = 0;
	NECluster *cluster = nullptr;
	double value = 0.0;

	// Combination
	// A + B --> D, A being this cluster
	// The flux for A is outgoing
	// F(C_A) = - k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k+_(A,B)*C_B
	// dF(C_A)/dC_B = - k+_(A,B)*C_A

	// Loop over all the combining clusters
	for (auto it = effCombiningList.begin(); it != effCombiningList.end();
			++it) {
		// Get the two reacting clusters
		cluster = (*it).first;
		double l0A = cluster->getConcentration();
		double l1A = cluster->getMomentum();

		// Compute the contribution from the combining cluster
		value = *((*it).kConstant) / (double) nTot;
		index = cluster->getId() - 1;
		partials[index] -= value * ((*it).a000 * l0 + (*it).a100 * l1);
		momentumPartials[index] -= value * ((*it).a001 * l0 + (*it).a101 * l1);
		index = cluster->getXeMomentumId() - 1;
		partials[index] -= value * ((*it).a010 * l0 + (*it).a110 * l1);
		momentumPartials[index] -= value * ((*it).a011 * l0 + (*it).a111 * l1);
		// Compute the contribution from this cluster
		index = id - 1;
		partials[index] -= value * ((*it).a000 * l0A + (*it).a010 * l1A);
		momentumPartials[index] -= value
				* ((*it).a001 * l0A + (*it).a011 * l1A);
		index = xeMomId - 1;
		partials[index] -= value * ((*it).a100 * l0A + (*it).a110 * l1A);
		momentumPartials[index] -= value
				* ((*it).a101 * l0A + (*it).a111 * l1A);
	}

	return;
}

void NESuperCluster::getDissociationPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int index = 0;
	NECluster *cluster = nullptr;
	double value = 0.0;

	// Dissociation
	// A --> B + D, B being this cluster
	// The flux for B is
	// F(C_B) = k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_B)/dC_A = k-_(B,D)

	// Loop over all the dissociating pairs
	for (auto it = effDissociatingList.begin(); it != effDissociatingList.end();
			++it) {
		// Get the dissociating clusters
		cluster = (*it).first;

		// Compute the contribution from the dissociating cluster
		value = *((*it).kConstant) / (double) nTot;
		index = cluster->getId() - 1;
		partials[index] += value * ((*it).a00);
		momentumPartials[index] += value * ((*it).a01);
		index = cluster->getXeMomentumId() - 1;
		partials[index] += value * ((*it).a10);
		momentumPartials[index] += value * ((*it).a11);
	}

	return;
}

void NESuperCluster::getEmissionPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	int index = 0;
	double value = 0.0;

	// Emission
	// A --> B + D, A being this cluster
	// The flux for A is
	// F(C_A) = - k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k-_(B,D)

	// Loop over all the emission pairs
	for (auto it = effEmissionList.begin(); it != effEmissionList.end(); ++it) {
		// Compute the contribution from the dissociating cluster
		value = *((*it).kConstant) / (double) nTot;
		index = id - 1;
		partials[index] -= value * ((*it).a00);
		momentumPartials[index] -= value * ((*it).a01);
		index = xeMomId - 1;
		partials[index] -= value * ((*it).a10);
		momentumPartials[index] -= value * ((*it).a11);
	}

	return;
}

void NESuperCluster::getMomentPartialDerivatives(
		std::vector<double> & partials) const {
	// Loop on the size of the vector
	for (int i = 0; i < partials.size(); i++) {
		// Set to the values that were already computed
		partials[i] = momentumPartials[i];
	}

	return;
}
