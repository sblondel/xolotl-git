// Includes
<<<<<<< HEAD
#include "Diffusion1DHandler.h"
#include <iostream>

namespace xolotlCore {

void Diffusion1DHandler::initializeDiffusionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid,
		int ny, double hy, int nz, double hz) {
	// Get the number of diffusing clusters
	const int nDiff = indexVector.size();
=======
#include <iostream>
#include <array>
#include "Diffusion1DHandler.h"

namespace xolotlCore {

void Diffusion1DHandler::initializeDiffusionGrid(
		std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid, int ny, double hy, int nz, double hz) {
	// Get the number of diffusing clusters
	const int nDiff = diffusingClusters.size();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the size of the grid in the depth direction
	int nx = grid.size();

	// Initialize the diffusion grid with true everywhere
	diffusionGrid.clear();
	for (int i = 0; i < nx; i++) {
<<<<<<< HEAD
		std::vector<bool> tempGrid;
		for (int n = 0; n < nDiff; n++) {
			tempGrid.push_back(true);
		}
		diffusionGrid.push_back(tempGrid);
	}

	// Initialize the grid position
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	// Loop on the advection handlers
	for (int l = 0; l < advectionHandlers.size(); l++) {
		// Get the list of advecting clusters
		auto advecVector = advectionHandlers[l]->getIndexVector();
=======
		diffusionGrid.emplace_back(nDiff, true);
	}

	// Initialize the grid position
	Point3D gridPosition { 0.0, 0.0, 0.0 };

	// Consider each advection handler
	for (auto const& currAdvectionHandler : advectionHandlers) {

		// Access collection of advecting clusters.
		auto const& advecClusters =
				currAdvectionHandler->getAdvectingClusters();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Loop on the spatial grid
		for (int i = 0; i < nx; i++) {
			// Set the grid position
			gridPosition[0] = grid[i] - grid[1];

			// Check if we are on a sink
<<<<<<< HEAD
			if (advectionHandlers[l]->isPointOnSink(gridPosition)) {
				// We have to find the corresponding index in the diffusion
				// index vector
				for (int m = 0; m < advecVector.size(); m++) {
					// Initialize n the index in the diffusion index vector
					int n = 0;
					while (n < nDiff) {
						if (indexVector[n] == advecVector[m]) break;
=======
			if (currAdvectionHandler->isPointOnSink(gridPosition)) {
				// We have to find the corresponding reactant in the diffusion
				// cluster collection.
				for (IReactant const& currAdvCluster : advecClusters) {

					// Initialize n the index in the diffusion index vector
					// TODO use std::find or std::find_if?
					int n = 0;
					while (n < nDiff) {
						IReactant const& currDiffCluster = diffusingClusters[n];
						if (&currDiffCluster == &currAdvCluster) {
							break;
						}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
						n++;
					}
					// Set this diffusion grid value to false
					diffusionGrid[i][n] = false;
				}
			}
		}
	}

	return;
}

<<<<<<< HEAD
void Diffusion1DHandler::computeDiffusion(IReactionNetwork *network,
		double **concVector, double *updatedConcOffset,
		double hxLeft, double hxRight, int ix,
		double, int, double, int) {
	// Get all the reactants
	auto reactants = network->getAll();
	// Get the number of diffusing clusters
	int nDiff = indexVector.size();

	// Loop on them
	for (int i = 0; i < nDiff; i++) {
		// Get the diffusing cluster and its index
		auto cluster = (PSICluster *) reactants->at(indexVector[i]);
		int index = cluster->getId() - 1;

		// Get the initial concentrations
		double oldConc = concVector[0][index] * diffusionGrid[ix+1][i];
		double oldLeftConc = concVector[1][index] * diffusionGrid[ix][i];
		double oldRightConc = concVector[2][index] * diffusionGrid[ix+2][i];

		// Use a simple midpoint stencil to compute the concentration
		double conc = cluster->getDiffusionCoefficient() * 2.0
=======
void Diffusion1DHandler::computeDiffusion(const IReactionNetwork& network,
		double **concVector, double *updatedConcOffset, double hxLeft,
		double hxRight, int ix, double, int, double, int) const {

	// Consider each diffusing cluster.
	// TODO Maintaining a separate index assumes that diffusingClusters is
	// visited in same order as diffusionGrid array for given point.
	// Currently true with C++11, but we'd like to be able to visit the
	// diffusing clusters in any order (so that we can parallelize).
	// Maybe with a zip? or a std::transform?
	int diffClusterIdx = 0;
	for (IReactant const& currReactant : diffusingClusters) {

		auto const& cluster = static_cast<PSICluster const&>(currReactant);
		int index = cluster.getId() - 1;

		// Get the initial concentrations
		double oldConc = concVector[0][index]
				* diffusionGrid[ix + 1][diffClusterIdx];
		double oldLeftConc = concVector[1][index]
				* diffusionGrid[ix][diffClusterIdx];
		double oldRightConc = concVector[2][index]
				* diffusionGrid[ix + 2][diffClusterIdx];

		// Use a simple midpoint stencil to compute the concentration
		double conc = cluster.getDiffusionCoefficient() * 2.0
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				* (oldLeftConc + (hxLeft / hxRight) * oldRightConc
						- (1.0 + (hxLeft / hxRight)) * oldConc)
				/ (hxLeft * (hxLeft + hxRight));

		// Update the concentration of the cluster
		updatedConcOffset[index] += conc;
	}

	return;
}

void Diffusion1DHandler::computePartialsForDiffusion(
<<<<<<< HEAD
		IReactionNetwork *network,
		double *val, int *indices, double hxLeft, double hxRight, int ix,
		double, int, double, int) {
	// Get all the reactants
	auto reactants = network->getAll();
	// Get the number of diffusing clusters
	int nDiff = indexVector.size();

	// Loop on them
	for (int i = 0; i < nDiff; i++) {
		// Get the diffusing cluster and its index
		auto cluster = (PSICluster *) reactants->at(indexVector[i]);
		int index = cluster->getId() - 1;
		// Get the diffusion coefficient of the cluster
		double diffCoeff = cluster->getDiffusionCoefficient();

		// Set the cluster index, the PetscSolver will use it to compute
		// the row and column indices for the Jacobian
		indices[i] = index;

		// Compute the partial derivatives for diffusion of this cluster
		// for the middle, left, and right grid point
		val[i * 3] = - 2.0 * diffCoeff / (hxLeft * hxRight) * diffusionGrid[ix+1][i]; // middle
		val[(i * 3) + 1] = diffCoeff * 2.0 / (hxLeft * (hxLeft + hxRight)) * diffusionGrid[ix][i]; // left
		val[(i * 3) + 2] = diffCoeff * 2.0 / (hxRight * (hxLeft + hxRight)) * diffusionGrid[ix+2][i]; // right
=======
		const IReactionNetwork& network, double *val, int *indices,
		double hxLeft, double hxRight, int ix, double, int, double, int) const {

	// Loop on them
	// TODO Maintaining a separate index assumes that diffusingClusters is
	// visited in same order as diffusionGrid array for given point.
	// Currently true with C++11, but we'd like to be able to visit the
	// diffusing clusters in any order (so that we can parallelize).
	// Maybe with a zip? or a std::transform?
	int diffClusterIdx = 0;
	for (IReactant const& currReactant : diffusingClusters) {

		auto const& cluster = static_cast<PSICluster const&>(currReactant);

		int index = cluster.getId() - 1;
		// Get the diffusion coefficient of the cluster
		double diffCoeff = cluster.getDiffusionCoefficient();

		// Set the cluster index, the PetscSolver will use it to compute
		// the row and column indices for the Jacobian
		indices[diffClusterIdx] = index;

		// Compute the partial derivatives for diffusion of this cluster
		// for the middle, left, and right grid point
		val[diffClusterIdx * 3] = -2.0 * diffCoeff / (hxLeft * hxRight)
				* diffusionGrid[ix + 1][diffClusterIdx]; // middle
		val[(diffClusterIdx * 3) + 1] = diffCoeff * 2.0
				/ (hxLeft * (hxLeft + hxRight))
				* diffusionGrid[ix][diffClusterIdx]; // left
		val[(diffClusterIdx * 3) + 2] = diffCoeff * 2.0
				/ (hxRight * (hxLeft + hxRight))
				* diffusionGrid[ix + 2][diffClusterIdx]; // right

		// Increase the index
		diffClusterIdx++;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

}/* end namespace xolotlCore */
