#ifndef IDIFFUSIONHANDLER_H
#define IDIFFUSIONHANDLER_H

// Includes
#include <PSICluster.h>
#include <IReactionNetwork.h>
#include <IAdvectionHandler.h>
#include <memory>

namespace xolotlCore {

/**
 * Realizations of this interface are responsible for all the physical parts
 * for the diffusion of mobile cluster. The solver call these methods to handle
 * the diffusion.
 */
class IDiffusionHandler {

public:

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~IDiffusionHandler() {}
=======
	virtual ~IDiffusionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Initialize the off-diagonal part of the Jacobian. If this step is skipped it
	 * won't be possible to set the partial derivatives for the diffusion.
	 *
	 * @param network The network
	 * @param ofill The pointer to the array that will contain the value 1 at the indices
	 * of the diffusing clusters
	 */
<<<<<<< HEAD
	virtual void initializeOFill(IReactionNetwork *network,
=======
	virtual void initializeOFill(const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			int *ofill) = 0;

	/**
	 * Initialize an array of the dimension of the physical domain times the number of diffusion
	 * clusters
	 *
	 * @param advectionHandlers The vector of advection handlers
	 * @param grid The spatial grid in the depth direction
	 * @param ny The number of grid points in the Y direction
	 * @param hy The step size in the Y direction
	 * @param nz The number of grid points in the Z direction
	 * @param hz The step size in the Z direction
	 */
<<<<<<< HEAD
	virtual void initializeDiffusionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid,
			int ny = 0, double hy = 0.0, int nz = 0, double hz = 0.0) = 0;
=======
	virtual void initializeDiffusionGrid(
			std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid, int ny = 0, double hy = 0.0, int nz = 0,
			double hz = 0.0) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the flux due to the diffusion for all the cluster that are diffusing,
	 * given the space parameters.
	 * This method is called by the RHSFunction from the PetscSolver.
	 *
	 * @param network The network
	 * @param concVector The pointer to the pointer of arrays of concentration at middle/
	 * left/right/bottom/top/front/back grid points
	 * @param updatedConcOffset The pointer to the array of the concentration at the grid
	 * point where the diffusion is computed used to find the next solution
	 * @param hxLeft The step size on the left side of the point in the x direction
	 * @param hxRight The step size on the right side of the point in the x direction
	 * @param ix The position on the x grid
	 * @param sy The space parameter, depending on the grid step size in the y direction
	 * @param iy The position on the y grid
	 * @param sz The space parameter, depending on the grid step size in the z direction
	 * @param iz The position on the z grid
	 */
<<<<<<< HEAD
	virtual void computeDiffusion(IReactionNetwork *network,
			double **concVector, double *updatedConcOffset,
			double hxLeft, double hxRight, int ix,
			double sy = 0.0, int iy = 0, double sz = 0.0, int iz = 0) = 0;
=======
	virtual void computeDiffusion(const IReactionNetwork& network,
			double **concVector, double *updatedConcOffset, double hxLeft,
			double hxRight, int ix, double sy = 0.0, int iy = 0,
			double sz = 0.0, int iz = 0) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the partials due to the diffusion of all the diffusing clusters given
	 * the space parameters.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 *
	 * @param network The network
	 * @param val The pointer to the array that will contain the values of partials
	 * for the diffusion
	 * @param indices The pointer to the array that will contain the indices of the
	 * diffusing clusters in the network
	 * @param hxLeft The step size on the left side of the point in the x direction
	 * @param hxRight The step size on the right side of the point in the x direction
	 * @param ix The position on the x grid
	 * @param sy The space parameter, depending on the grid step size in the y direction
	 * @param iy The position on the y grid
	 * @param sz The space parameter, depending on the grid step size in the z direction
	 * @param iz The position on the z grid
	 */
<<<<<<< HEAD
	virtual void computePartialsForDiffusion(IReactionNetwork *network,
			double *val, int *indices, double hxLeft, double hxRight, int ix,
			double sy = 0.0, int iy = 0, double sz = 0.0, int iz = 0) = 0;
=======
	virtual void computePartialsForDiffusion(const IReactionNetwork& network,
			double *val, int *indices, double hxLeft, double hxRight, int ix,
			double sy = 0.0, int iy = 0, double sz = 0.0, int iz = 0) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total number of diffusing clusters in the network.
	 *
	 * @return The number of diffusing clusters
	 */
<<<<<<< HEAD
	virtual int getNumberOfDiffusing() = 0;
=======
	virtual int getNumberOfDiffusing() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};
//end class IDiffusionHandler

} /* namespace xolotlCore */
#endif
