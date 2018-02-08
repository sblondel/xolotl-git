#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
<<<<<<< HEAD
#include <W100FitFluxHandler.h>
#include <HDF5NetworkLoader.h>
#include <XolotlConfig.h>
#include <DummyHandlerRegistry.h>
#include <mpi.h>
=======
#include "W100FitFluxHandler.h"
#include <mpi.h>
#include <HDF5NetworkLoader.h>
#include <DummyHandlerRegistry.h>
#include <XolotlConfig.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

using namespace std;
using namespace xolotlCore;

/**
<<<<<<< HEAD
 * The test suite is responsible for testing the WFitFluxHandler.
=======
 * The test suite is responsible for testing the W100FitFluxHandler.
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
 */
BOOST_AUTO_TEST_SUITE (W100FitFluxHandlerTester_testSuite)

BOOST_AUTO_TEST_CASE(checkGetIncidentFlux) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Create the network loader
<<<<<<< HEAD
	HDF5NetworkLoader loader =
			HDF5NetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
=======
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
<<<<<<< HEAD
	auto network = (PSIClusterReactionNetwork *) loader.load().get();

	// Specify the number of grid points that will be used
	int nGridpts = 5;
	// Specify the step size between grid points
	double step = 1.25;

	// Create the flux handler
    auto testFitFlux = make_shared<W100FitFluxHandler>();
    // Set the factor to change the helium flux
    testFitFlux->setFluxAmplitude(1.0);
    // Initialize the flux handler
    testFitFlux->initializeFluxHandler(network, nGridpts, step);
=======
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

	// Create the W100 flux handler
	auto testFitFlux = make_shared<W100FitFluxHandler>();
	// Set the flux amplitude
	testFitFlux->setFluxAmplitude(1.0);
	// Initialize the flux handler
	testFitFlux->initializeFluxHandler(network, surfacePos, grid);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Create a time
	double currTime = 1.0;

<<<<<<< HEAD
	// Get the flux vector
	auto testFluxVec = testFitFlux->getIncidentFluxVec(currTime);

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(testFluxVec[1], 0.476819, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[2], 0.225961, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[3], 0.097220, 0.01);

	return;
}

