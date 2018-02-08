#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSIClusterNetworkLoader.h>
#include <memory>
#include <typeinfo>
#include <limits>
<<<<<<< HEAD
#include <string.h>
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include <PSIClusterNetworkLoader.h>
#include <PSIClusterReactionNetwork.h>
#include <PetscSolver.h>
#include <XolotlConfig.h>
<<<<<<< HEAD
#include <xolotlPerf.h>
#include <DummyHandlerRegistry.h>
#include <HDF5NetworkLoader.h>
#include <Options.h>
#include <PetscSolver0DHandler.h>
#include <PetscSolver1DHandler.h>
#include <PetscSolver2DHandler.h>
#include <PetscSolver3DHandler.h>
#include <IMaterialFactory.h>
#include <TemperatureHandlerFactory.h>
#include <IReactionHandlerFactory.h>
#include <VizHandlerRegistryFactory.h>
#include <cassert>
=======
#include <DummyHandlerRegistry.h>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

using namespace std;
using namespace xolotlCore;

/**
 * The test suite configuration
<<<<<<< HEAD
 */
BOOST_AUTO_TEST_SUITE (PetscSolverTester_testSuite)

/**
 * This operation checks the concentration of clusters after solving a test case
 * in 0D.
 */
BOOST_AUTO_TEST_CASE(checkPetscSolver0DHandler) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Local Declarations
	string sourceDir(XolotlSourceDirectory);

	// Create the path to the network file
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string networkFilename = sourceDir + pathToFile;

	// Create the parameter file
	std::ofstream paramFile("param.txt");
	paramFile << "vizHandler=dummy" << std::endl
			<< "petscArgs=-fieldsplit_0_pc_type redundant "
					"-ts_max_snes_failures 200 "
					"-pc_fieldsplit_detect_coupling "
					"-ts_adapt_dt_max 10 "
					"-pc_type fieldsplit "
					"-fieldsplit_1_pc_type sor "
					"-ts_final_time 1000 "
					"-ts_max_steps 5 "
					"-ts_exact_final_time stepover" << std::endl
			<< "startTemp=900" << std::endl << "perfHandler=dummy" << std::endl
			<< "flux=4.0e5" << std::endl << "material=W100" << std::endl
			<< "dimensions=0" << std::endl << "process=reaction"
			<< std::endl << "networkFile="
			<< networkFilename << std::endl;
	paramFile.close();

	// Create a fake command line to read the options
	argv = new char*[2];
	std::string parameterFile = "param.txt";
	argv[0] = new char[parameterFile.length() + 1];
	strcpy(argv[0], parameterFile.c_str());
	argv[1] = 0; // null-terminate the array

	// Read the options
	Options opts;
	opts.readParams(argv);

	// Set the options to use a regular grid in the x direction because the parameter file
	// says the opposite
	opts.setRegularXGrid(true);

	// Create the network loader
	std::shared_ptr<HDF5NetworkLoader> loader = std::make_shared<
			HDF5NetworkLoader>(make_shared<xolotlPerf::DummyHandlerRegistry>());

	BOOST_TEST_MESSAGE(
			"PetscSolverTester Message: Network filename is: " << networkFilename);

	// Give the filename to the network loader
	loader->setFilename(networkFilename);

	// Create the solver
	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
			xolotlSolver::PetscSolver>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());

	// Create the material factory
	auto materialFactory =
			xolotlFactory::IMaterialFactory::createMaterialFactory(
					opts.getMaterial(), opts.getDimensionNumber());

	// Initialize and get the temperature handler
	bool tempInitOK = xolotlFactory::initializeTempHandler(opts);
	auto tempHandler = xolotlFactory::getTemperatureHandler();

	// Set up our dummy performance and visualization infrastructures
	xolotlPerf::initialize(xolotlPerf::toPerfRegistryType("dummy"));
	xolotlFactory::initializeVizHandler(false);

	// Create the network handler factory
	auto networkFactory =
			xolotlFactory::IReactionHandlerFactory::createNetworkFactory(
					opts.getMaterial());
	networkFactory->initializeReactionNetwork(opts,
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Get the network handler
	auto networkHandler = networkFactory->getNetworkHandler();

	// Create a solver handler and initialize it
	auto solvHandler = std::make_shared<xolotlSolver::PetscSolver0DHandler>();
	solvHandler->initializeHandlers(materialFactory, tempHandler,
			networkHandler, opts);

	// Set the solver command line to give the PETSc options and initialize it
	solver->setCommandLineOptions(opts.getPetscArgc(), opts.getPetscArgv());
	solver->initialize(solvHandler);

	// Solve and finalize
	solver->solve();
	solver->finalize();

	// Check the concentrations left in the network
	auto network = solvHandler->getNetwork();
	double concs[network->getAll()->size()];
	network->fillConcentrationsArray(concs);

	// Check some concentrations
	BOOST_REQUIRE_SMALL(concs[0], 1.0e-10);
	BOOST_REQUIRE_SMALL(concs[1], 1.0e-17);
	BOOST_REQUIRE_SMALL(concs[2], 1.0e-25);
	BOOST_REQUIRE_SMALL(concs[7], 1.0e-61);
	BOOST_REQUIRE_CLOSE(concs[8], 0.0, 0.01);

	// Remove the created file
	std::string tempFile = "param.txt";
	std::remove(tempFile.c_str());
}

