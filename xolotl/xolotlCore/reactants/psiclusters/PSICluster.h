#ifndef PSICLUSTER_H
#define PSICLUSTER_H

// Includes
#include <Reactant.h>
<<<<<<< HEAD
=======
#include "IntegerRange.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlPerf {
class ITimer;
}

namespace xolotlCore {

/**
 * The PSICluster class is a Reactant that is specialized to work for
 * simulations of plasma-surface interactions. It provides special routines
 * for calculating the total flux due to production and dissociation and
 * obtaining the cluster size.
 *
 * PSIClusters must always be initialized with a size. If the constructor is
 * passed a size of zero or less, the actual size will be set to 1.
 *
 * The getComposition() operation is implemented by subclasses and will always
 * return a map with the keys He, V, I, HeV or HeI. The operation getTypeName()
 * will always return one of the same values.
 *
 * As a rule, it is possible to access directly some of the private members of
 * this class (id, concentration, reactionRadius, diffusionCoefficient, size,
<<<<<<< HEAD
 * typeName) instead of using the "get" functions for performance reasons. In
=======
 * type) instead of using the "get" functions for performance reasons. In
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
 * order to change these values the "set" functions must still be used.
 */
class PSICluster: public Reactant {

protected:

	/**
	 * This is a protected class that is used to implement the flux calculations
	 * for two body reactions or dissociation.
	 *
	 * The constant k+ or k- is stored along the clusters taking part in the
	 * reaction or dissociation for faster computation because they only change
	 * when the temperature change. k is computed when setTemperature() is called.
	 */
	class ClusterPair {
	public:

		/**
		 * The first cluster in the pair
		 */
<<<<<<< HEAD
		PSICluster * first;
=======
		PSICluster& first;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		/**
		 * The second cluster in the pair
		 */
<<<<<<< HEAD
		PSICluster * second;

		/**
		 * The first cluster helium distance in the group (0.0 for non-super clusters)
		 */
		double firstHeDistance;

		/**
		 * The first cluster vacancy distance in the group (0.0 for non-super clusters)
		 */
		double firstVDistance;

		/**
		 * The second cluster helium distance in the group (0.0 for non-super clusters)
		 */
		double secondHeDistance;

		/**
		 * The second cluster vacancy distance in the group (0.0 for non-super clusters)
		 */
		double secondVDistance;

		/**
		 * The reaction/dissociation pointer to the list
		 */
		std::shared_ptr<Reaction> reaction;

		/**
		 * The number of times this reaction should be counted
		 */
		int multiplicity;

