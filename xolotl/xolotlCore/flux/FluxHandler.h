#ifndef FLUXHANDLER_H
#define FLUXHANDLER_H

#include "IFluxHandler.h"
#include <vector>
#include <memory>
#include <Constants.h>

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
	 * Vector to hold the position at each grid
	 * point (x position).
	 */
	std::vector<double> xGrid;

	/**
	 *  Fluence.
	 */
	double fluence;

	/**
	 * The amplitude of the flux.
	 */
	double fluxAmplitude;

	/**
<<<<<<< HEAD
	 * The index of the cluster.
	 */
	int fluxIndex;
=======
	 * The indices of the incoming clusters.
	 */
	std::vector<int> fluxIndices;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
	virtual double FitFunction(double) {
		return 0.0;
	}

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
	 *
	 * @param surfacePos The current position of the surface
	 */
	void recomputeFluxHandler(int surfacePos);

public:

	FluxHandler();

	~FluxHandler() {
	}

	/**
	 * Compute and store the incident flux values at each grid point.
	 * \see IFluxHandler.h
	 */
<<<<<<< HEAD
	virtual void initializeFluxHandler(IReactionNetwork *network,
=======
	virtual void initializeFluxHandler(const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			int surfacePos, std::vector<double> grid);

	/**
	 * This method reads the values on the time profile file and store them in the
	 * time and amplitude vectors.
	 * \see IFluxHandler.h
	 */
	virtual void initializeTimeProfile(const std::string& fileName);

	/**
	 * This operation computes the flux due to incoming particles at a given grid point.
	 * \see IFluxHandler.h
	 */
<<<<<<< HEAD
	virtual void computeIncidentFlux(double currentTime, double *updatedConcOffset, int xi, int surfacePos);
=======
	virtual void computeIncidentFlux(double currentTime,
			double *updatedConcOffset, int xi, int surfacePos);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation increments the fluence at the current time step.
	 * \see IFluxHandler.h
	 */
	virtual void incrementFluence(double dt);

	/**
	 * This operation returns the fluence.
	 * \see IFluxHandler.h
	 */
	virtual double getFluence() const;

	/**
	 * This operation sets the factor to change the intensity of the flux.
	 * \see IFluxHandler.h
	 */
	virtual void setFluxAmplitude(double flux);

	/**
	 * This operation gets the factor that changes the flux intensity/amplitude.
	 * \see IFluxHandler.h
	 */
	virtual double getFluxAmplitude() const;

};
//end class FluxHandler

}

#endif
