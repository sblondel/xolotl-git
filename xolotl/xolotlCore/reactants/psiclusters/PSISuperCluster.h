#ifndef PSISUPERCLUSTER_H
#define PSISUPERCLUSTER_H

// Includes
<<<<<<< HEAD
#include "PSICluster.h"
#include <string>
#include <forward_list>
=======
#include <string>
#include <unordered_map>
#include <Constants.h>
#include "PSICluster.h"
#include "IntegerRange.h"

// We use std::unordered_map for quick lookup of info about 
// reactions we participate in.
// The C++ standard library defines a std::hash for keys
// that are a single pointer, but not for pairs of pointers,
// so we define our own here.  To improve readability,
// we define a concise name for type of a pair of IReactant pointers
// that we use as keys.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlCore {
/**
 *  A cluster gathering the average properties of many HeV clusters.
 */
class PSISuperCluster: public PSICluster {

<<<<<<< HEAD
protected:

	/**
	 * This is a protected class that is used to implement the flux calculations
	 * for two body production reactions.
	 *
	 * The constants are stored along the clusters taking part in the
	 * reaction or dissociation for faster computation because they only change
	 * when the temperature change. k is computed when setTemperature() is called.
	 */
	class SuperClusterProductionPair {
	public:
=======
private:
	static std::string buildName(double nHe, double nV) {
		std::stringstream nameStream;
		nameStream << "He_" << nHe << "V_" << nV;
		return nameStream.str();
	}

protected:

	struct ReactingInfoBase {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		/**
		 * The first cluster in the pair
		 */
<<<<<<< HEAD
		PSICluster * first;
=======
		PSICluster& first;

		/**
		 * The reaction/dissociation constant associated to this
		 * reaction or dissociation
		 */
		const double& kConstant;

		//! The constructor
		ReactingInfoBase(Reaction& _reaction, PSICluster& _first) :
				first(_first), kConstant(_reaction.kConstant) {

		}

		/**
		 * Default and copy constructors, disallowed.
		 */
		ReactingInfoBase() = delete;
		ReactingInfoBase(const ReactingInfoBase& other) = delete;
	};

	struct ReactingPairBase: public ReactingInfoBase {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		/**
		 * The second cluster in the pair
		 */
<<<<<<< HEAD
		PSICluster * second;

		/**
		 * The reaction/dissociation constant associated to this
		 * reaction or dissociation
		 */
		const double * kConstant;
=======
		PSICluster& second;

		//! The constructor
		ReactingPairBase(Reaction& _reaction, PSICluster& _first,
				PSICluster& _second) :
				ReactingInfoBase(_reaction, _first), second(_second) {

		}

		/**
		 * Default and copy constructors, disallowed.
		 */
		ReactingPairBase() = delete;
		ReactingPairBase(const ReactingPairBase& other) = delete;
	};

	struct ProductionCoefficientBase {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		/**
		 * All the coefficient needed to compute each element
		 * The first number represent the momentum of A, the second of B
		 * in A + B -> C
		 *
		 * The third number represent which momentum we are computing.
		 *
		 * 0 -> l0
		 * 1 -> He
		 * 2 -> V
		 */
		double a000;
		double a001;
		double a002;
		double a100;
		double a101;
		double a102;
		double a200;
		double a201;
		double a202;
		double a010;
		double a011;
		double a012;
		double a020;
		double a021;
		double a022;
		double a110;
		double a111;
		double a112;
		double a120;
		double a121;
		double a122;
		double a210;
		double a211;
		double a212;
		double a220;
		double a221;
		double a222;