BOOST_AUTO_TEST_CASE(checkFluxIndex) {
	// Create the network loader
	HDF5NetworkLoader loader =
			HDF5NetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
	auto network = (PSIClusterReactionNetwork *) loader.load().get();

	// Specify the number of grid points that will be used
	int nGridpts = 5;
	// Specify the step size between grid points
	double step = 1.25;

	// Create the flux handler
    auto testFitFlux = make_shared<W100FitFluxHandler>();
    // Set the factor to change the helium flux
    testFitFlux->setFluxAmplitude(1.0);
    // Initialize the flux handler
    testFitFlux->initializeFluxHandler(network, nGridpts, step);

    // Check the value of the index of the cluster for the flux
    BOOST_REQUIRE_EQUAL(testFitFlux->getIncidentFluxClusterIndex(), 0);
=======
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
	BOOST_REQUIRE_CLOSE(newConcentration[9], 0.476819, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[18], 0.225961, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[27], 0.097220, 0.01);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

BOOST_AUTO_TEST_CASE(checkFluence) {
	// Create the network loader
<<<<<<< HEAD
	HDF5NetworkLoader loader =
			HDF5NetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
=======
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
<<<<<<< HEAD
	auto network = (PSIClusterReactionNetwork *) loader.load().get();

	// Specify the number of grid points that will be used
	int nGridpts = 5;
	// Specify the step size between grid points
	double step = 1.25;

	// Create the flux handler
    auto testFitFlux = make_shared<W100FitFluxHandler>();
    // Set the factor to change the helium flux
    testFitFlux->setFluxAmplitude(1.0);
    // Initialize the flux handler
    testFitFlux->initializeFluxHandler(network, nGridpts, step);
=======
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

	// Create the W100 flux handler
	auto testFitFlux = make_shared<W100FitFluxHandler>();
	// Set the flux amplitude
	testFitFlux->setFluxAmplitude(1.0);
	// Initialize the flux handler
	testFitFlux->initializeFluxHandler(network, surfacePos, grid);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Check that the fluence is 0.0 at the beginning
	BOOST_REQUIRE_EQUAL(testFitFlux->getFluence(), 0.0);

	// Increment the fluence
	testFitFlux->incrementFluence(1.0e-8);
<<<<<<< HEAD
	
=======

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Check that the fluence is not 0.0 anymore
	BOOST_REQUIRE_EQUAL(testFitFlux->getFluence(), 1.0e-8);

	return;
}

BOOST_AUTO_TEST_CASE(checkFluxAmplitude) {
	// Create the network loader
<<<<<<< HEAD
	HDF5NetworkLoader loader =
			HDF5NetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
=======
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
<<<<<<< HEAD
	auto network = (PSIClusterReactionNetwork *) loader.load().get();

	// Specify the number of grid points that will be used
	int nGridpts = 5;
	// Specify the step size between grid points
	double step = 1.25;

	// Create the flux handler
    auto testFitFlux = make_shared<W100FitFluxHandler>();
    // Set the factor to change the helium flux
    testFitFlux->setFluxAmplitude(1.0);
    // Set the factor to change the helium flux
    testFitFlux->setFluxAmplitude(2.5);
    // Initialize the flux handler
    testFitFlux->initializeFluxHandler(network, nGridpts, step);

    // Check the value of the helium flux
    BOOST_REQUIRE_EQUAL(testFitFlux->getFluxAmplitude(), 2.5);
=======
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

	// Create the W100 flux handler
	auto testFitFlux = make_shared<W100FitFluxHandler>();

	// Set the factor to change the flux amplitude
	testFitFlux->setFluxAmplitude(2.5);
	// Initialize the flux handler
	testFitFlux->initializeFluxHandler(network, surfacePos, grid);

	// Check the value of the flux amplitude
	BOOST_REQUIRE_EQUAL(testFitFlux->getFluxAmplitude(), 2.5);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Create a time
	double currTime = 1.0;

<<<<<<< HEAD
	// Get the flux vector
	auto testFluxVec = testFitFlux->getIncidentFluxVec(currTime);

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(testFluxVec[1], 1.192047, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[2], 0.564902, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[3], 0.243050, 0.01);
=======
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
	BOOST_REQUIRE_CLOSE(newConcentration[9], 1.192047, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[18], 0.564902, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[27], 0.243050, 0.01);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

BOOST_AUTO_TEST_CASE(checkTimeProfileFlux) {
	// Create the network loader
<<<<<<< HEAD
	HDF5NetworkLoader loader =
			HDF5NetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
=======
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
<<<<<<< HEAD
	auto network = (PSIClusterReactionNetwork *) loader.load().get();

	// Specify the number of grid points that will be used
	int nGridpts = 5;
	// Specify the step size between grid points
	double step = 1.25;
=======
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Create a file with a time profile for the flux
	// First column with the time and the second with
	// the amplitude (in He/nm2/s) at that time.
	std::ofstream writeFluxFile("fluxFile.dat");
	writeFluxFile << "0.0 1000.0 \n"
			"1.0 4000.0 \n"
			"2.0 2000.0 \n"
			"3.0 3000.0 \n"
			"4.0 0.0";
	writeFluxFile.close();

<<<<<<< HEAD
	// Create the flux handler
    auto testFitFlux = make_shared<W100FitFluxHandler>();
    // Initialize the time profile for the flux handler
    testFitFlux->initializeTimeProfile("fluxFile.dat");
    // Initialize the flux handler
    testFitFlux->initializeFluxHandler(network, nGridpts, step);
=======
	auto testFitFlux = make_shared<W100FitFluxHandler>();
	// Initialize the time profile for the flux handler
	testFitFlux->initializeTimeProfile("fluxFile.dat");
	// Initialize the flux handler
	testFitFlux->initializeFluxHandler(network, surfacePos, grid);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Create a time
	double currTime = 0.5;

<<<<<<< HEAD
	// Get the flux vector
	auto testFluxVec = testFitFlux->getIncidentFluxVec(currTime);

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(testFluxVec[1], 1192.047, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[2], 564.902, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[3], 243.050, 0.01);
	// Check the value of the helium flux
    BOOST_REQUIRE_EQUAL(testFitFlux->getFluxAmplitude(), 2500.0);

    // Change the current time
    currTime = 3.5;

	// Get the flux vector
	testFluxVec = testFitFlux->getIncidentFluxVec(currTime);

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(testFluxVec[1], 715.228, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[2], 338.941, 0.01);
	BOOST_REQUIRE_CLOSE(testFluxVec[3], 145.830, 0.01);
	// Check the value of the helium flux
    BOOST_REQUIRE_EQUAL(testFitFlux->getFluxAmplitude(), 1500.0);

    // Remove the created file
    std::string tempFile = "fluxFile.dat";
    std::remove(tempFile.c_str());
=======
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
	BOOST_REQUIRE_CLOSE(newConcentration[9], 1192.047, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[18], 564.902, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[27], 243.050, 0.01);
	// Check the value of the flux amplitude
	BOOST_REQUIRE_EQUAL(testFitFlux->getFluxAmplitude(), 2500.0);

	// Change the current time
	currTime = 3.5;

	// Reinitialize their values
	for (int i = 0; i < 5 * dof; i++) {
		newConcentration[i] = 0.0;
	}

	// Update the concentrations at some grid points
	updatedConcOffset = updatedConc + dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 1, surfacePos);
	updatedConcOffset = updatedConc + 2 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 2, surfacePos);
	updatedConcOffset = updatedConc + 3 * dof;
	testFitFlux->computeIncidentFlux(currTime, updatedConcOffset, 3, surfacePos);

	// Check the value at some grid points
	BOOST_REQUIRE_CLOSE(newConcentration[9], 715.228, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[18], 338.941, 0.01);
	BOOST_REQUIRE_CLOSE(newConcentration[27], 145.830, 0.01);
	// Check the value of the flux amplitude
	BOOST_REQUIRE_EQUAL(testFitFlux->getFluxAmplitude(), 1500.0);

	// Remove the created file
	std::string tempFile = "fluxFile.dat";
	std::remove(tempFile.c_str());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Finalize MPI
	MPI_Finalize();

	return;
}

BOOST_AUTO_TEST_SUITE_END()
