#ifndef IREACTIONNETWORK_H
#define IREACTIONNETWORK_H

<<<<<<< HEAD
#include "IReactant.h"
#include "ReactantUtils.h"
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <string>
#include <vector>
#include <map>
#include <memory>
<<<<<<< HEAD
=======
#include "IReactant.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlCore {

class IReactant;
<<<<<<< HEAD
=======
class ProductionReaction;
class DissociationReaction;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

/**
 *  This class manages the set of reactants and compound reactants
 *  (combinations of normal reactants). It also manages a set of properties
 *  that describe both.
 */
class IReactionNetwork {

public:
<<<<<<< HEAD
=======
	/**
	 * Nice name for vector of Reactants.
	 */
	using ReactantVector = std::vector<std::reference_wrapper<IReactant> >;

	/**
	 * Nice name for map of reactants, keyed by their composition.
	 */
	using ReactantMap = std::unordered_map<IReactant::Composition, std::unique_ptr<IReactant> >;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The destructor.
	 */
	virtual ~IReactionNetwork() {
	}

	/**
	 * This operation sets the temperature at which the reactants currently
	 * exists. It calls setTemperature() on each reactant.
	 *
	 * This is the simplest way to set the temperature for all reactants.
	 *
	 * @param temp The new temperature
	 */
	virtual void setTemperature(double temp) = 0;

	/**
	 * This operation returns the temperature at which the cluster currently exists.
	 *
	 * @return The temperature
	 */
	virtual double getTemperature() const = 0;

	/**
<<<<<<< HEAD
	 * This operation returns a reactant with the given type and size if it
	 * exists in the network or null if not.
	 *
	 * @param type The type of the reactant
	 * @param size The size of the reactant
	 * @return A pointer to the reactant
	 */
	virtual IReactant * get(const std::string& type, const int size) const = 0;

	/**
	 * This operation returns a compound reactant with the given type and size if it
	 * exists in the network or null if not.
	 *
	 * @param type The type of the compound reactant
	 * @param sizes An array containing the sizes of each piece of the reactant
	 * @return A pointer to the compound reactant
	 */
	virtual IReactant * getCompound(const std::string& type,
			const std::vector<int>& sizes) const = 0;
=======
	 * Retrieve the single-species reactant with the given type and size if it
	 * exists in the network or null if not.
	 * Convenience function for get() that takes a
	 * reactant type and composition.
	 *
	 * @param species The reactant's single species.
	 * @param size The size of the reactant.
	 * @return A pointer to the reactant, or nullptr if it does not 
	 * exist in the network.
	 */
	virtual IReactant * get(Species species,
			IReactant::SizeType size) const = 0;

	/**
	 * Retrieve the reactant with the given type and composition if
	 * exists in the network.
	 *
	 * @param type The type of the reactant
	 * @param comp The composition of the reactant
	 * @return A pointer to the reactant of type 'type' and with composition
	 * 'comp.' nullptr if no such reactant exists.
	 */
	virtual IReactant * get(ReactantType type,
			const IReactant::Composition& comp) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns all reactants in the network without regard for
	 * their composition or whether they are compound reactants. The list may
	 * or may not be ordered and the decision is left to implementers.
	 *
	 * @return The list of all of the reactants in the network
	 */
<<<<<<< HEAD
	virtual const std::shared_ptr<std::vector<IReactant *>> & getAll() const = 0;
=======
	virtual const IReactant::RefVector& getAll() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns all reactants in the network with the given type.
	 * The list may or may not be ordered and the decision is left to
	 * implementers.
	 *
	 * @param type The reactant or compound reactant type
<<<<<<< HEAD
	 * @return The list of all of the reactants in the network or null if the
	 * type is invalid
	 */
	virtual std::vector<IReactant *> getAll(const std::string& type) const = 0;