/**
 * This operation checks the concentration of clusters after solving a test case
 * in 1D.
 */
BOOST_AUTO_TEST_CASE(checkPetscSolver1DHandler) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Local Declarations
	string sourceDir(XolotlSourceDirectory);

	// Create the path to the network file
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string networkFilename = sourceDir + pathToFile;

	// Create the parameter file
	std::ofstream paramFile("param.txt");
	paramFile << "vizHandler=dummy" << std::endl
			<< "petscArgs=-fieldsplit_0_pc_type redundant "
					"-ts_max_snes_failures 200 "
					"-pc_fieldsplit_detect_coupling "
					"-ts_adapt_dt_max 10 "
					"-pc_type fieldsplit "
					"-fieldsplit_1_pc_type sor "
					"-ts_final_time 1000 "
					"-ts_max_steps 5 "
					"-ts_exact_final_time stepover" << std::endl
			<< "startTemp=900" << std::endl << "perfHandler=dummy" << std::endl
			<< "flux=4.0e5" << std::endl << "material=W100" << std::endl
			<< "dimensions=1" << std::endl << "process=diff advec reaction"
			<< std::endl << "voidPortion=0.0" << std::endl << "networkFile="
			<< networkFilename << std::endl;
	paramFile.close();

	// Create a fake command line to read the options
	argv = new char*[2];
	std::string parameterFile = "param.txt";
	argv[0] = new char[parameterFile.length() + 1];
	strcpy(argv[0], parameterFile.c_str());
	argv[1] = 0; // null-terminate the array

	// Read the options
	Options opts;
	opts.readParams(argv);

	// Set the options to use a regular grid in the x direction because the parameter file
	// says the opposite
	opts.setRegularXGrid(true);

	// Create the network loader
	std::shared_ptr<HDF5NetworkLoader> loader = std::make_shared<
			HDF5NetworkLoader>(make_shared<xolotlPerf::DummyHandlerRegistry>());

	BOOST_TEST_MESSAGE(
			"PetscSolverTester Message: Network filename is: " << networkFilename);

	// Give the filename to the network loader
	loader->setFilename(networkFilename);

	// Create the solver
	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
			xolotlSolver::PetscSolver>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());

	// Create the material factory
	auto materialFactory =
			xolotlFactory::IMaterialFactory::createMaterialFactory(
					opts.getMaterial(), opts.getDimensionNumber());

	// Initialize and get the temperature handler
	bool tempInitOK = xolotlFactory::initializeTempHandler(opts);
	auto tempHandler = xolotlFactory::getTemperatureHandler();

	// Set up our dummy performance and visualization infrastructures
	xolotlPerf::initialize(xolotlPerf::toPerfRegistryType("dummy"));
	xolotlFactory::initializeVizHandler(false);

	// Create the network handler factory
	auto networkFactory =
			xolotlFactory::IReactionHandlerFactory::createNetworkFactory(
					opts.getMaterial());
	networkFactory->initializeReactionNetwork(opts,
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Get the network handler
	auto networkHandler = networkFactory->getNetworkHandler();

	// Create a solver handler and initialize it
	auto solvHandler = std::make_shared<xolotlSolver::PetscSolver1DHandler>();
	solvHandler->initializeHandlers(materialFactory, tempHandler,
			networkHandler, opts);

	// Set the solver command line to give the PETSc options and initialize it
	solver->setCommandLineOptions(opts.getPetscArgc(), opts.getPetscArgv());
	solver->initialize(solvHandler);

	// Solve and finalize
	solver->solve();
	solver->finalize();

	// Check the concentrations left in the network
	auto network = solvHandler->getNetwork();
	double concs[network->getAll()->size()];
	network->fillConcentrationsArray(concs);

	// Check some concentrations
	BOOST_REQUIRE_SMALL(concs[0], 1.0e-10);
	BOOST_REQUIRE_SMALL(concs[1], 1.0e-17);
	BOOST_REQUIRE_SMALL(concs[2], 1.0e-25);
	BOOST_REQUIRE_SMALL(concs[7], 1.0e-61);
	BOOST_REQUIRE_CLOSE(concs[8], 0.0, 0.01);

	// Remove the created file
	std::string tempFile = "param.txt";
	std::remove(tempFile.c_str());
}

