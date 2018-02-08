#ifndef IFLUXHANDLER_H
#define IFLUXHANDLER_H

#include <vector>
#include <string>
#include <IReactionNetwork.h>

namespace xolotlCore {

/**
 * Realizations of this interface are responsible for handling the incident (incoming)
 * flux calculations.
 */
class IFluxHandler {

public:

<<<<<<< HEAD
	virtual ~IFluxHandler() { }
=======
	virtual ~IFluxHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute and store the incident flux values at each grid point.
	 *
	 * @param network The reaction network
	 * @param surfacePos The current position of the surface
	 * @param grid The grid on the x axis
	 */
<<<<<<< HEAD
	virtual void initializeFluxHandler(IReactionNetwork *network,
		int surfacePos, std::vector<double> grid) = 0;
		
=======
	virtual void initializeFluxHandler(const IReactionNetwork& network,
			int surfacePos, std::vector<double> grid) = 0;

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	/**
	 * This method reads the values on the time profile file and store them in the
	 * time and amplitude vectors.
	 *
	 * @param fileName The name of the file where the values are stored
	 */
	virtual void initializeTimeProfile(const std::string& fileName) = 0;

	/**
	 * This operation computes the flux due to incoming particles at a given grid point.
	 *
	 * @param currentTime The time
	 * @param updatedConcOffset The pointer to the array of the concentration at the grid
	 * point where the diffusion is computed used to find the next solution
	 * @param ix The position on the x grid
	 * @param surfacePos The current position of the surface
	 */
<<<<<<< HEAD
	virtual void computeIncidentFlux(double currentTime, double *updatedConcOffset, int xi, int surfacePos) = 0;
=======
	virtual void computeIncidentFlux(double currentTime,
			double *updatedConcOffset, int xi, int surfacePos) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation increments the fluence at the current time step.
	 *
	 * @param dt The length of the time step
	 */
	virtual void incrementFluence(double dt) = 0;

	/**
	 * This operation returns the fluence.
	 *
	 * @return The fluence
	 */
	virtual double getFluence() const = 0;

	/**
	 * This operation sets the factor to change the intensity of the flux.
	 *
	 * @param flux The flux intensity
	 */
	virtual void setFluxAmplitude(double flux) = 0;

	/**
	 * This operation gets the factor that changes the flux
	 * intensity/amplitude.
	 *
	 * @return The flux amplitude
	 */
	virtual double getFluxAmplitude() const = 0;

<<<<<<< HEAD
}; //end class IFluxHandler
=======
};
//end class IFluxHandler
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

}

#endif
