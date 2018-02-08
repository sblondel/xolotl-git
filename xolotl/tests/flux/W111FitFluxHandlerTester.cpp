#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include "W111FitFluxHandler.h"
#include <mpi.h>
#include <HDF5NetworkLoader.h>
#include <DummyHandlerRegistry.h>
#include <XolotlConfig.h>
<<<<<<< HEAD
=======
#include <Options.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

using namespace std;
using namespace xolotlCore;

/**
 * The test suite is responsible for testing the W111FitFluxHandler.
 */
BOOST_AUTO_TEST_SUITE (W111FitFluxHandlerTester_testSuite)

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

<<<<<<< HEAD
	// Load the network
	auto network = loader.load().get();
=======
	// Create the options needed to load the network
	Options opts;
	// Load the network
	auto network = loader.load(opts);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Get its size
	const int dof = network->getDOF();

	// Create a grid
	std::vector<double> grid;
	for (int l = 0; l < 7; l++) {
		grid.push_back((double) l * 1.25);
	}
	// Specify the surface position
	int surfacePos = 0;

	// Create the W111 flux handler
	auto testFitFlux = make_shared<W111FitFluxHandler>();
	// Set the flux amplitude
	testFitFlux->setFluxAmplitude(1.0);
	// Initialize the flux handler
<<<<<<< HEAD
	testFitFlux->initializeFluxHandler(network, surfacePos, grid);
=======
	testFitFlux->initializeFluxHandler(*network, surfacePos, grid);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
<<<<<<< HEAD
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 1, surfacePos);
	updatedConcOffset = updatedConc + 2 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 2, surfacePos);
	updatedConcOffset = updatedConc + 3 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 3, surfacePos);
=======
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 1,
			surfacePos);
	updatedConcOffset = updatedConc + 2 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 2,
			surfacePos);
	updatedConcOffset = updatedConc + 3 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 3,
			surfacePos);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(newConcentration[10], 0.391408, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[20], 0.268688, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[30], 0.139904, 0.01);

	// Finalize MPI
	MPI_Finalize();

	return;
}

BOOST_AUTO_TEST_SUITE_END()
