// Includes
#include "Reactant.h"
#include "ReactionNetwork.h"
#include <xolotlPerf.h>
#include <iostream>
<<<<<<< HEAD
=======
#include <math.h>
#include <MathUtils.h>
#include <Constants.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

// Namespaces
using namespace xolotlCore;

Reactant::Reactant() :
<<<<<<< HEAD
		concentration(0.0),
		name(""), id(0),
		temperature(0.0),
		network(nullptr),
		handlerRegistry(nullptr) {}

Reactant::Reactant(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		concentration(0.0),
		name(""),
		id(0),
		temperature(0.0),
		network(nullptr),
		handlerRegistry(registry) {}

Reactant::Reactant(const Reactant &other) :
		concentration(other.concentration),
		name(other.name),
		typeName(other.typeName),
		id(other.id),
		temperature(other.temperature),
		network(other.network),
		compositionMap(other.compositionMap),
		handlerRegistry(other.handlerRegistry) {}

std::shared_ptr<Reactant> Reactant::clone() {
	std::shared_ptr<Reactant> reactant(new Reactant(*this));
	return reactant;
}

Reactant::Reactant(double conc, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		concentration(conc),
		name(""),
		id(0),
		temperature(0.0),
		network(nullptr),
		handlerRegistry(registry) {}

double Reactant::getConcentration() const {
	return concentration;
}

void Reactant::increaseConcentration(double deltaConc) {
	concentration += deltaConc;

	return;
}

void Reactant::decreaseConcentration(double deltaConc) {
	concentration -= deltaConc;
=======
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void Reactant::setConcentration(double conc) {
	concentration = conc;

	return;
}

void Reactant::zero() {
	concentration = 0.0;
=======
double Reactant::getConcentration(double distA, double distB) const {
	return concentration;
}

void Reactant::setConcentration(double conc) {
	concentration = conc;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

double Reactant::getTotalFlux() {
	return 0.0;
}

void Reactant::setReactionNetwork(
<<<<<<< HEAD
	std::shared_ptr<ReactionNetwork> reactionNetwork) {
	network = reactionNetwork;
	
	return;
}

=======
		std::shared_ptr<IReactionNetwork> reactionNetwork) {
	network = reactionNetwork;

	return;
}

void Reactant::releaseReactionNetwork() {
	network.reset();

	return;
}

void Reactant::setReactionConnectivity(int id) {
	// Add the cluster to the set.
	reactionConnectivitySet.insert(id);

	return;
}

void Reactant::setDissociationConnectivity(int id) {
	// Add the cluster to the set.
	dissociationConnectivitySet.insert(id);

	return;
}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

std::vector<int> Reactant::getConnectivity() const {
	// The connectivity array by default is filled with
	// zeros.
<<<<<<< HEAD
	int connectivityLength = network->size();
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);

=======
	int connectivityLength = network->getDOF();
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);

	// This reactant should be connected to itself
	connectivity[id - 1] = 1;

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	return connectivity;
}

std::vector<double> Reactant::getPartialDerivatives() const {
	// The partial derivatives array by default is filled with
	// zeros.
<<<<<<< HEAD
	int length = network->size();
=======
	int length = network->getDOF();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	std::vector<double> partial_derivatives = std::vector<double>(length, 0.0);

	return partial_derivatives;
}

<<<<<<< HEAD
void Reactant::getPartialDerivatives(std::vector<double> & partials) const {
=======
void Reactant::getPartialDerivatives(std::vector<double> &) const {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Do nothing.
	return;
}

const std::string Reactant::getName() const {
	return name;
}

std::string Reactant::getType() const {
	return typeName;
}

const std::map<std::string, int> & Reactant::getComposition() const {
	// Return the composition map
	return compositionMap;
}

<<<<<<< HEAD
namespace xolotlCore {
std::ostream& operator<< (std::ostream& out, const Reactant& reactant) {
	// Output the name and Id of the reactant
	out << reactant.name << "  Reactant Id: " << reactant.id-1;

	return out;
}

};
=======
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

std::string Reactant::getCompositionString() const {

	// Return the canonical string representation of our composition.
	//
	// TODO Would it be better to cache the composition string as a member
	// variable?  It would require us to have control over the composition map,
	// so that no changes to it could be made without us knowing about it.
	// (I.e., need a protected function for derived classes to make changes,
	// and the map itself becomes private to us.)
	return toCanonicalString(getType(), compositionMap);
}

void Reactant::setId(int nId) {
	id = nId;

	return;
}

int Reactant::getId() const {
	return id;
}

void Reactant::setXeMomentumId(int nId) {
	xeMomId = nId;

	return;
}

int Reactant::getXeMomentumId() const {
	return xeMomId;
}

void Reactant::setHeMomentumId(int nId) {
	heMomId = nId;

	return;
}

int Reactant::getHeMomentumId() const {
	return heMomId;
}

void Reactant::setVMomentumId(int nId) {
	vMomId = nId;

	return;
}

int Reactant::getVMomentumId() const {
	return vMomId;
}

void Reactant::setTemperature(double temp) {
	temperature = temp;

	// Recompute the diffusion coefficient
	recomputeDiffusionCoefficient(temp);
}

double Reactant::getTemperature() const {
	return temperature;
}

int Reactant::getSize() const {
	// Return this cluster's size
	return size;
}

double Reactant::getFormationEnergy() const {
	return formationEnergy;
}

void Reactant::setFormationEnergy(double energy) {
	// Set the formation energy
	formationEnergy = energy;
	return;
}

double Reactant::getDiffusionFactor() const {
	// Return the diffusion factor
	return diffusionFactor;
}

void Reactant::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

double Reactant::getDiffusionCoefficient() const {
	return diffusionCoefficient;
}

double Reactant::getMigrationEnergy() const {
	// Return the migration energy
	return migrationEnergy;
}

void Reactant::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

double Reactant::getReactionRadius() const {
	return reactionRadius; // Computed by subclasses in constructors.
}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
