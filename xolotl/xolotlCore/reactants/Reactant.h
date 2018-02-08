#ifndef REACTANT_H
#define REACTANT_H

// Includes
<<<<<<< HEAD
#include "IReactant.h"
#include <math.h>
#include <sstream>
#include <set>
=======
#include <math.h>
#include <sstream>
#include <set>
#include "IReactant.h"
#include "IReactionNetwork.h"
#include "ProductionReaction.h"
#include "DissociationReaction.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlPerf {
class IHandlerRegistry;
class IEventCounter;
}

<<<<<<< HEAD
=======
// We use std::unordered_map for quick lookup of info about
// reactions we participate in.
// The C++ standard library defines a std::hash for keys
// that are a single pointer, but not for pairs of pointers,
// so we define our own here.  To improve readability,
// we define a concise name for type of a pair of IReactant pointers
// that we use as keys.
// TODO should this be moved "upward," e.g., into IReactant.h?
namespace xolotlCore {
using ReactantAddrPair = std::pair<IReactant*, IReactant*>;
} // namespace xolotlCore

namespace std {

template<>
struct hash<xolotlCore::ReactantAddrPair> {
	size_t operator()(const xolotlCore::ReactantAddrPair& pr) const {
		// Idea for implementation taken from
		// https://www.sultanik.com/blog/HashingPointers.
		auto sum = reinterpret_cast<uintptr_t>(pr.first)
				+ reinterpret_cast<uintptr_t>(pr.second);
		// Ensure result will fit in size_t
#if SIZE_MAX < UINTPTR_MAX
		sum %= SIZE_MAX;
#endif // SIZE_MAX < UINTPTR_MAX
		return sum;
	}
};

} // namespace std

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
namespace xolotlCore {

/**
 * A reactant is a general reacting body in a reaction network. It represents
 * any body whose population can change with time due to reactions of any type.
 *
 * Reactants inherently know the other reactants with which they interact. They
 * declare their interactions with other reactants in the network after it is
<<<<<<< HEAD
 * set (setReactionNetwork) via the getConnectivity() operation. "Connectivity"
=======
 * set (updateFromNetwork) via the getConnectivity() operation. "Connectivity"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
 * indicates whether two Reacants interact, via any mechanism, in an abstract
 * sense (as if they were nodes connected by an edge on a network graph).
 *
 * This is an abstract base class that only provides direct support for
 * manipulating the concentration, etc. It should be subclassed to add
 * functionality for calculate fluxes and computing connectivity.
 */
class Reactant: public IReactant {

<<<<<<< HEAD
private:
	/**
	 * A string description of our type/composition map that can
	 * be used for quick comparisons.
	 * Computed on demand by getCompositionString() and cached.
	 * Note: must be kept consistent with contents of compositionMap.
	 */
	mutable std::string compString;

=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
protected:

	/**
	 * The total concentration of this reactant.
	 */
	double concentration;

	/**
	 * The name of this reactant.
	 */
	std::string name;

	/**
	 * The type name of the reactant.
	 */
<<<<<<< HEAD
	std::string typeName;
=======
	ReactantType type;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * An integer identification number for this reactant.
	 */
	int id;

	/**
	 * An integer identification number for the xenon momentum.
	 */
	int xeMomId;

	/**
	 * An integer identification number for the helium momentum.
	 */
	int heMomId;

	/**
	 * An integer identification number for the vacancy momentum.
	 */
	int vMomId;

	/**
	 * The temperature at which the cluster currently exists. The diffusion
	 * coefficient is recomputed each time the temperature is changed.
	 */
	double temperature;

	/**
	 * The reaction network that includes this reactant.
	 */
<<<<<<< HEAD
	std::shared_ptr<IReactionNetwork> network;
=======
	IReactionNetwork& network;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The map that contains the composition of this cluster.
	 */
<<<<<<< HEAD
	std::map<std::string, int> compositionMap;
=======
	IReactant::Composition composition;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The performance handler registry that will be used with
	 * this class.
	 */
	std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;

