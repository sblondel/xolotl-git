// Includes
#include "Reactant.h"
#include "ReactionNetwork.h"
#include <xolotlPerf.h>
#include <iostream>
#include <math.h>
#include <MathUtils.h>
#include <Constants.h>

<<<<<<< HEAD
// Namespaces
using namespace xolotlCore;

Reactant::Reactant() :
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
<<<<<<< HEAD
=======
	compositionMap[dType] = 0;
	compositionMap[tType] = 0;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
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
<<<<<<< HEAD
=======
	compositionMap[dType] = 0;
	compositionMap[tType] = 0;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
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
<<<<<<< HEAD
<<<<<<< HEAD
=======
	compositionMap[dType] = other.compositionMap[dType];
	compositionMap[tType] = other.compositionMap[tType];
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
=======
namespace xolotlCore {

// TODO modify signature to take type as argument.
Reactant::Reactant(IReactionNetwork& _network,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry,
		const std::string& _name) :
		concentration(0.0), id(0), xeMomId(0), heMomId(0), vMomId(0), temperature(
				0.0), type(ReactantType::Invalid), network(_network), handlerRegistry(
				registry), size(0), formationEnergy(0.0), diffusionFactor(0.0), diffusionCoefficient(
				0.0), migrationEnergy(0.0), name(_name), reactionRadius(0.0) {

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
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

<<<<<<< HEAD
<<<<<<< HEAD
double Reactant::getConcentration(double distA, double distB) const {
	return concentration;
}

void Reactant::setConcentration(double conc) {
	concentration = conc;

	return;
}

double Reactant::getTotalFlux() {
	return 0.0;
}

void Reactant::setReactionNetwork(
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

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
std::vector<int> Reactant::getConnectivity() const {
	// The connectivity array by default is filled with
	// zeros.
<<<<<<< HEAD
	int connectivityLength = network->getDOF();
=======
	int connectivityLength = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	std::vector<int> connectivity = std::vector<int>(connectivityLength, 0);

	// This reactant should be connected to itself
	connectivity[id - 1] = 1;

	return connectivity;
}

<<<<<<< HEAD
<<<<<<< HEAD
std::vector<double> Reactant::getPartialDerivatives() const {
	// The partial derivatives array by default is filled with
	// zeros.
	int length = network->getDOF();
	std::vector<double> partial_derivatives = std::vector<double>(length, 0.0);

	return partial_derivatives;
}

void Reactant::getPartialDerivatives(std::vector<double> &) const {
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

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
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

<<<<<<< HEAD
<<<<<<< HEAD

std::string Reactant::getCompositionString() const {

	// Return the canonical string representation of our composition.
    if(compString.empty()) {

        // We have not found our descriptive string yet.
        // So determine it and cache it.
        compString = toCanonicalString(getType(), compositionMap);
    }
    return compString;
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

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
void Reactant::setTemperature(double temp) {
	temperature = temp;

	// Recompute the diffusion coefficient
	recomputeDiffusionCoefficient(temp);
}

<<<<<<< HEAD
<<<<<<< HEAD
double Reactant::getTemperature() const {
	return temperature;
}
=======
>>>>>>> master


=======
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
void Reactant::setDiffusionFactor(const double factor) {
	// Set the diffusion factor
	diffusionFactor = factor;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
double Reactant::getDiffusionCoefficient() const {
	return diffusionCoefficient;
}

double Reactant::getMigrationEnergy() const {
	// Return the migration energy
	return migrationEnergy;
}

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
void Reactant::setMigrationEnergy(const double energy) {
	// Set the migration energy
	migrationEnergy = energy;
	// Update the diffusion coefficient
	recomputeDiffusionCoefficient(temperature);

	return;
}
<<<<<<< HEAD

<<<<<<< HEAD
=======
std::ostream&
operator<<(std::ostream& os, const IReactant::Composition& comp) {
	std::vector<Species> compSpecies { Species::He, Species::I, Species::V,
			Species::Xe };
	for (auto const& currSpecies : compSpecies) {
		os << toString(currSpecies) << comp[toCompIdx(currSpecies)];
	}
	return os;
}

std::ostream&
operator<<(std::ostream& os, const IReactant& reactant) {
	os << "id: " << reactant.getId() << "; " << "type: "
			<< toString(reactant.getType()) << "; "
#if defined(USE_ORIG_REACTANT_COMP_STRING)
			// Output a string in format used by previous implementations,
			// to support comparisons.
			<< "comp: " << getCompString(reactant);
#else
			<< "comp: " << reactant.getComposition();
#endif // defined(USE_ORIG_REACTANT_COMP_STRING)
	return os;
}
<<<<<<< HEAD
=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======

} // namespace xolotlCore

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
