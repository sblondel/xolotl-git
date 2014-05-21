#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <HDF5Utils.h>
#include <PSIClusterReactionNetwork.h>
#include <DummyHandlerRegistry.h>
<<<<<<< HEAD
#include <HDF5NetworkLoader.h>
#include <XolotlConfig.h>
#include <mpi.h>
=======
#include <PSIClusterNetworkLoader.h>
<<<<<<< HEAD
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
=======
#include <XolotlConfig.h>
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
#include <memory>

using namespace std;
using namespace xolotlCore;

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * This suite is responsible for testing the HDF5Utils
=======
 * This suite is responsible for testing the DataProvider.
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
=======
 * This suite is responsible for testing the HDF5Utils
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
 */
BOOST_AUTO_TEST_SUITE(HDF5Utils_testSuite)

/**
 * Method checking the writing and reading of the HDF5 file.
 */
<<<<<<< HEAD
BOOST_AUTO_TEST_CASE(checkIO) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

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
=======
BOOST_AUTO_TEST_CASE(checkOI) {
	// Create the network loader
	PSIClusterNetworkLoader loader =
			PSIClusterNetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/reactants/testfiles/tungsten.txt");
	string filename = sourceDir + pathToFile;
	// Create the network stream
	shared_ptr<istream> networkStream;
	networkStream = make_shared<ifstream>(filename);
	// Read the buffer of the stream
	auto bufferSS = make_shared<stringstream>();
	(*bufferSS) << networkStream->rdbuf();
	// Give the network stream to the network loader
	loader.setInputstream(bufferSS);

	// Load the network
	auto network = loader.load();
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521

	// Get the size of the network
	int networkSize = network->size();
	// Set the time step number
	int timeStep = 0;
	// Initialize the HDF5 file
<<<<<<< HEAD
	HDF5Utils::initializeFile("test.h5");

	// Set the number of grid points and step size
	int nGrid = 5;
	double stepSize = 0.5;
	// Set the time information
	double currentTime = 0.0001;
	double previousTime = 0.00001;
	double currentTimeStep = 0.000001;
	// Set the surface information
	int iSurface = 3;
	double nInter = 1.0, previousFlux = 0.1;
	// Write the header in the HDF5 file
	HDF5Utils::fillHeader(nGrid, stepSize);

	// Write the network in the HDF5 file
	HDF5Utils::fillNetwork(filename);

	// Finalize the HDF5 file
	HDF5Utils::finalizeFile();

	// Open it again to add the concentrations
	HDF5Utils::openFile("test.h5");

	// Add the concentration sub group
	HDF5Utils::addConcentrationSubGroup(timeStep, currentTime, previousTime, currentTimeStep);

	// Write the surface position
	HDF5Utils::writeSurface1D(timeStep, iSurface, nInter, previousFlux);

	// Add the concentration dataset
	int length = 5;
	int gridPoint = 0;
	HDF5Utils::addConcentrationDataset(length, gridPoint);

	// Create a vector of concentration for one grid point
	std::vector< std::vector<double> > concVector;
	// Fill it
	for (int i = 0; i < length; i++) {
		// Create the concentration vector for this cluster
		std::vector<double> conc;
		conc.push_back((double) i);
		conc.push_back((double) i * 10.0 - 5.0);

		// Add it to the main vector
		concVector.push_back(conc);
	}

	// Write the concentrations in the HDF5 file
	HDF5Utils::fillConcentrations(concVector, gridPoint);

	// Close the HDF5 file
	xolotlCore::HDF5Utils::closeFile();

	// Read the header of the written file
	int nx = 0, ny = 0, nz = 0;
	double hx = 0.0, hy = 0.0, hz = 0.0;
	HDF5Utils::readHeader("test.h5", nx, hx, ny, hy, nz, hz);
	// Check the obtained values
	BOOST_REQUIRE_EQUAL(nx, nGrid);
	BOOST_REQUIRE_CLOSE(hx, stepSize, 0.0001);
	BOOST_REQUIRE_EQUAL(ny, 0);
	BOOST_REQUIRE_CLOSE(hy, 0.0, 0.0001);
	BOOST_REQUIRE_EQUAL(nz, 0);
	BOOST_REQUIRE_CLOSE(hz, 0.0, 0.0001);

	// Read the times
	double t = 0.0, dt = 0.0;
	HDF5Utils::readTimes("test.h5", 0, t, dt);
	BOOST_REQUIRE_CLOSE(t, currentTime, 0.0001);
	BOOST_REQUIRE_CLOSE(dt, currentTimeStep, 0.0001);
	double previousReadTime = HDF5Utils::readPreviousTime("test.h5", 0);
	BOOST_REQUIRE_CLOSE(previousReadTime, previousTime, 0.0001);

	// Read the surface position
	int surfacePos = HDF5Utils::readSurface1D("test.h5", timeStep);
	BOOST_REQUIRE_EQUAL(surfacePos, iSurface);
	double nInterstitial = HDF5Utils::readNInterstitial1D("test.h5", timeStep);
	BOOST_REQUIRE_CLOSE(nInterstitial, nInter, 0.0001);
	double previousIFlux = HDF5Utils::readPreviousIFlux1D("test.h5", timeStep);
	BOOST_REQUIRE_CLOSE(previousIFlux, previousFlux, 0.0001);

	// Read the network of the written file
	auto networkVector = HDF5Utils::readNetwork("test.h5");
=======
	HDF5Utils::initializeFile(timeStep, networkSize);

	// Set the physical dimension of the grid and the refinement
	int dimension = 5;
	int refinement = 0;
	// Set the time information
	double currentTime = 0.0001;
	double currentTimeStep = 0.000001;
	// Write the header in the HDF5 file
	HDF5Utils::fillHeader(dimension, refinement, currentTime, currentTimeStep);

	// Write the network in the HDF5 file
	HDF5Utils::fillNetwork(network);

	// Create an array of concentration for one grid point
	double concentrations[networkSize];
	// Fill it
	for (int i = 0; i < networkSize; i++) {
		concentrations[i] = (double) i / 5.0;
	}
	double * conc = &concentrations[0];
	// Set the position at this grid point
	int gridPoint = 0;
	double position = 1.5;
	// Write the concentrations in the HDF5 file
	HDF5Utils::fillConcentrations(conc, gridPoint, position);

	// Finalize the HDF5 file
	xolotlCore::HDF5Utils::finalizeFile();

	// Read the header of the written file
	int dim = 0;
	double t = 0.0, dt = 0.0;
	HDF5Utils::readHeader("xolotlStop_0.h5", dim, t, dt);
	// Check the obtained values
	BOOST_REQUIRE_EQUAL(dim, dimension);
	BOOST_REQUIRE_EQUAL(t, currentTime);
	BOOST_REQUIRE_EQUAL(dt, currentTimeStep);

	// Read the network of the written file
	auto networkVector = HDF5Utils::readNetwork("xolotlStop_0.h5");
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
	// Get all the reactants
	auto reactants = network->getAll();
	// Check the network vector
	for (int i = 0; i < networkSize; i++) {
		// Get the i-th reactant in the network
<<<<<<< HEAD
		auto reactant = (PSICluster *) reactants->at(i);
=======
		shared_ptr<PSICluster> reactant = static_pointer_cast<PSICluster>(reactants->at(i));
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
		int id = reactant->getId() - 1;
		// Get the corresponding line from the HDF5 file
		auto line = networkVector.at(id);

		// Check the composition
		auto composition = reactant->getComposition();
		BOOST_REQUIRE_EQUAL((int) line[0], composition["He"]);
		BOOST_REQUIRE_EQUAL((int) line[1], composition["V"]);
		BOOST_REQUIRE_EQUAL((int) line[2], composition["I"]);

<<<<<<< HEAD
		// Check the formation energy
		auto formationEnergy = reactant->getFormationEnergy();
		BOOST_REQUIRE_EQUAL(line[3], formationEnergy);

		// Check the migration energy
		double migrationEnergy = reactant->getMigrationEnergy();
		BOOST_REQUIRE_EQUAL(line[4], migrationEnergy);

		// Check the diffusion factor
		double diffusionFactor = reactant->getDiffusionFactor();
		BOOST_REQUIRE_EQUAL(line[5], diffusionFactor);
	}

	// If the HDF5 file contains initial concentrations
	int tempTimeStep = -2;
	if (HDF5Utils::hasConcentrationGroup("test.h5", tempTimeStep)) {
		// Read the concentrations at the given grid point
		auto returnedVector = HDF5Utils::readGridPoint("test.h5", tempTimeStep, gridPoint);

		// Check the size of the vector
		BOOST_REQUIRE_EQUAL(returnedVector.size(), concVector.size());
		// Check the values
		for (unsigned int i = 0; i < returnedVector.size(); i++) {
			BOOST_REQUIRE_CLOSE(returnedVector.at(i).at(0), concVector.at(i).at(0), 0.0001);
			BOOST_REQUIRE_CLOSE(returnedVector.at(i).at(1), concVector.at(i).at(1), 0.0001);
		}
	}
}