/**
 * This operation checks the concentration of clusters after solving a test case
 * in 1D with an irregular grid spacing in the x direction.
 */
BOOST_AUTO_TEST_CASE(checkIrregularPetscSolver1DHandler) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Local Declarations
	string sourceDir(XolotlSourceDirectory);

	// Create the path to the network file
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string networkFilename = sourceDir + pathToFile;

	// Create the parameter file
	std::ofstream paramFile("param.txt");
	paramFile << "vizHandler=dummy" << std::endl
			<< "petscArgs=-fieldsplit_0_pc_type redundant "
					"-ts_max_snes_failures 200 "
					"-pc_fieldsplit_detect_coupling "
					"-ts_adapt_dt_max 10 "
					"-pc_type fieldsplit "
					"-fieldsplit_1_pc_type sor "
					"-ts_final_time 1000 "
					"-ts_max_steps 5 "
					"-ts_exact_final_time stepover" << std::endl
			<< "startTemp=900" << std::endl << "perfHandler=dummy" << std::endl
			<< "flux=4.0e5" << std::endl << "material=W100" << std::endl
			<< "dimensions=1" << std::endl << "regularGrid=no" << std::endl
			<< "process=diff advec modifiedTM reaction" << std::endl
			<< "voidPortion=0.0" << std::endl << "networkFile="
			<< networkFilename << std::endl;
	paramFile.close();

	// Create a fake command line to read the options
	argc = 1;
	argv = new char*[2];
	std::string parameterFile = "param.txt";
	argv[0] = new char[parameterFile.length() + 1];
	strcpy(argv[0], parameterFile.c_str());
	argv[1] = 0; // null-terminate the array

	// Read the options
	Options opts;
	opts.readParams(argv);

	// Create the network loader
	std::shared_ptr<HDF5NetworkLoader> loader = std::make_shared<
			HDF5NetworkLoader>(make_shared<xolotlPerf::DummyHandlerRegistry>());

	BOOST_TEST_MESSAGE(
			"PetscSolverTester Message: Network filename is: " << networkFilename);

	// Give the filename to the network loader
	loader->setFilename(networkFilename);

	// Create the solver
	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
			xolotlSolver::PetscSolver>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());

	// Create the material factory
	auto materialFactory =
			xolotlFactory::IMaterialFactory::createMaterialFactory(
					opts.getMaterial(), opts.getDimensionNumber());

	// Initialize and get the temperature handler
	bool tempInitOK = xolotlFactory::initializeTempHandler(opts);
	BOOST_REQUIRE_EQUAL(tempInitOK, true);
	auto tempHandler = xolotlFactory::getTemperatureHandler();

	// Set up our dummy performance and visualization infrastructures
	xolotlPerf::initialize(xolotlPerf::toPerfRegistryType("dummy"));
	xolotlFactory::initializeVizHandler(false);

	// Create the network handler factory
	auto networkFactory =
			xolotlFactory::IReactionHandlerFactory::createNetworkFactory(
					opts.getMaterial());
	networkFactory->initializeReactionNetwork(opts,
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Get the network handler
	auto networkHandler = networkFactory->getNetworkHandler();

	// Create a solver handler and initialize it
	auto solvHandler = std::make_shared<xolotlSolver::PetscSolver1DHandler>();
	solvHandler->initializeHandlers(materialFactory, tempHandler,
			networkHandler, opts);

	// Set the solver command line to give the PETSc options and initialize it
	solver->setCommandLineOptions(opts.getPetscArgc(), opts.getPetscArgv());
	solver->initialize(solvHandler);

	// Solve and finalize
	solver->solve();
	solver->finalize();

	// Check the concentrations left in the network
	auto network = solvHandler->getNetwork();
	double concs[network->getAll()->size()];
	network->fillConcentrationsArray(concs);

	// Check some concentrations
	BOOST_REQUIRE_SMALL(concs[0], 1.0e-11);
	BOOST_REQUIRE_SMALL(concs[1], 1.0e-22);
	BOOST_REQUIRE_SMALL(concs[2], 1.0e-33);
	BOOST_REQUIRE_SMALL(concs[7], 1.0e-81);
	BOOST_REQUIRE_CLOSE(concs[8], 0.0, 0.01);

	// Remove the created file
	std::string tempFile = "param.txt";
	std::remove(tempFile.c_str());
}

