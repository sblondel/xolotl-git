// Includes
#include <PetscSolver2DHandler.h>
#include <HDF5Utils.h>
#include <MathUtils.h>
#include <Constants.h>

namespace xolotlSolver {

<<<<<<< HEAD
void PetscSolver2DHandler::createSolverContext(DM &da, int nx, double hx, int ny,
		double hy, int nz, double hz) {
	PetscErrorCode ierr;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->size();

	// Initialize the all reactants pointer
	allReactants = network->getAll();

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Create distributed array (DMDA) to manage parallel grid and vectors
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	ierr = DMDACreate2d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED, DM_BOUNDARY_PERIODIC,
	DMDA_STENCIL_STAR, nx, ny, PETSC_DECIDE, PETSC_DECIDE, dof, 1, NULL, NULL, &da);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: DMDACreate2d failed.");

	// Set the step size
	hX = hx;
=======
void PetscSolver2DHandler::createSolverContext(DM &da) {
	PetscErrorCode ierr;

	// Initialize the all reactants pointer
	allReactants = network->getAll();

	// Set the last temperature to 0
	lastTemperature = 0.0;

	// Reinitialize the connectivities in the network after updating the temperature
	// Get the temperature from the temperature handler
	auto temperature = temperatureHandler->getTemperature( { 0.0, 0.0, 0.0 },
			0.0);

	// Set the temperature to compute all the rate constants
	if (!xolotlCore::equal(temperature, lastTemperature)) {
		// Update the temperature and rate constants in the network
		// SetTemperature() does both
		network->setTemperature(temperature);
		lastTemperature = temperature;
	}

	// Recompute Ids and network size and redefine the connectivities
	network->reinitializeConnectivities();

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->getDOF();

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Create distributed array (DMDA) to manage parallel grid and vectors
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	// Get starting conditions from HDF5 file
	int nx = 0, ny = 0, nz = 0;
	double hx = 0.0, hy = 0.0, hz = 0.0;
	xolotlCore::HDF5Utils::readHeader(networkName, nx, hx, ny, hy, nz, hz);

	ierr = DMDACreate2d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED,
			DM_BOUNDARY_PERIODIC, DMDA_STENCIL_STAR, nx, ny, PETSC_DECIDE,
			PETSC_DECIDE, dof, 1, NULL, NULL, &da);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"DMDACreate2d failed.");
	ierr = DMSetFromOptions(da);
	checkPetscError(ierr,
			"PetscSolver2DHandler::createSolverContext: DMSetFromOptions failed.");
	ierr = DMSetUp(da);
	checkPetscError(ierr,
			"PetscSolver2DHandler::createSolverContext: DMSetUp failed.");

	// Set the position of the surface
	for (int j = 0; j < ny; j++) {
		surfacePosition.push_back(0);
		if (movingSurface)
			surfacePosition[j] = (int) (nx * portion / 100.0);
	}

	// Generate the grid in the x direction
	generateGrid(nx, hx, surfacePosition[0]);

	// Now that the grid was generated, we can update the surface position
	// if we are using a restart file
	int tempTimeStep = -2;
	bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
			networkName, tempTimeStep);

	// Get the actual surface position if concentrations were stored
	if (hasConcentrations) {
		auto surfaceIndices = xolotlCore::HDF5Utils::readSurface2D(networkName,
				tempTimeStep);

		// Set the actual surface positions
		for (int i = 0; i < surfaceIndices.size(); i++) {
			surfacePosition[i] = surfaceIndices[i];
		}
	}

//	for (int i = 0; i < grid.size(); i++) {
//		std::cout << grid[i] << " ";
//	}
//	std::cout << std::endl;

	// Initialize the surface of the first advection handler corresponding to the
	// advection toward the surface (or a dummy one if it is deactivated)
	advectionHandlers[0]->setLocation(grid[surfacePosition[0]]);

	// Set the step size
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	hY = hy;

	// Set the size of the partial derivatives vectors
	clusterPartials.resize(dof, 0.0);
	reactingPartialsForCluster.resize(dof, 0.0);

