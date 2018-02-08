#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSIClusterNetworkLoader.h>
#include <memory>
#include <typeinfo>
#include <limits>
<<<<<<< HEAD
#include <PSIClusterNetworkLoader.h>
#include <PSIClusterReactionNetwork.h>
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <XolotlConfig.h>
#include <DummyHandlerRegistry.h>

using namespace std;
using namespace xolotlCore;

/**
 * The test suite configuration
 */
BOOST_AUTO_TEST_SUITE (TungstenIntegrationTester_testSuite)

/**
 * This operation checks the fluxs from the reactant as best as is possible
 * given that it requires external data.
 */
BOOST_AUTO_TEST_CASE(checkGetReactantFluxesAndParials) {
	// Local Declarations
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten.txt");
	string networkFilename = sourceDir + pathToFile;

	BOOST_TEST_MESSAGE(
			"TungstenIntegrationTester Message: Network filename is: " << networkFilename);

	// Load the input file from the master task
<<<<<<< HEAD
	shared_ptr<istream> networkStream = make_shared < ifstream
			> (networkFilename);

	// Create a network loader and set the istream on every MPI task
	shared_ptr<PSIClusterNetworkLoader> networkLoader = make_shared
			< PSIClusterNetworkLoader
			> (std::make_shared<xolotlPerf::DummyHandlerRegistry>());
	networkLoader->setInputstream(networkStream);
	// Load the network
	shared_ptr<ReactionNetwork> network = networkLoader->load();

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: Network loaded");

	// Get everything from the network and set the temperature
	double temperature = 1000.0;
	int nReactants = network->size();
	auto reactants = network->getAll();
	network->setTemperature(temperature);

	// Initialize all the concentrations to 0.001;
	for (int i = 0; i < nReactants; ++i) {
		auto reactant = (PSICluster *) reactants->at(i);
		reactant->setConcentration(0.001);
	}

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: "
			<< "Size of the network is: "
			<< nReactants);

	// Create an array to test the second partial derivative routine.
	auto secondPartials = std::vector<double>(nReactants, 0.0);

	BOOST_TEST_MESSAGE("Check partial derivatives.");
	for (int i = 0; i < nReactants; ++i) {
		auto reactant = (PSICluster *) reactants->at(i);
=======
	shared_ptr<istream> networkStream = make_shared<ifstream>(networkFilename);

	// Create a network loader and set the istream on every MPI task
	shared_ptr<PSIClusterNetworkLoader> networkLoader = make_shared<
			PSIClusterNetworkLoader>(
			std::make_shared<xolotlPerf::DummyHandlerRegistry>());
	networkLoader->setInputstream(networkStream);
	// Load the network
	auto network = networkLoader->load();

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: Network loaded");

	// Get all the reactants
	auto allReactants = network->getAll();
	// Get the network size
	const int size = network->size();
	// Set the temperature
	double temperature = 1000.0;
	network->setTemperature(temperature);
	network->computeRateConstants();

	// Initialize all the concentrations to 0.001;
	for (int i = 0; i < size; ++i) {
		auto reactant = (PSICluster *) allReactants->at(i);
		reactant->setConcentration(0.001);
	}

	BOOST_TEST_MESSAGE(
			"TungstenIntegrationTester Message: " << "Size of the network is: " << size);

	// Create an array to test the second partial derivative routine.
	auto secondPartials = std::vector<double>(size, 0.0);

	BOOST_TEST_MESSAGE("Check partial derivatives.");
	for (int i = 0; i < size; ++i) {
		auto reactant = (PSICluster *) allReactants->at(i);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Get the partials using method 1
		auto partials = reactant->getPartialDerivatives();
		// Get the partials using method 2
		reactant->getPartialDerivatives(secondPartials);
		// Compare the two arrays of partial derivatives
<<<<<<< HEAD
		for (int j = 0; j < nReactants; ++j) {
			BOOST_REQUIRE_CLOSE(partials[j],secondPartials[j],1.0);
		}
		// Zero the partials array
		std::fill(secondPartials.begin(),secondPartials.end(),0.0);
=======
		for (int j = 0; j < size; ++j) {
			BOOST_REQUIRE_CLOSE(partials[j], secondPartials[j], 1.0);
		}
		// Zero the partials array
		std::fill(secondPartials.begin(), secondPartials.end(), 0.0);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

<<<<<<< HEAD
 /**
  * This operation checks the partial derivatives for the production
  * He_1 + He_1 --> He_2
  * and the dissociation
  * He_2 --> He_1 + He_1
  */
 BOOST_AUTO_TEST_CASE(checkSingleReaction) {
 	// Local Declarations
 	string sourceDir(XolotlSourceDirectory);
 	// This file contains specific values to obtain round numbers for the partial derivatives
 	string pathToFile("/tests/testfiles/single_reaction.txt");
 	string networkFilename = sourceDir + pathToFile;

 	BOOST_TEST_MESSAGE(
 			"TungstenIntegrationTester Message: Network filename is: " << networkFilename);

	// Load the input file from the master task
	shared_ptr<istream> networkStream = make_shared < ifstream
			> (networkFilename);

	// Create a network loader and set the istream on every MPI task
	shared_ptr<PSIClusterNetworkLoader> networkLoader = make_shared
			< PSIClusterNetworkLoader
			> (std::make_shared<xolotlPerf::DummyHandlerRegistry>());
	networkLoader->setInputstream(networkStream);
	// Load the network
	shared_ptr<ReactionNetwork> network = networkLoader->load();

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: Network loaded");

	// Get everything from the network and set the temperature
	double temperature = 1000.0;
	int nReactants = network->size();
	auto reactants = network->getAll();
	network->setTemperature(temperature);

	// Initialize all the concentrations to 0.001;
	for (int i = 0; i < nReactants; ++i) {
		auto reactant = (PSICluster *) reactants->at(i);
=======
/**
 * This operation checks the partial derivatives for the production
 * He_1 + He_1 --> He_2
 * and the dissociation
 * He_2 --> He_1 + He_1
 */
BOOST_AUTO_TEST_CASE(checkSingleReaction) {
	// Local Declarations
	string sourceDir(XolotlSourceDirectory);
	// This file contains specific values to obtain round numbers for the partial derivatives
	string pathToFile("/tests/testfiles/single_reaction.txt");
	string networkFilename = sourceDir + pathToFile;

	BOOST_TEST_MESSAGE(
			"TungstenIntegrationTester Message: Network filename is: " << networkFilename);

	// Load the input file from the master task
	shared_ptr<istream> networkStream = make_shared<ifstream>(networkFilename);

	// Create a network loader and set the istream on every MPI task
	shared_ptr<PSIClusterNetworkLoader> networkLoader = make_shared<
			PSIClusterNetworkLoader>(
			std::make_shared<xolotlPerf::DummyHandlerRegistry>());
	networkLoader->setInputstream(networkStream);
	// Load the network
	auto network = networkLoader->load();

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: Network loaded");

	// Get all the reactants
	auto allReactants = network->getAll();
	// Get the network size
	const int size = network->size();
	// Set the temperature
	double temperature = 1000.0;
	// Initialize the rate constants
	network->setTemperature(temperature);
	network->computeRateConstants();

	// Initialize all the concentrations to 0.001;
	for (int i = 0; i < size; ++i) {
		auto reactant = (PSICluster *) allReactants->at(i);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		reactant->setConcentration(0.001);
	}

	// Get He_1
<<<<<<< HEAD
	auto reactant = (PSICluster *) reactants->at(0);
=======
	auto reactant = (PSICluster *) allReactants->at(0);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Its partial derivatives
	auto partials = reactant->getPartialDerivatives();

	// Check the values of the partial derivatives
	BOOST_REQUIRE_CLOSE(partials[0], -2.0, 0.1);
	BOOST_REQUIRE_CLOSE(partials[1], 1.0, 0.1);

	// Get He_2
<<<<<<< HEAD
	reactant = (PSICluster *) reactants->at(1);
=======
	reactant = (PSICluster *) allReactants->at(1);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Its partial derivatives
	partials = reactant->getPartialDerivatives();

	// Check the values of the partial derivatives
	BOOST_REQUIRE_CLOSE(partials[0], 1.0, 0.1);
	BOOST_REQUIRE_CLOSE(partials[1], -0.5, 0.1);

	return;
}

BOOST_AUTO_TEST_SUITE_END()
