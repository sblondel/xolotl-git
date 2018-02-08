#ifndef PETSCSOLVER_H
#define PETSCSOLVER_H

// Includes
<<<<<<< HEAD
#include "Solver.h"

namespace xolotlSolver {

#ifndef CHECK_PETSC_ERROR
#define CHECK_PETSC_ERROR
/**
 * This operation checks a PETSc error code and throws an exception with given error message.
 *
 * @param errorCode The PETSc error code.
 * @param errMsg The error message in the thrown exception.
 */
inline void checkPetscError(PetscErrorCode errorCode, const char* errorMsg) {
	if (PetscUnlikely(errorCode))
		throw std::string(errorMsg);
}
#endif

/**
 * This class realizes the ISolver interface to solve the
 * advection-diffusion-reaction problem with the PETSc solvers from Argonne
 * National Laboratory.
 */
class PetscSolver: public Solver {
private:

	/**
	 * This operation configures the initial conditions of the grid in Xolotl.
	 * @param data The DM (data manager) created by PETSc
	 * @param solutionVector The solution vector that contains the PDE
	 * solution and which needs to be initialized.
	 */
	void setupInitialConditions(DM data, Vec solutionVector);
=======
#include "ISolver.h"
#include <PSIClusterNetworkLoader.h>
#include <PSIClusterReactionNetwork.h>
#include <petscsys.h>
#include <petscdmda.h>
#include <memory>

namespace xolotlPerf {
	class IHandlerRegistry;
    class IEventCounter;
};

namespace xolotlSolver {

/**
 * This class realizes the ISolver interface to solve the
 * advection-diffusion-reaction problem with the Petsc solvers from Argonne
 * National Laboratory.
 */
class PetscSolver: public ISolver {

private:

	//! The number command line arguments
	int numCLIArgs;

	//! The command line arguments
	char **CLIArgs;

	//! The network loader that can load the reaction network data.
	std::shared_ptr<PSIClusterNetworkLoader> networkLoader;

	//! The original network created from the network loader.
	static std::shared_ptr<PSIClusterReactionNetwork> network;

	//! The original flux handler created.
	static std::shared_ptr<IFluxHandler> fluxHandler;

	//! The original temperature handler created.
	static std::shared_ptr<ITemperatureHandler> temperatureHandler;

	/**
	 * This operation fills the diagonal block of the matrix. The diagonal
	 * block in Xolotl represents the coupling between different reactants
	 * via their reactions.
	 * @param diagFill The diagonal block of the matrix.
	 * @param diagFillSize The number of PetscInts in the diagonal block.
	 * @return The error code. 0 if there is no error.
	 */
	PetscErrorCode getDiagonalFill(PetscInt *diagFill, int diagFillSize);

	/**
	 * This operation configures the initial conditions of the grid in Xolotl.
	 * @param data The DM (data manager) created by Petsc
	 * @param solutionVector The solution vector that contains the PDE
	 * solution and which needs to be initialized.
	 * @return The error code. 0 if there is no error.
	 */
	PetscErrorCode setupInitialConditions(DM data, Vec solutionVector);

	//! The Constructor
	PetscSolver();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	//! The Constructor
	PetscSolver(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry);

	//! The Destructor
	~PetscSolver();

	/**
<<<<<<< HEAD
=======
	 * This operation transfers the input arguments passed to the program on
	 * startup to the solver. These options are static options specified at
	 * the start of the program whereas the options passed to setOptions() may
	 * change.
	 * @param argc The number of command line arguments
	 * @param argv The array of command line arguments
	 */
	void setCommandLineOptions(int argc, char **argv);

	/**
	 * This operation sets the PSIClusterNetworkLoader that should be used by
	 * the ISolver to load the ReactionNetwork.
	 * @param networkLoader The PSIClusterNetworkLoader that will load the
	 * network.
	 */
	void setNetworkLoader(
			std::shared_ptr<PSIClusterNetworkLoader> networkLoader);

	/**
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * This operation sets the run-time options of the solver. The map is a set
	 * of key-value std::string pairs that are interpreted by the solver. These
	 * options may change during execution, but it is up to Solvers to monitor
	 * the map for changes and they may do so at their discretion.
	 * @param options The set of options as key-value pairs with option names
	 * for keys and associated values mapped to those keys. A relevant example
	 * is "startTime" and "0.01" where both are of type std::string.
	 */
<<<<<<< HEAD
	void setOptions(const std::map<std::string, std::string>& options);
=======
	void setOptions(std::map<std::string, std::string> options);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation sets up the mesh that will be used by the solver and
	 * initializes the data on that mesh. This operation will throw an exception
	 * of type std::string if the mesh can not be setup.
	 */
	void setupMesh();

	/**
	 * This operation performs all necessary initialization for the solver
	 * possibly including but not limited to setting up MPI and loading initial
	 * conditions. If the solver can not be initialized, this operation will
	 * throw an exception of type std::string.
<<<<<<< HEAD
	 * @param solverHandler The solver handler
	 */
	void initialize(std::shared_ptr<ISolverHandler> solverHandler);
=======
	 */
	void initialize();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation directs the Solver to perform the solve. If the solve
	 * fails, it will throw an exception of type std::string.
<<<<<<< HEAD
	 */
	void solve();
=======
	 * @param fluxHandler The flux handler that will be used when performing
	 * the solve
	 */
	void solve(std::shared_ptr<IFluxHandler> fluxHandler,
			std::shared_ptr<ITemperatureHandler> temperatureHandler);

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation performs all necessary finalization for the solver
	 * including but not limited to cleaning up memory, finalizing MPI and
	 * printing diagnostic information. If the solver can not be finalized,
	 * this operation will throw an exception of type std::string.
	 */
	void finalize();
<<<<<<< HEAD
	
}; //end class PetscSolver

} /* end namespace xolotlSolver */

// Some compilers (e.g., recent versions of Intel) define __func__ 
// to include the namespace or class scope when compiled with the C++11
// support enabled.  Others don't.  Because PETSc's PetscFunctionBeginUser
// does a straight string comparison between what we call the function name
// and what it determines from the compiler, we need a way to provide
// either the scoped name or the unscoped name.
#if defined(__ICC) || defined(__INTEL_COMPILER)
#  define Actual__FUNCT__(sname,fname)  sname "::" fname
#else
#  define Actual__FUNCT__(sname,fname)  fname
#endif /* if it is the Intel compiler */

=======

	/**
	 * This operation returns the network loaded for this solver. This
	 * operation is only for use by PETSc code and is not part of the
	 * ISolver interface.
	 * @return The reaction network loaded for this solver
	 */
	static std::shared_ptr<PSIClusterReactionNetwork> getNetwork() {
		return network;
	}

	/**
	 * This operation returns the flux handler for this solver. This
	 * operation is only for use by PETSc code and is not part of the
	 * ISolver interface.
	 * @return The flux handler for this solver
	 */
	static std::shared_ptr<IFluxHandler> getFluxHandler() {
		return fluxHandler;
	}

	/**
	 * This operation returns the temperature handler for this solver. This
	 * operation is only for use by PETSc code and is not part of the
	 * ISolver interface.
	 * @return The temperature handler for this solver
	 */
	static std::shared_ptr<ITemperatureHandler> getTemperatureHandler() {
		return temperatureHandler;
	}

protected:

    /**
     * The performance handler registry that will be used
     * for this class.
     */
    std::shared_ptr<xolotlPerf::IHandlerRegistry> handlerRegistry;



}; //end class PetscSolver

} /* end namespace xolotlSolver */
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#endif
