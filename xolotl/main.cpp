/**
 * Main.c, currently only able to load clusters
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cassert>
#include <Reactant.h>
<<<<<<< HEAD
#include <PSIClusterNetworkLoader.h>
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <PetscSolver.h>
#include <mpi.h>
#include <MPIUtils.h>
#include <Options.h>
#include <xolotlPerf.h>
#include <IMaterialFactory.h>
#include <TemperatureHandlerFactory.h>
#include <VizHandlerRegistryFactory.h>
<<<<<<< HEAD
#include <HDF5NetworkLoader.h>
#include <SolverHandlerFactory.h>
#include <ISolverHandler.h>
=======
#include <INetworkLoader.h>
#include <IReactionNetwork.h>
#include <SolverHandlerFactory.h>
#include <ISolverHandler.h>
#include <IReactionHandlerFactory.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <ctime>

using namespace std;
using std::shared_ptr;
namespace xperf = xolotlPerf;

<<<<<<< HEAD

//! This operation prints the start message
void printStartMessage() {
	std::cout << "Starting Xolotl Plasma-Surface Interactions Simulator" << std::endl;
=======
//! This operation prints the start message
void printStartMessage() {
	std::cout << "Starting Xolotl Plasma-Surface Interactions Simulator"
			<< std::endl;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// TODO! Print copyright message
	// Print date and time
	std::time_t currentTime = std::time(NULL);
	std::cout << std::asctime(std::localtime(&currentTime)); // << std::endl;
}

<<<<<<< HEAD
std::shared_ptr<xolotlFactory::IMaterialFactory> initMaterial(Options &options) {
	// Create the material factory
	auto materialFactory = xolotlFactory::IMaterialFactory::createMaterialFactory(options.getMaterial(),
			options.getDimensionNumber());
=======
std::shared_ptr<xolotlFactory::IMaterialFactory> initMaterial(
		Options &options) {
	// Create the material factory
	auto materialFactory =
			xolotlFactory::IMaterialFactory::createMaterialFactory(
					options.getMaterial(), options.getDimensionNumber());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

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

<<<<<<< HEAD

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
<<<<<<< HEAD
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry, 
		std::shared_ptr<xolotlFactory::IMaterialFactory> material,
		std::shared_ptr<xolotlCore::ITemperatureHandler> tempHandler,
		std::shared_ptr<xolotlSolver::ISolverHandler> solvHandler,
		Options &options) {
	// Initialize the solver handler
	solvHandler->initializeHandlers(material, tempHandler, options);
=======
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry,
		std::shared_ptr<xolotlFactory::IMaterialFactory> material,
		std::shared_ptr<xolotlCore::ITemperatureHandler> tempHandler,
		std::shared_ptr<xolotlCore::IReactionNetwork> networkHandler,
		std::shared_ptr<xolotlSolver::ISolverHandler> solvHandler,
		Options &options) {
	// Initialize the solver handler
	solvHandler->initializeHandlers(material, tempHandler, networkHandler, options);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Setup the solver
	auto solverInitTimer = handlerRegistry->getTimer("initSolver");
	solverInitTimer->start();
	std::shared_ptr<xolotlSolver::PetscSolver> solver = std::make_shared<
			xolotlSolver::PetscSolver>(handlerRegistry);
<<<<<<< HEAD
	solver->setCommandLineOptions(options.getPetscArgc(), options.getPetscArgv());
=======
	solver->setCommandLineOptions(options.getPetscArgc(),
			options.getPetscArgv());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	solver->initialize(solvHandler);
	solverInitTimer->stop();

	return solver;
}

void launchPetscSolver(std::shared_ptr<xolotlSolver::PetscSolver> solver,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry) {

<<<<<<< HEAD
    xperf::IHardwareCounter::SpecType hwctrSpec;
    hwctrSpec.push_back( xperf::IHardwareCounter::FPOps );
    hwctrSpec.push_back( xperf::IHardwareCounter::Cycles );
    hwctrSpec.push_back( xperf::IHardwareCounter::L3CacheMisses );

	// Launch the PetscSolver
	auto solverTimer = handlerRegistry->getTimer("solve");
    auto solverHwctr = handlerRegistry->getHardwareCounter( "solve", hwctrSpec );
	solverTimer->start();
    solverHwctr->start();
	solver->solve();
    solverHwctr->stop();
	solverTimer->stop();
}

std::shared_ptr<PSIClusterNetworkLoader> setUpNetworkLoader(int rank,
		MPI_Comm comm, const std::string& networkFilename,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {

	// Create a HDF5NetworkLoader
	std::shared_ptr<HDF5NetworkLoader> networkLoader;
	networkLoader = std::make_shared<HDF5NetworkLoader>(registry);
	// Give the networkFilename to the network loader
	networkLoader->setFilename(networkFilename);

	return networkLoader;
}


=======
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
}

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
//! Main program
int main(int argc, char **argv) {

	// Local Declarations
	int rank;

	// Check the command line arguments.
	// Skip the executable name before parsing
	argc -= 1; // one for the executable name
	argv += 1; // one for the executable name
	Options opts;
<<<<<<< HEAD
	opts.readParams(argc, argv);
=======
	opts.readParams(argv);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	if (!opts.shouldRun()) {
		return opts.getExitCode();
	}

	// Skip the name of the parameter file that was just used.
	// The arguments should be empty now.
	argc -= 1;
	argv += 1;

	// Extract the argument for the file name
	std::string networkFilename = opts.getNetworkFilename();
	assert(!networkFilename.empty());

	try {
		// Set up our performance data infrastructure.
<<<<<<< HEAD
        xperf::initialize(opts.getPerfHandlerType());
=======
		xperf::initialize(opts.getPerfHandlerType());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Initialize MPI. We do this instead of leaving it to some
		// other package (e.g., PETSc), because we want to avoid problems
		// with overlapping Timer scopes.
		MPI_Init(&argc, &argv);

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
<<<<<<< HEAD
		assert(tempInitOK);
		// Set up the visualization infrastructure.
		bool vizInitOK = initViz(opts.useVizStandardHandlers());
		assert(vizInitOK);
=======
		if (!tempInitOK)
			return EXIT_FAILURE;
		// Set up the visualization infrastructure.
		bool vizInitOK = initViz(opts.useVizStandardHandlers());
		if (!vizInitOK)
			return EXIT_FAILURE;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Access the temperature handler registry to get the temperature
		auto tempHandler = xolotlFactory::getTemperatureHandler();

		// Access our performance handler registry to obtain a Timer
		// measuring the runtime of the entire program.
		auto handlerRegistry = xolotlPerf::getHandlerRegistry();
		auto totalTimer = handlerRegistry->getTimer("total");
		totalTimer->start();

		// Initialize and get the solver handler
		bool dimOK = xolotlFactory::initializeDimension(opts);
<<<<<<< HEAD
		assert(dimOK);
		auto solvHandler = xolotlFactory::getSolverHandler();

		// Setup the solver
		auto solver = setUpSolver(handlerRegistry, material,
				tempHandler, solvHandler, opts);

		// Load the network
		auto networkLoadTimer = handlerRegistry->getTimer("loadNetwork");
		networkLoadTimer->start();

		// Set up the network loader
		auto networkLoader = setUpNetworkLoader(rank, MPI_COMM_WORLD,
				networkFilename, handlerRegistry);

		// Give the network loader to PETSc as input
		solver->setNetworkLoader(networkLoader);
		networkLoadTimer->stop();
=======
		if (!dimOK)
			return EXIT_FAILURE;
		auto solvHandler = xolotlFactory::getSolverHandler();

		// Create the network handler factory
		auto networkFactory =
					xolotlFactory::IReactionHandlerFactory::createNetworkFactory(opts.getMaterial());

		// Setup and load the network
		auto networkLoadTimer = handlerRegistry->getTimer("loadNetwork");
		networkLoadTimer->start();
		networkFactory->initializeReactionNetwork(opts, handlerRegistry);
		networkLoadTimer->stop();

		// Get the network handler
		auto networkHandler = networkFactory->getNetworkHandler();

		// Setup the solver
		auto solver = setUpSolver(handlerRegistry, material, tempHandler, networkHandler,
				solvHandler, opts);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Launch the PetscSolver
		launchPetscSolver(solver, handlerRegistry);

		// Finalize our use of the solver.
		auto solverFinalizeTimer = handlerRegistry->getTimer("solverFinalize");
		solverFinalizeTimer->start();
		solver->finalize();
		solverFinalizeTimer->stop();

		totalTimer->stop();

<<<<<<< HEAD
        // Report statistics about the performance data collected during
        // the run we just completed.
        xperf::PerfObjStatsMap<xperf::ITimer::ValType> timerStats;
        xperf::PerfObjStatsMap<xperf::IEventCounter::ValType> counterStats;
        xperf::PerfObjStatsMap<xperf::IHardwareCounter::CounterType> hwCtrStats;
        handlerRegistry->collectStatistics( timerStats, counterStats, hwCtrStats );
        if( rank == 0 )
        {
            handlerRegistry->reportStatistics( std::cout, 
                                                timerStats, 
                                                counterStats, 
                                                hwCtrStats );
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Aborting." << std::endl;
        return EXIT_FAILURE;

=======
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
		return EXIT_FAILURE;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	} catch (const std::string& error) {
		std::cout << error << std::endl;
		std::cout << "Aborting." << std::endl;
		return EXIT_FAILURE;
	}

	// finalize our use of MPI
	MPI_Finalize();

	return EXIT_SUCCESS;
}
