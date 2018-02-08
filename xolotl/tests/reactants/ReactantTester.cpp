#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <Reactant.h>
#include "SimpleReactionNetwork.h"
#include <memory>
#include <typeinfo>
#include <limits>
#include <math.h>

using namespace std;
using namespace xolotlCore;
using namespace testUtils;

static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();

/**
 * This suite is responsible for testing the Reactant.
 */BOOST_AUTO_TEST_SUITE(Reactant_testSuite)

BOOST_AUTO_TEST_CASE(checkTemperature) {
<<<<<<< HEAD
	// Create a reactant
	Reactant reactant(registry);
=======
	// Get the simple reaction network
	auto network = getSimplePSIReactionNetwork(0);
	// Create a reactant
	Reactant reactant(*(network.get()), registry);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Set its temperature
	reactant.setTemperature(1000.0);

	// Check its temperature
	BOOST_REQUIRE_CLOSE(1000.0, reactant.getTemperature(), 0.0001);

	return;
}

BOOST_AUTO_TEST_CASE(checkComposition) {
<<<<<<< HEAD
	// Create a reactant
	Reactant reactant(registry);
=======
	// Get the simple reaction network
	auto network = getSimplePSIReactionNetwork(0);
	// Create a reactant
	Reactant reactant(*(network.get()), registry);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Check its default composition
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(4U, reactant.getComposition().size());
=======
	BOOST_REQUIRE_EQUAL(6U, reactant.getComposition().size());
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

	return;
}

BOOST_AUTO_TEST_CASE(checkPartialDerivatives) {
<<<<<<< HEAD
	// Create a reactant
	Reactant reactant(registry);

	// Create a network and set it
	auto network = make_shared<PSIClusterReactionNetwork>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	reactant.setReactionNetwork(network);
=======
	// Create a network
	auto network = make_shared<PSIClusterReactionNetwork>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Create a reactant
	Reactant reactant(*(network.get()), registry);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Check its default partial derivatives
	BOOST_REQUIRE_EQUAL(1U, reactant.getPartialDerivatives().size());

	// Create a reference and temp partial derivative vector
	std::vector<double> refPartials = std::vector<double>(3, 0.0);
	std::vector<double> tempPartials = std::vector<double>(3, 0.0);

	reactant.getPartialDerivatives(tempPartials);

	// Compare to the refence one
	BOOST_REQUIRE_EQUAL(tempPartials[0], refPartials[0]);
	BOOST_REQUIRE_EQUAL(tempPartials[1], refPartials[1]);
	BOOST_REQUIRE_EQUAL(tempPartials[2], refPartials[2]);

	return;
}

BOOST_AUTO_TEST_CASE(checkCopying) {
<<<<<<< HEAD
	// Create a reference Reactant
	Reactant reactant(registry);
=======
	// Get the simple reaction network
	auto network = getSimplePSIReactionNetwork(0);
	// Create a reference reactant
	Reactant reactant(*(network.get()), registry);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	reactant.setId(5);
	reactant.setConcentration(10.0);
	reactant.setTemperature(5.0);

	// Copy the Reactant
	Reactant reactantCopy(reactant);

	// Check the ids and names
	BOOST_REQUIRE_EQUAL(reactant.getId(), reactantCopy.getId());
	BOOST_REQUIRE_EQUAL(reactant.getName(), reactantCopy.getName());
	BOOST_REQUIRE_CLOSE(5.0, reactant.getTemperature(), 0.0001);

	// Increase the concentration
	reactantCopy.setConcentration(15.0);

	// The values should now be different,
	// so check them against the known values
	BOOST_REQUIRE_CLOSE(reactant.getConcentration(), 10.0, 1.0e-7);
	BOOST_REQUIRE_CLOSE(reactantCopy.getConcentration(), 15.0, 1.0e-7);

<<<<<<< HEAD
	// Try cloning the Reactant
	auto reactantClone = reactant.clone();

	BOOST_REQUIRE_CLOSE(10.0, reactantClone->getConcentration(), 1.0e-7);

=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	return;
}

BOOST_AUTO_TEST_CASE(checkConcentration) {
<<<<<<< HEAD
	// Create a Reactant
	Reactant reactant(registry);
=======
	// Get the simple reaction network
	auto network = getSimplePSIReactionNetwork(0);
	// Create a reactant
	Reactant reactant(*(network.get()), registry);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	reactant.setConcentration(1.0);

	// Make sure it was set correctly
	BOOST_REQUIRE_EQUAL(1.0, reactant.getConcentration());

	// Make sure the base class getTotalFlux returns 0 for now
	BOOST_REQUIRE_EQUAL(0.0, reactant.getTotalFlux());

	return;
}

<<<<<<< HEAD
BOOST_AUTO_TEST_CASE(checkIsConnected) {
	// Create a reaction network containing only clusters with maximum size 2
	shared_ptr<ReactionNetwork> network = getSimplePSIReactionNetwork(2);

	// Check the connectivity matrix (8 * 8)
	int connectivityExpected[8][8] = { { 1, 1, 1, 0, 1, 0, 1, 1 }, // He
			{ 1, 1, 0, 0, 0, 0, 0, 0 }, // He_2
			{ 1, 0, 1, 1, 1, 1, 1, 1 }, // V
			{ 0, 0, 1, 1, 1, 1, 0, 0 }, // V_2
			{ 1, 0, 1, 1, 1, 1, 1, 0 }, // I
			{ 0, 0, 1, 1, 1, 1, 0, 0 }, // I_2
			{ 1, 0, 1, 0, 1, 0, 1, 0 }, // HeV
			{ 1, 0, 1, 0, 1, 0, 0, 1 }  // HeI
	};

	// Check He
	auto reactantConnectivity = network->get("He", 1)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[0][j],
				reactantConnectivity[j]);
	}

	// Check He_2
	reactantConnectivity = network->get("He", 2)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[1][j],
				reactantConnectivity[j]);
	}

	// Check V
	reactantConnectivity = network->get("V", 1)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[2][j],
				reactantConnectivity[j]);
	}

	// Check V_2
	reactantConnectivity = network->get("V", 2)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[3][j],
				reactantConnectivity[j]);
	}

	// Check I
	reactantConnectivity = network->get("I", 1)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[4][j],
				reactantConnectivity[j]);
	}

	// Check I_2
	reactantConnectivity = network->get("I", 2)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[5][j],
				reactantConnectivity[j]);
	}

	// Check HeV
<<<<<<< HEAD
	std::vector<int> compositionVector = { 1, 1, 0 };
=======
	std::vector<int> compositionVector = { 1, -1 };
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	reactantConnectivity =
			network->getCompound("HeV", compositionVector)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[6][j],
				reactantConnectivity[j]);
	}

	// Check HeI
<<<<<<< HEAD
	compositionVector = {1,0,1};
=======
	compositionVector = {1, 1};
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	reactantConnectivity =
			network->getCompound("HeI", compositionVector)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[7][j],
				reactantConnectivity[j]);
	}

	return;
}

=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
BOOST_AUTO_TEST_SUITE_END()
