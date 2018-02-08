#ifndef TEMPERATUREHANDLER_H
#define TEMPERATUREHANDLER_H

#include "ITemperatureHandler.h"

namespace xolotlCore {

/**
 * This class realizes the ITemperatureHandler, it is responsible for the
 * handling of a temperature constant with time.
 */
class TemperatureHandler: public ITemperatureHandler {

private:

	/**
	 * The temperature in Kelvin
	 */
	double temperature;

	/**
	 * The number of degrees of freedom in the network
	 */
	int dof;

	/**
	 * The default constructor is private because the TemperatureHandler
	 * must be initialized with a temperature
	 */
	TemperatureHandler() :
			temperature(0.0), dof(0) {
	}

public:

	/**
	 * The constructor
	 *
	 * @param constTemperature the temperature
	 */
	TemperatureHandler(double constTemperature) :
			temperature(constTemperature), dof(0) {
	}

	/**
	 * The destructor.
	 */
	virtual ~TemperatureHandler() {
	}

	/**
	 * This operation initializes the ofill and dfill arrays so that the
	 * temperature is connected correctly in the solver.
	 *
	 * \see ITemperatureHandler.h
	 */
<<<<<<< HEAD
	virtual void initializeTemperature(IReactionNetwork *network, int *ofill,
			int *dfill) {
		// Set dof
		dof = network->getDOF();
=======
	virtual void initializeTemperature(const IReactionNetwork& network,
			int *ofill, int *dfill) {
		// Set dof
		dof = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Add the temperature to ofill
		ofill[(dof - 1) * dof + (dof - 1)] = 1;

		// Add the temperature to dfill
		dfill[(dof - 1) * dof + (dof - 1)] = 1;

		return;
	}

	/**
	 * This operation returns the temperature at the given position
	 * and time.
	 * Here it is a constant temperature.
	 *
	 * \see ITemperatureHandler.h
	 */
<<<<<<< HEAD
	virtual double getTemperature(const std::vector<double>& position,
			double) const {
=======
	virtual double getTemperature(const Point3D& position, double) const {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return temperature;
	}

	/**
	 * This operation sets the temperature given by the solver.
	 * Don't do anything.
	 *
	 * \see ITemperatureHandler.h
	 */
	virtual void setTemperature(double * solution) {
		return;
	}

	/**
	 * This operation sets the heat coefficient to use in the equation.
	 *
	 * \see ITemperatureHandler.h
	 */
	virtual void setHeatCoefficient(double coef) {
		return;
	}

	/**
	 * This operation sets the surface position.
	 * Don't do anything.
	 *
	 * \see ITemperatureHandler.h
	 */
	virtual void updateSurfacePosition(double surfacePos) {
		return;
	}

	/**
	 * Compute the flux due to the heat equation.
	 * This method is called by the RHSFunction from the PetscSolver.
	 * Don't do anything.
	 *
	 * \see ITemperatureHandler.h
	 */
	virtual void computeTemperature(double **concVector,
			double *updatedConcOffset, double hxLeft, double hxRight) {
		return;
	}

	/**
	 * Compute the partials due to the heat equation.
	 * This method is called by the RHSJacobian from the PetscSolver.
	 * Don't do anything.
	 *
	 * \see ITemperatureHandler.h
	 */
	virtual void computePartialsForTemperature(double *val, int *indices,
			double hxLeft, double hxRight) {
		// Set the cluster index, the PetscSolver will use it to compute
		// the row and column indices for the Jacobian
		indices[0] = dof - 1;

		// Compute the partial derivatives for diffusion of this cluster
		// for the middle, left, and right grid point
		val[0] = 0.0; // middle
		val[1] = 0.0; // left
		val[2] = 0.0; // right

		return;
	}

};
//end class TemperatureHandler

}

#endif
