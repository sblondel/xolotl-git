// Includes
#include "Reactant.h"
#include "ReactionNetwork.h"
<<<<<<< HEAD
#include <xolotlPerf.h>
#include <iostream>
#include <math.h>
#include <MathUtils.h>
#include <Constants.h>
=======
#include "xolotlPerf/HandlerRegistryFactory.h"
#include <iostream>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

// Namespaces
using namespace xolotlCore;

Reactant::Reactant() :
<<<<<<< HEAD
		concentration(0.0), id(0), xeMomId(0), heMomId(0), vMomId(0), temperature(
				0.0), typeName(""), network(nullptr), handlerRegistry(nullptr), size(
				0), formationEnergy(0.0), diffusionFactor(0.0), diffusionCoefficient(
				0.0), migrationEnergy(0.0), name("Reactant"), reactionRadius(
				0.0) {
	// Setup the composition map.
	compositionMap[xeType] = 0;
	compositionMap[heType] = 0;
	compositionMap[vType] = 0;
	compositionMap[iType] = 0;
}

Reactant::Reactant(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		concentration(0.0), id(0), xeMomId(0), heMomId(0), vMomId(0), temperature(
				0.0), typeName(""), network(nullptr), handlerRegistry(registry), size(
				0), formationEnergy(0.0), diffusionFactor(0.0), diffusionCoefficient(
				0.0), migrationEnergy(0.0), name("Reactant"), reactionRadius(
				0.0) {
	// Setup the composition map.
	compositionMap[xeType] = 0;
	compositionMap[heType] = 0;
	compositionMap[vType] = 0;
	compositionMap[iType] = 0;
}

Reactant::Reactant(Reactant &other) :
		concentration(other.concentration), name(other.name), typeName(
				other.typeName), id(other.id), xeMomId(other.xeMomId), heMomId(
				other.heMomId), vMomId(other.vMomId), temperature(
				other.temperature), network(other.network), handlerRegistry(
				other.handlerRegistry), size(other.size), formationEnergy(
				other.formationEnergy), diffusionFactor(other.diffusionFactor), diffusionCoefficient(
				other.diffusionCoefficient), migrationEnergy(
				other.migrationEnergy), reactionRadius(other.reactionRadius), reactionConnectivitySet(
				other.reactionConnectivitySet), dissociationConnectivitySet(
				other.dissociationConnectivitySet) {
	// Setup the composition map.
	compositionMap[xeType] = other.compositionMap[xeType];
	compositionMap[heType] = other.compositionMap[heType];
	compositionMap[vType] = other.compositionMap[vType];
	compositionMap[iType] = other.compositionMap[iType];
}

void Reactant::recomputeDiffusionCoefficient(double temp) {
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

std::vector<int> Reactant::getConnectivity() const {
	// The connectivity array by default is filled with
	// zeros.
	int connectivityLength = network->getDOF();
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);

	// This reactant should be connected to itself
	connectivity[id - 1] = 1;

	return connectivity;
}

std::string Reactant::toCanonicalString(std::string type,
		const std::map<std::string, int>& composition) {

	// Construct the canonical string representation of the given composition.
	// Note that this can only be considered to produce a canonical
	// representation of the reactant map's contents if the reactant map
	// is kept in a collection where we are guaranteed that iterating
	// over its contents will always be done in the same order, regardless
	// of how the map was produced.  Thankfully, std::map is an
	// ordered map and gives this guarantee.
	std::ostringstream ostr;
	ostr << type << ':';
	for (auto iter = composition.begin(); iter != composition.end(); ++iter) {
		// Add the current reactant's name and size to the string.
		// Note that we don't really care about nice formatting, since
		// this isn't intended to be a human-readable string.
		ostr << iter->first << iter->second;
	}
	return ostr.str();
}

void Reactant::setTemperature(double temp) {
	temperature = temp;

	// Recompute the diffusion coefficient
	recomputeDiffusionCoefficient(temp);
}



void Reactant::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

void Reactant::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

=======
		concentration(0.0e-16), name(""), id(0) {

	// Temporary definition used to specify the type of performance handler registry
	// that will be used (standard or dummy).  Currently, the handler registry is set via
	// commandline argument and the only way to access which handler registry will be used
	// is through getHandlerRegistry
//	handlerRegistry = xolotlPerf::getHandlerRegistry();
}

Reactant::Reactant(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		concentration(0.0e-16), name(""), id(0), handlerRegistry(registry) {

}

Reactant::Reactant(const Reactant &other) :
		concentration(other.concentration), name(other.name), id(other.id),
		compositionMap(other.compositionMap), handlerRegistry(other.handlerRegistry) {
}

Reactant::~Reactant() {
}

std::shared_ptr<Reactant> Reactant::clone() {
	std::shared_ptr<Reactant> reactant(new Reactant(*this));
	return reactant;
}

Reactant::Reactant(double conc, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		concentration(conc), name(""), id(0), handlerRegistry(registry) {
}

double Reactant::getConcentration() const {
	return concentration;
}

void Reactant::increaseConcentration(double deltaConc) {
	concentration += deltaConc;
	std::cout << "Conc = " << concentration << ", delta = " << deltaConc << std::endl;
	return;
}

void Reactant::decreaseConcentration(double deltaConc) {
	concentration -= deltaConc;
	return;
}

void Reactant::setConcentration(double conc) {
	concentration = std::max(conc, 0.);
	return;
}

void Reactant::zero() {
	concentration = 0.0e-16;
	return;
}

double Reactant::getTotalFlux(const double temperature) {
	return 0.0;
}

void Reactant::setReactionNetwork(
	std::shared_ptr<ReactionNetwork> reactionNetwork) {
	
	network = reactionNetwork;
}


std::vector<int> Reactant::getConnectivity() const {
	// The connectivity array by default is filled with
	// zeroes.
	int connectivityLength = network->size();
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);

	return connectivity;
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
std::vector<double> Reactant::getPartialDerivatives(double temperature) const {
	// The partial derivatives array by default is filled with
	// zeroes.
	int length = network->size();
	std::vector<double> partial_derivatives = std::vector<double>(length, 0.0);

	return partial_derivatives;
}

/**
 * This operation returns the name of the reactant.
 * @return the name
 */
const std::string Reactant::getName() const {
	return name;
}

const std::string Reactant::toString() {
	throw std::string("Reactant::toString() is unimplemented");
}

const std::map<std::string, int> & Reactant::getComposition() const {
	// Return the composition map
	return compositionMap;
}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
