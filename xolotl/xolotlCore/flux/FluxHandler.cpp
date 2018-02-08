#include "FluxHandler.h"
#include <xolotlPerf.h>
#include <Reactant.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <mpi.h>

namespace xolotlCore {

FluxHandler::FluxHandler() :
<<<<<<< HEAD
		fluence(0.0),
		fluxAmplitude(0.0),
		fluxIndex(-1),
		useTimeProfile(false),
		normFactor(0.0){
=======
		fluence(0.0), fluxAmplitude(0.0), fluxIndex(-1), useTimeProfile(false), normFactor(
				0.0) {
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	return;
}

void FluxHandler::initializeFluxHandler(IReactionNetwork *network,
=======
		fluence(0.0), fluxAmplitude(0.0), useTimeProfile(false), normFactor(0.0) {
	return;
}

void FluxHandler::initializeFluxHandler(const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		int surfacePos, std::vector<double> grid) {
	// Set the grid
	xGrid = grid;

<<<<<<< HEAD
	if (xGrid.size() == 0) return;
=======
	if (xGrid.size() == 0)
		return;
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

	// Compute the norm factor because the fit function has an
	// arbitrary amplitude
	normFactor = 0.0;
	// Loop on the x grid points skipping the first after the surface position
	// and last because of the boundary conditions
	for (int i = surfacePos + 1; i < xGrid.size() - 3; i++) {
		// Get the x position
<<<<<<< HEAD
		double x = xGrid[i+1] - xGrid[surfacePos+1];

		// Add the the value of the function times the step size
<<<<<<< HEAD
<<<<<<< HEAD
		normFactor += FitFunction(x) * (xGrid[i] - xGrid[i-1]);
=======
		normFactor += FitFunction(x) * (xGrid[i] - xGrid[i - 1]);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
		normFactor += FitFunction(x) * (xGrid[i+1] - xGrid[i]);
=======
		double x = xGrid[i + 1] - xGrid[surfacePos + 1];

		// Add the the value of the function times the step size
		normFactor += FitFunction(x) * (xGrid[i + 1] - xGrid[i]);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
	}

	// Factor the incident flux will be multiplied by to get
	// the wanted intensity
	double fluxNormalized = 0.0;
<<<<<<< HEAD
	if (normFactor > 0.0) fluxNormalized = fluxAmplitude / normFactor;
=======
	if (normFactor > 0.0)
		fluxNormalized = fluxAmplitude / normFactor;
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

	// Clear the flux vector
	incidentFluxVec.clear();
	// The first value corresponding to the surface position should always be 0.0
	incidentFluxVec.push_back(0.0);

	// Starts a i = surfacePos + 1 because the first value was already put in the vector
	for (int i = surfacePos + 1; i < xGrid.size() - 3; i++) {
		// Get the x position
<<<<<<< HEAD
		auto x = xGrid[i+1] - xGrid[surfacePos+1];
=======
		auto x = xGrid[i + 1] - xGrid[surfacePos + 1];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Compute the flux value
		double incidentFlux = fluxNormalized * FitFunction(x);
		// Add it to the vector
		incidentFluxVec.push_back(incidentFlux);
	}

	// The last value should always be 0.0 because of boundary conditions
	incidentFluxVec.push_back(0.0);

	return;
}

void FluxHandler::recomputeFluxHandler(int surfacePos) {
	// Factor the incident flux will be multiplied by
	double fluxNormalized = 0.0;
<<<<<<< HEAD
	if (normFactor > 0.0) fluxNormalized = fluxAmplitude / normFactor;
=======
	if (normFactor > 0.0)
		fluxNormalized = fluxAmplitude / normFactor;
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

	// Starts a i = surfacePos + 1 because the first values were already put in the vector
	for (int i = surfacePos + 1; i < xGrid.size() - 2; i++) {
		// Get the x position
<<<<<<< HEAD
		auto x = xGrid[i+1] - xGrid[surfacePos+1];
=======
		auto x = xGrid[i + 1] - xGrid[surfacePos + 1];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Compute the flux value
		double incidentFlux = fluxNormalized * FitFunction(x);
		// Add it to the vector
		incidentFluxVec[i - surfacePos] = incidentFlux;
	}

	return;
}

void FluxHandler::initializeTimeProfile(const std::string& fileName) {
	// Set use time profile to true
	useTimeProfile = true;

	// Open file dataFile.dat containing the time and amplitude
	std::ifstream inputFile(fileName.c_str());
	std::string line;

	// Read the file and store the values in the two vectors
	while (getline(inputFile, line)) {
		if (!line.length() || line[0] == '#')
			continue;
		double xamp = 0.0, yamp = 0.0;
		sscanf(line.c_str(), "%lf %lf", &xamp, &yamp);
		time.push_back(xamp);
		amplitudes.push_back(yamp);
	}

	return;
}

double FluxHandler::getProfileAmplitude(double currentTime) const {
	// Initialize the amplitude to return
	double f = 0.0;

	// If the time is smaller than or equal than the first stored time
	if (currentTime <= time[0])
		return f = amplitudes[0];

	// If the time is larger or equal to the last stored time
	if (currentTime >= time[time.size() - 1])
		return f = amplitudes[time.size() - 1];

	// Else loop to determine the interval the time falls in
	// i.e. time[k] < time < time[k + 1]
	for (unsigned int k = 0; k < time.size() - 1; k++) {
<<<<<<< HEAD
		if (currentTime < time[k]) continue;
		if (currentTime > time[k + 1]) continue;
=======
		if (currentTime < time[k])
			continue;
		if (currentTime > time[k + 1])
			continue;
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

		// Compute the amplitude following a linear interpolation between
		// the two stored values
		f = amplitudes[k]
				+ (amplitudes[k + 1] - amplitudes[k]) * (currentTime - time[k])
						/ (time[k + 1] - time[k]);
		break;
	}

	return f;
}

<<<<<<< HEAD
void FluxHandler::computeIncidentFlux(double currentTime, double *updatedConcOffset, int xi, int surfacePos) {
=======
void FluxHandler::computeIncidentFlux(double currentTime,
		double *updatedConcOffset, int xi, int surfacePos) {
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
	// Recompute the flux vector if a time profile is used
	if (useTimeProfile) {
		fluxAmplitude = getProfileAmplitude(currentTime);
		recomputeFluxHandler(surfacePos);
	}

	if (incidentFluxVec.size() == 0) {
<<<<<<< HEAD
		updatedConcOffset[fluxIndex] += fluxAmplitude;
=======
		updatedConcOffset[fluxIndices[0]] += fluxAmplitude;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		return;
	}

	// Update the concentration array
<<<<<<< HEAD
	updatedConcOffset[fluxIndex] += incidentFluxVec[xi - surfacePos];
=======
	updatedConcOffset[fluxIndices[0]] += incidentFluxVec[xi - surfacePos];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void FluxHandler::incrementFluence(double dt) {
	// The fluence is the flux times the time
	fluence += fluxAmplitude * dt;

	return;
}

double FluxHandler::getFluence() const {
	return fluence;
}

void FluxHandler::setFluxAmplitude(double flux) {
	fluxAmplitude = flux;
}

double FluxHandler::getFluxAmplitude() const {
	return fluxAmplitude;
}

} // end namespace xolotlCore
