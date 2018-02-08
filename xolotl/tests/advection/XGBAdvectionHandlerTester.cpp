#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <XGBAdvectionHandler.h>
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
 * This suite is responsible for testing the XGBAdvectionHandler.
 */
BOOST_AUTO_TEST_SUITE(XGBAdvectionHandler_testSuite)

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

	// Create ofill
	int mat[dof * dof];
	int *ofill = &mat[0];

	// Create the advection handler and initialize it with a sink at
	// 2nm in the X direction
	XGBAdvectionHandler advectionHandler;
<<<<<<< HEAD
	advectionHandler.initialize(network, ofill);
=======
	advectionHandler.initialize(*network, ofill);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	advectionHandler.setLocation(2.0);
	advectionHandler.setDimension(2);

	// Check if grid points are on the sink
<<<<<<< HEAD
	std::vector<double> pos0 = { 0.1, 3.0, 0.0 };
	std::vector<double> pos1 = { 2.0, 2.0, 0.0 };
=======
	Point3D pos0 { 0.1, 3.0, 0.0 };
	Point3D pos1 { 2.0, 2.0, 0.0 };
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	BOOST_REQUIRE_EQUAL(advectionHandler.isPointOnSink(pos0), false);
	BOOST_REQUIRE_EQUAL(advectionHandler.isPointOnSink(pos1), true);

	// Check the total number of advecting clusters
	BOOST_REQUIRE_EQUAL(advectionHandler.getNumberOfAdvecting(), 6);

	// Set the size parameters
	double hx = 1.0;
	double hy = 0.5;

	// The arrays of concentration
	double concentration[9 * dof];
	double newConcentration[9 * dof];

	// Initialize their values
	for (int i = 0; i < 9 * dof; i++) {
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
	// Supposing the 9 grid points are laid-out as follow:
	// 6 | 7 | 8
	// 3 | 4 | 5
	// 0 | 1 | 2
	double *concOffset = conc + 4 * dof;
	double *updatedConcOffset = updatedConc + 4 * dof;

	// Fill the concVector with the pointer to the middle, left, right, bottom, and top grid points
	double **concVector = new double*[5];
	concVector[0] = concOffset; // middle
	concVector[1] = conc + 3 * dof; // left
	concVector[2] = conc + 5 * dof; // right
	concVector[3] = conc + 1 * dof; // bottom
	concVector[4] = conc + 7 * dof; // top

	// Set the grid position
<<<<<<< HEAD
	std::vector<double> gridPosition = { hx, hy, 0.0 };

	// Compute the advection at this grid point
	advectionHandler.computeAdvection(network, gridPosition, concVector,
=======
	Point3D gridPosition { hx, hy, 0.0 };

	// Compute the advection at this grid point
	advectionHandler.computeAdvection(*network, gridPosition, concVector,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			updatedConcOffset, hx, hx, 1, hy, 1);

	// Check the new values of updatedConcOffset
	BOOST_REQUIRE_CLOSE(updatedConcOffset[0], -1.86186e+11, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[1], -1.79073e+11, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[2], -2.2668e+11, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[3], -4.06708e+11, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[4], -5.83541e+11, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[5], -2.25802e+10, 0.01);
	BOOST_REQUIRE_CLOSE(updatedConcOffset[6], 0.0, 0.01); // Does not advect
	BOOST_REQUIRE_CLOSE(updatedConcOffset[7], 0.0, 0.01); // Does not advect
	BOOST_REQUIRE_CLOSE(updatedConcOffset[8], 0.0, 0.01); // Does not advect

	// Initialize the rows, columns, and values to set in the Jacobian
	int nAdvec = advectionHandler.getNumberOfAdvecting();
	int indices[nAdvec];
	double val[3 * nAdvec];
	// Get the pointer on them for the compute advection method
	int *indicesPointer = &indices[0];
	double *valPointer = &val[0];

	// Compute the partial derivatives for the advection a the grid point 1
<<<<<<< HEAD
	advectionHandler.computePartialsForAdvection(network, valPointer,
=======
	advectionHandler.computePartialsForAdvection(*network, valPointer,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			indicesPointer, gridPosition, hx, hx, 1, hy, 1);

	// Check the values for the indices
	BOOST_REQUIRE_EQUAL(indices[0], 0);
	BOOST_REQUIRE_EQUAL(indices[1], 1);
	BOOST_REQUIRE_EQUAL(indices[2], 2);
	BOOST_REQUIRE_EQUAL(indices[3], 3);
	BOOST_REQUIRE_EQUAL(indices[4], 4);
	BOOST_REQUIRE_EQUAL(indices[5], 5);

	// Check values
	BOOST_REQUIRE_CLOSE(val[0], -1.20606e+08, 0.01);
	BOOST_REQUIRE_CLOSE(val[1], 7.53788e+06, 0.01);
	BOOST_REQUIRE_CLOSE(val[2], -1.10475e+08, 0.01);
	BOOST_REQUIRE_CLOSE(val[3], 6.90469e+06, 0.01);
	BOOST_REQUIRE_CLOSE(val[4], -1.33344e+08, 0.01);
	BOOST_REQUIRE_CLOSE(val[5], 8.33401e+06, 0.01);

	// Get the stencil
	auto stencil = advectionHandler.getStencilForAdvection(gridPosition);

	// Check the value of the stencil
	BOOST_REQUIRE_EQUAL(stencil[0], -1); // x
	BOOST_REQUIRE_EQUAL(stencil[1], 0);
	BOOST_REQUIRE_EQUAL(stencil[2], 0);

	// Finalize MPI
	MPI_Finalize();
}

BOOST_AUTO_TEST_SUITE_END()
