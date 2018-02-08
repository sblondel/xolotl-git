// Includes
#include <PetscSolver.h>
#include <HDF5NetworkLoader.h>
#include <HDF5Utils.h>

using namespace xolotlCore;

/*
 C_t =  -D*C_xx + A*C_x + F(C) + R(C) + D(C) from Brian Wirth's SciDAC project.

 D*C_xx  - diffusion of He and V and I
 A*C_x   - advection of He
 F(C)    - forcing function; He being created.
 R(C)    - reaction terms   (clusters combining)
 D(C)    - dissociation terms (cluster breaking up)

 Sample Options:
 -da_grid_x <nx>						 -- number of grid points in the x direction
 -ts_max_steps <maxsteps>                -- maximum number of time-steps to take
 -ts_final_time <time>                   -- maximum time to compute to
 -ts_dt <size>							 -- initial size of the time step

 */

namespace xolotlSolver {

//Timer for RHSFunction()
std::shared_ptr<xolotlPerf::ITimer> RHSFunctionTimer;

////Timer for RHSJacobian()
std::shared_ptr<xolotlPerf::ITimer> RHSJacobianTimer;

//! Help message
static char help[] =
		"Solves C_t =  -D*C_xx + A*C_x + F(C) + R(C) + D(C) from Brian Wirth's SciDAC project.\n";

// ----- GLOBAL VARIABLES ----- //
extern PetscErrorCode setupPetsc1DMonitor(TS);
extern PetscErrorCode setupPetsc2DMonitor(TS);
extern PetscErrorCode setupPetsc3DMonitor(TS);

void PetscSolver::setupInitialConditions(DM da, Vec C) {
	// Initialize the concentrations in the solution vector
	auto solverHandler = PetscSolver::getSolverHandler();
	solverHandler->initializeConcentration(da, C);

	return;
}

/* ------------------------------------------------------------------- */

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "RHSFunction")
/*
 RHSFunction - Evaluates the right-hand-side of the nonlinear function defining the ODE

 Input Parameters:
 .  ts - the TS context
 .  ftime - the physical time at which the function is evaluated
 .  C - input vector
 .  ptr - optional user-defined context

 Output Parameter:
 .  F - function values
 */
/* ------------------------------------------------------------------- */
<<<<<<< HEAD
PetscErrorCode RHSFunction(TS ts, PetscReal ftime, Vec C, Vec F, void *ptr) {
=======
PetscErrorCode RHSFunction(TS ts, PetscReal ftime, Vec C, Vec F, void *) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Start the RHSFunction Timer
	RHSFunctionTimer->start();

	PetscErrorCode ierr;

	// Get the local data vector from PETSc
	PetscFunctionBeginUser;
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);
	Vec localC;
	ierr = DMGetLocalVector(da, &localC);CHKERRQ(ierr);

	// Scatter ghost points to local vector, using the 2-step process
	// DMGlobalToLocalBegin(),DMGlobalToLocalEnd().
	// By placing code between these two statements, computations can be
	// done while messages are in transition.
	ierr = DMGlobalToLocalBegin(da, C, INSERT_VALUES, localC);CHKERRQ(ierr);
	ierr = DMGlobalToLocalEnd(da, C, INSERT_VALUES, localC);CHKERRQ(ierr);

	// Set the initial values of F
	ierr = VecSet(F, 0.0);CHKERRQ(ierr);

	// Compute the new concentrations
	auto solverHandler = PetscSolver::getSolverHandler();
	solverHandler->updateConcentration(ts, localC, F, ftime);

	// Stop the RHSFunction Timer
	RHSFunctionTimer->stop();

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "RHSJacobian")
/*
 Compute the Jacobian entries based on IFunction() and insert them into the matrix
 */
