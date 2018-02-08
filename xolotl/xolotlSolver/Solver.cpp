// Includes
#include <Solver.h>

using namespace xolotlCore;

namespace xolotlSolver {

<<<<<<< HEAD
// Allocate the static solver handler
ISolverHandler *Solver::solverHandler;

Solver::Solver(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
	numCLIArgs(0), CLIArgs(NULL), handlerRegistry(registry) {
=======
ISolverHandler* Solver::solverHandler = nullptr;

Solver::Solver(ISolverHandler& _solverHandler,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		numCLIArgs(0), CLIArgs(NULL), handlerRegistry(registry) {

	solverHandler = &_solverHandler;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

void Solver::setCommandLineOptions(int argc, char **argv) {
	// Keep the arguments
	numCLIArgs = argc;
	CLIArgs = argv;
}

} /* end namespace xolotlSolver */
