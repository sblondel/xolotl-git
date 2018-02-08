// Includes
#include "PSISuperCluster.h"
#include "PSIClusterReactionNetwork.h"
<<<<<<< HEAD
#include <Constants.h>
#include <MathUtils.h>
=======
#include <MathUtils.h>
#include <xolotlPerf.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

using namespace xolotlCore;

/**
 * The helium momentum partials.
 */
<<<<<<< HEAD
std::vector<double> heMomentumPartials;
=======
std::vector<double> psiHeMomentPartials;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

/**
 * The vacancy momentum partials.
 */
<<<<<<< HEAD
std::vector<double> vMomentumPartials;

PSISuperCluster::PSISuperCluster(double numHe, double numV, int nTot,
		int heWidth, int vWidth, double radius, double energy,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(registry), numHe(numHe), numV(numV), nTot(nTot), l0(0.0), l1He(
=======
std::vector<double> psiVMomentPartials;

PSISuperCluster::PSISuperCluster(double _numHe, double _numV, int _nTot,
		int heWidth, int vWidth, IReactionNetwork& _network,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(_network, registry, buildName(_numHe, _numV)), numHe(_numHe), numV(
				_numV), nTot(_nTot), heBounds(0, 0), vBounds(0, 0), l0(0.0), l1He(
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				0.0), l1V(0.0), dispersionHe(0.0), dispersionV(0.0), heMomentumFlux(
				0.0), vMomentumFlux(0.0) {
	// Set the cluster size as the sum of
	// the number of Helium and Vacancies
	size = (int) (numHe + numV);

	// Update the composition map
<<<<<<< HEAD
	compositionMap[heType] = (int) numHe;
	compositionMap[vType] = (int) numV;
=======
	composition[toCompIdx(Species::He)] = (int) numHe;
	composition[toCompIdx(Species::V)] = (int) numV;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Set the width
	sectionHeWidth = heWidth;
	sectionVWidth = vWidth;

<<<<<<< HEAD
	// Set the reaction radius and formation energy
	reactionRadius = radius;
=======
	// Set the formation energy
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	formationEnergy = 0.0; // It is set to 0.0 because we do not want the super clusters to undergo dissociation

	// Set the diffusion factor and the migration energy
	migrationEnergy = std::numeric_limits<double>::infinity();
	diffusionFactor = 0.0;

<<<<<<< HEAD
	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "He_" << numHe << "V_" << numV;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = PSISuperType;
=======
	// Set the typename appropriately
	type = ReactantType::PSISuper;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
PSISuperCluster::PSISuperCluster(PSISuperCluster &other) :
		PSICluster(other) {
	numHe = other.numHe;
	numV = other.numV;
	nTot = other.nTot;
	sectionHeWidth = other.sectionHeWidth;
	sectionVWidth = other.sectionVWidth;
	l0 = other.l0;
	l1He = other.l1He;
	l1V = other.l1V;
	dispersionHe = other.dispersionHe;
	dispersionV = other.dispersionV;
	reactingMap = other.reactingMap;
	combiningMap = other.combiningMap;
	dissociatingMap = other.dissociatingMap;
	emissionMap = other.emissionMap;
	effReactingList = other.effReactingList;
	effCombiningList = other.effCombiningList;
	effDissociatingList = other.effDissociatingList;
	effEmissionList = other.effEmissionList;
	heMomentumFlux = other.heMomentumFlux;
	vMomentumFlux = other.vMomentumFlux;
=======
void PSISuperCluster::resultFrom(ProductionReaction& reaction, int a, int b,
		int c, int d) {

	// Check if we already know about the reaction.
	auto rkey = std::make_pair(&(reaction.first), &(reaction.second));
	auto it = effReactingList.find(rkey);
	if (it == effReactingList.end()) {

		// We did not already know about this reaction.
		// Add info about production to our list.
		auto eret = effReactingList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(reaction.first),
						static_cast<PSICluster&>(reaction.second)));
		// Since we already checked and didn't know about the reaction,
		// we had better have added it with our emplace() call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effReactingList.end());
	auto& prodPair = it->second;

	// NB: prodPair's reactants are same as reaction.
	// So use prodPair only from here on.
	// TODO any way to enforce this?

	// Update the coefficients
	double firstHeDistance = 0.0, firstVDistance = 0.0, secondHeDistance = 0.0,
			secondVDistance = 0.0;
	if (prodPair.first.getType() == ReactantType::PSISuper) {
		auto const& super = static_cast<PSICluster const&>(prodPair.first);
		firstHeDistance = super.getHeDistance(c);
		firstVDistance = super.getVDistance(d);
	}
	if (prodPair.second.getType() == ReactantType::PSISuper) {
		auto const& super = static_cast<PSICluster const&>(prodPair.second);
		secondHeDistance = super.getHeDistance(c);
		secondVDistance = super.getVDistance(d);
	}
	double heFactor = (double) (a - numHe) / dispersionHe;
	double vFactor = (double) (b - numV) / dispersionV;
	// First is A, second is B, in A + B -> this
	prodPair.a000 += 1.0;
	prodPair.a001 += heFactor;
	prodPair.a002 += vFactor;
	prodPair.a100 += firstHeDistance;
	prodPair.a101 += firstHeDistance * heFactor;
	prodPair.a102 += firstHeDistance * vFactor;
	prodPair.a200 += firstVDistance;
	prodPair.a201 += firstVDistance * heFactor;
	prodPair.a202 += firstVDistance * vFactor;
	prodPair.a010 += secondHeDistance;
	prodPair.a011 += secondHeDistance * heFactor;
	prodPair.a012 += secondHeDistance * vFactor;
	prodPair.a020 += secondVDistance;
	prodPair.a021 += secondVDistance * heFactor;
	prodPair.a022 += secondVDistance * vFactor;
	prodPair.a110 += firstHeDistance * secondHeDistance;
	prodPair.a111 += firstHeDistance * secondHeDistance * heFactor;
	prodPair.a112 += firstHeDistance * secondHeDistance * vFactor;
	prodPair.a120 += firstHeDistance * secondVDistance;
	prodPair.a121 += firstHeDistance * secondVDistance * heFactor;
	prodPair.a122 += firstHeDistance * secondVDistance * vFactor;
	prodPair.a210 += firstVDistance * secondHeDistance;
	prodPair.a211 += firstVDistance * secondHeDistance * heFactor;
	prodPair.a212 += firstVDistance * secondHeDistance * vFactor;
	prodPair.a220 += firstVDistance * secondVDistance;
	prodPair.a221 += firstVDistance * secondVDistance * heFactor;
	prodPair.a222 += firstVDistance * secondVDistance * vFactor;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
std::shared_ptr<IReactant> PSISuperCluster::clone() {
	std::shared_ptr<IReactant> reactant(new PSISuperCluster(*this));

	return reactant;
}

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
void PSISuperCluster::setReactionNetwork(
		const std::shared_ptr<IReactionNetwork> reactionNetwork) {
	// Call the superclass's method to actually set the reference
	Reactant::setReactionNetwork(reactionNetwork);

	// Clear the flux-related arrays
	reactingPairs.clear();
	combiningReactants.clear();
	dissociatingPairs.clear();
	emissionPairs.clear();

	// Aggregate the reacting pairs and combining reactants from the xeVector
	// Loop on the xeVector
	for (int i = 0; i < heVVector.size(); i++) {
		// Get the cluster composition
		auto comp = heVVector[i]->getComposition();
		// Create the key to the map
		auto key = std::make_pair(comp[heType], comp[vType]);
		// Get all vectors
		auto react = heVVector[i]->reactingPairs;
		auto combi = heVVector[i]->combiningReactants;
		auto disso = heVVector[i]->dissociatingPairs;
		auto emi = heVVector[i]->emissionPairs;

		// Set them in the super cluster map
		reactingMap[key] = react;
		combiningMap[key] = combi;
		dissociatingMap[key] = disso;
		emissionMap[key] = emi;
	}

	// Compute the dispersions
	computeDispersion();
=======
void PSISuperCluster::resultFrom(ProductionReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {

	// Check if we already know about the reaction.
	auto rkey = std::make_pair(&(reaction.first), &(reaction.second));
	auto it = effReactingList.find(rkey);
	if (it == effReactingList.end()) {

		// We did not already know about this reaction.
		// Add info about production to our list.
		auto eret = effReactingList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(reaction.first),
						static_cast<PSICluster&>(reaction.second)));
		// Since we already checked and didn't know about the reaction,
		// we had better have added it with our emplace() call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effReactingList.end());
	auto& prodPair = it->second;

	// NB: prodPair's reactants are same as reaction.
	// So use prodPair only from here on.
	// TODO any way to enforce this?

	// Update the coefficients
	std::for_each(prInfos.begin(), prInfos.end(),
			[this,&prodPair](const PendingProductionReactionInfo& currPRI) {

				// Use names corresponding to those in single version.
				int a = currPRI.numHe;
				int b = currPRI.numV;
				int c = currPRI.i;
				int d = currPRI.j;

				double firstHeDistance = 0.0, firstVDistance = 0.0, secondHeDistance = 0.0,
				secondVDistance = 0.0;
				if (prodPair.first.getType() == ReactantType::PSISuper) {
					auto const& super = static_cast<PSICluster const&>(prodPair.first);
					firstHeDistance = super.getHeDistance(c);
					firstVDistance = super.getVDistance(d);
				}
				if (prodPair.second.getType() == ReactantType::PSISuper) {
					auto const& super = static_cast<PSICluster const&>(prodPair.second);
					secondHeDistance = super.getHeDistance(c);
					secondVDistance = super.getVDistance(d);
				}
				double heFactor = (double) (a - numHe) / dispersionHe;
				double vFactor = (double) (b - numV) / dispersionV;
				// First is A, second is B, in A + B -> this
				prodPair.a000 += 1.0;
				prodPair.a001 += heFactor;
				prodPair.a002 += vFactor;
				prodPair.a100 += firstHeDistance;
				prodPair.a101 += firstHeDistance * heFactor;
				prodPair.a102 += firstHeDistance * vFactor;
				prodPair.a200 += firstVDistance;
				prodPair.a201 += firstVDistance * heFactor;
				prodPair.a202 += firstVDistance * vFactor;
				prodPair.a010 += secondHeDistance;
				prodPair.a011 += secondHeDistance * heFactor;
				prodPair.a012 += secondHeDistance * vFactor;
				prodPair.a020 += secondVDistance;
				prodPair.a021 += secondVDistance * heFactor;
				prodPair.a022 += secondVDistance * vFactor;
				prodPair.a110 += firstHeDistance * secondHeDistance;
				prodPair.a111 += firstHeDistance * secondHeDistance * heFactor;
				prodPair.a112 += firstHeDistance * secondHeDistance * vFactor;
				prodPair.a120 += firstHeDistance * secondVDistance;
				prodPair.a121 += firstHeDistance * secondVDistance * heFactor;
				prodPair.a122 += firstHeDistance * secondVDistance * vFactor;
				prodPair.a210 += firstVDistance * secondHeDistance;
				prodPair.a211 += firstVDistance * secondHeDistance * heFactor;
				prodPair.a212 += firstVDistance * secondHeDistance * vFactor;
				prodPair.a220 += firstVDistance * secondVDistance;
				prodPair.a221 += firstVDistance * secondVDistance * heFactor;
				prodPair.a222 += firstVDistance * secondVDistance * vFactor;
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
double PSISuperCluster::getConcentration(double distHe, double distV) const {
	return l0 + (distHe * l1He) + (distV * l1V);
}

double PSISuperCluster::getHeMomentum() const {
	return l1He;
}

double PSISuperCluster::getVMomentum() const {
	return l1V;
}

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
double PSISuperCluster::getTotalConcentration() const {
	// Initial declarations
	int heIndex = 0, vIndex = 0;
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the vacancy width
	for (int k = 0; k < sectionVWidth; k++) {
		// Compute the vacancy index
		vIndex = (int) (numV - (double) sectionVWidth / 2.0) + k + 1;

		// Loop on the helium width
		for (int j = 0; j < sectionHeWidth; j++) {
			// Compute the helium index
			heIndex = (int) (numHe - (double) sectionHeWidth / 2.0) + j + 1;

			// Check if this cluster exists
			if (reactingMap.find(std::make_pair(heIndex, vIndex))
					== reactingMap.end())
				continue;

			// Compute the distances
			heDistance = getHeDistance(heIndex);
			vDistance = getVDistance(vIndex);

			// Add the concentration of each cluster in the group times its number of helium
			conc += getConcentration(heDistance, vDistance);
		}
	}

	return conc;
}

double PSISuperCluster::getTotalHeliumConcentration() const {
	// Initial declarations
	int heIndex = 0, vIndex = 0;
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the vacancy width
	for (int k = 0; k < sectionVWidth; k++) {
		// Compute the vacancy index
		vIndex = (int) (numV - (double) sectionVWidth / 2.0) + k + 1;

		// Loop on the helium width
		for (int j = 0; j < sectionHeWidth; j++) {
			// Compute the helium index
			heIndex = (int) (numHe - (double) sectionHeWidth / 2.0) + j + 1;

			// Check if this cluster exists
			if (reactingMap.find(std::make_pair(heIndex, vIndex))
					== reactingMap.end())
				continue;

			// Compute the distances
			heDistance = getHeDistance(heIndex);
			vDistance = getVDistance(vIndex);

			// Add the concentration of each cluster in the group times its number of helium
			conc += getConcentration(heDistance, vDistance) * (double) heIndex;
		}
	}

	return conc;
}

double PSISuperCluster::getTotalVacancyConcentration() const {
	// Initial declarations
	int heIndex = 0, vIndex = 0;
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the vacancy width
	for (int k = 0; k < sectionVWidth; k++) {
		// Compute the vacancy index
		vIndex = (int) (numV - (double) sectionVWidth / 2.0) + k + 1;

		// Loop on the helium width
		for (int j = 0; j < sectionHeWidth; j++) {
			// Compute the helium index
			heIndex = (int) (numHe - (double) sectionHeWidth / 2.0) + j + 1;

			// Check if this cluster exists
			if (reactingMap.find(std::make_pair(heIndex, vIndex))
					== reactingMap.end())
				continue;

			// Compute the distances
			heDistance = getHeDistance(heIndex);
			vDistance = getVDistance(vIndex);

			// Add the concentration of each cluster in the group times its number of helium
			conc += getConcentration(heDistance, vDistance) * (double) vIndex;
		}
	}

	return conc;
}

<<<<<<< HEAD
<<<<<<< HEAD
double PSISuperCluster::getHeDistance(int he) const {
	if (sectionHeWidth == 1)
		return 0.0;
	return 2.0 * (double) (he - numHe) / ((double) sectionHeWidth - 1.0);
}
=======
double PSISuperCluster::getIntegratedVConcentration(int v) const {
	// Initial declarations
	int heIndex = 0;
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;
>>>>>>> master

	// Loop on the helium width
	for (int j = 0; j < sectionHeWidth; j++) {
		// Compute the helium index
		heIndex = (int) (numHe - (double) sectionHeWidth / 2.0) + j + 1;

		// Check if this cluster exists
		if (reactingMap.find(std::make_pair(heIndex, v)) == reactingMap.end())
			continue;

		// Compute the distances
		heDistance = getHeDistance(heIndex);
		vDistance = getVDistance(v);

		// Add the concentration of each cluster in the group times its number of helium
		conc += getConcentration(heDistance, vDistance);
	}

	return conc;
}

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
void PSISuperCluster::computeDispersion() {
	// Local declarations
	int heIndex = 0, vIndex = 0;
	// Initialize the dispersion sum
	double nHeSquare = 0.0, nVSquare = 0.0;

	// Loop on the vacancy width
	for (int k = 0; k < sectionVWidth; k++) {
		// Compute the vacancy index
		vIndex = (int) (numV - (double) sectionVWidth / 2.0) + k + 1;

		// Loop on the helium width
		for (int j = 0; j < sectionHeWidth; j++) {
			// Compute the helium index
			heIndex = (int) (numHe - (double) sectionHeWidth / 2.0) + j + 1;

			// Create the key for the maps
			auto key = std::make_pair(heIndex, vIndex);

			// Check if this cluster exists
			if (reactingMap.find(key) == reactingMap.end())
				continue;

			// Compute nSquare for the dispersion
			nHeSquare += (double) heIndex * heIndex;
			nVSquare += (double) vIndex * vIndex;
		}
=======
void PSISuperCluster::participateIn(ProductionReaction& reaction, int a,
		int b) {

	setReactionConnectivity(id);
	// Look for the other cluster
	auto& otherCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if we already know about the reaction.
	auto rkey = &otherCluster;
	auto it = effCombiningList.find(rkey);
	if (it == effCombiningList.end()) {

		// We did not already know about the reaction.
		// Note that we combine with the other cluster in this reaction.
		auto eret = effCombiningList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(otherCluster)));
		// Since we already checked and didn't know about the reaction then,
		// we had better have added it with our emplace call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effCombiningList.end());
	auto& combCluster = it->second;

	// Update the coefficients
	double heDistance = getHeDistance(a);
	double heFactor = (double) (a - numHe) / dispersionHe;
	double vDistance = getVDistance(b);
	double vFactor = (double) (b - numV) / dispersionV;
	// This is A, itBis is B, in A + B -> C
	combCluster.a000 += 1.0;
	combCluster.a001 += heFactor;
	combCluster.a002 += vFactor;
	combCluster.a100 += heDistance;
	combCluster.a101 += heDistance * heFactor;
	combCluster.a102 += heDistance * vFactor;
	combCluster.a200 += vDistance;
	combCluster.a201 += vDistance * heFactor;
	combCluster.a202 += vDistance * vFactor;

	return;
}

void PSISuperCluster::participateIn(ProductionReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& pendingPRInfos) {

	setReactionConnectivity(id);
	// Look for the other cluster
	auto& otherCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if we already know about the reaction.
	auto rkey = &otherCluster;
	auto it = effCombiningList.find(rkey);
	if (it == effCombiningList.end()) {

		// We did not already know about the reaction.
		// Note that we combine with the other cluster in this reaction.
		auto eret = effCombiningList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(otherCluster)));
		// Since we already checked and didn't know about the reaction then,
		// we had better have added it with our emplace call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effCombiningList.end());
	auto& combCluster = it->second;

	// Update the coefficients
	std::for_each(pendingPRInfos.begin(), pendingPRInfos.end(),
			[this,&combCluster](const PendingProductionReactionInfo& currPRInfo) {

				// Use names corresponding to the single-item version.
				int a = currPRInfo.i;
				int b = currPRInfo.j;

				double heDistance = getHeDistance(a);
				double heFactor = (double) (a - numHe) / dispersionHe;
				double vDistance = getVDistance(b);
				double vFactor = (double) (b - numV) / dispersionV;
				// This is A, itBis is B, in A + B -> C
				combCluster.a000 += 1.0;
				combCluster.a001 += heFactor;
				combCluster.a002 += vFactor;
				combCluster.a100 += heDistance;
				combCluster.a101 += heDistance * heFactor;
				combCluster.a102 += heDistance * vFactor;
				combCluster.a200 += vDistance;
				combCluster.a201 += vDistance * heFactor;
				combCluster.a202 += vDistance * vFactor;
			});

	return;
}

void PSISuperCluster::participateIn(DissociationReaction& reaction, int a,
		int b, int c, int d) {

	// Determine which is the other cluster.
	auto& emittedCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if we already know about the reaction.
	auto rkey = std::make_pair(&(reaction.dissociating), &emittedCluster);
	auto it = effDissociatingList.find(rkey);
	if (it == effDissociatingList.end()) {

		// We did not already know about it.

		// Add it to the network
		auto eret = effDissociatingList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(reaction.dissociating),
						static_cast<PSICluster&>(emittedCluster)));
		// Since we already checked and didn't know about the reaction then,
		// we had better have added it with our emplace() call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effDissociatingList.end());
	auto& dissPair = it->second;

	// Update the coefficients
	double firstHeDistance = 0.0, firstVDistance = 0.0;
	if (reaction.dissociating.getType() == ReactantType::PSISuper) {
		auto const& super =
				static_cast<PSICluster const&>(reaction.dissociating);
		firstHeDistance = super.getHeDistance(a);
		firstVDistance = super.getVDistance(b);
	}
	double heFactor = (double) (c - numHe) / dispersionHe;
	double vFactor = (double) (d - numV) / dispersionV;

	// A is the dissociating cluster
	dissPair.a00 += 1.0;
	dissPair.a01 += heFactor;
	dissPair.a02 += vFactor;
	dissPair.a10 += firstHeDistance;
	dissPair.a11 += firstHeDistance * heFactor;
	dissPair.a12 += firstHeDistance * vFactor;
	dissPair.a20 += firstVDistance;
	dissPair.a21 += firstVDistance * heFactor;
	dissPair.a22 += firstVDistance * vFactor;

	return;
}

void PSISuperCluster::participateIn(DissociationReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {

	// Determine which is the other cluster.
	auto& emittedCluster = static_cast<PSICluster&>(
			(reaction.first.getId() == id) ? reaction.second : reaction.first);

	// Check if we already know about the reaction.
	auto rkey = std::make_pair(&(reaction.dissociating), &emittedCluster);
	auto it = effDissociatingList.find(rkey);
	if (it == effDissociatingList.end()) {

		// We did not already know about it.

		// Add it to the network
		auto eret = effDissociatingList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(reaction.dissociating),
						static_cast<PSICluster&>(emittedCluster)));
		// Since we already checked and didn't know about the reaction then,
		// we had better have added it with our emplace() call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effDissociatingList.end());
	auto& dissPair = it->second;

	// Update the coefficients
	std::for_each(prInfos.begin(), prInfos.end(),
			[this,&dissPair,&reaction](const PendingProductionReactionInfo& currPRI) {

				// Use names corresponding to the single-item version.
				int a = currPRI.numHe;
				int b = currPRI.numV;
				int c = currPRI.i;
				int d = currPRI.j;

				double firstHeDistance = 0.0, firstVDistance = 0.0;
				if (reaction.dissociating.getType() == ReactantType::PSISuper) {
					auto const& super = static_cast<PSICluster const&>(reaction.dissociating);
					firstHeDistance = super.getHeDistance(a);
					firstVDistance = super.getVDistance(b);
				}
				double heFactor = (double) (c - numHe) / dispersionHe;
				double vFactor = (double) (d - numV) / dispersionV;

				// A is the dissociating cluster
				dissPair.a00 += 1.0;
				dissPair.a01 += heFactor;
				dissPair.a02 += vFactor;
				dissPair.a10 += firstHeDistance;
				dissPair.a11 += firstHeDistance * heFactor;
				dissPair.a12 += firstHeDistance * vFactor;
				dissPair.a20 += firstVDistance;
				dissPair.a21 += firstVDistance * heFactor;
				dissPair.a22 += firstVDistance * vFactor;
			});

	return;
}

void PSISuperCluster::emitFrom(DissociationReaction& reaction, int a, int b,
		int c, int d) {

	// Check if we already know about the reaction.
	auto rkey = std::make_pair(&(reaction.first), &(reaction.second));
	auto it = effEmissionList.find(rkey);
	if (it == effEmissionList.end()) {

		// We did not already know about it.

		// Note that we emit from the two rectants according to the given
		// reaction.
		auto eret = effEmissionList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(reaction.first),
						static_cast<PSICluster&>(reaction.second)));
		// Since we already checked and didn't know about the reaction then,
		// we had better have added it with our emplace() call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effEmissionList.end());
	auto& dissPair = it->second;

	// Update the coeeficients
	double heDistance = getHeDistance(a);
	double heFactor = (double) (a - numHe) / dispersionHe;
	double vDistance = getVDistance(b);
	double vFactor = (double) (b - numV) / dispersionV;
	// A is the dissociating cluster
	dissPair.a00 += 1.0;
	dissPair.a01 += heFactor;
	dissPair.a02 += vFactor;
	dissPair.a10 += heDistance;
	dissPair.a11 += heDistance * heFactor;
	dissPair.a12 += heDistance * vFactor;
	dissPair.a20 += vDistance;
	dissPair.a21 += vDistance * heFactor;
	dissPair.a22 += vDistance * vFactor;

	return;
}

void PSISuperCluster::emitFrom(DissociationReaction& reaction,
		const std::vector<PendingProductionReactionInfo>& prInfos) {

	// Check if we already know about the reaction.
	auto rkey = std::make_pair(&(reaction.first), &(reaction.second));
	auto it = effEmissionList.find(rkey);
	if (it == effEmissionList.end()) {

		// We did not already know about it.

		// Note that we emit from the two rectants according to the given
		// reaction.
		auto eret = effEmissionList.emplace(std::piecewise_construct,
				std::forward_as_tuple(rkey),
				std::forward_as_tuple(reaction,
						static_cast<PSICluster&>(reaction.first),
						static_cast<PSICluster&>(reaction.second)));
		// Since we already checked and didn't know about the reaction then,
		// we had better have added it with our emplace() call.
		assert(eret.second);
		it = eret.first;
	}
	assert(it != effEmissionList.end());
	auto& dissPair = it->second;

	// Update the coeeficients
	std::for_each(prInfos.begin(), prInfos.end(),
			[this,&dissPair](const PendingProductionReactionInfo& currPRI) {

				// Use same names as used in single version.
				int a = currPRI.numHe;
				int b = currPRI.numV;

				double heDistance = getHeDistance(a);
				double heFactor = (double) (a - numHe) / dispersionHe;
				double vDistance = getVDistance(b);
				double vFactor = (double) (b - numV) / dispersionV;
				// A is the dissociating cluster
				dissPair.a00 += 1.0;
				dissPair.a01 += heFactor;
				dissPair.a02 += vFactor;
				dissPair.a10 += heDistance;
				dissPair.a11 += heDistance * heFactor;
				dissPair.a12 += heDistance * vFactor;
				dissPair.a20 += vDistance;
				dissPair.a21 += vDistance * heFactor;
				dissPair.a22 += vDistance * vFactor;
			});

	return;
}

void PSISuperCluster::setHeVVector(std::set<std::pair<int, int> > vec) {
	// Copy the list of coordinates
	heVList = vec;

	// Initialize the dispersion sum
	double nHeSquare = 0.0, nVSquare = 0.0;
	// Update the network map, compute the radius and dispersions
	for (auto it = heVList.begin(); it != heVList.end(); it++) {
		reactionRadius += xolotlCore::tungstenLatticeConstant
				* pow((3.0 * (double) ((*it).second)) / xolotlCore::pi,
						(1.0 / 3.0)) * 0.5 / (double) nTot;

		// Compute nSquare for the dispersion
		nHeSquare += (double) (*it).first * (*it).first;
		nVSquare += (double) (*it).second * (*it).second;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Compute the dispersions
	if (sectionHeWidth == 1)
		dispersionHe = 1.0;
	else
		dispersionHe = 2.0 * (nHeSquare - (numHe * (double) nTot * numHe))
<<<<<<< HEAD
				/ ((double) nTot * (double) (sectionHeWidth - 1));
=======
				/ ((double) (nTot * (sectionHeWidth - 1)));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	if (sectionVWidth == 1)
		dispersionV = 1.0;
	else
		dispersionV = 2.0 * (nVSquare - (numV * (double) nTot * numV))
<<<<<<< HEAD
				/ ((double) nTot * (double) (sectionVWidth - 1));
=======
				/ ((double) (nTot * (sectionVWidth - 1)));

	// Set the boundaries
	heBounds = IntegerRange<IReactant::SizeType>(
			static_cast<IReactant::SizeType>((numHe
					- (double) sectionHeWidth / 2.0) + 1),
			static_cast<IReactant::SizeType>((numHe
					- (double) sectionHeWidth / 2.0) + sectionHeWidth) + 1);
	vBounds = IntegerRange<IReactant::SizeType>(
			static_cast<IReactant::SizeType>((numV
					- (double) sectionVWidth / 2.0) + 1),
			static_cast<IReactant::SizeType>((numV
					- (double) sectionVWidth / 2.0) + sectionVWidth) + 1);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
void PSISuperCluster::optimizeReactions() {
	// Local declarations
	double heFactor = 0.0, vFactor = 0.0, heDistance = 0.0, vDistance = 0.0;
	PSICluster *firstReactant = nullptr, *secondReactant = nullptr,
			*combiningReactant = nullptr, *dissociatingCluster = nullptr,
			*otherEmittedCluster = nullptr, *firstCluster = nullptr,
			*secondCluster = nullptr;
	int heIndex = 0, vIndex = 0;

	// Loop on the effective reacting map
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
			auto reaction = std::make_shared<ProductionReaction>(firstReactant,
					secondReactant);
			// Add it to the network
			reaction = network->addProductionReaction(reaction);

			// Create a new SuperClusterProductionPair
			SuperClusterProductionPair superPair(firstReactant, secondReactant,
					reaction.get());

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != reactingMap.end();
					++mapItBis) {
				// Compute the helium index
				heIndex = mapItBis->first.first;
				heFactor = (double) (heIndex - numHe) / dispersionHe;
				// Compute the vacancy index
				vIndex = mapItBis->first.second;
				vFactor = (double) (vIndex - numV) / dispersionV;

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
						// First is A, second is B, in A + B -> this
						superPair.a000 += 1.0;
						superPair.a001 += heFactor;
						superPair.a002 += vFactor;
						superPair.a100 += (*itBis).firstHeDistance;
						superPair.a101 += (*itBis).firstHeDistance * heFactor;
						superPair.a102 += (*itBis).firstHeDistance * vFactor;
						superPair.a200 += (*itBis).firstVDistance;
						superPair.a201 += (*itBis).firstVDistance * heFactor;
						superPair.a202 += (*itBis).firstVDistance * vFactor;
						superPair.a010 += (*itBis).secondHeDistance;
						superPair.a011 += (*itBis).secondHeDistance * heFactor;
						superPair.a012 += (*itBis).secondHeDistance * vFactor;
						superPair.a020 += (*itBis).secondVDistance;
						superPair.a021 += (*itBis).secondVDistance * heFactor;
						superPair.a022 += (*itBis).secondVDistance * vFactor;
						superPair.a110 += (*itBis).firstHeDistance
								* (*itBis).secondHeDistance;
						superPair.a111 += (*itBis).firstHeDistance
								* (*itBis).secondHeDistance * heFactor;
						superPair.a112 += (*itBis).firstHeDistance
								* (*itBis).secondHeDistance * vFactor;
						superPair.a120 += (*itBis).firstHeDistance
								* (*itBis).secondVDistance;
						superPair.a121 += (*itBis).firstHeDistance
								* (*itBis).secondVDistance * heFactor;
						superPair.a122 += (*itBis).firstHeDistance
								* (*itBis).secondVDistance * vFactor;
						superPair.a210 += (*itBis).firstVDistance
								* (*itBis).secondHeDistance;
						superPair.a211 += (*itBis).firstVDistance
								* (*itBis).secondHeDistance * heFactor;
						superPair.a212 += (*itBis).firstVDistance
								* (*itBis).secondHeDistance * vFactor;
						superPair.a220 += (*itBis).firstVDistance
								* (*itBis).secondVDistance;
						superPair.a221 += (*itBis).firstVDistance
								* (*itBis).secondVDistance * heFactor;
						superPair.a222 += (*itBis).firstVDistance
								* (*itBis).secondVDistance * vFactor;

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

	// Loop on the effective combining map
	for (auto mapIt = combiningMap.begin(); mapIt != combiningMap.end();
			++mapIt) {
		// Get the pairs
		auto clusters = mapIt->second;
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

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != combiningMap.end();
					++mapItBis) {
				// Compute the helium index
				heIndex = mapItBis->first.first;
				heDistance = getHeDistance(heIndex);
				heFactor = (double) (heIndex - numHe) / dispersionHe;
				// Compute the vacancy index
				vIndex = mapItBis->first.second;
				vDistance = getVDistance(vIndex);
				vFactor = (double) (vIndex - numV) / dispersionV;

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
						// This is A, itBis is B, in this + B -> C
						superPair.a000 += 1.0;
						superPair.a001 += heFactor;
						superPair.a002 += vFactor;
						superPair.a010 += (*itBis).heDistance;
						superPair.a011 += (*itBis).heDistance * heFactor;
						superPair.a012 += (*itBis).heDistance * vFactor;
						superPair.a020 += (*itBis).vDistance;
						superPair.a021 += (*itBis).vDistance * heFactor;
						superPair.a022 += (*itBis).vDistance * vFactor;
						superPair.a100 += heDistance;
						superPair.a101 += heDistance * heFactor;
						superPair.a102 += heDistance * vFactor;
						superPair.a200 += vDistance;
						superPair.a201 += vDistance * heFactor;
						superPair.a202 += vDistance * vFactor;
						superPair.a110 += (*itBis).heDistance * heDistance;
						superPair.a111 += (*itBis).heDistance * heDistance
								* heFactor;
						superPair.a112 += (*itBis).heDistance * heDistance
								* vFactor;
						superPair.a210 += (*itBis).heDistance * vDistance;
						superPair.a211 += (*itBis).heDistance * vDistance
								* heFactor;
						superPair.a212 += (*itBis).heDistance * vDistance
								* vFactor;
						superPair.a120 += (*itBis).vDistance * heDistance;
						superPair.a121 += (*itBis).vDistance * heDistance
								* heFactor;
						superPair.a122 += (*itBis).vDistance * heDistance
								* vFactor;
						superPair.a220 += (*itBis).vDistance * vDistance;
						superPair.a221 += (*itBis).vDistance * vDistance
								* heFactor;
						superPair.a222 += (*itBis).vDistance * vDistance
								* vFactor;

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
			}

			// Add the super pair
			effCombiningList.push_front(superPair);

			// Remove the reaction from the vector
			it = clusters.erase(it);
		}
	}

	// Loop on the effective dissociating map
<<<<<<< HEAD
<<<<<<< HEAD
	for (auto mapIt = dissociatingMap.begin();
			mapIt != dissociatingMap.end(); ++mapIt) {
=======
	for (auto mapIt = dissociatingMap.begin(); mapIt != dissociatingMap.end();
			++mapIt) {
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	for (auto mapIt = dissociatingMap.begin(); mapIt != dissociatingMap.end();
			++mapIt) {
>>>>>>> master
		// Get the pairs
		auto pairs = mapIt->second;
		// Loop over all the reacting pairs
		for (auto it = pairs.begin(); it != pairs.end();) {
			// Get the two reacting clusters
			dissociatingCluster = (*it).first;
			otherEmittedCluster = (*it).second;

			// Create a dissociation reaction
			auto reaction = std::make_shared<DissociationReaction>(
					dissociatingCluster, this, otherEmittedCluster);
			// Add it to the network
			reaction = network->addDissociationReaction(reaction);

			// Create a new SuperClusterProductionPair
			SuperClusterDissociationPair superPair(dissociatingCluster,
					otherEmittedCluster, reaction.get());

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != dissociatingMap.end();
					++mapItBis) {
				// Compute the helium index
				heIndex = mapItBis->first.first;
				heFactor = (double) (heIndex - numHe) / dispersionHe;
				// Compute the vacancy index
				vIndex = mapItBis->first.second;
				vFactor = (double) (vIndex - numV) / dispersionV;

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
						// A is the dissociating cluster
						superPair.a00 += 1.0;
						superPair.a01 += heFactor;
						superPair.a02 += vFactor;
						superPair.a10 += (*itBis).firstHeDistance;
						superPair.a11 += (*itBis).firstHeDistance * heFactor;
						superPair.a12 += (*itBis).firstHeDistance * vFactor;
						superPair.a20 += (*itBis).firstVDistance;
						superPair.a21 += (*itBis).firstVDistance * heFactor;
						superPair.a22 += (*itBis).firstVDistance * vFactor;

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

	// Loop on the effective emission map
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
<<<<<<< HEAD
			auto reaction = std::make_shared<DissociationReaction>(
					this, firstCluster, secondCluster);
=======
			auto reaction = std::make_shared<DissociationReaction>(this,
					firstCluster, secondCluster);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
			auto reaction = std::make_shared<DissociationReaction>(this,
					firstCluster, secondCluster);
>>>>>>> master
			// Add it to the network
			reaction = network->addDissociationReaction(reaction);

			// Create a new SuperClusterProductionPair
			SuperClusterDissociationPair superPair(firstCluster, secondCluster,
					reaction.get());

			// Loop on the whole super cluster to fill this super pair
			for (auto mapItBis = mapIt; mapItBis != emissionMap.end();
					++mapItBis) {
				// Compute the helium index
				heIndex = mapItBis->first.first;
				heDistance = getHeDistance(heIndex);
				heFactor = (double) (heIndex - numHe) / dispersionHe;
				// Compute the vacancy index
				vIndex = mapItBis->first.second;
				vDistance = getVDistance(vIndex);
				vFactor = (double) (vIndex - numV) / dispersionV;

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
						// A is the dissociating cluster
						superPair.a00 += 1.0;
						superPair.a01 += heFactor;
						superPair.a02 += vFactor;
						superPair.a10 += heDistance;
						superPair.a11 += heDistance * heFactor;
						superPair.a12 += heDistance * vFactor;
						superPair.a20 += vDistance;
						superPair.a21 += vDistance * heFactor;
						superPair.a22 += vDistance * vFactor;

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
=======
double PSISuperCluster::getTotalConcentration() const {
	// Initial declarations
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the indices
	for (auto const& pair : heVList) {
		// Compute the distances
		heDistance = getHeDistance(pair.first);
		vDistance = getVDistance(pair.second);

		// Add the concentration of each cluster in the group times its number of helium
		conc += getConcentration(heDistance, vDistance);
	}

	return conc;
}

double PSISuperCluster::getTotalHeliumConcentration() const {
	// Initial declarations
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the indices
	for (auto const& pair : heVList) {
		// Compute the distances
		heDistance = getHeDistance(pair.first);
		vDistance = getVDistance(pair.second);

		// Add the concentration of each cluster in the group times its number of helium
		conc += getConcentration(heDistance, vDistance) * (double) pair.first;
	}

	return conc;
}

double PSISuperCluster::getTotalVacancyConcentration() const {
	// Initial declarations
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the indices
	for (auto const& pair : heVList) {
		// Compute the distances
		heDistance = getHeDistance(pair.first);
		vDistance = getVDistance(pair.second);

		// Add the concentration of each cluster in the group times its number of vacancies
		conc += getConcentration(heDistance, vDistance) * (double) pair.second;
	}

	return conc;
}

double PSISuperCluster::getIntegratedVConcentration(int v) const {
	// Initial declarations
	int heIndex = 0;
	double heDistance = 0.0, vDistance = 0.0, conc = 0.0;

	// Loop on the helium width
	for (int j = 0; j < sectionHeWidth; j++) {
		// Compute the helium index
		heIndex = (int) (numHe - (double) sectionHeWidth / 2.0) + j + 1;

		// Check if this cluster exists
		if (heVList.find(std::make_pair(heIndex, v)) == heVList.end())
			continue;

		// Compute the distances
		heDistance = getHeDistance(heIndex);
		vDistance = getVDistance(v);

		// Add the concentration of each cluster in the group times its number of helium
		conc += getConcentration(heDistance, vDistance);
	}

	return conc;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

void PSISuperCluster::resetConnectivities() {
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

<<<<<<< HEAD
	// Loop over all the reacting pairs
	for (auto it = effReactingList.begin(); it != effReactingList.end(); ++it) {
		// The cluster is connecting to both clusters in the pair
		setReactionConnectivity((*it).first->getId());
		setReactionConnectivity((*it).first->getHeMomentumId());
		setReactionConnectivity((*it).first->getVMomentumId());
		setReactionConnectivity((*it).second->getId());
		setReactionConnectivity((*it).second->getHeMomentumId());
		setReactionConnectivity((*it).second->getVMomentumId());
	}

	// Loop over all the combining pairs
	for (auto it = effCombiningList.begin(); it != effCombiningList.end();
			++it) {
		// The cluster is connecting to the combining cluster
		setReactionConnectivity((*it).first->getId());
		setReactionConnectivity((*it).first->getHeMomentumId());
		setReactionConnectivity((*it).first->getVMomentumId());
	}

	// Loop over all the dissociating pairs
	for (auto it = effDissociatingList.begin(); it != effDissociatingList.end();
			++it) {
		// The cluster is connecting to the combining cluster
		setDissociationConnectivity((*it).first->getId());
		setDissociationConnectivity((*it).first->getHeMomentumId());
		setDissociationConnectivity((*it).first->getVMomentumId());
	}
=======
	// Visit all the reacting pairs
	std::for_each(effReactingList.begin(), effReactingList.end(),
			[this](ProductionPairMap::value_type const& currMapItem) {
				// The cluster is connecting to both clusters in the pair
				auto const& currPair = currMapItem.second;
				setReactionConnectivity(currPair.first.getId());
				setReactionConnectivity(currPair.first.getHeMomentumId());
				setReactionConnectivity(currPair.first.getVMomentumId());
				setReactionConnectivity(currPair.second.getId());
				setReactionConnectivity(currPair.second.getHeMomentumId());
				setReactionConnectivity(currPair.second.getVMomentumId());
			});

	// Visit all the combining pairs
	std::for_each(effCombiningList.begin(), effCombiningList.end(),
			[this](CombiningClusterMap::value_type const& currMapItem) {
				// The cluster is connecting to the combining cluster
				auto const& currComb = currMapItem.second;
				setReactionConnectivity(currComb.first.getId());
				setReactionConnectivity(currComb.first.getHeMomentumId());
				setReactionConnectivity(currComb.first.getVMomentumId());
			});

	// Loop over all the dissociating pairs
	std::for_each(effDissociatingList.begin(), effDissociatingList.end(),
			[this](DissociationPairMap::value_type const& currMapItem) {
				// The cluster is connecting to the combining cluster
				auto const& currPair = currMapItem.second;
				setDissociationConnectivity(currPair.first.getId());
				setDissociationConnectivity(currPair.first.getHeMomentumId());
				setDissociationConnectivity(currPair.first.getVMomentumId());
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Don't loop on the effective emission pairs because
	// this cluster is not connected to them

	// Initialize the partial vector for the momentum
<<<<<<< HEAD
	int dof = network->getDOF();
	heMomentumPartials.resize(dof, 0.0);
	vMomentumPartials.resize(dof, 0.0);
=======
	int dof = network.getDOF();
	psiHeMomentPartials.resize(dof, 0.0);
	psiVMomentPartials.resize(dof, 0.0);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
double PSISuperCluster::getTotalFlux() {
	// Initialize the fluxes
	heMomentumFlux = 0.0;
	vMomentumFlux = 0.0;

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
double PSISuperCluster::getDissociationFlux() {
	// Initial declarations
<<<<<<< HEAD
	double flux = 0.0, value = 0.0;
	PSICluster *dissociatingCluster = nullptr;

	// Loop over all the dissociating pairs
	for (auto it = effDissociatingList.begin(); it != effDissociatingList.end();
			++it) {
		// Get the dissociating clusters
		dissociatingCluster = (*it).first;
		double l0A = dissociatingCluster->getConcentration(0.0, 0.0);
		double lHeA = dissociatingCluster->getHeMomentum();
		double lVA = dissociatingCluster->getVMomentum();
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value * ((*it).a00 * l0A + (*it).a10 * lHeA + (*it).a20 * lVA);
		// Compute the momentum fluxes
		heMomentumFlux += value
				* ((*it).a01 * l0A + (*it).a11 * lHeA + (*it).a21 * lVA);
		vMomentumFlux += value
				* ((*it).a02 * l0A + (*it).a12 * lHeA + (*it).a22 * lVA);
	}
=======
	double flux = 0.0;

	// Sum over all the dissociating pairs
	// TODO consider using std::accumulate.  May also want to change side
	// effect of updating member variables heMomentumFlux and
	// vMomentumFlux here.
	std::for_each(effDissociatingList.begin(), effDissociatingList.end(),
			[this,&flux](DissociationPairMap::value_type const& currMapItem) {
				auto const& currPair = currMapItem.second;

				// Get the dissociating clusters
				auto const& dissociatingCluster = currPair.first;
				double l0A = dissociatingCluster.getConcentration(0.0, 0.0);
				double lHeA = dissociatingCluster.getHeMomentum();
				double lVA = dissociatingCluster.getVMomentum();
				// Update the flux
				auto value = currPair.kConstant / (double) nTot;
				flux += value * (currPair.a00 * l0A + currPair.a10 * lHeA + currPair.a20 * lVA);
				// Compute the momentum fluxes
				heMomentumFlux += value
				* (currPair.a01 * l0A + currPair.a11 * lHeA + currPair.a21 * lVA);
				vMomentumFlux += value
				* (currPair.a02 * l0A + currPair.a12 * lHeA + currPair.a22 * lVA);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Return the flux
	return flux;
}

double PSISuperCluster::getEmissionFlux() {
	// Initial declarations
<<<<<<< HEAD
	double flux = 0.0, value = 0.0;

	// Loop over all the emission pairs
	for (auto it = effEmissionList.begin(); it != effEmissionList.end(); ++it) {
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value * ((*it).a00 * l0 + (*it).a10 * l1He + (*it).a20 * l1V);
		// Compute the momentum fluxes
		heMomentumFlux -= value
				* ((*it).a01 * l0 + (*it).a11 * l1He + (*it).a21 * l1V);
		vMomentumFlux -= value
				* ((*it).a02 * l0 + (*it).a12 * l1He + (*it).a22 * l1V);
	}
=======
	double flux = 0.0;

	// Loop over all the emission pairs
	// TODO consider using std::accumulate.  May also want to change side
	// effect of updating member variables heMomentumFlux and
	// vMomentumFlux here.
	std::for_each(effEmissionList.begin(), effEmissionList.end(),
			[this,&flux](DissociationPairMap::value_type const& currMapItem) {
				auto const& currPair = currMapItem.second;

				// Update the flux
				auto value = currPair.kConstant / (double) nTot;
				flux += value * (currPair.a00 * l0 + currPair.a10 * l1He + currPair.a20 * l1V);
				// Compute the momentum fluxes
				heMomentumFlux -= value
				* (currPair.a01 * l0 + currPair.a11 * l1He + currPair.a21 * l1V);
				vMomentumFlux -= value
				* (currPair.a02 * l0 + currPair.a12 * l1He + currPair.a22 * l1V);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return flux;
}

double PSISuperCluster::getProductionFlux() {
	// Local declarations
<<<<<<< HEAD
	double flux = 0.0, value = 0.0;
	PSICluster *firstReactant = nullptr, *secondReactant = nullptr;

	// Loop over all the reacting pairs
	for (auto it = effReactingList.begin(); it != effReactingList.end(); ++it) {
		// Get the two reacting clusters
		firstReactant = (*it).first;
		secondReactant = (*it).second;
		double l0A = firstReactant->getConcentration(0.0, 0.0);
		double l0B = secondReactant->getConcentration(0.0, 0.0);
		double lHeA = firstReactant->getHeMomentum();
		double lHeB = secondReactant->getHeMomentum();
		double lVA = firstReactant->getVMomentum();
		double lVB = secondReactant->getVMomentum();
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value
				* ((*it).a000 * l0A * l0B + (*it).a010 * l0A * lHeB
						+ (*it).a020 * l0A * lVB + (*it).a100 * lHeA * l0B
						+ (*it).a110 * lHeA * lHeB + (*it).a120 * lHeA * lVB
						+ (*it).a200 * lVA * l0B + (*it).a210 * lVA * lHeB
						+ (*it).a220 * lVA * lVB);
		// Compute the momentum fluxes
		heMomentumFlux += value
				* ((*it).a001 * l0A * l0B + (*it).a011 * l0A * lHeB
						+ (*it).a021 * l0A * lVB + (*it).a101 * lHeA * l0B
						+ (*it).a111 * lHeA * lHeB + (*it).a121 * lHeA * lVB
						+ (*it).a201 * lVA * l0B + (*it).a211 * lVA * lHeB
						+ (*it).a221 * lVA * lVB);
		vMomentumFlux += value
				* ((*it).a002 * l0A * l0B + (*it).a012 * l0A * lHeB
						+ (*it).a022 * l0A * lVB + (*it).a102 * lHeA * l0B
						+ (*it).a112 * lHeA * lHeB + (*it).a122 * lHeA * lVB
						+ (*it).a202 * lVA * l0B + (*it).a212 * lVA * lHeB
						+ (*it).a222 * lVA * lVB);
	}
=======
	double flux = 0.0;

	// Sum over all the reacting pairs
	// TODO consider using std::accumulate.  May also want to change side
	// effect of updating member variables heMomentumFlux and
	// vMomentumFlux here.
	std::for_each(effReactingList.begin(), effReactingList.end(),
			[this,&flux](ProductionPairMap::value_type const& currMapItem) {

				auto const& currPair = currMapItem.second;

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
				auto value = currPair.kConstant / (double) nTot;
				flux += value
				* (currPair.a000 * l0A * l0B + currPair.a010 * l0A * lHeB
						+ currPair.a020 * l0A * lVB + currPair.a100 * lHeA * l0B
						+ currPair.a110 * lHeA * lHeB + currPair.a120 * lHeA * lVB
						+ currPair.a200 * lVA * l0B + currPair.a210 * lVA * lHeB
						+ currPair.a220 * lVA * lVB);
				// Compute the momentum fluxes
				heMomentumFlux += value
				* (currPair.a001 * l0A * l0B + currPair.a011 * l0A * lHeB
						+ currPair.a021 * l0A * lVB + currPair.a101 * lHeA * l0B
						+ currPair.a111 * lHeA * lHeB + currPair.a121 * lHeA * lVB
						+ currPair.a201 * lVA * l0B + currPair.a211 * lVA * lHeB
						+ currPair.a221 * lVA * lVB);
				vMomentumFlux += value
				* (currPair.a002 * l0A * l0B + currPair.a012 * l0A * lHeB
						+ currPair.a022 * l0A * lVB + currPair.a102 * lHeA * l0B
						+ currPair.a112 * lHeA * lHeB + currPair.a122 * lHeA * lVB
						+ currPair.a202 * lVA * l0B + currPair.a212 * lVA * lHeB
						+ currPair.a222 * lVA * lVB);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Return the production flux
	return flux;
}

double PSISuperCluster::getCombinationFlux() {
	// Local declarations
<<<<<<< HEAD
	double flux = 0.0, value = 0.0;
	PSICluster *combiningCluster = nullptr;

	// Loop over all the combining clusters
	for (auto it = effCombiningList.begin(); it != effCombiningList.end();
			++it) {
		// Get the two reacting clusters
		combiningCluster = (*it).first;
		double l0B = combiningCluster->getConcentration(0.0, 0.0);
		double lHeB = combiningCluster->getHeMomentum();
		double lVB = combiningCluster->getVMomentum();
		// Update the flux
		value = *((*it).kConstant) / (double) nTot;
		flux += value
				* ((*it).a000 * l0B * l0 + (*it).a100 * l0B * l1He
						+ (*it).a200 * l0B * l1V + (*it).a010 * lHeB * l0
						+ (*it).a110 * lHeB * l1He + (*it).a210 * lHeB * l1V
						+ (*it).a020 * lVB * l0 + (*it).a120 * lVB * l1He
						+ (*it).a220 * lVB * l1V);
		// Compute the momentum fluxes
		heMomentumFlux -= value
				* ((*it).a001 * l0B * l0 + (*it).a101 * l0B * l1He
						+ (*it).a201 * l0B * l1V + (*it).a011 * lHeB * l0
						+ (*it).a111 * lHeB * l1He + (*it).a211 * lHeB * l1V
						+ (*it).a021 * lVB * l0 + (*it).a121 * lVB * l1He
						+ (*it).a221 * lVB * l1V);
		vMomentumFlux -= value
				* ((*it).a002 * l0B * l0 + (*it).a102 * l0B * l1He
						+ (*it).a202 * l0B * l1V + (*it).a012 * lHeB * l0
						+ (*it).a112 * lHeB * l1He + (*it).a212 * lHeB * l1V
						+ (*it).a022 * lVB * l0 + (*it).a122 * lVB * l1He
						+ (*it).a222 * lVB * l1V);
	}
=======
	double flux = 0.0;

	// Sum over all the combining clusters
	// TODO consider using std::accumulate.  May also want to change side
	// effect of updating member variables heMomentumFlux and
	// vMomentumFlux here.
	std::for_each(effCombiningList.begin(), effCombiningList.end(),
			[this,&flux](CombiningClusterMap::value_type const& currMapItem) {
				// Get the combining cluster
				auto const& currComb = currMapItem.second;
				auto const& combiningCluster = currComb.first;
				double l0B = combiningCluster.getConcentration(0.0, 0.0);
				double lHeB = combiningCluster.getHeMomentum();
				double lVB = combiningCluster.getVMomentum();
				// Update the flux
				auto value = currComb.kConstant / (double) nTot;
				flux += value
				* (currComb.a000 * l0B * l0 + currComb.a100 * l0B * l1He
						+ currComb.a200 * l0B * l1V + currComb.a010 * lHeB * l0
						+ currComb.a110 * lHeB * l1He + currComb.a210 * lHeB * l1V
						+ currComb.a020 * lVB * l0 + currComb.a120 * lVB * l1He
						+ currComb.a220 * lVB * l1V);
				// Compute the momentum fluxes
				heMomentumFlux -= value
				* (currComb.a001 * l0B * l0 + currComb.a101 * l0B * l1He
						+ currComb.a201 * l0B * l1V + currComb.a011 * lHeB * l0
						+ currComb.a111 * lHeB * l1He + currComb.a211 * lHeB * l1V
						+ currComb.a021 * lVB * l0 + currComb.a121 * lVB * l1He
						+ currComb.a221 * lVB * l1V);
				vMomentumFlux -= value
				* (currComb.a002 * l0B * l0 + currComb.a102 * l0B * l1He
						+ currComb.a202 * l0B * l1V + currComb.a012 * lHeB * l0
						+ currComb.a112 * lHeB * l1He + currComb.a212 * lHeB * l1V
						+ currComb.a022 * lVB * l0 + currComb.a122 * lVB * l1He
						+ currComb.a222 * lVB * l1V);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return flux;
}

void PSISuperCluster::getPartialDerivatives(
		std::vector<double> & partials) const {
	// Reinitialize the momentum partial derivatives vector
<<<<<<< HEAD
	std::fill(heMomentumPartials.begin(), heMomentumPartials.end(), 0.0);
	std::fill(vMomentumPartials.begin(), vMomentumPartials.end(), 0.0);
=======
	std::fill(psiHeMomentPartials.begin(), psiHeMomentPartials.end(), 0.0);
	std::fill(psiVMomentPartials.begin(), psiVMomentPartials.end(), 0.0);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the partial derivatives for each reaction type
	getProductionPartialDerivatives(partials);
	getCombinationPartialDerivatives(partials);
	getDissociationPartialDerivatives(partials);
	getEmissionPartialDerivatives(partials);

	return;
}

void PSISuperCluster::getProductionPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	double value = 0.0;
	int index = 0;
	PSICluster *firstReactant = nullptr, *secondReactant = nullptr;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Production
	// A + B --> D, D being this cluster
	// The flux for D is
	// F(C_D) = k+_(A,B)*C_A*C_B
	// Thus, the partial derivatives
	// dF(C_D)/dC_A = k+_(A,B)*C_B
	// dF(C_D)/dC_B = k+_(A,B)*C_A

	// Loop over all the reacting pairs
<<<<<<< HEAD
	for (auto it = effReactingList.begin(); it != effReactingList.end(); ++it) {
		// Get the two reacting clusters
		firstReactant = (*it).first;
		secondReactant = (*it).second;
		double l0A = firstReactant->getConcentration(0.0, 0.0);
		double l0B = secondReactant->getConcentration(0.0, 0.0);
		double lHeA = firstReactant->getHeMomentum();
		double lHeB = secondReactant->getHeMomentum();
		double lVA = firstReactant->getVMomentum();
		double lVB = secondReactant->getVMomentum();

		// Compute the contribution from the first part of the reacting pair
		value = *((*it).kConstant) / (double) nTot;
		index = firstReactant->getId() - 1;
		partials[index] += value
				* ((*it).a000 * l0B + (*it).a010 * lHeB + (*it).a020 * lVB);
		heMomentumPartials[index] += value
				* ((*it).a001 * l0B + (*it).a011 * lHeB + (*it).a021 * lVB);
		vMomentumPartials[index] += value
				* ((*it).a002 * l0B + (*it).a012 * lHeB + (*it).a022 * lVB);
		index = firstReactant->getHeMomentumId() - 1;
		partials[index] += value
				* ((*it).a100 * l0B + (*it).a110 * lHeB + (*it).a120 * lVB);
		heMomentumPartials[index] += value
				* ((*it).a101 * l0B + (*it).a111 * lHeB + (*it).a121 * lVB);
		vMomentumPartials[index] += value
				* ((*it).a102 * l0B + (*it).a112 * lHeB + (*it).a122 * lVB);
		index = firstReactant->getVMomentumId() - 1;
		partials[index] += value
				* ((*it).a200 * l0B + (*it).a210 * lHeB + (*it).a220 * lVB);
		heMomentumPartials[index] += value
				* ((*it).a201 * l0B + (*it).a211 * lHeB + (*it).a221 * lVB);
		vMomentumPartials[index] += value
				* ((*it).a202 * l0B + (*it).a212 * lHeB + (*it).a222 * lVB);
		// Compute the contribution from the second part of the reacting pair
		index = secondReactant->getId() - 1;
		partials[index] += value
				* ((*it).a000 * l0A + (*it).a100 * lHeA + (*it).a200 * lVA);
		heMomentumPartials[index] += value
				* ((*it).a001 * l0A + (*it).a101 * lHeA + (*it).a201 * lVA);
		vMomentumPartials[index] += value
				* ((*it).a002 * l0A + (*it).a102 * lHeA + (*it).a202 * lVA);
		index = secondReactant->getHeMomentumId() - 1;
		partials[index] += value
				* ((*it).a010 * l0A + (*it).a110 * lHeA + (*it).a210 * lVA);
		heMomentumPartials[index] += value
				* ((*it).a011 * l0A + (*it).a111 * lHeA + (*it).a211 * lVA);
		vMomentumPartials[index] += value
				* ((*it).a012 * l0A + (*it).a112 * lHeA + (*it).a212 * lVA);
		index = secondReactant->getVMomentumId() - 1;
		partials[index] += value
				* ((*it).a020 * l0A + (*it).a120 * lHeA + (*it).a220 * lVA);
		heMomentumPartials[index] += value
				* ((*it).a021 * l0A + (*it).a121 * lHeA + (*it).a221 * lVA);
		vMomentumPartials[index] += value
				* ((*it).a022 * l0A + (*it).a122 * lHeA + (*it).a222 * lVA);
	}
=======
	std::for_each(effReactingList.begin(), effReactingList.end(),
			[this,&partials](ProductionPairMap::value_type const& currMapItem) {

				auto const& currPair = currMapItem.second;

				// Get the two reacting clusters
				auto const& firstReactant = currPair.first;
				auto const& secondReactant = currPair.second;
				double l0A = firstReactant.getConcentration(0.0, 0.0);
				double l0B = secondReactant.getConcentration(0.0, 0.0);
				double lHeA = firstReactant.getHeMomentum();
				double lHeB = secondReactant.getHeMomentum();
				double lVA = firstReactant.getVMomentum();
				double lVB = secondReactant.getVMomentum();

				// Compute the contribution from the first part of the reacting pair
				auto value = currPair.kConstant / (double) nTot;
				auto index = firstReactant.getId() - 1;
				partials[index] += value
				* (currPair.a000 * l0B + currPair.a010 * lHeB + currPair.a020 * lVB);
				psiHeMomentPartials[index] += value
				* (currPair.a001 * l0B + currPair.a011 * lHeB + currPair.a021 * lVB);
				psiVMomentPartials[index] += value
				* (currPair.a002 * l0B + currPair.a012 * lHeB + currPair.a022 * lVB);
				index = firstReactant.getHeMomentumId() - 1;
				partials[index] += value
				* (currPair.a100 * l0B + currPair.a110 * lHeB + currPair.a120 * lVB);
				psiHeMomentPartials[index] += value
				* (currPair.a101 * l0B + currPair.a111 * lHeB + currPair.a121 * lVB);
				psiVMomentPartials[index] += value
				* (currPair.a102 * l0B + currPair.a112 * lHeB + currPair.a122 * lVB);
				index = firstReactant.getVMomentumId() - 1;
				partials[index] += value
				* (currPair.a200 * l0B + currPair.a210 * lHeB + currPair.a220 * lVB);
				psiHeMomentPartials[index] += value
				* (currPair.a201 * l0B + currPair.a211 * lHeB + currPair.a221 * lVB);
				psiVMomentPartials[index] += value
				* (currPair.a202 * l0B + currPair.a212 * lHeB + currPair.a222 * lVB);
				// Compute the contribution from the second part of the reacting pair
				index = secondReactant.getId() - 1;
				partials[index] += value
				* (currPair.a000 * l0A + currPair.a100 * lHeA + currPair.a200 * lVA);
				psiHeMomentPartials[index] += value
				* (currPair.a001 * l0A + currPair.a101 * lHeA + currPair.a201 * lVA);
				psiVMomentPartials[index] += value
				* (currPair.a002 * l0A + currPair.a102 * lHeA + currPair.a202 * lVA);
				index = secondReactant.getHeMomentumId() - 1;
				partials[index] += value
				* (currPair.a010 * l0A + currPair.a110 * lHeA + currPair.a210 * lVA);
				psiHeMomentPartials[index] += value
				* (currPair.a011 * l0A + currPair.a111 * lHeA + currPair.a211 * lVA);
				psiVMomentPartials[index] += value
				* (currPair.a012 * l0A + currPair.a112 * lHeA + currPair.a212 * lVA);
				index = secondReactant.getVMomentumId() - 1;
				partials[index] += value
				* (currPair.a020 * l0A + currPair.a120 * lHeA + currPair.a220 * lVA);
				psiHeMomentPartials[index] += value
				* (currPair.a021 * l0A + currPair.a121 * lHeA + currPair.a221 * lVA);
				psiVMomentPartials[index] += value
				* (currPair.a022 * l0A + currPair.a122 * lHeA + currPair.a222 * lVA);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSISuperCluster::getCombinationPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int index = 0;
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
	// Loop over all the combining clusters
	for (auto it = effCombiningList.begin(); it != effCombiningList.end();
			++it) {
		// Get the two reacting clusters
		cluster = (*it).first;
		double l0B = cluster->getConcentration(0.0, 0.0);
		double lHeB = cluster->getHeMomentum();
		double lVB = cluster->getVMomentum();

		// Compute the contribution from the combining cluster
		value = *((*it).kConstant) / (double) nTot;
		index = cluster->getId() - 1;
		partials[index] -= value
				* ((*it).a000 * l0 + (*it).a100 * l1He + (*it).a200 * l1V);
		heMomentumPartials[index] -= value
				* ((*it).a001 * l0 + (*it).a101 * l1He + (*it).a201 * l1V);
		vMomentumPartials[index] -= value
				* ((*it).a002 * l0 + (*it).a102 * l1He + (*it).a202 * l1V);
		index = cluster->getHeMomentumId() - 1;
		partials[index] -= value
				* ((*it).a010 * l0 + (*it).a110 * l1He + (*it).a210 * l1V);
		heMomentumPartials[index] -= value
				* ((*it).a011 * l0 + (*it).a111 * l1He + (*it).a211 * l1V);
		vMomentumPartials[index] -= value
				* ((*it).a012 * l0 + (*it).a112 * l1He + (*it).a212 * l1V);
		index = cluster->getVMomentumId() - 1;
		partials[index] -= value
				* ((*it).a020 * l0 + (*it).a120 * l1He + (*it).a220 * l1V);
		heMomentumPartials[index] -= value
				* ((*it).a021 * l0 + (*it).a121 * l1He + (*it).a221 * l1V);
		vMomentumPartials[index] -= value
				* ((*it).a022 * l0 + (*it).a122 * l1He + (*it).a222 * l1V);
		// Compute the contribution from this cluster
		index = id - 1;
		partials[index] -= value
				* ((*it).a000 * l0B + (*it).a010 * lHeB + (*it).a020 * lVB);
		heMomentumPartials[index] -= value
				* ((*it).a001 * l0B + (*it).a011 * lHeB + (*it).a021 * lVB);
		vMomentumPartials[index] -= value
				* ((*it).a002 * l0B + (*it).a012 * lHeB + (*it).a022 * lVB);
		index = heMomId - 1;
		partials[index] -= value
				* ((*it).a100 * l0B + (*it).a110 * lHeB + (*it).a120 * lVB);
		heMomentumPartials[index] -= value
				* ((*it).a101 * l0B + (*it).a111 * lHeB + (*it).a121 * lVB);
		vMomentumPartials[index] -= value
				* ((*it).a102 * l0B + (*it).a112 * lHeB + (*it).a122 * lVB);
		index = vMomId - 1;
		partials[index] -= value
				* ((*it).a200 * l0B + (*it).a210 * lHeB + (*it).a220 * lVB);
		heMomentumPartials[index] -= value
				* ((*it).a201 * l0B + (*it).a211 * lHeB + (*it).a221 * lVB);
		vMomentumPartials[index] -= value
				* ((*it).a202 * l0B + (*it).a212 * lHeB + (*it).a222 * lVB);
	}
=======
	// Visit all the combining clusters
	std::for_each(effCombiningList.begin(), effCombiningList.end(),
			[this,&partials](CombiningClusterMap::value_type const& currMapItem) {
				// Get the combining clusters
				auto const& currComb = currMapItem.second;
				auto const& cluster = currComb.first;
				double l0B = cluster.getConcentration(0.0, 0.0);
				double lHeB = cluster.getHeMomentum();
				double lVB = cluster.getVMomentum();

				// Compute the contribution from the combining cluster
				auto value = currComb.kConstant / (double) nTot;
				auto index = cluster.getId() - 1;
				partials[index] -= value
				* (currComb.a000 * l0 + currComb.a100 * l1He + currComb.a200 * l1V);
				psiHeMomentPartials[index] -= value
				* (currComb.a001 * l0 + currComb.a101 * l1He + currComb.a201 * l1V);
				psiVMomentPartials[index] -= value
				* (currComb.a002 * l0 + currComb.a102 * l1He + currComb.a202 * l1V);
				index = cluster.getHeMomentumId() - 1;
				partials[index] -= value
				* (currComb.a010 * l0 + currComb.a110 * l1He + currComb.a210 * l1V);
				psiHeMomentPartials[index] -= value
				* (currComb.a011 * l0 + currComb.a111 * l1He + currComb.a211 * l1V);
				psiVMomentPartials[index] -= value
				* (currComb.a012 * l0 + currComb.a112 * l1He + currComb.a212 * l1V);
				index = cluster.getVMomentumId() - 1;
				partials[index] -= value
				* (currComb.a020 * l0 + currComb.a120 * l1He + currComb.a220 * l1V);
				psiHeMomentPartials[index] -= value
				* (currComb.a021 * l0 + currComb.a121 * l1He + currComb.a221 * l1V);
				psiVMomentPartials[index] -= value
				* (currComb.a022 * l0 + currComb.a122 * l1He + currComb.a222 * l1V);
				// Compute the contribution from this cluster
				index = id - 1;
				partials[index] -= value
				* (currComb.a000 * l0B + currComb.a010 * lHeB + currComb.a020 * lVB);
				psiHeMomentPartials[index] -= value
				* (currComb.a001 * l0B + currComb.a011 * lHeB + currComb.a021 * lVB);
				psiVMomentPartials[index] -= value
				* (currComb.a002 * l0B + currComb.a012 * lHeB + currComb.a022 * lVB);
				index = heMomId - 1;
				partials[index] -= value
				* (currComb.a100 * l0B + currComb.a110 * lHeB + currComb.a120 * lVB);
				psiHeMomentPartials[index] -= value
				* (currComb.a101 * l0B + currComb.a111 * lHeB + currComb.a121 * lVB);
				psiVMomentPartials[index] -= value
				* (currComb.a102 * l0B + currComb.a112 * lHeB + currComb.a122 * lVB);
				index = vMomId - 1;
				partials[index] -= value
				* (currComb.a200 * l0B + currComb.a210 * lHeB + currComb.a220 * lVB);
				psiHeMomentPartials[index] -= value
				* (currComb.a201 * l0B + currComb.a211 * lHeB + currComb.a221 * lVB);
				psiVMomentPartials[index] -= value
				* (currComb.a202 * l0B + currComb.a212 * lHeB + currComb.a222 * lVB);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSISuperCluster::getDissociationPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int index = 0;
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
	// Loop over all the dissociating pairs
	for (auto it = effDissociatingList.begin(); it != effDissociatingList.end();
			++it) {
		// Get the dissociating clusters
		cluster = (*it).first;
		// Compute the contribution from the dissociating cluster
		value = *((*it).kConstant) / (double) nTot;
		index = cluster->getId() - 1;
		partials[index] += value * ((*it).a00);
		heMomentumPartials[index] += value * ((*it).a01);
		vMomentumPartials[index] += value * ((*it).a02);
		index = cluster->getHeMomentumId() - 1;
		partials[index] += value * ((*it).a10);
		heMomentumPartials[index] += value * ((*it).a11);
		vMomentumPartials[index] += value * ((*it).a12);
		index = cluster->getVMomentumId() - 1;
		partials[index] += value * ((*it).a20);
		heMomentumPartials[index] += value * ((*it).a21);
		vMomentumPartials[index] += value * ((*it).a22);
	}
=======
	// Visit all the dissociating pairs
	std::for_each(effDissociatingList.begin(), effDissociatingList.end(),
			[this,&partials](DissociationPairMap::value_type const& currMapItem) {
				auto& currPair = currMapItem.second;

				// Get the dissociating clusters
				auto const& cluster = currPair.first;
				// Compute the contribution from the dissociating cluster
				auto value = currPair.kConstant / (double) nTot;
				auto index = cluster.getId() - 1;
				partials[index] += value * (currPair.a00);
				psiHeMomentPartials[index] += value * (currPair.a01);
				psiVMomentPartials[index] += value * (currPair.a02);
				index = cluster.getHeMomentumId() - 1;
				partials[index] += value * (currPair.a10);
				psiHeMomentPartials[index] += value * (currPair.a11);
				psiVMomentPartials[index] += value * (currPair.a12);
				index = cluster.getVMomentumId() - 1;
				partials[index] += value * (currPair.a20);
				psiHeMomentPartials[index] += value * (currPair.a21);
				psiVMomentPartials[index] += value * (currPair.a22);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSISuperCluster::getEmissionPartialDerivatives(
		std::vector<double> & partials) const {
<<<<<<< HEAD
	// Initial declarations
	int index = 0;
	double value = 0.0;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Emission
	// A --> B + D, A being this cluster
	// The flux for A is
	// F(C_A) = - k-_(B,D)*C_A
	// Thus, the partial derivatives
	// dF(C_A)/dC_A = - k-_(B,D)

<<<<<<< HEAD
	// Loop over all the emission pairs
	for (auto it = effEmissionList.begin(); it != effEmissionList.end(); ++it) {
		// Compute the contribution from the dissociating cluster
		value = *((*it).kConstant) / (double) nTot;
		index = id - 1;
		partials[index] -= value * ((*it).a00);
		heMomentumPartials[index] -= value * ((*it).a01);
		vMomentumPartials[index] -= value * ((*it).a02);
		index = heMomId - 1;
		partials[index] -= value * ((*it).a10);
		heMomentumPartials[index] -= value * ((*it).a11);
		vMomentumPartials[index] -= value * ((*it).a12);
		index = vMomId - 1;
		partials[index] -= value * ((*it).a20);
		heMomentumPartials[index] -= value * ((*it).a21);
		vMomentumPartials[index] -= value * ((*it).a22);
	}
=======
	// Visit all the emission pairs
	std::for_each(effEmissionList.begin(), effEmissionList.end(),
			[this,&partials](DissociationPairMap::value_type const& currMapItem) {
				auto& currPair = currMapItem.second;

				// Compute the contribution from the dissociating cluster
				auto value = currPair.kConstant / (double) nTot;
				auto index = id - 1;
				partials[index] -= value * (currPair.a00);
				psiHeMomentPartials[index] -= value * (currPair.a01);
				psiVMomentPartials[index] -= value * (currPair.a02);
				index = heMomId - 1;
				partials[index] -= value * (currPair.a10);
				psiHeMomentPartials[index] -= value * (currPair.a11);
				psiVMomentPartials[index] -= value * (currPair.a12);
				index = vMomId - 1;
				partials[index] -= value * (currPair.a20);
				psiHeMomentPartials[index] -= value * (currPair.a21);
				psiVMomentPartials[index] -= value * (currPair.a22);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSISuperCluster::getHeMomentPartialDerivatives(
		std::vector<double> & partials) const {
	// Loop on the size of the vector
	for (int i = 0; i < partials.size(); i++) {
		// Set to the values that were already computed
<<<<<<< HEAD
		partials[i] = heMomentumPartials[i];
=======
		partials[i] = psiHeMomentPartials[i];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

void PSISuperCluster::getVMomentPartialDerivatives(
		std::vector<double> & partials) const {
	// Loop on the size of the vector
	for (int i = 0; i < partials.size(); i++) {
		// Set to the values that were already computed
<<<<<<< HEAD
		partials[i] = vMomentumPartials[i];
=======
		partials[i] = psiVMomentPartials[i];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}
<<<<<<< HEAD
=======

void PSISuperCluster::dumpCoefficients(std::ostream& os,
		PSISuperCluster::ProductionCoefficientBase const& curr) const {

	os << "a[0-2][0-2][0-2]:" << ' ' << curr.a000 << ' ' << curr.a001 << ' '
			<< curr.a002 << ' ' << curr.a100 << ' ' << curr.a101 << ' '
			<< curr.a102 << ' ' << curr.a200 << ' ' << curr.a201 << ' '
			<< curr.a202 << ' ' << curr.a010 << ' ' << curr.a011 << ' '
			<< curr.a012 << ' ' << curr.a020 << ' ' << curr.a021 << ' '
			<< curr.a022 << ' ' << curr.a110 << ' ' << curr.a111 << ' '
			<< curr.a112 << ' ' << curr.a120 << ' ' << curr.a121 << ' '
			<< curr.a122 << ' ' << curr.a210 << ' ' << curr.a211 << ' '
			<< curr.a212 << ' ' << curr.a220 << ' ' << curr.a221 << ' '
			<< curr.a222;
}

void PSISuperCluster::dumpCoefficients(std::ostream& os,
		PSISuperCluster::SuperClusterDissociationPair const& currPair) const {

	os << "a[0-2][0-2]:" << ' ' << currPair.a00 << ' ' << currPair.a01 << ' '
			<< currPair.a02 << ' ' << currPair.a10 << ' ' << currPair.a11 << ' '
			<< currPair.a12 << ' ' << currPair.a20 << ' ' << currPair.a21 << ' '
			<< currPair.a22;
}

void PSISuperCluster::outputCoefficientsTo(std::ostream& os) const {

	os << "id: " << id << '\n';
	os << "reacting: " << effReactingList.size() << '\n';
	std::for_each(effReactingList.begin(), effReactingList.end(),
			[this,&os](ProductionPairMap::value_type const& currMapItem) {
				auto const& currPair = currMapItem.second;
				os << "first: " << currPair.first.getId()
				<< "; second: " << currPair.second.getId()
				<< "; ";
				dumpCoefficients(os, currPair);
				os << '\n';
			});

	os << "combining: " << effCombiningList.size() << '\n';
	std::for_each(effCombiningList.begin(), effCombiningList.end(),
			[this,&os](CombiningClusterMap::value_type const& currMapItem) {
				auto const& currComb = currMapItem.second;
				os << "other: " << currComb.first.getId()
				<< "; ";
				dumpCoefficients(os, currComb);
				os << '\n';
			});

	os << "dissociating: " << effDissociatingList.size() << '\n';
	std::for_each(effDissociatingList.begin(), effDissociatingList.end(),
			[this,&os](DissociationPairMap::value_type const& currMapItem) {
				auto const& currPair = currMapItem.second;
				os << "first: " << currPair.first.getId()
				<< "; second: " << currPair.second.getId()
				<< "; ";
				dumpCoefficients(os, currPair);
				os << '\n';
			});

	os << "emitting: " << effEmissionList.size() << '\n';
	std::for_each(effEmissionList.begin(), effEmissionList.end(),
			[this,&os](DissociationPairMap::value_type const& currMapItem) {
				auto const& currPair = currMapItem.second;
				os << "first: " << currPair.first.getId()
				<< "; second: " << currPair.second.getId()
				<< "; ";
				dumpCoefficients(os, currPair);
				os << '\n';
			});
}

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
