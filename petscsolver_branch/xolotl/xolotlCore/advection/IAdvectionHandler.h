#ifndef IADVECTIONHANDLER_H
#define IADVECTIONHANDLER_H

// Includes
#include <PSICluster.h>
#include <PSIClusterReactionNetwork.h>
#include <memory>

namespace xolotlCore {

/**
 * Realizations of this interface are responsible for all the physical parts
 * for the advection of mobile helium cluster. The solver call these methods to handle
 * the advection.
 */
class IAdvectionHandler {

public:

	/**
	 * The destructor
	 */
	virtual ~IAdvectionHandler() {}

	/**
	 * This function initialize the list of clusters that will move through advection
	 * and their corresponding sink strength (or driving forces).
	 *
	 * @param network The network
	 * @param ofill The pointer to the array that will contain the value 1 at the indices
	 * of the advecting clusters
	 */
	virtual void initialize(PSIClusterReactionNetwork *network, int *ofill) = 0;

	/**
	 * Set the location of the sink.
	 *
	 * @param pos The location of the sink
	 */
	virtual void setLocation(double pos) = 0;

	/**
	 * Compute the flux due to the advection for all the helium clusters,
	 * given the space parameters and the position.
	 * This method is called by the RHSFunction from the PetscSolver.
	 *
	 * @param network The network
	 * @param pos The position on the grid
	 * @param concVector The pointer to the pointer of arrays of concentration at middle,
	 * left, and right grid points
	 * @param updatedConcOffset The pointer to the array of the concentration at the grid
	 * point where the advection is computed used to find the next solution
	 * @param hxLeft The step size on the left side of the point in the x direction
	 * @param hxRight The step size on the right side of the point in the x direction
	 * @param hy The step size in the y direction
	 * @param hz The step size in the z direction
	 */
	virtual void computeAdvection(PSIClusterReactionNetwork *network,
			std::vector<double> &pos, double **concVector, double *updatedConcOffset,
			double hxLeft, double hxRight, double hy = 0.0, double hz = 0.0) = 0;

	/**
	 * Compute the partial derivatives due to the advection of all the helium clusters given
	 * the space parameters and the position.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 *
	 * @param network The network
	 * @param h The space parameters in the three directions
	 * @param val The pointer to the array that will contain the values of partials
	 * for the advection
	 * @param indices The pointer to the array that will contain the indices of the
	 * advecting cluster in the network
	 * @param pos The position on the grid
	 * @param hxLeft The step size on the left side of the point in the x direction
	 * @param hxRight The step size on the right side of the point in the x direction
	 * @param hy The step size in the y direction
	 * @param hz The step size in the z direction
	 */
	virtual void computePartialsForAdvection(PSIClusterReactionNetwork *network,
			double *val, int *indices, std::vector<double> &pos,
			double hxLeft, double hxRight, double hy = 0.0, double hz = 0.0) = 0;

	/**
	 * Compute the indices that will determine where the partial derivatives will
	 * be put in the Jacobian.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 *
	 * @param pos The position on the grid
	 * @return The indices for the position in the Jacobian
	 */
	virtual std::vector<int> getStencilForAdvection(std::vector<double> &pos) = 0;

	/**
	 * Check whether the grid point is located on the sink surface or not.
	 *
	 * @param pos The position on the grid
	 * @return True if the point is on the sink
	 */
	virtual bool isPointOnSink(std::vector<double> &pos) = 0;

	/**
	 * Get the total number of advecting clusters in the network.
	 *
	 * @return The number of advecting clusters
	 */
	virtual int getNumberOfAdvecting() = 0;

};
//end class IAdvectionHandler

} /* namespace xolotlCore */
#endif