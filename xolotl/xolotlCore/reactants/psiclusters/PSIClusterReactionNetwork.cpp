<<<<<<< HEAD
=======
#include <cassert>
#include <iterator>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include "PSIClusterReactionNetwork.h"
#include "PSICluster.h"
#include "PSISuperCluster.h"
#include <xolotlPerf.h>
#include <Constants.h>
<<<<<<< HEAD

using namespace xolotlCore;

void PSIClusterReactionNetwork::setDefaultPropsAndNames() {
	// Shared pointers for the cluster type map
	std::shared_ptr<std::vector<std::shared_ptr<IReactant>>>heVector =
	std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> vVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> iVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> heVVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> heIVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();
	std::shared_ptr < std::vector<std::shared_ptr<IReactant>>> superVector
	= std::make_shared<std::vector<std::shared_ptr<IReactant>>>();

	// Initialize default properties
	dissociationsEnabled = true;
	numHeClusters = 0;
	numVClusters = 0;
	numIClusters = 0;
	numHeVClusters = 0;
	numHeIClusters = 0;
	numSuperClusters = 0;
	maxHeClusterSize = 0;
	maxVClusterSize = 0;
	maxIClusterSize = 0;
	maxHeVClusterSize = 0;
	maxHeIClusterSize = 0;

	// Initialize the current and last size to 0
	networkSize = 0;
	// Set the reactant names
	names.push_back(heType);
	names.push_back(vType);
	names.push_back(iType);
	// Set the compound reactant names
	compoundNames.push_back(heVType);
	compoundNames.push_back(heIType);
	compoundNames.push_back(PSISuperType);

	// Setup the cluster type map
	clusterTypeMap[heType] = heVector;
	clusterTypeMap[vType] = vVector;
	clusterTypeMap[iType] = iVector;
	clusterTypeMap[heVType] = heVVector;
	clusterTypeMap[heIType] = heIVector;
	clusterTypeMap[PSISuperType] = superVector;

	return;
}

PSIClusterReactionNetwork::PSIClusterReactionNetwork() :
		ReactionNetwork() {
	// Setup the properties map and the name lists
	setDefaultPropsAndNames();

	return;
}