/**
 * This operation checks the concentration of clusters after solving a test case
 * in 2D.
 */
BOOST_AUTO_TEST_CASE(checkPetscSolver2DHandler) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Local Declarations
	string sourceDir(XolotlSourceDirectory);

	// Create the path to the network file
	string pathToFile("/tests/testfiles/tungsten_diminutive_2D.h5");
	string networkFilename = sourceDir + pathToFile;

	// Create the parameter file
	std::ofstream paramFile("param.txt");
	paramFile << "vizHandler=dummy" << std::endl
			<< "petscArgs=-fieldsplit_0_pc_type redundant "
					"-ts_max_snes_failures 200 "
					"-pc_fieldsplit_detect_coupling "
					"-ts_adapt_dt_max 10 "
					"-pc_type fieldsplit "
					"-fieldsplit_1_pc_type sor "
					"-ts_final_time 1000 "
					"-ts_max_steps 5 "
					"-ts_exact_final_time stepover" << std::endl
			<< "startTemp=900" << std::endl << "perfHandler=dummy" << std::endl
			<< "flux=4.0e5" << std::endl << "material=W100" << std::endl
			<< "dimensions=2" << std::endl << "process=diff advec reaction"
			<< std::endl << "voidPortion=0.0" << std::endl << "networkFile="
			<< networkFilename << std::endl;
	paramFile.close();

	// Create a fake command line to read the options
	argv = new char*[2];
	std::string parameterFile = "param.txt";
	argv[0] = new char[parameterFile.length() + 1];
	strcpy(argv[0], parameterFile.c_str());
	argv[1] = 0; // null-terminate the array

	// Read the options
	Options opts;
	opts.readParams(argv);

	// Create the network loader
	std::shared_ptr<HDF5NetworkLoader> loader = std::make_shared<
			HDF5NetworkLoader>(make_shared<xolotlPerf::DummyHandlerRegistry>());

	BOOST_TEST_MESSAGE(
			"PetscSolverTester Message: Network filename is: " << networkFilename);

	// Give the filename to the network loader
	loader->setFilename(networkFilename);

	// Create the solver
	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
			xolotlSolver::PetscSolver>(
			make_shared<xolotlPerf::DummyHandlerRegistry>());

	// Create the material factory
	auto materialFactory =
			xolotlFactory::IMaterialFactory::createMaterialFactory(
					opts.getMaterial(), opts.getDimensionNumber());

	// Initialize and get the temperature handler
	bool tempInitOK = xolotlFactory::initializeTempHandler(opts);
	BOOST_REQUIRE_EQUAL(tempInitOK, true);
	auto tempHandler = xolotlFactory::getTemperatureHandler();

	// Set up our dummy performance and visualization infrastructures
	xolotlPerf::initialize(xolotlPerf::toPerfRegistryType("dummy"));
	xolotlFactory::initializeVizHandler(false);

	// Create the network handler factory
	auto networkFactory =
			xolotlFactory::IReactionHandlerFactory::createNetworkFactory(
					opts.getMaterial());
	networkFactory->initializeReactionNetwork(opts,
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Get the network handler
	auto networkHandler = networkFactory->getNetworkHandler();

	// Create a solver handler and initialize it
	auto solvHandler = std::make_shared<xolotlSolver::PetscSolver2DHandler>();
	solvHandler->initializeHandlers(materialFactory, tempHandler,
			networkHandler, opts);

	// Set the solver command line to give the PETSc options and initialize it
	solver->setCommandLineOptions(opts.getPetscArgc(), opts.getPetscArgv());
	solver->initialize(solvHandler);

	// Solve and finalize
	solver->solve();
	solver->finalize();

	// Check the concentrations left in the network
	auto network = solvHandler->getNetwork();
	double concs[network->getAll()->size()];
	network->fillConcentrationsArray(concs);

	// Check some concentrations
	BOOST_REQUIRE_SMALL(concs[0], 1.0e-24);
	BOOST_REQUIRE_SMALL(concs[1], 1.0e-46);
	BOOST_REQUIRE_SMALL(concs[6], 1.0e-4);
	BOOST_REQUIRE_SMALL(concs[14], 1.0e-120);
	BOOST_REQUIRE_SMALL(concs[23], 1.0e-21);

	// Remove the created file
	std::string tempFile = "param.txt";
	std::remove(tempFile.c_str());
}

