#ifndef YGBADVECTIONHANDLER_H
#define YGBADVECTIONHANDLER_H

// Includes
#include "AdvectionHandler.h"
#include <MathUtils.h>

namespace xolotlCore {

/**
 * This class realizes the IAdvectionHandler interface responsible for all
 * the physical parts for the advection of mobile helium cluster.
 * It represents the advection (drift) toward grain boundaries (GB) in the
 * Y direction, perpendicular to the surface. It has been observed that clusters
 * don't diffuse anymore once on the GB, the diffusion is thus cancelled out
 * here on the GB.
 */
class YGBAdvectionHandler: public AdvectionHandler {
public:

	//! The Constructor
<<<<<<< HEAD
	YGBAdvectionHandler() {}

	//! The Destructor
	~YGBAdvectionHandler() {}
=======
	YGBAdvectionHandler() :
			AdvectionHandler() {
	}

	//! The Destructor
	~YGBAdvectionHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This function initialize the list of clusters that will move through advection for
	 * grain boundaries.
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	void initialize(IReactionNetwork *network, int *ofill);
=======
	void initialize(const IReactionNetwork& network, int *ofill) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Initialize an array of the dimension of the physical domain times the number of advecting
	 * clusters. For each location, True means the cluster is moving, False means it is not.
	 * Don't do anything here.
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	void initializeAdvectionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid,
			int ny = 1, double hy = 0.0, int nz = 1, double hz = 0.0) {return;}
=======
	void initializeAdvectionGrid(
			std::vector<IAdvectionHandler *> advectionHandlers,
			std::vector<double> grid, int ny = 1, double hy = 0.0, int nz = 1,
			double hz = 0.0) override {
		return;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute the flux due to the advection for all the helium clusters,
	 * given the space parameters and the position.
	 * This method is called by the RHSFunction from the PetscSolver.
	 * This method also removes the flux from diffusion of the advecting clusters
	 * on the GB.
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
	 * the space parameters and the position.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 * This method also removes the partials from diffusion of the advecting clusters
	 * on the GB.
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
	 * Here we consider GB in the Y direction.
	 *
	 * \see IAdvectionHandler.h
	 */
<<<<<<< HEAD
	std::vector<int> getStencilForAdvection(std::vector<double> &pos);
=======
	std::array<int, 3> getStencilForAdvection(const Point3D& pos) const
			override;
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
		// Return true if pos[1] is equal to location
		return fabs(location - pos[1]) < 0.001;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};
//end class YGBAdvectionHandler

} /* end namespace xolotlCore */
#endif
