// Includes
#include <PetscSolver1DHandler.h>
#include <HDF5Utils.h>
#include <MathUtils.h>
#include <Constants.h>

namespace xolotlSolver {

<<<<<<< HEAD
void PetscSolver1DHandler::createSolverContext(DM &da, int nx, double hx, int ny,
		double hy, int nz, double hz) {
	PetscErrorCode ierr;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->size();

	// Initialize the all reactants pointer
	allReactants = network->getAll();

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	 Create distributed array (DMDA) to manage parallel grid and vectors
	 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
	ierr = DMDACreate1d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED, nx, dof, 1,
	NULL, &da);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: DMDACreate1d failed.");

	// Set the step size
	hX = hx;
=======
void PetscSolver1DHandler::createSolverContext(DM &da) {
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

	ierr = DMDACreate1d(PETSC_COMM_WORLD, DM_BOUNDARY_GHOSTED, nx, dof, 1,
	NULL, &da);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"DMDACreate1d failed.");
	ierr = DMSetFromOptions(da);
	checkPetscError(ierr,
			"PetscSolver1DHandler::createSolverContext: DMSetFromOptions failed.");
	ierr = DMSetUp(da);
	checkPetscError(ierr,
			"PetscSolver1DHandler::createSolverContext: DMSetUp failed.");

	// Set the position of the surface
	surfacePosition = 0;
	if (movingSurface)
		surfacePosition = (int) (nx * portion / 100.0);

	// Generate the grid in the x direction
	generateGrid(nx, hx, surfacePosition);

	// Now that the grid was generated, we can update the surface position
	// if we are using a restart file
	int tempTimeStep = -2;
	bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
			networkName, tempTimeStep);
	if (hasConcentrations) {
		surfacePosition = xolotlCore::HDF5Utils::readSurface1D(networkName,
				tempTimeStep);
	}

	// Initialize the surface of the first advection handler corresponding to the
	// advection toward the surface (or a dummy one if it is deactivated)
	advectionHandlers[0]->setLocation(grid[surfacePosition]);