///**
// * This operation checks the concentration of clusters after solving a test case
// * in 3D.
// */
//BOOST_AUTO_TEST_CASE(checkPetscSolver3DHandler) {
//	// Initialize MPI for HDF5
//	int argc = 0;
//	char **argv;
//	MPI_Init(&argc, &argv);
//
//	// Local Declarations
//	string sourceDir(XolotlSourceDirectory);
//
//	// Create the path to the network file
//	string pathToFile("/tests/testfiles/tungsten_diminutive_3D.h5");
//	string networkFilename = sourceDir + pathToFile;
//
//	// Create the parameter file
//	std::ofstream paramFile("param.txt");
//	paramFile << "vizHandler=dummy" << std::endl
//			<< "petscArgs=-fieldsplit_0_pc_type redundant "
//					"-ts_max_snes_failures 200 "
//					"-pc_fieldsplit_detect_coupling "
//					"-ts_adapt_dt_max 10 "
//					"-pc_type fieldsplit "
//					"-fieldsplit_1_pc_type sor "
//					"-ts_final_time 1000 "
//					"-ts_max_steps 5 "
//					"-ts_exact_final_time stepover" << std::endl
//			<< "startTemp=900" << std::endl << "perfHandler=dummy" << std::endl
//			<< "flux=4.0e5" << std::endl << "material=W100" << std::endl
//			<< "dimensions=3" << std::endl << "process=diff advec reaction"
//			<< std::endl << "voidPortion=0.0" << std::endl << "networkFile="
//			<< networkFilename << std::endl;
//	paramFile.close();
//
//	// Create a fake command line to read the options
//	argv = new char*[2];
//	std::string parameterFile = "param.txt";
//	argv[0] = new char[parameterFile.length() + 1];
//	strcpy(argv[0], parameterFile.c_str());
//	argv[1] = 0; // null-terminate the array
//
//	// Read the options
//	Options opts;
//	opts.readParams(argv);
//
//	// Create the network loader
//	std::shared_ptr<HDF5NetworkLoader> loader = std::make_shared<
//			HDF5NetworkLoader>(make_shared<xolotlPerf::DummyHandlerRegistry>());
//
//	BOOST_TEST_MESSAGE(
//			"PetscSolverTester Message: Network filename is: " << networkFilename);
//
//	// Give the filename to the network loader
//	loader->setFilename(networkFilename);
//
//	// Create the solver
//	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
//			xolotlSolver::PetscSolver>(
//			make_shared<xolotlPerf::DummyHandlerRegistry>());
//
//	// Create the material factory
//	auto materialFactory =
//			xolotlFactory::IMaterialFactory::createMaterialFactory(
//					opts.getMaterial(), opts.getDimensionNumber());
//
//	// Initialize and get the temperature handler
//	bool tempInitOK = xolotlFactory::initializeTempHandler(opts);
//	BOOST_REQUIRE_EQUAL(tempInitOK, true);
//	auto tempHandler = xolotlFactory::getTemperatureHandler();
//
//	// Set up our dummy performance and visualization infrastructures
//	xolotlPerf::initialize(xolotlPerf::toPerfRegistryType("dummy"));
//	xolotlFactory::initializeVizHandler(false);
//
//	// Create the network handler factory
//	auto networkFactory =
//			xolotlFactory::IReactionHandlerFactory::createNetworkFactory(
//					opts.getMaterial());
//	networkFactory->initializeReactionNetwork(opts,
//			make_shared<xolotlPerf::DummyHandlerRegistry>());
//	// Get the network handler
//	auto networkHandler = networkFactory->getNetworkHandler();
//
//	// Create a solver handler and initialize it
//	auto solvHandler = std::make_shared<xolotlSolver::PetscSolver3DHandler>();
//	solvHandler->initializeHandlers(materialFactory, tempHandler,
//			networkHandler, opts);
//
//	// Set the solver command line to give the PETSc options and initialize it
//	solver->setCommandLineOptions(opts.getPetscArgc(), opts.getPetscArgv());
//	solver->initialize(solvHandler);
//
//	// Solve and finalize
//	solver->solve();
//	solver->finalize();
//
//	// Check the concentrations left in the network
//	auto network = solvHandler->getNetwork();
//	double concs[network->getAll()->size()];
//	network->fillConcentrationsArray(concs);
//
//	// Check some concentrations
//	BOOST_REQUIRE_SMALL(concs[0], 1.0e-27);
//	BOOST_REQUIRE_SMALL(concs[6], 1.0e-4);
//	BOOST_REQUIRE_SMALL(concs[14], 1.0e-120);
//	BOOST_REQUIRE_SMALL(concs[15], 1.0e-106);
//	BOOST_REQUIRE_SMALL(concs[16], 1.0e-92);
//
//	// Remove the created file
//	std::string tempFile = "param.txt";
//	std::remove(tempFile.c_str());
//}

=======
 */BOOST_AUTO_TEST_SUITE (PetscSolverTester_testSuite)

/**
 * This operation checks the fluxs from the reactant as best as is possible
 * given that it requires external data.
 */
BOOST_AUTO_TEST_CASE(checkDOFConversion) {

	// Local Declarations
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/reactants/testfiles/tungsten.txt");
	string networkFilename = sourceDir + pathToFile;

	BOOST_TEST_MESSAGE(
			"PetscSolverTester Message: Network filename is: " << networkFilename);

	// Load the input file from the master task
	shared_ptr<istream> networkStream = make_shared<ifstream>(networkFilename);

	// Create a network loader and set the istream on every MPI task
	shared_ptr<PSIClusterNetworkLoader> networkLoader = make_shared<
			PSIClusterNetworkLoader>(
			std::make_shared<xolotlPerf::DummyHandlerRegistry>());
	networkLoader->setInputstream(networkStream);
	// Load the network
	shared_ptr<ReactionNetwork> network = networkLoader->load();

	BOOST_TEST_MESSAGE("PetscSolverTester Message: Network loaded");
}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
BOOST_AUTO_TEST_SUITE_END()
