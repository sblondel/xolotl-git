#ifndef IADVECTIONHANDLER_H
#define IADVECTIONHANDLER_H

// Includes
<<<<<<< HEAD
#include <PSICluster.h>
#include <IReactionNetwork.h>
#include <memory>
=======
#include <array>
#include <memory>
#include "Point3D.h"
#include <PSICluster.h>
#include <IReactionNetwork.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
<<<<<<< HEAD
	virtual ~IAdvectionHandler() {}
=======
	virtual ~IAdvectionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This function initialize the list of clusters that will move through advection
	 * and their corresponding sink strength (or driving forces).
	 *
	 * @param network The network
	 * @param ofill The pointer to the array that will contain the value 1 at the indices
	 * of the advecting clusters
	 */
<<<<<<< HEAD
	virtual void initialize(IReactionNetwork *network, int *ofill) = 0;
=======
	virtual void initialize(const IReactionNetwork& network, int *ofill) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Set the number of dimension
	 *
	 * @param dim The number of dimensions of the problem
	 */
	virtual void setDimension(int dim) = 0;

	/**
	 * Set the location of the sink.
	 *
	 * @param pos The location of the sink
	 */
	virtual void setLocation(double pos) = 0;

	/**
	 * Initialize an array of the dimension of the physical domain times the number of advecting
	 * clusters. For each location, True means the cluster is moving, False means it is not.
	 *
	 * @param advectionHandlers The vector of advection handlers
	 * @param grid The spatial grid in the depth direction
	 * @param ny The number of grid points in the Y direction
	 * @param hy The step size in the Y direction
	 * @param nz The number of grid points in the Z direction
	 * @param hz The step size in the Z direction
	 */
<<<<<<< HEAD
	virtual void initializeAdvectionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid,
			int ny = 1, double hy = 0.0, int nz = 1, double hz = 0.0) = 0;
=======
	virtual void initializeAdvectionGrid(
			std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid, int ny = 1, double hy = 0.0, int nz = 1,
			double hz = 0.0) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
	 * @param ix The position on the x grid
	 * @param hy The step size in the y direction
	 * @param iy The position on the y grid
	 * @param hz The step size in the z direction
	 * @param iz The position on the z grid
	 */
<<<<<<< HEAD
	virtual void computeAdvection(IReactionNetwork *network,
			std::vector<double> &pos, double **concVector, double *updatedConcOffset,
			double hxLeft, double hxRight, int ix,
			double hy = 0.0, int iy = 0, double hz = 0.0, int iz = 0) = 0;
=======
	virtual void computeAdvection(const IReactionNetwork& network,
			const Point3D& pos, double **concVector, double *updatedConcOffset,
			double hxLeft, double hxRight, int ix, double hy = 0.0, int iy = 0,
			double hz = 0.0, int iz = 0) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
	 * @param ix The position on the x grid
	 * @param hy The step size in the y direction
	 * @param iy The position on the y grid
	 * @param hz The step size in the z direction
	 * @param iz The position on the z grid
	 */
<<<<<<< HEAD
	virtual void computePartialsForAdvection(IReactionNetwork *network,
			double *val, int *indices, std::vector<double> &pos,
			double hxLeft, double hxRight, int ix,
			double hy = 0.0, int iy = 0, double hz = 0.0, int iz = 0) = 0;
=======
	virtual void computePartialsForAdvection(const IReactionNetwork& network,
			double *val, int *indices, const Point3D& pos, double hxLeft,
			double hxRight, int ix, double hy = 0.0, int iy = 0,
			double hz = 0.0, int iz = 0) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the indices that will determine where the partial derivatives will
	 * be put in the Jacobian.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 *
	 * @param pos The position on the grid
	 * @return The indices for the position in the Jacobian
	 */
<<<<<<< HEAD
	virtual std::vector<int> getStencilForAdvection(std::vector<double> &pos) = 0;
=======
	virtual std::array<int, 3> getStencilForAdvection(
			const Point3D& pos) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Check whether the grid point is located on the sink surface or not.
	 *
	 * @param pos The position on the grid
	 * @return True if the point is on the sink
	 */
<<<<<<< HEAD
	virtual bool isPointOnSink(std::vector<double> &pos) = 0;
=======
	virtual bool isPointOnSink(const Point3D& pos) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the total number of advecting clusters in the network.
	 *
	 * @return The number of advecting clusters
	 */
<<<<<<< HEAD
	virtual int getNumberOfAdvecting() = 0;
=======
	virtual int getNumberOfAdvecting() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the vector of index of advecting clusters in the network.
	 *
	 * @return The vector of advecting clusters
	 */
<<<<<<< HEAD
	virtual std::vector<int> getIndexVector() = 0;
=======
	virtual const IReactant::ConstRefVector& getAdvectingClusters() = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Get the location of the sink.
	 *
	 * @return The location
	 */
<<<<<<< HEAD
	virtual double getLocation() = 0;
=======
	virtual double getLocation() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};
//end class IAdvectionHandler

} /* namespace xolotlCore */
#endif