<<<<<<< HEAD
	// Set the last temperature to 0
	lastTemperature = 0.0;

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	/*  The only spatial coupling in the Jacobian is due to diffusion.
	 *  The ofill (thought of as a dof by dof 2d (row-oriented) array represents
	 *  the nonzero coupling between degrees of freedom at one point with degrees
	 *  of freedom on the adjacent point to the left or right. A 1 at i,j in the
	 *  ofill array indicates that the degree of freedom i at a point is coupled
	 *  to degree of freedom j at the adjacent point.
	 *  In this case ofill has only a few diagonal entries since the only spatial
	 *  coupling is regular diffusion.
	 */
	PetscInt *ofill, *dfill;
	ierr = PetscMalloc(dof * dof * sizeof(PetscInt), &ofill);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: PetscMalloc (ofill) failed.");
	ierr = PetscMalloc(dof * dof * sizeof(PetscInt), &dfill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: PetscMalloc (dfill) failed.");
	ierr = PetscMemzero(ofill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: PetscMemzero (ofill) failed.");
	ierr = PetscMemzero(dfill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: PetscMemzero (dfill) failed.");

	// Fill ofill, the matrix of "off-diagonal" elements that represents diffusion
	diffusionHandler->initializeOFill(network, ofill);

	// Get the diagonal fill
	getDiagonalFill(dfill, dof * dof);

	// Load up the block fills
	ierr = DMDASetBlockFills(da, dfill, ofill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: DMDASetBlockFills failed.");

	// Free the temporary fill arrays
	ierr = PetscFree(ofill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: PetscFree (ofill) failed.");
	ierr = PetscFree(dfill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: PetscFree (dfill) failed.");
=======
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"PetscMalloc (ofill) failed.");
	ierr = PetscMalloc(dof * dof * sizeof(PetscInt), &dfill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"PetscMalloc (dfill) failed.");
	ierr = PetscMemzero(ofill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"PetscMemzero (ofill) failed.");
	ierr = PetscMemzero(dfill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"PetscMemzero (dfill) failed.");

	// Fill ofill, the matrix of "off-diagonal" elements that represents diffusion
	diffusionHandler->initializeOFill(network, ofill);
	// Loop on the advection handlers to account the other "off-diagonal" elements
	for (int i = 0; i < advectionHandlers.size(); i++) {
		advectionHandlers[i]->initialize(network, ofill);
	}

	// Initialize the modified trap-mutation handler because it adds connectivity
	mutationHandler->initialize(network, grid, ny, hy);
	mutationHandler->initializeIndex2D(surfacePosition, network,
			advectionHandlers, grid, ny, hy);

	// Get the diagonal fill
	network->getDiagonalFill(dfill);

	// Load up the block fills
	ierr = DMDASetBlockFills(da, dfill, ofill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"DMDASetBlockFills failed.");

	// Free the temporary fill arrays
	ierr = PetscFree(ofill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"PetscFree (ofill) failed.");
	ierr = PetscFree(dfill);
	checkPetscError(ierr, "PetscSolver2DHandler::createSolverContext: "
			"PetscFree (dfill) failed.");

	// Initialize the arrays for the reaction partial derivatives
	reactionVals = new PetscScalar[dof * dof];
	reactionIndices = new PetscInt[dof * dof];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PetscSolver2DHandler::initializeConcentration(DM &da, Vec &C) const {
	PetscErrorCode ierr;

	// Pointer for the concentration vector
	PetscScalar ***concentrations;
	ierr = DMDAVecGetArrayDOF(da, C, &concentrations);
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: DMDAVecGetArrayDOF failed.");
=======
void PetscSolver2DHandler::initializeConcentration(DM &da, Vec &C) {
	PetscErrorCode ierr;

	// Pointer for the concentration vector
	PetscScalar ***concentrations = nullptr;
	ierr = DMDAVecGetArrayDOF(da, C, &concentrations);
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: "
			"DMDAVecGetArrayDOF failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the local boundaries
	PetscInt xs, xm, ys, ym;
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: DMDAGetCorners failed.");
=======
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: "
			"DMDAGetCorners failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the last time step written in the HDF5 file
	int tempTimeStep = -2;
	bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
			networkName, tempTimeStep);

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: DMDAGetInfo failed.");

	// Initialize the flux handler
	fluxHandler->initializeFluxHandler(network, Mx, hX);

	// Initialize the advection handler
	advectionHandler->initialize(network);

	// Pointer for the concentration vector at a specific grid point
	PetscScalar *concOffset;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->size();
=======
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: "
			"DMDAGetInfo failed.");

	// Initialize the flux handler
	fluxHandler->initializeFluxHandler(network, surfacePosition[0], grid);

	// Initialize the grid for the diffusion
	diffusionHandler->initializeDiffusionGrid(advectionHandlers, grid, My, hY);

	// Initialize the grid for the advection
	advectionHandlers[0]->initializeAdvectionGrid(advectionHandlers, grid, My,
			hY);

	// Pointer for the concentration vector at a specific grid point
	PetscScalar *concOffset = nullptr;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->getDOF();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the single vacancy ID
	auto singleVacancyCluster = network->get(xolotlCore::vType, 1);
	int vacancyIndex = -1;
	if (singleVacancyCluster)
		vacancyIndex = singleVacancyCluster->getId() - 1;

	// Loop on all the grid points
<<<<<<< HEAD
	for (int j = ys; j < ys + ym; j++) {
		for (int i = xs; i < xs + xm; i++) {
=======
	for (PetscInt j = ys; j < ys + ym; j++) {
		for (PetscInt i = xs; i < xs + xm; i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			concOffset = concentrations[j][i];

			// Loop on all the clusters to initialize at 0.0
			for (int n = 0; n < dof; n++) {
				concOffset[n] = 0.0;
			}

			// Initialize the vacancy concentration
<<<<<<< HEAD
			if (i > 0 && i < Mx - 1 && vacancyIndex > 0) {
=======
			if (i > surfacePosition[j] && i < Mx - 1 && vacancyIndex > 0 && !hasConcentrations) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				concOffset[vacancyIndex] = initialVConc;
			}
		}
	}

	// If the concentration must be set from the HDF5 file
	if (hasConcentrations) {
		// Loop on the full grid
<<<<<<< HEAD
		for (int j = 0; j < My; j++) {
			for (int i = 0; i < Mx; i++) {
				// Read the concentrations from the HDF5 file
				auto concVector = xolotlCore::HDF5Utils::readGridPoint(networkName,
						tempTimeStep, i, j);
=======
		for (PetscInt j = 0; j < My; j++) {
			for (PetscInt i = 0; i < Mx; i++) {
				// Read the concentrations from the HDF5 file
				auto concVector = xolotlCore::HDF5Utils::readGridPoint(
						networkName, tempTimeStep, i, j);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

				// Change the concentration only if we are on the locally owned part of the grid
				if (i >= xs && i < xs + xm && j >= ys && j < ys + ym) {
					concOffset = concentrations[j][i];
					// Loop on the concVector size
<<<<<<< HEAD
					for (int l = 0; l < concVector.size(); l++) {
=======
					for (unsigned int l = 0; l < concVector.size(); l++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
						concOffset[(int) concVector.at(l).at(0)] =
								concVector.at(l).at(1);
					}
				}
			}
		}
	}

	/*
	 Restore vectors
	 */
	ierr = DMDAVecRestoreArrayDOF(da, C, &concentrations);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: DMDAVecRestoreArrayDOF failed.");
=======
	checkPetscError(ierr, "PetscSolver2DHandler::initializeConcentration: "
			"DMDAVecRestoreArrayDOF failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

void PetscSolver2DHandler::updateConcentration(TS &ts, Vec &localC, Vec &F,
		PetscReal ftime) {
	PetscErrorCode ierr;

	// Get the local data vector from PETSc
	DM da;
	ierr = TSGetDM(ts, &da);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMDAGetInfo failed.");

	// Pointers to the PETSc arrays that start at the beginning (xs, ys) of the
	// local array!
	PetscScalar ***concs, ***updatedConcs;
	// Get pointers to vector data
	ierr = DMDAVecGetArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMDAVecGetArrayDOF (localC) failed.");
	ierr = DMDAVecGetArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMDAVecGetArrayDOF (F) failed.");
=======
	checkPetscError(ierr,
			"PetscSolver2DHandler::updateConcentration: TSGetDM failed.");

	// Get the total size of the grid in the x direction for the boundary conditions
	int xSize = grid.size();

	// Pointers to the PETSc arrays that start at the beginning (xs, ys) of the
	// local array!
	PetscScalar ***concs = nullptr, ***updatedConcs = nullptr;
	// Get pointers to vector data
	ierr = DMDAVecGetArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMDAVecGetArrayDOFRead (localC) failed.");
	ierr = DMDAVecGetArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMDAVecGetArrayDOF (F) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get local grid boundaries
	PetscInt xs, xm, ys, ym;
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMDAGetCorners failed.");
=======
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMDAGetCorners failed.");

	// Get the total size of the grid
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMDAGetInfo failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// The following pointers are set to the first position in the conc or
	// updatedConc arrays that correspond to the beginning of the data for the
	// current grid point. They are accessed just like regular arrays.
<<<<<<< HEAD
	PetscScalar *concOffset, *updatedConcOffset;

	// Set some step size variable
	double sx = 1.0 / (hX * hX);
	double sy = 1.0 / (hY * hY);

	// Get the incident flux vector
	auto incidentFluxVector = fluxHandler->getIncidentFluxVec(ftime);

	// Declarations for variables used in the loop
	double flux;
	int fluxIndex = fluxHandler->getIncidentFluxClusterIndex(), reactantIndex;
	xolotlCore::PSICluster *cluster = NULL;
	double **concVector = new double*[5];
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->size();

	// Loop over grid points computing ODE terms for each grid point
	for (int yj = ys; yj < ys + ym; yj++) {
		for (int xi = xs; xi < xs + xm; xi++) {
=======
	PetscScalar *concOffset = nullptr, *updatedConcOffset = nullptr;

	// Set some step size variable
	double sy = 1.0 / (hY * hY);

	// Declarations for variables used in the loop
	double **concVector = new double*[5];
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 }, incidentFluxVector;
	double atomConc = 0.0, totalAtomConc = 0.0;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->getDOF();

	// Loop over grid points
	for (PetscInt yj = 0; yj < My; yj++) {

		// Compute the total concentration of atoms contained in bubbles
		atomConc = 0.0;

		// Loop over grid points
		for (int xi = surfacePosition[yj]; xi < Mx - 1; xi++) {
			// We are only interested in the helium near the surface
			if (grid[xi] - grid[surfacePosition[yj]] > 2.0)
				continue;

			// Check if we are on the right processor
			if (xi >= xs && xi < xs + xm && yj >= ys && yj < ys + ym) {
				// Get the concentrations at this grid point
				concOffset = concs[yj][xi];
				// Copy data into the PSIClusterReactionNetwork
				network->updateConcentrationsFromArray(concOffset);

				// Sum the total atom concentration
				atomConc += network->getTotalTrappedAtomConcentration()
						* (grid[xi] - grid[xi - 1]);
			}
		}

		// Share the concentration with all the processes
		totalAtomConc = 0.0;
		MPI_Allreduce(&atomConc, &totalAtomConc, 1, MPI_DOUBLE, MPI_SUM,
				MPI_COMM_WORLD);

		// Set the disappearing rate in the modified TM handler
		mutationHandler->updateDisappearingRate(totalAtomConc);

		// Skip if we are not on the right process
		if (yj < ys || yj >= ys + ym)
			continue;

		// Set the grid position
		gridPosition[1] = yj * hY;

		// Initialize the flux, advection, and trap-mutation handlers which depend
		// on the surface position at Y
		fluxHandler->initializeFluxHandler(network, surfacePosition[yj], grid);
		advectionHandlers[0]->setLocation(grid[surfacePosition[yj]]);

		for (PetscInt xi = xs; xi < xs + xm; xi++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// Compute the old and new array offsets
			concOffset = concs[yj][xi];
			updatedConcOffset = updatedConcs[yj][xi];

<<<<<<< HEAD
			// Fill the concVector with the pointer to the middle, left, right, bottom, and top grid points
			concVector[0] = concOffset; // middle
			concVector[1] = concs[yj][xi - 1]; // left
			concVector[2] = concs[yj][xi + 1]; // right
			concVector[3] = concs[yj - 1][xi]; // bottom
			concVector[4] = concs[yj + 1][xi]; // top

			// Boundary conditions
			if (xi == 0 || xi == Mx - 1) {
=======
			// Boundary conditions
			// Everything to the left of the surface is empty
			if (xi <= surfacePosition[yj] || xi == xSize - 1) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				for (int i = 0; i < dof; i++) {
					updatedConcOffset[i] = 1.0 * concOffset[i];
				}

				continue;
			}

			// Set the grid position
<<<<<<< HEAD
			gridPosition[0] = xi * hX;
			gridPosition[1] = yj * hY;
=======
			gridPosition[0] = grid[xi];

			// Fill the concVector with the pointer to the middle, left, right, bottom, and top grid points
			concVector[0] = concOffset; // middle
			concVector[1] = concs[yj][xi - 1]; // left
			concVector[2] = concs[yj][xi + 1]; // right
			concVector[3] = concs[yj - 1][xi]; // bottom
			concVector[4] = concs[yj + 1][xi]; // top
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

			// Get the temperature from the temperature handler
			auto temperature = temperatureHandler->getTemperature(gridPosition,
					ftime);

			// Update the network if the temperature changed
			if (!xolotlCore::equal(temperature, lastTemperature)) {
				network->setTemperature(temperature);
<<<<<<< HEAD
				lastTemperature = temperature;
			}

			// Copy data into the PSIClusterReactionNetwork so that it can
=======
				// Update the modified trap-mutation rate that depends on the
				// network reaction rates
				mutationHandler->updateTrapMutationRate(network);
				lastTemperature = temperature;
			}

			// Copy data into the ReactionNetwork so that it can
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// compute the fluxes properly. The network is only used to compute the
			// fluxes and hold the state data from the last time step. I'm reusing
			// it because it cuts down on memory significantly (about 400MB per
			// grid point) at the expense of being a little tricky to comprehend.
			network->updateConcentrationsFromArray(concOffset);

<<<<<<< HEAD
			// ----- Account for flux of incoming He of cluster size 1 -----
				updatedConcOffset[fluxIndex] += incidentFluxVector[xi];

			// ---- Compute diffusion over the locally owned part of the grid -----
			diffusionHandler->computeDiffusion(network, concVector,
					updatedConcOffset, sx, sy);

			// ---- Compute advection over the locally owned part of the grid -----
			advectionHandler->computeAdvection(network, hX, gridPosition, concVector,
					updatedConcOffset);

			// ----- Compute all of the new fluxes -----
			for (int i = 0; i < dof; i++) {
				cluster = (xolotlCore::PSICluster *) allReactants->at(i);
				// Compute the flux
				flux = cluster->getTotalFlux();
				// Update the concentration of the cluster
				reactantIndex = cluster->getId() - 1;
				updatedConcOffset[reactantIndex] += flux;
			}
=======
			// ----- Account for flux of incoming particles -----
			fluxHandler->computeIncidentFlux(ftime, updatedConcOffset, xi, surfacePosition[yj]);

			// ---- Compute diffusion over the locally owned part of the grid -----
			diffusionHandler->computeDiffusion(network, concVector,
					updatedConcOffset, grid[xi] - grid[xi - 1],
					grid[xi + 1] - grid[xi], xi, sy, yj);

			// ---- Compute advection over the locally owned part of the grid -----
			for (int i = 0; i < advectionHandlers.size(); i++) {
				advectionHandlers[i]->computeAdvection(network, gridPosition,
						concVector, updatedConcOffset, grid[xi] - grid[xi - 1],
						grid[xi + 1] - grid[xi], xi, hY, yj);
			}

			// ----- Compute the modified trap-mutation over the locally owned part of the grid -----
			mutationHandler->computeTrapMutation(network, concOffset,
					updatedConcOffset, xi, yj);

			// ----- Compute the reaction fluxes over the locally owned part of the grid -----
			network->computeAllFluxes(updatedConcOffset);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		}
	}

	/*
	 Restore vectors
	 */
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMDAVecRestoreArrayDOF (localC) failed.");
	ierr = DMDAVecRestoreArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMDAVecRestoreArrayDOF (F) failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: DMRestoreLocalVector failed.");
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMDAVecRestoreArrayDOFRead (localC) failed.");
	ierr = DMDAVecRestoreArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMDAVecRestoreArrayDOF (F) failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver2DHandler::updateConcentration: "
			"DMRestoreLocalVector failed.");

	// Clear memory
	delete[] concVector;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PetscSolver2DHandler::computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J) const {
=======
void PetscSolver2DHandler::computeOffDiagonalJacobian(TS &ts, Vec &localC,
		Mat &J, PetscReal ftime) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;

	// Get the distributed array
	DM da;
	ierr = TSGetDM(ts, &da);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: DMDAGetInfo failed.");

	// Setup some step size variables
	double sx = 1.0 / (hX * hX);
	double sy = 1.0 / (hY * hY);

	// Get pointers to vector data
	PetscScalar ***concs;
	ierr = DMDAVecGetArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: DMDAVecGetArrayDOF failed.");

	// Get local grid boundaries
	PetscInt xs, xm, ys, ym;
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: DMDAGetCorners failed.");

	// Pointer to the concentrations at a given grid point
	PetscScalar *concOffset;
=======
	checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: "
			"TSGetDM failed.");

	// Get the total size of the grid in the x direction for the boundary conditions
	int xSize = grid.size();

	// Setup some step size variables
	double sy = 1.0 / (hY * hY);

	// Get local grid boundaries
	PetscInt xs, xm, ys, ym;
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: "
			"DMDAGetCorners failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the total number of diffusing clusters
	const int nDiff = diffusionHandler->getNumberOfDiffusing();

	// Get the total number of advecting clusters
<<<<<<< HEAD
	const int nAdvec = advectionHandler->getNumberOfAdvecting();

	// Arguments for MatSetValuesStencil called below
	MatStencil row, cols[5];
	PetscScalar vals[5 * nDiff];
	int indices[nDiff];
=======
	int nAdvec = 0;
	for (int l = 0; l < advectionHandlers.size(); l++) {
		int n = advectionHandlers[l]->getNumberOfAdvecting();
		if (n > nAdvec)
			nAdvec = n;
	}

	// Arguments for MatSetValuesStencil called below
	MatStencil row, cols[5];
	PetscScalar diffVals[5 * nDiff];
	PetscInt diffIndices[nDiff];
	PetscScalar advecVals[2 * nAdvec];
	PetscInt advecIndices[nAdvec];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	/*
	 Loop over grid points computing Jacobian terms for diffusion and advection
	 at each grid point
	 */
<<<<<<< HEAD
	for (int yj = ys; yj < ys + ym; yj++) {
		for (int xi = xs; xi < xs + xm; xi++) {
			// Boundary conditions
			if (xi == 0 || xi == Mx - 1) continue;

			// Set the grid position
			gridPosition[0] = xi * hX;
			gridPosition[1] = yj * hY;

			// Copy data into the PSIClusterReactionNetwork so that it can
			// compute the new concentrations.
			concOffset = concs[yj][xi];
			network->updateConcentrationsFromArray(concOffset);

			// Get the partial derivatives for the diffusion
			diffusionHandler->computePartialsForDiffusion(network, vals, indices, sx, sy);
=======
	for (PetscInt yj = ys; yj < ys + ym; yj++) {
		// Set the grid position
		gridPosition[1] = yj * hY;

		// Initialize the advection handler which depends
		// on the surface position at Y
		advectionHandlers[0]->setLocation(grid[surfacePosition[yj]]);

		for (PetscInt xi = xs; xi < xs + xm; xi++) {
			// Boundary conditions
			// Everything to the left of the surface is empty
			if (xi <= surfacePosition[yj] || xi == xSize - 1)
				continue;

			// Set the grid position
			gridPosition[0] = grid[xi];

			// Get the temperature from the temperature handler
			auto temperature = temperatureHandler->getTemperature(gridPosition,
					ftime);

			// Update the network if the temperature changed
			if (!xolotlCore::equal(temperature, lastTemperature)) {
				network->setTemperature(temperature);
				// Update the modified trap-mutation rate that depends on the
				// network reaction rates
				mutationHandler->updateTrapMutationRate(network);
				lastTemperature = temperature;
			}

			// Get the partial derivatives for the diffusion
			diffusionHandler->computePartialsForDiffusion(network, diffVals,
					diffIndices, grid[xi] - grid[xi - 1],
					grid[xi + 1] - grid[xi], xi, sy, yj);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

			// Loop on the number of diffusion cluster to set the values in the Jacobian
			for (int i = 0; i < nDiff; i++) {
				// Set grid coordinate and component number for the row
				row.i = xi;
				row.j = yj;
<<<<<<< HEAD
				row.c = indices[i];
=======
				row.c = diffIndices[i];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

				// Set grid coordinates and component numbers for the columns
				// corresponding to the middle, left, right, bottom, and top grid points
				cols[0].i = xi; // middle
				cols[0].j = yj;
<<<<<<< HEAD
				cols[0].c = indices[i];
				cols[1].i = xi - 1; // left
				cols[1].j = yj;
				cols[1].c = indices[i];
				cols[2].i = xi + 1; // right
				cols[2].j = yj;
				cols[2].c = indices[i];
				cols[3].i = xi; // bottom
				cols[3].j = yj - 1;
				cols[3].c = indices[i];
				cols[4].i = xi; // top
				cols[4].j = yj + 1;
				cols[4].c = indices[i];

				ierr = MatSetValuesStencil(J, 1, &row, 5, cols, vals + (5 * i), ADD_VALUES);
				checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: MatSetValuesStencil (diffusion) failed.");
			}

			// Get the partial derivatives for the advection
			advectionHandler->computePartialsForAdvection(network, hX, vals,
					indices, gridPosition);

			// Loop on the number of advecting cluster to set the values in the Jacobian
			for (int i = 0; i < nAdvec; i++) {
				// Set grid coordinate and component number for the row
				row.i = xi;
				row.j = yj;
				row.c = indices[i];

				// Set grid coordinates and component numbers for the columns
				// corresponding to the middle and right grid points
				cols[0].i = xi; // middle
				cols[0].j = yj;
				cols[0].c = indices[i];
				cols[1].i = xi + 1; // right
				cols[1].j = yj;
				cols[1].c = indices[i];

				// Update the matrix
				ierr = MatSetValuesStencil(J, 1, &row, 2, cols, vals + (2 * i), ADD_VALUES);
				checkPetscError(ierr, "PetscSolver2DHandler::computeOffDiagonalJacobian: MatSetValuesStencil (advection) failed.");
=======
				cols[0].c = diffIndices[i];
				cols[1].i = xi - 1; // left
				cols[1].j = yj;
				cols[1].c = diffIndices[i];
				cols[2].i = xi + 1; // right
				cols[2].j = yj;
				cols[2].c = diffIndices[i];
				cols[3].i = xi; // bottom
				cols[3].j = yj - 1;
				cols[3].c = diffIndices[i];
				cols[4].i = xi; // top
				cols[4].j = yj + 1;
				cols[4].c = diffIndices[i];

				ierr = MatSetValuesStencil(J, 1, &row, 5, cols,
						diffVals + (5 * i), ADD_VALUES);
				checkPetscError(ierr,
						"PetscSolver2DHandler::computeOffDiagonalJacobian: "
								"MatSetValuesStencil (diffusion) failed.");
			}

			// Get the partial derivatives for the advection
			for (int l = 0; l < advectionHandlers.size(); l++) {
				advectionHandlers[l]->computePartialsForAdvection(network,
						advecVals, advecIndices, gridPosition,
						grid[xi] - grid[xi - 1], grid[xi + 1] - grid[xi], xi,
						hY, yj);

				// Get the stencil indices to know where to put the partial derivatives in the Jacobian
				auto advecStencil =
						advectionHandlers[l]->getStencilForAdvection(
								gridPosition);

				// Get the number of advecting clusters
				nAdvec = advectionHandlers[l]->getNumberOfAdvecting();

				// Loop on the number of advecting cluster to set the values in the Jacobian
				for (int i = 0; i < nAdvec; i++) {
					// Set grid coordinate and component number for the row
					row.i = xi;
					row.j = yj;
					row.c = advecIndices[i];

					// If we are on the sink, the partial derivatives are not the same
					// Both sides are giving their concentrations to the center
					if (advectionHandlers[l]->isPointOnSink(gridPosition)) {
						cols[0].i = xi - advecStencil[0]; // left?
						cols[0].j = yj - advecStencil[1]; // bottom?
						cols[0].c = advecIndices[i];
						cols[1].i = xi + advecStencil[0]; // right?
						cols[1].j = yj + advecStencil[1]; // top?
						cols[1].c = advecIndices[i];
					} else {
						// Set grid coordinates and component numbers for the columns
						// corresponding to the middle and other grid points
						cols[0].i = xi; // middle
						cols[0].j = yj;
						cols[0].c = advecIndices[i];
						cols[1].i = xi + advecStencil[0]; // left or right?
						cols[1].j = yj + advecStencil[1]; // bottom or top?
						cols[1].c = advecIndices[i];
					}

					// Update the matrix
					ierr = MatSetValuesStencil(J, 1, &row, 2, cols,
							advecVals + (2 * i), ADD_VALUES);
					checkPetscError(ierr,
							"PetscSolver2DHandler::computeOffDiagonalJacobian: "
									"MatSetValuesStencil (advection) failed.");
				}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			}
		}
	}

	return;
}

<<<<<<< HEAD
void PetscSolver2DHandler::computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J) {
=======
void PetscSolver2DHandler::computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J,
		PetscReal ftime) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;

	// Get the distributed array
	DM da;
	ierr = TSGetDM(ts, &da);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: DMDAGetInfo failed.");

	// Get pointers to vector data
	PetscScalar ***concs;
	ierr = DMDAVecGetArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: DMDAVecGetArrayDOF failed.");
=======
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: "
			"TSGetDM failed.");

	// Get the total size of the grid in the x direction for the boundary conditions
	int xSize = grid.size();

	// Get pointers to vector data
	PetscScalar ***concs = nullptr;
	ierr = DMDAVecGetArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: "
			"DMDAVecGetArrayDOFRead failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get local grid boundaries
	PetscInt xs, xm, ys, ym;
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: DMDAGetCorners failed.");

	// The degree of freedom is the size of the network
	const int dof = network->size();

	// Pointer to the concentrations at a given grid point
	PetscScalar *concOffset;
=======
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: "
			"DMDAGetCorners failed.");

	// Get the total size of the grid
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: "
			"DMDAGetInfo failed.");

	// The degree of freedom is the size of the network
	const int dof = network->getDOF();

	// Pointer to the concentrations at a given grid point
	PetscScalar *concOffset = nullptr;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Arguments for MatSetValuesStencil called below
	MatStencil rowId;
	MatStencil colIds[dof];
	int pdColIdsVectorSize = 0;
<<<<<<< HEAD

	// Declarations for variables used in the loop
	int reactantIndex;

	// Loop over the grid points
	for (int yj = ys; yj < ys + ym; yj++) {
		for (int xi = xs; xi < xs + xm; xi++) {
			// Boundary conditions
			if (xi == 0 || xi == Mx - 1) continue;

			// Copy data into the PSIClusterReactionNetwork so that it can
=======
	PetscInt reactionSize[dof];

	// Store the total number of He clusters in the network for the
	// modified trap-mutation
	int nHelium = network->getAll(xolotlCore::heType).size();

	// Declarations for variables used in the loop
	double atomConc = 0.0, totalAtomConc = 0.0;
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	// Loop over the grid points
	for (PetscInt yj = 0; yj < My; yj++) {

		// Compute the total concentration of atoms contained in bubbles
		atomConc = 0.0;

		// Loop over grid points
		for (int xi = surfacePosition[yj]; xi < Mx -1; xi++) {
			// We are only interested in the helium near the surface
			if (grid[xi] - grid[surfacePosition[yj]] > 2.0)
				continue;

			// Check if we are on the right processor
			if (xi >= xs && xi < xs + xm && yj >= ys && yj < ys + ym) {
				// Get the concentrations at this grid point
				concOffset = concs[yj][xi];
				// Copy data into the PSIClusterReactionNetwork
				network->updateConcentrationsFromArray(concOffset);

				// Sum the total atom concentration
				atomConc += network->getTotalTrappedAtomConcentration()
						* (grid[xi] - grid[xi - 1]);
			}
		}

		// Share the concentration with all the processes
		totalAtomConc = 0.0;
		MPI_Allreduce(&atomConc, &totalAtomConc, 1, MPI_DOUBLE, MPI_SUM,
				MPI_COMM_WORLD);

		// Set the disappearing rate in the modified TM handler
		mutationHandler->updateDisappearingRate(totalAtomConc);

		// Skip if we are not on the right process
		if (yj < ys || yj >= ys + ym)
			continue;

		// Set the grid position
		gridPosition[1] = yj * hY;

		for (PetscInt xi = xs; xi < xs + xm; xi++) {
			// Boundary conditions
			// Everything to the left of the surface is empty
			if (xi <= surfacePosition[yj] || xi == xSize - 1)
				continue;

			// Set the grid position
			gridPosition[0] = grid[xi];

			// Get the temperature from the temperature handler
			auto temperature = temperatureHandler->getTemperature(gridPosition,
					ftime);

			// Update the network if the temperature changed
			if (!xolotlCore::equal(temperature, lastTemperature)) {
				network->setTemperature(temperature);
				// Update the modified trap-mutation rate that depends on the
				// network reaction rates
				mutationHandler->updateTrapMutationRate(network);
				lastTemperature = temperature;
			}

			// Copy data into the ReactionNetwork so that it can
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// compute the new concentrations.
			concOffset = concs[yj][xi];
			network->updateConcentrationsFromArray(concOffset);

<<<<<<< HEAD
			// Update the column in the Jacobian that represents each reactant
			for (int i = 0; i < dof; i++) {
				auto reactant = allReactants->at(i);
				// Get the reactant index
				reactantIndex = reactant->getId() - 1;

				// Set grid coordinate and component number for the row
				rowId.i = xi;
				rowId.j = yj;
				rowId.c = reactantIndex;

				// Get the partial derivatives
				reactant->getPartialDerivatives(clusterPartials);
				// Get the list of column ids from the map
				auto pdColIdsVector = dFillMap.at(reactantIndex);
				// Number of partial derivatives
				pdColIdsVectorSize = pdColIdsVector.size();
=======
			// ----- Take care of the reactions for all the reactants -----

			// Compute all the partial derivatives for the reactions
			network->computeAllPartials(reactionVals, reactionIndices,
					reactionSize);

			// Update the column in the Jacobian that represents each DOF
			for (int i = 0; i < dof; i++) {
				// Set grid coordinate and component number for the row
				rowId.i = xi;
				rowId.j = yj;
				rowId.c = i;

				// Number of partial derivatives
				pdColIdsVectorSize = reactionSize[i];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				// Loop over the list of column ids
				for (int j = 0; j < pdColIdsVectorSize; j++) {
					// Set grid coordinate and component number for a column in the list
					colIds[j].i = xi;
					colIds[j].j = yj;
<<<<<<< HEAD
					colIds[j].c = pdColIdsVector[j];
					// Get the partial derivative from the array of all of the partials
					reactingPartialsForCluster[j] =
							clusterPartials[pdColIdsVector[j]];
					// Reset the cluster partial value to zero. This is much faster
					// than using memset.
					clusterPartials[pdColIdsVector[j]] = 0.0;
				}
				// Update the matrix
				ierr = MatSetValuesStencil(J, 1, &rowId, pdColIdsVectorSize, colIds,
						reactingPartialsForCluster.data(), ADD_VALUES);
				checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: MatSetValuesStencil failed.");
=======
					colIds[j].c = reactionIndices[i * dof + j];
					// Get the partial derivative from the array of all of the partials
					reactingPartialsForCluster[j] = reactionVals[i * dof + j];
				}
				// Update the matrix
				ierr = MatSetValuesStencil(J, 1, &rowId, pdColIdsVectorSize,
						colIds, reactingPartialsForCluster.data(), ADD_VALUES);
				checkPetscError(ierr,
						"PetscSolver1DHandler::computeDiagonalJacobian: "
								"MatSetValuesStencil (reactions) failed.");
			}

			// ----- Take care of the modified trap-mutation for all the reactants -----

			// Arguments for MatSetValuesStencil called below
			MatStencil row, col;
			PetscScalar mutationVals[3 * nHelium];
			PetscInt mutationIndices[3 * nHelium];

			// Compute the partial derivative from modified trap-mutation at this grid point
			int nMutating = mutationHandler->computePartialsForTrapMutation(
					network, mutationVals, mutationIndices, xi, yj);

			// Loop on the number of helium undergoing trap-mutation to set the values
			// in the Jacobian
			for (int i = 0; i < nMutating; i++) {
				// Set grid coordinate and component number for the row and column
				// corresponding to the helium cluster
				row.i = xi;
				row.j = yj;
				row.c = mutationIndices[3 * i];
				col.i = xi;
				col.j = yj;
				col.c = mutationIndices[3 * i];

				ierr = MatSetValuesStencil(J, 1, &row, 1, &col,
						mutationVals + (3 * i), ADD_VALUES);
				checkPetscError(ierr,
						"PetscSolver2DHandler::computeDiagonalJacobian: "
								"MatSetValuesStencil (He trap-mutation) failed.");

				// Set component number for the row
				// corresponding to the HeV cluster created through trap-mutation
				row.c = mutationIndices[(3 * i) + 1];

				ierr = MatSetValuesStencil(J, 1, &row, 1, &col,
						mutationVals + (3 * i) + 1, ADD_VALUES);
				checkPetscError(ierr,
						"PetscSolver2DHandler::computeDiagonalJacobian: "
								"MatSetValuesStencil (HeV trap-mutation) failed.");

				// Set component number for the row
				// corresponding to the interstitial created through trap-mutation
				row.c = mutationIndices[(3 * i) + 2];

				ierr = MatSetValuesStencil(J, 1, &row, 1, &col,
						mutationVals + (3 * i) + 2, ADD_VALUES);
				checkPetscError(ierr,
						"PetscSolver2DHandler::computeDiagonalJacobian: "
								"MatSetValuesStencil (I trap-mutation) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			}
		}
	}

	/*
	 Restore vectors
	 */
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: DMDAVecRestoreArrayDOF failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: DMRestoreLocalVector failed.");
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: "
			"DMDAVecRestoreArrayDOFRead failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver2DHandler::computeDiagonalJacobian: "
			"DMRestoreLocalVector failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

} /* end namespace xolotlSolver */
