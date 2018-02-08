#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <W110AdvectionHandler.h>
#include <HDF5NetworkLoader.h>
#include <XolotlConfig.h>
<<<<<<< HEAD
=======
#include <Options.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <DummyHandlerRegistry.h>
#include <mpi.h>

using namespace std;
using namespace xolotlCore;

/**
 * This suite is responsible for testing the W110AdvectionHandler.
 */
BOOST_AUTO_TEST_SUITE(W110AdvectionHandler_testSuite)

/**
 * Method checking the initialization and the compute advection methods.
 */
BOOST_AUTO_TEST_CASE(checkAdvection) {
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
	for (int l = 0; l < 5; l++) {
		grid.push_back((double) l);
	}

	// Create ofill
	int mat[dof * dof];
	int *ofill = &mat[0];

	// Create a collection of advection handlers
	std::vector<IAdvectionHandler *> advectionHandlers;

	// Create the advection handler and initialize it
	W110AdvectionHandler advectionHandler;
<<<<<<< HEAD
	advectionHandler.initialize(network, ofill);
=======
	advectionHandler.initialize(*network, ofill);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	advectionHandler.initializeAdvectionGrid(advectionHandlers, grid);

	// Check the total number of advecting clusters
	BOOST_REQUIRE_EQUAL(advectionHandler.getNumberOfAdvecting(), 6);

	// Check the clusters in ofill
	BOOST_REQUIRE_EQUAL(ofill[0], 1);
	BOOST_REQUIRE_EQUAL(ofill[11], 1);
	BOOST_REQUIRE_EQUAL(ofill[22], 1);
	BOOST_REQUIRE_EQUAL(ofill[33], 1);
	BOOST_REQUIRE_EQUAL(ofill[44], 1);
	BOOST_REQUIRE_EQUAL(ofill[55], 1);

	// Set the size parameter in the x direction
	double hx = 1.0;

	// Create the arrays of concentration
	double concentration[3 * dof];
	double newConcentration[3 * dof];

	// Initialize their values
	for (int i = 0; i < 3 * dof; i++) {
		concentration[i] = (double) i * i;
		newConcentration[i] = 0.0;
	}

	// Set the temperature to 1000K to initialize the diffusion coefficients
<<<<<<< HEAD
	auto reactants = network->getAll();
	for (int i = 0; i < dof - 1; i++) {
		auto cluster = (PSICluster *) reactants->at(i);
		cluster->setTemperature(1000.0);
	}
=======
	network->setTemperature(1000.0);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get pointers
	double *conc = &concentration[0];
	double *updatedConc = &newConcentration[0];

	// Get the offset for the grid point in the middle
	double *concOffset = conc + dof;
	double *updatedConcOffset = updatedConc + dof;

	// Fill the concVector with the pointer to the middle, left, and right grid points
	double **concVector = new double*[3];
	concVector[0] = concOffset; // middle
	concVector[1] = conc; // left
	concVector[2] = conc + 2 * dof; // right

	// Set the grid position
<<<<<<< HEAD
	std::vector<double> gridPosition = { hx, 0.0, 0.0 };

	// Compute the advection at this grid point
	advectionHandler.computeAdvection(network, gridPosition, concVector,
=======
	Point3D gridPosition { hx, 0.0, 0.0 };

	// Compute the advection at this grid point
	advectionHandler.computeAdvection(*network, gridPosition, concVector,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			updatedConcOffset, hx, hx, 1);

	// Check the new values of updatedConcOffset
	BOOST_REQUIRE_CLOSE(updatedConcOffset[0], -1.54108e+10, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[1], -1.51261e+10, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[2], -3.36897e+10, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[3], -4.88168e+10, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[4], -2.32559e+11, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[5], -7.48408e+09, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[6], 0.0, 0.01); // Does not advect
	BOOST_REQUIRE_CLOSE(updatedConcOffset[7], 0.0, 0.01); // Does not advect
	BOOST_REQUIRE_CLOSE(updatedConcOffset[8], 0.0, 0.01); // Does not advect

	// Initialize the rows, columns, and values to set in the Jacobian
	int nAdvec = advectionHandler.getNumberOfAdvecting();
	int indices[nAdvec];
	double val[2 * nAdvec];
	// Get the pointer on them for the compute advection method
	int *indicesPointer = &indices[0];
	double *valPointer = &val[0];

	// Compute the partial derivatives for the advection a the grid point 1
<<<<<<< HEAD
	advectionHandler.computePartialsForAdvection(network, valPointer,
=======
	advectionHandler.computePartialsForAdvection(*network, valPointer,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			indicesPointer, gridPosition, hx, hx, 1);

	// Check the values for the indices
	BOOST_REQUIRE_EQUAL(indices[0], 0);
	BOOST_REQUIRE_EQUAL(indices[1], 1);
	BOOST_REQUIRE_EQUAL(indices[2], 2);
	BOOST_REQUIRE_EQUAL(indices[3], 3);
	BOOST_REQUIRE_EQUAL(indices[4], 4);
	BOOST_REQUIRE_EQUAL(indices[5], 5);

	// Check values
	BOOST_REQUIRE_CLOSE(val[0], -205476899.0, 0.01);
	BOOST_REQUIRE_CLOSE(val[1], 12842306.0, 0.01);
	BOOST_REQUIRE_CLOSE(val[2], -161884163.0, 0.01);
	BOOST_REQUIRE_CLOSE(val[3], 10117760.0, 0.01);

	// Get the stencil
	auto stencil = advectionHandler.getStencilForAdvection(gridPosition);

	// Check the value of the stencil
	BOOST_REQUIRE_EQUAL(stencil[0], 1); //x
	BOOST_REQUIRE_EQUAL(stencil[1], 0);
	BOOST_REQUIRE_EQUAL(stencil[2], 0);

	// Finalize MPI
	MPI_Finalize();
}

BOOST_AUTO_TEST_SUITE_END()
