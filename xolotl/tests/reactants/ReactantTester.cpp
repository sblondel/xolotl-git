<<<<<<< HEAD
=======
/*
 * PSIClusterTester.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Jay Jay Billings
 */
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
<<<<<<< HEAD
#include <Reactant.h>
=======
#include <PSICluster.h>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include "SimpleReactionNetwork.h"
#include <memory>
#include <typeinfo>
#include <limits>
#include <math.h>

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
 * This suite is responsible for testing the Reactant.
 */BOOST_AUTO_TEST_SUITE(Reactant_testSuite)

<<<<<<< HEAD
BOOST_AUTO_TEST_CASE(checkTemperature) {
	// Create a reactant
	Reactant reactant(registry);
	// Set its temperature
	reactant.setTemperature(1000.0);

	// Check its temperature
	BOOST_REQUIRE_CLOSE(1000.0, reactant.getTemperature(), 0.0001);

	return;
}

BOOST_AUTO_TEST_CASE(checkComposition) {
	// Create a reactant
	Reactant reactant(registry);

	// Check its default composition
	BOOST_REQUIRE_EQUAL(4U, reactant.getComposition().size());

	return;
}

BOOST_AUTO_TEST_CASE(checkPartialDerivatives) {
	// Create a reactant
	Reactant reactant(registry);

	// Create a network and set it
	auto network = make_shared<PSIClusterReactionNetwork>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	reactant.setReactionNetwork(network);

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
	// Create a reference Reactant
	Reactant reactant(registry);
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

	// Try cloning the Reactant
	auto reactantClone = reactant.clone();

	BOOST_REQUIRE_CLOSE(10.0, reactantClone->getConcentration(), 1.0e-7);

	return;
}

