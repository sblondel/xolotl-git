#ifndef REACTANT_H
#define REACTANT_H

// Includes
<<<<<<< HEAD
<<<<<<< HEAD
#include "IReactant.h"
#include <math.h>
#include <sstream>
#include <set>

namespace xolotlPerf {
class IHandlerRegistry;
class IEventCounter;
}
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "ReactionNetwork.h"

namespace xolotlPerf {
	class IHandlerRegistry;
    class IEventCounter;
};
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

namespace xolotlCore {

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * A reactant is a general reacting body in a reaction network. It represents
 * any body whose population can change with time due to reactions of any type.
 *
 * Reactants inherently know the other reactants with which they interact. They
 * declare their interactions with other reactants in the network after it is
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
 * A Reactant is a general reacting body in a reaction network. It represents
 * any body whose population can change with time due to reactions of any type.
 *
 * Reactants inherently know the other Reactants with which they interact. They
 * declare their interactions with other Reactants in the network after it is
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
 * set (setReactionNetwork) via the getConnectivity() operation. "Connectivity"
 * indicates whether two Reacants interact, via any mechanism, in an abstract
 * sense (as if they were nodes connected by an edge on a network graph).
 *
 * This is an abstract base class that only provides direct support for
<<<<<<< HEAD
<<<<<<< HEAD
 * manipulating the concentration, etc. It should be subclassed to add
 * functionality for calculate fluxes and computing connectivity.
 */
class Reactant: public IReactant {

private:
    /**
     * A string description of our type/composition map that can
     * be used for quick comparisons.
     * Computed on demand by getCompositionString() and cached.
     * Note: must be kept consistent with contents of compositionMap.
     */
    mutable std::string compString;

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
	std::string typeName;

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
	std::shared_ptr<IReactionNetwork> network;

	/**
	 * The map that contains the composition of this cluster.
	 */
	std::map<std::string, int> compositionMap;

	/**
	 * The performance handler registry that will be used with
	 * this class.
	 */
	std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;

	/**
	 * The total size of this cluster including the contributions from all
	 * species.
	 */
	int size;

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

    
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
 * manipulate the concentration, etc. It should be subclassed to add
 * functionality for calculate fluxes and computing connectivity.
 */
class Reactant {

protected:

	/** The total concentration of this Reactant.
	 */
	double concentration;

	/** The name of this Reactant.
	 */
	std::string name;

	/**
	 * The type name of the reactant.
	 */
	std::string typeName;

	/** An integer identification number for this reactant.
	 */
	int id;

	/**
	 * The temperature t which the cluster currently exists. The diffusion
	 * coefficient is recomputed each time the temperature is changed.
	 */
	double temperature;

	/** The reaction network that includes this reactant.
	 */
	std::shared_ptr<ReactionNetwork> network;

	/**
	 * The map that contains the composition of this cluster
	 */
	std::map<std::string,int> compositionMap;

    /**
     * The performance handler registry that will be used with
     * this class.
     */
    std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;

<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	/**
	 * The constructor.
	 */
	Reactant();

public:

