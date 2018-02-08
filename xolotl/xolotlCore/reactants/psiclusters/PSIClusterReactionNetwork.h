#ifndef PSI_CLUSTER_REACTION_NETWORK_H
#define PSI_CLUSTER_REACTION_NETWORK_H

// Includes
<<<<<<< HEAD
//#include <xolotlPerf.h>
=======
#include <iostream>
#include <iomanip>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
<<<<<<< HEAD
#include <ReactionNetwork.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
=======
#include <algorithm>
#include "ReactionNetwork.h"
#include "PSISuperCluster.h"
#include "ReactantType.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlCore {

/**
 *  This class manages the set of reactants and compound reactants (
 *  combinations of normal reactants) for PSI clusters. It also manages a
 *  set of properties that describes the total collection.
 *
 *  This class is a very heavyweight class that should not be abused.
 *
 *  Reactants that are added to this network must be added as with shared_ptrs.
 *  Furthermore, reactants that are added to this network have their ids set to
 *  a network specific id. Reactants should not be shared between separate
 *  instances of a PSIClusterReactionNetwork.
 */
class PSIClusterReactionNetwork: public ReactionNetwork {

private:
<<<<<<< HEAD

	/**
	 * The map of single-species clusters, indexed by a string representation
	 * of a map that contains the name of the reactant and its size.
	 */
	std::unordered_map<std::string, std::shared_ptr<IReactant> > singleSpeciesMap;

	/**
	 * The map of mixed or compound species clusters, indexed by a string
	 * representation of a map that contains the name of the constituents
	 * of the compound reactant and their sizes.
	 */
	std::unordered_map<std::string, std::shared_ptr<IReactant> > mixedSpeciesMap;

	/**
	 * The map of super species clusters, indexed by a map that
	 * contains the name of the constituents of the compound reactant and their
	 * sizes.
	 */
	std::unordered_map<std::string, std::shared_ptr<IReactant> > superSpeciesMap;

	/**
	 * This map stores all of the clusters in the network by type.
	 */
	std::map<std::string,
			std::shared_ptr<std::vector<std::shared_ptr<IReactant> > > > clusterTypeMap;
	/**
	 * Number of He clusters in our network.
	 */
	int numHeClusters;

	/**
<<<<<<< HEAD
=======
	 * Number of deuterium clusters in our network.
	 */
	int numDClusters;

	/**
	 * Number of tritium clusters in our network.
	 */
	int numTClusters;

	/**
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	 * Number of HeV clusters in our network.
	 */
	int numHeVClusters;

	/**
	 * Number of HeI clusters in our network.
	 */
	int numHeIClusters;

	/**
	 * Maximum size of He clusters in our network.
	 */
	int maxHeClusterSize;

	/**
<<<<<<< HEAD
=======
	 * Maximum size of deuterium clusters in our network.
	 */
	int maxDClusterSize;

	/**
	 * Maximum size of tritium clusters in our network.
	 */
	int maxTClusterSize;

	/**
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	 * Maximum size of HeV clusters in our network.
	 */
	int maxHeVClusterSize;

	/**
	 * Maximum size of HeI clusters in our network.
	 */
	int maxHeIClusterSize;

	/**
	 * This operation sets the default values of the properties table and names
	 * for this network. It is used on construction and during a copy.
	 */
	void setDefaultPropsAndNames();

	/**
	 * Calculate the dissociation constant of the first cluster with respect to
	 * the single-species cluster of the same type based on the current clusters
	 * atomic volume, reaction rate constant, and binding energies.
	 *
	 * @param reaction The reaction
	 * @return The dissociation constant
	 */
	double calculateDissociationConstant(DissociationReaction * reaction) const;

	/**
	 * The Constructor
	 */
	PSIClusterReactionNetwork();

public:

