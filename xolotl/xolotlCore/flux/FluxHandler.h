#ifndef FLUXHANDLER_H
#define FLUXHANDLER_H

#include "IFluxHandler.h"
#include <vector>
#include <memory>
<<<<<<< HEAD
=======
#include <Constants.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

namespace xolotlCore {

/**
 * Realizations of this interface are responsible for handling the incident (incoming)
 * flux calculations.
 */
class FluxHandler: public IFluxHandler {

protected:

	/**
	 * Vector to hold the incident flux values at each grid
	 * point (x position).
	 */
	std::vector<double> incidentFluxVec;

	/**
<<<<<<< HEAD
	 * Step size between each grid point in the x direction.
	 */
	double stepSize;
=======
	 * Vector to hold the position at each grid
	 * point (x position).
	 */
	std::vector<double> xGrid;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 *  Fluence.
	 */
	double fluence;

	/**
	 * The amplitude of the flux.
	 */
	double fluxAmplitude;

	/**
	 * The index of the cluster.
	 */
	int fluxIndex;

	/**
	 * Are we using a time profile for the amplitude of the helium incoming flux?
	 */
	bool useTimeProfile;

	/**
	 * Value of the fit function integrated on the grid.
	 */
	double normFactor;

	/**
	 * Vector to hold the time read from the input
	 * time profile file.
	 */
	std::vector<double> time;

	/**
	 * Vector to hold the amplitude read from the input
	 * time profile file.
	 */
	std::vector<double> amplitudes;

	/**
	 * Function that calculates the flux at a given position x (in nm).
	 * It needs to be implemented by the daughter classes.
	 *
	 * @param x The position where to evaluate the fit
	 * @return The evaluated value
	 */
<<<<<<< HEAD
	virtual double FitFunction(double x) {return 0.0;}
=======
	virtual double FitFunction(double) {
		return 0.0;
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * This method returns the value of the helium incident flux amplitude at the
	 * given time when a time profile is used.
	 *
	 * @param currentTime The time
	 * @return The value of the helium flux at this time
	 */
	double getProfileAmplitude(double currentTime) const;

	/**
	 * This method recomputes the values of the incident flux vector when
	 * a time profile is given.
<<<<<<< HEAD
	 */
	void recomputeFluxHandler();
=======
	 *
	 * @param surfacePos The current position of the surface
	 */
	void recomputeFluxHandler(int surfacePos);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	FluxHandler();

	~FluxHandler() {
	}

	/**
	 * Compute and store the incident flux values at each grid point.
<<<<<<< HEAD
     * \see IFluxHandler.h
	 */
	virtual void initializeFluxHandler(PSIClusterReactionNetwork *network,
			int nx, double hx);
=======
	 * \see IFluxHandler.h
	 */
	virtual void initializeFluxHandler(IReactionNetwork *network,
			int surfacePos, std::vector<double> grid);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * This method reads the values on the time profile file and store them in the
	 * time and amplitude vectors.
<<<<<<< HEAD
     * \see IFluxHandler.h
	 */
	void initializeTimeProfile(const std::string& fileName);

	/**
	 * This operation returns the incident flux vector.
     * \see IFluxHandler.h
	 */
	virtual std::vector<double> getIncidentFluxVec(double currentTime);

	/**
	 * This operation returns the index of the cluster that is irradiating
	 * the material.
     * \see IFluxHandler.h
	 */
	virtual int getIncidentFluxClusterIndex();

	/**
	 * This operation increments the fluence at the current time step.
     * \see IFluxHandler.h
=======
	 * \see IFluxHandler.h
	 */
	virtual void initializeTimeProfile(const std::string& fileName);

	/**
	 * This operation computes the flux due to incoming particles at a given grid point.
	 * \see IFluxHandler.h
	 */
	virtual void computeIncidentFlux(double currentTime, double *updatedConcOffset, int xi, int surfacePos);

	/**
	 * This operation increments the fluence at the current time step.
	 * \see IFluxHandler.h
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 */
	virtual void incrementFluence(double dt);

	/**
	 * This operation returns the fluence.
<<<<<<< HEAD
     * \see IFluxHandler.h
=======
	 * \see IFluxHandler.h
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 */
	virtual double getFluence() const;

	/**
	 * This operation sets the factor to change the intensity of the flux.
<<<<<<< HEAD
     * \see IFluxHandler.h
=======
	 * \see IFluxHandler.h
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 */
	virtual void setFluxAmplitude(double flux);

	/**
	 * This operation gets the factor that changes the flux intensity/amplitude.
<<<<<<< HEAD
     * \see IFluxHandler.h
=======
	 * \see IFluxHandler.h
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	 */
	virtual double getFluxAmplitude() const;

};
//end class FluxHandler

}

#endif
