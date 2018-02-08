#ifndef SOLVERHANDLERFACTORY_H
#define SOLVERHANDLERFACTORY_H

#include <memory>
#include <ISolverHandler.h>
#include <Options.h>

namespace xolotlFactory {

/**
 * Build the desired type of solver.
 *
 * @param options Options for the program
 * @return True if the solver handler was created successfully.
 */
bool initializeDimension(xolotlCore::Options &options);

/**
 * Access the created solver handler.
 *
 *  @return A pointer to the solver handler.
 */
std::shared_ptr<xolotlSolver::ISolverHandler> getSolverHandler();

<<<<<<< HEAD
};
=======
}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

#endif /* SOLVERHANDLERFACTORY_H */