	/**
	 * This operation adds a reactant or a compound reactant to the network.
	 * Adding a reactant to the network does not set the network as the
	 * reaction network for the reactant. This step must be performed
	 * separately to allow for the scenario where the network is generated
	 * entirely before running.
	 *
	 * @param reactant The reactant that should be added to the network
	 */
	virtual void add(std::shared_ptr<IReactant> reactant) = 0;

	/**
	 * This operation adds a super reactant to the network.
	 * Used with a grouping method.
	 *
	 * @param reactant The reactant that should be added to the network
	 */
	virtual void addSuper(std::shared_ptr<IReactant> reactant) = 0;
=======
	 * @return The list of all of the reactants in the network.
	 */
	virtual const ReactantMap& getAll(ReactantType type) const = 0;

	/**
	 * Give the reactant to the network.
	 *
	 * @param reactant The reactant that should be added to the network
	 */
	virtual void add(std::unique_ptr<IReactant> reactant) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation removes a group of reactants from the network.
	 *
	 * @param reactants The reactants that should be removed.
	 */
<<<<<<< HEAD
	virtual void removeReactants(const std::vector<IReactant*>& reactants) = 0;
=======
	virtual void removeReactants(const ReactantVector& reactants) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation reinitializes the network.
	 *
	 * It computes the cluster Ids and network size from the allReactants vector.
	 */
	virtual void reinitializeNetwork() = 0;

	/**
	 * This method redefines the connectivities for each cluster in the
	 * allReactans vector.
	 */
	virtual void reinitializeConnectivities() = 0;

	/**
<<<<<<< HEAD
	 * This operation returns the names of the reactants in the network.
	 *
	 * @return A vector with one entry for each of the distinct reactant types
	 * in the network
	 */
	virtual const std::vector<std::string> & getNames() const = 0;

	/**
	 * This operation returns the names of the compound reactants in the
	 * network.
	 *
	 * @return A vector with one each for each of the distinct compound
	 * reactant types in the network
	 */
	virtual const std::vector<std::string> & getCompoundNames() const = 0;

	/**
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 * This operation returns the size or number of reactants in the network.
	 *
	 * @return The number of reactants in the network
	 */
<<<<<<< HEAD
	virtual int size() = 0;
=======
	virtual int size() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the size or number of reactants and momentums in the network.
	 *
	 * @return The number of degrees of freedom
	 */
<<<<<<< HEAD
	virtual int getDOF() = 0;

	/**
	 * This operation adds a production reaction to the network.
	 *
	 * @param reaction The reaction that should be added to the network
	 * @return The pointer to the reaction that is now in the network
	 */
	virtual std::shared_ptr<ProductionReaction> addProductionReaction(
			std::shared_ptr<ProductionReaction> reaction) = 0;

	/**
	 * This operation adds a dissociation reaction to the network.
	 *
	 * @param reaction The reaction that should be added to the network
	 * @return The pointer to the reaction that is now in the network
	 */
	virtual std::shared_ptr<DissociationReaction> addDissociationReaction(
			std::shared_ptr<DissociationReaction> reaction) = 0;
=======
	virtual int getDOF() const = 0;

	/**
	 * Add a production reaction to the network.
	 *
	 * @param reaction The reaction that should be added to the network
	 * @return The reaction that is now in the network
	 */
	virtual ProductionReaction& add(
			std::unique_ptr<ProductionReaction> reaction) = 0;

	/**
	 * Add a dissociation reaction to the network.
	 *
	 * @param reaction The reaction that should be added to the network
	 * @return The reaction that is now in the network
	 */
	virtual DissociationReaction& add(
			std::unique_ptr<DissociationReaction> reaction) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation fills an array of doubles with the concentrations of all
	 * of the reactants in the network.
	 *
	 * @param concentrations The array that will be filled with the
	 * concentrations. This operation does NOT create, destroy or resize the
	 * array. If the array is too small to hold the concentrations, SIGSEGV will
	 * be thrown.
	 */
	virtual void fillConcentrationsArray(double * concentrations) = 0;

