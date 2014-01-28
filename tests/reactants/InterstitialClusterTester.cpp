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
#include <InterstitialCluster.h>
#include "SimpleReactionNetwork.h"
#include <memory>
#include <typeinfo>
#include <limits>
#include <algorithm>

using namespace std;
using namespace xolotlCore;
using namespace testUtils;

/**
 * This operation writes information about the cluster to stdout
 * @param cluster The cluster to dump
 */
void writeCluster(shared_ptr<Reactant> cluster) {
	shared_ptr<PSICluster> psiCluster = static_pointer_cast < PSICluster
			> (cluster);
	BOOST_TEST_MESSAGE(psiCluster->getSize());
	return;
}

/**
 * This suite is responsible for testing the InterstitialCluster.
 */BOOST_AUTO_TEST_SUITE(InterstitialCluster_testSuite)

/**
 * This operation checks the ability of the InterstitialCluster to describe
 * its connectivity to other clusters.
 */
BOOST_AUTO_TEST_CASE(checkConnectivity) {
	
	shared_ptr<ReactionNetwork> network = testUtils::getSimpleReactionNetwork();
	auto reactants = network->getAll();
	auto props = network->getProperties();
	
	// Prevent dissociation from being added to the connectivity array
	props["dissociationsEnabled"] = "false";
	
	// Check the reaction connectivity of the 4th interstitial cluster (4I)
	
	{
		// Get the connectivity array from the reactant
		auto reactant = std::dynamic_pointer_cast < PSICluster
				> (network->get("I", 4));
		auto reactionConnectivity = reactant->getConnectivity();
		
		// Check the connectivity for He, V, and I
		
		int connectivityExpected[] = {
			// He
			1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
			
			// V
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			
			// I
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			
			// HeV
			1, 1, 1, 1, 1, 0, 0, 0, 0,
			1, 1, 1, 1, 0, 0, 0, 0,
			1, 1, 1, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0,
			1, 1, 1, 1, 1,
			1, 1, 1, 1,
			1, 1, 1,
			1, 1,
			1,
			
			// HeI
			// Only a single-Interstitial cluster can react with a HeI cluster
			0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 1, 1, 1,
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
}

/**
 * This operation checks the reaction radius for InterstitialCluster.
 */
BOOST_AUTO_TEST_CASE(checkReactionRadius) {

	std::vector<std::shared_ptr<InterstitialCluster>> clusters;
	std::shared_ptr<InterstitialCluster> cluster;
	double expectedRadii[] = { 0.1578547805, 0.1984238001, 0.2268820159,
			0.2495375620, 0.2686693072, 0.2853926671, 0.3003469838,
			0.3139368664, 0.3264365165, 0.3380413550 };

	for (int i = 1; i <= 10; i++) {
		cluster = std::shared_ptr<InterstitialCluster>(
				new InterstitialCluster(i));
		BOOST_CHECK_CLOSE(expectedRadii[i - 1], cluster->getReactionRadius(),
				.000001);
	}
}

BOOST_AUTO_TEST_SUITE_END()