//	for (int i = 0; i < grid.size(); i++) {
//		std::cout << grid[i] - grid[surfacePosition] << " ";
//	}
//	std::cout << std::endl;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

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
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: PetscMalloc (ofill) failed.");
	ierr = PetscMalloc(dof * dof * sizeof(PetscInt), &dfill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: PetscMalloc (dfill) failed.");
	ierr = PetscMemzero(ofill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: PetscMemzero (ofill) failed.");
	ierr = PetscMemzero(dfill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: PetscMemzero (dfill) failed.");

	// Fill ofill, the matrix of "off-diagonal" elements that represents diffusion
	diffusionHandler->initializeOFill(network, ofill);

	// Get the diagonal fill
	getDiagonalFill(dfill, dof * dof);

	// Load up the block fills
	ierr = DMDASetBlockFills(da, dfill, ofill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: DMDASetBlockFills failed.");

	// Free the temporary fill arrays
	ierr = PetscFree(ofill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: PetscFree (ofill) failed.");
	ierr = PetscFree(dfill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: PetscFree (dfill) failed.");
=======
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"PetscMalloc (ofill) failed.");
	ierr = PetscMalloc(dof * dof * sizeof(PetscInt), &dfill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"PetscMalloc (dfill) failed.");
	ierr = PetscMemzero(ofill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"PetscMemzero (ofill) failed.");
	ierr = PetscMemzero(dfill, dof * dof * sizeof(PetscInt));
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"PetscMemzero (dfill) failed.");

	// Fill ofill, the matrix of "off-diagonal" elements that represents diffusion
	diffusionHandler->initializeOFill(network, ofill);
	// Loop on the advection handlers to account the other "off-diagonal" elements
	for (int i = 0; i < advectionHandlers.size(); i++) {
		advectionHandlers[i]->initialize(network, ofill);
	}

	// Initialize the modified trap-mutation handler here
	// because it adds connectivity
	mutationHandler->initialize(network, grid);
	mutationHandler->initializeIndex1D(surfacePosition, network,
			advectionHandlers, grid);

	// Get the diagonal fill
	network->getDiagonalFill(dfill);

	// Load up the block fills
	ierr = DMDASetBlockFills(da, dfill, ofill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"DMDASetBlockFills failed.");

	// Free the temporary fill arrays
	ierr = PetscFree(ofill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"PetscFree (ofill) failed.");
	ierr = PetscFree(dfill);
	checkPetscError(ierr, "PetscSolver1DHandler::createSolverContext: "
			"PetscFree (dfill) failed.");

	// Initialize the arrays for the reaction partial derivatives
	reactionVals = new PetscScalar[dof * dof];
	reactionIndices = new PetscInt[dof * dof];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PetscSolver1DHandler::initializeConcentration(DM &da, Vec &C) const {
	PetscErrorCode ierr;

	// Pointer for the concentration vector
	PetscScalar **concentrations;
	ierr = DMDAVecGetArrayDOF(da, C, &concentrations);
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: DMDAVecGetArrayDOF failed.");
=======
void PetscSolver1DHandler::initializeConcentration(DM &da, Vec &C) {
	PetscErrorCode ierr;

	// Pointer for the concentration vector
	PetscScalar **concentrations = nullptr;
	ierr = DMDAVecGetArrayDOF(da, C, &concentrations);
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: "
			"DMDAVecGetArrayDOF failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the local boundaries
	PetscInt xs, xm;
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: DMDAGetCorners failed.");

	// Get the last time step written in the HDF5 file
	int tempTimeStep = -2;
	bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(networkName,
			tempTimeStep);

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: DMDAGetInfo failed.");

	// Initialize the flux handler
	fluxHandler->initializeFluxHandler(network, Mx, hX);

	// Initialize the advection handler
	advectionHandler->initialize(network);

	// Pointer for the concentration vector at a specific grid point
	PetscScalar *concOffset;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->size();
=======
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: "
			"DMDAGetCorners failed.");

	// Get the last time step written in the HDF5 file
	int tempTimeStep = -2;
	bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
			networkName, tempTimeStep);

	// Get the total size of the grid for the boundary conditions
	int xSize = grid.size();

	// Initialize the flux handler
	fluxHandler->initializeFluxHandler(network, surfacePosition, grid);

	// Initialize the displacement handler
	displacementHandler->initializeDisplacementHandler(network, surfacePosition,
			grid);

	// Initialize the grid for the diffusion
	diffusionHandler->initializeDiffusionGrid(advectionHandlers, grid);

	// Initialize the grid for the advection
	advectionHandlers[0]->initializeAdvectionGrid(advectionHandlers, grid);

	// Pointer for the concentration vector at a specific grid point
	PetscScalar *concOffset = nullptr;

	// Degrees of freedom is the total number of clusters in the network
	// + the super clusters
	const int dof = network->getDOF();

	// Get the initial displacement vector
	auto initialDisplacementVector =
			displacementHandler->getInitialDisplacementVec();
	int vId = displacementHandler->getInitialDisplacementClusterIndex();

	// Get the initial interstitial vector
	auto initialInterstitialVector =
			displacementHandler->getInitialInterstitialVec();
	int iId = displacementHandler->getInitialInterstitialClusterIndex();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the single vacancy ID
	auto singleVacancyCluster = network->get(xolotlCore::vType, 1);
	int vacancyIndex = -1;
	if (singleVacancyCluster)
		vacancyIndex = singleVacancyCluster->getId() - 1;

<<<<<<< HEAD
	// Loop on all the grid points
	for (int i = xs; i < xs + xm; i++) {
=======
//	// Get the single interstitial ID
//	auto singleInterstitialCluster = network->get(xolotlCore::iType, 1);
//	int interstitialIndex = -1;
//	if (singleInterstitialCluster)
//		interstitialIndex = singleInterstitialCluster->getId() - 1;
//
//	double vNorm = 0.0, iNorm = 0.0;
//	double p0V = 1.600418928759454, p1V = 2.248882336566957,
//			p0I = 1.664901915671198, p1I = 2.463576251524528;
//	for (int i = surfacePosition + 1; i < xSize - 1; i++) {
//		// Get the x position
//		double x = grid[i] - grid[surfacePosition];
//
//		// Add the the value of the function times the step size
//		vNorm += p0V/p1V * pow(x/p1V,(p0V-1.0)) * exp(-pow(x/p1V,p0V)) * (grid[i] - grid[i-1]);
//		iNorm += p0I/p1I * pow(x/p1I,(p0I-1.0)) * exp(-pow(x/p1I,p0I)) * (grid[i] - grid[i-1]);
//	}

	// Loop on all the grid points
	for (PetscInt i = xs; i < xs + xm; i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		concOffset = concentrations[i];

		// Loop on all the clusters to initialize at 0.0
		for (int n = 0; n < dof; n++) {
			concOffset[n] = 0.0;
		}

<<<<<<< HEAD
		// Initialize the vacancy concentration
		if (i > 0 && i < Mx - 1 && vacancyIndex > 0) {
			concOffset[vacancyIndex] = initialVConc;
		}
=======
//		// Initialize the displacement concentration
//		if (i > surfacePosition && i < xSize - 1 && singleVacancyCluster && singleInterstitialCluster) {
//			double x = grid[i] - grid[surfacePosition];
//			double value=1./3. * 3.2630862758 * 10.0 * 8.0e-3 * p0V/p1V * pow(x/p1V,(p0V-1.0)) * exp(-pow(x/p1V,p0V)) / vNorm;
//			concOffset[vacancyIndex] = value;
//
//			value=1./3. * 331985259.408 * 1.0e-7 * 8.0e-3 * p0I/p1I * pow(x/p1I,(p0I-1.0)) * exp(-pow(x/p1I,p0I)) / iNorm;
//			concOffset[interstitialIndex] = value;
//		}

		// Initialize the vacancy concentration
		if (i > surfacePosition && i < xSize - 1 && singleVacancyCluster
				&& !hasConcentrations) {
			concOffset[vacancyIndex] = initialVConc;
		}

		// Add the initial displacement
		if (i > surfacePosition && i < xSize - 1) {
			concOffset[vId] = initialDisplacementVector[i - surfacePosition];
			concOffset[iId] = initialInterstitialVector[i - surfacePosition];
		}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// If the concentration must be set from the HDF5 file
	if (hasConcentrations) {
		// Loop on the full grid
<<<<<<< HEAD
		for (int i = 0; i < Mx; i++) {
=======
		for (int i = 0; i < xSize; i++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// Read the concentrations from the HDF5 file
			auto concVector = xolotlCore::HDF5Utils::readGridPoint(networkName,
					tempTimeStep, i);

			// Change the concentration only if we are on the locally owned part of the grid
			if (i >= xs && i < xs + xm) {
				concOffset = concentrations[i];
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

	/*
	 Restore vectors
	 */
	ierr = DMDAVecRestoreArrayDOF(da, C, &concentrations);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: DMDAVecRestoreArrayDOF failed.");
=======
	checkPetscError(ierr, "PetscSolver1DHandler::initializeConcentration: "
			"DMDAVecRestoreArrayDOF failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

void PetscSolver1DHandler::updateConcentration(TS &ts, Vec &localC, Vec &F,
		PetscReal ftime) {
	PetscErrorCode ierr;

	// Get the local data vector from PETSc
	DM da;
	ierr = TSGetDM(ts, &da);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMDAGetInfo failed.");

	// Pointers to the PETSc arrays that start at the beginning (xs) of the
	// local array!
	PetscScalar **concs, **updatedConcs;
	// Get pointers to vector data
	ierr = DMDAVecGetArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMDAVecGetArrayDOF (localC) failed.");
	ierr = DMDAVecGetArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMDAVecGetArrayDOF (F) failed.");
=======
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	int xSize = grid.size();

	// Pointers to the PETSc arrays that start at the beginning (xs) of the
	// local array!
	PetscScalar **concs = nullptr, **updatedConcs = nullptr;
	// Get pointers to vector data
	ierr = DMDAVecGetArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"DMDAVecGetArrayDOFRead (localC) failed.");
	ierr = DMDAVecGetArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"DMDAVecGetArrayDOF (F) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get local grid boundaries
	PetscInt xs, xm;
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMDAGetCorners failed.");
=======
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"DMDAGetCorners failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// The following pointers are set to the first position in the conc or
	// updatedConc arrays that correspond to the beginning of the data for the
	// current grid point. They are accessed just like regular arrays.
<<<<<<< HEAD
	PetscScalar *concOffset, *updatedConcOffset;

	// Set some step size variable
	double sx = 1.0 / (hX * hX);

	// Get the incident flux vector
	auto incidentFluxVector = fluxHandler->getIncidentFluxVec(ftime);

	// Declarations for variables used in the loop
	double flux;
	int fluxIndex = fluxHandler->getIncidentFluxClusterIndex(), reactantIndex;
	xolotlCore::PSICluster *cluster = NULL;
	double **concVector = new double*[3];
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->size();

	// Loop over grid points computing ODE terms for each grid point
	for (int xi = xs; xi < xs + xm; xi++) {
=======
	PetscScalar *concOffset = nullptr, *updatedConcOffset = nullptr;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->getDOF();

	// Compute the total concentration of atoms contained in bubbles
	double atomConc = 0.0;

	// Loop over grid points to get the atom concentration
	// near the surface
	for (int xi = xs; xi < xs + xm; xi++) {
		// Boundary conditions
		if (xi <= surfacePosition || xi == xSize - 1)
			continue;

		// We are only interested in the helium near the surface
		if (grid[xi] - grid[surfacePosition] > 2.0)
			continue;

		// Get the concentrations at this grid point
		concOffset = concs[xi];
		// Copy data into the PSIClusterReactionNetwork
		network->updateConcentrationsFromArray(concOffset);

		// Sum the total atom concentration
		atomConc += network->getTotalTrappedAtomConcentration()
				* (grid[xi] - grid[xi - 1]);
	}

	// Share the concentration with all the processes
	double totalAtomConc = 0.0;
	MPI_Allreduce(&atomConc, &totalAtomConc, 1, MPI_DOUBLE, MPI_SUM,
			MPI_COMM_WORLD);

	// Set the disappearing rate in the modified TM handler
	mutationHandler->updateDisappearingRate(totalAtomConc);

	// Declarations for variables used in the loop
	double **concVector = new double*[3];
	std::vector<double> gridPosition = { 0.0, 0.0, 0.0 };

	// Loop over grid points computing ODE terms for each grid point
	for (PetscInt xi = xs; xi < xs + xm; xi++) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Compute the old and new array offsets
		concOffset = concs[xi];
		updatedConcOffset = updatedConcs[xi];

<<<<<<< HEAD
		// Fill the concVector with the pointer to the middle, left, and right grid points
		concVector[0] = concOffset; // middle
		concVector[1] = concs[xi - 1]; // left
		concVector[2] = concs[xi + 1]; // right

		// Boundary conditions
		if (xi == 0 || xi == Mx - 1) {
=======
		// Boundary conditions
		// Everything to the left of the surface is empty
		if (xi <= surfacePosition || xi == xSize - 1) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			for (int i = 0; i < dof; i++) {
				updatedConcOffset[i] = 1.0 * concOffset[i];
			}

			continue;
		}

		// Set the grid position
<<<<<<< HEAD
		gridPosition[0] = xi * hX;
=======
		gridPosition[0] = grid[xi];

		// Fill the concVector with the pointer to the middle, left, and right grid points
		concVector[0] = concOffset; // middle
		concVector[1] = concs[xi - 1]; // left
		concVector[2] = concs[xi + 1]; // right
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
			// Update the modified trap-mutation rate
			// that depends on the network reaction rates
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
				updatedConcOffset, sx);

		// ---- Compute advection over the locally owned part of the grid -----
		advectionHandler->computeAdvection(network, hX, gridPosition,
				concVector, updatedConcOffset);

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
		fluxHandler->computeIncidentFlux(ftime, updatedConcOffset, xi,
				surfacePosition);

		// ---- Compute diffusion over the locally owned part of the grid -----
		diffusionHandler->computeDiffusion(network, concVector,
				updatedConcOffset, grid[xi] - grid[xi - 1],
				grid[xi + 1] - grid[xi], xi);

		// ---- Compute advection over the locally owned part of the grid -----
		for (int i = 0; i < advectionHandlers.size(); i++) {
			advectionHandlers[i]->computeAdvection(network, gridPosition,
					concVector, updatedConcOffset, grid[xi] - grid[xi - 1],
					grid[xi + 1] - grid[xi], xi);
		}

		// ----- Compute the modified trap-mutation over the locally owned part of the grid -----
		mutationHandler->computeTrapMutation(network, concOffset,
				updatedConcOffset, xi);

		// ----- Compute the reaction fluxes over the locally owned part of the grid -----
		network->computeAllFluxes(updatedConcOffset);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	/*
	 Restore vectors
	 */
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMDAVecRestoreArrayDOF (localC) failed.");
	ierr = DMDAVecRestoreArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMDAVecRestoreArrayDOF (F) failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: DMRestoreLocalVector failed.");
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"DMDAVecRestoreArrayDOFRead (localC) failed.");
	ierr = DMDAVecRestoreArrayDOF(da, F, &updatedConcs);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"DMDAVecRestoreArrayDOF (F) failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver1DHandler::updateConcentration: "
			"DMRestoreLocalVector failed.");

	// Clear memory
	delete[] concVector;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

<<<<<<< HEAD
void PetscSolver1DHandler::computeOffDiagonalJacobian(TS &ts, Vec &localC, Mat &J) const {
=======
void PetscSolver1DHandler::computeOffDiagonalJacobian(TS &ts, Vec &localC,
		Mat &J, PetscReal ftime) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;

	// Get the distributed array
	DM da;
	ierr = TSGetDM(ts, &da);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: DMDAGetInfo failed.");

	// Setup some step size variables
	double sx = 1.0 / (hX * hX);

	// Get pointers to vector data
	PetscScalar **concs;
	ierr = DMDAVecGetArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: DMDAVecGetArrayDOF failed.");
=======
	checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: "
			"TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	int xSize = grid.size();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get local grid boundaries
	PetscInt xs, xm;
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: DMDAGetCorners failed.");

	// Pointer to the concentrations at a given grid point
	PetscScalar *concOffset;
=======
	checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: "
			"DMDAGetCorners failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the total number of diffusing clusters
	const int nDiff = diffusionHandler->getNumberOfDiffusing();

	// Get the total number of advecting clusters
<<<<<<< HEAD
	const int nAdvec = advectionHandler->getNumberOfAdvecting();

	// Arguments for MatSetValuesStencil called below
	MatStencil row, cols[3];
	PetscScalar vals[3 * nDiff];
	int indices[nDiff];
=======
	int nAdvec = 0;
	for (int l = 0; l < advectionHandlers.size(); l++) {
		int n = advectionHandlers[l]->getNumberOfAdvecting();
		if (n > nAdvec)
			nAdvec = n;
	}

	// Arguments for MatSetValuesStencil called below
	MatStencil row, cols[3];
	PetscScalar diffVals[3 * nDiff];
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
	for (int xi = xs; xi < xs + xm; xi++) {
		// Boundary conditions
		if (xi == 0 || xi == Mx - 1) continue;

		// Set the grid position
		gridPosition[0] = xi * hX;

		// Copy data into the PSIClusterReactionNetwork so that it can
		// compute the new concentrations.
		concOffset = concs[xi];
		network->updateConcentrationsFromArray(concOffset);

		// Get the partial derivatives for the diffusion
		diffusionHandler->computePartialsForDiffusion(network, vals, indices, sx);
=======
	for (PetscInt xi = xs; xi < xs + xm; xi++) {
		// Boundary conditions
		// Everything to the left of the surface is empty
		if (xi <= surfacePosition || xi == xSize - 1)
			continue;

		// Set the grid position
		gridPosition[0] = grid[xi];

		// Get the temperature from the temperature handler
		auto temperature = temperatureHandler->getTemperature(gridPosition,
				ftime);

		// Update the network if the temperature changed
		if (!xolotlCore::equal(temperature, lastTemperature)) {
			network->setTemperature(temperature);
			// Update the modified trap-mutation rate
			// that depends on the network reaction rates
			mutationHandler->updateTrapMutationRate(network);
			lastTemperature = temperature;
		}

		// Get the partial derivatives for the diffusion
		diffusionHandler->computePartialsForDiffusion(network, diffVals,
				diffIndices, grid[xi] - grid[xi - 1], grid[xi + 1] - grid[xi],
				xi);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Loop on the number of diffusion cluster to set the values in the Jacobian
		for (int i = 0; i < nDiff; i++) {
			// Set grid coordinate and component number for the row
			row.i = xi;
<<<<<<< HEAD
			row.c = indices[i];
=======
			row.c = diffIndices[i];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

			// Set grid coordinates and component numbers for the columns
			// corresponding to the middle, left, and right grid points
			cols[0].i = xi; // middle
<<<<<<< HEAD
			cols[0].c = indices[i];
			cols[1].i = xi - 1; // left
			cols[1].c = indices[i];
			cols[2].i = xi + 1; // right
			cols[2].c = indices[i];

			ierr = MatSetValuesStencil(J, 1, &row, 3, cols, vals + (3 * i), ADD_VALUES);
			checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: MatSetValuesStencil (diffusion) failed.");
		}

		// Get the partial derivatives for the advection
		advectionHandler->computePartialsForAdvection(network, hX, vals,
				indices, gridPosition);

		// Loop on the number of advecting cluster to set the values in the Jacobian
		for (int i = 0; i < nAdvec; i++) {
			// Set grid coordinate and component number for the row
			row.i = xi;
			row.c = indices[i];

			// Set grid coordinates and component numbers for the columns
			// corresponding to the middle and right grid points
			cols[0].i = xi; // middle
			cols[0].c = indices[i];
			cols[1].i = xi + 1; // right
			cols[1].c = indices[i];

			// Update the matrix
			ierr = MatSetValuesStencil(J, 1, &row, 2, cols, vals + (2 * i), ADD_VALUES);
			checkPetscError(ierr, "PetscSolver1DHandler::computeOffDiagonalJacobian: MatSetValuesStencil (advection) failed.");
=======
			cols[0].c = diffIndices[i];
			cols[1].i = xi - 1; // left
			cols[1].c = diffIndices[i];
			cols[2].i = xi + 1; // right
			cols[2].c = diffIndices[i];

			ierr = MatSetValuesStencil(J, 1, &row, 3, cols, diffVals + (3 * i),
					ADD_VALUES);
			checkPetscError(ierr,
					"PetscSolver1DHandler::computeOffDiagonalJacobian: "
							"MatSetValuesStencil (diffusion) failed.");
		}

		// Get the partial derivatives for the advection
		for (int l = 0; l < advectionHandlers.size(); l++) {
			advectionHandlers[l]->computePartialsForAdvection(network,
					advecVals, advecIndices, gridPosition,
					grid[xi] - grid[xi - 1], grid[xi + 1] - grid[xi], xi);

			// Get the stencil indices to know where to put the partial derivatives in the Jacobian
			auto advecStencil = advectionHandlers[l]->getStencilForAdvection(
					gridPosition);

			// Get the number of advecting clusters
			nAdvec = advectionHandlers[l]->getNumberOfAdvecting();

			// Loop on the number of advecting cluster to set the values in the Jacobian
			for (int i = 0; i < nAdvec; i++) {
				// Set grid coordinate and component number for the row
				row.i = xi;
				row.c = advecIndices[i];

				// If we are on the sink, the partial derivatives are not the same
				// Both sides are giving their concentrations to the center
				if (advectionHandlers[l]->isPointOnSink(gridPosition)) {
					cols[0].i = xi - advecStencil[0]; // left?
					cols[0].c = advecIndices[i];
					cols[1].i = xi + advecStencil[0]; // right?
					cols[1].c = advecIndices[i];
				} else {
					// Set grid coordinates and component numbers for the columns
					// corresponding to the middle and other grid points
					cols[0].i = xi; // middle
					cols[0].c = advecIndices[i];
					cols[1].i = xi + advecStencil[0]; // left or right
					cols[1].c = advecIndices[i];
				}

				// Update the matrix
				ierr = MatSetValuesStencil(J, 1, &row, 2, cols,
						advecVals + (2 * i), ADD_VALUES);
				checkPetscError(ierr,
						"PetscSolver1DHandler::computeOffDiagonalJacobian: "
								"MatSetValuesStencil (advection) failed.");
			}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		}
	}

	return;
}

<<<<<<< HEAD
void PetscSolver1DHandler::computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J) {
=======
void PetscSolver1DHandler::computeDiagonalJacobian(TS &ts, Vec &localC, Mat &J,
		PetscReal ftime) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;

	// Get the distributed array
	DM da;
	ierr = TSGetDM(ts, &da);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	PetscInt Mx;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: DMDAGetInfo failed.");

	// Get pointers to vector data
	PetscScalar **concs;
	ierr = DMDAVecGetArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: DMDAVecGetArrayDOF failed.");
=======
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: "
			"TSGetDM failed.");

	// Get the total size of the grid for the boundary conditions
	int xSize = grid.size();

	// Get pointers to vector data
	PetscScalar **concs = nullptr;
	ierr = DMDAVecGetArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: "
			"DMDAVecGetArrayDOFRead failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get local grid boundaries
	PetscInt xs, xm;
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
<<<<<<< HEAD
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: DMDAGetCorners failed.");

	// The degree of freedom is the size of the network
	const int dof = network->size();

	// Pointer to the concentrations at a given grid point
	PetscScalar *concOffset;
=======
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: "
			"DMDAGetCorners failed.");

	// Pointer to the concentrations at a given grid point
	PetscScalar *concOffset = nullptr;

	// Degrees of freedom is the total number of clusters in the network
	const int dof = network->getDOF();

	// Get all the He clusters in the network
	auto heliums = network->getAll(xolotlCore::heType);

	// Compute the total concentration of atoms contained in bubbles
	double atomConc = 0.0;

	// Loop over grid points to get the atom concentration
	// near the surface
	for (int xi = xs; xi < xs + xm; xi++) {
		// Boundary conditions
		if (xi <= surfacePosition || xi == xSize - 1)
			continue;

		// We are only interested in the helium near the surface
		if (grid[xi] - grid[surfacePosition] > 2.0)
			continue;

		// Get the concentrations at this grid point
		concOffset = concs[xi];
		// Copy data into the PSIClusterReactionNetwork
		network->updateConcentrationsFromArray(concOffset);

		// Sum the total atom concentration
		atomConc += network->getTotalTrappedAtomConcentration()
				* (grid[xi] - grid[xi - 1]);
	}

	// Share the concentration with all the processes
	double totalAtomConc = 0.0;
	MPI_Allreduce(&atomConc, &totalAtomConc, 1, MPI_DOUBLE, MPI_SUM,
			MPI_COMM_WORLD);

	// Set the disappearing rate in the modified TM handler
	mutationHandler->updateDisappearingRate(totalAtomConc);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Arguments for MatSetValuesStencil called below
	MatStencil rowId;
	MatStencil colIds[dof];
	int pdColIdsVectorSize = 0;
<<<<<<< HEAD

	// Declarations for variables used in the loop
	int reactantIndex;

	// Loop over the grid points
	for (int xi = xs; xi < xs + xm; xi++) {
		// Boundary conditions
		if (xi == 0 || xi == Mx - 1) continue;

		// Copy data into the PSIClusterReactionNetwork so that it can
=======
	PetscInt reactionSize[dof];

	// Store the total number of He clusters in the network for the
	// modified trap-mutation
	int nHelium = heliums.size();

	// Declarations for variables used in the loop
	std::vector<double> gridPosition;
	gridPosition.push_back(0.0);
	gridPosition.push_back(0.0);
	gridPosition.push_back(0.0);

	// Loop over the grid points
	for (PetscInt xi = xs; xi < xs + xm; xi++) {
		// Boundary conditions
		// Everything to the left of the surface is empty
		if (xi <= surfacePosition || xi == xSize - 1)
			continue;

		// Set the grid position
		gridPosition[0] = grid[xi];

		// Get the temperature from the temperature handler
		auto temperature = temperatureHandler->getTemperature(gridPosition,
				ftime);

		// Update the network if the temperature changed
		if (!xolotlCore::equal(temperature, lastTemperature)) {
			network->setTemperature(temperature);
			// Update the modified trap-mutation rate
			// that depends on the network reaction rates
			mutationHandler->updateTrapMutationRate(network);
			lastTemperature = temperature;
		}

		// Copy data into the ReactionNetwork so that it can
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// compute the new concentrations.
		concOffset = concs[xi];
		network->updateConcentrationsFromArray(concOffset);

<<<<<<< HEAD
		// Update the column in the Jacobian that represents each reactant
		for (int i = 0; i < dof; i++) {
			auto reactant = allReactants->at(i);
			// Get the reactant index
			reactantIndex = reactant->getId() - 1;

			// Set grid coordinate and component number for the row
			rowId.i = xi;
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
			rowId.c = i;

			// Number of partial derivatives
			pdColIdsVectorSize = reactionSize[i];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// Loop over the list of column ids
			for (int j = 0; j < pdColIdsVectorSize; j++) {
				// Set grid coordinate and component number for a column in the list
				colIds[j].i = xi;
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
			ierr = MatSetValuesStencil(J, 1, &rowId, pdColIdsVectorSize,
					colIds, reactingPartialsForCluster.data(), ADD_VALUES);
			checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: MatSetValuesStencil failed.");
=======
				colIds[j].c = reactionIndices[i * dof + j];
				// Get the partial derivative from the array of all of the partials
				reactingPartialsForCluster[j] = reactionVals[i * dof + j];
			}
			// Update the matrix
			ierr = MatSetValuesStencil(J, 1, &rowId, pdColIdsVectorSize, colIds,
					reactingPartialsForCluster.data(), ADD_VALUES);
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
		int nMutating = mutationHandler->computePartialsForTrapMutation(network,
				mutationVals, mutationIndices, xi);

		// Loop on the number of helium undergoing trap-mutation to set the values
		// in the Jacobian
		for (int i = 0; i < nMutating; i++) {
			// Set grid coordinate and component number for the row and column
			// corresponding to the helium cluster
			row.i = xi;
			row.c = mutationIndices[3 * i];
			col.i = xi;
			col.c = mutationIndices[3 * i];

			ierr = MatSetValuesStencil(J, 1, &row, 1, &col,
					mutationVals + (3 * i), ADD_VALUES);
			checkPetscError(ierr,
					"PetscSolver1DHandler::computeDiagonalJacobian: "
							"MatSetValuesStencil (He trap-mutation) failed.");

			// Set component number for the row
			// corresponding to the HeV cluster created through trap-mutation
			row.c = mutationIndices[(3 * i) + 1];

			ierr = MatSetValuesStencil(J, 1, &row, 1, &col,
					mutationVals + (3 * i) + 1, ADD_VALUES);
			checkPetscError(ierr,
					"PetscSolver1DHandler::computeDiagonalJacobian: "
							"MatSetValuesStencil (HeV trap-mutation) failed.");

			// Set component number for the row
			// corresponding to the interstitial created through trap-mutation
			row.c = mutationIndices[(3 * i) + 2];

			ierr = MatSetValuesStencil(J, 1, &row, 1, &col,
					mutationVals + (3 * i) + 2, ADD_VALUES);
			checkPetscError(ierr,
					"PetscSolver1DHandler::computeDiagonalJacobian: "
							"MatSetValuesStencil (I trap-mutation) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		}
	}

	/*
	 Restore vectors
	 */
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOF(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: DMDAVecRestoreArrayDOF failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: DMRestoreLocalVector failed.");
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, localC, &concs);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: "
			"DMDAVecRestoreArrayDOFRead failed.");
	ierr = DMRestoreLocalVector(da, &localC);
	checkPetscError(ierr, "PetscSolver1DHandler::computeDiagonalJacobian: "
			"DMRestoreLocalVector failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

} /* end namespace xolotlSolver */