BOOST_AUTO_TEST_CASE(checkConcentration) {
	// Create a Reactant
	Reactant reactant(registry);
	reactant.setConcentration(1.0);

	// Make sure it was set correctly
	BOOST_REQUIRE_EQUAL(1.0, reactant.getConcentration());

	// Make sure the base class getTotalFlux returns 0 for now
	BOOST_REQUIRE_EQUAL(0.0, reactant.getTotalFlux());

	return;
=======
/**
 * This operation checks the ability to set the temperature
 */
BOOST_AUTO_TEST_CASE(checkTemperature) {
	Reactant reactant(registry);
	reactant.setTemperature(1000.0);
	BOOST_REQUIRE_CLOSE(1000.0, reactant.getTemperature(),0.0001);
}

/**
 * This operation asserts that the default composition is empty.
 */
BOOST_AUTO_TEST_CASE(checkComposition) {
	Reactant reactant(registry);
	BOOST_REQUIRE_EQUAL(0, reactant.getComposition().size());
}

/**
 * This operation tests the copy constructor.
 */BOOST_AUTO_TEST_CASE(checkCopying) {

	// Create a reference Reactant
	Reactant reactant(registry);
	reactant.setId(5);
	reactant.setConcentration(10.0);
	reactant.setTemperature(5.0);

	// Copy the Reactant
	Reactant reactantCopy(reactant);

	// Check the ids and names
	BOOST_REQUIRE_EQUAL(reactant.getId(), reactantCopy.getId());
	BOOST_REQUIRE_EQUAL(reactant.getName(), reactantCopy.getName());
	BOOST_REQUIRE_CLOSE(5.0,reactant.getTemperature(),0.0001);

	// Increase the concentration
	reactantCopy.increaseConcentration(5.0);

	// The values should now be different,
	// so check them against the known values
	BOOST_REQUIRE_CLOSE(reactant.getConcentration(), 10.0, 1e-7);
	BOOST_REQUIRE_CLOSE(reactantCopy.getConcentration(), 15.0, 1e-7);

	// Try cloning the Reactant
	auto reactantClone = reactant.clone();
	BOOST_REQUIRE_CLOSE(10.0, reactantClone->getConcentration(), 1e-7);
}

/**
 * This operation insures that the concentration can be manipulated
 * appropriately.
 */BOOST_AUTO_TEST_CASE(checkConcentration) {

	// Create a Reactant
	Reactant reactant(registry);
	reactant.setConcentration(1.0);

	// Make sure it was set correctly
	BOOST_REQUIRE_EQUAL(1.0, reactant.getConcentration());

	// Increase it
	reactant.increaseConcentration(3.3);

	// Make sure its correct
	BOOST_REQUIRE_EQUAL(4.3, reactant.getConcentration());

	// Decrease it
	reactant.decreaseConcentration(1.3);

	// Make sure its correct
	BOOST_REQUIRE_EQUAL(3.0, reactant.getConcentration());

	// Zero it
	reactant.zero();

	// Check it was zeroed
	BOOST_REQUIRE_EQUAL(0.0, reactant.getConcentration());

	// Make sure the base class getTotalFlux returns 0 for now
	BOOST_REQUIRE_EQUAL(0.0, reactant.getTotalFlux(0.0));

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

BOOST_AUTO_TEST_CASE(checkIsConnected) {
	// Create a reaction network containing only clusters with maximum size 2
<<<<<<< HEAD
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
=======
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork(2);

	// Check the connectivity matrix (8 * 8)
	int connectivityExpected[8][8] = {
			{1, 1, 1, 0, 1, 0, 1, 1}, // He
			{1, 1, 0, 0, 0, 0, 0, 0}, // He_2
			{1, 0, 1, 1, 1, 1, 1, 0}, // V
			{0, 0, 1, 1, 1, 0, 0, 0}, // V_2
			{1, 0, 1, 1, 1, 1, 0, 1}, // I
			{0, 0, 1, 0, 1, 1, 0, 0}, // I_2
			{0, 0, 0, 0, 0, 0, 1, 0}, // HeV
			{0, 0, 0, 0, 0, 0, 0, 1}  // HeI
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	};

	// Check He
	auto reactantConnectivity = network->get("He", 1)->getConnectivity();
	for (int j = 0; j < 8; j++) {
<<<<<<< HEAD
		BOOST_REQUIRE_EQUAL(connectivityExpected[0][j],
				reactantConnectivity[j]);
=======
		BOOST_REQUIRE_EQUAL(connectivityExpected[0][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Check He_2
	reactantConnectivity = network->get("He", 2)->getConnectivity();
	for (int j = 0; j < 8; j++) {
<<<<<<< HEAD
		BOOST_REQUIRE_EQUAL(connectivityExpected[1][j],
				reactantConnectivity[j]);
=======
		BOOST_REQUIRE_EQUAL(connectivityExpected[1][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Check V
	reactantConnectivity = network->get("V", 1)->getConnectivity();
	for (int j = 0; j < 8; j++) {
<<<<<<< HEAD
		BOOST_REQUIRE_EQUAL(connectivityExpected[2][j],
				reactantConnectivity[j]);
=======
		BOOST_REQUIRE_EQUAL(connectivityExpected[2][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Check V_2
	reactantConnectivity = network->get("V", 2)->getConnectivity();
	for (int j = 0; j < 8; j++) {
<<<<<<< HEAD
		BOOST_REQUIRE_EQUAL(connectivityExpected[3][j],
				reactantConnectivity[j]);
=======
		BOOST_REQUIRE_EQUAL(connectivityExpected[3][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Check I
	reactantConnectivity = network->get("I", 1)->getConnectivity();
	for (int j = 0; j < 8; j++) {
<<<<<<< HEAD
		BOOST_REQUIRE_EQUAL(connectivityExpected[4][j],
				reactantConnectivity[j]);
=======
		BOOST_REQUIRE_EQUAL(connectivityExpected[4][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Check I_2
	reactantConnectivity = network->get("I", 2)->getConnectivity();
	for (int j = 0; j < 8; j++) {
<<<<<<< HEAD
		BOOST_REQUIRE_EQUAL(connectivityExpected[5][j],
				reactantConnectivity[j]);
	}

	// Check HeV
	std::vector<int> compositionVector = { 1, 1, 0 };
	reactantConnectivity =
			network->getCompound("HeV", compositionVector)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[6][j],
				reactantConnectivity[j]);
=======
		BOOST_REQUIRE_EQUAL(connectivityExpected[5][j],reactantConnectivity[j]);
	}

	// Check HeV
	std::vector<int> compositionVector = {1,1,0};
	reactantConnectivity = network->getCompound("HeV", compositionVector)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[6][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// Check HeI
	compositionVector = {1,0,1};
<<<<<<< HEAD
	reactantConnectivity =
			network->getCompound("HeI", compositionVector)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[7][j],
				reactantConnectivity[j]);
=======
	reactantConnectivity = network->getCompound("HeI", compositionVector)->getConnectivity();
	for (int j = 0; j < 8; j++) {
		BOOST_REQUIRE_EQUAL(connectivityExpected[7][j],reactantConnectivity[j]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	return;
}
<<<<<<< HEAD

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
BOOST_AUTO_TEST_SUITE_END()