		//! The constructor
<<<<<<< HEAD
		SuperClusterProductionPair(PSICluster * firstPtr,
				PSICluster * secondPtr, Reaction * reaction) :
				first(firstPtr), second(secondPtr), kConstant(
						&(reaction->kConstant)), a000(0.0), a001(0.0), a002(
						0.0), a100(0.0), a101(0.0), a102(0.0), a200(0.0), a201(
						0.0), a202(0.0), a010(0.0), a011(0.0), a012(0.0), a020(
						0.0), a021(0.0), a022(0.0), a110(0.0), a111(0.0), a112(
						0.0), a120(0.0), a121(0.0), a122(0.0), a210(0.0), a211(
						0.0), a212(0.0), a220(0.0), a221(0.0), a222(0.0) {
		}
=======
		ProductionCoefficientBase() :
				a000(0.0), a001(0.0), a002(0.0), a100(0.0), a101(0.0), a102(
						0.0), a200(0.0), a201(0.0), a202(0.0), a010(0.0), a011(
						0.0), a012(0.0), a020(0.0), a021(0.0), a022(0.0), a110(
						0.0), a111(0.0), a112(0.0), a120(0.0), a121(0.0), a122(
						0.0), a210(0.0), a211(0.0), a212(0.0), a220(0.0), a221(
						0.0), a222(0.0) {
		}

		/**
		 * Copy constructor, disallowed.
		 */
		ProductionCoefficientBase(const ProductionCoefficientBase& other) = delete;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	};

	/**
	 * This is a protected class that is used to implement the flux calculations
<<<<<<< HEAD
	 * for two dissociation reactions.
=======
	 * for two body production reactions.
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 *
	 * The constants are stored along the clusters taking part in the
	 * reaction or dissociation for faster computation because they only change
	 * when the temperature change. k is computed when setTemperature() is called.
	 */
<<<<<<< HEAD
	class SuperClusterDissociationPair {
	public:

		/**
		 * The first cluster in the pair
		 */
		PSICluster * first;

		/**
		 * The second cluster in the pair
		 */
		PSICluster * second;

		/**
		 * The reaction/dissociation constant associated to this
		 * reaction or dissociation
		 */
		const double * kConstant;
=======
	struct SuperClusterProductionPair: public ReactingPairBase,
			public ProductionCoefficientBase {

		/**
		 * Nice name for key type in map of key to production pair.
		 */
		using KeyType = ReactantAddrPair;

		//! The constructor
		SuperClusterProductionPair(Reaction& _reaction, PSICluster& _first,
				PSICluster& _second) :
				ReactingPairBase(_reaction, _first, _second), ProductionCoefficientBase() {

		}

		/**
		 * Default and copy constructors, deleted to enforce constructing
		 * using reactants.
		 */
		SuperClusterProductionPair() = delete;
		SuperClusterProductionPair(const SuperClusterProductionPair& other) = delete;
	};

	/**
	 * Concise name for type of map of SuperClusterProductionPairs.
	 */
	using ProductionPairMap = std::unordered_map<SuperClusterProductionPair::KeyType, SuperClusterProductionPair>;

	/**
	 * Info about a cluster we combine with.
	 */
	struct SuperClusterCombiningCluster: public ReactingInfoBase,
			public ProductionCoefficientBase {

		/**
		 * Concise name for type of keys in map of keys to
		 * combining cluster info.
		 */
		using KeyType = IReactant*;

		//! The constructor
		SuperClusterCombiningCluster(Reaction& _reaction, PSICluster& _first) :
				ReactingInfoBase(_reaction, _first), ProductionCoefficientBase() {

		}

		/**
		 * Default and copy construtors, deleted to enforce constructing
		 * using reactants.
		 */
		SuperClusterCombiningCluster() = delete;
		SuperClusterCombiningCluster(const SuperClusterCombiningCluster& other) = delete;
	};

	/**
	 * Concise name for type of map of SuperClusterCombiningClusters.
	 */
	using CombiningClusterMap = std::unordered_map<SuperClusterCombiningCluster::KeyType, SuperClusterCombiningCluster>;

	/**
	 * This is a protected class that is used to implement the flux calculations
	 * for two dissociation reactions.
	 *
	 * The constants are stored along the clusters taking part in the
	 * reaction or dissociation for faster computation because they only change
	 * when the temperature change. k is computed when setTemperature() is called.
	 */
	struct SuperClusterDissociationPair: public ReactingPairBase {

		/**
		 * Concise name for type of key into map of dissociation pairs.
		 */
		using KeyType = ReactantAddrPair;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		/**
		 * All the coefficient needed to compute each element
		 * The first number represent the momentum of A
		 * in A -> B + C
		 *
		 * The second number represent which momentum we are computing.
		 *
		 * 0 -> l0
		 * 1 -> He
		 * 2 -> V
		 */
		double a00;
		double a01;
		double a02;
		double a10;
		double a11;
		double a12;
		double a20;
		double a21;
		double a22;