	/**
	 * The Constructor
	 *
	 * @param registry The performance handler registry
	 */
	PSIClusterReactionNetwork(
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The copy constructor.
	 *
	 * @param other
	 */
	PSIClusterReactionNetwork(const PSIClusterReactionNetwork &other);

	/**
	 * Computes the full reaction connectivity matrix for this network.
	 */
	void createReactionConnectivity();

	/**
	 * Add the dissociation connectivity for the reverse reaction if it is allowed.
	 *
	 * @param emittingReactant The reactant that would emit the pair
	 * @param reaction The reaction we want to reverse
	 *
	 */
	void checkDissociationConnectivity(IReactant * emittingReactant,
			std::shared_ptr<ProductionReaction> reaction);

	/**
	 * This operation sets the temperature at which the reactants currently
	 * exists. It calls setTemperature() on each reactant.
	 *
	 * This is the simplest way to set the temperature for all reactants is to
	 * call the ReactionNetwork::setTemperature() operation.
	 *
	 * @param temp The new temperature
	 */
	virtual void setTemperature(double temp);

	/**
	 * This operation returns the temperature at which the cluster currently exists.
	 *
	 * @return The temperature.
	 */
	virtual double getTemperature() const;

	/**
	 * This operation returns a reactant with the given type and size if it
	 * exists in the network or null if not.
	 *
	 * @param type the type of the reactant
	 * @param size the size of the reactant
	 * @return A pointer to the reactant
	 */
	IReactant * get(const std::string& type, const int size) const;

	/**
	 * This operation returns a compound reactant with the given type and size
	 * if it exists in the network or null if not.
	 *
	 * @param type the type of the compound reactant
	 * @param sizes an array containing the sizes of each piece of the reactant.
	 * For PSIClusters, this array must be ordered in size by He, V and I. This
	 * array must contain an entry for He, V and I, even if only He and V or He
	 * and I are contained in the mixed-species cluster.
	 * @return A pointer to the compound reactant
	 */
	IReactant * getCompound(const std::string& type,
			const std::vector<int>& sizes) const;

	/**
	 * This operation returns a super reactant with the given type and size
	 * if it exists in the network or null if not.
	 *
	 * @param type the type of the compound reactant
	 * @param sizes an array containing the sizes of each piece of the reactant.
	 * For PSIClusters, this array must be ordered in size by He, V and I. This
	 * array must contain an entry for He, V and I, even if only He and V or He
	 * and I are contained in the mixed-species cluster.
	 * @return A pointer to the compound reactant
	 */
	IReactant * getSuper(const std::string& type,
			const std::vector<int>& sizes) const;

	/**
	 * This operation returns all reactants in the network without regard for
	 * their composition or whether they are compound reactants. The list may
	 * or may not be ordered and the decision is left to implementers.
	 *
	 * @return The list of all of the reactants in the network
	 */
	const std::shared_ptr<std::vector<IReactant *>> & getAll() const;

	/**
	 * This operation returns all reactants in the network with the given name.
	 * The list may or may not be ordered and the decision is left to
	 * implementers.
	 *
	 * @param name The reactant or compound reactant name
	 * @return The list of all of the reactants in the network or null if the
	 * name is invalid.
	 */
	std::vector<IReactant *> getAll(const std::string& name) const;

	/**
	 * This operation adds a reactant or a compound reactant to the network.
	 * Adding a reactant to the network does not set the network as the
	 * reaction network for the reactant. This step must be performed
	 * separately to allow for the scenario where the network is generated
	 * entirely before running.
	 *
	 * This operation sets the id of the reactant to one that is specific
	 * to this network. Do not share reactants across networks! This id is
	 * guaranteed to be between 1 and n, including both, for n reactants in
	 * the network.
	 *
	 * The reactant will not be added to the network if the PSICluster does
	 * not recognize it as a type of reactant that it cares about (including
	 * adding null). This operation throws an exception of type std::string
	 * if the reactant is  already in the network.
	 *
	 * @param reactant The reactant that should be added to the network.
	 */
	void add(std::shared_ptr<IReactant> reactant);

	/**
	 * This operation adds a super reactant to the network.
	 * Adding a reactant to the network does not set the network as the
	 * reaction network for the reactant. This step must be performed
	 * separately to allow for the scenario where the network is generated
	 * entirely before running.
	 *
	 * This operation sets the id of the reactant to one that is specific
	 * to this network. Do not share Reactants across networks! This id is
	 * guaranteed to be between 1 and n, including both, for n reactants in
	 * the network.
	 *
	 * The reactant will not be added to the network if the PSICluster does
	 * not recognize it as a type of reactant that it cares about (including
	 * adding null). This operation throws an exception of type std::string
	 * if the reactant is  already in the network.
	 *
	 * @param reactant The reactant that should be added to the network.
	 */
	void addSuper(std::shared_ptr<IReactant> reactant);

	/**
	 * This operation removes a group of reactants from the network.
	 *
	 * @param reactants The reactants that should be removed.
	 */
	void removeReactants(const std::vector<IReactant*>& reactants);
=======
	/**
	 * Concise name for map supporting quick lookup of supercluster containing
	 * specifc number of He and V.
	 *
	 * We could use a map, but because we expect it to be dense (i.e.,
	 * most pairs of He and V counts will have a valid super cluster),
	 * a 2D matrix indexed by nHe and nV gives better performance for
	 * lookups without costing too much more (if any) in terms of memory.
	 * We use a vector of vectors instead of array of arrays because
	 * we don't know the dimensions at compile time.  We use a vector of
	 * vectors instead of a single vector with more complex indexing
	 * to simplify indexing.  It may be worthwhile to compare performance
	 * with a single vector implementation to see if the single
	 * memory allocation ends up giving better performance.
	 */
	using HeVToSuperClusterMap = std::vector<std::vector<ReactantMap::const_iterator> >;

	/**
	 * Map supporting quick identification of super cluster containing
	 * given number of He and V.
	 */
	HeVToSuperClusterMap superClusterLookupMap;

	/**
	 * Calculate the dissociation constant of the first cluster with respect to
	 * the single-species cluster of the same type based on the current clusters
	 * atomic volume, reaction rate constant, and binding energies.
	 *
	 * @param reaction The reaction
	 * @return The dissociation constant
	 */
	double calculateDissociationConstant(
			const DissociationReaction& reaction) const override;

	/**
	 * Calculate the binding energy for the dissociation cluster to emit the single
	 * and second cluster.
	 *
	 * @param reaction The reaction
	 * @return The binding energy corresponding to this dissociation
	 */
	double computeBindingEnergy(const DissociationReaction& reaction) const
			override;

	/**
	 * Find the super cluster that contains the original cluster with nHe
	 * helium atoms and nV vacancies.
	 *
	 * @param nHe the type of the compound reactant
	 * @param nV an array containing the sizes of each piece of the reactant.
	 * @return The super cluster representing the cluster with nHe helium
	 * and nV vacancies, or nullptr if no such cluster exists.
	 */
	IReactant * getSuperFromComp(IReactant::SizeType nHe,
			IReactant::SizeType nV);

	ProductionReaction& defineReactionBase(IReactant& r1, IReactant& r2, int a =
			0, int b = 0, bool secondProduct = false)
			__attribute__((always_inline)) {

		// Add a production reaction to our network.
		std::unique_ptr<ProductionReaction> reaction(
				new ProductionReaction(r1, r2));
		auto& prref = add(std::move(reaction));

		// Tell the reactants that they are involved in this reaction
		// if this is not the second product
		if (secondProduct)
			return prref;

		r1.participateIn(prref, a, b);
		r2.participateIn(prref, a, b);

		return prref;
	}

	void defineAnnihilationReaction(IReactant& r1, IReactant& r2,
			IReactant& product) {

		// Define the basic reaction.
		auto& reaction = defineReactionBase(r1, r2);

		// Tell the product it results from the reaction.
		product.resultFrom(reaction);
	}

	void defineCompleteAnnihilationReaction(IReactant& r1, IReactant& r2) {

		// Define the basic reaction
		defineReactionBase(r1, r2);

		// Nothing else to do since there is no product.
	}

	void defineProductionReaction(IReactant& r1, IReactant& super,
			IReactant& product, int a = 0, int b = 0, int c = 0, int d = 0,
			bool secondProduct = false) {

		// Define the basic production reaction.
		auto& reaction = defineReactionBase(r1, super, c, d, secondProduct);

		// Tell product it is a product of this reaction.
		product.resultFrom(reaction, a, b, c, d);

		if (secondProduct)
			return;

		// Check if reverse reaction is allowed.
		checkForDissociation(product, reaction, a, b, c, d);
	}

	/**
	 * Define a batch of production reactions for the given
	 * pair of reactants.
	 *
	 * @param r1 A reactant involved in a production reaction.
	 * @param r2 The super reactant involved in a production reaction.
	 * @param pris Information about reactants are involved with each reaction.
	 * @param secondProduct If we are setting the reaction for the second product.
	 */
	void defineProductionReactions(IReactant& r1, IReactant& super,
			const std::vector<PendingProductionReactionInfo>& pris,
			bool secondProduct = false);

	// TODO should we default a, b, c, d to 0?
	void defineDissociationReaction(ProductionReaction& forwardReaction,
			IReactant& emitting, int a, int b, int c, int d) {

		std::unique_ptr<DissociationReaction> dissociationReaction(
				new DissociationReaction(emitting, forwardReaction.first,
						forwardReaction.second, &forwardReaction));
		auto& drref = add(std::move(dissociationReaction));

		// Tell the reactants that they are in this reaction
		forwardReaction.first.participateIn(drref, a, b, c, d);
		forwardReaction.second.participateIn(drref, a, b, c, d);
		emitting.emitFrom(drref, a, b, c, d);
	}

	/**
	 * Define a batch of dissociation reactions for the given
	 * forward reaction.
	 *
	 * @param forwardReaction The forward reaction in question.
	 * @param prodMap Map of reaction parameters, keyed by the product
	 * of the reaction.
	 */
	// TODO possible to use a ref for the key?
	using ProductToProductionMap =
	std::unordered_map<IReactant*, std::vector<PendingProductionReactionInfo> >;

	void defineDissociationReactions(ProductionReaction& forwardReaction,
			const ProductToProductionMap& prodMap);

	/**
	 * Check whether dissociation reaction is allowed for
	 * given production reaction.
	 *
	 * @param reaction The reaction to test.
	 * @return true iff dissociation for the given reaction is allowed.
	 */
	bool canDissociate(ProductionReaction& reaction) const;

	/**
	 * Add the dissociation connectivity for the reverse reaction if it is allowed.
	 *
	 * @param emittingReactant The reactant that would emit the pair
	 * @param reaction The reaction we want to reverse
	 * @param a The helium number for the emitting superCluster
	 * @param b The vacancy number for the emitting superCluster
	 * @param c The helium number for the emitted superCluster
	 * @param d The vacancy number for the emitted superCluster
	 *
	 */
	void checkForDissociation(IReactant& emittingReactant,
			ProductionReaction& reaction, int a = 0, int b = 0, int c = 0,
			int d = 0);

public:

	/**
	 * Default constructor, deleted to force construction using parameters.
	 */
	PSIClusterReactionNetwork() = delete;

	/**
	 * The Constructor
	 *
	 * @param registry The performance handler registry
	 */
	PSIClusterReactionNetwork(
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Copy constructor, deleted to prevent use.
	 */
	PSIClusterReactionNetwork(const PSIClusterReactionNetwork& other) = delete;

	/**
	 * Computes the full reaction connectivity matrix for this network.
	 */
	void createReactionConnectivity();

	/**
	 * This operation sets the temperature at which the reactants currently
	 * exists. It calls setTemperature() on each reactant.
	 *
	 * This is the simplest way to set the temperature for all reactants is to
	 * call the ReactionNetwork::setTemperature() operation.
	 *
	 * @param temp The new temperature
	 */
	virtual void setTemperature(double temp) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation reinitializes the network.
	 *
	 * It computes the cluster Ids and network size from the allReactants vector.
	 */
<<<<<<< HEAD
	void reinitializeNetwork();
=======
	void reinitializeNetwork() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This method redefines the connectivities for each cluster in the
	 * allReactans vector.
	 */
<<<<<<< HEAD
	void reinitializeConnectivities();
=======
	void reinitializeConnectivities() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation updates the concentrations for all reactants in the
	 * network from an array.
	 *
	 * @param concentrations The array of doubles that will be for the
	 * concentrations. This operation does NOT create, destroy or resize the
	 * array. Properly aligning the array in memory so that this operation
	 * does not overrun is up to the caller.
	 */
<<<<<<< HEAD
	void updateConcentrationsFromArray(double * concentrations);
=======
	void updateConcentrationsFromArray(double * concentrations) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the size or number of reactants and momentums in the network.
	 *
	 * @return The number of degrees of freedom
	 */
<<<<<<< HEAD
	virtual int getDOF() {
		return networkSize + 2 * numSuperClusters + 1;
=======
	virtual int getDOF() const override {
		return size() + 2 * getAll(ReactantType::PSISuper).size() + 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	/**
	 * Get the diagonal fill for the Jacobian, corresponding to the reactions.
	 *
	 * @param diagFill The pointer to the vector where the connectivity information is kept
	 */
<<<<<<< HEAD
	void getDiagonalFill(int *diagFill);
=======
	void getDiagonalFill(int *diagFill) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total concentration of atoms contained in the network.
	 *
	 * Here the atoms that are considered are helium atoms.
	 *
	 * @return The total concentration
	 */
<<<<<<< HEAD
	double getTotalAtomConcentration();
=======
	double getTotalAtomConcentration() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total concentration of atoms contained in bubbles in the network.
	 *
	 * Here the atoms that are considered are helium atoms.
	 *
	 * @return The total concentration
	 */
<<<<<<< HEAD
	double getTotalTrappedAtomConcentration();
=======
	double getTotalTrappedAtomConcentration() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total concentration of vacancies contained in the network.
	 *
	 * @return The total concentration
	 */
<<<<<<< HEAD
	double getTotalVConcentration();
=======
	double getTotalVConcentration() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total concentration of tungsten interstitials in the network.
	 *
	 * @return The total concentration
	 */
<<<<<<< HEAD
	double getTotalIConcentration();
=======
	double getTotalIConcentration() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Calculate all the rate constants for the reactions and dissociations of the network.
	 * Need to be called only when the temperature changes.
	 */
<<<<<<< HEAD
	void computeRateConstants() ;
=======
	void computeRateConstants() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the fluxes generated by all the reactions
	 * for all the clusters and their momentums.
	 *
	 * @param updatedConcOffset The pointer to the array of the concentration at the grid
	 * point where the fluxes are computed used to find the next solution
	 */
<<<<<<< HEAD
	void computeAllFluxes(double *updatedConcOffset);
=======
	void computeAllFluxes(double *updatedConcOffset) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the partial derivatives generated by all the reactions
	 * for all the clusters and their momentum.
	 *
	 * @param vals The pointer to the array that will contain the values of
	 * partials for the reactions
	 * @param indices The pointer to the array that will contain the indices
	 * of the clusters
	 * @param size The pointer to the array that will contain the number of reactions for
	 * this cluster
	 */
<<<<<<< HEAD
	virtual void computeAllPartials(double *vals, int *indices, int *size);

	/**
	 * Number of He clusters in our network.
	 */
	int getNumHeClusters() const {
		return numHeClusters;
	}

	/**
<<<<<<< HEAD
=======
	 * Number of D clusters in our network.
	 */
	int getNumDClusters() const {
		return numDClusters;
	}

	/**
	 * Number of T clusters in our network.
	 */
	int getNumTClusters() const {
		return numTClusters;
	}

	/**
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	 * Number of HeV clusters in our network.
	 */
	int getNumHeVClusters() const {
		return numHeVClusters;
	}

	/**
	 * Number of HeI clusters in our network.
	 */
	int getNumHeIClusters() const {
		return numHeIClusters;
	}

	/**
	 * Maximum size of He clusters in our network.
	 */
	int getMaxHeClusterSize() const {
		return maxHeClusterSize;
	}

	/**
<<<<<<< HEAD
=======
	 * Maximum size of D clusters in our network.
	 */
	int getMaxDClusterSize() const {
		return maxDClusterSize;
	}

	/**
	 * Maximum size of T clusters in our network.
	 */
	int getMaxTClusterSize() const {
		return maxTClusterSize;
	}

	/**
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	 * Maximum size of HeV clusters in our network.
	 */
	int getMaxHeVClusterSize() const {
		return maxHeVClusterSize;
	}

	/**
	 * Maximum size of HeI clusters in our network.
	 */
	int getMaxHeIClusterSize() const {
		return maxHeIClusterSize;
	}

};

}
=======
	virtual void computeAllPartials(double *vals, int *indices, int *size)
			override;
};

} // namespace xolotlCore
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

#endif
