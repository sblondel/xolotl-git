#ifndef PETSCSOLVER1DHANDLER_H
#define PETSCSOLVER1DHANDLER_H

// Includes
#include "PetscSolverHandler.h"

namespace xolotlSolver {

/**
 * This class is a subclass of PetscSolverHandler and implement all the methods needed
 * to solve the ADR equations in 1D using PETSc from Argonne National Laboratory.
 */
class PetscSolver1DHandler: public PetscSolverHandler {
<<<<<<< HEAD
public:

	//! The Constructor
	PetscSolver1DHandler() {}

	//! The Destructor
	~PetscSolver1DHandler() {}

	/**
	 * Create everything needed before starting to solve.
     * \see ISolverHandler.h
	 */
	void createSolverContext(DM &da, int nx, double hx, int ny,
			double hy, int nz, double hz);

	/**
	 * Initialize the concentration solution vector.
     * \see ISolverHandler.h
	 */
	void initializeConcentration(DM &da, Vec &C) const;
=======
private:
	//! The position of the surface
	int surfacePosition;

public:

	//! The Constructor
	PetscSolver1DHandler() {
	}

	//! The Destructor
	~PetscSolver1DHandler() {
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Compute the new concentrations for the RHS function given an initial
	 * vector of concentrations. Apply the diffusion, advection and all the reactions.
<<<<<<< HEAD
     * \see ISolverHandler.h
=======
	 * \see ISolverHandler.h
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 */
	void updateConcentration(TS &ts, Vec &localC, Vec &F, PetscReal ftime);

	/**
	 * Compute the off-diagonal part of the Jacobian which is related to cluster's motion.
<<<<<<< HEAD
     * \see ISolverHandler.h
	 */
	void computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J) const;

	/**
	 * Compute the diagonal part of the Jacobian which is related to cluster reactions.
     * \see ISolverHandler.h
	 */
	void computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J);

}; //end class PetscSolver1DHandler
=======
	 * \see ISolverHandler.h
	 */
	void computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J, PetscReal ftime);

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
		return surfacePosition;
	}

	/**
	 * Set the position of the surface.
	 * \see ISolverHandler.h
	 */
	void setSurfacePosition(int pos, int j = -1, int k = -1) {
		surfacePosition = pos;
	}

};
//end class PetscSolver1DHandler
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

} /* end namespace xolotlSolver */
#endif
