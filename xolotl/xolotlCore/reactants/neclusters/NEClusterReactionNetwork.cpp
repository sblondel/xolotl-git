#include "NEClusterReactionNetwork.h"
#include "NECluster.h"
#include "NESuperCluster.h"
#include <xolotlPerf.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <Constants.h>

using namespace xolotlCore;

<<<<<<< HEAD
void NEClusterReactionNetwork::setDefaultPropsAndNames() {
	// Shared pointers for the cluster type map
	std::shared_ptr<std::vector<std::shared_ptr<IReactant>>>xeVector =
	std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> vVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> iVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> xeVVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> xeIVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> superVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();

	// Initialize default properties
	dissociationsEnabled = true;
	numXeClusters = 0;
	numVClusters = 0;
	numIClusters = 0;
	numXeVClusters = 0;
	numXeIClusters = 0;
	numSuperClusters = 0;
	maxXeClusterSize = 0;
	maxVClusterSize = 0;
	maxIClusterSize = 0;
	maxXeVClusterSize = 0;
	maxXeIClusterSize = 0;

	// Initialize the current and last size to 0
	networkSize = 0;
	// Set the reactant names
	names.push_back(xeType);
	names.push_back(vType);
	names.push_back(iType);
	names.push_back(NESuperType);
	// Set the compound reactant names
	compoundNames.push_back(xeVType);
	compoundNames.push_back(xeIType);

	// Setup the cluster type map
	clusterTypeMap[xeType] = xeVector;
	clusterTypeMap[vType] = vVector;
	clusterTypeMap[iType] = iVector;
	clusterTypeMap[xeVType] = xeVVector;
	clusterTypeMap[xeIType] = xeIVector;
	clusterTypeMap[NESuperType] = superVector;

	return;
}

NEClusterReactionNetwork::NEClusterReactionNetwork() :
		ReactionNetwork() {
	// Setup the properties map and the name lists
	setDefaultPropsAndNames();

	return;
}