	/**
	 * The total size of this cluster including the contributions from all
	 * species.
	 */
<<<<<<< HEAD
	int size;
=======
	IReactant::SizeType size;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The diffusion factor, D_0, that is used to calculate the diffusion
	 * coefficient for this cluster. The default value is 0 (does not diffuse).
	 */
	double diffusionFactor;

	/**
	 * The diffusion coefficient computed from the diffusion factor using an
	 * Arrhenius rate equation. It is re-computed every time the temperature is
	 * updated.
	 */
	double diffusionCoefficient;

	/**
	 * The formation energy of this cluster. It will be used to compute the
	 * binding energies appearing in the dissociation constant calculation.
	 */
	double formationEnergy;

	/**
	 * The migration energy for this cluster.
	 */
	double migrationEnergy;

	/**
	 * The reaction radius of this cluster
	 */
	double reactionRadius;

	/**
	 * The row of the reaction connectivity matrix corresponding to
	 * this Reactant stored as a set.
	 *
	 * If a cluster is involved in a reaction with this Reactant,
	 * the cluster id is an element of this set.
	 */
	std::set<int> reactionConnectivitySet;

	/**
	 * The row of the dissociation connectivity matrix corresponding to
	 * this Reactant stored as a set.
	 *
	 * If this Reactant can dissociate into a particular cluster,
	 * the cluster id is an element of this set.
	 */
	std::set<int> dissociationConnectivitySet;

	/**
	 * This operation recomputes the diffusion coefficient. It is called
	 * whenever the diffusion factor, migration energy or temperature change.
	 *
	 * @param temp the temperature
	 */
	void recomputeDiffusionCoefficient(double temp);

<<<<<<< HEAD
	/**
	 * The constructor.
	 */
	Reactant();

public:
=======
public:

	/**
	 * Default constructor, deleted because we require info to construct.
	 */
	Reactant() = delete;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The constructor.
	 *
<<<<<<< HEAD
	 * @param registry The performance handler registry to use
	 */
	Reactant(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The copy constructor. All reactants MUST be deep copied.
	 *
	 * @param other The reactant to copy
	 */
	Reactant(Reactant &other);
=======
	 * @param _network The network we will belong to.
	 * @param _name Our human-readable name.
	 * @param _registry The performance handler registry to use
	 */
	Reactant(IReactionNetwork& _network,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> _registry,
			const std::string& _name = "Reactant");

	/**
	 * Copy constructor.
	 * Only used to construct dummy cluster objects of Reactant type
	 * as a copy of the Reactant part of objects of a more derived type.
	 * The more derived types initialize their base class' data, and
	 * we don't have a ctor that lets them specify all of our data,
	 * so we use this ctor to copy the Reactant data.
	 *
	 * @param other The reactant to copy
	 */
	Reactant(Reactant &other) :
			concentration(other.concentration), name(other.name), type(
					other.type), id(other.id), xeMomId(other.xeMomId), heMomId(
					other.heMomId), vMomId(other.vMomId), temperature(
					other.temperature), network(other.network), handlerRegistry(
					other.handlerRegistry), size(other.size), composition(
					other.composition), formationEnergy(other.formationEnergy), diffusionFactor(
					other.diffusionFactor), diffusionCoefficient(
					other.diffusionCoefficient), migrationEnergy(
					other.migrationEnergy), reactionRadius(
					other.reactionRadius), reactionConnectivitySet(
					other.reactionConnectivitySet), dissociationConnectivitySet(
					other.dissociationConnectivitySet) {
		return;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The destructor
	 */
	virtual ~Reactant() {
	}

	/**
<<<<<<< HEAD
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant>(new Reactant(*this));
	}

	/**
	 * Create a production pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	virtual void createProduction(
			std::shared_ptr<ProductionReaction> reaction) {
=======
	 * Note that we result from the given reaction.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 * @param c Number that can be used by daughter classes.
	 * @param d Number that can be used by daughter classes.
	 */
	virtual void resultFrom(ProductionReaction& reaction, int a = 0, int b = 0,
			int c = 0, int d = 0) override {
		return;
	}

	/**
	 * Note that we result from the given reaction involving a super cluster.
	 * Assumes the reaction is already in the network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param prInfos Production reaction parameters used by derived classes.
	 */
	virtual void resultFrom(ProductionReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos)
					override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
		return;
	}

	/**
	 * Note that we result from the given reaction involving a super cluster.
	 * Assumes the reaction is already in the network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param product The cluster created by the reaction.
	 */
	virtual void resultFrom(ProductionReaction& reaction, IReactant& product)
			override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
		return;
	}

