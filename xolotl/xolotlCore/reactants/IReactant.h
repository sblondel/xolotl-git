#ifndef IREACTANT_H
#define IREACTANT_H

// Includes
<<<<<<< HEAD
#include "IReactionNetwork.h"
#include "ReactantUtils.h"
#include <memory>
#include <vector>
#include <map>
=======
#include <memory>
#include <numeric>
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <sstream>
#include "Species.h"
#include "ReactantType.h"
#include "PendingProductionReactionInfo.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlCore {

class IReactionNetwork;
<<<<<<< HEAD
=======
class ProductionReaction;
class DissociationReaction;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
class IReactant {

public:
<<<<<<< HEAD
=======
	/**
	 * A nice name for type of variable holding amount of a species.
	 */
	using SizeType = uint32_t;

	/**
	 * Type of a reactant's composition.
	 * It is an array of values, one per known Species.
	 * The array values are ordered according to the integer values of
	 * the Species enums, so casting a Species value to an int can
	 * be used to index into the array to get the concentration of
	 * that Species.
	 */
	struct Composition: public std::array<SizeType,
			static_cast<int>(Species::last) + 1> {
		Composition() {
			// By default, initialize all species concentrations to 0.
			fill(0);
		}
	};

	/**
	 * Nice name for vector of IReactant references.
	 */
	using RefVector = std::vector<std::reference_wrapper<IReactant> >;
	using ConstRefVector = std::vector<std::reference_wrapper<const IReactant> >;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The destructor
	 */
	virtual ~IReactant() {
	}

	/**
<<<<<<< HEAD
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() = 0;

	/**
	 * Create a production pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	virtual void createProduction(std::shared_ptr<ProductionReaction> reaction) = 0;

	/**
	 * Create a combination associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 */
	virtual void createCombination(std::shared_ptr<ProductionReaction> reaction) = 0;

	/**
	 * Create a dissociation pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	virtual void createDissociation(std::shared_ptr<DissociationReaction> reaction) = 0;

	/**
	 * Create an emission pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster emits.
	 */
	virtual void createEmission(std::shared_ptr<DissociationReaction> reaction) = 0;
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
			int c = 0, int d = 0) = 0;

	/**
	 * Note that we result from the given reaction involving a super cluster.
	 * Assumes the reaction is already in the network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param prInfos Production reaction parameters used by derived classes.
	 */
	virtual void resultFrom(ProductionReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) = 0;

	/**
	 * Note that we result from the given reaction involving a super cluster.
	 * Assumes the reaction is already in the network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param product The cluster created by the reaction.
	 */
	virtual void resultFrom(ProductionReaction& reaction,
			IReactant& product) = 0;

	/**
	 * Note that we combine with another cluster in a production reaction.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 */
	virtual void participateIn(ProductionReaction& reaction, int a = 0, int b =
			0) = 0;

	/**
	 * Note that we combine with another cluster in a production reaction
	 * involving a super cluster.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param prInfos Production reaction parameters.
	 */
	virtual void participateIn(ProductionReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) = 0;

	/**
	 * Note that we combine with another cluster in a production reaction
	 * involving a super cluster.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param product The cluster created by the reaction.
	 */
	virtual void participateIn(ProductionReaction& reaction,
			IReactant& product) = 0;

	/**
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
			int b = 0, int c = 0, int d = 0) = 0;

	/**
	 * Note that we combine with another cluster in a dissociation reaction
	 * involving a super cluster.
	 * Assumes the reaction is already inour network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param prInfos Production reaction parameters.
	 */
	virtual void participateIn(DissociationReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) = 0;

	/**
	 * Note that we combine with another cluster in a dissociation reaction
	 * involving a super cluster.
	 * Assumes the reaction is already inour network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param disso The dissociating cluster.
	 */
	virtual void participateIn(DissociationReaction& reaction,
			IReactant& disso) = 0;

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
			int c = 0, int d = 0) = 0;

	/**
	 * Note that we emit from the given reaction involving a super cluster.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster emits.
	 * @param prInfos Production reaction parameters.
	 */
	virtual void emitFrom(DissociationReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) = 0;

	/**
	 * Note that we emit from the given reaction involving a super cluster.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster emits.
	 * @param disso The dissociating cluster.
	 */
	virtual void emitFrom(DissociationReaction& reaction, IReactant& disso) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Add the reactions to the network lists.
	 */
	virtual void optimizeReactions() = 0;

	/**
	 * This operation returns the current concentration.
	 *
	 * @param distA The first distance for super clusters
	 * @param distB The second distance for super clusters
	 * @return The concentration of this reactant
	 */
	virtual double getConcentration(double distA = 0.0,
			double distB = 0.0) const = 0;

	/**
	 * This operation sets the concentration of the reactant to the
	 * specified amount.
	 *
	 * @param conc The new concentation
	 */
	virtual void setConcentration(double conc) = 0;

	/**
	 * This operation returns the total flux of this reactant in the
	 * current network.
	 *
	 * @return The total change in flux for this reactant due to all
	 * reactions
	 */
	virtual double getTotalFlux() = 0;

	/**
<<<<<<< HEAD
	 * This operation sets the collection of other reactants that make up
	 * the reaction network in which this reactant exists.
	 *
	 * @param network The reaction network of which this reactant is a part
	 */
	virtual void setReactionNetwork(
			std::shared_ptr<IReactionNetwork> reactionNetwork) = 0;

	/**
	 * Release the reaction network object.
	 *
	 * This should only be done when the reaction network is no longer needed
	 * by the program, and is done to break dependence cycles that would
	 * otherwise keep the network and reactant objects from being destroyed.
	 */
	virtual void releaseReactionNetwork() = 0;
