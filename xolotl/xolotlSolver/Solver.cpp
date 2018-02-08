// Includes
#include <Solver.h>
<<<<<<< HEAD
#include <HDF5NetworkLoader.h>
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

using namespace xolotlCore;

namespace xolotlSolver {

// Allocate the static solver handler
ISolverHandler *Solver::solverHandler;

Solver::Solver(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
	numCLIArgs(0), CLIArgs(NULL), handlerRegistry(registry) {
}

<<<<<<< HEAD
Solver::~Solver() {
	// std::cerr << "Destroying a Solver" << std::endl;

	// Break "pointer" cycles so that network, clusters, reactants
	// will deallocate when the std::shared_ptrs owning them 
	// are destroyed.
	network->askReactantsToReleaseNetwork();
}

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
void Solver::setCommandLineOptions(int argc, char **argv) {
	// Keep the arguments
	numCLIArgs = argc;
	CLIArgs = argv;
}

<<<<<<< HEAD
void Solver::setNetworkLoader(
		std::shared_ptr<PSIClusterNetworkLoader> networkLoader) {

	// Store the loader and load the network
	this->networkLoader = (PSIClusterNetworkLoader *) networkLoader.get();
	network = (PSIClusterReactionNetwork *) networkLoader->load().get();

	// Debug output
	// Get the processor id
	int procId;
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	if (procId == 0) {
		std::cout << "\nSolver Message: " << "Master loaded network of size "
				<< network->size() << "." << std::endl;
	}

	// Get the name of the HDF5 file to give to the solver handler
	auto HDF5Loader = (HDF5NetworkLoader *) this->networkLoader;
	auto fileName = HDF5Loader->getFilename();

	// Set the network in the solver handler
	Solver::solverHandler->initializeNetwork(fileName, network);

	return;
}

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
} /* end namespace xolotlSolver */