/**
 * Method checking the writing and reading of the surface position specifically
 * in the case of a 2D grid.
 */
BOOST_AUTO_TEST_CASE(checkSurface2D) {
	// Initialize the HDF5 file
	HDF5Utils::initializeFile("test.h5");

	// Set the number of grid points and step size
	int nGrid = 5;
	double stepSize = 0.5;
	// Set the time information
	double currentTime = 0.0001;
	double previousTime = 0.00001;
	double currentTimeStep = 0.000001;
	// Write the header in the HDF5 file
	HDF5Utils::fillHeader(nGrid, stepSize);

	// Finalize the HDF5 file
	HDF5Utils::finalizeFile();

	// Open it again to add the concentrations
	HDF5Utils::openFile("test.h5");

	// Set the time step number
	int timeStep = 0;

	// Add the concentration sub group
	HDF5Utils::addConcentrationSubGroup(timeStep, currentTime, previousTime, currentTimeStep);

	// Set the surface information in 2D
	std::vector<int> iSurface = {2, 3, 2, 0, 5};
	std::vector<double> nInter = {0.0, 0.0, 0.5, 0.6, 0.5};
	std::vector<double> previousFlux = {0.0, 0.1, 3.0, -1.0, 5.0};

	// Write the surface position
	HDF5Utils::writeSurface2D(timeStep, iSurface, nInter, previousFlux);

	// Close the HDF5 file
	xolotlCore::HDF5Utils::closeFile();

	// Read the surface position
	auto surfacePos = HDF5Utils::readSurface2D("test.h5", timeStep);
	// Check all the values
	for (int i = 0; i < surfacePos.size(); i++) {
		BOOST_REQUIRE_EQUAL(surfacePos[i], iSurface[i]);
	}

	// Read the interstitial quantity
	auto nInterstitial = HDF5Utils::readNInterstitial2D("test.h5", timeStep);
	// Check all the values
	for (int i = 0; i < nInterstitial.size(); i++) {
		BOOST_REQUIRE_CLOSE(nInterstitial[i], nInter[i], 0.0001);
	}

	// Read the interstitial flux
	auto previousIFlux = HDF5Utils::readPreviousIFlux2D("test.h5", timeStep);
	// Check all the values
	for (int i = 0; i < previousIFlux.size(); i++) {
		BOOST_REQUIRE_CLOSE(previousIFlux[i], previousFlux[i], 0.0001);
	}
}

