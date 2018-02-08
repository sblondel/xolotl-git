<<<<<<< HEAD
/*
 * PSIClusterTester.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Jay Jay Billings
 */
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSICluster.h>
#include "SimpleReactionNetwork.h"
#include <HeCluster.h>
#include <HeVCluster.h>
#include <memory>
#include <typeinfo>
#include <limits>
#include <algorithm>
#include <math.h>
#include <limits>

using namespace std;
using namespace xolotlCore;
using namespace testUtils;

<<<<<<< HEAD
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>();
=======
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * This suite is responsible for testing the HeVCluster.
 */
BOOST_AUTO_TEST_SUITE(HeVCluster_testSuite)

<<<<<<< HEAD

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
BOOST_AUTO_TEST_CASE(getSpeciesSize) {
	HeVCluster cluster(4, 5, registry);

	// Get the composition back
	auto composition = cluster.getComposition();

	// Check the composition is the created one
	BOOST_REQUIRE_EQUAL(composition["He"], 4);
	BOOST_REQUIRE_EQUAL(composition["V"], 5);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);

	// Check if it is a mixed cluster
	BOOST_REQUIRE_EQUAL(cluster.isMixed(), true);

	return;
}

/**
 * This operation checks the ability of the HeVCluster to describe
 * its connectivity to other clusters.
 */
