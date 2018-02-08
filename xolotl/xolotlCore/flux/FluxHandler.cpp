#include "FluxHandler.h"
#include <xolotlPerf.h>
<<<<<<< HEAD
=======
#include <Reactant.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <mpi.h>

namespace xolotlCore {

FluxHandler::FluxHandler() :
<<<<<<< HEAD
		stepSize(0.0),
=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		fluence(0.0),
		fluxAmplitude(0.0),
		fluxIndex(-1),
		useTimeProfile(false),
		normFactor(0.0){
	return;
}

<<<<<<< HEAD
void FluxHandler::initializeFluxHandler(PSIClusterReactionNetwork *network,
		int nx, double hx) {
	// Set the step and elementary surface sizes
	stepSize = hx;
=======
void FluxHandler::initializeFluxHandler(IReactionNetwork *network,
		int surfacePos, std::vector<double> grid) {
	// Set the grid
	xGrid = grid;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Compute the norm factor because the fit function has an
	// arbitrary amplitude
	normFactor = 0.0;
<<<<<<< HEAD
	// Loop on the x grid points skipping the first and last because
	// of the boundary conditions
	for (int i = 1; i < nx - 1; i++) {
		// Get the x position
		double x = (double) i * stepSize;

		// Add the the value of the function times the step size
		normFactor += FitFunction(x) * stepSize;
=======
	// Loop on the x grid points skipping the first after the surface position
	// and last because of the boundary conditions
	for (int i = surfacePos + 1; i < xGrid.size() - 1; i++) {
		// Get the x position
		double x = xGrid[i] - xGrid[surfacePos];

		// Add the the value of the function times the step size
		normFactor += FitFunction(x) * (xGrid[i] - xGrid[i-1]);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Factor the incident flux will be multiplied by to get
	// the wanted intensity
	double fluxNormalized = fluxAmplitude / normFactor;

<<<<<<< HEAD
	// The first value should always be 0.0 because of boundary conditions
	incidentFluxVec.push_back(0.0);

	// Starts a i = 1 because the first value was already put in the vector
	for (int i = 1; i < nx - 1; i++) {
		// Get the x position
		double x = i * stepSize;
=======
	// Clear the flux vector
	incidentFluxVec.clear();
	// The first value corresponding to the surface position should always be 0.0
	incidentFluxVec.push_back(0.0);

	// Starts a i = surfacePos + 1 because the first value was already put in the vector
	for (int i = surfacePos + 1; i < xGrid.size() - 1; i++) {
		// Get the x position
		auto x = xGrid[i] - xGrid[surfacePos];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Compute the flux value
		double incidentFlux = fluxNormalized * FitFunction(x);
		// Add it to the vector
		incidentFluxVec.push_back(incidentFlux);
	}

	// The last value should always be 0.0 because of boundary conditions
	incidentFluxVec.push_back(0.0);

<<<<<<< HEAD
	// Set the flux index corresponding the the single helium cluster here
	auto fluxCluster = (PSICluster *) network->get(heType, 1);
	// Check that the helium cluster is present in the network
	if (!fluxCluster) {
		throw std::string(
				"\nThe single helium cluster is not present in the network, "
				"cannot use the flux option!");
	}
	fluxIndex = fluxCluster->getId() - 1;

	return;
}

void FluxHandler::recomputeFluxHandler() {
	// Factor the incident flux will be multiplied by
	double fluxNormalized = fluxAmplitude / normFactor;

	// Get the number of grid points
	int numGridPoints = incidentFluxVec.size();

	// Clear the flux vector
	incidentFluxVec.clear();

	// The first value should always be 0.0 because of boundary conditions
	incidentFluxVec.push_back(0.0);

	// Starts a i = 1 because the first value was already put in the vector
	for (int i = 1; i < numGridPoints; i++) {
		// Get the x position
		double x = i * stepSize;
=======
	return;
}

void FluxHandler::recomputeFluxHandler(int surfacePos) {
	// Factor the incident flux will be multiplied by
	double fluxNormalized = fluxAmplitude / normFactor;

	// Starts a i = surfacePos + 1 because the first values were already put in the vector
	for (int i = surfacePos + 1; i < xGrid.size() - 1; i++) {
		// Get the x position
		auto x = xGrid[i] - xGrid[surfacePos];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Compute the flux value
		double incidentFlux = fluxNormalized * FitFunction(x);
		// Add it to the vector
<<<<<<< HEAD
		incidentFluxVec.push_back(incidentFlux);
=======
		incidentFluxVec[i - surfacePos] = incidentFlux;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
<<<<<<< HEAD
	for (int k = 0; k < time.size() - 1; k++) {
=======
	for (unsigned int k = 0; k < time.size() - 1; k++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		if (currentTime < time[k]) continue;
		if (currentTime > time[k + 1]) continue;

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
std::vector<double> FluxHandler::getIncidentFluxVec(double currentTime) {
	// Recompute the flux vector if a time profile is used
	if (useTimeProfile) {
		fluxAmplitude = getProfileAmplitude(currentTime);
		recomputeFluxHandler();
	}

	return incidentFluxVec;
}

int FluxHandler::getIncidentFluxClusterIndex() {
	return fluxIndex;
=======
void FluxHandler::computeIncidentFlux(double currentTime, double *updatedConcOffset, int xi, int surfacePos) {
	// Recompute the flux vector if a time profile is used
	if (useTimeProfile) {
		fluxAmplitude = getProfileAmplitude(currentTime);
		recomputeFluxHandler(surfacePos);
	}

	// Update the concentration array
	updatedConcOffset[fluxIndex] += incidentFluxVec[xi - surfacePos];

	return;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