	/**
	 * Note that we combine with another cluster in a production reaction.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 */
	virtual void participateIn(ProductionReaction& reaction, int a = 0, int b =
			0) override {
		return;
	}

	/**
	 * Note that we combine with another cluster in a production reaction
	 * involving a super cluster.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param prInfos Production reaction parameters.
	 */
	virtual void participateIn(ProductionReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos)
					override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	/**
<<<<<<< HEAD
	 * Create a combination associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 */
	virtual void createCombination(
			std::shared_ptr<ProductionReaction> reaction) {
=======
	 * Note that we combine with another cluster in a production reaction
	 * involving a super cluster.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param product The cluster created by the reaction.
	 */
	virtual void participateIn(ProductionReaction& reaction, IReactant& product)
			override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	/**
<<<<<<< HEAD
	 * Create a dissociation pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	virtual void createDissociation(
			std::shared_ptr<DissociationReaction> reaction) {
=======
	 * Note that we combine with another cluster in a dissociation reaction.
	 * Assumes the reaction is already inour network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 * @param c Number that can be used by daughter classes.
	 * @param d Number that can be used by daughter classes.
	 */
	virtual void participateIn(DissociationReaction& reaction, int a = 0,
			int b = 0, int c = 0, int d = 0) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	/**
<<<<<<< HEAD
	 * Create an emission pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster emits.
	 */
	virtual void createEmission(
			std::shared_ptr<DissociationReaction> reaction) {
=======
	 * Note that we combine with another cluster in a dissociation reaction
	 * involving a super cluster.
	 * Assumes the reaction is already inour network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param prInfos Production reaction parameters.
	 */
	virtual void participateIn(DissociationReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos)
					override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
		return;
	}

	/**
	 * Note that we combine with another cluster in a dissociation reaction
	 * involving a super cluster.
	 * Assumes the reaction is already inour network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param disso The dissociating cluster.
	 */
	virtual void participateIn(DissociationReaction& reaction, IReactant& disso)
			override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
		return;
	}

	/**
	 * Note that we emit from the given reaction.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster emits.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 * @param c Number that can be used by daughter classes.
	 * @param d Number that can be used by daughter classes.
	 */
	virtual void emitFrom(DissociationReaction& reaction, int a = 0, int b = 0,
			int c = 0, int d = 0) override {
		return;
	}

	/**
	 * Note that we emit from the given reaction involving a super cluster.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster emits.
	 * @param prInfos Production reaction parameters.
	 */
	virtual void emitFrom(DissociationReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos)
					override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
		return;
	}

