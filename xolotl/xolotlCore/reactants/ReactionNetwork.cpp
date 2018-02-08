#include "ReactionNetwork.h"
<<<<<<< HEAD
#include "Reactant.h"
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <xolotlPerf.h>
#include <iostream>
#include <cassert>

using namespace xolotlCore;

<<<<<<< HEAD
ReactionNetwork::ReactionNetwork()
  : properties(new std::map<std::string, std::string>())
{
//    concUpdateCounter = xolotlPerf::getHandlerRegistry()->getEventCounter("net_conc_updates");
	return;
}

ReactionNetwork::ReactionNetwork(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry)
  : properties(new std::map<std::string, std::string>()), handlerRegistry(registry)
{
	// Counter for the number of times the network concentration is updated.
    concUpdateCounter = handlerRegistry->getEventCounter("net_conc_updates");
=======
ReactionNetwork::ReactionNetwork() :
		temperature(0.0), networkSize(0), reactionsEnabled(true), dissociationsEnabled(
				true), numVClusters(0), numIClusters(0), numSuperClusters(0), maxVClusterSize(
				0), maxIClusterSize(0) {
//    concUpdateCounter = xolotlPerf::getHandlerRegistry()->getEventCounter("net_conc_updates");
	// Setup the vector to hold all of the reactants
	allReactants = make_shared<std::vector<IReactant *>>();
	return;
}

ReactionNetwork::ReactionNetwork(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		handlerRegistry(registry), temperature(0.0), networkSize(0), reactionsEnabled(
				true), dissociationsEnabled(true), numVClusters(0), numIClusters(
				0), numSuperClusters(0), maxVClusterSize(0), maxIClusterSize(0) {
	// Counter for the number of times the network concentration is updated.
	concUpdateCounter = handlerRegistry->getEventCounter("net_conc_updates");
	// Setup the vector to hold all of the reactants
	allReactants = make_shared<std::vector<IReactant *>>();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

ReactionNetwork::ReactionNetwork(const ReactionNetwork &other) {
<<<<<<< HEAD
	// The copy constructor of std::map copies each of the keys and values.
	properties.reset(new std::map<std::string, std::string>(*other.properties));

	handlerRegistry = other.handlerRegistry;

    // TODO - do we copy the source ReactionNetwork's counter also?
    // Or should we have our own counter?  How to distinguish them by name?
//    concUpdateCounter = xolotlPerf::getHandlerRegistry()->getEventCounter("net_conc_updates");

	// Counter for the number of times the network concentration is updated.
    concUpdateCounter = handlerRegistry->getEventCounter("net_conc_updates");
=======
	handlerRegistry = other.handlerRegistry;
	allReactants = other.allReactants;
	temperature = other.temperature;
	networkSize = other.networkSize;
	names = other.names;
	compoundNames = other.compoundNames;
	reactionsEnabled = other.reactionsEnabled;
	dissociationsEnabled = other.dissociationsEnabled;
	numVClusters = other.numVClusters;
	numIClusters = other.numIClusters;
	numSuperClusters = other.numSuperClusters;
	maxVClusterSize = other.maxVClusterSize;
	maxIClusterSize = other.maxIClusterSize;

	// TODO - do we copy the source ReactionNetwork's counter also?
	// Or should we have our own counter?  How to distinguish them by name?

	// Counter for the number of times the network concentration is updated.
	concUpdateCounter = handlerRegistry->getEventCounter("net_conc_updates");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
=======
double ReactionNetwork::calculateReactionRateConstant(
		ProductionReaction * reaction) const {
	// Get the reaction radii
	double r_first = reaction->first->getReactionRadius();
	double r_second = reaction->second->getReactionRadius();

	// Get the diffusion coefficients
	double firstDiffusion = reaction->first->getDiffusionCoefficient();
	double secondDiffusion = reaction->second->getDiffusionCoefficient();

	// Calculate and return
	double k_plus = 4.0 * xolotlCore::pi * (r_first + r_second)
			* (firstDiffusion + secondDiffusion);
	return k_plus;
}

double ReactionNetwork::computeBindingEnergy(
		DissociationReaction * reaction) const {
	// for the dissociation A --> B + C we need A binding energy
	// E_b(A) = E_f(B) + E_f(C) - E_f(A) where E_f is the formation energy
	double bindingEnergy = reaction->first->getFormationEnergy()
			+ reaction->second->getFormationEnergy()
			- reaction->dissociating->getFormationEnergy();

	if (reaction->dissociating->getName() == "He_2V_1") {
		bindingEnergy = 3.00;
	} else if (reaction->dissociating->getName() == "He_3V_1") {
		bindingEnergy = 2.75;
	} else if (reaction->dissociating->getName() == "He_2V_2"
			&& reaction->first->getName() == "He_1V_2") {
		bindingEnergy = 4.42;
	} else if (reaction->dissociating->getName() == "He_4V_1") {
		bindingEnergy = 2.45;
	} else if (reaction->dissociating->getName() == "He_1V_1") {
		bindingEnergy = 4.00;
	} else if (reaction->dissociating->getName() == "He_1V_2"
			&& reaction->first->getName() == "He_1V_1") {
		bindingEnergy = 1.67;
	}
	return bindingEnergy;
}

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
void ReactionNetwork::fillConcentrationsArray(double * concentrations) {
	// Local Declarations
	auto reactants = getAll();
	int size = reactants->size();
<<<<<<< HEAD
	int id = 1;
=======
	int id = -1;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Fill the array
	for (int i = 0; i < size; i++) {
		id = reactants->at(i)->getId() - 1;
		concentrations[id] = reactants->at(i)->getConcentration();
	}

	return;
}

void ReactionNetwork::updateConcentrationsFromArray(double * concentrations) {
	// Local Declarations
<<<<<<< HEAD
	auto reactants = getAll();
	int size = reactants->size();
	int id = 1;

	// Set the concentrations
    concUpdateCounter->increment();		// increment the update concentration counter
	for (int i = 0; i < size; i++) {
		id = reactants->at(i)->getId() - 1;
		reactants->at(i)->setConcentration(concentrations[id]);
=======
	auto allReactants = this->getAll();
	int id = -1;

	// Set the concentrations
	concUpdateCounter->increment();	// increment the update concentration counter
	for (auto iter = allReactants->begin(); iter != allReactants->end();
			++iter) {
		id = (*iter)->getId() - 1;
		(*iter)->setConcentration(concentrations[id]);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

void ReactionNetwork::askReactantsToReleaseNetwork(void) {
	// Get all the reactants
<<<<<<< HEAD
    auto allReactants = this->getAll();    

    // Loop on each reactant to release the network
    for(auto iter = allReactants->begin(); iter != allReactants->end(); ++iter) {
        Reactant* currReactant = *iter;
        assert( currReactant != NULL );

        currReactant->releaseReactionNetwork();
    }
=======
	auto allReactants = this->getAll();

	// Loop on each reactant to release the network
	for (auto iter = allReactants->begin(); iter != allReactants->end();
			++iter) {
		IReactant* currReactant = *iter;
		assert(currReactant != NULL);

		currReactant->releaseReactionNetwork();
	}
}

void ReactionNetwork::setTemperature(double temp) {
	// Set the temperature
	temperature = temp;

	// Update the temperature for all of the clusters
	for (int i = 0; i < networkSize; i++) {
		// This part will set the temperature in each reactant
		// and recompute the diffusion coefficient
		allReactants->at(i)->setTemperature(temp);
	}

	return;
}

double ReactionNetwork::getTemperature() const {
	return temperature;
}

IReactant * ReactionNetwork::get(const std::string& type,
		const int size) const {
	// Local Declarations
	std::shared_ptr<IReactant> retReactant;

	return (IReactant *) retReactant.get();
}

IReactant * ReactionNetwork::getCompound(const std::string& type,
		const std::vector<int>& sizes) const {
	// Local Declarations
	std::shared_ptr<IReactant> retReactant;

	return (IReactant *) retReactant.get();
}

const std::shared_ptr<std::vector<IReactant *>> & ReactionNetwork::getAll() const {
	return allReactants;
}

std::vector<IReactant *> ReactionNetwork::getAll(
		const std::string& name) const {
	// Local Declarations
	std::vector<IReactant *> reactants;

	return reactants;
}

const std::vector<std::string> & ReactionNetwork::getNames() const {
	return names;
}

const std::vector<std::string> & ReactionNetwork::getCompoundNames() const {
	return compoundNames;
}

std::shared_ptr<ProductionReaction> ReactionNetwork::addProductionReaction(
		std::shared_ptr<ProductionReaction> reaction) {
	// Loop on all the production reactions
	for (auto iter = allProductionReactions.rbegin();
			iter != allProductionReactions.rend(); iter++) {
		if (((*iter)->first == reaction->first
				&& (*iter)->second == reaction->second)
				|| ((*iter)->first == reaction->second
						&& (*iter)->second == reaction->first)) {
			// Return the already existing one
			return (*iter);
		}
	}

	// The reaction is not present in the vector yet so add it
	allProductionReactions.push_back(reaction);

	return reaction;
}

std::shared_ptr<DissociationReaction> ReactionNetwork::addDissociationReaction(
		std::shared_ptr<DissociationReaction> reaction) {
	// Loop on all the dissociation reactions
	for (auto iter = allDissociationReactions.rbegin();
			iter != allDissociationReactions.rend(); iter++) {
		if ((*iter)->dissociating == reaction->dissociating) {
			if (((*iter)->first == reaction->first
					&& (*iter)->second == reaction->second)
					|| ((*iter)->first == reaction->second
							&& (*iter)->second == reaction->first)) {
				// Return the already existing one
				return (*iter);
			}
		}
	}

	// The reaction is not present in the vector yet so add it
	// But first you have to link it to the reverse reaction
	// Create the reverse reaction to get a pointer to it
	auto reverseReaction = std::make_shared<ProductionReaction>(reaction->first,
			reaction->second);
	// Get the pointer to the reaction in the production vector
	reverseReaction = addProductionReaction(reverseReaction);
	// Update this pointer in this reaction
	reaction->reverseReaction = reverseReaction.get();
	// Add it to the vector
	allDissociationReactions.push_back(reaction);

	return reaction;
}

void ReactionNetwork::pushProductionReaction(
		std::shared_ptr<ProductionReaction> reaction) {
	// Add the reaction
	allProductionReactions.push_back(reaction);

	return;
}

void ReactionNetwork::pushDissociationReaction(
		std::shared_ptr<DissociationReaction> reaction) {
	// First you have to link it to the reverse reaction
	// Create the reverse reaction to get a pointer to it
	auto reverseReaction = std::make_shared<ProductionReaction>(reaction->first,
			reaction->second);
	// Get the pointer to the reaction in the production vector
	reverseReaction = addProductionReaction(reverseReaction);
	// Update this pointer in this reaction
	reaction->reverseReaction = reverseReaction.get();
	// Add it to the vector
	allDissociationReactions.push_back(reaction);

	return;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}
