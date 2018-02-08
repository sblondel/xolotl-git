#ifndef SOLVER_H
#define SOLVER_H

// Includes
#include "ISolver.h"

namespace xolotlSolver {

/**
 * This class and its subclasses realize the ISolver interface to solve the
 * advection-diffusion-reaction problem with currently supported solvers.
 */
class Solver: public ISolver {
protected:

	//! The number command line arguments
	int numCLIArgs;

	//! The command line arguments
	char **CLIArgs;

	//! The original solver handler.
<<<<<<< HEAD
	static ISolverHandler *solverHandler;

public:

	//! The Constructor
	Solver(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! The Destructor
	virtual ~Solver() {};
=======
	static ISolverHandler* solverHandler;

public:

	/**
	 * Default constructor, deleted because we must have arguments to construct.
	 */
	Solver() = delete;

	//! Constuct a solver.
	Solver(ISolverHandler& _solverHandler,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! The Destructor
	virtual ~Solver() {
	}
	;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation transfers the input arguments passed to the program on
	 * startup to the solver. These options are static options specified at
	 * the start of the program whereas the options passed to setOptions() may
	 * change.
	 * @param argc The number of command line arguments
	 * @param argv The array of command line arguments
	 */
	void setCommandLineOptions(int argc, char **argv);

	/**
	 * This operation returns the solver handler for this solver. This
	 * operation is only for use by solver code and is not part of the
	 * ISolver interface.
	 * @return The advection handler for this solver
	 */
<<<<<<< HEAD
	static ISolverHandler *getSolverHandler() {
		return solverHandler;
=======
	static ISolverHandler& getSolverHandler() {
		return *solverHandler;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

protected:

	/**
	 * The performance handler registry that will be used
	 * for this class.
	 */
	std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;

};
//end class Solver

} /* end namespace xolotlSolver */
#endif