BOOST_AUTO_TEST_CASE(checkConnectivity) {
<<<<<<< HEAD
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork();
	auto props = network->getProperties();
	
	// Prevent dissociation from being added to the connectivity array
	props["dissociationsEnabled"] = "false";
	
	// Check the reaction connectivity of the HeV cluster
	// with 3He and 2V
	// Get the connectivity array from the reactant
	vector<int> composition = {3, 2, 0 };
	auto reactant = (PSICluster *) network->getCompound("HeV", composition);
	
	// Check the type name
	BOOST_REQUIRE_EQUAL("HeV",reactant->getType());
	auto reactionConnectivity = reactant->getConnectivity();
		
	BOOST_REQUIRE_EQUAL(reactant->getComposition().at("He"), 3);
	BOOST_REQUIRE_EQUAL(reactant->getComposition().at("V"), 2);
		
	// Check the connectivity for He, V, and I
	int connectivityExpected[] = {
		// He
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
			
		// V
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			
		// I
		1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
			
		// HeV
		0, 0, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 1,
		0, 0,
		0,
			
		// HeI
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0,
		0, 0,
		0
	};
		
	for (int i = 0; i < reactionConnectivity.size(); i++) {
=======
	shared_ptr<ReactionNetwork> network = getSimplePSIReactionNetwork();

	// Prevent dissociation from being added to the connectivity array
	network->disableDissociations();

	// Check the reaction connectivity of the HeV cluster
	// with 3He and 2V
	// Get the connectivity array from the reactant
	vector<int> composition = { 3, 2, 0 };
	auto reactant = (PSICluster *) network->getCompound("HeV", composition);

	// Check the type name
	BOOST_REQUIRE_EQUAL("HeV", reactant->getType());
	auto reactionConnectivity = reactant->getConnectivity();

	BOOST_REQUIRE_EQUAL(reactant->getComposition().at("He"), 3);
	BOOST_REQUIRE_EQUAL(reactant->getComposition().at("V"), 2);

	// Check the connectivity for He, V, and I
	int connectivityExpected[] = {
			// He
			1, 1, 1, 1, 1, 0, 0, 0, 0, 0,

			// V
			1, 1, 0, 0, 0, 0, 0, 0, 0, 0,

			// I
			1, 1, 1, 1, 1, 0, 0, 0, 0, 0,

			// HeV
			0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
			0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,

			// HeI
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (unsigned int i = 0; i < reactionConnectivity.size(); i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		BOOST_REQUIRE_EQUAL(reactionConnectivity[i], connectivityExpected[i]);
	}

	return;
}

/**
 * This operation checks the ability of the HeVCluster to compute the total flux.
 */
BOOST_AUTO_TEST_CASE(checkTotalFlux) {
	// Local Declarations
<<<<<<< HEAD
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork();

	// Get an HeV cluster with compostion 2,1,0.
	vector<int> composition = {2, 1, 0};
	auto cluster = (PSICluster *) network->getCompound(
			"HeV",composition);
=======
	auto network = getSimplePSIReactionNetwork();

	// Get an HeV cluster with compostion 2,1,0.
	vector<int> composition = { 2, 1, 0 };
	auto cluster = (PSICluster *) network->getCompound("HeV", composition);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get one that it combines with (He)
	auto secondCluster = (PSICluster *) network->get("He", 1);
	// Set the diffusion factor and migration energy based on the
	// values from the preprocessor.
	cluster->setDiffusionFactor(0.0);
	cluster->setMigrationEnergy(numeric_limits<double>::infinity());
<<<<<<< HEAD
	cluster->setTemperature(1000.0);
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	cluster->setConcentration(0.5);

	// Set the diffusion factor and migration energy based on the
	// values from the tungsten benchmark for this problem for the second cluster
	secondCluster->setDiffusionFactor(2.950E+10);
	secondCluster->setMigrationEnergy(0.13);
<<<<<<< HEAD
	secondCluster->setTemperature(1000.0);
	secondCluster->setConcentration(0.5);

 	// Compute the rate constants that are needed for the flux
 	cluster->computeRateConstants();
	// The flux can pretty much be anything except "not a number" (nan).
	double flux = cluster->getTotalFlux();
	BOOST_TEST_MESSAGE("HeVClusterTester Message: \n" << "Total Flux is " << flux << "\n"
			  << "   -Production Flux: " << cluster->getProductionFlux() << "\n"
			  << "   -Combination Flux: " << cluster->getCombinationFlux() << "\n"
			  << "   -Dissociation Flux: " << cluster->getDissociationFlux() << "\n"
	  	  	  << "   -Emission Flux: " << cluster->getEmissionFlux() << "\n");
=======
	secondCluster->setConcentration(0.5);

	// Compute the rate constants that are needed for the flux
	network->setTemperature(1000.0);
	network->reinitializeNetwork();
	network->computeRateConstants();
	// The flux can pretty much be anything except "not a number" (nan).
	double flux = cluster->getTotalFlux();
	BOOST_TEST_MESSAGE(
			"HeVClusterTester Message: \n" << "Total Flux is " << flux << "\n" << "   -Production Flux: " << cluster->getProductionFlux() << "\n" << "   -Combination Flux: " << cluster->getCombinationFlux() << "\n" << "   -Dissociation Flux: " << cluster->getDissociationFlux() << "\n" << "   -Emission Flux: " << cluster->getEmissionFlux() << "\n");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	BOOST_REQUIRE_CLOSE(-1134677704810.4, flux, 0.1);

	return;
}

/**
 * This operation checks the HeVCluster get*PartialDerivatives methods.
 */
BOOST_AUTO_TEST_CASE(checkPartialDerivatives) {
	// Local Declarations
	// The vector of partial derivatives to compare with
<<<<<<< HEAD
	double knownPartials[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 0.0, 0.0};
	// Get the simple reaction network
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork(3);

	// Get an HeV cluster with compostion 2,1,0.
	vector<int> composition = {2, 1, 0};
	auto cluster = (PSICluster *) network->getCompound(
			"HeV",composition);
=======
	double knownPartials[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.854292435040,
			0.0, 0.0, 0.0, -1072.407352511, 0.0, 0.0, 0.0, 0.0 };
	// Get the simple reaction network
	auto network = getSimplePSIReactionNetwork(3);

	// Get an HeV cluster with compostion 2,1,0.
	vector<int> composition = { 2, 1, 0 };
	auto cluster = (PSICluster *) network->getCompound("HeV", composition);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Set the diffusion factor and migration energy based on the
	// values from the tungsten benchmark for this problem.
	cluster->setDiffusionFactor(0.0);
	cluster->setMigrationEnergy(numeric_limits<double>::infinity());
<<<<<<< HEAD
	cluster->setTemperature(1000.0);
	cluster->setConcentration(0.5);

	// Compute the rate constants that are needed for the partial derivatives
	cluster->computeRateConstants();
=======
	cluster->setConcentration(0.5);

	// Compute the rate constants that are needed for the partials
	network->setTemperature(1000.0);
	network->reinitializeNetwork();
	network->computeRateConstants();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get the vector of partial derivatives
	auto partials = cluster->getPartialDerivatives();

	// Check the size of the partials
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(partials.size(), 15);

	// Check all the values
	for (int i = 0; i < partials.size(); i++) {
=======
	BOOST_REQUIRE_EQUAL(partials.size(), 15U);

	// Check all the values
	for (unsigned int i = 0; i < partials.size(); i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		BOOST_REQUIRE_CLOSE(partials[i], knownPartials[i], 0.1);
	}

	return;
}

/**
 * This operation checks the reaction radius for HeVCluster.
 */
BOOST_AUTO_TEST_CASE(checkReactionRadius) {
	// Create the HeV cluster
	shared_ptr<HeVCluster> cluster;

	// The vector of radii to compare with
	double expectedRadii[] = { 0.1372650265, 0.1778340462, 0.2062922619,
			0.2289478080, 0.2480795532 };

	// Check all the values
	for (int i = 1; i <= 5; i++) {
		cluster = shared_ptr<HeVCluster>(new HeVCluster(1, i, registry));
		BOOST_REQUIRE_CLOSE(expectedRadii[i - 1], cluster->getReactionRadius(),
				0.000001);
	}

	return;
}

BOOST_AUTO_TEST_SUITE_END()
