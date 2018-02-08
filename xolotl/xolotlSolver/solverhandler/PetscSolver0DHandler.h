#ifndef PETSCSOLVER0DHANDLER_H
#define PETSCSOLVER0DHANDLER_H

// Includes
#include "PetscSolverHandler.h"

namespace xolotlSolver {

/**
 * This class is a subclass of PetscSolverHandler and implement all the methods needed
 * to solve the ADR equations in 0D using PETSc from Argonne National Laboratory.
 */
class PetscSolver0DHandler: public PetscSolverHandler {

public:

<<<<<<< HEAD
	//! The Constructor
	PetscSolver0DHandler() {
=======
	/**
	 * Construct a PetscSolver0DHandler.
	 *
	 * @param _network The reaction network to use.
	 */
	PetscSolver0DHandler() = delete;

	/**
	 * Construct a PetscSolver0DHandler.
	 *
	 * @param _network The reaction network to use.
	 */
	PetscSolver0DHandler(xolotlCore::IReactionNetwork& _network) :
			PetscSolverHandler(_network) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	//! The Destructor
	~PetscSolver0DHandler() {
	}

	/**
	 * Create everything needed before starting to solve.
	 * \see ISolverHandler.h
	 */
	void createSolverContext(DM &da);

	/**
	 * Initialize the concentration solution vector.
	 * \see ISolverHandler.h
	 */
	void initializeConcentration(DM &da, Vec &C);

	/**
	 * Compute the new concentrations for the RHS function given an initial
	 * vector of concentrations. Apply the diffusion, advection and all the reactions.
	 * \see ISolverHandler.h
	 */
	void updateConcentration(TS &ts, Vec &localC, Vec &F, PetscReal ftime);

	/**
	 * Compute the off-diagonal part of the Jacobian which is related to cluster's motion.
	 * \see ISolverHandler.h
	 */
<<<<<<< HEAD
	void computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J, PetscReal ftime);
=======
	void computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J,
			PetscReal ftime);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the diagonal part of the Jacobian which is related to cluster reactions.
	 * \see ISolverHandler.h
	 */
	void computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J, PetscReal ftime);

	/**
	 * Get the position of the surface.
	 * \see ISolverHandler.h
	 */
	int getSurfacePosition(int j = -1, int k = -1) const {
		return 0;
	}

	/**
	 * Set the position of the surface.
	 * \see ISolverHandler.h
	 */
	void setSurfacePosition(int pos, int j = -1, int k = -1) {
		return;
	}

};
//end class PetscSolver0DHandler

} /* end namespace xolotlSolver */
#endif
