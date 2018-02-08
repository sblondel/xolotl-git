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

<<<<<<< HEAD
	//! The network loader that can load the reaction network data.
	PSIClusterNetworkLoader *networkLoader;

	//! The original network created from the network loader.
	PSIClusterReactionNetwork *network;

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	//! The original solver handler.
	static ISolverHandler *solverHandler;

public:

	//! The Constructor
	Solver(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! The Destructor
<<<<<<< HEAD
	virtual ~Solver();
=======
	virtual ~Solver() {};
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

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
<<<<<<< HEAD
	 * This operation sets the PSIClusterNetworkLoader that should be used by
	 * the ISolver to load the ReactionNetwork.
	 * @param networkLoader The PSIClusterNetworkLoader that will load the
	 * network.
	 */
	void setNetworkLoader(
			std::shared_ptr<PSIClusterNetworkLoader> networkLoader);

	/**
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 * This operation returns the solver handler for this solver. This
	 * operation is only for use by solver code and is not part of the
	 * ISolver interface.
	 * @return The advection handler for this solver
	 */
	static ISolverHandler *getSolverHandler() {
		return solverHandler;
	}

protected:

<<<<<<< HEAD
    /**
     * The performance handler registry that will be used
     * for this class.
     */
    std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;

}; //end class Solver
=======
	/**
	 * The performance handler registry that will be used
	 * for this class.
	 */
	std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;

};
//end class Solver
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

} /* end namespace xolotlSolver */
#endif