/**
 * Method checking the writing and reading of the surface position specifically
 * in the case of a 3D grid.
 */
BOOST_AUTO_TEST_CASE(checkSurface3D) {
	// Initialize the HDF5 file
	HDF5Utils::initializeFile("test.h5");

	// Set the number of grid points and step size
	int nGrid = 5;
	double stepSize = 0.5;
	// Set the time information
	double currentTime = 0.0001;
	double previousTime = 0.00001;
	double currentTimeStep = 0.000001;
	// Write the header in the HDF5 file
	HDF5Utils::fillHeader(nGrid, stepSize);

	// Finalize the HDF5 file
	HDF5Utils::finalizeFile();

	// Open it again to add the concentrations
	HDF5Utils::openFile("test.h5");

	// Set the time step number
	int timeStep = 0;

	// Add the concentration sub group
	HDF5Utils::addConcentrationSubGroup(timeStep, currentTime, previousTime, currentTimeStep);

	// Set the surface information in 2D
	std::vector< std::vector<int> > iSurface = {{2, 4, 1, 0, 5}, {2, 3, 2, 0, 5}, {6, 1, 2, 3, 2}};
	std::vector< std::vector<double> > nInter = {{0.0, 0.0, 0.0, 0.0, 0.0},
			{2.0, 3.0, 2.0, 0.0, 0.5}, {0.0, 0.0, 0.0, 0.0, 0.0}};
	std::vector< std::vector<double> > previousFlux = {{0.0, 0.0, 0.0, 0.0, 0.0},
			{-2.0, 3.0, 2.0, 0.0, -0.5}, {0.0, 0.0, 0.0, 0.0, 0.0}};

	// Write the surface position
	HDF5Utils::writeSurface3D(timeStep, iSurface, nInter, previousFlux);

	// Close the HDF5 file
	xolotlCore::HDF5Utils::closeFile();

	// Read the surface position
	auto surfacePos = HDF5Utils::readSurface3D("test.h5", timeStep);
	// Check all the values
	for (int i = 0; i < surfacePos.size(); i++) {
		for (int j = 0; j < surfacePos[0].size(); j++) {
			BOOST_REQUIRE_EQUAL(surfacePos[i][j], iSurface[i][j]);
		}
	}
	auto nInterstitial = HDF5Utils::readNInterstitial3D("test.h5", timeStep);
	// Check all the values
	for (int i = 0; i < nInterstitial.size(); i++) {
		for (int j = 0; j < nInterstitial[0].size(); j++) {
			BOOST_REQUIRE_CLOSE(nInterstitial[i][j], nInter[i][j], 0.0001);
		}
	}
	auto previousIFlux = HDF5Utils::readPreviousIFlux3D("test.h5", timeStep);
	// Check all the values
	for (int i = 0; i < previousIFlux.size(); i++) {
		for (int j = 0; j < previousIFlux[0].size(); j++) {
			BOOST_REQUIRE_CLOSE(previousIFlux[i][j], previousFlux[i][j], 0.0001);
		}
=======
		// Check the binding energies
		auto bindingEnergies = reactant->getBindingEnergies();
		BOOST_REQUIRE_EQUAL(line[3], bindingEnergies.at(0)); // Helium binding energy
		BOOST_REQUIRE_EQUAL(line[4], bindingEnergies.at(1)); // Vacancy binding energy
		BOOST_REQUIRE_EQUAL(line[5], bindingEnergies.at(2)); // Interstitial binding energy

		// Check the migration energy
		double migrationEnergy = reactant->getMigrationEnergy();
		BOOST_REQUIRE_EQUAL(line[6], migrationEnergy);

		// Check the diffusion factor
		double diffusionFactor = reactant->getDiffusionFactor();
		BOOST_REQUIRE_EQUAL(line[7], diffusionFactor);
	}

	// Read the concentrations at the given grid point
	double newConcentrations[networkSize];
	double * newConc = &newConcentrations[0];
	HDF5Utils::readGridPoint("xolotlStop_0.h5", networkSize, gridPoint, newConc);
	// Check them
	for (int i = 0; i < networkSize; i++) {
		BOOST_REQUIRE_EQUAL(newConcentrations[i], concentrations[i]);
>>>>>>> Adding unit test for HDF5Utils and fixing the type for storing int in HDF5 files to 32 bits. SB 20140521
	}
}

BOOST_AUTO_TEST_SUITE_END()
