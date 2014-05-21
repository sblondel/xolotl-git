/**
 * Main.c, currently only able to load clusters
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <Reactant.h>
<<<<<<< HEAD
#include <PetscSolver.h>
#include <mpi.h>
#include <MPIUtils.h>
#include <Options.h>
#include <xolotlPerf.h>
#include <IMaterialFactory.h>
#include <TemperatureHandlerFactory.h>
#include <VizHandlerRegistryFactory.h>
#include <INetworkLoader.h>
#include <IReactionNetwork.h>
#include <SolverHandlerFactory.h>
#include <ISolverHandler.h>
#include <IReactionHandlerFactory.h>
#include <ctime>

using namespace std;
using std::shared_ptr;
namespace xperf = xolotlPerf;

//! This operation prints the start message
void printStartMessage() {
	std::cout << "Starting Xolotl Plasma-Surface Interactions Simulator"
			<< std::endl;
	// TODO! Print copyright message
	// Print date and time
	std::time_t currentTime = std::time(NULL);
	std::cout << std::asctime(std::localtime(&currentTime)); // << std::endl;
}

std::shared_ptr<xolotlFactory::IMaterialFactory> initMaterial(
		Options &options) {
	// Create the material factory
	auto materialFactory =
			xolotlFactory::IMaterialFactory::createMaterialFactory(
					options.getMaterial(), options.getDimensionNumber());

	// Initialize it with the options
	materialFactory->initializeMaterial(options);

	return materialFactory;
}

bool initTemp(Options &options) {

	bool tempInitOK = xolotlFactory::initializeTempHandler(options);
	if (!tempInitOK) {
		std::cerr << "Unable to initialize requested temperature.  Aborting"
				<< std::endl;
		return EXIT_FAILURE;
	} else
		return tempInitOK;
}

bool initViz(bool opts) {

	bool vizInitOK = xolotlFactory::initializeVizHandler(opts);
	if (!vizInitOK) {
		std::cerr
				<< "Unable to initialize requested visualization infrastructure. "
				<< "Aborting" << std::endl;
		return EXIT_FAILURE;
	} else
		return vizInitOK;
}

std::shared_ptr<xolotlSolver::PetscSolver> setUpSolver(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry,
		std::shared_ptr<xolotlFactory::IMaterialFactory> material,
		std::shared_ptr<xolotlCore::ITemperatureHandler> tempHandler,
		std::shared_ptr<xolotlCore::IReactionNetwork> networkHandler,
		std::shared_ptr<xolotlSolver::ISolverHandler> solvHandler,
		Options &options) {
	// Initialize the solver handler
	solvHandler->initializeHandlers(material, tempHandler, networkHandler,
			options);
=======
#include <PSIClusterNetworkLoader.h>
#include <PetscSolver.h>
#include <mpi.h>
#include <MPIUtils.h>
#include <XolotlOptions.h>
#include <HandlerRegistryFactory.h>
#include <HardwareQuantities.h>
#include <IHandlerRegistry.h>
#include <HDF5NetworkLoader.h>

using namespace std;
using std::shared_ptr;

//! This operation prints the start message
void printStartMessage() {
	cout << "Starting Xolotl Plasma-Surface Interactions Simulator" << endl;
	// TODO! Print copyright message
	// TODO! Print date and time
}

//std::vector<xolotlPerf::HardwareQuantities> declareHWcounters();
//bool initPerf(bool opts, std::vector<xolotlPerf::HardwareQuantities> hwq);
//xolotlSolver::PetscSolver setUpSolver(std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry, int argc, char **argv);
//void launchPetscSolver(xolotlSolver::PetscSolver solver, std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry);
//std::shared_ptr<PSIClusterNetworkLoader> setUpNetworkLoader(int rank, MPI_Comm comm, std::string networkFilename);

std::vector<xolotlPerf::HardwareQuantities> declareHWcounters() {

	// Indicate we want to monitor some important hardware counters.
	std::vector<xolotlPerf::HardwareQuantities> hwq;

	hwq.push_back(xolotlPerf::FP_OPS);
	hwq.push_back(xolotlPerf::L1_CACHE_MISS);

	return hwq;
}

bool initPerf(bool opts, std::vector<xolotlPerf::HardwareQuantities> hwq) {

	bool perfInitOK = xolotlPerf::initialize(opts, hwq);
	if (!perfInitOK) {
		std::cerr
				<< "Unable to initialize requested performance data infrastructure. "
				<< "Aborting" << std::endl;
		return EXIT_FAILURE;
	} else
		return perfInitOK;
}

xolotlSolver::PetscSolver setUpSolver(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry, int argc,
		char **argv) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	// Setup the solver
	auto solverInitTimer = handlerRegistry->getTimer("initSolver");
	solverInitTimer->start();
<<<<<<< HEAD
	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
			xolotlSolver::PetscSolver>(handlerRegistry);
	solver->setCommandLineOptions(options.getPetscArgc(),
			options.getPetscArgv());
	solver->initialize(solvHandler);
=======
	xolotlSolver::PetscSolver solver(handlerRegistry);
	solver.setCommandLineOptions(argc, argv);
	solver.initialize();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	solverInitTimer->stop();

	return solver;
}

<<<<<<< HEAD
void launchPetscSolver(std::shared_ptr<xolotlSolver::PetscSolver> solver,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry) {

	xperf::IHardwareCounter::SpecType hwctrSpec;
	hwctrSpec.push_back(xperf::IHardwareCounter::FPOps);
	hwctrSpec.push_back(xperf::IHardwareCounter::Cycles);
	hwctrSpec.push_back(xperf::IHardwareCounter::L3CacheMisses);

	// Launch the PetscSolver
	auto solverTimer = handlerRegistry->getTimer("solve");
	auto solverHwctr = handlerRegistry->getHardwareCounter("solve", hwctrSpec);
	solverTimer->start();
	solverHwctr->start();
	solver->solve();
	solverHwctr->stop();
	solverTimer->stop();
=======
void launchPetscSolver(xolotlSolver::PetscSolver solver,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry) {

	// Launch the PetscSolver
	auto solverTimer = handlerRegistry->getTimer("solve");
	solverTimer->start();
	// Create object to handle incident flux calculations
	auto fitFluxHandler = std::make_shared<xolotlSolver::FitFluxHandler>();
	// Create object to handle temperature
	auto tempHandler = std::make_shared<xolotlSolver::TemperatureHandler>();
	solver.solve(fitFluxHandler, tempHandler);
	solverTimer->stop();

}

std::shared_ptr<PSIClusterNetworkLoader> setUpNetworkLoader(int rank,
		MPI_Comm comm, std::string networkFilename,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {

	// Create a HDF5NetworkLoader
	std::shared_ptr<HDF5NetworkLoader> networkLoader;
	networkLoader = std::make_shared<HDF5NetworkLoader>(registry);
	// Give the networkFilename to the network loader
	networkLoader->setFilename(networkFilename);

//	std::shared_ptr<PSIClusterNetworkLoader> networkLoader;
//	shared_ptr<std::istream> networkStream;
//
//	// Setup the master
//	if (rank == 0) {
//		// Say hello
//		printStartMessage();
//		// Set the input stream on the master
//		networkStream = make_shared<std::ifstream>(networkFilename);
//	}
//
//	// Broadcast the stream to all worker tasks
//	networkLoader = std::make_shared<PSIClusterNetworkLoader>(registry);
//	networkStream = xolotlCore::MPIUtils::broadcastStream(networkStream, 0,
//			comm);
//
//	// Create a network loader and set the stream on every MPI task
//	networkLoader->setInputstream(networkStream);

	return networkLoader;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

//! Main program
int main(int argc, char **argv) {

	// Local Declarations
	int rank;
<<<<<<< HEAD
	int ret = EXIT_SUCCESS;

	// Check the command line arguments.
	// Skip the executable name before parsing
	argc -= 1; // one for the executable name
	argv += 1; // one for the executable name
	Options opts;
	opts.readParams(argv);
	if (!opts.shouldRun()) {
		return opts.getExitCode();
	}

	// Skip the name of the parameter file that was just used.
	// The arguments should be empty now.
	argc -= 1;
	argv += 1;

	try {
		// Set up our performance data infrastructure.
		xperf::initialize(opts.getPerfHandlerType());

		// Initialize MPI. We do this instead of leaving it to some
=======

	// Check the command line arguments.
	// Skip the executable name before parsing.
	argc -= 1;  // one for the executable name
	argv += 1;  // one for the executable name
	XolotlOptions xopts;
	int nOptsUsed = xopts.parseCommandLine(argc, argv);
	if (!xopts.shouldRun()) {
		return xopts.getExitCode();
	}
	argc -= nOptsUsed;
	argv += nOptsUsed;

	// Extract the argument for the file name
	std::string networkFilename = xopts.getNetworkFilename();
	assert(!networkFilename.empty());

	try {
		// Set up our performance data infrastructure.
		// Indicate we want to monitor some important hardware counters.
		auto hwq = declareHWcounters();
		auto perfInitOK = initPerf(xopts.useStandardHandlers(), hwq);

		// Initialize MPI.  We do this instead of leaving it to some
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
		// other package (e.g., PETSc), because we want to avoid problems
		// with overlapping Timer scopes.
		MPI_Init(&argc, &argv);

<<<<<<< HEAD
		// Get the MPI rank
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		if (rank == 0) {
			// Print the start message
			printStartMessage();
		}

		// Set up the material infrastructure that is used to calculate flux
		auto material = initMaterial(opts);
		// Set up the temperature infrastructure
		bool tempInitOK = initTemp(opts);
		if (!tempInitOK) {
			throw std::runtime_error("Unable to initialize temperature.");
		}
		// Set up the visualization infrastructure.
		bool vizInitOK = initViz(opts.useVizStandardHandlers());
		if (!vizInitOK) {
			throw std::runtime_error(
					"Unable to initialize visualization infrastructure.");
		}

		// Access the temperature handler registry to get the temperature
		auto tempHandler = xolotlFactory::getTemperatureHandler();

		// Access our performance handler registry to obtain a Timer
		// measuring the runtime of the entire program.
=======
		// Access our handler registry to obtain a Timer
		// measuring the runtime of the entire program.
		// NOTE: these long template types could be replaced with 'auto'
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
		auto handlerRegistry = xolotlPerf::getHandlerRegistry();
		auto totalTimer = handlerRegistry->getTimer("total");
		totalTimer->start();

<<<<<<< HEAD
		// Initialize and get the solver handler
		bool dimOK = xolotlFactory::initializeDimension(opts);
		if (!dimOK) {
			throw std::runtime_error(
					"Unable to initialize dimension from inputs.");
		}
		auto solvHandler = xolotlFactory::getSolverHandler();

		// Create the network handler factory
		auto networkFactory =
				xolotlFactory::IReactionHandlerFactory::createNetworkFactory(
						opts.getMaterial());

		// Setup and load the network
		auto networkLoadTimer = handlerRegistry->getTimer("loadNetwork");
		networkLoadTimer->start();
		networkFactory->initializeReactionNetwork(opts, handlerRegistry);
		networkLoadTimer->stop();

		// Get the network handler
		auto networkHandler = networkFactory->getNetworkHandler();

		// Setup the solver
		auto solver = setUpSolver(handlerRegistry, material, tempHandler,
				networkHandler, solvHandler, opts);
=======
		// Setup the solver
		auto solver = setUpSolver(handlerRegistry, argc, argv);

		// Load the network
		auto networkLoadTimer = handlerRegistry->getTimer("loadNetwork");
		networkLoadTimer->start();

		// Get the MPI rank
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		// Set up the network loader
		auto networkLoader = setUpNetworkLoader(rank, MPI_COMM_WORLD,
				networkFilename, handlerRegistry);

		// Give the network loader to PETSc as input
		solver.setNetworkLoader(networkLoader);
		networkLoadTimer->stop();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

		// Launch the PetscSolver
		launchPetscSolver(solver, handlerRegistry);

		// Finalize our use of the solver.
		auto solverFinalizeTimer = handlerRegistry->getTimer("solverFinalize");
		solverFinalizeTimer->start();
<<<<<<< HEAD
		solver->finalize();
		solverFinalizeTimer->stop();

		totalTimer->stop();

		// Report statistics about the performance data collected during
		// the run we just completed.
		xperf::PerfObjStatsMap<xperf::ITimer::ValType> timerStats;
		xperf::PerfObjStatsMap<xperf::IEventCounter::ValType> counterStats;
		xperf::PerfObjStatsMap<xperf::IHardwareCounter::CounterType> hwCtrStats;
		handlerRegistry->collectStatistics(timerStats, counterStats,
				hwCtrStats);
		if (rank == 0) {
			handlerRegistry->reportStatistics(std::cout, timerStats,
					counterStats, hwCtrStats);
		}
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::cerr << "Aborting." << std::endl;
		ret = EXIT_FAILURE;
	} catch (const std::string& error) {
		std::cout << error << std::endl;
		std::cout << "Aborting." << std::endl;
		ret = EXIT_FAILURE;
=======
		solver.finalize();
		solverFinalizeTimer->stop();
		totalTimer->stop();

		// Report the performance data about the run we just completed
		// TODO Currently, this call writes EventCounter data to the
		// given stream, but Timer and any hardware counter data is
		// written by the underlying timing library to files, one per process.
		if (rank == 0) {
			handlerRegistry->dump(std::cout);
		}

	} catch (std::string & error) {
		std::cout << error << std::endl;
		std::cout << "Aborting." << std::endl;
		return EXIT_FAILURE;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	}

	// finalize our use of MPI
	MPI_Finalize();

<<<<<<< HEAD
	return ret;
=======
	// Uncomment if GPTL was built with pmpi disabled
	// Output performance data if pmpi is disabled in GPTL
	// Access the handler registry to output performance data
//    auto handlerRegistry = xolotlPerf::getHandlerRegistry();
//    handlerRegistry->dump(rank);

	return EXIT_SUCCESS;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}