NEClusterReactionNetwork::NEClusterReactionNetwork(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		ReactionNetwork(registry) {
	// Setup the properties map and the name lists
	setDefaultPropsAndNames();

	return;
}

NEClusterReactionNetwork::NEClusterReactionNetwork(
		const NEClusterReactionNetwork &other) :
		ReactionNetwork(other) {
	// The size and ids do not need to be copied. They will be fixed when the
	// reactants are added.

	// Reset the properties table so that it can be properly updated when the
	// network is filled.
	setDefaultPropsAndNames();
	// Get all of the reactants from the other network and add them to this one
	// Load the single-species clusters. Calling getAll() will not work because
	// it is not const.
	std::vector<std::shared_ptr<IReactant> > reactants;
	for (auto it = other.singleSpeciesMap.begin();
			it != other.singleSpeciesMap.end(); ++it) {
		reactants.push_back(it->second);
	}
	// Load the mixed-species clusters
	for (auto it = other.mixedSpeciesMap.begin();
			it != other.mixedSpeciesMap.end(); ++it) {
		reactants.push_back(it->second);
	}
	// Load the super-species clusters
	for (auto it = other.superSpeciesMap.begin();
			it != other.superSpeciesMap.end(); ++it) {
		reactants.push_back(it->second);
	}
	for (unsigned int i = 0; i < reactants.size(); i++) {
		add(reactants[i]->clone());
	}
=======
NEClusterReactionNetwork::NEClusterReactionNetwork(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		ReactionNetwork( { ReactantType::V, ReactantType::I, ReactantType::Xe,
				ReactantType::XeV, ReactantType::XeI, ReactantType::NESuper },
				ReactantType::NESuper, registry) {

	// Initialize default properties
	dissociationsEnabled = true;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

double NEClusterReactionNetwork::calculateDissociationConstant(
<<<<<<< HEAD
		DissociationReaction * reaction) const {
=======
		const DissociationReaction& reaction) const {

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// If the dissociations are not allowed
	if (!dissociationsEnabled)
		return 0.0;

	// Compute the atomic volume
	double atomicVolume = 0.5 * xolotlCore::uraniumDioxydeLatticeConstant
			* xolotlCore::uraniumDioxydeLatticeConstant
			* xolotlCore::uraniumDioxydeLatticeConstant;

	// Get the rate constant from the reverse reaction
<<<<<<< HEAD
	double kPlus = reaction->reverseReaction->kConstant;
=======
	double kPlus = reaction.reverseReaction->kConstant;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Calculate and return
	double bindingEnergy = computeBindingEnergy(reaction);
	double k_minus_exp = exp(
			-1.0 * bindingEnergy / (xolotlCore::kBoltzmann * temperature));
	double k_minus = (1.0 / atomicVolume) * kPlus * k_minus_exp;

	return k_minus;
}

void NEClusterReactionNetwork::createReactionConnectivity() {
	// Initial declarations
	int firstSize = 0, secondSize = 0, productSize = 0;

	// Single species clustering (Xe)
	// We know here that only Xe_1 can cluster so we simplify the search
	// Xe_(a-i) + Xe_i --> Xe_a
	firstSize = 1;
<<<<<<< HEAD
	auto singleXeCluster = get(xeType, firstSize);
	// Get all the Xe clusters
	auto xeClusters = getAll(xeType);
	// Loop on them
	for (auto it = xeClusters.begin(); it != xeClusters.end(); it++) {
		// Get the size of the second reactant and product
		secondSize = (*it)->getSize();
		productSize = firstSize + secondSize;
		// Get the product cluster for the reaction
		auto product = get(xeType, productSize);
		// Check that the reaction can occur
		if (product
				&& (singleXeCluster->getDiffusionFactor() > 0.0
						|| (*it)->getDiffusionFactor() > 0.0)) {
			// Create a production reaction
			auto reaction = std::make_shared<ProductionReaction>(
					singleXeCluster, (*it));
			// Tell the reactants that they are in this reaction
			singleXeCluster->createCombination(reaction);
			(*it)->createCombination(reaction);
			product->createProduction(reaction);

			// Check if the reverse reaction is allowed
			checkDissociationConnectivity(product, reaction);
=======
	auto singleXeCluster = get(Species::Xe, firstSize);
	// Get all the Xe clusters
	auto const& xeClusters = getAll(ReactantType::Xe);
	// Consider each Xe cluster.
	for (auto const& currMapItem : getAll(ReactantType::Xe)) {

		auto& xeReactant = *(currMapItem.second);

		// Get the size of the second reactant and product
		secondSize = xeReactant.getSize();
		productSize = firstSize + secondSize;
		// Get the product cluster for the reaction
		auto product = get(Species::Xe, productSize);
		// Check that the reaction can occur
		if (product
				&& (singleXeCluster->getDiffusionFactor() > 0.0
						|| xeReactant.getDiffusionFactor() > 0.0)) {
			// Create a production reaction
			auto reaction = std::make_shared<ProductionReaction>(
					*singleXeCluster, xeReactant);
			// Tell the reactants that they are in this reaction
			singleXeCluster->participateIn(*reaction);
			xeReactant.participateIn(*reaction);
			product->resultFrom(*reaction);

			// Check if the reverse reaction is allowed
			checkForDissociation(product, reaction);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
	}

	return;
}

<<<<<<< HEAD
void NEClusterReactionNetwork::checkDissociationConnectivity(
		IReactant * emittingReactant,
		std::shared_ptr<ProductionReaction> reaction) {
	// Check if at least one of the potentially emitted cluster is size one
	if (reaction->first->getSize() != 1 && reaction->second->getSize() != 1) {
=======
void NEClusterReactionNetwork::checkForDissociation(
		IReactant * emittingReactant,
		std::shared_ptr<ProductionReaction> reaction) {
	// Check if at least one of the potentially emitted cluster is size one
	if (reaction->first.getSize() != 1 && reaction->second.getSize() != 1) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Don't add the reverse reaction
		return;
	}

	// The reaction can occur, create the dissociation
	// Create a dissociation reaction
<<<<<<< HEAD
	auto dissociationReaction = std::make_shared<DissociationReaction>(
			emittingReactant, reaction->first, reaction->second);
	// Set the reverse reaction
	dissociationReaction->reverseReaction = reaction.get();
	// Tell the reactants that their are in this reaction
	reaction->first->createDissociation(dissociationReaction);
	reaction->second->createDissociation(dissociationReaction);
	emittingReactant->createEmission(dissociationReaction);
=======
	// TODO can this be on the stack?
	std::unique_ptr<DissociationReaction> dissociationReaction(
			new DissociationReaction(*emittingReactant, reaction->first,
					reaction->second));
	// Set the reverse reaction
	dissociationReaction->reverseReaction = reaction.get();
	// Tell the reactants that their are in this reaction
	reaction->first.participateIn(*dissociationReaction);
	reaction->second.participateIn(*dissociationReaction);
	emittingReactant->emitFrom(*dissociationReaction);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NEClusterReactionNetwork::setTemperature(double temp) {
	ReactionNetwork::setTemperature(temp);

	computeRateConstants();

	return;
}

<<<<<<< HEAD
double NEClusterReactionNetwork::getTemperature() const {
	return temperature;
}

IReactant * NEClusterReactionNetwork::get(const std::string& type,
		const int size) const {
	// Local Declarations
	static std::map<std::string, int> composition = { { xeType, 0 },
			{ vType, 0 }, { iType, 0 }, { heType, 0 } };
	std::shared_ptr<IReactant> retReactant;

	// Setup the composition map to default values because it is static
	composition[xeType] = 0;
	composition[vType] = 0;
	composition[iType] = 0;

	// Only pull the reactant if the name and size are valid
	if ((type == xeType || type == vType || type == iType) && size >= 1) {
		composition[type] = size;
		//std::string encodedName = NECluster::encodeCompositionAsName(composition);
		// Make sure the reactant is in the map
		std::string compStr = Reactant::toCanonicalString(type, composition);
		if (singleSpeciesMap.count(compStr)) {
			retReactant = singleSpeciesMap.at(compStr);
		}
	}

	return retReactant.get();
}

IReactant * NEClusterReactionNetwork::getCompound(const std::string& type,
		const std::vector<int>& sizes) const {
	// Local Declarations
	static std::map<std::string, int> composition = { { xeType, 0 },
			{ vType, 0 }, { iType, 0 }, { heType, 0 } };
	std::shared_ptr<IReactant> retReactant;

	// Setup the composition map to default values because it is static
	composition[xeType] = 0;
	composition[vType] = 0;
	composition[iType] = 0;

	// Only pull the reactant if the name is valid and there are enough sizes
	// to fill the composition.
	if ((type == xeVType || type == xeIType) && sizes.size() == 3) {
		composition[xeType] = sizes[0];
		composition[vType] = sizes[1];
		composition[iType] = sizes[2];
		// Make sure the reactant is in the map
		std::string compStr = Reactant::toCanonicalString(type, composition);
		if (mixedSpeciesMap.count(compStr)) {
			retReactant = mixedSpeciesMap.at(compStr);
		}
	}

	return retReactant.get();
}

IReactant * NEClusterReactionNetwork::getSuper(const std::string& type,
		const int size) const {
	// Local Declarations
	static std::map<std::string, int> composition = { { xeType, 0 },
			{ vType, 0 }, { iType, 0 }, { heType, 0 } };
	std::shared_ptr<IReactant> retReactant;

	// Setup the composition map to default values
	composition[xeType] = 0;
	composition[vType] = 0;
	composition[iType] = 0;

	// Only pull the reactant if the name and size are valid.
	if (type == NESuperType && size >= 1) {
		composition[xeType] = size;
		// Make sure the reactant is in the map
		std::string compStr = Reactant::toCanonicalString(type, composition);
		if (superSpeciesMap.count(compStr)) {
			retReactant = superSpeciesMap.at(compStr);
		}
	}

	return retReactant.get();
}

const std::shared_ptr<std::vector<IReactant *>> & NEClusterReactionNetwork::getAll() const {
	return allReactants;
}

std::vector<IReactant *> NEClusterReactionNetwork::getAll(
		const std::string& name) const {
	// Local Declarations
	std::vector<IReactant *> reactants;

	// Only pull the reactants if the name is valid
	if (name == xeType || name == vType || name == iType || name == xeVType
			|| name == xeIType || name == NESuperType) {
		std::shared_ptr<std::vector<std::shared_ptr<IReactant>> > storedReactants =
				clusterTypeMap.at(name);
		int vecSize = storedReactants->size();
		for (int i = 0; i < vecSize; i++) {
			reactants.push_back(storedReactants->at(i).get());
		}
	}

	return reactants;
}

void NEClusterReactionNetwork::add(std::shared_ptr<IReactant> reactant) {
	// Local Declarations
	int numXe = 0, numV = 0, numI = 0;
	bool isMixed = false;
	int* numClusters = nullptr;
	int* maxClusterSize = nullptr;

	// Only add a complete reactant
	if (reactant != NULL) {
		// Get the composition
		auto composition = reactant->getComposition();
		std::string compStr = reactant->getCompositionString();

		// Get the species sizes
		numXe = composition.at(xeType);
		numV = composition.at(vType);
		numI = composition.at(iType);

		// Determine if the cluster is a compound. If there is more than one
		// type, then the check below will sum to greater than one and we know
		// that we have a mixed cluster.
		isMixed = ((numXe > 0) + (numV > 0) + (numI > 0)) > 1;
		// Only add the element if we don't already have it
		// Add the compound or regular reactant.
		if (isMixed && mixedSpeciesMap.count(compStr) == 0) {
			// Put the compound in its map
			mixedSpeciesMap[compStr] = reactant;
			// Figure out whether we have XeV or XeI
			if (numV > 0) {
				numClusters = &numXeVClusters;
				maxClusterSize = &maxXeVClusterSize;
			} else {
				numClusters = &numXeIClusters;
				maxClusterSize = &maxXeIClusterSize;
			}
		} else if (!isMixed && singleSpeciesMap.count(compStr) == 0) {
			/// Put the reactant in its map
			singleSpeciesMap[compStr] = reactant;

			// Figure out whether we have Xe, V or I
			if (numXe > 0) {
				numClusters = &numXeClusters;
				maxClusterSize = &maxXeClusterSize;
			} else if (numV > 0) {
				numClusters = &numVClusters;
				maxClusterSize = &maxVClusterSize;
			} else {
				numClusters = &numIClusters;
				maxClusterSize = &maxIClusterSize;
			}
		} else {
			std::stringstream errStream;
			errStream << "NEClusterReactionNetwork Message: "
					<< "Duplicate Reactant (Xe=" << numXe << ",V=" << numV
					<< ",I=" << numI << ") not added!" << std::endl;
			throw errStream.str();
		}

		// Increment the number of total clusters of this type
		(*numClusters)++;
		// Increment the max cluster size key
		int clusterSize = numXe + numV + numI;
		(*maxClusterSize) = std::max(clusterSize, *maxClusterSize);
		// Update the size
		++networkSize;
		// Set the id for this cluster
		reactant->setId(networkSize);
		// Get the vector for this reactant from the type map
		auto clusters = clusterTypeMap[reactant->getType()];

		clusters->push_back(reactant);
		// Add the pointer to the list of all clusters
		allReactants->push_back(reactant.get());
	}

	return;
}

void NEClusterReactionNetwork::addSuper(std::shared_ptr<IReactant> reactant) {
	// Local Declarations
	int numXe = 0, numV = 0, numI = 0;
	bool isMixed = false;
	int* numClusters = nullptr;

	// Only add a complete reactant
	if (reactant != NULL) {
		// Get the composition
		auto composition = reactant->getComposition();
		// Get the species sizes
		numXe = composition.at(xeType);
		numV = composition.at(vType);
		numI = composition.at(iType);
		// Determine if the cluster is a compound. If there is more than one
		// type, then the check below will sum to greater than one and we know
		// that we have a mixed cluster.
		isMixed = ((numXe > 0) + (numV > 0) + (numI > 0)) > 1;
		// Only add the element if we don't already have it
		// Add the compound or regular reactant.
		std::string compStr = reactant->getCompositionString();
		if (!isMixed && superSpeciesMap.count(compStr) == 0) {
			// Put the compound in its map
			superSpeciesMap[compStr] = reactant;
			// Set the key
			numClusters = &numSuperClusters;
		} else {
			std::stringstream errStream;
			errStream << "NEClusterReactionNetwork Message: "
					<< "Duplicate Super Reactant (Xe=" << numXe << ",V=" << numV
					<< ",I=" << numI << ") not added!" << std::endl;
			throw errStream.str();
		}

		// Increment the number of total clusters of this type
		(*numClusters)++;
		// Update the size
		++networkSize;
		// Set the id for this cluster
		reactant->setId(networkSize);
		// Get the vector for this reactant from the type map
		auto clusters = clusterTypeMap[reactant->getType()];
		clusters->push_back(reactant);
		// Add the pointer to the list of all clusters
		allReactants->push_back(reactant.get());
	}

	return;
}

void NEClusterReactionNetwork::removeReactants(
		const std::vector<IReactant*>& doomedReactants) {

	// Build a ReactantMatcher functor for the doomed reactants.
	// Doing this here allows us to construct the canonical composition
	// strings for the doomed reactants once and reuse them.
	// If we used an anonymous functor object in the std::remove_if
	// calls we would build these strings several times in this function.
	ReactionNetwork::ReactantMatcher doomedReactantMatcher(doomedReactants);

	// Remove the doomed reactants from our collection of all known reactants.
	auto ariter = std::remove_if(allReactants->begin(), allReactants->end(),
			doomedReactantMatcher);
	allReactants->erase(ariter, allReactants->end());

	// Remove the doomed reactants from the type-specific cluster vectors.
	// First, determine all cluster types used by clusters in the collection
	// of doomed reactants...
	std::set<std::string> typesUsed;
	for (auto reactant : doomedReactants) {
		typesUsed.insert(reactant->getType());
	}

	// ...Next, examine each type's collection of clusters and remove the
	// doomed reactants.
	for (auto currType : typesUsed) {
		auto clusters = clusterTypeMap[currType];
		auto citer = std::remove_if(clusters->begin(), clusters->end(),
				doomedReactantMatcher);
		clusters->erase(citer, clusters->end());
	}

	// Remove the doomed reactants from the SpeciesMap.
	// We cannot use std::remove_if and our ReactantMatcher here
	// because std::remove_if reorders the elements in the underlying
	// container to move the doomed elements to the end of the container,
	// but the std::map doesn't support reordering.
	for (auto reactant : doomedReactants) {
		if (reactant->isMixed())
			mixedSpeciesMap.erase(reactant->getCompositionString());
		else
			singleSpeciesMap.erase(reactant->getCompositionString());
	}

	return;
}

void NEClusterReactionNetwork::reinitializeNetwork() {
	// Recount the number of Xe clusters
	numXeClusters = 0;
	// Reset the Ids
	int id = 0;
	for (auto it = allReactants->begin(); it != allReactants->end(); ++it) {
		id++;
		(*it)->setId(id);
		(*it)->setXeMomentumId(id);

		(*it)->optimizeReactions();

		if ((*it)->getType() == xeType)
			numXeClusters++;
	}

	// Reset the network size
	networkSize = id;

	// Get all the super clusters and loop on them
	for (auto it = clusterTypeMap[NESuperType]->begin();
			it != clusterTypeMap[NESuperType]->end(); ++it) {
		id++;
		(*it)->setXeMomentumId(id);
=======
void NEClusterReactionNetwork::reinitializeNetwork() {
	// Reset the Ids
	int id = 0;
	std::for_each(allReactants.begin(), allReactants.end(),
			[&id](IReactant& currReactant) {
				id++;
				currReactant.setId(id);
				currReactant.setXeMomentumId(id);

				currReactant.optimizeReactions();
			});

	// Get all the super clusters and loop on them
	for (auto const& currMapItem : clusterTypeMap.at(ReactantType::NESuper)) {

		auto& currCluster = static_cast<NESuperCluster&>(*(currMapItem.second));
		id++;
		currCluster.setXeMomentumId(id);

		currCluster.optimizeReactions();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

void NEClusterReactionNetwork::reinitializeConnectivities() {
	// Loop on all the reactants to reset their connectivities
<<<<<<< HEAD
	for (auto it = allReactants->begin(); it != allReactants->end(); ++it) {
		(*it)->resetConnectivities();
	}
=======
	std::for_each(allReactants.begin(), allReactants.end(),
			[](IReactant& currReactant) {
				currReactant.resetConnectivities();
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NEClusterReactionNetwork::updateConcentrationsFromArray(
		double * concentrations) {
<<<<<<< HEAD
	// Local Declarations
	auto reactants = getAll();
	int size = reactants->size();
	int id = 0;

	// Set the concentrations
	concUpdateCounter->increment();	// increment the update concentration counter
	for (int i = 0; i < size; i++) {
		id = reactants->at(i)->getId() - 1;
		reactants->at(i)->setConcentration(concentrations[id]);
	}

	// Set the moments
	for (int i = size - numSuperClusters; i < size; i++) {
		// Get the superCluster
		auto cluster = (NESuperCluster *) reactants->at(i);
		id = cluster->getId() - 1;
		cluster->setZerothMomentum(concentrations[id]);
		id = cluster->getXeMomentumId() - 1;
		cluster->setMomentum(concentrations[id]);
	}
=======

	// Set the concentration on each reactant.
	std::for_each(allReactants.begin(), allReactants.end(),
			[&concentrations](IReactant& currReactant) {
				auto id = currReactant.getId() - 1;
				currReactant.setConcentration(concentrations[id]);
			});

	// Set the moments
	auto const& superTypeMap = getAll(ReactantType::NESuper);
	std::for_each(superTypeMap.begin(), superTypeMap.end(),
			[&concentrations](const ReactantMap::value_type& currMapItem) {
				auto& cluster = static_cast<NESuperCluster&>(*(currMapItem.second));
				cluster.setZerothMomentum(concentrations[cluster.getId() - 1]);
				cluster.setMomentum(concentrations[cluster.getXeMomentumId() - 1]);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void NEClusterReactionNetwork::getDiagonalFill(int *diagFill) {
<<<<<<< HEAD
	// Get all the super clusters
	auto superClusters = getAll(NESuperType);
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Degrees of freedom is the total number of clusters in the network
	const int dof = getDOF();

<<<<<<< HEAD
	// Declarations for the loop
	std::vector<int> connectivity;
	int connectivityLength, id, index;

	// Get the connectivity for each reactant
	for (int i = 0; i < networkSize; i++) {
		// Get the reactant and its connectivity
		auto reactant = allReactants->at(i);
		connectivity = reactant->getConnectivity();
		connectivityLength = connectivity.size();
		// Get the reactant id so that the connectivity can be lined up in
		// the proper column
		id = reactant->getId() - 1;
		// Create the vector that will be inserted into the dFill map
		std::vector<int> columnIds;
		// Add it to the diagonal fill block
		for (int j = 0; j < connectivityLength; j++) {
			// The id starts at j*connectivity length and is always offset
			// by the id, which denotes the exact column.
			index = id * dof + j;
			diagFill[index] = connectivity[j];
			// Add a column id if the connectivity is equal to 1.
			if (connectivity[j] == 1) {
				columnIds.push_back(j);
			}
		}
		// Update the map
		dFillMap[id] = columnIds;
	}
	// Get the connectivity for each moment
	for (int i = 0; i < superClusters.size(); i++) {
		// Get the reactant and its connectivity
		auto reactant = superClusters[i];
		connectivity = reactant->getConnectivity();
		connectivityLength = connectivity.size();
		// Get the xenon momentum id so that the connectivity can be lined up in
		// the proper column
		id = reactant->getXeMomentumId() - 1;
=======
	// Get the connectivity for each reactant
	std::for_each(allReactants.begin(), allReactants.end(),
			[&diagFill, &dof, this](const IReactant& reactant) {
				// Get the reactant and its connectivity
				auto const& connectivity = reactant.getConnectivity();
				auto connectivityLength = connectivity.size();
				// Get the reactant id so that the connectivity can be lined up in
				// the proper column
				auto id = reactant.getId() - 1;
				// Create the vector that will be inserted into the dFill map
				std::vector<int> columnIds;
				// Add it to the diagonal fill block
				for (int j = 0; j < connectivityLength; j++) {
					// The id starts at j*connectivity length and is always offset
					// by the id, which denotes the exact column.
					auto index = id * dof + j;
					diagFill[index] = connectivity[j];
					// Add a column id if the connectivity is equal to 1.
					if (connectivity[j] == 1) {
						columnIds.push_back(j);
					}
				}
				// Update the map
				dFillMap[id] = columnIds;
			});

	// Get the connectivity for each moment
	for (auto const& currMapItem : getAll(ReactantType::NESuper)) {

		// Get the reactant and its connectivity
		auto const& reactant =
				static_cast<NESuperCluster&>(*(currMapItem.second));

		auto const& connectivity = reactant.getConnectivity();
		auto connectivityLength = connectivity.size();
		// Get the xenon momentum id so that the connectivity can be lined up in
		// the proper column
		auto id = reactant.getXeMomentumId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Create the vector that will be inserted into the dFill map
		std::vector<int> columnIds;
		// Add it to the diagonal fill block
		for (int j = 0; j < connectivityLength; j++) {
			// The id starts at j*connectivity length and is always offset
			// by the id, which denotes the exact column.
<<<<<<< HEAD
			index = (id) * dof + j;
=======
			auto index = (id) * dof + j;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			diagFill[index] = connectivity[j];
			// Add a column id if the connectivity is equal to 1.
			if (connectivity[j] == 1) {
				columnIds.push_back(j);
			}
		}
		// Update the map
		dFillMap[id] = columnIds;
	}

	return;
}

void NEClusterReactionNetwork::computeRateConstants() {
	// Local declarations
	double rate = 0.0;
	// Initialize the value for the biggest production rate
	double biggestProductionRate = 0.0;

	// Loop on all the production reactions
<<<<<<< HEAD
	for (auto iter = allProductionReactions.begin();
			iter != allProductionReactions.end(); iter++) {
		// Compute the rate
		rate = calculateReactionRateConstant(iter->get());
		// Set it in the reaction
		(*iter)->kConstant = rate;
=======
	for (auto& currReactionInfo : productionReactionMap) {

		auto& currReaction = currReactionInfo.second;

		// Compute the rate
		rate = calculateReactionRateConstant(*currReaction);
		// Set it in the reaction
		currReaction->kConstant = rate;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Check if the rate is the biggest one up to now
		if (rate > biggestProductionRate)
			biggestProductionRate = rate;
	}

	// Loop on all the dissociation reactions
<<<<<<< HEAD
	for (auto iter = allDissociationReactions.begin();
			iter != allDissociationReactions.end(); iter++) {
		// Compute the rate
		rate = calculateDissociationConstant(iter->get());
		// Set it in the reaction
		(*iter)->kConstant = rate;
=======
	for (auto& currReactionInfo : dissociationReactionMap) {

		auto& currReaction = currReactionInfo.second;

		// Compute the rate
		rate = calculateDissociationConstant(*currReaction);
		// Set it in the reaction
		currReaction->kConstant = rate;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Set the biggest rate
	biggestRate = biggestProductionRate;

	return;
}

void NEClusterReactionNetwork::computeAllFluxes(double *updatedConcOffset) {
<<<<<<< HEAD
	// Initial declarations
	IReactant * cluster;
	NESuperCluster * superCluster;
	double flux = 0.0;
	int reactantIndex = 0;
	auto superClusters = getAll(NESuperType);

	// ----- Compute all of the new fluxes -----
	for (int i = 0; i < networkSize; i++) {
		cluster = allReactants->at(i);
		// Compute the flux
		flux = cluster->getTotalFlux();
		// Update the concentration of the cluster
		reactantIndex = cluster->getId() - 1;
		updatedConcOffset[reactantIndex] += flux;
	}

	// ---- Moments ----
	for (int i = 0; i < superClusters.size(); i++) {
		superCluster = (xolotlCore::NESuperCluster *) superClusters[i];

		// Compute the xenon momentum flux
		flux = superCluster->getMomentumFlux();
		// Update the concentration of the cluster
		reactantIndex = superCluster->getXeMomentumId() - 1;
=======

	// ----- Compute all of the new fluxes -----
	std::for_each(allReactants.begin(), allReactants.end(),
			[&updatedConcOffset](IReactant& cluster) {

				// Compute the flux
				auto flux = cluster.getTotalFlux();
				// Update the concentration of the cluster
				auto reactantIndex = cluster.getId() - 1;
				updatedConcOffset[reactantIndex] += flux;
			});

	// ---- Moments ----
	for (auto const& currMapItem : getAll(ReactantType::NESuper)) {

		auto& superCluster = static_cast<NESuperCluster&>(*(currMapItem.second));

		// Compute the xenon momentum flux
		auto flux = superCluster.getMomentumFlux();
		// Update the concentration of the cluster
		auto reactantIndex = superCluster.getXeMomentumId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		updatedConcOffset[reactantIndex] += flux;
	}

	return;
}

void NEClusterReactionNetwork::computeAllPartials(double *vals, int *indices,
		int *size) {
<<<<<<< HEAD
	// Initial declarations
	int reactantIndex = 0, pdColIdsVectorSize = 0;
	const int dof = getDOF();
	std::vector<double> clusterPartials;
	clusterPartials.resize(dof, 0.0);
	// Get the super clusters
	auto superClusters = getAll(NESuperType);

	// Update the column in the Jacobian that represents each normal reactant
	for (int i = 0; i < networkSize - superClusters.size(); i++) {
		auto reactant = allReactants->at(i);
		// Get the reactant index
		reactantIndex = reactant->getId() - 1;

		// Get the partial derivatives
		reactant->getPartialDerivatives(clusterPartials);
		// Get the list of column ids from the map
		auto pdColIdsVector = dFillMap.at(reactantIndex);
		// Number of partial derivatives
		pdColIdsVectorSize = pdColIdsVector.size();
=======

	// Initial declarations
	const int dof = getDOF();
	std::vector<double> clusterPartials;
	clusterPartials.resize(dof, 0.0);

	// Update the column in the Jacobian that represents each normal reactant
	for (auto const& superMapItem : getAll(ReactantType::Xe)) {
		auto const& reactant = *(superMapItem.second);

		// Get the reactant index
		auto reactantIndex = reactant.getId() - 1;

		// Get the partial derivatives
		reactant.getPartialDerivatives(clusterPartials);
		// Get the list of column ids from the map
		auto pdColIdsVector = dFillMap.at(reactantIndex);
		// Number of partial derivatives
		auto pdColIdsVectorSize = pdColIdsVector.size();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		size[reactantIndex] = pdColIdsVectorSize;

		// Loop over the list of column ids
		for (int j = 0; j < pdColIdsVectorSize; j++) {
			// Set the index
			indices[reactantIndex * dof + j] = pdColIdsVector[j];

			// Get the partial derivative from the array of all of the partials
			vals[reactantIndex * dof + j] = clusterPartials[pdColIdsVector[j]];

			// Reset the cluster partial value to zero. This is much faster
			// than using memset.
			clusterPartials[pdColIdsVector[j]] = 0.0;
		}
	}

<<<<<<< HEAD
	// Update the column in the Jacobian that represents the moment for the super clusters
	for (int i = 0; i < superClusters.size(); i++) {
		auto reactant = (NESuperCluster *) superClusters[i];

		// Get the super cluster index
		reactantIndex = reactant->getId() - 1;

		// Get the partial derivatives
		reactant->getPartialDerivatives(clusterPartials);
		// Get the list of column ids from the map
		auto pdColIdsVector = dFillMap.at(reactantIndex);
		// Number of partial derivatives
		pdColIdsVectorSize = pdColIdsVector.size();
=======
	// Get the super clusters
	auto const& superClusters = getAll(ReactantType::NESuper);

	// Update the column in the Jacobian that represents the moment for the super clusters
	for (auto const& currMapItem : superClusters) {
		auto const& reactant =
				static_cast<NESuperCluster&>(*(currMapItem.second));

		// Get the super cluster index
		auto reactantIndex = reactant.getId() - 1;

		// Get the partial derivatives
		reactant.getPartialDerivatives(clusterPartials);
		// Get the list of column ids from the map
		auto pdColIdsVector = dFillMap.at(reactantIndex);
		// Number of partial derivatives
		auto pdColIdsVectorSize = pdColIdsVector.size();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		size[reactantIndex] = pdColIdsVectorSize;

		// Loop over the list of column ids
		for (int j = 0; j < pdColIdsVectorSize; j++) {
			// Set the index
			indices[reactantIndex * dof + j] = pdColIdsVector[j];
			// Get the partial derivative from the array of all of the partials
			vals[reactantIndex * dof + j] = clusterPartials[pdColIdsVector[j]];

			// Reset the cluster partial value to zero. This is much faster
			// than using memset.
			clusterPartials[pdColIdsVector[j]] = 0.0;
		}

		// Get the helium momentum index
<<<<<<< HEAD
		reactantIndex = reactant->getXeMomentumId() - 1;

		// Get the partial derivatives
		reactant->getMomentPartialDerivatives(clusterPartials);
=======
		reactantIndex = reactant.getXeMomentumId() - 1;

		// Get the partial derivatives
		reactant.getMomentPartialDerivatives(clusterPartials);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Get the list of column ids from the map
		pdColIdsVector = dFillMap.at(reactantIndex);
		// Number of partial derivatives
		pdColIdsVectorSize = pdColIdsVector.size();
		size[reactantIndex] = pdColIdsVectorSize;

		// Loop over the list of column ids
		for (int j = 0; j < pdColIdsVectorSize; j++) {
			// Set the index
			indices[reactantIndex * dof + j] = pdColIdsVector[j];
			// Get the partial derivative from the array of all of the partials
			vals[reactantIndex * dof + j] = clusterPartials[pdColIdsVector[j]];

			// Reset the cluster partial value to zero. This is much faster
			// than using memset.
			clusterPartials[pdColIdsVector[j]] = 0.0;
		}
	}

	return;
}
<<<<<<< HEAD
=======

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
