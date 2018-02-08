// Includes
#include "Diffusion1DHandler.h"
<<<<<<< HEAD

namespace xolotlCore {

void Diffusion1DHandler::computeDiffusion(PSIClusterReactionNetwork *network,
		double **concVector, double *updatedConcOffset,
		double sx, double sy, double sz) {
=======
#include <iostream>

namespace xolotlCore {

void Diffusion1DHandler::initializeDiffusionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid,
		int ny, double hy, int nz, double hz) {
	// Get the number of diffusing clusters
	const int nDiff = indexVector.size();

	// Get the size of the grid in the depth direction
	int nx = grid.size();

	// Initialize the diffusion grid with true everywhere
	diffusionGrid.clear();
	for (int i = 0; i < nx + 2; i++) {
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

		// Loop on the spatial grid
		for (int i = -1; i < nx + 1; i++) {
			// Set the grid position
			if (i == -1) gridPosition[0] = - 1.0;
			else if (i == nx) gridPosition[0] = grid[i-1] + 1.0;
			else gridPosition[0] = grid[i];

			// Check if we are on a sink
			if (advectionHandlers[l]->isPointOnSink(gridPosition)) {
				// We have to find the corresponding index in the diffusion
				// index vector
				for (int m = 0; m < advecVector.size(); m++) {
					// Initialize n the index in the diffusion index vector
					int n = 0;
					while (n < nDiff) {
						if (indexVector[n] == advecVector[m]) break;
						n++;
					}
					// Set this diffusion grid value to false
					diffusionGrid[i+1][n] = false;
				}
			}
		}
	}

	return;
}

void Diffusion1DHandler::computeDiffusion(IReactionNetwork *network,
		double **concVector, double *updatedConcOffset,
		double hxLeft, double hxRight, int ix,
		double, int, double, int) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
<<<<<<< HEAD
		double oldConc = concVector[0][index];
		double oldLeftConc = concVector[1][index];
		double oldRightConc = concVector[2][index];

		// Use a simple midpoint stencil to compute the concentration
		double conc = cluster->getDiffusionCoefficient()
				* (-2.0 * oldConc + oldLeftConc + oldRightConc) * sx;
=======
		double oldConc = concVector[0][index] * diffusionGrid[ix+1][i];
		double oldLeftConc = concVector[1][index] * diffusionGrid[ix][i];
		double oldRightConc = concVector[2][index] * diffusionGrid[ix+2][i];

		// Use a simple midpoint stencil to compute the concentration
		double conc = cluster->getDiffusionCoefficient() * 2.0
				* (oldLeftConc + (hxLeft / hxRight) * oldRightConc
						- (1.0 + (hxLeft / hxRight)) * oldConc)
				/ (hxLeft * (hxLeft + hxRight));
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Update the concentration of the cluster
		updatedConcOffset[index] += conc;
	}

	return;
}

void Diffusion1DHandler::computePartialsForDiffusion(
<<<<<<< HEAD
		PSIClusterReactionNetwork *network,
		double *val, int *indices,
		double sx, double sy, double sz) {
=======
		IReactionNetwork *network,
		double *val, int *indices, double hxLeft, double hxRight, int ix,
		double, int, double, int) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
<<<<<<< HEAD
		val[i * 3] = -2.0 * diffCoeff * sx; // middle
		val[(i * 3) + 1] = diffCoeff * sx; // left
		val[(i * 3) + 2] = diffCoeff * sx; // right
=======
		val[i * 3] = - 2.0 * diffCoeff / (hxLeft * hxRight) * diffusionGrid[ix+1][i]; // middle
		val[(i * 3) + 1] = diffCoeff * 2.0 / (hxLeft * (hxLeft + hxRight)) * diffusionGrid[ix][i]; // left
		val[(i * 3) + 2] = diffCoeff * 2.0 / (hxRight * (hxLeft + hxRight)) * diffusionGrid[ix+2][i]; // right
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

}/* end namespace xolotlCore */
