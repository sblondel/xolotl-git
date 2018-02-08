#ifndef ISOLVERHANDLER_H
#define ISOLVERHANDLER_H

// Includes
#include <petscsys.h>
#include <petscts.h>
#include <petscdmda.h>
#include <memory>
#include <ITemperatureHandler.h>
#include <IDiffusionHandler.h>
#include <IAdvectionHandler.h>
<<<<<<< HEAD
#include <IMaterialFactory.h>
=======
#include <ITrapMutationHandler.h>
#include <IMaterialFactory.h>
#include <IReactionNetwork.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

namespace xolotlSolver {

/**
 * Realizations of this interface are responsible for the actual implementation of
 * each piece of the solver. It is created to handle the multiple dimensions more easily.
 *
 * TODO - It will be better to have a PETSc-free solver handler interface (like ISolver)
 */
class ISolverHandler {

public:

	/**
	 * The destructor.
	 */
	virtual ~ISolverHandler(){}

	/**
	 * Initialize all the physics handlers that are needed to solve the ADR equations.
	 *
	 * @param material The material factory
	 * @param tempHandler The temperature handler
<<<<<<< HEAD
=======
	 * @param networkHandler The network handler
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 * @param options The Xolotl options
	 */
	virtual void initializeHandlers(std::shared_ptr<xolotlFactory::IMaterialFactory> material,
			std::shared_ptr<xolotlCore::ITemperatureHandler> tempHandler,
<<<<<<< HEAD
			xolotlCore::Options &options) = 0;

	/**
	 * Initialize the network and network file name.
	 *
	 * @param fileName The name of the file from which the network was loaded
	 * @param net The network
	 */
	virtual void initializeNetwork(const std::string& fileName,
			xolotlCore::PSIClusterReactionNetwork *net) = 0;

	/**
	 * Create everything needed before starting to solve.
	 *
	 * @param da The PETSc distributed array
	 * @param nx The number of grid points in the x direction (depth)
	 * @param hx The step size in the x direction
	 * @param ny The number of grid points in the y direction
	 * @param hy The step size in the y direction
	 * @param nz The number of grid points in the z direction
	 * @param hz The step size in the z direction
	 */
	virtual void createSolverContext(DM &da, int nx, double hx, int ny,
			double hy, int nz, double hz) = 0;

	/**
	 * Get the diagonal fill for the Jacobian, corresponding to the reactions.
	 *
	 * @param diagFill The pointer to the vector where the connectivity information is kept
	 * @param diagFillSize The size of this vector
	 */
	virtual void getDiagonalFill(PetscInt *diagFill, int diagFillSize) = 0;
=======
			std::shared_ptr<xolotlCore::IReactionNetwork> networkHandler,
			xolotlCore::Options &options) = 0;

	/**
	 * Create everything needed before starting to solve.
	 *
	 * @param da The PETSc distributed array
	 */
	virtual void createSolverContext(DM &da) = 0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Initialize the concentration solution vector.
	 *
	 * @param da The PETSc distributed array
	 * @param C The PETSc solution vector
	 */
<<<<<<< HEAD
	virtual void initializeConcentration(DM &da, Vec &C) const = 0;
=======
	virtual void initializeConcentration(DM &da, Vec &C) = 0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Compute the new concentrations for the RHS function given an initial
	 * vector of concentrations.
	 *
	 * @param ts The PETSc time stepper
	 * @param localC The PETSc local solution vector
	 * @param F The updated PETSc solution vector
	 * @param ftime The real time
	 */
	virtual void updateConcentration(TS &ts, Vec &localC, Vec &F, PetscReal ftime) = 0;

	/**
	 * Compute the off-diagonal part of the Jacobian which is related to cluster's motion.
	 *
	 * @param ts The PETSc time stepper
	 * @param localC The PETSc local solution vector
	 * @param J The Jacobian
<<<<<<< HEAD
	 */
	virtual void computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J) const = 0;
=======
	 * @param ftime The real time
	 */
	virtual void computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J, PetscReal ftime) = 0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Compute the diagonal part of the Jacobian which is related to cluster reactions.
	 *
	 * @param ts The PETSc time stepper
	 * @param localC The PETSc local solution vector
	 * @param J The Jacobian
<<<<<<< HEAD
	 */
	virtual void computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J) = 0;

	/**
	 * Get the step size in the x direction.
	 *
	 * @return The step size in the x direction
	 */
	virtual double getStepSizeX() const = 0;
=======
	 * @param ftime The real time
	 */
	virtual void computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J, PetscReal ftime) = 0;

	/**
	 * Get the grid in the x direction.
	 *
	 * @return The grid in the x direction
	 */
	virtual std::vector<double> getXGrid() const = 0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Get the step size in the y direction.
	 *
	 * @return The step size in the y direction
	 */
	virtual double getStepSizeY() const = 0;

	/**
	 * Get the step size in the z direction.
	 *
	 * @return The step size in the z direction
	 */
	virtual double getStepSizeZ() const = 0;

	/**
	 * Get the number of dimensions of the problem.
	 *
	 * @return The number of dimensions
	 */
	virtual int getDimension() const = 0;

	/**
<<<<<<< HEAD
=======
	 * Get the position of the surface.
	 *
	 * @param j The index on the grid in the y direction
	 * @param k The index on the grid in the z direction
	 * @return The position of the surface at this y,z coordinates
	 */
	virtual int getSurfacePosition(int j = -1, int k = -1) const = 0;

	/**
	 * Set the position of the surface.
	 *
	 * @param pos The index of the position
	 * @param j The index on the grid in the y direction
	 * @param k The index on the grid in the z direction
	 */
	virtual void setSurfacePosition(int pos, int j = -1, int k = -1) = 0;

	/**
	 * Get the initial vacancy concentration.
	 *
	 * @return The initial vacancy concentration
	 */
	virtual double getInitialVConc() const = 0;

	/**
	 * Get the sputtering yield.
	 *
	 * @return The sputtering yield
	 */
	virtual double getSputteringYield() const = 0;

	/**
	 * To know if the surface should be able to move.
	 *
	 * @return True if the surface should be able to move.
	 */
	virtual bool moveSurface() const = 0;

	/**
	 * To know if the bubble bursting should be used.
	 *
	 * @return True if we want the bubble bursting.
	 */
	virtual bool burstBubbles() const = 0;

	/**
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 * Get the flux handler.
	 *
	 * @return The flux handler
	 */
	virtual xolotlCore::IFluxHandler *getFluxHandler() const = 0;

	/**
<<<<<<< HEAD
=======
	 * Get the advection handler.
	 *
	 * @return The first advection handler
	 */
	virtual xolotlCore::IAdvectionHandler *getAdvectionHandler() const = 0;

	/**
	 * Get the advection handlers.
	 *
	 * @return The first advection handlers
	 */
	virtual std::vector<xolotlCore::IAdvectionHandler *> getAdvectionHandlers() const = 0;

	/**
	 * Get the modified trap-mutation handler.
	 *
	 * @return The modified trap-mutation handler
	 */
	virtual xolotlCore::ITrapMutationHandler *getMutationHandler() const = 0;

	/**
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 * Get the network.
	 *
	 * @return The network
	 */
<<<<<<< HEAD
	virtual xolotlCore::PSIClusterReactionNetwork *getNetwork() const = 0;
=======
	virtual xolotlCore::IReactionNetwork *getNetwork() const = 0;

	/**
	 * Get the network name.
	 *
	 * @return The network name
	 */
	virtual std::string getNetworkName() const = 0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

}; //end class ISolverHandler

} /* namespace xolotlSolver */
#endif
