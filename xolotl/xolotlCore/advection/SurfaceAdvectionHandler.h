#ifndef SURFACEADVECTIONHANDLER_H
#define SURFACEADVECTIONHANDLER_H

// Includes
#include "AdvectionHandler.h"
#include <MathUtils.h>

namespace xolotlCore {

/**
 * This class realizes the IAdvectionHandler interface responsible for all
 * the physical parts for the advection of mobile helium cluster, in the case
 * where cluster are drifting toward the surface.
 */
class SurfaceAdvectionHandler: public AdvectionHandler {
private:

	//! The vector to know which clusters are moving where
<<<<<<< HEAD
	std::vector < std::vector < std::vector < std::vector <bool> > > > advectionGrid;
=======
	std::vector<std::vector<std::vector<std::vector<bool> > > > advectionGrid;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

public:

	//! The Constructor
<<<<<<< HEAD
	SurfaceAdvectionHandler() {}

	//! The Destructor
	~SurfaceAdvectionHandler() {}
=======
	SurfaceAdvectionHandler() : AdvectionHandler() {
	}

	//! The Destructor
	~SurfaceAdvectionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Initialize an array of the dimension of the physical domain times the number of advecting
	 * clusters. For each location, True means the cluster is moving, False means it is not.
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	void initializeAdvectionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid,
			int ny = 1, double hy = 0.0, int nz = 1, double hz = 0.0);
=======
	void initializeAdvectionGrid(
			std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid, int ny = 1, double hy = 0.0, int nz = 1,
			double hz = 0.0) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the flux due to the advection for all the helium clusters,
	 * given the space parameter hx and the position.
	 * This method is called by the RHSFunction from the PetscSolver.
	 *
	 * If D is the diffusion coefficient, and C_r, C_m the right and middle concentration
	 * of this cluster, A the sink strength, K the Boltzmann constant, T the temperature,
	 * the value to add to the updated concentration is:
	 *
	 * [(3 * A * D) / (K * T * hx)] * [(C_r / [pos_x + hx]^4) - (C_m / (pos_x)^4)]
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	void computeAdvection(IReactionNetwork *network,
			std::vector<double> &pos, double **concVector, double *updatedConcOffset,
			double hxLeft, double hxRight, int ix,
			double hy = 0.0, int iy = 0, double hz = 0.0, int iz = 0);
=======
	void computeAdvection(const IReactionNetwork& network, const Point3D& pos,
			double **concVector, double *updatedConcOffset, double hxLeft,
			double hxRight, int ix, double hy = 0.0, int iy = 0,
			double hz = 0.0, int iz = 0) const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the partials due to the advection of all the helium clusters given
	 * the space parameter hx and the position.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 *
	 * The partial derivative on the right grid point is given by (same notation as for
	 * the computeAdvection method)
	 *
	 * (3 * A * D) / [K * T * hx * (pos_x + hx)^4]
	 *
	 * and on this grid point we have
	 *
	 * - (3 * A * D) / [K * T * hx * (pos_x)^4]
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	void computePartialsForAdvection(IReactionNetwork *network,
			double *val, int *indices, std::vector<double> &pos,
			double hxLeft, double hxRight, int ix,
			double hy = 0.0, int iy = 0, double hz = 0.0, int iz = 0);
=======
	void computePartialsForAdvection(const IReactionNetwork& network,
			double *val, int *indices, const Point3D& pos, double hxLeft,
			double hxRight, int ix, double hy = 0.0, int iy = 0,
			double hz = 0.0, int iz = 0) const override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the indices that will determine where the partial derivatives will
	 * be put in the Jacobian.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 *
	 * For the surface advection the stencil is always the same:
	 *
	 * stencil[0] = 1 //x
	 * stencil[1] = 0 //y
	 * stencil[2] = 0 //z
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	std::vector<int> getStencilForAdvection(std::vector<double> &pos);
=======
	std::array<int, 3> getStencilForAdvection(const Point3D& pos) const
			override {
		// Always return (1, 0, 0)
		return {1, 0, 0};
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Check whether the grid point is located on the sink surface or not.
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	bool isPointOnSink(std::vector<double> &pos);
=======
	bool isPointOnSink(const Point3D& pos) const override {
		// Always return false
		return false;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};
//end class SurfaceAdvectionHandler

} /* end namespace xolotlCore */
#endif