PSIClusterReactionNetwork::PSIClusterReactionNetwork(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		ReactionNetwork(registry) {
	// Setup the properties map and the name lists
	setDefaultPropsAndNames();

	return;
}

PSIClusterReactionNetwork::PSIClusterReactionNetwork(
		const PSIClusterReactionNetwork &other) :
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
#include <MathUtils.h>

namespace xolotlCore {

PSIClusterReactionNetwork::PSIClusterReactionNetwork(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		ReactionNetwork( { ReactantType::V, ReactantType::I, ReactantType::He,
				ReactantType::HeV, ReactantType::HeI, ReactantType::PSISuper },
				ReactantType::PSISuper, registry) {

	// Initialize default properties
	dissociationsEnabled = true;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

double PSIClusterReactionNetwork::calculateDissociationConstant(
<<<<<<< HEAD
		DissociationReaction * reaction) const {
=======
		const DissociationReaction& reaction) const {

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// If the dissociations are not allowed
	if (!dissociationsEnabled)
		return 0.0;

	// The atomic volume is computed by considering the BCC structure of the
	// tungsten. In a given lattice cell in tungsten there are tungsten atoms
	// at each corner and a tungsten atom in the center. The tungsten atoms at
	// the corners are shared across a total of eight cells. The fraction of
	// the volume of the lattice cell that is filled with tungsten atoms is the
	// atomic volume and is a_0^3/(8*1/8 + 1) = 0.5*a_0^3.
	double atomicVolume = 0.5 * xolotlCore::tungstenLatticeConstant
			* xolotlCore::tungstenLatticeConstant
			* xolotlCore::tungstenLatticeConstant;

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

<<<<<<< HEAD
void PSIClusterReactionNetwork::createReactionConnectivity() {
	// Initial declarations
	int firstSize = 0, secondSize = 0, productSize = 0;
=======
void PSIClusterReactionNetwork::defineProductionReactions(IReactant& r1,
		IReactant& r2,
		const std::vector<PendingProductionReactionInfo>& pendingPRInfos,
		bool secondProduct) {

	// Define the production reaction to the network.
	// Do this *once* for the given reactants, since it doesn't
	// depend on the product or the other parameters.
	std::unique_ptr<ProductionReaction> reaction(
			new ProductionReaction(r1, r2));
	auto& prref = add(std::move(reaction));

	// Determine if reverse reaction is allowed.
	auto dissociationAllowed = canDissociate(prref);

	// Build the product-to-production map that we will
	// use for batched resultsFrom() and defineDissociationReactions() calls.
	ProductToProductionMap prodMap;
	std::for_each(pendingPRInfos.begin(), pendingPRInfos.end(),
			[&prodMap](const PendingProductionReactionInfo& currPRI) {

				prodMap[&(currPRI.product)].emplace_back(currPRI);
			});

	// Tell both reactants they are involved in this reaction
	// with the given parameters if this is not the second product
	if (!secondProduct) {
		prref.first.participateIn(prref, pendingPRInfos);
		prref.second.participateIn(prref, pendingPRInfos);
	}

	// Tell all products they are involved in this reaction
	// with their given parameters.
	std::for_each(prodMap.begin(), prodMap.end(),
			[&prref](const ProductToProductionMap::value_type& prodMapItem) {

				IReactant& currProduct = *(prodMapItem.first);
				ProductToProductionMap::mapped_type const& currPRIs = prodMapItem.second;

				currProduct.resultFrom(prref, currPRIs);
			});

	// Determine if reverse reaction is allowed. Never for the second product
	if (dissociationAllowed && !secondProduct) {
		// Forward reaction can dissociate.
		// Define all dissociation reactions for this forward reaction
		defineDissociationReactions(prref, prodMap);
	}
}

void PSIClusterReactionNetwork::defineDissociationReactions(
		ProductionReaction& forwardReaction,
		const ProductToProductionMap& prodMap) {

	// Consider each production of the given forward reaction.
	std::for_each(prodMap.begin(), prodMap.end(),
			[this,&forwardReaction](const ProductToProductionMap::value_type& currMapItem) {
				// Add a dissociation reaction to our network.
				// Do this once here for each forward reaction product.
				IReactant& emitting = *(currMapItem.first);

				std::unique_ptr<DissociationReaction> dissociationReaction(new DissociationReaction(emitting,
								forwardReaction.first, forwardReaction.second, &forwardReaction));
				auto& drref = add(std::move(dissociationReaction));

				// Tell all participants in this reaction of their involvement.
				ProductToProductionMap::mapped_type const& currPRIs = currMapItem.second;
				drref.first.participateIn(drref, currPRIs);
				drref.second.participateIn(drref, currPRIs);
				emitting.emitFrom(drref, currPRIs);
			});
}

void PSIClusterReactionNetwork::createReactionConnectivity() {
	// Initial declarations
	IReactant::SizeType firstSize = 0, secondSize = 0, productSize = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Single species clustering (He, V, I)
	// We know here that only Xe_1 can cluster so we simplify the search
	// X_(a-i) + X_i --> X_a
	// Make a vector of types
<<<<<<< HEAD
	std::vector<string> typeVec = { heType, vType, iType };
	// Loop on it
	for (auto tvIter = typeVec.begin(); tvIter != typeVec.end(); ++tvIter) {
		string typeName = *tvIter;

		// Get all the reactants of this type
		auto allTypeReactants = getAll(typeName);
		// Loop on them
		for (auto firstIt = allTypeReactants.begin();
				firstIt != allTypeReactants.end(); firstIt++) {
			// Get its size
			firstSize = (*firstIt)->getSize();
			// Loop on the second cluster starting at the same pointer to avoid double counting
			for (auto secondIt = firstIt; secondIt != allTypeReactants.end();
					secondIt++) {
				// Get its size
				secondSize = (*secondIt)->getSize();
				productSize = firstSize + secondSize;
				// Get the product
				auto product = get(typeName, productSize);
				// Check that the reaction can occur
				if (product
						&& ((*firstIt)->getDiffusionFactor() > 0.0
								|| (*secondIt)->getDiffusionFactor() > 0.0)) {
					// Create a production reaction
					auto reaction = std::make_shared<ProductionReaction>(
							(*firstIt), (*secondIt));
					// Tell the reactants that they are in this reaction
					(*firstIt)->createCombination(reaction);
					(*secondIt)->createCombination(reaction);
					product->createProduction(reaction);

					// Check if the reverse reaction is allowed
					checkDissociationConnectivity(product, reaction);
=======
	std::vector<ReactantType> typeVec { ReactantType::He, ReactantType::V,
			ReactantType::I };
	// Loop on it
	for (auto tvIter = typeVec.begin(); tvIter != typeVec.end(); ++tvIter) {

		auto currType = *tvIter;

		// Consider all reactants of the current type.
		auto const& currTypeReactantMap = getAll(currType);
		for (auto firstIt = currTypeReactantMap.begin();
				firstIt != currTypeReactantMap.end(); firstIt++) {

			auto& firstReactant = *(firstIt->second);

			// Get its size
			firstSize = firstReactant.getSize();
			// Loop on the second cluster starting at the same pointer to avoid double counting
			for (auto secondIt = firstIt; secondIt != currTypeReactantMap.end();
					secondIt++) {

				auto& secondReactant = *(secondIt->second);

				// Get its size
				secondSize = secondReactant.getSize();
				productSize = firstSize + secondSize;
				// Get the product
				auto product = get(toSpecies(currType), productSize);
				// Check that the reaction can occur
				if (product
						&& (firstReactant.getDiffusionFactor() > 0.0
								|| secondReactant.getDiffusionFactor() > 0.0)) {

					defineProductionReaction(firstReactant, secondReactant,
							*product);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				}
			}
		}
	}

	// Helium absorption by HeV clusters
	// He_(a) + (He_b)(V_c) --> [He_(a+b)](V_c)
<<<<<<< HEAD
	// Get all the He and HeV clusters
	auto allHeReactants = getAll(heType);
	auto allHeVReactants = getAll(heVType);
	// Loop on the He clusters
	for (auto firstIt = allHeReactants.begin(); firstIt != allHeReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the HeV clusters
		for (auto secondIt = allHeVReactants.begin();
				secondIt != allHeVReactants.end(); secondIt++) {
			// Get its composition
			auto comp = (*secondIt)->getComposition();
			// Create the composition of the potential product
			std::vector<int> compositionVec = { comp[heType] + firstSize,
					comp[vType], 0 };
			// Get the product
			auto product = getCompound(heVType, compositionVec);
			// Check that the reaction can occur
			if (product
					&& ((*firstIt)->getDiffusionFactor() > 0.0
							|| (*secondIt)->getDiffusionFactor() > 0.0)) {
				// Create a production reaction
				auto reaction = std::make_shared<ProductionReaction>((*firstIt),
						(*secondIt));
				// Tell the reactants that they are in this reaction
				(*firstIt)->createCombination(reaction);
				(*secondIt)->createCombination(reaction);
				product->createProduction(reaction);

				// Check if the reverse reaction is allowed
				checkDissociationConnectivity(product, reaction);
			}
		}
	}

	// Single Vacancy absorption by HeV clusters
	// (He_a)(V_b) + V --> (He_a)[V_(b+1)]
	// Get the single vacancy cluster
	auto singleVacancyCluster = get(vType, 1);
	// Loop on the HeV clusters
	for (auto secondIt = allHeVReactants.begin();
			secondIt != allHeVReactants.end(); secondIt++) {
		// Get its composition
		auto comp = (*secondIt)->getComposition();
		// Create the composition of the potential product
		std::vector<int> compositionVec = { comp[heType], comp[vType] + 1, 0 };
		// Get the product
		auto product = getCompound(heVType, compositionVec);
		// Check that the reaction can occur
		if (product
				&& (singleVacancyCluster->getDiffusionFactor() > 0.0
						|| (*secondIt)->getDiffusionFactor() > 0.0)) {
			// Create a production reaction
			auto reaction = std::make_shared<ProductionReaction>(
					singleVacancyCluster, (*secondIt));
			// Tell the reactants that they are in this reaction
			singleVacancyCluster->createCombination(reaction);
			(*secondIt)->createCombination(reaction);
			product->createProduction(reaction);

			// Check if the reverse reaction is allowed
			checkDissociationConnectivity(product, reaction);
=======
	// Consider each He reactant.
	for (auto const& heMapItem : getAll(ReactantType::He)) {

		auto& heReactant = *(heMapItem.second);

		// Skip if it can't diffuse
		if (xolotlCore::equal(heReactant.getDiffusionFactor(), 0.0))
			continue;
		// Get its size
		firstSize = heReactant.getSize();

		// Consider product with each HeV cluster
		for (auto const& heVMapItem : getAll(ReactantType::HeV)) {

			auto& heVReactant = *(heVMapItem.second);

			// Get its composition
			auto& comp = heVReactant.getComposition();
			// Create the composition of the potential product
			auto newNumHe = comp[toCompIdx(Species::He)] + firstSize;
			auto newNumV = comp[toCompIdx(Species::V)];

			// Check if product already exists.
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::V)] = newNumV;
			auto product = get(ReactantType::HeV, newComp);

			// Check if the product can be a super cluster
			if (!product) {
				// Check if it is a super cluster from the map
				product = getSuperFromComp(newNumHe, newNumV);
			}
			// Check that the reaction can occur
			if (product
					&& (heReactant.getDiffusionFactor() > 0.0
							|| heVReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(heReactant, heVReactant, *product,
						newNumHe, newNumV);
			}
		}

		// Consider product with each super cluster
		for (auto const& superMapItem : getAll(ReactantType::PSISuper)) {

			auto& superCluster =
					static_cast<PSISuperCluster&>(*(superMapItem.second));
			std::vector<PendingProductionReactionInfo> prInfos;

			// Get its boundaries
			auto const& vBounds = superCluster.getVBounds();
			// Loop on them
			for (auto const& i : superCluster.getHeBounds()) {
				for (auto const& j : superCluster.getVBounds()) {
					// Assume the product can only be a super cluster here
					auto newNumHe = i + firstSize;
					auto newNumV = j;
					IReactant* product = getSuperFromComp(newNumHe, newNumV);
					// Check that the reaction can occur
					if (product
							&& (heReactant.getDiffusionFactor() > 0.0
									|| superCluster.getDiffusionFactor() > 0.0)) {

						// Note that current reactant reacts with
						// current superCluster to produce product,
						// according to current parameters.
						prInfos.emplace_back(*product, newNumHe, newNumV, i, j);
					}
				}
			}

			// Now that we know how current reactant reacts with
			// current superCluster, create the production
			// reaction(s) for them.
			defineProductionReactions(heReactant, superCluster, prInfos);
		}
	}

	// Vacancy absorption by HeV clusters
	// (He_a)(V_b) + V_c --> (He_a)[V_(b+c)]
	// Consider each V cluster.
	for (auto const& vMapItem : getAll(ReactantType::V)) {

		auto& vReactant = *(vMapItem.second);

		// Skip if it can't diffuse
		if (xolotlCore::equal(vReactant.getDiffusionFactor(), 0.0))
			continue;
		// Get the V size
		firstSize = vReactant.getSize();
		// Consider product with every HeV cluster.
		for (auto const& heVMapItem : getAll(ReactantType::HeV)) {

			auto& heVReactant = *(heVMapItem.second);

			// Get its composition
			auto& comp = heVReactant.getComposition();
			// Create the composition of the potential product
			auto newNumHe = comp[toCompIdx(Species::He)];
			auto newNumV = comp[toCompIdx(Species::V)] + firstSize;

			// Check if product already exists.
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::V)] = newNumV;
			auto product = get(ReactantType::HeV, newComp);

			// Check if the product can be a super cluster
			if (!product) {
				product = getSuperFromComp(newNumHe, newNumV);
			}
			// Check that the reaction can occur
			if (product
					&& (vReactant.getDiffusionFactor() > 0.0
							|| heVReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(vReactant, heVReactant, *product,
						newNumHe, newNumV);
			}
		}

		// Consider product with super clusters.
		for (auto const& superMapItem : getAll(ReactantType::PSISuper)) {

			auto& superCluster =
					static_cast<PSISuperCluster&>(*(superMapItem.second));
			std::vector<PendingProductionReactionInfo> prInfos;

			// Get its boundaries
			auto const& heBounds = superCluster.getHeBounds();
			auto const& vBounds = superCluster.getVBounds();
			// Loop on them
			for (auto const& i : superCluster.getHeBounds()) {
				for (auto const& j : superCluster.getVBounds()) {

					// Assume the product can only be a super cluster here
					auto newNumHe = i;
					auto newNumV = j + firstSize;
					IReactant* product = getSuperFromComp(newNumHe, newNumV);
					// Check that the reaction can occur
					if (product
							&& (vReactant.getDiffusionFactor() > 0.0
									|| superCluster.getDiffusionFactor() > 0.0)) {
						prInfos.emplace_back(*product, newNumHe, newNumV, i, j);
					}
				}
			}

			// Now that we know how current reactant interacts with
			// current supercluster, define the production reactions.
			defineProductionReactions(vReactant, superCluster, prInfos);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
	}

	// Helium-Vacancy clustering
	// He_a + V_b --> (He_a)(V_b)
<<<<<<< HEAD
	// Get all the V clusters
	auto allVReactants = getAll(vType);
	// Loop on the He clusters
	for (auto firstIt = allHeReactants.begin(); firstIt != allHeReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the HeV clusters
		for (auto secondIt = allVReactants.begin();
				secondIt != allVReactants.end(); secondIt++) {
			// Get its size
			secondSize = (*secondIt)->getSize();
			// Create the composition of the potential product
			std::vector<int> compositionVec = { firstSize, secondSize, 0 };
			// Get the product
			auto product = getCompound(heVType, compositionVec);
			// Check that the reaction can occur
			if (product
					&& ((*firstIt)->getDiffusionFactor() > 0.0
							|| (*secondIt)->getDiffusionFactor() > 0.0)) {
				// Create a production reaction
				auto reaction = std::make_shared<ProductionReaction>((*firstIt),
						(*secondIt));
				// Tell the reactants that they are in this reaction
				(*firstIt)->createCombination(reaction);
				(*secondIt)->createCombination(reaction);
				product->createProduction(reaction);

				// Check if the reverse reaction is allowed
				checkDissociationConnectivity(product, reaction);
=======
	// Consider each He cluster.
	for (auto const& heMapItem : getAll(ReactantType::He)) {

		auto& heReactant = *(heMapItem.second);

		// Get its size
		firstSize = heReactant.getSize();
		// Consider product with each V cluster.
		for (auto const& vMapItem : getAll(ReactantType::V)) {

			auto& vReactant = *(vMapItem.second);

			// Get its size
			secondSize = vReactant.getSize();
			// Create the composition of the potential product
			auto newNumHe = firstSize;
			auto newNumV = secondSize;

			// Get the product
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::V)] = newNumV;
			auto product = get(ReactantType::HeV, newComp);

			// Check if the product can be a super cluster
			if (!product) {
				product = getSuperFromComp(newNumHe, newNumV);
			}
			// Check that the reaction can occur
			if (product
					&& (heReactant.getDiffusionFactor() > 0.0
							|| vReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(heReactant, vReactant, *product,
						newNumHe, newNumV);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			}
		}
	}

	// Vacancy reduction by Interstitial absorption in HeV clusters
	// (He_a)(V_b) + (I_c) --> (He_a)[V_(b-c)]
<<<<<<< HEAD
	// Get all the I clusters
	auto allIReactants = getAll(iType);
	// Loop on them
	for (auto firstIt = allIReactants.begin(); firstIt != allIReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the HeV clusters
		for (auto secondIt = allHeVReactants.begin();
				secondIt != allHeVReactants.end(); secondIt++) {
			// Get its composition
			auto comp = (*secondIt)->getComposition();
			// The product can be He or HeV
			IReactant * product = nullptr;
			if (comp[vType] == firstSize) {
				// The product is He
				product = get(heType, comp[heType]);
			} else {
				// The product is HeV
				// Create the composition of the potential product
				std::vector<int> compositionVec = { comp[heType], comp[vType]
						- firstSize, 0 };
				// Get the product
				product = getCompound(heVType, compositionVec);
			}
			// Check that the reaction can occur
			if (product
					&& ((*firstIt)->getDiffusionFactor() > 0.0
							|| (*secondIt)->getDiffusionFactor() > 0.0)) {
				// Create a production reaction
				auto reaction = std::make_shared<ProductionReaction>((*firstIt),
						(*secondIt));
				// Tell the reactants that they are in this reaction
				(*firstIt)->createCombination(reaction);
				(*secondIt)->createCombination(reaction);
				product->createProduction(reaction);

				// Check if the reverse reaction is allowed
				checkDissociationConnectivity(product, reaction);
			}
		}
=======
	// Consider each I cluster
	for (auto const& iMapItem : getAll(ReactantType::I)) {

		auto& iReactant = *(iMapItem.second);

		// Get its size
		firstSize = iReactant.getSize();
		// Consider product with each HeV cluster.
		for (auto const& heVMapItem : getAll(ReactantType::HeV)) {

			auto& heVReactant = *(heVMapItem.second);

			// Get its composition
			auto& comp = heVReactant.getComposition();
			// The product can be He or HeV
			IReactant * product = nullptr;
			if (comp[toCompIdx(Species::V)] == firstSize) {
				// The product is He
				product = get(Species::He, comp[toCompIdx(Species::He)]);
			} else {
				// The product is HeV
				// Create the composition of the potential product
				IReactant::Composition newComp;
				newComp[toCompIdx(Species::He)] = comp[toCompIdx(Species::He)];
				newComp[toCompIdx(Species::V)] = comp[toCompIdx(Species::V)]
						- firstSize;
				// Get the product
				product = get(ReactantType::HeV, newComp);
			}
			// Check that the reaction can occur
			if (product
					&& (iReactant.getDiffusionFactor() > 0.0
							|| heVReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(iReactant, heVReactant, *product);
			}
		}

		// Consider product with all super clusters.
		for (auto const& superMapItem : getAll(ReactantType::PSISuper)) {
			auto& superCluster =
					static_cast<PSISuperCluster&>(*(superMapItem.second));
			std::vector<PendingProductionReactionInfo> prInfos;

			// Get its boundaries
			auto const& heBounds = superCluster.getHeBounds();
			auto const& vBounds = superCluster.getVBounds();
			// Loop on them
			for (auto const& i : superCluster.getHeBounds()) {
				for (auto const& j : superCluster.getVBounds()) {
					// The product might be HeV or He
					auto newNumHe = i;
					auto newNumV = j - firstSize;

					// Get the product
					IReactant* product = nullptr;
					if (newNumV == 0) {
						// The product is He
						product = get(Species::He, i);
					} else {
						// Create the composition of the potential product
						IReactant::Composition newComp;
						newComp[toCompIdx(Species::He)] = newNumHe;
						newComp[toCompIdx(Species::V)] = newNumV;
						product = get(ReactantType::HeV, newComp);

						// If the product doesn't exist check for super clusters
						if (!product) {
							product = getSuperFromComp(newNumHe, newNumV);
						}
					}
					// Check that the reaction can occur
					if (product
							&& (iReactant.getDiffusionFactor() > 0.0
									|| superCluster.getDiffusionFactor() > 0.0)) {

						prInfos.emplace_back(*product, newNumHe, newNumV, i, j);
					}
				}
			}

			// Now that we know how current reactant interacts with
			// current supercluster, define its production reactions
			// according to given parameters.
			defineProductionReactions(iReactant, superCluster, prInfos);
		}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Helium clustering leading to trap mutation
	// He_a + He_b --> [He_(a+b)](V_c) + I_c
	// Loop on the He clusters
<<<<<<< HEAD
	for (auto firstIt = allHeReactants.begin(); firstIt != allHeReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the second He cluster starting at the same pointer to avoid double counting
		for (auto secondIt = firstIt; secondIt != allHeReactants.end();
				secondIt++) {
			// Get its size
			secondSize = (*secondIt)->getSize();
			// Get the simple product
			productSize = firstSize + secondSize;
			auto product = get(heType, productSize);
=======
	for (auto firstIt = getAll(ReactantType::He).begin();
			firstIt != getAll(ReactantType::He).end(); firstIt++) {
		// Get the reactant
		auto& firstReactant = static_cast<PSICluster&>(*(firstIt->second));
		// Get its size
		firstSize = firstReactant.getSize();
		// Loop on the second He cluster starting at the same pointer to avoid double counting
		for (auto secondIt = firstIt;
				secondIt != getAll(ReactantType::He).end(); secondIt++) {
			// Get the reactant
			auto& secondReactant = static_cast<PSICluster&>(*(secondIt->second));
			// Get its size
			secondSize = secondReactant.getSize();
			// Get the simple product
			productSize = firstSize + secondSize;
			auto product = get(toSpecies(ReactantType::He), productSize);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Doesn't do anything if the product exist
			if (product)
				continue;

			// Trap mutation is happening
			// Loop on the possible I starting by the smallest
<<<<<<< HEAD
			for (auto it = allIReactants.begin(); it != allIReactants.end();
					it++) {
				// Get the size of the I cluster
				int iSize = (*it)->getSize();
				// Create the composition of the potential product
				std::vector<int> compositionVec = { firstSize + secondSize,
						iSize, 0 };
				product = getCompound(heVType, compositionVec);
				// Check that the reaction can occur
				if (product
						&& ((*firstIt)->getDiffusionFactor() > 0.0
								|| (*secondIt)->getDiffusionFactor() > 0.0)) {
					// Create a production reaction
					auto reaction = std::make_shared<ProductionReaction>(
							(*firstIt), (*secondIt));
					// Tell the reactants that they are in this reaction
					(*firstIt)->createCombination(reaction);
					(*secondIt)->createCombination(reaction);
					product->createProduction(reaction);
					(*it)->createProduction(reaction);
=======
			for (auto const& iMapItem : getAll(ReactantType::I)) {
				auto& iReactant = *(iMapItem.second);
				// Get the size of the I cluster
				int iSize = iReactant.getSize();
				// Create the composition of the potential product
				IReactant::Composition newComp;
				int newNumHe = firstSize + secondSize;
				int newNumV = iSize;
				newComp[toCompIdx(Species::He)] = newNumHe;
				newComp[toCompIdx(Species::V)] = newNumV;
				product = get(ReactantType::HeV, newComp);

				// Check if the product can be a super cluster
				if (!product) {
					// Check if it is a super cluster from the map
					product = getSuperFromComp(newNumHe, newNumV);
				}

				// Check that the reaction can occur
				if (product
						&& (firstReactant.getDiffusionFactor() > 0.0
								|| secondReactant.getDiffusionFactor() > 0.0)) {

					defineProductionReaction(firstReactant, secondReactant,
							*product, newNumHe, newNumV);
					// This is a reaction with two products so we need to tell the other product
					// it is participating too
					defineProductionReaction(firstReactant, secondReactant,
							iReactant, newNumHe, newNumV, 0, 0, true);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

					// Stop the loop on I clusters here
					break;
				}
			}
		}
	}

	// Helium absorption by HeV leading to trap mutation
	// (He_a)(V_b) + He_c --> [He_(a+c)][V_(b+d)] + I_d
	// Loop on the He clusters
<<<<<<< HEAD
	for (auto firstIt = allHeReactants.begin(); firstIt != allHeReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the HeV clusters
		for (auto secondIt = allHeVReactants.begin();
				secondIt != allHeVReactants.end(); secondIt++) {
			// Get its composition
			auto comp = (*secondIt)->getComposition();
			// Get the simple product
			std::vector<int> compositionVec = { firstSize + comp[heType],
					comp[vType], 0 };
			auto product = getCompound(heVType, compositionVec);
=======
	for (auto const& heMapItem : getAll(ReactantType::He)) {
		auto& heReactant = *(heMapItem.second);

		// Skip if it can't diffuse
		if (xolotlCore::equal(heReactant.getDiffusionFactor(), 0.0))
			continue;
		// Get its size
		firstSize = heReactant.getSize();

		// Loop on the HeV clusters
		for (auto const& heVMapItem : getAll(ReactantType::HeV)) {

			auto& heVReactant = *(heVMapItem.second);

			// Get its composition
			auto& comp = heVReactant.getComposition();
			// Create the composition of the potential product
			auto newNumHe = comp[toCompIdx(Species::He)] + firstSize;
			auto newNumV = comp[toCompIdx(Species::V)];

			// Check if product already exists.
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::V)] = newNumV;
			auto product = get(ReactantType::HeV, newComp);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Doesn't do anything if the product exist
			if (product)
				continue;

			// Trap mutation is happening
			// Loop on the possible I starting by the smallest
<<<<<<< HEAD
			for (auto it = allIReactants.begin(); it != allIReactants.end();
					it++) {
				// Get the size of the I cluster
				int iSize = (*it)->getSize();
				// Create the composition of the potential product
				compositionVec[1] = comp[vType] + iSize;
				product = getCompound(heVType, compositionVec);
				// Check that the reaction can occur
				if (product
						&& ((*firstIt)->getDiffusionFactor() > 0.0
								|| (*secondIt)->getDiffusionFactor() > 0.0)) {
					// Create a production reaction
					auto reaction = std::make_shared<ProductionReaction>(
							(*firstIt), (*secondIt));
					// Tell the reactants that they are in this reaction
					(*firstIt)->createCombination(reaction);
					(*secondIt)->createCombination(reaction);
					product->createProduction(reaction);
					(*it)->createProduction(reaction);
=======
			for (auto const& iMapItem : getAll(ReactantType::I)) {
				auto& iReactant = *(iMapItem.second);
				// Get the size of the I cluster
				int iSize = iReactant.getSize();
				// Create the composition of the potential product
				newNumV += iSize;
				newComp[toCompIdx(Species::V)] = newNumV;
				product = get(ReactantType::HeV, newComp);

				// Check if the product can be a super cluster
				if (!product) {
					// Check if it is a super cluster from the map
					product = getSuperFromComp(newNumHe, newNumV);
				}

				// Check that the reaction can occur
				if (product
						&& (heReactant.getDiffusionFactor() > 0.0
								|| heVReactant.getDiffusionFactor() > 0.0)) {

					defineProductionReaction(heReactant, heVReactant, *product,
							newNumHe, newNumV);
					// This is a reaction with two products so we need to tell the other product
					// it is participating too
					// Define the basic production reaction.
					auto& reaction = defineReactionBase(heReactant,
							heVReactant);
					iReactant.resultFrom(reaction, newNumHe, newNumV);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

					// Stop the loop on I clusters here
					break;
				}
			}
		}
<<<<<<< HEAD
=======

		// Consider product with all super clusters.
		for (auto const& superMapItem : getAll(ReactantType::PSISuper)) {
			auto& superCluster =
					static_cast<PSISuperCluster&>(*(superMapItem.second));
			std::vector<PendingProductionReactionInfo> prInfos1;
			std::vector<PendingProductionReactionInfo> prInfos2;

			// Get its boundaries
			auto const& heBounds = superCluster.getHeBounds();
			auto const& vBounds = superCluster.getVBounds();
			// Loop on them
			for (auto const& i : superCluster.getHeBounds()) {
				for (auto const& j : superCluster.getVBounds()) {
					// Check these coordinates are actually contained by the super cluster
					if (!superCluster.isIn(i, j))
						continue;

					// The product might be HeV or He
					auto newNumHe = i + firstSize;
					auto newNumV = j;

					// Get the product
					IReactant* product = getSuperFromComp(newNumHe, newNumV);
					// Skip if the product exists because we want trap mutation
					if (product)
						continue;

					// Trap mutation is happening
					// Loop on the possible I starting by the smallest
					for (auto const& iMapItem : getAll(ReactantType::I)) {
						auto& iReactant = *(iMapItem.second);
						// Get the size of the I cluster
						int iSize = iReactant.getSize();
						// Update the composition of the potential product
						newNumV += iSize;
						product = getSuperFromComp(newNumHe, newNumV);

						// Check that the reaction can occur
						if (product && heReactant.getDiffusionFactor() > 0.0) {

							prInfos1.emplace_back(*product, newNumHe, newNumV,
									i, j);

							prInfos2.emplace_back(iReactant, 0, 0, i, j);
						}
					}
				}
			}

			// Now that we know how current reactant interacts with
			// current supercluster, define its production reactions
			// according to given parameters.
			defineProductionReactions(heReactant, superCluster, prInfos1);
			defineProductionReactions(heReactant, superCluster, prInfos2, true);
		}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Vacancy-Interstitial annihilation
	// I_a + V_b
	//        --> I_(a-b), if a > b
	//        --> V_(b-a), if a < b
	//        --> 0, if a = b
<<<<<<< HEAD
	// Loop on the I clusters
	for (auto firstIt = allIReactants.begin(); firstIt != allIReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the V clusters
		for (auto secondIt = allVReactants.begin();
				secondIt != allVReactants.end(); secondIt++) {
			// Get its size
			secondSize = (*secondIt)->getSize();
=======
	// Consider all I clusters.
	for (auto const& iMapItem : getAll(ReactantType::I)) {

		auto& iReactant = *(iMapItem.second);

		// Get its size
		firstSize = iReactant.getSize();

		// Consider product with each V cluster.
		for (auto const& vMapItem : getAll(ReactantType::V)) {

			auto& vReactant = *(vMapItem.second);

			// Get its size
			secondSize = vReactant.getSize();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Check the possibilities
			if (firstSize > secondSize) {
				// Get the product
				productSize = firstSize - secondSize;
<<<<<<< HEAD
				auto product = get(iType, productSize);
				// Check that the reaction can occur
				if (product
						&& ((*firstIt)->getDiffusionFactor() > 0.0
								|| (*secondIt)->getDiffusionFactor() > 0.0)) {
					// Create a production reaction
					auto reaction = std::make_shared<ProductionReaction>(
							(*firstIt), (*secondIt));
					// Tell the reactants that they are in this reaction
					(*firstIt)->createCombination(reaction);
					(*secondIt)->createCombination(reaction);
					product->createProduction(reaction);
=======
				auto product = get(Species::I, productSize);
				// Check that the reaction can occur
				if (product
						&& (iReactant.getDiffusionFactor() > 0.0
								|| vReactant.getDiffusionFactor() > 0.0)) {

					defineAnnihilationReaction(iReactant, vReactant, *product);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				}
			} else if (firstSize < secondSize) {
				// Get the product
				productSize = secondSize - firstSize;
<<<<<<< HEAD
				auto product = get(vType, productSize);
				// Check that the reaction can occur
				if (product
						&& ((*firstIt)->getDiffusionFactor() > 0.0
								|| (*secondIt)->getDiffusionFactor() > 0.0)) {
					// Create a production reaction
					auto reaction = std::make_shared<ProductionReaction>(
							(*firstIt), (*secondIt));
					// Tell the reactants that they are in this reaction
					(*firstIt)->createCombination(reaction);
					(*secondIt)->createCombination(reaction);
					product->createProduction(reaction);
=======
				auto product = get(Species::V, productSize);
				// Check that the reaction can occur
				if (product
						&& (iReactant.getDiffusionFactor() > 0.0
								|| vReactant.getDiffusionFactor() > 0.0)) {

					defineAnnihilationReaction(iReactant, vReactant, *product);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				}

			} else {
				// Annihilation
				// Check that the reaction can occur
<<<<<<< HEAD
				if (((*firstIt)->getDiffusionFactor() > 0.0
						|| (*secondIt)->getDiffusionFactor() > 0.0)) {
					// Create a production reaction
					auto reaction = std::make_shared<ProductionReaction>(
							(*firstIt), (*secondIt));
					// Tell the reactants that they are in this reaction
					(*firstIt)->createCombination(reaction);
					(*secondIt)->createCombination(reaction);
=======
				if ((iReactant.getDiffusionFactor() > 0.0
						|| vReactant.getDiffusionFactor() > 0.0)) {

					defineCompleteAnnihilationReaction(iReactant, vReactant);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				}
			}
		}
	}

	// Helium absorption by HeI clusters
	// He_(a) + (He_b)(I_c) --> [He_(a+b)](I_c)
<<<<<<< HEAD
	// Get all the HeI clusters
	auto allHeIReactants = getAll(heIType);
	// Loop on the He clusters
	for (auto firstIt = allHeReactants.begin(); firstIt != allHeReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the HeV clusters
		for (auto secondIt = allHeIReactants.begin();
				secondIt != allHeIReactants.end(); secondIt++) {
			// Get its composition
			auto comp = (*secondIt)->getComposition();
			// Create the composition of the potential product
			std::vector<int> compositionVec = { comp[heType] + firstSize, 0,
					comp[iType] };
			// Get the product
			auto product = getCompound(heIType, compositionVec);
			// Check that the reaction can occur
			if (product
					&& ((*firstIt)->getDiffusionFactor() > 0.0
							|| (*secondIt)->getDiffusionFactor() > 0.0)) {
				// Create a production reaction
				auto reaction = std::make_shared<ProductionReaction>((*firstIt),
						(*secondIt));
				// Tell the reactants that they are in this reaction
				(*firstIt)->createCombination(reaction);
				(*secondIt)->createCombination(reaction);
				product->createProduction(reaction);

				// Check if the reverse reaction is allowed
				checkDissociationConnectivity(product, reaction);
=======
	// Consider each He reactant.
	for (auto const& heMapItem : getAll(ReactantType::He)) {

		auto& heReactant = *(heMapItem.second);

		// Skip if it can't diffuse
		if (xolotlCore::equal(heReactant.getDiffusionFactor(), 0.0))
			continue;
		// Get its size
		firstSize = heReactant.getSize();

		// Consider product with each HeI cluster
		for (auto const& heIMapItem : getAll(ReactantType::HeI)) {

			auto& heIReactant = *(heIMapItem.second);

			// Get its composition
			auto& comp = heIReactant.getComposition();
			// Create the composition of the potential product
			auto newNumHe = comp[toCompIdx(Species::He)] + firstSize;
			auto newNumI = comp[toCompIdx(Species::I)];

			// Check if product already exists.
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::I)] = newNumI;
			auto product = get(ReactantType::HeI, newComp);

			// Check that the reaction can occur
			if (product
					&& (heReactant.getDiffusionFactor() > 0.0
							|| heIReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(heReactant, heIReactant, *product,
						newNumHe, newNumI);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			}
		}
	}

<<<<<<< HEAD
	// Single Interstitial absorption by HeI clusters
	// (He_a)(I_b) + I --> (He_a)[I_(b+1)]
	// Get the single interstitial cluster
	auto singleInterstitialCluster = get(iType, 1);
	// Loop on the HeI clusters
	for (auto secondIt = allHeIReactants.begin();
			secondIt != allHeIReactants.end(); secondIt++) {
		// Get its composition
		auto comp = (*secondIt)->getComposition();
		// Create the composition of the potential product
		std::vector<int> compositionVec = { comp[heType], 0, comp[iType] + 1 };
		// Get the product
		auto product = getCompound(heIType, compositionVec);
		// Check that the reaction can occur
		if (product
				&& (singleInterstitialCluster->getDiffusionFactor() > 0.0
						|| (*secondIt)->getDiffusionFactor() > 0.0)) {
			// Create a production reaction
			auto reaction = std::make_shared<ProductionReaction>(
					singleInterstitialCluster, (*secondIt));
			// Tell the reactants that they are in this reaction
			singleInterstitialCluster->createCombination(reaction);
			(*secondIt)->createCombination(reaction);
			product->createProduction(reaction);

			// Check if the reverse reaction is allowed
			checkDissociationConnectivity(product, reaction);
=======
	// Interstitial absorption by HeI clusters
	// (He_a)(I_b) + I_c --> (He_a)[I_(b+c)]
	// Consider each I cluster.
	for (auto const& iMapItem : getAll(ReactantType::I)) {

		auto& iReactant = *(iMapItem.second);

		// Skip if it can't diffuse
		if (xolotlCore::equal(iReactant.getDiffusionFactor(), 0.0))
			continue;
		// Get the I size
		firstSize = iReactant.getSize();
		// Consider product with every HeI cluster.
		for (auto const& heIMapItem : getAll(ReactantType::HeI)) {

			auto& heIReactant = *(heIMapItem.second);

			// Get its composition
			auto& comp = heIReactant.getComposition();
			// Create the composition of the potential product
			auto newNumHe = comp[toCompIdx(Species::He)];
			auto newNumI = comp[toCompIdx(Species::I)] + firstSize;

			// Check if product already exists.
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::I)] = newNumI;
			auto product = get(ReactantType::HeI, newComp);

			// Check that the reaction can occur
			if (product
					&& (iReactant.getDiffusionFactor() > 0.0
							|| heIReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(iReactant, heIReactant, *product,
						newNumHe, newNumI);
			}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
	}

	// Helium-Interstitial clustering
	// He_a + I_b --> (He_a)(I_b)
<<<<<<< HEAD
	// Loop on the He clusters
	for (auto firstIt = allHeReactants.begin(); firstIt != allHeReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the I clusters
		for (auto secondIt = allIReactants.begin();
				secondIt != allIReactants.end(); secondIt++) {
			// Get its size
			secondSize = (*secondIt)->getSize();
			// Create the composition of the potential product
			std::vector<int> compositionVec = { firstSize, 0, secondSize };
			// Get the product
			auto product = getCompound(heIType, compositionVec);
			// Check that the reaction can occur
			if (product
					&& ((*firstIt)->getDiffusionFactor() > 0.0
							|| (*secondIt)->getDiffusionFactor() > 0.0)) {
				// Create a production reaction
				auto reaction = std::make_shared<ProductionReaction>((*firstIt),
						(*secondIt));
				// Tell the reactants that they are in this reaction
				(*firstIt)->createCombination(reaction);
				(*secondIt)->createCombination(reaction);
				product->createProduction(reaction);

				// Check if the reverse reaction is allowed
				checkDissociationConnectivity(product, reaction);
=======
	// Consider each He cluster.
	for (auto const& heMapItem : getAll(ReactantType::He)) {

		auto& heReactant = *(heMapItem.second);

		// Get its size
		firstSize = heReactant.getSize();
		// Consider product with each I cluster.
		for (auto const& iMapItem : getAll(ReactantType::I)) {

			auto& iReactant = *(iMapItem.second);

			// Get its size
			secondSize = iReactant.getSize();
			// Create the composition of the potential product
			auto newNumHe = firstSize;
			auto newNumI = secondSize;

			// Get the product
			IReactant::Composition newComp;
			newComp[toCompIdx(Species::He)] = newNumHe;
			newComp[toCompIdx(Species::I)] = newNumI;
			auto product = get(ReactantType::HeI, newComp);

			// Check that the reaction can occur
			if (product
					&& (heReactant.getDiffusionFactor() > 0.0
							|| iReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(heReactant, iReactant, *product,
						newNumHe, newNumI);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			}
		}
	}

<<<<<<< HEAD
	// Interstitial reduction by Vacancy absorption in HeI clusters
	// (He_a)(I_b) + (V_c) --> (He_a)[I_(b-c)]
	// Loop on V clusters
	for (auto firstIt = allVReactants.begin(); firstIt != allVReactants.end();
			firstIt++) {
		// Get its size
		firstSize = (*firstIt)->getSize();
		// Loop on the HeI clusters
		for (auto secondIt = allHeIReactants.begin();
				secondIt != allHeIReactants.end(); secondIt++) {
			// Get its composition
			auto comp = (*secondIt)->getComposition();
			// The product can be He or HeI
			IReactant * product = nullptr;
			if (comp[iType] == firstSize) {
				// The product is He
				product = get(heType, comp[heType]);
			} else {
				// The product is HeI
				// Create the composition of the potential product
				std::vector<int> compositionVec = { comp[heType], 0, comp[iType]
						- firstSize };
				// Get the product
				product = getCompound(heIType, compositionVec);
			}
			// Check that the reaction can occur
			if (product
					&& ((*firstIt)->getDiffusionFactor() > 0.0
							|| (*secondIt)->getDiffusionFactor() > 0.0)) {
				// Create a production reaction
				auto reaction = std::make_shared<ProductionReaction>((*firstIt),
						(*secondIt));
				// Tell the reactants that they are in this reaction
				(*firstIt)->createCombination(reaction);
				(*secondIt)->createCombination(reaction);
				product->createProduction(reaction);

				// Check if the reverse reaction is allowed
				checkDissociationConnectivity(product, reaction);
=======
	// Interstitial reduction by vacancy absorption in HeI clusters
	// (He_a)(I_b) + (V_c) --> (He_a)[I_(b-c)]
	// Consider each V cluster
	for (auto const& vMapItem : getAll(ReactantType::V)) {

		auto& vReactant = *(vMapItem.second);

		// Get its size
		firstSize = vReactant.getSize();
		// Consider product with each HeI cluster.
		for (auto const& heIMapItem : getAll(ReactantType::HeI)) {

			auto& heIReactant = *(heIMapItem.second);

			// Get its composition
			auto& comp = heIReactant.getComposition();
			// The product can be He or HeV
			IReactant * product = nullptr;
			if (comp[toCompIdx(Species::I)] == firstSize) {
				// The product is He
				product = get(Species::He, comp[toCompIdx(Species::He)]);
			} else {
				// The product is HeI
				// Create the composition of the potential product
				IReactant::Composition newComp;
				newComp[toCompIdx(Species::He)] = comp[toCompIdx(Species::He)];
				newComp[toCompIdx(Species::I)] = comp[toCompIdx(Species::I)]
						- firstSize;
				// Get the product
				product = get(ReactantType::HeI, newComp);
			}
			// Check that the reaction can occur
			if (product
					&& (vReactant.getDiffusionFactor() > 0.0
							|| heIReactant.getDiffusionFactor() > 0.0)) {

				defineProductionReaction(vReactant, heIReactant, *product);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			}
		}
	}

	return;
}

<<<<<<< HEAD
void PSIClusterReactionNetwork::checkDissociationConnectivity(
		IReactant * emittingReactant,
		std::shared_ptr<ProductionReaction> reaction) {
	// Check if at least one of the potentially emitted cluster is size one
	if (reaction->first->getSize() != 1 && reaction->second->getSize() != 1) {
		// Don't add the reverse reaction
		return;
	}

	// Check for trap mutations (with XOR)
	if ((reaction->first->getType() == iType)
			== !(reaction->second->getType() == iType)) {
		// Don't add the reverse reaction
		return;
	}

	// The reaction can occur, create the dissociation
	// Create a dissociation reaction
	auto dissociationReaction = std::make_shared<DissociationReaction>(
			emittingReactant, reaction->first, reaction->second);
	// Set the reverse reaction
	dissociationReaction->reverseReaction = reaction.get();
	// Tell the reactants that their are in this reaction
	reaction->first->createDissociation(dissociationReaction);
	reaction->second->createDissociation(dissociationReaction);
	emittingReactant->createEmission(dissociationReaction);

	return;
}

void PSIClusterReactionNetwork::setTemperature(double temp) {
	ReactionNetwork::setTemperature(temp);

	computeRateConstants();

	return;
}

double PSIClusterReactionNetwork::getTemperature() const {
	return temperature;
}

IReactant * PSIClusterReactionNetwork::get(const std::string& type,
		const int size) const {
	// Local Declarations
	static std::map<std::string, int> composition = { { heType, 0 },
			{ vType, 0 }, { iType, 0 }, { xeType, 0 } };
	std::shared_ptr<IReactant> retReactant;

	// Initialize the values because it's static
	composition[heType] = 0;
	composition[vType] = 0;
	composition[iType] = 0;

	// Only pull the reactant if the name and size are valid
	if ((type == heType || type == vType || type == iType) && size >= 1) {
		composition[type] = size;
		//std::string encodedName = PSICluster::encodeCompositionAsName(composition);
		// Make sure the reactant is in the map
		std::string compStr = Reactant::toCanonicalString(type, composition);
		if (singleSpeciesMap.count(compStr)) {
			retReactant = singleSpeciesMap.at(compStr);
		}
	}

	return retReactant.get();
}

IReactant * PSIClusterReactionNetwork::getCompound(const std::string& type,
		const std::vector<int>& sizes) const {
	// Local Declarations
	static std::map<std::string, int> composition = { { heType, 0 },
			{ vType, 0 }, { iType, 0 }, { xeType, 0 } };
	std::shared_ptr<IReactant> retReactant;

	// Initialize the values because it's static
	composition[heType] = 0;
	composition[vType] = 0;
	composition[iType] = 0;

	// Only pull the reactant if the name is valid and there are enough sizes
	// to fill the composition.
	if ((type == heVType || type == heIType) && sizes.size() == 3) {
		composition[heType] = sizes[0];
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

IReactant * PSIClusterReactionNetwork::getSuper(const std::string& type,
		const std::vector<int>& sizes) const {
	// Local Declarations
	static std::map<std::string, int> composition = { { heType, 0 },
			{ vType, 0 }, { iType, 0 }, { xeType, 0 } };
	std::shared_ptr<IReactant> retReactant;

	// Setup the composition map to default values
	composition[heType] = 0;
	composition[vType] = 0;
	composition[iType] = 0;

	// Only pull the reactant if the name is valid and there are enough sizes
	// to fill the composition.
	if (type == PSISuperType && sizes.size() == 3) {
		composition[heType] = sizes[0];
		composition[vType] = sizes[1];
		composition[iType] = sizes[2];
		// Make sure the reactant is in the map
		std::string compStr = Reactant::toCanonicalString(type, composition);
		if (superSpeciesMap.count(compStr)) {
			retReactant = superSpeciesMap.at(compStr);
		}
	}

	return retReactant.get();
}

const std::shared_ptr<std::vector<IReactant *>> & PSIClusterReactionNetwork::getAll() const {
	return allReactants;
}

std::vector<IReactant *> PSIClusterReactionNetwork::getAll(
		const std::string& name) const {
	// Local Declarations
	std::vector<IReactant *> reactants;

	// Only pull the reactants if the name is valid
	if (name == heType || name == vType || name == iType || name == heVType
			|| name == heIType || name == PSISuperType) {
		std::shared_ptr<std::vector<std::shared_ptr<IReactant>> > storedReactants =
				clusterTypeMap.at(name);
		int vecSize = storedReactants->size();
		for (int i = 0; i < vecSize; i++) {
			reactants.push_back(storedReactants->at(i).get());
		}
	}

	return reactants;
}

void PSIClusterReactionNetwork::add(std::shared_ptr<IReactant> reactant) {
	// Local Declarations
	int numHe = 0, numV = 0, numI = 0;
	bool isMixed = false;
	int* numClusters = nullptr;
	int* maxClusterSize = nullptr;

	// Only add a complete reactant
	if (reactant != NULL) {
		// Get the composition
		auto composition = reactant->getComposition();
		std::string compStr = reactant->getCompositionString();
		// Get the species sizes
		numHe = composition.at(heType);
		numV = composition.at(vType);
		numI = composition.at(iType);

		// Determine if the cluster is a compound. If there is more than one
		// type, then the check below will sum to greater than one and we know
		// that we have a mixed cluster.
		isMixed = ((numHe > 0) + (numV > 0) + (numI > 0)) > 1;
		// Only add the element if we don't already have it
		// Add the compound or regular reactant.
		if (isMixed && mixedSpeciesMap.count(compStr) == 0) {
			// Put the compound in its map
			mixedSpeciesMap[compStr] = reactant;
			// Figure out whether we have HeV or HeI and set the keys
			if (numV > 0) {
				numClusters = &numHeVClusters;
				maxClusterSize = &maxHeVClusterSize;
			} else {
				numClusters = &numHeIClusters;
				maxClusterSize = &maxHeIClusterSize;
			}
		} else if (!isMixed && singleSpeciesMap.count(compStr) == 0) {
			/// Put the reactant in its map
			singleSpeciesMap[compStr] = reactant;

			// Figure out whether we have He, V or I and set the keys
			if (numHe > 0) {
				numClusters = &numHeClusters;
				maxClusterSize = &maxHeClusterSize;
			} else if (numV > 0) {
				numClusters = &numVClusters;
				maxClusterSize = &maxVClusterSize;
			} else {
				numClusters = &numIClusters;
				maxClusterSize = &maxIClusterSize;
			}
		} else {
			std::stringstream errStream;
			errStream << "PSIClusterReactionNetwork Message: "
					<< "Duplicate Reactant (He=" << numHe << ",V=" << numV
					<< ",I=" << numI << ") not added!" << std::endl;
			throw errStream.str();
		}

		// Increment the number of total clusters of this type
		(*numClusters)++;
		// Increment the max cluster size key
		int clusterSize = numHe + numV + numI;
		(*maxClusterSize) = std::max(clusterSize, (*maxClusterSize));
		// Update the size
		++networkSize;
		// Set the id for this cluster
		reactant->setId(networkSize);
		// Get the vector for this reactant from the type map
		auto clusters = clusterTypeMap[reactant->getType()];

		clusters->push_back(reactant);
		// Add the pointer to the list of all clusters
		allReactants->push_back(reactant.get());
=======
bool PSIClusterReactionNetwork::canDissociate(
		ProductionReaction& reaction) const {
	// Assume reaction can dissociate by default.
	bool ret = true;

	// Check if at least one of the potentially emitted cluster is size one
	if (reaction.first.getSize() != 1 && reaction.second.getSize() != 1) {
		// Don't add the reverse reaction
		ret = false;
	}

	// Check for trap mutations (with XOR)
	else if ((reaction.first.getType() == ReactantType::I)
			== !(reaction.second.getType() == ReactantType::I)) {
		// Don't add the reverse reaction
		ret = false;
	}

	return ret;
}

void PSIClusterReactionNetwork::checkForDissociation(
		IReactant& emittingReactant, ProductionReaction& reaction, int a, int b,
		int c, int d) {

	// Check if reaction can dissociate.
	if (canDissociate(reaction)) {
		// The dissociation can occur, so create a reaction for it.
		defineDissociationReaction(reaction, emittingReactant, a, b, c, d);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

<<<<<<< HEAD
void PSIClusterReactionNetwork::addSuper(std::shared_ptr<IReactant> reactant) {
	// Local Declarations
	int numHe = 0, numV = 0, numI = 0;
	bool isMixed = false;
	int* numClusters = nullptr;

	// Only add a complete reactant
	if (reactant != NULL) {
		// Get the composition
		auto composition = reactant->getComposition();
		std::string compStr = reactant->getCompositionString();
		// Get the species sizes
		numHe = composition.at(heType);
		numV = composition.at(vType);
		numI = composition.at(iType);
		// Determine if the cluster is a compound. If there is more than one
		// type, then the check below will sum to greater than one and we know
		// that we have a mixed cluster.
		isMixed = ((numHe > 0) + (numV > 0) + (numI > 0)) > 1;
		// Only add the element if we don't already have it
		// Add the compound or regular reactant.
		if (isMixed && superSpeciesMap.count(compStr) == 0) {
			// Put the compound in its map
			superSpeciesMap[compStr] = reactant;
			// Set the key
			numClusters = &numSuperClusters;
		} else {
			std::stringstream errStream;
			errStream << "PSIClusterReactionNetwork Message: "
					<< "Duplicate Super Reactant (He=" << numHe << ",V=" << numV
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

void PSIClusterReactionNetwork::removeReactants(
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
=======
void PSIClusterReactionNetwork::setTemperature(double temp) {
	ReactionNetwork::setTemperature(temp);

	computeRateConstants();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSIClusterReactionNetwork::reinitializeNetwork() {
<<<<<<< HEAD
	// Recount HeV clusters
	numHeVClusters = 0;
	// Reset the Ids
	int id = 0;
	for (auto it = allReactants->begin(); it != allReactants->end(); ++it) {
		id++;
		(*it)->setId(id);
		(*it)->setHeMomentumId(id);
		(*it)->setVMomentumId(id);

		(*it)->optimizeReactions();

		if ((*it)->getType() == heVType)
			numHeVClusters++;
	}

	// Reset the network size
	networkSize = id;

	// Get all the super clusters and loop on them
	for (auto it = clusterTypeMap[PSISuperType]->begin();
			it != clusterTypeMap[PSISuperType]->end(); ++it) {
		id++;
		(*it)->setHeMomentumId(id);
		id++;
		(*it)->setVMomentumId(id);
=======

	// Reset the Ids
	// std::for_each is guaranteed to visit reactants in order for C++11.
	int id = 0;
	std::for_each(allReactants.begin(), allReactants.end(),
			[&id](IReactant& currReactant) {
				id++;
				currReactant.setId(id);
				currReactant.setHeMomentumId(id);
				currReactant.setVMomentumId(id);
			});

	// Get all the super clusters and loop on them
	for (auto const& currMapItem : clusterTypeMap[ReactantType::PSISuper]) {

		auto& currCluster = static_cast<PSISuperCluster&>(*(currMapItem.second));

		id++;
		currCluster.setHeMomentumId(id);
		id++;
		currCluster.setVMomentumId(id);

		// Update the HeV size
		IReactant::SizeType clusterSize = currCluster.getHeBounds().second
				+ currCluster.getVBounds().second;
		if (clusterSize > maxClusterSizeMap[ReactantType::HeV]) {
			maxClusterSizeMap[ReactantType::HeV] = clusterSize;
		}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

void PSIClusterReactionNetwork::reinitializeConnectivities() {
<<<<<<< HEAD
	// Loop on all the reactants to reset their connectivities
	for (auto it = allReactants->begin(); it != allReactants->end(); ++it) {
		(*it)->resetConnectivities();
	}
=======

	// Reset connectivities of each reactant.
	std::for_each(allReactants.begin(), allReactants.end(),
			[](IReactant& currReactant) {
				currReactant.resetConnectivities();
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSIClusterReactionNetwork::updateConcentrationsFromArray(
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
		auto cluster = (PSISuperCluster *) reactants->at(i);
		id = cluster->getId() - 1;
		cluster->setZerothMomentum(concentrations[id]);
		id = cluster->getHeMomentumId() - 1;
		cluster->setHeMomentum(concentrations[id]);
		id = cluster->getVMomentumId() - 1;
		cluster->setVMomentum(concentrations[id]);
	}
=======

	// Set the concentration on each reactant.
	std::for_each(allReactants.begin(), allReactants.end(),
			[&concentrations](IReactant& currReactant) {
				auto id = currReactant.getId() - 1;
				currReactant.setConcentration(concentrations[id]);
			});

	// Set the moments
	auto const& superTypeMap = getAll(ReactantType::PSISuper);
	std::for_each(superTypeMap.begin(), superTypeMap.end(),
			[&concentrations](const ReactantMap::value_type& currMapItem) {

				auto& cluster = static_cast<PSISuperCluster&>(*(currMapItem.second));

				cluster.setZerothMomentum(concentrations[cluster.getId() - 1]);
				cluster.setHeMomentum(concentrations[cluster.getHeMomentumId() - 1]);
				cluster.setVMomentum(concentrations[cluster.getVMomentumId() - 1]);
			});
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void PSIClusterReactionNetwork::getDiagonalFill(int *diagFill) {
<<<<<<< HEAD
	// Get all the super clusters
	auto superClusters = getAll(PSISuperType);

	// Degrees of freedom is the total number of clusters in the network
	const int dof = getDOF();

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
		// Get the helium momentum id so that the connectivity can be lined up in
		// the proper column
		id = reactant->getHeMomentumId() - 1;
=======
	// Degrees of freedom is the total number of clusters in the network
	const int dof = getDOF();

	// Get the connectivity for each reactant
	std::for_each(allReactants.begin(), allReactants.end(),
			[&diagFill,&dof,this](const IReactant& reactant) {

				// Get the reactant's connectivity
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
	for (auto const& superMapItem : getAll(ReactantType::PSISuper)) {

		auto const& reactant =
				static_cast<PSISuperCluster&>(*(superMapItem.second));

		// Get the reactant and its connectivity
		auto const& connectivity = reactant.getConnectivity();
		auto connectivityLength = connectivity.size();
		// Get the helium momentum id so that the connectivity can be lined up in
		// the proper column
		auto id = reactant.getHeMomentumId() - 1;
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

		// Get the vacancy momentum id so that the connectivity can be lined up in
		// the proper column
<<<<<<< HEAD
		id = reactant->getVMomentumId() - 1;
=======
		id = reactant.getVMomentumId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
		}
		// Update the map
		dFillMap[id] = columnIds;
	}

	return;
}

double PSIClusterReactionNetwork::getTotalAtomConcentration() {
	// Initial declarations
	double heliumConc = 0.0;

<<<<<<< HEAD
	// Get all the He clusters
	auto heClusters = getAll(heType);
	// Loop on them
	for (int i = 0; i < heClusters.size(); i++) {
		// Get the cluster and its composition
		auto cluster = heClusters[i];
		double size = cluster->getSize();

		// Add the concentration times the He content to the total helium concentration
		heliumConc += cluster->getConcentration() * size;
	}

	// Get all the HeV clusters
	auto heVClusters = getAll(heVType);
	// Loop on them
	for (int i = 0; i < heVClusters.size(); i++) {
		// Get the cluster and its composition
		auto cluster = heVClusters[i];
		auto comp = cluster->getComposition();

		// Add the concentration times the He content to the total helium concentration
		heliumConc += cluster->getConcentration() * comp[heType];
	}

	// Get all the super clusters
	auto superClusters = getAll(PSISuperType);
	// Loop on them
	for (int i = 0; i < superClusters.size(); i++) {
		// Get the cluster
		auto cluster = (PSISuperCluster *) superClusters[i];

		// Add its total helium concentration helium concentration
		heliumConc += cluster->getTotalHeliumConcentration();
=======
	// Sum over all He clusters.
	for (auto const& currMapItem : getAll(ReactantType::He)) {

		// Get the cluster and its composition
		auto const& cluster = *(currMapItem.second);
		double size = cluster.getSize();

		// Add the concentration times the He content to the total helium concentration
		heliumConc += cluster.getConcentration() * size;
	}

	// Sum over all HeV clusters.
	for (auto const& currMapItem : getAll(ReactantType::HeV)) {

		// Get the cluster and its composition
		auto const& cluster = *(currMapItem.second);
		auto& comp = cluster.getComposition();

		// Add the concentration times the He content to the total helium concentration
		heliumConc += cluster.getConcentration() * comp[toCompIdx(Species::He)];
	}

	// Sum over all super clusters.
	for (auto const& currMapItem : getAll(ReactantType::PSISuper)) {

		// Get the cluster
		auto const& cluster =
				static_cast<PSISuperCluster&>(*(currMapItem.second));

		// Add its total helium concentration helium concentration
		heliumConc += cluster.getTotalHeliumConcentration();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return heliumConc;
}

double PSIClusterReactionNetwork::getTotalTrappedAtomConcentration() {
	// Initial declarations
	double heliumConc = 0.0;

<<<<<<< HEAD
	// Get all the HeV clusters
	auto heVClusters = getAll(heVType);
	// Loop on them
	for (int i = 0; i < heVClusters.size(); i++) {
		// Get the cluster and its composition
		auto cluster = heVClusters[i];
		auto comp = cluster->getComposition();

		// Add the concentration times the He content to the total helium concentration
		heliumConc += cluster->getConcentration() * comp[heType];
	}

	// Get all the super clusters
	auto superClusters = getAll(PSISuperType);
	// Loop on them
	for (int i = 0; i < superClusters.size(); i++) {
		// Get the cluster
		auto cluster = (PSISuperCluster *) superClusters[i];

		// Add its total helium concentration
		heliumConc += cluster->getTotalHeliumConcentration();
=======
	// Sum over all HeV clusters.
	for (auto const& currMapItem : getAll(ReactantType::HeV)) {
		// Get the cluster and its composition
		auto const& cluster = *(currMapItem.second);
		auto& comp = cluster.getComposition();

		// Add the concentration times the He content to the total helium concentration
		heliumConc += cluster.getConcentration() * comp[toCompIdx(Species::He)];
	}

	// Sum over all super clusters.
	for (auto const& currMapItem : getAll(ReactantType::PSISuper)) {
		// Get the cluster
		auto const& cluster =
				static_cast<PSISuperCluster&>(*(currMapItem.second));

		// Add its total helium concentration
		heliumConc += cluster.getTotalHeliumConcentration();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return heliumConc;
}

double PSIClusterReactionNetwork::getTotalVConcentration() {
	// Initial declarations
	double vConc = 0.0;

<<<<<<< HEAD
	// Get all the V clusters
	auto vClusters = getAll(vType);
	// Loop on them
	for (int i = 0; i < vClusters.size(); i++) {
		// Get the cluster and its composition
		auto cluster = vClusters[i];
		double size = cluster->getSize();

		// Add the concentration times the V content to the total vacancy concentration
		vConc += cluster->getConcentration() * size;
	}

	// Get all the HeV clusters
	auto heVClusters = getAll(heVType);
	// Loop on them
	for (int i = 0; i < heVClusters.size(); i++) {
		// Get the cluster and its composition
		auto cluster = heVClusters[i];
		auto comp = cluster->getComposition();

		// Add the concentration times the V content to the total vacancy concentration
		vConc += cluster->getConcentration() * comp[vType];
	}

	// Get all the super clusters
	auto superClusters = getAll(PSISuperType);
	// Loop on them
	for (int i = 0; i < superClusters.size(); i++) {
		// Get the cluster
		auto cluster = (PSISuperCluster *) superClusters[i];

		// Add its total vacancy concentration
		vConc += cluster->getTotalVacancyConcentration();
=======
	// Sum over all V clusters.
	for (auto const& currMapItem : getAll(ReactantType::V)) {
		// Get the cluster and its composition
		auto const& cluster = *(currMapItem.second);
		double size = cluster.getSize();

		// Add the concentration times the V content to the total vacancy concentration
		vConc += cluster.getConcentration() * size;
	}

	// Sum over all HeV clusters
	for (auto const& currMapItem : getAll(ReactantType::HeV)) {
		// Get the cluster and its composition
		auto const& cluster = *(currMapItem.second);
		auto& comp = cluster.getComposition();

		// Add the concentration times the V content to the total vacancy concentration
		vConc += cluster.getConcentration() * comp[toCompIdx(Species::V)];
	}

	// Sum over all super clusters
	for (auto const& currMapItem : getAll(ReactantType::PSISuper)) {
		// Get the cluster
		auto const& cluster =
				static_cast<PSISuperCluster&>(*(currMapItem.second));

		// Add its total vacancy concentration
		vConc += cluster.getTotalVacancyConcentration();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return vConc;
}

double PSIClusterReactionNetwork::getTotalIConcentration() {
	// Initial declarations
	double iConc = 0.0;

<<<<<<< HEAD
	// Get all the V clusters
	auto iClusters = getAll(iType);
	// Loop on them
	for (int i = 0; i < iClusters.size(); i++) {
		// Get the cluster and its composition
		auto cluster = iClusters[i];
		double size = cluster->getSize();

		// Add the concentration times the I content to the total interstitial concentration
		iConc += cluster->getConcentration() * size;
=======
	// Sum over all I clusters
	for (auto const& currMapItem : getAll(ReactantType::I)) {
		// Get the cluster and its composition
		auto const& cluster = *(currMapItem.second);
		double size = cluster.getSize();

		// Add the concentration times the I content to the total interstitial concentration
		iConc += cluster.getConcentration() * size;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return iConc;
}

void PSIClusterReactionNetwork::computeRateConstants() {
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

void PSIClusterReactionNetwork::computeAllFluxes(double *updatedConcOffset) {
<<<<<<< HEAD
	// Initial declarations
	IReactant * cluster;
	PSISuperCluster * superCluster;
	double flux = 0.0;
	int reactantIndex = 0;
	auto superClusters = getAll(PSISuperType);

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
		superCluster = (xolotlCore::PSISuperCluster *) superClusters[i];

		// Compute the helium momentum flux
		flux = superCluster->getHeMomentumFlux();
		// Update the concentration of the cluster
		reactantIndex = superCluster->getHeMomentumId() - 1;
		updatedConcOffset[reactantIndex] += flux;

		// Compute the vacancy momentum flux
		flux = superCluster->getVMomentumFlux();
		// Update the concentration of the cluster
		reactantIndex = superCluster->getVMomentumId() - 1;
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
	for (auto const& currMapItem : getAll(ReactantType::PSISuper)) {

		auto const& superCluster =
				static_cast<PSISuperCluster&>(*(currMapItem.second));

		// Compute the helium momentum flux
		auto flux = superCluster.getHeMomentumFlux();
		// Update the concentration of the cluster
		auto reactantIndex = superCluster.getHeMomentumId() - 1;
		updatedConcOffset[reactantIndex] += flux;

		// Compute the vacancy momentum flux
		flux = superCluster.getVMomentumFlux();
		// Update the concentration of the cluster
		reactantIndex = superCluster.getVMomentumId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		updatedConcOffset[reactantIndex] += flux;
	}

	return;
}

void PSIClusterReactionNetwork::computeAllPartials(double *vals, int *indices,
		int *size) {
	// Initial declarations
<<<<<<< HEAD
	int reactantIndex = 0, pdColIdsVectorSize = 0;
	const int dof = getDOF();
	std::vector<double> clusterPartials;
	clusterPartials.resize(dof, 0.0);
	// Get the super clusters
	auto superClusters = getAll(PSISuperType);

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
=======
	const int dof = getDOF();
	std::vector<double> clusterPartials;
	clusterPartials.resize(dof, 0.0);

	// Get the super clusters
	auto const& superClusters = getAll(ReactantType::PSISuper);

	// Make a vector of types for the non super clusters
	std::vector<ReactantType> typeVec { ReactantType::He, ReactantType::V,
			ReactantType::I, ReactantType::HeV };
	// Loop on it
	for (auto tvIter = typeVec.begin(); tvIter != typeVec.end(); ++tvIter) {

		auto currType = *tvIter;

		// Consider all reactants of the current type.
		auto const& currTypeReactantMap = getAll(currType);

		// Update the column in the Jacobian that represents each normal reactant
		for (auto const& currMapItem : currTypeReactantMap) {

			auto const& reactant =
					static_cast<PSICluster&>(*(currMapItem.second));

			// Get the reactant index
			auto reactantIndex = reactant.getId() - 1;

			// Get the partial derivatives
			reactant.getPartialDerivatives(clusterPartials);
			// Get the list of column ids from the map
			auto const& pdColIdsVector = dFillMap.at(reactantIndex);
			// Number of partial derivatives
			auto pdColIdsVectorSize = pdColIdsVector.size();
			size[reactantIndex] = pdColIdsVectorSize;

			// Loop over the list of column ids
			for (int j = 0; j < pdColIdsVectorSize; j++) {
				// Set the index
				indices[reactantIndex * dof + j] = pdColIdsVector[j];

				// Get the partial derivative from the array of all of the partials
				vals[reactantIndex * dof + j] =
						clusterPartials[pdColIdsVector[j]];

				// Reset the cluster partial value to zero. This is much faster
				// than using memset.
				clusterPartials[pdColIdsVector[j]] = 0.0;
			}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
	}

	// Update the column in the Jacobian that represents the moment for the super clusters
<<<<<<< HEAD
	for (int i = 0; i < superClusters.size(); i++) {
		auto reactant = (PSISuperCluster *) superClusters[i];

		// Get the super cluster index
		reactantIndex = reactant->getId() - 1;

		// Get the partial derivatives
		reactant->getPartialDerivatives(clusterPartials);
		// Get the list of column ids from the map
		auto pdColIdsVector = dFillMap.at(reactantIndex);
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

		// Get the helium momentum index
		reactantIndex = reactant->getHeMomentumId() - 1;

		// Get the partial derivatives
		reactant->getHeMomentPartialDerivatives(clusterPartials);
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

		// Get the vacancy momentum index
		reactantIndex = reactant->getVMomentumId() - 1;

		// Get the partial derivatives
		reactant->getVMomentPartialDerivatives(clusterPartials);
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
=======
	for (auto const& currMapItem : superClusters) {

		auto const& reactant =
				static_cast<PSISuperCluster&>(*(currMapItem.second));

		{
			// Get the super cluster index
			auto reactantIndex = reactant.getId() - 1;

			// Get the partial derivatives
			reactant.getPartialDerivatives(clusterPartials);

			// Get the list of column ids from the map
			auto const& pdColIdsVector = dFillMap.at(reactantIndex);
			// Number of partial derivatives
			auto pdColIdsVectorSize = pdColIdsVector.size();
			size[reactantIndex] = pdColIdsVectorSize;

			// Loop over the list of column ids
			for (int j = 0; j < pdColIdsVectorSize; j++) {
				// Set the index
				indices[reactantIndex * dof + j] = pdColIdsVector[j];
				// Get the partial derivative from the array of all of the partials
				vals[reactantIndex * dof + j] =
						clusterPartials[pdColIdsVector[j]];

				// Reset the cluster partial value to zero. This is much faster
				// than using memset.
				clusterPartials[pdColIdsVector[j]] = 0.0;
			}
		}

		{
			// Get the helium momentum index
			auto reactantIndex = reactant.getHeMomentumId() - 1;

			// Get the partial derivatives
			reactant.getHeMomentPartialDerivatives(clusterPartials);
			// Get the list of column ids from the map
			auto const& pdColIdsVector = dFillMap.at(reactantIndex);
			// Number of partial derivatives
			auto pdColIdsVectorSize = pdColIdsVector.size();
			size[reactantIndex] = pdColIdsVectorSize;

			// Loop over the list of column ids
			for (int j = 0; j < pdColIdsVectorSize; j++) {
				// Set the index
				indices[reactantIndex * dof + j] = pdColIdsVector[j];
				// Get the partial derivative from the array of all of the partials
				vals[reactantIndex * dof + j] =
						clusterPartials[pdColIdsVector[j]];

				// Reset the cluster partial value to zero. This is much faster
				// than using memset.
				clusterPartials[pdColIdsVector[j]] = 0.0;
			}
		}

		{
			// Get the vacancy momentum index
			auto reactantIndex = reactant.getVMomentumId() - 1;

			// Get the partial derivatives
			reactant.getVMomentPartialDerivatives(clusterPartials);
			// Get the list of column ids from the map
			auto const& pdColIdsVector = dFillMap.at(reactantIndex);
			// Number of partial derivatives
			auto pdColIdsVectorSize = pdColIdsVector.size();
			size[reactantIndex] = pdColIdsVectorSize;

			// Loop over the list of column ids
			for (int j = 0; j < pdColIdsVectorSize; j++) {
				// Set the index
				indices[reactantIndex * dof + j] = pdColIdsVector[j];
				// Get the partial derivative from the array of all of the partials
				vals[reactantIndex * dof + j] =
						clusterPartials[pdColIdsVector[j]];

				// Reset the cluster partial value to zero. This is much faster
				// than using memset.
				clusterPartials[pdColIdsVector[j]] = 0.0;
			}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
	}

	return;
}
<<<<<<< HEAD
=======

double PSIClusterReactionNetwork::computeBindingEnergy(
		const DissociationReaction& reaction) const {
	// for the dissociation A --> B + C we need A binding energy
	// E_b(A) = E_f(B) + E_f(C) - E_f(A) where E_f is the formation energy
	double bindingEnergy = reaction.first.getFormationEnergy()
			+ reaction.second.getFormationEnergy()
			- reaction.dissociating.getFormationEnergy();

	return max(bindingEnergy, -5.0);
}

IReactant * PSIClusterReactionNetwork::getSuperFromComp(IReactant::SizeType nHe,
		IReactant::SizeType nV) {

	// Requests for finding a particular supercluster have high locality.
	// See if the last supercluster we were asked to find is the right
	// one for this request.
	static IReactant* lastRet = nullptr;
	if (lastRet and static_cast<PSISuperCluster*>(lastRet)->isIn(nHe, nV)) {
		return lastRet;
	}

	// We didn't find the last supercluster in our cache, so do a full lookup.
	IReactant* ret = nullptr;

	for (auto const& superMapItem : getAll(ReactantType::PSISuper)) {

		auto const& reactant =
				static_cast<PSISuperCluster&>(*(superMapItem.second));
		if (reactant.isIn(nHe, nV))
			return superMapItem.second.get();
	}

	return ret;
}

} // namespace xolotlCore

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