	/**
	 * This operation updates the concentrations for all reactants in the
	 * network from an array.
	 *
	 * @param concentrations The array of doubles that will be for the
	 * concentrations. This operation does NOT create, destroy or resize the
	 * array. Properly aligning the array in memory so that this operation
	 * does not overrun is up to the caller.
	 */
	virtual void updateConcentrationsFromArray(double * concentrations) = 0;

	/**
<<<<<<< HEAD
	 * Request that all reactants in the network release their
	 * pointers to the network, to break cycles and allow the
	 * network and the clusters/reactant objects it contains to
	 * be destroyed gracefully.
	 *
	 * Should only be done when the network is no longer needed.
	 * Ideally, we would do this from the network's destructor.
	 * However, unless the reactants in the network release their
	 * shared_ptrs to the network, the reference count on the
	 * network's shared_ptr will never reach zero and the
	 * object it owns will never be destroyed.  (Hence, the
	 * reactant objects will also never be destroyed.)
	 */
	virtual void askReactantsToReleaseNetwork() = 0;

	/**
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 * Get the diagonal fill for the Jacobian, corresponding to the reactions.
	 *
	 * @param diagFill The pointer to the vector where the connectivity information is kept
	 */
	virtual void getDiagonalFill(int *diagFill) = 0;

	/**
	 * Get the total concentration of atoms in the network.
	 *
	 * @return The total concentration
	 */
	virtual double getTotalAtomConcentration() = 0;

	/**
	 * Get the total concentration of atoms contained in bubbles in the network.
	 *
	 * @return The total concentration
	 */
	virtual double getTotalTrappedAtomConcentration() = 0;

	/**
	 * Get the total concentration of vacancies in the network.
	 *
	 * @return The total concentration
	 */
	virtual double getTotalVConcentration() = 0;

	/**
	 * Get the total concentration of material interstitials in the network.
	 *
	 * @return The total concentration
	 */
	virtual double getTotalIConcentration() = 0;

	/**
	 * Calculate all the rate constants for the reactions and dissociations of the network.
	 * Need to be called only when the temperature changes.
	 */
	virtual void computeRateConstants() = 0;

	/**
	 * Compute the fluxes generated by all the reactions
	 * for all the clusters and their momentum.
	 *
	 * @param updatedConcOffset The pointer to the array of the concentration at the grid
	 * point where the fluxes are computed used to find the next solution
	 */
	virtual void computeAllFluxes(double *updatedConcOffset) = 0;

	/**
	 * Compute the partial derivatives generated by all the reactions
	 * for all the clusters and their momentum.
	 *
	 * @param vals The pointer to the array that will contain the values of
	 * partials for the reactions
	 * @param indices The pointer to the array that will contain the indices
	 * of the clusters for the partial derivatives
	 * @param size The pointer to the array that will contain the number of reactions for
	 * this cluster
	 */
	virtual void computeAllPartials(double *vals, int *indices, int *size) = 0;

	/**
	 * This operation returns the biggest production rate in the network.
	 *
	 * @return The biggest rate
	 */
	virtual double getBiggestRate() const = 0;

	/**
	 * Are dissociations enabled?
	 *
	 * @returns true if reactions are enabled, false otherwise.
	 */
	virtual bool getDissociationsEnabled() const = 0;

<<<<<<< HEAD
=======
	/**
	 * Find maximum cluster size currently in the network
	 * for the given reactant type.
	 *
	 * @param rtype Reactant type of interest.
	 * @return Maximum size of cluster of type rtype currently in network.
	 */
	virtual IReactant::SizeType getMaxClusterSize(ReactantType rtype) const = 0;

	/**
	 * Dump a representation of the network to the given output stream.
	 *
	 * @param os Output stream on which to write network description.
	 */
	virtual void dumpTo(std::ostream& os) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
};

}

#endif