		//! The constructor
		ClusterPair(PSICluster * firstPtr, PSICluster * secondPtr) :
<<<<<<< HEAD
<<<<<<< HEAD
				first(firstPtr), second(secondPtr), reaction(
						nullptr), firstHeDistance(0.0), firstVDistance(
						0.0), secondHeDistance(0.0), secondVDistance(0.0), multiplicity(1) {
=======
				first(firstPtr), second(secondPtr), reaction(nullptr), firstHeDistance(
						0.0), firstVDistance(0.0), secondHeDistance(0.0), secondVDistance(
						0.0), multiplicity(1) {
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
				first(firstPtr), second(secondPtr), reaction(nullptr), firstHeDistance(
						0.0), firstVDistance(0.0), secondHeDistance(0.0), secondVDistance(
						0.0), multiplicity(1) {
>>>>>>> master
		}
=======
		PSICluster& second;

		/**
		 * The reaction/dissociation pointer to the list
		 */
		Reaction& reaction;

		/**
		 * All the coefficient needed to compute each element
		 * The first number represent the momentum of A, the second of B
		 * in A + B -> C
		 *
		 * 0 -> l0
		 * 1 -> He
		 * 2 -> V
		 */
		double a00;
		double a10;
		double a20;
		double a01;
		double a02;
		double a11;
		double a12;
		double a21;
		double a22;

		//! The constructor
		ClusterPair(Reaction& _reaction, PSICluster& _first,
				PSICluster& _second) :
				first(_first), second(_second), reaction(_reaction), a00(0.0), a10(
						0.0), a20(0.0), a01(0.0), a02(0.0), a11(0.0), a12(0.0), a21(
						0.0), a22(0.0) {
		}

		/**
		 * Default and copy constructors, disallowed.
		 */
		ClusterPair() = delete;

		// NB: if PSICluster keeps these in a std::vector,
		// copy ctor is needed.  Implicit definition is fine.
		// CombiningCluster(const CombiningCluster& other) = delete;
		// ClusterPair(const ClusterPair& other) = delete;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	};

	/**
	 * This is a protected class that is used to implement the flux calculations
	 * for combinations.
	 *
	 * The constant k+ is stored along the cluster that combines with this cluster
	 * for faster computation because they only change when the temperature change.
	 * k+ is computed when setTemperature() is called.
	 */
<<<<<<< HEAD
	class CombiningCluster {
	public:
=======
	struct CombiningCluster {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		/**
		 * The combining cluster
		 */
<<<<<<< HEAD
		PSICluster * combining;

		/**
		 * The combining cluster helium distance in the group (0.0 for non-super clusters)
		 */
		double heDistance;

		/**
		 * The combining cluster vacancy distance in the group (0.0 for non-super clusters)
		 */
		double vDistance;

		/**
		 * The reaction pointer to the list
		 */
		std::shared_ptr<Reaction> reaction;

		/**
		 * The number of times this reaction should be counted
		 */
		int multiplicity;

		//! The constructor
		CombiningCluster(PSICluster * ptr) :
<<<<<<< HEAD
<<<<<<< HEAD
				combining(ptr), reaction(nullptr), heDistance(
						0.0), vDistance(0.0), multiplicity(1) {
=======
				combining(ptr), reaction(nullptr), heDistance(0.0), vDistance(
						0.0), multiplicity(1) {
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
				combining(ptr), reaction(nullptr), heDistance(0.0), vDistance(
						0.0), multiplicity(1) {
		}
	};

	/**

=======
		PSICluster& combining;

		/**
		 * The reaction pointer to the list
		 */
		Reaction& reaction;

		/**
		 * All the coefficient needed to compute each element
		 * The first number represent the momentum of A
		 * in A + this -> C
		 *
		 * 0 -> l0
		 * 1 -> He
		 * 2 -> V
		 */
		double a0;
		double a1;
		double a2;

		//! The constructor
		CombiningCluster(Reaction& _reaction, PSICluster& _comb) :
				combining(_comb), reaction(_reaction), a0(0.0), a1(0.0), a2(0.0) {
>>>>>>> master
		}

		/**
		 * Default constructor, disallowed to prohibit building without args.
		 */
		CombiningCluster() = delete;

		// NB: if PSICluster keeps these in a std::vector,
		// copy ctor is needed.  Implicit definition is fine.
		// CombiningCluster(const CombiningCluster& other) = delete;
	};

	/**
	 * Bounds on number of He atoms represented by this cluster.
	 */
	IntegerRange<IReactant::SizeType> heBounds;

	/**
	 * Bounds on number of vacancies represented by this cluster.
	 */
	IntegerRange<IReactant::SizeType> vBounds;

	/**
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 * This operation returns a set that contains only the entries of the
	 * reaction connectivity array that are non-zero.
	 *
	 * @return The set of connected reactants. Each entry in the set is the id
	 * of a connected cluster for forward reactions.
	 */
	std::set<int> getReactionConnectivitySet() const;

	/**
	 * This operation returns a set that contains only the entries of the
	 * dissociation connectivity array that are non-zero.
	 *
	 * @return The set of connected reactants. Each entry in the set is the id
	 * of a connected cluster for dissociation reactions
	 */
	const std::set<int> & getDissociationConnectivitySet() const;

	/**
<<<<<<< HEAD
	 * The default constructor is protected
	 */
	PSICluster();
=======
	 * Output coefficients for a given reaction to the given output stream.
	 *
	 * @param os The output stream on which to write the coefficients.
	 * @param curr Information about our participation in a reaction.
	 */
	void dumpCoefficients(std::ostream& os, ClusterPair const& curr) const;
	void dumpCoefficients(std::ostream& os, CombiningCluster const& curr) const;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

public:

	/**
	 * A vector of ClusterPairs that represents reacting pairs of clusters
	 * that produce this cluster. This vector should be populated early in the
	 * cluster's lifecycle by subclasses. In the standard Xolotl clusters,
	 * this vector is filled in createReactionConnectivity.
	 */
	std::vector<ClusterPair> reactingPairs;

	/**
	 * A vector of clusters that combine with this cluster to produce other
	 * clusters. This vector should be populated early in the cluster's
	 * lifecycle by subclasses. In the standard Xolotl clusters, this vector is
	 * filled in createReactionConnectivity.
	 */
	std::vector<CombiningCluster> combiningReactants;

	/**
	 * A vector of pairs of clusters: the first one is the one dissociation into
	 * this cluster, the second one is the one that is emitted at the same time
	 * during the dissociation. This vector should be populated early in the
	 * cluster's lifecycle by subclasses. In the standard Xolotl clusters, this
	 * vector is filled in dissociateCluster that is called by
	 * createDissociationConnectivity.
	 */
	std::vector<ClusterPair> dissociatingPairs;

	/**
	 * A vector of ClusterPairs that represent pairs of clusters that are emitted
	 * from the dissociation of this cluster. This vector should be populated early
	 * in the cluster's lifecycle by subclasses. In the standard Xolotl clusters,
	 * this vector is filled in emitClusters that is called by
	 * createDissociationConnectivity.
	 */
	std::vector<ClusterPair> emissionPairs;

	/**
<<<<<<< HEAD
	 * The default constructor
	 *
	 * @param registry The performance handler registry
	 */
	PSICluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * The copy constructor
	 *
	 * @param other The cluster to copy
	 */
	PSICluster(PSICluster &other);
=======
	 * Default constructor, deleted because we require info to construct.
	 */
	PSICluster() = delete;

	/**
	 * Construct a PSICluster.
	 *
	 * @param registry The performance handler registry
	 */
	PSICluster(IReactionNetwork& _network,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry,
			const std::string& _name = "PSICluster") :
			Reactant(_network, registry, _name), heBounds(0, 0), vBounds(0, 0) {

	}

	/**
	 * Copy constructor, deleted to prevent use.
	 */
	PSICluster(PSICluster &other) :
			Reactant(other), heBounds(0, 0), vBounds(0, 0) {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The destructor
	 */
	virtual ~PSICluster() {
	}

	/**
<<<<<<< HEAD
	 * Returns a reactant created using the copy constructor
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::shared_ptr<IReactant>(new PSICluster(*this));
	}

	/**
	 * Sets the collection of other clusters that make up
	 * the reaction network in which this cluster exists.
	 *
	 * @param network The reaction network of which this cluster is a part
	 */
	virtual void setReactionNetwork(
			const std::shared_ptr<IReactionNetwork> reactionNetwork);

	/**
	 * Create a production pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	void createProduction(std::shared_ptr<ProductionReaction> reaction);

	/**
	 * Create a combination associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 */
	void createCombination(std::shared_ptr<ProductionReaction> reaction);

	/**
	 * Create a dissociation pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction creating this cluster.
	 */
	void createDissociation(std::shared_ptr<DissociationReaction> reaction);

	/**
	 * Create an emission pair associated with the given reaction.
	 * Create the connectivity.
	 *
	 * @param reaction The reaction where this cluster emits.
	 */
	void createEmission(std::shared_ptr<DissociationReaction> reaction);

	/**
	 * Add the reactions to the network lists.
	 */
	virtual void optimizeReactions();
=======
	 * Update reactant using other reactants in its network.
	 */
	virtual void updateFromNetwork() override;

	/**
	 * Note that we result from the given reaction.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 * @param c Number that can be used by daughter classes.
	 * @param d Number that can be used by daughter classes.
	 */
	void resultFrom(ProductionReaction& reaction, int a = 0, int b = 0, int c =
			0, int d = 0) override;

	/**
	 * Note that we result from the given reaction involving a super cluster.
	 * Assumes the reaction is already in the network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param prInfos Production reaction parameters.
	 */
	void resultFrom(ProductionReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) override;

	/**
	 * Note that we combine with another cluster in a production reaction.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param a Number that can be used by daughter classes.
	 * @param b Number that can be used by daughter classes.
	 */
	void participateIn(ProductionReaction& reaction, int a = 0, int b = 0)
			override;

	/**
	 * Note that we combine with another cluster in a production reaction
	 * involving a super cluster.
	 * Assumes that the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster takes part.
	 * @param prInfos Production reaction parameters.
	 */
	void participateIn(ProductionReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) override;

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
	void participateIn(DissociationReaction& reaction, int a = 0, int b = 0,
			int c = 0, int d = 0) override;

	/**
	 * Note that we combine with another cluster in a dissociation reaction
	 * involving a super cluster.
	 * Assumes the reaction is already inour network.
	 *
	 * @param reaction The reaction creating this cluster.
	 * @param prInfos Production reaction parameters.
	 */
	void participateIn(DissociationReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) override;

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
	void emitFrom(DissociationReaction& reaction, int a = 0, int b = 0, int c =
			0, int d = 0) override;

	/**
	 * Note that we emit from the given reaction involving a super cluster.
	 * Assumes the reaction is already in our network.
	 *
	 * @param reaction The reaction where this cluster emits.
	 * @param prInfos Production reaction parameters.
	 */
	void emitFrom(DissociationReaction& reaction,
			const std::vector<PendingProductionReactionInfo>& prInfos) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the connectivity array for this cluster for
	 * forward reactions. An entry with value one means that this cluster
	 * and the cluster with id = index + 1 are connected.
	 * 
	 * @return The connectivity array for "forward" (non-dissociating)
	 * reactions
	 */
	virtual std::vector<int> getReactionConnectivity() const;

	/**
	 * This operation returns the connectivity array for this cluster for
	 * forward reactions. An entry with value one means that this cluster
	 * and the cluster with id = index + 1 are connected.
	 * 
	 * @return The connectivity array for "forward" (non-dissociating)
	 * reactions
	 */
	virtual std::vector<int> getDissociationConnectivity() const;

	/**
	 * This operation returns the first helium momentum.
	 *
	 * @return The momentum
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual double getHeMomentum() const;
=======
	virtual double getHeMomentum() const {
		return 0.0;
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	virtual double getHeMomentum() const {
		return 0.0;
	}
>>>>>>> master

	/**
	 * This operation returns the first vacancy momentum.
	 *
	 * @return The momentum
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual double getVMomentum() const;
=======
	virtual double getVMomentum() const {
		return 0.0;
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	virtual double getVMomentum() const {
		return 0.0;
	}
<<<<<<< HEAD
=======
	/**
	 * This operation returns the distance to the mean.
	 *
	 * @param he The number of helium
	 * @return The distance to the mean number of helium in the group
	 */
	virtual double getHeDistance(int he) const {
		return 0.0;
	}

	/**
	 * This operation returns the distance to the mean.
	 *
	 * @param he The number of vacancy
	 * @return The distance to the mean number of vacancy in the group
	 */
	virtual double getVDistance(int v) const {
		return 0.0;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

	/**
	 * This operation returns the total flux of this cluster in the
	 * current network.
	 *
	 * @return The total change in flux for this cluster due to all
	 * reactions
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual double getTotalFlux();
=======
	virtual double getTotalFlux() {
		return getProductionFlux() - getCombinationFlux()
				+ getDissociationFlux() - getEmissionFlux();
	}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	virtual double getTotalFlux() {
=======
	virtual double getTotalFlux() override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return getProductionFlux() - getCombinationFlux()
				+ getDissociationFlux() - getEmissionFlux();
	}
>>>>>>> master

	/**
	 * This operation returns the total change in this cluster due to
	 * other clusters dissociating into it.
	 *
	 * @return The flux due to dissociation of other clusters
	 */
	virtual double getDissociationFlux() const;

	/**
	 * This operation returns the total change in this cluster due its
	 * own dissociation.
	 *
	 * @return The flux due to its dissociation
	 */
	virtual double getEmissionFlux() const;

	/**
	 * This operation returns the total change in this cluster due to
	 * the production of this cluster by other clusters.
	 *
	 * @return The flux due to this cluster being produced
	 */
	virtual double getProductionFlux() const;

	/**
	 * This operation returns the total change in this cluster due to
	 * the combination of this cluster with others.
	 *
	 * @return The flux due to this cluster combining with other clusters
	 */
	virtual double getCombinationFlux() const;

	/**
	 * This operation returns the list of partial derivatives of this cluster
	 * with respect to all other clusters in the network. The combined lists
	 * of partial derivatives from all of the clusters in the network can be
	 * used to form, for example, a Jacobian.
	 *
	 * @return The partial derivatives for this cluster where index zero
	 * corresponds to the first cluster in the list returned by the
	 * ReactionNetwork::getAll() operation.
	 */
<<<<<<< HEAD
	virtual std::vector<double> getPartialDerivatives() const;
=======
	virtual std::vector<double> getPartialDerivatives() const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation works as getPartialDerivatives above, but instead of
	 * returning a vector that it creates it fills a vector that is passed to
	 * it by the caller. This allows the caller to optimize the amount of
	 * memory allocations to just one if they are accessing the partial
	 * derivatives many times.
	 *
	 * @param the vector that should be filled with the partial derivatives
	 * for this reactant where index zero corresponds to the first reactant in
	 * the list returned by the ReactionNetwork::getAll() operation. The size of
	 * the vector should be equal to ReactionNetwork::size().
	 *
	 */
<<<<<<< HEAD
	virtual void getPartialDerivatives(std::vector<double> & partials) const;
=======
	virtual void getPartialDerivatives(std::vector<double> & partials) const
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the partial derivatives due to production
	 * reactions.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
	virtual void getProductionPartialDerivatives(
			std::vector<double> & partials) const;

	/**
	 * This operation computes the partial derivatives due to combination
	 * reactions.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
	virtual void getCombinationPartialDerivatives(
			std::vector<double> & partials) const;

	/**
	 * This operation computes the partial derivatives due to dissociation of
	 * other clusters into this one.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
	virtual void getDissociationPartialDerivatives(
			std::vector<double> & partials) const;

	/**
	 * This operation computes the partial derivatives due to emission
	 * reactions.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
	virtual void getEmissionPartialDerivatives(
			std::vector<double> & partials) const;

	/**
	 * This operation reset the connectivity sets based on the information
	 * in the effective production and dissociation vectors.
	 */
<<<<<<< HEAD
	void resetConnectivities();
=======
	void resetConnectivities() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation sets the diffusion factor, D_0, that is used to calculate
	 * the diffusion coefficient for this cluster.
	 *
	 * @param factor The diffusion factor
	 */
<<<<<<< HEAD
	void setDiffusionFactor(const double factor);
=======
	void setDiffusionFactor(const double factor) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation sets the migration energy for this reactant.
	 *
	 * @param energy The migration energy
	 */
<<<<<<< HEAD
	void setMigrationEnergy(const double energy);
=======
	void setMigrationEnergy(const double energy) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the sum of combination rate and emission rate
	 * (where this cluster is on the left side of the reaction) for this
	 * particular cluster.
	 * This is used to computed the desorption rate in the
	 * modified trap-mutation handler.
	 *
	 * @return The rate
	 */
<<<<<<< HEAD
	double getLeftSideRate() const;
=======
	double getLeftSideRate() const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns a list that represents the connectivity
	 * between this cluster and other clusters in the network.
	 * "Connectivity" indicates whether two clusters interact, via any
	 * mechanism, in an abstract sense (as if they were nodes connected by
	 * an edge on a network graph).
	 *
	 * @return An array of ones and zeros that indicate whether or not this
	 * cluster interacts via any mechanism with another cluster. A "1" at
	 * the i-th entry in this array indicates that the cluster interacts
	 * with the i-th cluster in the ReactionNetwork and a "0" indicates
	 * that it does not.
	 */
<<<<<<< HEAD
	std::vector<int> getConnectivity() const;

=======
	std::vector<int> getConnectivity() const override;

	/**
	 * Tell reactant to output a representation of its reaction coefficients
	 * to the given output stream.
	 *
	 * @param os Output stream on which to output coefficients.
	 */
	virtual void outputCoefficientsTo(std::ostream& os) const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
};

} /* end namespace xolotlCore */
#endif
