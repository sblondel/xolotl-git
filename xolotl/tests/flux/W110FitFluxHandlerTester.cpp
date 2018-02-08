#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include "W110FitFluxHandler.h"
#include <mpi.h>
#include <HDF5NetworkLoader.h>
#include <DummyHandlerRegistry.h>
#include <XolotlConfig.h>

using namespace std;
using namespace xolotlCore;

/**
 * The test suite is responsible for testing the W110FitFluxHandler.
 */
BOOST_AUTO_TEST_SUITE (W110FitFluxHandlerTester_testSuite)

BOOST_AUTO_TEST_CASE(checkComputeIncidentFlux) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
	auto network = loader.load().get();
	// Get its size
	const int dof = network->getDOF();

	// Create a grid
	std::vector<double> grid;
	for (int l = 0; l < 5; l++) {
		grid.push_back((double) l * 1.25);
	}
	// Specify the surface position
	int surfacePos = 0;

	// Create the W110 flux handler
	auto testFitFlux = make_shared<W110FitFluxHandler>();
	// Set the flux amplitude
	testFitFlux->setFluxAmplitude(1.0);
	// Initialize the flux handler
	testFitFlux->initializeFluxHandler(network, surfacePos, grid);

	// Create a time
	double currTime = 1.0;

	// The array of concentration
	double newConcentration[5 * dof];

	// Initialize their values
	for (int i = 0; i < 5 * dof; i++) {
		newConcentration[i] = 0.0;
	}

	// The pointer to the grid point we want
	double *updatedConc = &newConcentration[0];
	double *updatedConcOffset = updatedConc + dof;

	// Update the concentrations at some grid points
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 1, surfacePos);
	updatedConcOffset = updatedConc + 2 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 2, surfacePos);
	updatedConcOffset = updatedConc + 3 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 3, surfacePos);

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(newConcentration[9], 0.524627, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[18], 0.211160, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[27], 0.064213, 0.01);

	// Finalize MPI
	MPI_Finalize();

	return;
}

BOOST_AUTO_TEST_SUITE_END()
