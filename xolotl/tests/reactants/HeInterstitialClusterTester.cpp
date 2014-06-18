/*
 * PSIClusterTester.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Jay Jay Billings
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSICluster.h>
#include "SimpleReactionNetwork.h"
#include <HeInterstitialCluster.h>
#include <HeCluster.h>
#include <memory>
#include <typeinfo>
#include <limits>
#include <algorithm>

using namespace std;
using namespace xolotlCore;
using namespace testUtils;

<<<<<<< HEAD
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();
=======
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

/**
 * This suite is responsible for testing the HeInterstitialCluster.
 */
BOOST_AUTO_TEST_SUITE(HeInterstitialCluster_testSuite)

<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
BOOST_AUTO_TEST_CASE(getSpeciesSize) {
	HeInterstitialCluster cluster(4, 2, registry);

	// Get the composition back
	auto composition = cluster.getComposition();

	// Check the composition is the created one
	BOOST_REQUIRE_EQUAL(composition["He"], 4);
	BOOST_REQUIRE_EQUAL(composition["V"], 0);
	BOOST_REQUIRE_EQUAL(composition["I"], 2);
<<<<<<< HEAD

	// Check if it is a mixed cluster
	BOOST_REQUIRE_EQUAL(cluster.isMixed(), true);

	return;
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

/**
 * This operation checks the ability of the HeInterstitialCluster to describe
 * its connectivity to other clusters.
 */
BOOST_AUTO_TEST_CASE(checkConnectivity) {
<<<<<<< HEAD
	shared_ptr<ReactionNetwork> network = getSimplePSIReactionNetwork();

	// Check the reaction connectivity of the HeI cluster
	// with 5He and 3I
	// Get the connectivity array from the reactant
	vector<int> composition = { 5, 0, 3 };
	auto reactant = (PSICluster *) (network->getCompound("HeI", composition));
	// Check the type name
	BOOST_REQUIRE_EQUAL("HeI", reactant->getType());
	auto reactionConnectivity = reactant->getConnectivity();

	BOOST_REQUIRE_EQUAL(reactant->getComposition().at("He"), 5);
	BOOST_REQUIRE_EQUAL(reactant->getComposition().at("I"), 3);

	// Check the connectivity for He, V, and I
	int connectivityExpected[] = {
			// He
			1, 1, 1, 1, 1, 0, 0, 0, 0, 0,

			// V
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0,

			// I
			1, 0, 1, 0, 0, 0, 0, 0, 0, 0,

			// HeV
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

			// HeI
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

			// temperature
			0 };

	for (unsigned int i = 0; i < reactionConnectivity.size(); i++) {
		BOOST_REQUIRE_EQUAL(reactionConnectivity[i], connectivityExpected[i]);
	}

	return;
=======

	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork();
	auto props = network->getProperties();
	
	// Prevent dissociation from being added to the connectivity array
	props["dissociationsEnabled"] = "false";
	
	// Check the reaction connectivity of the HeI cluster
	// with 5He and 3I
	
	{
		// Get the connectivity array from the reactant
		vector<int> composition = {5, 0, 3 };
		auto reactant = (PSICluster *) (network->getCompound("HeI", composition));
		// Check the type name
		BOOST_REQUIRE_EQUAL("HeI",reactant->getType());
		auto reactionConnectivity = reactant->getConnectivity();
		
		BOOST_REQUIRE_EQUAL(reactant->getComposition().at("He"), 5);
		BOOST_REQUIRE_EQUAL(reactant->getComposition().at("I"), 3);
		
		// Check the connectivity for He, V, and I
		
		int connectivityExpected[] = {
			// He
			1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			
			// V
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			
			// I
			// Only single-I clusters react with HeI
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			
			// HeV
			0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0,
			0, 0,
			0,
			
			// HeI
			0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 1, 0, 0, 0,
			0, 0, 0, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0,
			0, 0,
			0
		};

		for (int i = 0; i < reactionConnectivity.size(); i++) {
			BOOST_REQUIRE_EQUAL(reactionConnectivity[i], connectivityExpected[i]);
		}
	}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

/**
 * This operation checks the ability of the HeInterstitialCluster to compute
 * the total flux.
 */
BOOST_AUTO_TEST_CASE(checkTotalFlux) {
<<<<<<< HEAD
	BOOST_TEST_MESSAGE(
			"HeInterstitialClusterTester Message: \n" << "BOOST_AUTO_TEST_CASE(checkTotalFlux): " << "Arbitrary values used because of lack of data!" << "\n");

	// Local Declarations
	auto network = getSimplePSIReactionNetwork();

	// Get an HeI cluster with compostion 1,0,1.
	vector<int> composition = { 1, 0, 1 };
	auto cluster = (PSICluster *) network->getCompound("HeI", composition);
	// Get one that it combines with (I)
	auto secondCluster = (PSICluster *) network->get("I", 1);
	// Set the diffusion factor and migration energy to arbitrary values
	cluster->setDiffusionFactor(1.5E+10);
	cluster->setMigrationEnergy(numeric_limits<double>::infinity());
	cluster->setConcentration(0.5);

	// Set the diffusion factor and migration energy based on the
	// values from the preprocessor
	secondCluster->setDiffusionFactor(2.13E+10);
	secondCluster->setMigrationEnergy(0.013);
	secondCluster->setConcentration(0.5);

	// Compute the rate constants that are needed for the flux
	network->setTemperature(1000.0);
	network->reinitializeNetwork();
	network->computeRateConstants();
	// The flux can pretty much be anything except "not a number" (nan).
	double flux = cluster->getTotalFlux();
	BOOST_TEST_MESSAGE(
			"HeInterstitialClusterTester Message: \n" << "Total Flux is " << flux << "\n" << "   -Production Flux: " << cluster->getProductionFlux() << "\n" << "   -Combination Flux: " << cluster->getCombinationFlux() << "\n" << "   -Dissociation Flux: " << cluster->getDissociationFlux() << "\n" << "   -Emission Flux: " << cluster->getEmissionFlux() << "\n");

	// Check the flux
	BOOST_REQUIRE_CLOSE(-16982855380.0, flux, 0.1);

	return;
}

/**
 * This operation checks the HeInterstitialCluster get*PartialDerivatives methods.
 */
BOOST_AUTO_TEST_CASE(checkPartialDerivatives) {
	// Local Declarations
	// The vector of partial derivatives to compare with
	double knownPartials[] = { 0.0, 3248951483086.9521, 0.0,
			-25873847932.526035, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			-344.9902456, 0.0, 0.0 };
	// Get the simple reaction network
	auto network = getSimplePSIReactionNetwork(3);

	// Get an HeI cluster with compostion 2,0,1.
	vector<int> composition = { 2, 0, 1 };
	auto cluster = (PSICluster *) network->getCompound("HeI", composition);
	// Set the diffusion factor and migration energy to arbitrary values
	cluster->setDiffusionFactor(1.5E+10);
	cluster->setConcentration(0.5);

	// Compute the rate constants that are needed for the partials
	network->setTemperature(1000.0);
	network->reinitializeNetwork();
	network->computeRateConstants();
	// Get the vector of partial derivatives
	auto partials = cluster->getPartialDerivatives();

	// Check the size of the partials
	BOOST_REQUIRE_EQUAL(partials.size(), 16U);

	// Check all the values
	for (unsigned int i = 0; i < partials.size(); i++) {
		BOOST_REQUIRE_CLOSE(partials[i], knownPartials[i], 0.1);
	}

	return;
=======
	BOOST_TEST_MESSAGE("HeInterstitialClusterTester Message: \n"
			  << "BOOST_AUTO_TEST_CASE(checkTotalFlux): "
			  << "Arbitrary values used because of lack of data!"
			  << "\n");

	// Local Declarations
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork();

	// Get an HeI cluster with compostion 1,0,1.
	vector<int> composition = {1, 0, 1};
	auto cluster = (PSICluster *) network->getCompound(
			"HeI",composition);
	// Get one that it combines with (I2)
	auto secondCluster = (PSICluster *) network->get("I", 1);
	// Set the diffusion factor, migration and binding energies to arbitrary
	// values because HeI does not exist in benchmarks
	cluster->setDiffusionFactor(1.5E+10);
 	cluster->setTemperature(1000.0);
	cluster->setMigrationEnergy(numeric_limits<double>::infinity());
	vector<double> energies = {5.09, numeric_limits<double>::infinity(),
			5.09, 12.6};
	cluster->setBindingEnergies(energies);
	cluster->setConcentration(0.5);

	// Set the diffusion factor, migration and binding energies based on the
	// values from the tungsten benchmark for this problem for the second cluster
	secondCluster->setDiffusionFactor(2.13E+10);
	secondCluster->setMigrationEnergy(0.013);
	energies = {numeric_limits<double>::infinity(), numeric_limits<double>::infinity(),
			numeric_limits<double>::infinity(), numeric_limits<double>::infinity()};
	secondCluster->setBindingEnergies(energies);
	secondCluster->setConcentration(0.5);
 	secondCluster->setTemperature(1000.0);
	// The flux can pretty much be anything except "not a number" (nan).
	double flux = cluster->getTotalFlux(1000.0);
	BOOST_TEST_MESSAGE("HeInterstitialClusterTester Message: \n" << "Total Flux is " << flux << "\n"
			  << "   -Production Flux: " << cluster->getProductionFlux(1000.0) << "\n"
			  << "   -Combination Flux: " << cluster->getCombinationFlux(1000.0) << "\n"
			  << "   -Dissociation Flux: " << cluster->getDissociationFlux(1000.0) << "\n");

	// The flux should be nearly zero because the binding energies for all the
	// data that we have are infinite for I1.
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(-4.747e-14, flux,.01);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE_CLOSE(-5958214005696.4355, flux,.01);

	return;
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
}

/**
 * This operation checks the reaction radius for HeInterstitialCluster.
 */
BOOST_AUTO_TEST_CASE(checkReactionRadius) {
<<<<<<< HEAD
	// Create the HeI clsuter
	shared_ptr<HeInterstitialCluster> cluster;

	// The vector of radii to compare with
	double expectedRadii[] = { 0.1372650265, 0.1778340462, 0.2062922619,
			0.2289478080, 0.2480795532 };

	// Check all the values
	for (int i = 1; i <= 5; i++) {
		cluster = shared_ptr<HeInterstitialCluster>(
				new HeInterstitialCluster(1, i, registry));
		BOOST_REQUIRE_CLOSE(expectedRadii[i - 1], cluster->getReactionRadius(),
				0.000001);
	}

	return;
}

=======

	vector<shared_ptr<HeInterstitialCluster>> clusters;
	shared_ptr<HeInterstitialCluster> cluster;
	double expectedRadii[] = { 0.1372650265, 0.1778340462, 0.2062922619,
			0.2289478080, 0.2480795532 };

	for (int i = 1; i <= 5; i++) {
		cluster = shared_ptr<HeInterstitialCluster>(new HeInterstitialCluster(1, i, registry));
		BOOST_REQUIRE_CLOSE(expectedRadii[i - 1], cluster->getReactionRadius(),
				.000001);
	}
}


>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
BOOST_AUTO_TEST_SUITE_END()
