#ifndef PSI_CLUSTER_REACTION_NETWORK_H
#define PSI_CLUSTER_REACTION_NETWORK_H

// Includes
<<<<<<< HEAD
//#include <xolotlPerf.h>
=======
//#include "xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <ReactionNetwork.h>
<<<<<<< HEAD
=======
#include <PSICluster.h>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include <iostream>
#include <iomanip>
#include <algorithm>

<<<<<<< HEAD
=======
// Override the hash operation for the composition maps used by the
// PSIClusterReactionNetwork to store reactants.
namespace std {
template<>
class hash<std::map<std::string, int>> {
public:
	long operator()(const std::map<std::string, int>& composition) const {
		int bigNumber = 1e9;
		return (composition.at("He") * 10 + composition.at("V") * 200
				+ composition.at("I") * 3000) * bigNumber;
	}
};
}

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
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

	/**
<<<<<<< HEAD
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
	 * Maximum size of HeV clusters in our network.
	 */
	int maxHeVClusterSize;

	/**
	 * Maximum size of HeI clusters in our network.
	 */
	int maxHeIClusterSize;
=======
	 * The map of single-species clusters, indexed by a map that contains the
	 * name of the reactant and its size.
	 */
	std::unordered_map<std::map<std::string, int>, std::shared_ptr<PSICluster>> singleSpeciesMap;

	/**
	 * The map of mixed or compound species clusters, indexed by a map that
	 * contains the name of the constituents of the compound reactant and their
	 * sizes.
	 */
	std::unordered_map<std::map<std::string, int>, std::shared_ptr<PSICluster>> mixedSpeciesMap;

	/**
	 * This map stores all of the clusters in the network by type
	 */
	std::map<std::string,
			std::shared_ptr<std::vector<std::shared_ptr<Reactant>>> >clusterTypeMap;

	/**
	 * The names of the reactants supported by this network.
	 */
	std::vector<std::string> names;

	/**
	 * The names of the compound reactants supported by this network.
	 */
	std::vector<std::string> compoundNames;

	/**
	 * The size of the network. It is also used to set the id of new Reactants
	 * that are added to the network.
	 */
	int networkSize;

	/**
	 * The list of all of the reactants in the network. This list is filled and
	 * maintained by the getAll() operation.
	 */
	std::shared_ptr<std::vector<std::shared_ptr<Reactant> > > allReactants;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation sets the default values of the properties table and names
	 * for this network. It is used on construction and during a copy.
	 */
	void setDefaultPropsAndNames();

	/**
<<<<<<< HEAD
	 * Calculate the dissociation constant of the first cluster with respect to
	 * the single-species cluster of the same type based on the current clusters
	 * atomic volume, reaction rate constant, and binding energies.
	 *
	 * @param reaction The reaction
	 * @return The dissociation constant
	 */
	double calculateDissociationConstant(DissociationReaction * reaction) const;

	/**
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * The Constructor
	 */
	PSIClusterReactionNetwork();