PetscErrorCode RHSJacobian(TS ts, PetscReal ftime, Vec C, Mat A, Mat J,
<<<<<<< HEAD
		void *ptr) {
=======
		void *) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Start the RHSJacobian timer
	RHSJacobianTimer->start();

	PetscErrorCode ierr;

	// Get the matrix from PETSc
	PetscFunctionBeginUser;
	ierr = MatZeroEntries(J);CHKERRQ(ierr);
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);
	Vec localC;
	ierr = DMGetLocalVector(da, &localC);CHKERRQ(ierr);

	// Get the complete data array
	ierr = DMGlobalToLocalBegin(da, C, INSERT_VALUES, localC);CHKERRQ(ierr);
	ierr = DMGlobalToLocalEnd(da, C, INSERT_VALUES, localC);CHKERRQ(ierr);

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	/* ----- Compute the off-diagonal part of the Jacobian ----- */
<<<<<<< HEAD
	solverHandler->computeOffDiagonalJacobian(ts, localC, J);
=======
	solverHandler->computeOffDiagonalJacobian(ts, localC, J, ftime);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	ierr = MatAssemblyBegin(J, MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	ierr = MatAssemblyEnd(J, MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);

	/* ----- Compute the partial derivatives for the reaction term ----- */
<<<<<<< HEAD
	solverHandler->computeDiagonalJacobian(ts, localC, J);
=======
	solverHandler->computeDiagonalJacobian(ts, localC, J, ftime);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	ierr = MatAssemblyBegin(J, MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	ierr = MatAssemblyEnd(J, MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);

	if (A != J) {
		ierr = MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
		ierr = MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);CHKERRQ(ierr);
	}

	// Stop the RHSJacobian timer
	RHSJacobianTimer->stop();

	PetscFunctionReturn(0);
}