		//! The constructor
<<<<<<< HEAD
		SuperClusterDissociationPair(PSICluster * firstPtr,
				PSICluster * secondPtr, Reaction * reaction) :
				first(firstPtr), second(secondPtr), kConstant(
						&(reaction->kConstant)), a00(0.0), a01(0.0), a02(0.0), a10(
						0.0), a11(0.0), a12(0.0), a20(0.0), a21(0.0), a22(0.0) {
		}
	};

=======
		SuperClusterDissociationPair(Reaction& _reaction, PSICluster& _first,
				PSICluster& _second) :
				ReactingPairBase(_reaction, _first, _second), a00(0.0), a01(
						0.0), a02(0.0), a10(0.0), a11(0.0), a12(0.0), a20(0.0), a21(
						0.0), a22(0.0) {

		}

		/**
		 * Default and copy constructors, disallowed.
		 */
		SuperClusterDissociationPair() = delete;
		SuperClusterDissociationPair(const SuperClusterDissociationPair& other) = delete;
	};

	/**
	 * Concise name for type of map of SuperClusterDissociationPairs.
	 */
	using DissociationPairMap = std::unordered_map<SuperClusterDissociationPair::KeyType, SuperClusterDissociationPair>;

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
private:

	//! The mean number of helium atoms in this cluster.
	double numHe;

	//! The mean number of atomic vacancies in this cluster.
	double numV;

	//! The total number of clusters gathered in this super cluster.
	int nTot;

	//! The width in the helium direction.
	int sectionHeWidth;

	//! The width in the vacancy direction.
	int sectionVWidth;

<<<<<<< HEAD
=======
	/**
	 * Bounds on number of He atoms represented by this cluster.
	 */
	IntegerRange<IReactant::SizeType> heBounds;

	/**
	 * Bounds on number of vacancies represented by this cluster.
	 */
	IntegerRange<IReactant::SizeType> vBounds;

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	//! The 0th order momentum (mean).
	double l0;

	//! The first order momentum in the helium direction.
	double l1He;

	//! The first order momentum in the vacancy direction.
	double l1V;

	//! The dispersion in the group in the helium direction.
	double dispersionHe;

	//! The dispersion in the group in the vacancy direction.
	double dispersionV;

<<<<<<< HEAD
	//! The map containing all the reacting pairs separated by original composition.
	std::map<std::pair<int, int>, std::vector<ClusterPair> > reactingMap;

	//! The map containing all the combining clusters separated by original composition.
	std::map<std::pair<int, int>, std::vector<CombiningCluster> > combiningMap;

	//! The map containing all the dissociating pairs separated by original composition.
	std::map<std::pair<int, int>, std::vector<ClusterPair> > dissociatingMap;

	//! The map containing all the emission pairs separated by original composition.
	std::map<std::pair<int, int>, std::vector<ClusterPair> > emissionMap;

	//! The list of optimized effective reacting pairs.
	std::forward_list<SuperClusterProductionPair> effReactingList;

	//! The list of optimized effective combining pairs.
	std::forward_list<SuperClusterProductionPair> effCombiningList;

	//! The list of optimized effective dissociating pairs.
	std::forward_list<SuperClusterDissociationPair> effDissociatingList;

	//! The list of optimized effective emission pairs.
	std::forward_list<SuperClusterDissociationPair> effEmissionList;
=======
	/**
	 * The list of clusters gathered in this.
	 */
	std::set<std::pair<int, int> > heVList;

	//! The list of optimized effective reacting pairs.
	ProductionPairMap effReactingList;

	//! The list of optimized effective combining pairs.
	CombiningClusterMap effCombiningList;

	//! The list of optimized effective dissociating pairs.
	DissociationPairMap effDissociatingList;

	//! The list of optimized effective emission pairs.
	DissociationPairMap effEmissionList;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The helium momentum flux.
	 */
	double heMomentumFlux;

