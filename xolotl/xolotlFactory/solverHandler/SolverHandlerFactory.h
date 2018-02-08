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
<<<<<<< HEAD
bool initializeDimension(xolotlCore::Options &options);
=======
bool initializeDimension(xolotlCore::Options &options,
		xolotlCore::IReactionNetwork& network);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

/**
 * Access the created solver handler.
 *
<<<<<<< HEAD
 *  @return A pointer to the solver handler.
 */
std::shared_ptr<xolotlSolver::ISolverHandler> getSolverHandler();
=======
 *  @return The solver handler.
 */
xolotlSolver::ISolverHandler& getSolverHandler();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

}

#endif /* SOLVERHANDLERFACTORY_H */