	/**
	 * The constructor.
	 *
<<<<<<< HEAD
<<<<<<< HEAD
	 * @param registry The performance handler registry to use
=======
	 * @param registry  The performance handler registry to use
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	 * @param registry  The performance handler registry to use
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 */
	Reactant(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The copy constructor. All reactants MUST be deep copied.
<<<<<<< HEAD
<<<<<<< HEAD
	 *
	 * @param other The reactant to copy
	 */
	Reactant(Reactant &other);
=======
	 * @param other The reactant to copy
	 */
	Reactant(const Reactant &other);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	 * @param other The reactant to copy
	 */
	Reactant(const Reactant &other);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual ~Reactant() {
	}

	/**
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
		return;
	}

	/**
	 * Create a combination associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 */
	virtual void createCombination(
			std::shared_ptr<ProductionReaction> reaction) {
		return;
	}

	/**
	 * Create a dissociation pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	virtual void createDissociation(
			std::shared_ptr<DissociationReaction> reaction) {
		return;
	}

	/**
	 * Create an emission pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster emits.
	 */
	virtual void createEmission(
			std::shared_ptr<DissociationReaction> reaction) {
		return;
	}

	/**
	 * Add the reactions to the network lists.
	 */
	virtual void optimizeReactions() {
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
			double distB = 0.0) const {

        return concentration;
    }
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	virtual ~Reactant();

	/**
	 * This operation returns a Reactant that is created using the copy
	 * constructor. If this Reactant is actually a subclass of Reactant, the
	 * clone will be of the same type and therefore carry all of the members
	 * and virtual functions of the subclass in addition to those of the
	 * Reactant. This type of copy is not only handy but, in fact, quite
	 * necessary in those cases where a Reactant must be copied but its exact
	 * subclass is unknown and there is no way to make a reasonable assumption
	 * about it.
	 * @return A copy of this reactant.
	 */
	virtual std::shared_ptr<Reactant> clone();

	/**
	 * An alternative constructor that can be used to create a reactant
	 * with an initial concentration.
	 *
	 * @param conc The initial concentration
	 */
	Reactant(double conc, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * This operation returns the current concentration.
	 *
	 * @return The concentration of this reactant
	 */
	double getConcentration() const;

	/**
	 * This operation increases the concentration of the reactant by the
	 * specified amount.
	 *
	 * @param deltaConc the change in concentration
	 */
	void increaseConcentration(double deltaConc);

	/**
	 * This operation decreases the concentration of the reactant by the
	 * specified amount.
	 *
	 * @param deltaConc the change in concentration
	 */
	void decreaseConcentration(double deltaConc);
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation sets the concentration of the reactant to the
	 * specified amount.
	 *
	 * @param conc The new concentation
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	void setConcentration(double conc) {
        concentration = conc;
    }
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	void setConcentration(double conc);

	/**
	 * This operation sets the concentration of the reactant to zero.
	 */
	void zero();
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation returns the total flux of this reactant in the
	 * current network.
	 *
<<<<<<< HEAD
<<<<<<< HEAD
	 * @return The total change in flux for this reactant due to all
	 * reactions
	 */
	virtual double getTotalFlux() {
        return 0.0;
    }
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * @param temperature The temperature at which to calculate the Diffusion Coefficient
	 * @return The total change in flux for this reactant due to all
	 * reactions
	 */
	virtual double getTotalFlux(const double temperature);
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation sets the collection of other reactants that make up
	 * the reaction network in which this reactant exists.
	 *
	 * @param network The reaction network of which this reactant is a part
	 */
	virtual void setReactionNetwork(
<<<<<<< HEAD
<<<<<<< HEAD
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
    }

	/**
	 * This operation signifies that the reactant with reactant Id should be
	 * listed as connected with this reactant through forward reactions.
	 *
	 * @param id The integer id of the reactant that is connected
	 * to this reactant
	 */
	void setReactionConnectivity(int id) {
        reactionConnectivitySet.insert(id);
    }

	/**
	 * This operation signifies that the reactant with reactant Id should be
	 * listed as connected with this reactant through forward reactions.
	 *
	 * @param id The integer id of the reactant that is connected
	 * to this reactant
	 */
	void setDissociationConnectivity(int id) {
        dissociationConnectivitySet.insert(id);
    }

	/**
	 * This operation reset the connectivity sets based on the information
	 * in the effective production and dissociation vectors.
	 */
	virtual void resetConnectivities() {
		return;
	}

	/**
	 * This operation returns a list that represents the connectivity
	 * between this reactant and other reactants in the network.
	 * "Connectivity" indicates whether two reactants interact, via any
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
			std::shared_ptr<ReactionNetwork> reactionNetwork);


    /**
     * Release the reaction network object.
     *
     * This should only be done when the reaction network is no longer needed
     * by the program, and is done to break dependence cycles that would
     * otherwise keep the network and reactant objects from being destroyed.
     */
    virtual void releaseReactionNetwork( void ) {
        network.reset();
    }


	/**
	 * This operation returns a list that represents the connectivity
	 * between this Reactant and other Reactants in the network.
	 * "Connectivity" indicates whether two Reactants interact, via any
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * mechanism, in an abstract sense (as if they were nodes connected by
	 * an edge on a network graph).
	 *
	 * @return An array of ones and zeros that indicate whether or not this
<<<<<<< HEAD
<<<<<<< HEAD
	 * reactant interacts via any mechanism with another reactant. A "1" at
	 * the i-th entry in this array indicates that the reactant interacts
	 * with the i-th reactant in the ReactionNetwork and a "0" indicates
=======
	 * Reactant interacts via any mechanism with another Reactant. A "1" at
	 * the i-th entry in this array indicates that the Reactant interacts
	 * with the i-th Reactant in the ReactionNetwork and a "0" indicates
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	 * Reactant interacts via any mechanism with another Reactant. A "1" at
	 * the i-th entry in this array indicates that the Reactant interacts
	 * with the i-th Reactant in the ReactionNetwork and a "0" indicates
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * that it does not.
	 */
	virtual std::vector<int> getConnectivity() const;

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * This operation returns the list of partial derivatives of this reactant
=======
	 * This operation returns the list of partial derivatives of this Reactant
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	 * This operation returns the list of partial derivatives of this Reactant
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * with respect to all other reactants in the network. The combined lists
	 * of partial derivatives from all of the reactants in the network can be
	 * used to form, for example, a Jacobian.
	 *
<<<<<<< HEAD
<<<<<<< HEAD
	 * @return the partial derivatives for this reactant where index zero
	 * corresponds to the first reactant in the list returned by the
	 * ReactionNetwork::getAll() operation.
	 */
	virtual std::vector<double> getPartialDerivatives() const {
        return std::vector<double>(network->getDOF(), 0.0);
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
	virtual void getPartialDerivatives(std::vector<double> & partials) const {
        // nothing to do.
    }

	/**
	 * This operation returns the name of the reactant.
	 *
	 * @return The name
	 */
	const std::string getName() const {
        return name;
    }

	/**
	 * This operation returns the reactant's type. It is up to subclasses to
	 * define exactly what the allowed types may be.
	 *
	 * @return The type of this reactant as a string
	 */
	std::string getType() const {
        return typeName;
    }

	/**
	 * This operation returns the composition of this reactant. This map is empty
	 * when returned by the base class.
	 *
	 * @return The composition returned as a map with keys naming distinct
	 * elements and values indicating the amount of the element present.
	 */
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
        if(compString.empty()) {
            compString = toCanonicalString(getType(), compositionMap);
        }
        return compString;
    }
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * @param the temperature at which the reactions are occurring
	 * @return the partial derivatives for this reactant where index zero
	 * corresponds to the first reactant in the list returned by the
	 * ReactionNetwork::getAll() operation.
	 */
	virtual std::vector<double> getPartialDerivatives(double temperature) const;

	/**
	 * This operation works as getPartialDerivatives above, but instead of
	 * returning a vector that it creates it fills a vector that is passed to
	 * it by the caller. This allows the caller to optimize the amount of
	 * memory allocations to just one if they are accessing the partial
	 * derivatives many times.
	 *
	 * The base class (Reactant) implementation does nothing.
	 *
	 * @param the temperature at which the reactions are occurring
	 * @param the vector that should be filled with the partial derivatives
	 * for this reactant where index zero corresponds to the first reactant in
	 * the list returned by the ReactionNetwork::getAll() operation. The size of
	 * the vector should be equal to ReactionNetwork::size().
	 */
	virtual void getPartialDerivatives(double temperature, std::vector<double> & partials) const;

	/**
	 * This operation writes the contents of the reactant to a string. This
	 * operation should be overridden by subclasses.
	 *
	 * @return A serialized version of this reactant as a string.
	 */
	virtual const std::string toString();

	/**
	 * This operation returns the name of the reactant.
	 * @return the name
	 */
	const std::string getName() const;

	/**
	 * This operation returns the reactant's type. It is up to subclasses to
	 * define exactly what the allowed types may be.
	 * @return The type of this reactant as a string.
	 */
	std::string getType() const;

	/**
	 * This operation returns the compositon of this reactant. This map is empty
	 * when returned by the base class.
	 * @return The composition returned as a map with keys naming distinct
	 * elements and values indicating the amount of the element present.
	 */
	virtual const std::map<std::string, int> & getComposition() const;
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation sets the id of the reactant, The id is zero by default
	 * and clients, most likely the ReactionNetwork, are expected to set the
	 * id as needed.
<<<<<<< HEAD
<<<<<<< HEAD
	 *
	 * @param nId The new id for this reactant
	 */
	void setId(int nId) {
        id = nId;
    }

	/**
	 * This operation returns the id for this reactant.
	 *
	 * @return The id
	 */
	int getId() const {
        return id;
    }

	/**
	 * This operation sets the id of the xenon momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
	void setXeMomentumId(int nId) {
        xeMomId = nId;
    }

	/**
	 * This operation returns the id for this reactant xenon momentum.
	 *
	 * @return The id
	 */
	int getXeMomentumId() const {
        return xeMomId;
    }

	/**
	 * This operation sets the id of the helium momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
	void setHeMomentumId(int nId) {
        heMomId = nId;
    }

	/**
	 * This operation returns the id for this reactant helium momentum.
	 *
	 * @return The id
	 */
	int getHeMomentumId() const {
        return heMomId;
    }

	/**
	 * This operation sets the id of the vacancy momentum of the reactant.
	 *
	 * @param nId The new id for this momentum
	 */
	void setVMomentumId(int nId) {
        vMomId = nId;
    }

	/**
	 * This operation returns the id for this reactant vacancy momentum.
	 *
	 * @return The id
	 */
	int getVMomentumId() const {
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
	void setTemperature(double temp);

	/**
	 * This operation returns the temperature at which the reactant currently exists.
	 *
	 * @return The temperature.
	 */
	double getTemperature() const {
        return temperature;
    }

	/**
	 * This operation returns the total size of the reactant.
	 *
	 * @return The total size of this reactant including the contributions
	 * from all species types
	 */
	int getSize() const {
        return size;
    }

	/**
	 * This operation retrieves the formation energy for this reactant.
	 *
	 * @return The value of the formation energy
	 */
	double getFormationEnergy() const {
        return formationEnergy;
    }

	/**
	 * This operation sets the formation energy for this reactant.
	 *
	 * @param energy The formation energy
	 */
	void setFormationEnergy(double energy) {
        formationEnergy = energy;
    }

	/**
	 * This operation retrieves the diffusion factor, D_0, that is used to
	 * calculate the diffusion coefficient for this reactant.
	 *
	 * @return The diffusion factor of this reactant
	 */
	double getDiffusionFactor() const {
        return diffusionFactor;
    }

	/**
	 * This operation sets the diffusion factor, D_0, that is used to calculate
	 * the diffusion coefficient for this reactant.
	 *
	 * @param factor The diffusion factor
	 */
	virtual void setDiffusionFactor(const double factor);

	/**
	 * This operation returns the diffusion coefficient for this reactant and is
	 * calculated from the diffusion factor.
	 *
	 * @return The diffusion coefficient
	 */
	double getDiffusionCoefficient() const {
        return diffusionCoefficient;
    }

	/**
	 * This operation sets the migration energy for this reactant.
	 *
	 * @param energy The migration energy
	 */
	virtual void setMigrationEnergy(const double energy);

	/**
	 * This operation retrieves the migration energy for this reactant.
	 *
	 * @return the migration energy
	 */
	double getMigrationEnergy() const {
        return migrationEnergy;
    }

	/**
	 * This operation returns the reaction radius for the
	 * particular reactant.
	 *
	 * @return The reaction radius
	 */
	double getReactionRadius() const {
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
	virtual double getLeftSideRate() const {
		return 0.0;
	}

	/**
	 * This operation returns true if the cluster is a mixed-species or compound
	 * cluster and false if it is a single species cluster.
	 */
	virtual bool isMixed() const {
		return false;
	}

	/**
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
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * @param nId The new id for this reactant
	 */
	void setId(int nId) {
		id = nId;
	}

	/**
	 * This operation returns the id for this reactant.
	 * @return The id
	 */
	int getId() const {
		return id;
	}
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

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
	virtual void setTemperature(double temp) {
		temperature = temp;
	}

	/**
	 * This operation returns the temperature at which the reactant currently exists.
	 * @return The temperature.
	 */
	double getTemperature() const {
		return temperature;
	}

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======

>>>>>>> Pulling "break circular dependencies of network and reactant objects" into the HDF5 branch. SB 20140624
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
};

} // end namespace xolotlCore

#endif