=======
	 * Update reactant using other reactants in its network.
	 */
	virtual void updateFromNetwork() = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation signifies that the reactant with reactant Id should be
	 * listed as connected with this reactant through forward reactions.
	 *
	 * @param id The integer id of the reactant that is connected
	 * to this reactant
	 */
	virtual void setReactionConnectivity(int id) = 0;

	/**
	 * This operation signifies that the reactant with reactant Id should be
	 * listed as connected with this reactant through forward reactions.
	 *
	 * @param id The integer id of the reactant that is connected
	 * to this reactant
	 */
	virtual void setDissociationConnectivity(int id) = 0;

	/**
	 * This operation reset the connectivity sets based on the information
	 * in the effective production and dissociation vectors.
	 */
	virtual void resetConnectivities() = 0;

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
	virtual std::vector<int> getConnectivity() const = 0;

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
	virtual std::vector<double> getPartialDerivatives() const = 0;

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
	virtual void getPartialDerivatives(
			std::vector<double> & partials) const = 0;

	/**
	 * This operation returns the name of the reactant.
	 *
	 * @return The name
	 */
	virtual const std::string getName() const = 0;

	/**
	 * This operation returns the reactant's type. It is up to subclasses to
	 * define exactly what the allowed types may be.
	 *
<<<<<<< HEAD
	 * @return The type of this reactant as a string
	 */
	virtual std::string getType() const = 0;
=======
	 * @return The type of this reactant.
	 */
	virtual ReactantType getType() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the composition of this reactant. This map is empty
	 * when returned by the base class.
	 *
	 * @return The composition returned as a map with keys naming distinct
	 * elements and values indicating the amount of the element present.
	 */
<<<<<<< HEAD
	virtual const std::map<std::string, int> & getComposition() const = 0;

	/**
	 * Get a string containing the canonical representation of the
	 * composition of this reactant.  The string is not intended to
	 * be human-readable, but rather is useful for keys in reactant maps
	 * and for composition match tests (as opposed to comparisons of
	 * the composition maps themselves).
	 * TODO is this the same information as our name?
	 *
	 * @return A string containing the canonical representation of our
	 * composition.
	 */
	virtual std::string getCompositionString() const = 0;
=======
	virtual const Composition & getComposition() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation sets the id of the reactant, The id is zero by default
	 * and clients, most likely the ReactionNetwork, are expected to set the
	 * id as needed.
	 *
	 * @param nId The new id for this reactant
	 */
	virtual void setId(int nId) = 0;

	/**
	 * This operation returns the id for this reactant.
	 *
	 * @return The id
	 */
	virtual int getId() const = 0;

	/**
	 * This operation sets the id of the xenon momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
	virtual void setXeMomentumId(int nId) = 0;

	/**
	 * This operation returns the id for this reactant xenon momentum.
	 *
	 * @return The id
	 */
	virtual int getXeMomentumId() const = 0;

	/**
	 * This operation sets the id of the helium momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
	virtual void setHeMomentumId(int nId) = 0;

	/**
	 * This operation returns the id for this reactant helium momentum.
	 *
	 * @return The id
	 */
	virtual int getHeMomentumId() const = 0;

	/**
	 * This operation sets the id of the vacancy momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
	virtual void setVMomentumId(int nId) = 0;

	/**
	 * This operation returns the id for this reactant vacancy momentum.
	 *
	 * @return The id
	 */
	virtual int getVMomentumId() const = 0;

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
	 * @param temp The new reactant temperature
	 */
	virtual void setTemperature(double temp) = 0;

	/**
	 * This operation returns the temperature at which the reactant currently exists.
	 *
	 * @return The temperature.
	 */
	virtual double getTemperature() const = 0;

	/**
	 * This operation returns the total size of the reactant.
	 *
	 * @return The total size of this reactant including the contributions
	 * from all species types
	 */