PetscSolver::PetscSolver(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
	Solver(registry) {
	RHSFunctionTimer = handlerRegistry->getTimer("RHSFunctionTimer");
	RHSJacobianTimer = handlerRegistry->getTimer("RHSJacobianTimer");
}

PetscSolver::~PetscSolver() {
}

<<<<<<< HEAD
void PetscSolver::setOptions(const std::map<std::string, std::string>& options) {
=======
void PetscSolver::setOptions(const std::map<std::string, std::string>&) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

void PetscSolver::setupMesh() {
}

void PetscSolver::initialize(std::shared_ptr<ISolverHandler> solverHandler) {
	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Initialize program
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	PetscInitialize(&numCLIArgs, &CLIArgs, (char*) 0, help);

	// Set the solver handler
	Solver::solverHandler = (ISolverHandler *) solverHandler.get();

	return;
}

void PetscSolver::solve() {
	PetscErrorCode ierr;

<<<<<<< HEAD
	// Check the network before getting busy.
	if (!network) {
		throw std::string("PetscSolver Exception: Network not set!");
	}

	// Get the name of the HDF5 file to read the concentrations from
	auto HDF5Loader = (HDF5NetworkLoader *) networkLoader;
	auto fileName = HDF5Loader->getFilename();

	// Get starting conditions from HDF5 file
	int nx = 0, ny = 0, nz = 0;
	double hx = 0.0, hy = 0.0, hz = 0.0;
	HDF5Utils::readHeader(fileName, nx, hx, ny, hy, nz, hz);

	// Create the solver context
	DM da;
	Solver::solverHandler->createSolverContext(da, nx, hx, ny, hy, nz, hz);
=======
	// Create the solver context
	DM da;
	Solver::solverHandler->createSolverContext(da);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Extract global vector from DMDA to hold solution
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	Vec C;
	ierr = DMCreateGlobalVector(da, &C);
	checkPetscError(ierr, "PetscSolver::solve: DMCreateGlobalVector failed.");

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Create timestepping solver context
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	TS ts;
	ierr = TSCreate(PETSC_COMM_WORLD, &ts);
	checkPetscError(ierr, "PetscSolver::solve: TSCreate failed.");
	ierr = TSSetType(ts, TSARKIMEX);
	checkPetscError(ierr, "PetscSolver::solve: TSSetType failed.");
	ierr = TSARKIMEXSetFullyImplicit(ts, PETSC_TRUE);
	checkPetscError(ierr, "PetscSolver::solve: TSARKIMEXSetFullyImplicit failed.");
	ierr = TSSetDM(ts, da);
	checkPetscError(ierr, "PetscSolver::solve: TSSetDM failed.");
	ierr = TSSetProblemType(ts, TS_NONLINEAR);
	checkPetscError(ierr, "PetscSolver::solve: TSSetProblemType failed.");
	ierr = TSSetRHSFunction(ts, NULL, RHSFunction, NULL);
	checkPetscError(ierr, "PetscSolver::solve: TSSetRHSFunction failed.");
	ierr = TSSetRHSJacobian(ts, NULL, NULL, RHSJacobian, NULL);
	checkPetscError(ierr, "PetscSolver::solve: TSSetRHSJacobian failed.");
	ierr = TSSetSolution(ts, C);
	checkPetscError(ierr, "PetscSolver::solve: TSSetSolution failed.");

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Set solver options
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

	// Read the times if the information is in the HDF5 file
<<<<<<< HEAD
=======
	auto fileName = Solver::solverHandler->getNetworkName();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	double time = 0.0, deltaTime = 1.0e-12;
	int tempTimeStep = -2;
	if (HDF5Utils::hasConcentrationGroup(fileName, tempTimeStep)) {
		HDF5Utils::readTimes(fileName, tempTimeStep, time, deltaTime);
	}

	ierr = TSSetInitialTimeStep(ts, time, deltaTime);
	checkPetscError(ierr, "PetscSolver::solve: TSSetInitialTimeStep failed.");
	ierr = TSSetFromOptions(ts);
	checkPetscError(ierr, "PetscSolver::solve: TSSetFromOptions failed.");

	// Switch on the number of dimensions to set the monitors
	int dim = Solver::solverHandler->getDimension();
	switch (dim) {
		case 1:
			// One dimension
			ierr = setupPetsc1DMonitor(ts);
			checkPetscError(ierr, "PetscSolver::solve: setupPetsc1DMonitor failed.");
			break;
		case 2:
			// Two dimensions
			ierr = setupPetsc2DMonitor(ts);
			checkPetscError(ierr, "PetscSolver::solve: setupPetsc2DMonitor failed.");
			break;
		case 3:
			// Three dimensions
			ierr = setupPetsc3DMonitor(ts);
			checkPetscError(ierr, "PetscSolver::solve: setupPetsc3DMonitor failed.");
			break;
		default:
			throw std::string(
							"PetscSolver Exception: Wrong number of dimensions "
							"to set the monitors.");
	}

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Set initial conditions
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	setupInitialConditions(da, C);

	// Set the output precision for std::out
	std::cout.precision(16);

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Solve the ODE system
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	if (ts != NULL && C != NULL) {
		ierr = TSSolve(ts, C);
		checkPetscError(ierr, "PetscSolver::solve: TSSolve failed.");
	} else {
		throw std::string(
				"PetscSolver Exception: Unable to solve! Data not configured properly.");
	}

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Free work space.
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	ierr = VecDestroy(&C);
	checkPetscError(ierr, "PetscSolver::solve: VecDestroy failed.");
	ierr = TSDestroy(&ts);
	checkPetscError(ierr, "PetscSolver::solve: TSDestroy failed.");
	ierr = DMDestroy(&da);
	checkPetscError(ierr, "PetscSolver::solve: DMDestroy failed.");

	return;
}

void PetscSolver::finalize() {
	PetscErrorCode ierr;

	ierr = PetscFinalize();
	checkPetscError(ierr, "PetscSolver::finalize: PetscFinalize failed.");

	return;
}

} /* end namespace xolotlSolver */
