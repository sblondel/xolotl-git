#ifndef PETSCSOLVER2DHANDLER_H
#define PETSCSOLVER2DHANDLER_H

// Includes
#include "PetscSolverHandler.h"

namespace xolotlSolver {

/**
 * This class is a subclass of PetscSolverHandler and implement all the methods needed
 * to solve the ADR equations in 2D using PETSc from Argonne National Laboratory.
 */
class PetscSolver2DHandler: public PetscSolverHandler {
private:
	//! The position of the surface
	std::vector<int> surfacePosition;

public:

<<<<<<< HEAD
	//! The Constructor
	PetscSolver2DHandler() {
=======
	/**
	 * Construct a PetscSolver2DHandler.
	 */
	PetscSolver2DHandler() = delete;

	/**
	 * Construct a PetscSolver2DHandler.
	 *
	 * @param _network The reaction network to use.
	 */
	PetscSolver2DHandler(xolotlCore::IReactionNetwork& _network) :
			PetscSolverHandler(_network) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	//! The Destructor
	~PetscSolver2DHandler() {
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
		return surfacePosition[j];
	}

	/**
	 * Set the position of the surface.
	 * \see ISolverHandler.h
	 */
	void setSurfacePosition(int pos, int j = -1, int k = -1) {
		surfacePosition[j] = pos;
	}

};
//end class PetscSolver2DHandler

} /* end namespace xolotlSolver */
#endif