<<<<<<< HEAD
	virtual int getSize() const = 0;
=======
	virtual SizeType getSize() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation retrieves the formation energy for this reactant.
	 *
	 * @return The value of the formation energy
	 */
	virtual double getFormationEnergy() const = 0;

	/**
	 * This operation sets the formation energy for this reactant.
	 *
	 * @param energy The formation energy
	 */
	virtual void setFormationEnergy(double energy) = 0;

	/**
	 * This operation retrieves the diffusion factor, D_0, that is used to
	 * calculate the diffusion coefficient for this reactant.
	 *
	 * @return The diffusion factor of this reactant
	 */
	virtual double getDiffusionFactor() const = 0;

	/**
	 * This operation sets the diffusion factor, D_0, that is used to calculate
	 * the diffusion coefficient for this reactant.
	 *
	 * @param factor The diffusion factor
	 */
	virtual void setDiffusionFactor(const double factor) = 0;

	/**
	 * This operation returns the diffusion coefficient for this reactant and is
	 * calculated from the diffusion factor.
	 *
	 * @return The diffusion coefficient
	 */
	virtual double getDiffusionCoefficient() const = 0;

	/**
	 * This operation sets the migration energy for this reactant.
	 *
	 * @param energy The migration energy
	 */
	virtual void setMigrationEnergy(const double energy) = 0;

	/**
	 * This operation retrieves the migration energy for this reactant.
	 *
	 * @return the migration energy
	 */
	virtual double getMigrationEnergy() const = 0;

	/**
	 * This operation returns the reaction radius for the
	 * particular reactant.
	 *
	 * @return The reaction radius
	 */
	virtual double getReactionRadius() const = 0;

	/**
	 * This operation returns the sum of combination rate and emission rate
	 * (where this reactant is on the left side of the reaction) for this
	 * particular reactant.
	 * This is used to computed the desorption rate in the
	 * modified trap-mutation handler.
	 *
	 * @return The rate
	 */
	virtual double getLeftSideRate() const = 0;

	/**
	 * This operation returns true if the cluster is a mixed-species or compound
	 * cluster and false if it is a single species cluster.
	 */
	virtual bool isMixed() const = 0;

<<<<<<< HEAD
};

} // end namespace xolotlCore
=======
	/**
	 * Tell reactant to output a representation of its reaction coefficients
	 * to the given output stream.
	 *
	 * @param os Output stream on which to output coefficients.
	 */
	virtual void outputCoefficientsTo(std::ostream& os) const = 0;
};

/**
 * Output basic description of an IReactant's composition to the given output
 * stream.
 *
 * @param os Output stream on which to write description.
 * @param comp Composition to describe.
 * @return Output stream after having written description.
 */
std::ostream& operator<<(std::ostream& os, const IReactant::Composition& comp);

/**
 * Output basic description of an IReactant to the given output stream.
 *
 * @param os Output stream on which to write description.
 * @param r Reactant to describe.
 * @return Output stream after having written description.
 */
std::ostream& operator<<(std::ostream& os, const IReactant& r);

}
 // end namespace xolotlCore

// For an IReactant::Composition to be used as a key in an std::unordered_map,
// we need to define a hash function for it.
// Since std::unordered_map uses std::hash on its keys, and because
// ours is a user-defined type, we add our hash function to the std namespace.
namespace std {

template<>
struct hash<xolotlCore::IReactant::Composition> {

size_t operator()(const xolotlCore::IReactant::Composition& comp) const {
	// This may not be a good hash function - needs to be evaluated
	// for the compositions Xolotl uses.
	return std::accumulate(comp.begin(), comp.end(), 0);
}
};
}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

#endif