	/**
	 * The vacancy momentum flux.
	 */
	double vMomentumFlux;

	/**
<<<<<<< HEAD
	 * The default constructor is private because PSIClusters must always be
	 * initialized with a size.
	 */
	PSISuperCluster() :
			PSICluster() {
	}

	/**
	 * Group the same reactions together.
	 */
	void optimizeReactions();

public:

	//! The vector of HeV clusters it will replace
	std::vector<PSICluster *> heVVector;
=======
	 * Output coefficients for a given reaction to the given output stream.
	 *
	 * @param os The output stream on which to write the coefficients.
	 * @param curr Information about our participation in a reaction.
	 */
	void dumpCoefficients(std::ostream& os,
			ProductionCoefficientBase const& curr) const;
	void dumpCoefficients(std::ostream& os,
			SuperClusterDissociationPair const& curr) const;

public:

	/**
	 * Default constructor, deleted because we require info to construct.
	 */
	PSISuperCluster() = delete;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The constructor. All SuperClusters must be initialized with its
	 * composition.
	 *
	 * @param numHe The mean number of helium atoms in this cluster
	 * @param numV The mean number of vacancies in this cluster
	 * @param nTot The total number of clusters in this cluster
	 * @param heWidth The width of this super cluster in the helium direction
	 * @param vWidth The width of this super cluster in the vacancy direction
	 * @param radius The mean radius
	 * @param energy The mean formation energy
	 * @param registry The performance handler registry
	 */
	PSISuperCluster(double numHe, double numV, int nTot, int heWidth,
<<<<<<< HEAD
			int vWidth, double radius, double energy,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Copy constructor.
	 *
	 * @param other the reactant to be copied
	 */
	PSISuperCluster(PSISuperCluster &other);
=======
			int vWidth, IReactionNetwork& _network,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	/**
	 * Copy constructor, deleted to prevent use.
	 */
	PSISuperCluster(PSISuperCluster &other) = delete;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	//! Destructor
	~PSISuperCluster() {
	}

	/**
<<<<<<< HEAD
	 * This operation returns a Reactant that is created using the copy
	 * constructor of PSISuperCluster.
	 *
	 * @return A copy of this reactant
	 */
	virtual std::shared_ptr<IReactant> clone() {
		return std::make_shared<PSISuperCluster>(*this);
	}

	/**
	 * Sets the collection of other clusters that make up
	 * the reaction network in which this cluster exists.
	 *
	 * @param network The reaction network of which this cluster is a part
	 */
	void setReactionNetwork(
			const std::shared_ptr<IReactionNetwork> reactionNetwork);
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
	 * This operation returns true to signify that this cluster is a mixture of
	 * He and V.
	 *
	 * @return True if mixed
	 */
<<<<<<< HEAD
	virtual bool isMixed() const {
=======
	virtual bool isMixed() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return true;
	}

	/**
<<<<<<< HEAD
	 * Set the HeV vector
	 */
	void setHeVVector(std::vector<PSICluster *> vec) {
		heVVector = vec;
	}
=======
	 * Set the HeV vector and compute different parameters
	 */
	void setHeVVector(std::set<std::pair<int, int> > vec);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the current concentration.
	 *
	 * @param distHe The helium distance in the group
	 * @param distV The vacancy distance in the group
	 * @return The concentration of this reactant
	 */
<<<<<<< HEAD
	double getConcentration(double distHe, double distV) const {
=======
	double getConcentration(double distHe, double distV) const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return l0 + (distHe * l1He) + (distV * l1V);
	}

	/**
	 * This operation returns the first helium momentum.
	 *
	 * @return The momentum
	 */
<<<<<<< HEAD
	double getHeMomentum() const {
=======
	double getHeMomentum() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return l1He;
	}

	/**
	 * This operation returns the first vacancy momentum.
	 *
	 * @return The momentum
	 */
<<<<<<< HEAD
	double getVMomentum() const {
=======
	double getVMomentum() const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return l1V;
	}

	/**
	 * This operation returns the current total concentration of clusters in the group.

	 * @return The concentration
	 */
	double getTotalConcentration() const;

	/**
	 * This operation returns the current total concentration of helium in the group.

	 * @return The concentration
	 */
	double getTotalHeliumConcentration() const;

	/**
	 * This operation returns the current total concentration of vacancies in the group.
<<<<<<< HEAD
	 *
=======

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 * @return The concentration
	 */
	double getTotalVacancyConcentration() const;

	/**
	 * This operation returns the current concentration for a vacancy number.
	 *
	 * @param v The vacancy number
	 * @return The concentration
	 */
	double getIntegratedVConcentration(int v) const;

	/**
	 * This operation returns the distance to the mean.
	 *
	 * @param he The number of helium
	 * @return The distance to the mean number of helium in the group
	 */
<<<<<<< HEAD
	double getHeDistance(int he) const {
=======
	double getHeDistance(int he) const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return (sectionHeWidth == 1) ?
				0.0 : 2.0 * (he - numHe) / (sectionHeWidth - 1.0);
	}

	/**
	 * This operation returns the distance to the mean.
	 *
<<<<<<< HEAD
	 * @param v The number of vacancy
	 * @return The distance to the mean number of vacancy in the group
	 */
	double getVDistance(int v) const {
=======
	 * @param he The number of vacancy
	 * @return The distance to the mean number of vacancy in the group
	 */
	double getVDistance(int v) const override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return (sectionVWidth == 1) ?
				0.0 : 2.0 * (v - numV) / (sectionVWidth - 1.0);
	}

	/**
<<<<<<< HEAD
	 * Calculate the dispersion of the group.
	 */
	void computeDispersion();

	/**
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	 * This operation sets the zeroth order momentum.
	 *
	 * @param mom The momentum
	 */
	void setZerothMomentum(double mom) {
		l0 = mom;
	}

	/**
	 * This operation sets the first order momentum in the helium direction.
	 *
	 * @param mom The momentum
	 */
	void setHeMomentum(double mom) {
		l1He = mom;
	}

	/**
	 * This operation sets the first order momentum in the vacancy direction.
	 *
	 * @param mom The momentum
	 */
	void setVMomentum(double mom) {
		l1V = mom;
	}

	/**
	 * This operation reset the connectivity sets based on the information
	 * in the production and dissociation vectors.
	 */
<<<<<<< HEAD
	void resetConnectivities();
=======
	void resetConnectivities() override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation returns the total flux of this cluster in the
	 * current network.
	 *
	 * @return The total change in flux for this cluster due to all
	 * reactions
	 */
<<<<<<< HEAD
	double getTotalFlux() {
=======
	double getTotalFlux() override {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Initialize the fluxes
		heMomentumFlux = 0.0;
		vMomentumFlux = 0.0;

		// Compute the fluxes.
		return getProductionFlux() - getCombinationFlux()
				+ getDissociationFlux() - getEmissionFlux();
	}

	/**
	 * This operation returns the total change in this cluster due to
	 * other clusters dissociating into it. Compute the contributions to
	 * the momentum fluxes at the same time.
	 *
	 * @return The flux due to dissociation of other clusters
	 */
	double getDissociationFlux();

	/**
	 * This operation returns the total change in this cluster due its
	 * own dissociation. Compute the contributions to
	 * the momentum fluxes at the same time.
	 *
	 * @return The flux due to its dissociation
	 */
	double getEmissionFlux();

	/**
	 * This operation returns the total change in this cluster due to
	 * the production of this cluster by other clusters. Compute the contributions to
	 * the momentum fluxes at the same time.
	 *
	 * @return The flux due to this cluster being produced
	 */
	double getProductionFlux();

	/**
	 * This operation returns the total change in this cluster due to
	 * the combination of this cluster with others. Compute the contributions to
	 * the momentum fluxes at the same time.
	 *
	 * @return The flux due to this cluster combining with other clusters
	 */
	double getCombinationFlux();

	/**
	 * This operation returns the total change for its helium momentum.
	 *
	 * @return The momentum flux
	 */
<<<<<<< HEAD
	double getHeMomentumFlux() {
=======
	double getHeMomentumFlux() const {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return heMomentumFlux;
	}

	/**
	 * This operation returns the total change for its vacancy momentum.
	 *
	 * @return The momentum flux
	 */
<<<<<<< HEAD
	double getVMomentumFlux() {
=======
	double getVMomentumFlux() const {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return vMomentumFlux;
	}

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
	void getPartialDerivatives(std::vector<double> & partials) const;
=======
	void getPartialDerivatives(std::vector<double> & partials) const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the partial derivatives due to production
	 * reactions.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
<<<<<<< HEAD
	void getProductionPartialDerivatives(std::vector<double> & partials) const;
=======
	void getProductionPartialDerivatives(std::vector<double> & partials) const
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the partial derivatives due to combination
	 * reactions.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
<<<<<<< HEAD
	void getCombinationPartialDerivatives(std::vector<double> & partials) const;
=======
	void getCombinationPartialDerivatives(std::vector<double> & partials) const
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the partial derivatives due to dissociation of
	 * other clusters into this one.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
<<<<<<< HEAD
	void getDissociationPartialDerivatives(
			std::vector<double> & partials) const;
=======
	void getDissociationPartialDerivatives(std::vector<double> & partials) const
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the partial derivatives due to emission
	 * reactions.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted. This vector should have a length equal to the size of the
	 * network.
	 */
<<<<<<< HEAD
	void getEmissionPartialDerivatives(std::vector<double> & partials) const;
=======
	void getEmissionPartialDerivatives(std::vector<double> & partials) const
			override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation computes the partial derivatives for the helium momentum.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted.
	 */
	void getHeMomentPartialDerivatives(std::vector<double> & partials) const;

	/**
	 * This operation computes the partial derivatives for the vacancy momentum.
	 *
	 * @param partials The vector into which the partial derivatives should be
	 * inserted.
	 */
	void getVMomentPartialDerivatives(std::vector<double> & partials) const;

	/**
	 * Returns the average number of vacancies.
	 *
	 * @return The average number of vacancies
	 */
<<<<<<< HEAD
	double getNumV() {
=======
	double getNumV() const {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return numV;
	}

	/**
<<<<<<< HEAD
	 * Returns a vector containing the information about the group's bounderies
	 * in the helium and vacancy directions.
	 *
	 * @return The boundaries
	 */
	std::vector<int> getBoundaries() const {
		std::vector<int> boundaries;
		boundaries.push_back((int) (numHe - (double) sectionHeWidth / 2.0) + 1);
		boundaries.push_back(
				(int) (numHe - (double) sectionHeWidth / 2.0) + sectionHeWidth);
		boundaries.push_back((int) (numV - (double) sectionVWidth / 2.0) + 1);
		boundaries.push_back(
				(int) (numV - (double) sectionVWidth / 2.0) + sectionVWidth);
		return boundaries;
	}

=======
	 * Returns the number of clusters contained.
	 *
	 * @return The number of clusters
	 */
	double getNTot() const {
		return nTot;
	}

	/**
	 * Access bounds on number of He atoms represented by this cluster.
	 */
	// TODO do we want to make this generic by taking a type parameter?
	const IntegerRange<IReactant::SizeType>& getHeBounds() const {
		return heBounds;
	}

	/**
	 * Access bounds on number of vacancies represented by this cluster.
	 */
	const IntegerRange<IReactant::SizeType>& getVBounds() const {
		return vBounds;
	}

	/**
	 * Detect if given number of He and V are in this cluster's group.
	 *
	 * @param _nHe number of He of interest.
	 * @param _nV number of V of interest
	 * @return True if _nHe and _nV is contained in our super cluster.
	 */
	bool isIn(IReactant::SizeType _nHe, IReactant::SizeType _nV) const {
		if (!heBounds.contains(_nHe))
			return false;
		if (!vBounds.contains(_nV))
			return false;

		return (heVList.find(std::make_pair(_nHe, _nV)) != heVList.end());
	}

	/**
	 * Tell reactant to output a representation of its reaction coefficients
	 * to the given output stream.
	 *
	 * @param os Output stream on which to output coefficients.
	 */
	virtual void outputCoefficientsTo(std::ostream& os) const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
};
//end class PSISuperCluster

} /* end namespace xolotlCore */
#endif