public:

	/**
	 * The Constructor
<<<<<<< HEAD
	 *
	 * @param registry The performance handler registry
	 */
	PSIClusterReactionNetwork(
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The copy constructor.
	 *
=======
	 */
	PSIClusterReactionNetwork(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The copy constructor
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * @param other
	 */
	PSIClusterReactionNetwork(const PSIClusterReactionNetwork &other);

	/**
<<<<<<< HEAD
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
=======
	 * This operation returns a reactant with the given name and size if it
	 * exists in the network or null if not.
	 * @param rName the name of the reactant
	 * @param size the size of the reactant
	 * @return A shared pointer to the reactant
	 */
	std::shared_ptr<Reactant> get(const std::string rName,
			const int size) const;

	/**
	 * This operation returns a compound reactant with the given name and size
	 * if it exists in the network or null if not.
	 * @param rName the name of the compound reactant
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * @param sizes an array containing the sizes of each piece of the reactant.
	 * For PSIClusters, this array must be ordered in size by He, V and I. This
	 * array must contain an entry for He, V and I, even if only He and V or He
	 * and I are contained in the mixed-species cluster.
<<<<<<< HEAD
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
=======
	 * @return A shared pointer to the compound reactant
	 */
	std::shared_ptr<Reactant> getCompound(const std::string rName,
			const std::vector<int> sizes) const;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns all reactants in the network without regard for
	 * their composition or whether they are compound reactants. The list may
	 * or may not be ordered and the decision is left to implementers.
<<<<<<< HEAD
	 *
	 * @return The list of all of the reactants in the network
	 */
	const std::shared_ptr<std::vector<IReactant *>> & getAll() const;
=======
	 * @return The list of all of the reactants in the network
	 */
	std::shared_ptr<std::vector<std::shared_ptr<Reactant> > > getAll() const;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns all reactants in the network with the given name.
	 * The list may or may not be ordered and the decision is left to
	 * implementers.
<<<<<<< HEAD
	 *
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * @param name The reactant or compound reactant name
	 * @return The list of all of the reactants in the network or null if the
	 * name is invalid.
	 */
<<<<<<< HEAD
	std::vector<IReactant *> getAll(const std::string& name) const;
=======
	std::shared_ptr<std::vector<std::shared_ptr<Reactant> > > getAll(std::string name) const;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation adds a reactant or a compound reactant to the network.
	 * Adding a reactant to the network does not set the network as the
	 * reaction network for the reactant. This step must be performed
	 * separately to allow for the scenario where the network is generated
	 * entirely before running.
	 *
	 * This operation sets the id of the reactant to one that is specific
<<<<<<< HEAD
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
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * to this network. Do not share Reactants across networks! This id is
	 * guaranteed to be between 1 and n, including both, for n reactants in
	 * the network.
	 *
	 * The reactant will not be added to the network if the PSICluster does
	 * not recognize it as a type of reactant that it cares about (including
	 * adding null). This operation throws an exception of type std::string
	 * if the reactant is  already in the network.
<<<<<<< HEAD
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

	/**
	 * This operation reinitializes the network.
	 *
	 * It computes the cluster Ids and network size from the allReactants vector.
	 */
	void reinitializeNetwork();

	/**
	 * This method redefines the connectivities for each cluster in the
	 * allReactans vector.
	 */
	void reinitializeConnectivities();

	/**
	 * This operation updates the concentrations for all reactants in the
	 * network from an array.
	 *
	 * @param concentrations The array of doubles that will be for the
	 * concentrations. This operation does NOT create, destroy or resize the
	 * array. Properly aligning the array in memory so that this operation
	 * does not overrun is up to the caller.
	 */
	void updateConcentrationsFromArray(double * concentrations);

	/**
	 * This operation returns the size or number of reactants and momentums in the network.
	 *
	 * @return The number of degrees of freedom
	 */
	virtual int getDOF() {
		return networkSize + 2 * numSuperClusters + 1;
	}

	/**
	 * Get the diagonal fill for the Jacobian, corresponding to the reactions.
	 *
	 * @param diagFill The pointer to the vector where the connectivity information is kept
	 */
	void getDiagonalFill(int *diagFill);

	/**
	 * Get the total concentration of atoms contained in the network.
	 *
	 * Here the atoms that are considered are helium atoms.
	 *
	 * @return The total concentration
	 */
	double getTotalAtomConcentration();

	/**
	 * Get the total concentration of atoms contained in bubbles in the network.
	 *
	 * Here the atoms that are considered are helium atoms.
	 *
	 * @return The total concentration
	 */
	double getTotalTrappedAtomConcentration();

	/**
	 * Get the total concentration of vacancies contained in the network.
	 *
	 * @return The total concentration
	 */
	double getTotalVConcentration();

	/**
	 * Get the total concentration of tungsten interstitials in the network.
	 *
	 * @return The total concentration
	 */
	double getTotalIConcentration();

	/**
	 * Calculate all the rate constants for the reactions and dissociations of the network.
	 * Need to be called only when the temperature changes.
	 */
	void computeRateConstants() ;

	/**
	 * Compute the fluxes generated by all the reactions
	 * for all the clusters and their momentums.
	 *
	 * @param updatedConcOffset The pointer to the array of the concentration at the grid
	 * point where the fluxes are computed used to find the next solution
	 */
	void computeAllFluxes(double *updatedConcOffset);

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
	virtual void computeAllPartials(double *vals, int *indices, int *size);

	/**
	 * Number of He clusters in our network.
	 */
	int getNumHeClusters() const {
		return numHeClusters;
	}

	/**
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
=======
	 * @param reactant The reactant that should be added to the network.
	 */
	void add(std::shared_ptr<Reactant> reactant);

	/**
	 * This operation returns the names of the reactants in the network. For a
	 * PSIClusterReactionNetwork, these are He, V, I, HeV, HeI.
	 * @return A vector with one entry for each of the distinct reactant types
	 * in the network.
	 */
	const std::vector<std::string> & getNames() const;

	/**
	 * This operation returns the names of the compound reactants in the
	 * network.
	 * @return A vector with one each for each of the distinct compound
	 * reactant types in the network.
	 */
	const std::vector<std::string> & getCompoundNames() const;

	/**
	 * This operation returns a map of the properties of this reaction network.
	 * @return The map of properties that has been configured for this
	 * ReactionNetwork.
	 *
	 * The PSIClusterReactionNetwork always has the following properties:
	 * > maxHeClusterSize - The number of He atoms in the largest single-species
	 *  He cluster.
	 * > maxVClusterSize - The number of atomic vacancies in the largest
	 * single-species V cluster.
	 * > maxIClusterSize - The number of interstitials in the largest
	 * single-species I cluster.
	 * > maxHeVClusterSize - The number of species of all types in the largest
	 * mixed species in the network. It is equal to the sum of the max single
	 * species helium and vacancy cluster sizes by default.
	 * > maxHeIClusterSize - The number of species of all types in the largest
	 * mixed species in the network. It is equal to the sum of the max single
	 * species helium and vacancy cluster sizes by default.
	 * > numHeClusters - The number of single-species He clusters of all sizes in
	 * the network.
	 * > numVClusters - The number of single-species V clusters of all sizes in the
	 * network.
	 * > numIClusters - The number of single-species I clusters of all sizes in the
	 * network.
	 * > numHeVClusters - The number of HeV clusters of all sizes in the
	 * network.
	 * > numHeIClusters - The number of HeI clusters of all sizes in the
	 * network.
	 *
	 * These properties are always updated when a cluster is added.
	 */
	const std::map<std::string, std::string> & getProperties();

	/**
	 * This operation sets a property with the given key to the specified value
	 * for the network. ReactionNetworks may reserve the right to ignore this
	 * operation for special key types, most especially those that they manage
	 * on their own.
	 * @param key The key for the property
	 * @param value The value to which the key should be set.
	 */
	void setProperty(std::string key, std::string value);

	/**
	 * This operation returns the size or number of reactants in the network.
	 * @return The number of reactants in the network
	 */
	int size();

	/**
	 * This is a utility operation that creates a composition vector with an
	 * entry for helium, vacancies and interstitials. It is handy because it
	 * removes the need to construct the vectors properly and locally. The
	 * vector can be used to retrieve clusters.
	 *
	 * This function will never return an composition with less than three
	 * elements and it will always return element sizes greater than zero. If
	 * any of the elements are negative, it will default to 1,0,0 (single He).
	 * @param numHe The number of helium atoms in the cluster
	 * @param numV The number of atomic vacancies in the cluster
	 * @param numI The number of interstitial defects in the cluster
	 * @return A vector of size three with an entry for each of the parts
	 * equal to the numbers that were passed for that part.
	 */
	std::vector<int> getCompositionVector(int numHe, int numV, int numI) {
		// This flag is used so that negative numbers can be checked without
		// branching.
		int hasNegativeElement = ((numHe < 0) + (numV < 0) + (numI < 0) > 0);
		std::vector<int> composition(3);
		composition[0] = std::max(0,numHe*!hasNegativeElement);
		composition[1] = std::max(0,numV*!hasNegativeElement);
		composition[2] = std::max(0,numI*!hasNegativeElement);
		return composition;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

};

}

#endif