	/**
	 * Note that we emit from the given reaction involving a super cluster.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster emits.
	 * @param disso The dissociating cluster.
	 */
	virtual void emitFrom(DissociationReaction& reaction, IReactant& disso)
			override {
		// Must be defined because we use stock Reactants with dummy
		// Reactions, so we need to be able to create Reactant objects.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	/**
	 * Add the reactions to the network lists.
	 */
<<<<<<< HEAD
	virtual void optimizeReactions() {
=======
	virtual void optimizeReactions() override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	/**
	 * This operation returns the current concentration.
	 *
	 * @param distA The first distance for super clusters
	 * @param distB The second distance for super clusters
	 * @return The concentration of this reactant
	 */
	virtual double getConcentration(double distA = 0.0,
<<<<<<< HEAD
			double distB = 0.0) const {
=======
			double distB = 0.0) const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		return concentration;
	}

	/**
	 * This operation sets the concentration of the reactant to the
	 * specified amount.
	 *
	 * @param conc The new concentation
	 */
<<<<<<< HEAD
	void setConcentration(double conc) {
=======
	void setConcentration(double conc) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		concentration = conc;
	}

	/**
	 * This operation returns the total flux of this reactant in the
	 * current network.
	 *
	 * @return The total change in flux for this reactant due to all
	 * reactions
	 */
<<<<<<< HEAD
	virtual double getTotalFlux() {
=======
	virtual double getTotalFlux() override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return 0.0;
	}

	/**
<<<<<<< HEAD
	 * This operation sets the collection of other reactants that make up
	 * the reaction network in which this reactant exists.
	 *
	 * @param network The reaction network of which this reactant is a part
	 */
	virtual void setReactionNetwork(
			std::shared_ptr<IReactionNetwork> reactionNetwork) {
		network = reactionNetwork;
	}

	/**
	 * Release the reaction network object.
	 *
	 * This should only be done when the reaction network is no longer needed
	 * by the program, and is done to break dependence cycles that would
	 * otherwise keep the network and reactant objects from being destroyed.
	 */
	void releaseReactionNetwork() {
		network.reset();
=======
	 * Update reactant using other reactants in its network.
	 */
	virtual void updateFromNetwork() override {
		// Nothing to do - derived classes do any meaningful work.
		// Required to be defined because we create explicit Reactant objects,
		// e.g. as dummy objects.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * This operation signifies that the reactant with reactant Id should be
	 * listed as connected with this reactant through forward reactions.
	 *
	 * @param id The integer id of the reactant that is connected
	 * to this reactant
	 */
<<<<<<< HEAD
	void setReactionConnectivity(int id) {
=======
	void setReactionConnectivity(int id) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		reactionConnectivitySet.insert(id);
	}

	/**
	 * This operation signifies that the reactant with reactant Id should be
	 * listed as connected with this reactant through forward reactions.
	 *
	 * @param id The integer id of the reactant that is connected
	 * to this reactant
	 */
<<<<<<< HEAD
	void setDissociationConnectivity(int id) {
=======
	void setDissociationConnectivity(int id) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		dissociationConnectivitySet.insert(id);
	}

	/**
	 * This operation reset the connectivity sets based on the information
	 * in the effective production and dissociation vectors.
	 */
<<<<<<< HEAD
	virtual void resetConnectivities() {
=======
	virtual void resetConnectivities() override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	/**
	 * This operation returns a list that represents the connectivity
	 * between this reactant and other reactants in the network.
	 * "Connectivity" indicates whether two reactants interact, via any
	 * mechanism, in an abstract sense (as if they were nodes connected by
	 * an edge on a network graph).
	 *
	 * @return An array of ones and zeros that indicate whether or not this
	 * reactant interacts via any mechanism with another reactant. A "1" at
	 * the i-th entry in this array indicates that the reactant interacts
	 * with the i-th reactant in the ReactionNetwork and a "0" indicates
	 * that it does not.
	 */
<<<<<<< HEAD
	virtual std::vector<int> getConnectivity() const;
=======
	virtual std::vector<int> getConnectivity() const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the list of partial derivatives of this reactant
	 * with respect to all other reactants in the network. The combined lists
	 * of partial derivatives from all of the reactants in the network can be
	 * used to form, for example, a Jacobian.
	 *
	 * @return the partial derivatives for this reactant where index zero
	 * corresponds to the first reactant in the list returned by the
	 * ReactionNetwork::getAll() operation.
	 */
<<<<<<< HEAD
	virtual std::vector<double> getPartialDerivatives() const {
		return std::vector<double>(network->getDOF(), 0.0);
=======
	virtual std::vector<double> getPartialDerivatives() const override {
		return std::vector<double>(network.getDOF(), 0.0);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * This operation works as getPartialDerivatives above, but instead of
	 * returning a vector that it creates it fills a vector that is passed to
	 * it by the caller. This allows the caller to optimize the amount of
	 * memory allocations to just one if they are accessing the partial
	 * derivatives many times.
	 *
	 * The base class (Reactant) implementation does nothing.
	 *
	 * @param partials The vector that should be filled with the partial derivatives
	 * for this reactant where index zero corresponds to the first reactant in
	 * the list returned by the ReactionNetwork::getAll() operation. The size of
	 * the vector should be equal to ReactionNetwork::size().
	 */
<<<<<<< HEAD
	virtual void getPartialDerivatives(std::vector<double> & partials) const {
=======
	virtual void getPartialDerivatives(std::vector<double> & partials) const
			override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// nothing to do.
	}

	/**
	 * This operation returns the name of the reactant.
	 *
	 * @return The name
	 */
<<<<<<< HEAD
	const std::string getName() const {
=======
	const std::string getName() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return name;
	}

	/**
	 * This operation returns the reactant's type. It is up to subclasses to
	 * define exactly what the allowed types may be.
	 *
<<<<<<< HEAD
	 * @return The type of this reactant as a string
	 */
	std::string getType() const {
		return typeName;
=======
	 * @return The type of this reactant.
	 */
	ReactantType getType() const override {
		return type;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * This operation returns the composition of this reactant. This map is empty
	 * when returned by the base class.
	 *
	 * @return The composition returned as a map with keys naming distinct
	 * elements and values indicating the amount of the element present.
	 */
<<<<<<< HEAD
	virtual const std::map<std::string, int> & getComposition() const {
		return compositionMap;
	}

	/**
	 * Get a string containing the canonical representation of the
	 * composition of this reactant.  The string is not intended to
	 * be human-readable, but rather is useful for keys in reactant maps
	 * and for composition match tests (as opposed to comparisons of
	 * the composition maps themselves).
	 *
	 * @return A string containing the canonical representation of our
	 * composition.
	 */
	virtual std::string getCompositionString() const {
		if (compString.empty()) {
			compString = toCanonicalString(getType(), compositionMap);
		}
		return compString;
=======
	virtual const IReactant::Composition & getComposition() const override {
		return composition;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * This operation sets the id of the reactant, The id is zero by default
	 * and clients, most likely the ReactionNetwork, are expected to set the
	 * id as needed.
	 *
	 * @param nId The new id for this reactant
	 */
<<<<<<< HEAD
	void setId(int nId) {
=======
	void setId(int nId) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		id = nId;
	}

	/**
	 * This operation returns the id for this reactant.
	 *
	 * @return The id
	 */
<<<<<<< HEAD
	int getId() const {
=======
	int getId() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return id;
	}

	/**
	 * This operation sets the id of the xenon momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
<<<<<<< HEAD
	void setXeMomentumId(int nId) {
=======
	void setXeMomentumId(int nId) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		xeMomId = nId;
	}

	/**
	 * This operation returns the id for this reactant xenon momentum.
	 *
	 * @return The id
	 */
<<<<<<< HEAD
	int getXeMomentumId() const {
=======
	int getXeMomentumId() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return xeMomId;
	}

	/**
	 * This operation sets the id of the helium momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
<<<<<<< HEAD
	void setHeMomentumId(int nId) {
=======
	void setHeMomentumId(int nId) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		heMomId = nId;
	}

	/**
	 * This operation returns the id for this reactant helium momentum.
	 *
	 * @return The id
	 */
<<<<<<< HEAD
	int getHeMomentumId() const {
=======
	int getHeMomentumId() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return heMomId;
	}

	/**
	 * This operation sets the id of the vacancy momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
<<<<<<< HEAD
	void setVMomentumId(int nId) {
=======
	void setVMomentumId(int nId) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		vMomId = nId;
	}

	/**
	 * This operation returns the id for this reactant vacancy momentum.
	 *
	 * @return The id
	 */
<<<<<<< HEAD
	int getVMomentumId() const {
=======
	int getVMomentumId() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return vMomId;
	}

	/**
	 * This operation sets the temperature at which the reactant currently
	 * exists. Temperature-dependent quantities are recomputed when this
	 * operation is called, so the temperature should always be set first.
	 *
	 * The simplest way to set the temperature for all reactants is to call the
	 * ReactionNetwork::setTemperature() operation.
	 *
	 * The base class implementation only stores the temperature value.
	 * Subclasses are responsible for implementing their own update
	 * calculations and for calling setTemperature() in their copy constructors.
	 *
	 * @param temp The new cluster temperature
	 */
<<<<<<< HEAD
	void setTemperature(double temp);
=======
	void setTemperature(double temp) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the temperature at which the reactant currently exists.
	 *
	 * @return The temperature.
	 */
<<<<<<< HEAD
	double getTemperature() const {
=======
	double getTemperature() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return temperature;
	}

	/**
	 * This operation returns the total size of the reactant.
	 *
	 * @return The total size of this reactant including the contributions
	 * from all species types
	 */
<<<<<<< HEAD
	int getSize() const {
=======
	IReactant::SizeType getSize() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return size;
	}

	/**
	 * This operation retrieves the formation energy for this reactant.
	 *
	 * @return The value of the formation energy
	 */
<<<<<<< HEAD
	double getFormationEnergy() const {
=======
	double getFormationEnergy() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return formationEnergy;
	}

	/**
	 * This operation sets the formation energy for this reactant.
	 *
	 * @param energy The formation energy
	 */
<<<<<<< HEAD
	void setFormationEnergy(double energy) {
=======
	void setFormationEnergy(double energy) override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		formationEnergy = energy;
	}

	/**
	 * This operation retrieves the diffusion factor, D_0, that is used to
	 * calculate the diffusion coefficient for this reactant.
	 *
	 * @return The diffusion factor of this reactant
	 */
<<<<<<< HEAD
	double getDiffusionFactor() const {
=======
	double getDiffusionFactor() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return diffusionFactor;
	}

	/**
	 * This operation sets the diffusion factor, D_0, that is used to calculate
	 * the diffusion coefficient for this reactant.
	 *
	 * @param factor The diffusion factor
	 */
<<<<<<< HEAD
	virtual void setDiffusionFactor(const double factor);
=======
	virtual void setDiffusionFactor(const double factor) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the diffusion coefficient for this reactant and is
	 * calculated from the diffusion factor.
	 *
	 * @return The diffusion coefficient
	 */
<<<<<<< HEAD
	double getDiffusionCoefficient() const {
=======
	double getDiffusionCoefficient() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return diffusionCoefficient;
	}

	/**
	 * This operation sets the migration energy for this reactant.
	 *
	 * @param energy The migration energy
	 */
<<<<<<< HEAD
	virtual void setMigrationEnergy(const double energy);
=======
	virtual void setMigrationEnergy(const double energy) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation retrieves the migration energy for this reactant.
	 *
	 * @return the migration energy
	 */
<<<<<<< HEAD
	double getMigrationEnergy() const {
=======
	double getMigrationEnergy() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return migrationEnergy;
	}

	/**
	 * This operation returns the reaction radius for the
	 * particular reactant.
	 *
	 * @return The reaction radius
	 */
<<<<<<< HEAD
	double getReactionRadius() const {
=======
	double getReactionRadius() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return reactionRadius;
	}

	/**
	 * This operation returns the sum of combination rate and emission rate
	 * (where this reactant is on the left side of the reaction) for this
	 * particular reactant.
	 * This is used to computed the desorption rate in the
	 * modified trap-mutation handler.
	 *
	 * @return The rate
	 */
<<<<<<< HEAD
	virtual double getLeftSideRate() const {
=======
	virtual double getLeftSideRate() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return 0.0;
	}

	/**
	 * This operation returns true if the cluster is a mixed-species or compound
	 * cluster and false if it is a single species cluster.
	 */
<<<<<<< HEAD
	virtual bool isMixed() const {
=======
	virtual bool isMixed() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return false;
	}

	/**
<<<<<<< HEAD
	 * Get a string containing the canonical representation of the
	 * given composition.  The string is not intended to
	 * be human-readable, but rather is useful for keys in reactant maps
	 * and for composition match tests (as opposed to comparisons of
	 * the composition maps themselves).
	 *
	 * @param type The type that will be used with the given composition.
	 * @param composition A map containing the names and amounts of each
	 * part of the reactant.
	 * @return A string containing the canonical representation of our
	 * composition.
	 */
	static std::string toCanonicalString(std::string type,
			const std::map<std::string, int>& composition);

=======
	 * Tell reactant to output a representation of its reaction coefficients
	 * to the given output stream.
	 *
	 * @param os Output stream on which to output coefficients.
	 */
	// We must define this because the code may use a stock Reactant
	// when using dummy reactions, and thus we have to define all
	// pure virtual functions from our base class(es).
	virtual void outputCoefficientsTo(std::ostream& os) const override {
		// Nothing to do.
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
};

} // end namespace xolotlCore

#endif
