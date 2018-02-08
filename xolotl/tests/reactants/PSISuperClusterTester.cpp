#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSICluster.h>
#include <PSISuperCluster.h>
#include <HDF5NetworkLoader.h>
#include <HeCluster.h>
#include <HeVCluster.h>
#include <XolotlConfig.h>
#include <DummyHandlerRegistry.h>
#include <Constants.h>

using namespace std;
using namespace xolotlCore;

/**
 * This suite is responsible for testing the PSISuperCluster.
 */
BOOST_AUTO_TEST_SUITE(PSISuperCluster_testSuite)

/**
 * This operation checks the ability of the PSISuperCluster to describe
 * its connectivity to other clusters.
 */
BOOST_AUTO_TEST_CASE(checkConnectivity) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive_2D.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);
	// Set grouping parameters
	loader.setVMin(1);
	loader.setHeWidth(4);
	loader.setVWidth(1);

	// Load the network
	auto network = loader.load();

	// Set the temperature in the network
	int networkSize = network->size();
	auto allReactants = network->getAll();
	double temperature = 1000.0;
	for (int i = 0; i < networkSize; i++) {
		// This part will set the temperature in each reactant
		// and recompute the diffusion coefficient
		allReactants->at(i)->setTemperature(temperature);
	}
	network->computeRateConstants();
	// Recompute Ids and network size and redefine the connectivities
	network->reinitializeConnectivities();

	// Check the reaction connectivity of the super cluster
	auto reactant = network->getAll(PSISuperType).at(0);

	// Check the type name
	BOOST_REQUIRE_EQUAL(PSISuperType, reactant->getType());
	auto reactionConnectivity = reactant->getConnectivity();

	// Check the connectivity for He, V, and I
	int connectivityExpected[] = { 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,
			1, 1, 0, 1, 1, 1, 1, 0, 0 };

	for (unsigned int i = 0; i < reactionConnectivity.size(); i++) {
		BOOST_REQUIRE_EQUAL(reactionConnectivity[i], connectivityExpected[i]);
	}

	return;
}

/**
 * This operation checks the ability of the PSISuperCluster to compute the total flux.
 */
BOOST_AUTO_TEST_CASE(checkTotalFlux) {

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive_2D.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);
	// Set grouping parameters
	loader.setVMin(1);
	loader.setHeWidth(4);
	loader.setVWidth(1);

	// Load the network
	auto network = loader.load();

	// Set the temperature in the network
	int networkSize = network->size();
	auto allReactants = network->getAll();
	double temperature = 1000.0;
	for (int i = 0; i < networkSize; i++) {
		// This part will set the temperature in each reactant
		// and recompute the diffusion coefficient
		allReactants->at(i)->setTemperature(temperature);
	}
	network->computeRateConstants();
	// Recompute Ids and network size and redefine the connectivities
	network->reinitializeConnectivities();

	// Check the reaction connectivity of the super cluster
	auto cluster = network->getAll(PSISuperType).at(0);
	// Get one that it combines with (He)
	auto secondCluster = (PSICluster *) network->get(heType, 1);
	// Set the concentrations
	cluster->setConcentration(0.5);
	secondCluster->setConcentration(0.5);

	// Get and check the flux
	double flux = cluster->getTotalFlux();
	BOOST_REQUIRE_CLOSE(0.0, flux, 0.1);

	return;
}

/**
 * This operation checks the PSISuperCluster get*PartialDerivatives methods.
 */
BOOST_AUTO_TEST_CASE(checkPartialDerivatives) {

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive_2D.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);
	// Set grouping parameters
	loader.setVMin(1);
	loader.setHeWidth(4);
	loader.setVWidth(1);

	// Load the network
	auto network = loader.load();

	// Set the temperature in the network
	int networkSize = network->size();
	auto allReactants = network->getAll();
	double temperature = 1000.0;
	for (int i = 0; i < networkSize; i++) {
		// This part will set the temperature in each reactant
		// and recompute the diffusion coefficient
		allReactants->at(i)->setTemperature(temperature);
	}
	network->computeRateConstants();
	// Recompute Ids and network size and redefine the connectivities
	network->reinitializeConnectivities();

	// Check the reaction connectivity of the super cluster
	auto cluster = network->getAll(PSISuperType).at(0);

	// Local Declarations
	// The vector of partial derivatives to compare with
	double knownPartials[] =
			{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
					0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	// Set the concentration
	cluster->setConcentration(0.5);

	// Get the vector of partial derivatives
	auto partials = cluster->getPartialDerivatives();

	// Check the size of the partials
	BOOST_REQUIRE_EQUAL(partials.size(), 24U);

	// Check all the values
	for (unsigned int i = 0; i < partials.size(); i++) {
		BOOST_REQUIRE_CLOSE(partials[i], knownPartials[i], 0.1);
	}

	return;
}

/**
 * This operation checks the reaction radius for PSISuperCluster.
 */
BOOST_AUTO_TEST_CASE(checkReactionRadius) {

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive_2D.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);
	// Set grouping parameters
	loader.setVMin(1);
	loader.setHeWidth(4);
	loader.setVWidth(1);

	// Load the network
	auto network = loader.load();

	// Check the reaction connectivity of the super cluster
	auto cluster = network->getAll(PSISuperType).at(0);

	// Check the radius
	BOOST_REQUIRE_CLOSE(0.137265, cluster->getReactionRadius(), 0.001);

	// Finalize MPI
	MPI_Finalize();

	return;
}

BOOST_AUTO_TEST_SUITE_END()
