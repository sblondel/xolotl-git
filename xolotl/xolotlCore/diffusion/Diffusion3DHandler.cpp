// Includes
#include "Diffusion3DHandler.h"

namespace xolotlCore {

<<<<<<< HEAD
void Diffusion3DHandler::computeDiffusion(PSIClusterReactionNetwork *network,
		double **concVector, double *updatedConcOffset,
		double sx, double sy, double sz) {
=======
void Diffusion3DHandler::initializeDiffusionGrid(std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid,
		int ny, double hy, int nz, double hz) {
	// Get the number of diffusing clusters
	int nDiff = indexVector.size();

	// Get the size of the grid in the depth direction
	int nx = grid.size();

	// Initialize the diffusion grid with true everywhere
	diffusionGrid.clear();
	// Initialize it to True
	for (int k = 0; k < nz + 2; k++) {
		std::vector < std::vector < std::vector<bool> > > tempGridTer;
		for (int j = 0; j < ny + 2; j++) {
			std::vector < std::vector<bool> > tempGridBis;
			for (int i = 0; i < nx + 2; i++) {
				std::vector<bool> tempGrid;
				for (int n = 0; n < nDiff; n++) {
					tempGrid.push_back(true);
				}
				tempGridBis.push_back(tempGrid);
			}
			tempGridTer.push_back(tempGridBis);
		}
		diffusionGrid.push_back(tempGridTer);
	}

	// Initialize the grid position
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	// Loop on the advection handlers
	for (int l = 0; l < advectionHandlers.size(); l++) {
		// Get the list of advecting clusters
		auto advecVector = advectionHandlers[l]->getIndexVector();

		// Loop on the spatial grid
		for (int k = -1; k < nz + 1; k++) {
			// Set the grid position
			gridPosition[2] = hz * (double) k;
			for (int j = -1; j < ny + 1; j++) {
				// Set the grid position
				gridPosition[1] = hy * (double) j;
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
							diffusionGrid[k+1][j+1][i+1][n] = false;
						}
					}
				}
			}
		}
	}

	return;
}

void Diffusion3DHandler::computeDiffusion(IReactionNetwork *network,
		double **concVector, double *updatedConcOffset,
		double hxLeft, double hxRight, int ix,
		double sy, int iy, double sz, int iz) {
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
		double oldConc = concVector[0][index]; // middle
		double oldLeftConc = concVector[1][index]; // left
		double oldRightConc = concVector[2][index]; // right
		double oldBottomConc = concVector[3][index]; // bottom
		double oldTopConc = concVector[4][index]; // top
		double oldFrontConc = concVector[5][index]; // front
		double oldBackConc = concVector[6][index]; // back

		// Use a simple midpoint stencil to compute the concentration
		double conc = cluster->getDiffusionCoefficient()
						* (sx * (oldLeftConc + oldRightConc - 2.0 * oldConc)
=======
		double oldConc = concVector[0][index] * diffusionGrid[iz+1][iy+1][ix+1][i]; // middle
		double oldLeftConc = concVector[1][index] * diffusionGrid[iz+1][iy+1][ix][i]; // left
		double oldRightConc = concVector[2][index] * diffusionGrid[iz+1][iy+1][ix+2][i]; // right
		double oldBottomConc = concVector[3][index] * diffusionGrid[iz+1][iy][ix+1][i]; // bottom
		double oldTopConc = concVector[4][index] * diffusionGrid[iz+1][iy+2][ix+1][i]; // top
		double oldFrontConc = concVector[5][index] * diffusionGrid[iz][iy+1][ix+1][i]; // front
		double oldBackConc = concVector[6][index] * diffusionGrid[iz+2][iy+1][ix+1][i]; // back

		// Use a simple midpoint stencil to compute the concentration
		double conc = cluster->getDiffusionCoefficient()
						* (2.0 * (oldLeftConc + (hxLeft / hxRight) * oldRightConc
										- (1.0 + (hxLeft / hxRight)) * oldConc)
								/ (hxLeft * (hxLeft + hxRight))
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
								+ sy * (oldBottomConc + oldTopConc - 2.0 * oldConc)
								+ sz * (oldFrontConc + oldBackConc - 2.0 * oldConc));

		// Update the concentration of the cluster
		updatedConcOffset[index] += conc;
	}

	return;
}

void Diffusion3DHandler::computePartialsForDiffusion(
<<<<<<< HEAD
		PSIClusterReactionNetwork *network,
		double *val, int *indices,
		double sx, double sy, double sz) {
=======
		IReactionNetwork *network,
		double *val, int *indices, double hxLeft, double hxRight, int ix,
		double sy, int iy, double sz, int iz) {
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
		// for the middle, left, right, bottom, top, front, and back grid point
<<<<<<< HEAD
		val[i * 7] = -2.0 * diffCoeff * (sx + sy + sz); // middle
		val[(i * 7) + 1] = diffCoeff * sx; // left
		val[(i * 7) + 2] = diffCoeff * sx; // right
		val[(i * 7) + 3] = diffCoeff * sy; // bottom
		val[(i * 7) + 4] = diffCoeff * sy; // top
		val[(i * 7) + 5] = diffCoeff * sz; // front
		val[(i * 7) + 6] = diffCoeff * sz; // back
=======
		val[i * 7] = - 2.0 * diffCoeff * ((1.0 / (hxLeft * hxRight)) + sy + sz)
				* diffusionGrid[iz+1][iy+1][ix+1][i]; // middle
		val[(i * 7) + 1] = diffCoeff * 2.0 / (hxLeft * (hxLeft + hxRight))
				* diffusionGrid[iz+1][iy+1][ix][i]; // left
		val[(i * 7) + 2] = diffCoeff * 2.0 / (hxRight * (hxLeft + hxRight))
				* diffusionGrid[iz+1][iy+1][ix+2][i]; // right
		val[(i * 7) + 3] = diffCoeff * sy * diffusionGrid[iz+1][iy][ix+1][i]; // bottom
		val[(i * 7) + 4] = diffCoeff * sy * diffusionGrid[iz+1][iy+2][ix+1][i]; // top
		val[(i * 7) + 5] = diffCoeff * sz * diffusionGrid[iz][iy+1][ix+1][i]; // front
		val[(i * 7) + 6] = diffCoeff * sz * diffusionGrid[iz+2][iy+1][ix+1][i]; // back
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	return;
}

}/* end namespace xolotlCore */
