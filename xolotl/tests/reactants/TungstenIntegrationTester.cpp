#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSIClusterNetworkLoader.h>
#include <memory>
#include <typeinfo>
#include <limits>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <PSIClusterNetworkLoader.h>
#include <PSIClusterReactionNetwork.h>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include <PSIClusterNetworkLoader.h>
#include <PSIClusterReactionNetwork.h>
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include <XolotlConfig.h>
#include <DummyHandlerRegistry.h>

using namespace std;
using namespace xolotlCore;

/**
 * The test suite configuration
<<<<<<< HEAD
<<<<<<< HEAD
 */
BOOST_AUTO_TEST_SUITE (TungstenIntegrationTester_testSuite)
=======
 */BOOST_AUTO_TEST_SUITE (TungstenIntegrationTester_testSuite)
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
 */BOOST_AUTO_TEST_SUITE (TungstenIntegrationTester_testSuite)
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

/**
 * I just noticed that there is no unit test for checking the partial
 * derivatives computed by Xolotl. I think I did this because there is no good
 * way to unit test them other than computing them and then sticking that array
 * in for a direct comparison. Ideally there would be some analytic version to
 * which we could compare.
 *
 * The simplest way to test these is to use PETSc’s -snes_type test option and
 * grep/diff the output.
 *
 * I just modified the test below to checks the convenience method I added to
 * get the partials in a pre-allocated array against the original. They should
 * give the same results.
 *
 * ~JJB 20140525 10:19
 *
 */

/**
 * This operation checks the fluxs from the reactant as best as is possible
 * given that it requires external data.
 */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
BOOST_AUTO_TEST_CASE(checkGetReactantFluxesAndParials) {
	// Local Declarations
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten.txt");
=======
BOOST_AUTO_TEST_CASE(checkGetReactantFluxes) {
=======
BOOST_AUTO_TEST_CASE(checkGetReactantFluxesAndParials) {
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
	// Local Declarations
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/reactants/testfiles/tungsten.txt");
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
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
<<<<<<< HEAD
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
		// Get the partials using method 1
		auto partials = reactant->getPartialDerivatives();
		// Get the partials using method 2
		reactant->getPartialDerivatives(secondPartials);
		// Compare the two arrays of partial derivatives
		for (int j = 0; j < size; ++j) {
			BOOST_REQUIRE_CLOSE(partials[j], secondPartials[j], 1.0);
		}
		// Zero the partials array
		std::fill(secondPartials.begin(), secondPartials.end(), 0.0);
	}

	return;
}

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
=======
BOOST_AUTO_TEST_CASE(checkGetReactantFluxesAndParials) {
	// Local Declarations
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/reactants/testfiles/tungsten.txt");
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
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
<<<<<<< HEAD
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
		reactant->setConcentration(0.001);
	}

	// Get He_1
	auto reactant = (PSICluster *) allReactants->at(0);
	// Its partial derivatives
	auto partials = reactant->getPartialDerivatives();

	// Check the values of the partial derivatives
	BOOST_REQUIRE_CLOSE(partials[0], -2.0, 0.1);
	BOOST_REQUIRE_CLOSE(partials[1], 1.0, 0.1);

	// Get He_2
	reactant = (PSICluster *) allReactants->at(1);
	// Its partial derivatives
	partials = reactant->getPartialDerivatives();

	// Check the values of the partial derivatives
	BOOST_REQUIRE_CLOSE(partials[0], 1.0, 0.1);
	BOOST_REQUIRE_CLOSE(partials[1], -0.5, 0.1);

	return;
}

=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	shared_ptr<ReactionNetwork> network = networkLoader->load();

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: Network loaded");

	// Get everything from the network and set the temperature
	double temperature = 1000.0;
	int nReactants = network->size();
	auto reactants = network->getAll();
	network->setTemperature(temperature);

	BOOST_TEST_MESSAGE("TungstenIntegrationTester Message: "
			<< "Size of the network is: "
			<< nReactants);

	// Create an array to test the second partial derivative routine.
	auto secondPartials = std::vector<double>(nReactants,0.0);

	BOOST_TEST_MESSAGE("Check partial derivatives.");
	for (int i = 0; i < nReactants; ++i) {
		auto reactant = (PSICluster *) reactants->at(i);
		double flux = reactant->getTotalFlux(temperature);
		// Get the partials using method 1
		auto partials = reactant->getPartialDerivatives(temperature);
		// Get the partials using method 2
		reactant->getPartialDerivatives(temperature,secondPartials);
		// Compare the two arrays of partial derivatives
		for (int j = 0; j < nReactants; ++j) {
			BOOST_REQUIRE_CLOSE(partials[j],secondPartials[j],temperature);
		}
		// Zero the partials array
		std::fill(secondPartials.begin(),secondPartials.end(),0.0);
	}

}
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
BOOST_AUTO_TEST_SUITE_END()
