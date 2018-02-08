// Includes
#include "PetscSolver.h"
#include <xolotlPerf.h>
#include <VizHandlerRegistryFactory.h>
#include <PlotType.h>
#include <CvsXDataProvider.h>
#include <CvsXYDataProvider.h>
#include <LabelProvider.h>
<<<<<<< HEAD
=======
#include <Constants.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
#include <petscts.h>
#include <petscsys.h>
#include <sstream>
#include <fstream>
#include <iostream>
<<<<<<< HEAD
#include <vector>
#include <memory>
#include <HDF5Utils.h>
=======
#include <iomanip>
#include <vector>
#include <memory>
#include <HDF5Utils.h>
#include <NESuperCluster.h>
#include <PSISuperCluster.h>
#include <NEClusterReactionNetwork.h>
#include <PSIClusterReactionNetwork.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

namespace xolotlSolver {

// Declaration of the functions defined in Monitor.cpp
extern PetscErrorCode monitorTime(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx);
<<<<<<< HEAD
extern PetscErrorCode computeHeliumFluence(TS ts, PetscInt timestep, PetscReal time,
=======
extern PetscErrorCode computeFluence(TS ts, PetscInt timestep, PetscReal time,
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		Vec solution, void *ictx);
extern PetscErrorCode monitorPerf(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx);

// Declaration of the variables defined in Monitor.cpp
extern std::shared_ptr<xolotlViz::IPlot> perfPlot;
extern double previousTime;

//! The pointer to the plot used in monitorScatter1D.
std::shared_ptr<xolotlViz::IPlot> scatterPlot1D;
//! The pointer to the series plot used in monitorSeries1D.
std::shared_ptr<xolotlViz::IPlot> seriesPlot1D;
//! The pointer to the 2D plot used in MonitorSurface.
std::shared_ptr<xolotlViz::IPlot> surfacePlot1D;
//! The variable to store the interstitial flux at the previous time step.
double previousIFlux1D = 0.0;
<<<<<<< HEAD
//! How often HDF5 file is written
PetscInt hdf5Stride1D = 0;
//! HDF5 output file name
std::string hdf5OutputName1D = "xolotlStop.h5";
// Declare the vector that will store the Id of the helium clusters
std::vector<int> heIndices1D;
// Declare the vector that will store the weight of the helium clusters
// (their He composition)
std::vector<int> heWeights1D;
=======
//! The variable to store the total number of interstitials going through the surface.
double nInterstitial1D = 0.0;
//! The variable to store the sputtering yield at the surface.
double sputteringYield1D = 0.0;
//! How often HDF5 file is written
PetscReal hdf5Stride1D = 0.0;
//! Previous time for HDF5
PetscInt hdf5Previous1D = 0;
//! HDF5 output file name
std::string hdf5OutputName1D = "xolotlStop.h5";
// Declare the vector that will store the Id of the helium clusters
std::vector<int> indices1D;
// Declare the vector that will store the weight of the helium clusters
// (their He composition)
std::vector<int> weights1D;
// Declare the vector that will store the radii of bubbles
std::vector<double> radii1D;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
// Variable to indicate whether or not the fact that the concentration of the biggest
// cluster in the network is higher than 1.0e-16 should be printed.
// Becomes false once it is printed.
bool printMaxClusterConc1D = true;

#undef __FUNCT__
<<<<<<< HEAD
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "startStop1D")
/**
 * This is a monitoring method that will save an hdf5 file at each time step.
 * HDF5 is handling the parallel part, so no call to MPI here.
 */
PetscErrorCode startStop1D(TS ts, PetscInt timestep, PetscReal time, Vec solution,
		void *ictx) {
=======
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeBoundaryFlux1D")
/**
 * This is a monitoring method that will compute the total helium fluence
 */
PetscErrorCode computeBoundaryFlux1D(TS ts, PetscInt, PetscReal time,
		Vec solution, void *) {
	PetscErrorCode ierr;
	PetscInt xs, xm;

	PetscFunctionBeginUser;

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the flux handler that will be used to compute fluxes.
	auto fluxHandler = solverHandler->getFluxHandler();
	auto network = solverHandler->getNetwork();
	auto heliums = network->getAll("He");
	auto cluster = (PSICluster *) heliums.at(0);
	auto temp = network->getTemperature();
	int id = cluster->getId() - 1;
	double difCoef = cluster->getDiffusionCoefficient();
	auto allHeVReactants = network->getAll(heVType);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Setup step size variable
	auto grid = solverHandler->getXGrid();
	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the array of concentration
	PetscReal **solutionArray;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Store the concentration over the grid
	double he1Concentration = 0;
	double v1Concentration = 0;
	double he1V1Concentration = 0;
	double he2V1Concentration = 0;
	double he3V1Concentration = 0;
	double he4V1Concentration = 0;
	double i1Concentration = 0;

	auto he1V1Cluster = (PSICluster *) allHeVReactants[0];
	auto he2V1Cluster = (PSICluster *) allHeVReactants[1];
	auto he3V1Cluster = (PSICluster *) allHeVReactants[2];
	auto he4V1Cluster = (PSICluster *) allHeVReactants[3];

	auto he1Cluster = (PSICluster *) network->get(heType, 1);
	auto v1Cluster = (PSICluster *) network->get(vType, 1);
	auto i1Cluster = (PSICluster *) network->get(iType, 1);

	auto he1Index = he1Cluster->getId() - 1;
	auto he1Name = he1Cluster->getName();

	auto v1Index = v1Cluster->getId() - 1;
	auto v1Name = v1Cluster->getName();
	auto i1Index = i1Cluster->getId() - 1;
	auto i1Name = i1Cluster->getName();

	auto he1V1Index = he1V1Cluster->getId() - 1;
	auto he2V1Index = he2V1Cluster->getId() - 1;
	auto he3V1Index = he3V1Cluster->getId() - 1;
	auto he4V1Index = he4V1Cluster->getId() - 1;

	auto he1V1Name = he1V1Cluster->getName();
	auto he2V1Name = he2V1Cluster->getName();
	auto he3V1Name = he3V1Cluster->getName();
	auto he4V1Name = he4V1Cluster->getName();

	// Declare the necessary coefficients for He flux calculation at the boundary
	double fluxBoundary = 0.0;
	double concentration_1 = 0.0;

	// Declare the pointer for the concentrations at a specific grid point
	PetscReal *gridPointSolution;

	// Loop on the grid
	for (PetscInt xi = xs; xi < xs + xm; xi++) {

		// Boundary conditions
		if (xi <= surfacePos || xi == grid.size() - 1)
			continue;

		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];
		double hx = grid[xi] - grid[xi - 1];


		he1Concentration += gridPointSolution[he1Index] * hx;
		v1Concentration += gridPointSolution[v1Index] * hx;
		i1Concentration += gridPointSolution[i1Index] * hx;
		he1V1Concentration += gridPointSolution[he1V1Index] * hx;
		he2V1Concentration += gridPointSolution[he2V1Index] * hx;
		he3V1Concentration += gridPointSolution[he3V1Index] * hx;
		he4V1Concentration += gridPointSolution[he4V1Index] * hx;

		if (xi == surfacePos + 1)
			concentration_1 = gridPointSolution[he1Index];
	}

	// Get the current process ID
	int procId;
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	// Sum all the concentrations through MPI reduce
	double totalHe1Concentration = 0.0;
	double totalV1Concentration = 0.0;
	double totalI1Concentration = 0.0;
	double totalHe1V1Concentration = 0.0;
	double totalHe2V1Concentration = 0.0;
	double totalHe3V1Concentration = 0.0;
	double totalHe4V1Concentration = 0.0;

	MPI_Reduce(&he1Concentration, &totalHe1Concentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&v1Concentration, &totalV1Concentration, 1, MPI_DOUBLE, MPI_SUM,
			0, MPI_COMM_WORLD);
	MPI_Reduce(&i1Concentration, &totalI1Concentration, 1, MPI_DOUBLE, MPI_SUM,
			0, MPI_COMM_WORLD);
	MPI_Reduce(&he1V1Concentration, &totalHe1V1Concentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&he2V1Concentration, &totalHe2V1Concentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&he3V1Concentration, &totalHe3V1Concentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&he4V1Concentration, &totalHe4V1Concentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);

	// Master process
	if (procId == 0) {
		// Get the fluence
		double heliumFluence = fluxHandler->getFluence();

		double hx = grid[surfacePos + 1] - grid[surfacePos];

		// Helium flux calculation at the boundary
		fluxBoundary = difCoef * concentration_1 / hx;

		// Print the result
		std::cout << "\nTemperature: " << temp << std::endl;
		std::cout << "\nTime: " << time << std::endl;
		std::cout << "Helium fluence = " << heliumFluence << "\n" << std::endl;
		std::cout << "Cluster concentrations: " << std::endl;
		std::cout << he1Name << "=" << totalHe1Concentration << std::endl;
		std::cout << v1Name << "=" << totalV1Concentration << std::endl;
		std::cout << he1V1Name << "=" << totalHe1V1Concentration << std::endl;
		std::cout << he2V1Name << "=" << totalHe2V1Concentration << std::endl;
		std::cout << he3V1Name << "=" << totalHe3V1Concentration << std::endl;
		std::cout << he4V1Name << "=" << totalHe4V1Concentration << std::endl;
		std::cout << i1Name << "=" << totalI1Concentration << std::endl;

		// Uncomment to write the flux at the boundary and temperature in a file
		std::ofstream outputFile;
		outputFile.open("thds.txt", ios::app);
		outputFile << temp << " " << fluxBoundary << std::endl;
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "startStop1D")
/**
 * This is a monitoring method that update an hdf5 file at each time step.
 */
PetscErrorCode startStop1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declaration
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, Mx;

	PetscFunctionBeginUser;

	// Don't do anything if it is not on the stride
<<<<<<< HEAD
	if (timestep % hdf5Stride1D != 0)
		PetscFunctionReturn(0);

=======
	if ((int) (time / hdf5Stride1D) == hdf5Previous1D)
		PetscFunctionReturn(0);

	// Update the previous time
	hdf5Previous1D++;

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID (important when it is running in parallel)
	int procId;
<<<<<<< HEAD
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);
=======
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get the size of the total grid
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
<<<<<<< HEAD
	PETSC_IGNORE);CHKERRQ(ierr);
=======
	PETSC_IGNORE);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

<<<<<<< HEAD
	// Get the network
	auto network = solverHandler->getNetwork();

	// Network size
	const int networkSize = network->size();
=======
	// Get the network and dof
	auto network = solverHandler->getNetwork();
	const int dof = network->getDOF();

	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Open the already created HDF5 file
	xolotlCore::HDF5Utils::openFile(hdf5OutputName1D);

	// Get the current time step
	double currentTimeStep;
<<<<<<< HEAD
	ierr = TSGetTimeStep(ts, &currentTimeStep);CHKERRQ(ierr);

	// Add a concentration sub group
	xolotlCore::HDF5Utils::addConcentrationSubGroup(timestep, networkSize, time,
			currentTimeStep);

	// Loop on the full grid
	for (int i = 0; i < Mx; i++) {
=======
	ierr = TSGetTimeStep(ts, &currentTimeStep);
	CHKERRQ(ierr);

	// Add a concentration sub group
	xolotlCore::HDF5Utils::addConcentrationSubGroup(timestep, time,
			previousTime, currentTimeStep);

	// Write the surface positions and the associated interstitial quantities
	// in the concentration sub group
	xolotlCore::HDF5Utils::writeSurface1D(timestep, surfacePos, nInterstitial1D,
			previousIFlux1D);

	// Loop on the full grid
	for (PetscInt i = 0; i < Mx; i++) {
		// Wait for all the processes
		MPI_Barrier(PETSC_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Size of the concentration that will be stored
		int concSize = -1;
		// Vector for the concentrations
		std::vector<std::vector<double> > concVector;

		// If it is the locally owned part of the grid
		if (i >= xs && i < xs + xm) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[i];

			// Loop on the concentrations
			concVector.clear();
<<<<<<< HEAD
			for (int l = 0; l < networkSize; l++) {
				if (gridPointSolution[l] > 1.0e-16) {
=======
			for (int l = 0; l < dof; l++) {
				if (gridPointSolution[l] > 1.0e-16
						|| gridPointSolution[l] < -1.0e-16) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					// Create the concentration vector for this cluster
					std::vector<double> conc;
					conc.push_back((double) l);
					conc.push_back(gridPointSolution[l]);

					// Add it to the main vector
					concVector.push_back(conc);
				}
			}

			// Send the size of the vector to the other processes
			concSize = concVector.size();
			// Loop on all the processes
			for (int l = 0; l < worldSize; l++) {
				// Skip its own
				if (l == procId)
					continue;

				// Send the size
<<<<<<< HEAD
				MPI_Send(&concSize, 1, MPI_INT, l, 0, MPI_COMM_WORLD);
=======
				MPI_Send(&concSize, 1, MPI_INT, l, 0, PETSC_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			}
		}

		// Else: only receive the conc size
		else {
<<<<<<< HEAD
			MPI_Recv(&concSize, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
=======
			MPI_Recv(&concSize, 1, MPI_INT, MPI_ANY_SOURCE, 0, PETSC_COMM_WORLD,
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					MPI_STATUS_IGNORE);
		}

		// Skip the grid point if the size is 0
		if (concSize == 0)
			continue;

		// All processes must create the dataset
		xolotlCore::HDF5Utils::addConcentrationDataset(concSize, i);

		// If it is the locally owned part of the grid
		if (i >= xs && i < xs + xm) {
			// Fill the dataset
			xolotlCore::HDF5Utils::fillConcentrations(concVector, i);
		}
	}

	// Finalize the HDF5 file
	xolotlCore::HDF5Utils::closeFile();

	// Restore the solutionArray
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeHeliumRetention1D")
/**
<<<<<<< HEAD
 * This is a monitoring method that will compute the total helium fluence
 */
PetscErrorCode computeHeliumRetention1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
=======
 * This is a monitoring method that will compute the helium retention
 */
PetscErrorCode computeHeliumRetention1D(TS ts, PetscInt, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;
	PetscInt xs, xm;

	PetscFunctionBeginUser;

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

<<<<<<< HEAD
	// Get the flux handler that will be used to compute fluxes.
=======
	// Get the flux handler that will be used to know the fluence
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	auto fluxHandler = solverHandler->getFluxHandler();

	// Get the da from ts
	DM da;
<<<<<<< HEAD
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);

	// Setup step size variable
	double hx = solverHandler->getStepSizeX();

	// Get the array of concentration
	PetscReal **solutionArray;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Store the concentration over the grid
	double heConcentration = 0;
=======
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();
	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the network
	auto network = solverHandler->getNetwork();
	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);

	// Get the array of concentration
	PetscReal **solutionArray;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Store the concentration over the grid
	double heConcentration = 0.0, bubbleConcentration = 0.0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Declare the pointer for the concentrations at a specific grid point
	PetscReal *gridPointSolution;

	// Loop on the grid
<<<<<<< HEAD
	for (int xi = xs; xi < xs + xm; xi++) {
		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];

		// Loop on all the indices
		for (int i = 0; i < heIndices1D.size(); i++) {
			// Add the current concentration times the number of helium in the cluster
			// (from the weight vector)
			heConcentration += gridPointSolution[heIndices1D[i]] * heWeights1D[i] * hx;
=======
	for (PetscInt xi = xs; xi < xs + xm; xi++) {

		// Boundary conditions
		if (xi <= surfacePos || xi == grid.size() - 1)
			continue;

		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];

		// Update the concentration in the network
		network->updateConcentrationsFromArray(gridPointSolution);

		// Loop on all the indices
		for (unsigned int l = 0; l < indices1D.size(); l++) {
			// Add the current concentration times the number of helium in the cluster
			// (from the weight vector)
			heConcentration += gridPointSolution[indices1D[l]] * weights1D[l]
					* (grid[xi] - grid[xi - 1]);
			bubbleConcentration += gridPointSolution[indices1D[l]]
					* (grid[xi] - grid[xi - 1]);
		}

		// Loop on all the super clusters
		for (int l = 0; l < superClusters.size(); l++) {
			auto cluster = (xolotlCore::PSISuperCluster *) superClusters[l];
			heConcentration += cluster->getTotalHeliumConcentration()
					* (grid[xi] - grid[xi - 1]);
			bubbleConcentration += cluster->getTotalConcentration()
					* (grid[xi] - grid[xi - 1]);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		}
	}

	// Get the current process ID
	int procId;
<<<<<<< HEAD
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	// Sum all the concentrations through MPI reduce
	double totalHeConcentration = 0.0;
	MPI_Reduce(&heConcentration, &totalHeConcentration, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
=======
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Sum all the concentrations through MPI reduce
	double totalHeConcentration = 0.0;
	MPI_Reduce(&heConcentration, &totalHeConcentration, 1, MPI_DOUBLE, MPI_SUM,
			0, PETSC_COMM_WORLD);
	double totalBubbleConcentration = 0.0;
	MPI_Reduce(&bubbleConcentration, &totalBubbleConcentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Master process
	if (procId == 0) {
		// Get the fluence
		double heliumFluence = fluxHandler->getFluence();

		// Print the result
		std::cout << "\nTime: " << time << std::endl;
		std::cout << "Helium retention = "
				<< 100.0 * (totalHeConcentration / heliumFluence) << " %"
				<< std::endl;
<<<<<<< HEAD
		std::cout << "Helium concentration = " << totalHeConcentration << std::endl;
		std::cout << "Helium fluence = " << heliumFluence << "\n" << std::endl;

//		// Uncomment to write the retention and the fluence in a file
//		std::ofstream outputFile;
//		outputFile.open("retentionOut.txt", ios::app);
//		outputFile << heliumFluence << " "
//				<< 100.0 * (totalHeConcentration / heliumFluence) << std::endl;
//		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);
=======
		std::cout << "Helium concentration = " << totalHeConcentration
				<< std::endl;
		std::cout << "Helium fluence = " << heliumFluence << "\n" << std::endl;

		// Uncomment to write the retention and the fluence in a file
		std::ofstream outputFile;
		outputFile.open("retentionOut.txt", ios::app);
		outputFile << heliumFluence << " "
				<< 100.0 * (totalHeConcentration / heliumFluence) << " "
				<< totalHeConcentration << " "
				<< totalHeConcentration / totalBubbleConcentration << std::endl;
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeXenonRetention1D")
/**
 * This is a monitoring method that will compute the xenon retention
 */
PetscErrorCode computeXenonRetention1D(TS ts, PetscInt, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
	PetscErrorCode ierr;
	PetscInt xs, xm;

	PetscFunctionBeginUser;

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the flux handler that will be used to get the fluence
	auto fluxHandler = solverHandler->getFluxHandler();

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();
	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the network
	auto network = solverHandler->getNetwork();
	// Get all the super clusters
	auto superClusters = network->getAll(NESuperType);

	// Get the array of concentration
	PetscReal **solutionArray;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Store the concentration and other values over the grid
	double xeConcentration = 0.0, bubbleConcentration = 0.0, radii = 0.0;

	// Declare the pointer for the concentrations at a specific grid point
	PetscReal *gridPointSolution;

	// Loop on the grid
	for (PetscInt xi = xs; xi < xs + xm; xi++) {

		// Boundary conditions
		if (xi <= surfacePos || xi == grid.size() - 1)
			continue;

		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];

		// Update the concentration in the network
		network->updateConcentrationsFromArray(gridPointSolution);

		// Loop on all the indices
		for (unsigned int i = 0; i < indices1D.size(); i++) {
			// Add the current concentration times the number of xenon in the cluster
			// (from the weight vector)
			xeConcentration += gridPointSolution[indices1D[i]] * weights1D[i]
					* (grid[xi] - grid[xi - 1]);
			bubbleConcentration += gridPointSolution[indices1D[i]]
					* (grid[xi] - grid[xi - 1]);
			radii += gridPointSolution[indices1D[i]] * radii1D[i]
					* (grid[xi] - grid[xi - 1]);
		}

		// Loop on all the super clusters
		for (int i = 0; i < superClusters.size(); i++) {
			auto cluster = (xolotlCore::NESuperCluster *) superClusters[i];
			xeConcentration += cluster->getTotalXenonConcentration()
					* (grid[xi] - grid[xi - 1]);
			bubbleConcentration += cluster->getTotalConcentration()
					* (grid[xi] - grid[xi - 1]);
			radii += cluster->getTotalConcentration()
					* cluster->getReactionRadius() * (grid[xi] - grid[xi - 1]);
		}
	}

	// Get the current process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Sum all the concentrations through MPI reduce
	double totalXeConcentration = 0.0;
	MPI_Reduce(&xeConcentration, &totalXeConcentration, 1, MPI_DOUBLE, MPI_SUM,
			0, PETSC_COMM_WORLD);
	double totalBubbleConcentration = 0.0;
	MPI_Reduce(&bubbleConcentration, &totalBubbleConcentration, 1, MPI_DOUBLE,
	MPI_SUM, 0, MPI_COMM_WORLD);
	double totalRadii = 0.0;
	MPI_Reduce(&radii, &totalRadii, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	// Master process
	if (procId == 0) {
		// Get the fluence
		double fluence = fluxHandler->getFluence();

		// Print the result
		std::cout << "\nTime: " << time << std::endl;
		std::cout << "Xenon retention = "
				<< 100.0 * (totalXeConcentration / fluence) << " %"
				<< std::endl;
		std::cout << "Xenon concentration = " << totalXeConcentration
				<< std::endl << std::endl;

		// Uncomment to write the retention and the fluence in a file
		std::ofstream outputFile;
		outputFile.open("retentionOut.txt", ios::app);
		outputFile << time << " " << 100.0 * (totalXeConcentration / fluence)
				<< " " << totalXeConcentration << " "
				<< fluence - totalXeConcentration << " "
				<< totalRadii / totalBubbleConcentration << std::endl;
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeHeliumConc1D")
/**
 * This is a monitoring method that will compute the helium concentrations
 */
PetscErrorCode computeHeliumConc1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	// Initial declarations
	PetscErrorCode ierr;
	PetscInt xs, xm;

	PetscFunctionBeginUser;

	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the physical grid in the x direction
	auto grid = solverHandler->getXGrid();

	// Get the network
	auto network = solverHandler->getNetwork();
	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);

	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the total size of the grid
	PetscInt Mx;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	CHKERRQ(ierr);

	// Get the array of concentration
	double **solutionArray, *gridPointSolution;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Create the vectors that will hold the concentrations
	// as a function of helium size
	std::vector<double> heConcLocal;
	std::vector<double> heConcentrations;
	int maxSize = 1001;
	// Initialize
	for (int i = 0; i < maxSize; i++) {
		heConcLocal.push_back(0.0);
		heConcentrations.push_back(0.0);
	}

	// Open the file
	std::ofstream outputFile;
	if (procId == 0) {
		std::stringstream name;
		name << "heliumConc_" << timestep << ".dat";
		outputFile.open(name.str());
	}

	// Loop on the full grid
	for (PetscInt xi = surfacePos; xi < Mx; xi++) {
		// Wait for everybody at each grid point
		MPI_Barrier(PETSC_COMM_WORLD);

		// Set x
		double x = grid[xi];

		// If we are on the right process
		if (xi >= xs && xi < xs + xm) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Update the concentration in the network
			network->updateConcentrationsFromArray(gridPointSolution);

			// Loop on all the indices
			for (int l = 0; l < indices1D.size(); l++) {
				// Add the current concentration
				heConcLocal[weights1D[l]] += gridPointSolution[indices1D[l]]
						* (grid[xi] - grid[xi - 1]);
			}

			// Loop on the super clusters
			for (int l = 0; l < superClusters.size(); l++) {
				// Get the super cluster
				auto superCluster = (PSISuperCluster *) superClusters[l];
				// Get its boundaries
				auto boundaries = superCluster->getBoundaries();
				// Is it the right one?
				for (int i = boundaries[0]; i <= boundaries[1]; i++) {
					for (int j = boundaries[2]; j <= boundaries[3]; j++) {
						heConcLocal[i] += superCluster->getConcentration(
								superCluster->getHeDistance(i),
								superCluster->getVDistance(j))
								* (grid[xi] - grid[xi - 1]);
					}
				}
			}
		}

		// Gather all the data
		for (int i = 0; i < maxSize; i++) {
			MPI_Reduce(&heConcLocal[i], &heConcentrations[i], 1, MPI_DOUBLE,
			MPI_SUM, 0, PETSC_COMM_WORLD);
		}

		// Print it from the main proc
		if (procId == 0) {
			for (int i = 0; i < maxSize; i++) {
				if (heConcentrations[i] > 1.0e-16) {
					outputFile << x << " " << i << " " << heConcentrations[i]
							<< std::endl;
				}
			}
		}

		// Reinitialize the concentrations
		for (int i = 0; i < maxSize; i++) {
			heConcLocal[i] = 0.0;
			heConcentrations[i] = 0.0;
		}
	}

	// Close the file
	outputFile.close();

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeCumulativeHelium1D")
/**
 * This is a monitoring method that will compute the cumulative distribution of helium
 */
PetscErrorCode computeCumulativeHelium1D(TS ts, PetscInt timestep,
		PetscReal time, Vec solution, void *ictx) {
	// Initial declarations
	PetscErrorCode ierr;
	PetscInt xs, xm;

	PetscFunctionBeginUser;

	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the physical grid and its length
	auto grid = solverHandler->getXGrid();
	int xSize = grid.size();

	// Get the array of concentration
	PetscReal **solutionArray;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Store the concentration over the grid
	double heConcentration = 0.0;

	// Declare the pointer for the concentrations at a specific grid point
	PetscReal *gridPointSolution;

	// Create the output file
	std::ofstream outputFile;
	if (procId == 0) {
		std::stringstream name;
		name << "heliumCumul_" << timestep << ".dat";
		outputFile.open(name.str());
	}

	// Loop on the entire grid
	for (int xi = surfacePos; xi < xSize; xi++) {
		// Wait for everybody at each grid point
		MPI_Barrier(PETSC_COMM_WORLD);

		// Set x
		double x = grid[xi];

		// Initialize the helium concentration at this grid point
		double heLocalConc = 0.0;

		// Check if this process is in charge of xi
		if (xi >= xs && xi < xs + xm) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Update the concentration in the network
			network->updateConcentrationsFromArray(gridPointSolution);

			// Get the total helium concentration at this grid point
			heLocalConc += network->getTotalAtomConcentration()
					* (grid[xi] - grid[xi - 1]);

			// If this is not the master process, send the value
			if (procId != 0) {
				MPI_Send(&heLocalConc, 1, MPI_DOUBLE, 0, 2, PETSC_COMM_WORLD);
			}
		}
		// If this process is not in charge of xi but is the master one, receive the value
		else if (procId == 0) {
			MPI_Recv(&heLocalConc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2,
					PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		// The master process writes computes the cumulative value and writes in the file
		if (procId == 0) {
			heConcentration += heLocalConc;
			outputFile << x - grid[surfacePos] << " " << heConcentration
					<< std::endl;
		}
	}

	// Close the file
	if (procId == 0) {
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeTRIDYN1D")
/**
 * This is a monitoring method that will compute the data to send to TRIDYN
 */
PetscErrorCode computeTRIDYN1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	// Initial declarations
	PetscErrorCode ierr;
	PetscInt xs, xm;

	PetscFunctionBeginUser;

	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the physical grid and its length
	auto grid = solverHandler->getXGrid();
	int xSize = grid.size();

	// Get the array of concentration
	PetscReal **solutionArray;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Declare the pointer for the concentrations at a specific grid point
	PetscReal *gridPointSolution;

	// Create the output file
	std::ofstream outputFile;
	if (procId == 0) {
		std::stringstream name;
		name << "TRIDYN_" << timestep << ".dat";
		outputFile.open(name.str());
	}

	// Loop on the entire grid
	for (int xi = surfacePos; xi < xSize; xi++) {
		// Wait for everybody at each grid point
		MPI_Barrier(PETSC_COMM_WORLD);

		// Set x
		double x = grid[xi];

		// Initialize the concentrations at this grid point
		double heLocalConc = 0.0, vLocalConc = 0.0, iLocalConc = 0.0;

		// Check if this process is in charge of xi
		if (xi >= xs && xi < xs + xm) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Update the concentration in the network
			network->updateConcentrationsFromArray(gridPointSolution);

			// Get the total helium concentration at this grid point
			heLocalConc += network->getTotalAtomConcentration();
			vLocalConc += network->getTotalVConcentration();
			iLocalConc += network->getTotalIConcentration();

			// If this is not the master process, send the values
			if (procId != 0) {
				MPI_Send(&heLocalConc, 1, MPI_DOUBLE, 0, 2, PETSC_COMM_WORLD);
				MPI_Send(&vLocalConc, 1, MPI_DOUBLE, 0, 3, PETSC_COMM_WORLD);
				MPI_Send(&iLocalConc, 1, MPI_DOUBLE, 0, 4, PETSC_COMM_WORLD);
			}
		}
		// If this process is not in charge of xi but is the master one, receive the values
		else if (procId == 0) {
			MPI_Recv(&heLocalConc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2,
					PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&vLocalConc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 3,
					PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&vLocalConc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 4,
					PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		// The master process writes computes the cumulative value and writes in the file
		if (procId == 0) {
			outputFile << x - grid[surfacePos] << " " << heLocalConc << " "
					<< vLocalConc << " " << iLocalConc << std::endl;
		}
	}

	// Close the file
	if (procId == 0) {
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorScatter1D")
/**
<<<<<<< HEAD
 * This is a monitoring method that will save 1D plots of one concentration
 */
PetscErrorCode monitorScatter1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;
	double x;

	PetscFunctionBeginUser;

=======
 * This is a monitoring method that will save 1D plots of the xenon concentration
 * distribution at the middle of the grid.
 */
PetscErrorCode monitorScatter1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
	PetscErrorCode ierr;
	double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi, Mx;

	PetscFunctionBeginUser;

	// Don't do anything if it is not on the stride
	if (timestep % 10 != 0)
		PetscFunctionReturn(0);

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID (important when it is running in parallel)
	int procId;
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
<<<<<<< HEAD
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);
=======
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the size of the total grid
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
	checkPetscError(ierr, "setupPetsc1DMonitor: DMDAGetInfo failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

<<<<<<< HEAD
	// Get the network
	auto network = solverHandler->getNetwork();

	// Setup step size variable
	double hx = solverHandler->getStepSizeX();

	// Choice of the cluster to be plotted
	int iCluster = 6;
=======
	// Get the network and its size
	auto network = solverHandler->getNetwork();
	int networkSize = network->size();
	auto superClusters = network->getAll(NESuperType);

	// Get the index of the middle of the grid
	PetscInt ix = Mx / 2;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	if (procId == 0) {
		// Create a Point vector to store the data to give to the data provider
		// for the visualization
		auto myPoints = std::make_shared<std::vector<xolotlViz::Point> >();

<<<<<<< HEAD
		// Loop on the grid
		for (xi = xs; xi < xs + xm; xi++) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Create a Point with the concentration[iCluster] as the value
			// and add it to myPoints
			xolotlViz::Point aPoint;
			aPoint.value = gridPointSolution[iCluster];
			aPoint.t = time;
			aPoint.x = (double) xi * hx;
			myPoints->push_back(aPoint);
		}

		// Loop on the other processes
		for (int i = 1; i < worldSize; i++) {
			// Get the size of the local grid of that process
			int localSize = 0;
			MPI_Recv(&localSize, 1, MPI_INT, i, 10, MPI_COMM_WORLD,
					MPI_STATUS_IGNORE);

			// Loop on their grid
			for (int k = 0; k < localSize; k++) {
				// Get the position
				MPI_Recv(&x, 1, MPI_DOUBLE, i, 11, MPI_COMM_WORLD,
						MPI_STATUS_IGNORE);

				// and the concentration
				double conc = 0.0;
				MPI_Recv(&conc, 1, MPI_DOUBLE, i, 12, MPI_COMM_WORLD,
						MPI_STATUS_IGNORE);

				// Create a Point with the concentration[iCluster] as the value
=======
		// If the middle is on this process
		if (ix >= xs && ix < xs + xm) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[ix];

			// Update the concentration in the network
			network->updateConcentrationsFromArray(gridPointSolution);

			for (int i = 0; i < networkSize - superClusters.size(); i++) {
				// Create a Point with the concentration[i] as the value
				// and add it to myPoints
				xolotlViz::Point aPoint;
				aPoint.value = gridPointSolution[i];
				aPoint.t = time;
				aPoint.x = (double) i + 1.0;
				myPoints->push_back(aPoint);
			}
			int nXe = networkSize - superClusters.size() + 1;
			for (int i = 0; i < superClusters.size(); i++) {
				// Get the cluster
				auto cluster = (NESuperCluster *) superClusters[i];
				// Get the width
				int width = cluster->getSectionWidth();
				// Loop on the width
				for (int k = 0; k < width; k++) {
					// Compute the distance
					double dist = cluster->getDistance(nXe + k);
					// Create a Point with the concentration[i] as the value
					// and add it to myPoints
					xolotlViz::Point aPoint;
					aPoint.value = cluster->getConcentration(dist);
					aPoint.t = time;
					aPoint.x = (double) nXe + k;
					myPoints->push_back(aPoint);
				}

				// update nXe
				nXe += width;
			}
		}

		// else receive the values from another process
		else {
			for (int i = 0; i < networkSize - superClusters.size(); i++) {
				double conc = 0.0;
				MPI_Recv(&conc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 10,
						MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				// Create a Point with conc as the value
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				// and add it to myPoints
				xolotlViz::Point aPoint;
				aPoint.value = conc;
				aPoint.t = time;
<<<<<<< HEAD
				aPoint.x = x;
				myPoints->push_back(aPoint);
			}
=======
				aPoint.x = (double) i + 1.0;
				myPoints->push_back(aPoint);
			}
			int nXe = networkSize - superClusters.size() + 1;
			for (int i = 0; i < superClusters.size(); i++) {
				// Get the cluster
				auto cluster = (NESuperCluster *) superClusters[i];
				// Get the width
				int width = cluster->getSectionWidth();
				// Loop on the width
				for (int k = 0; k < width; k++) {
					double conc = 0.0;
					MPI_Recv(&conc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 10,
							MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					// Create a Point with conc as the value
					// and add it to myPoints
					xolotlViz::Point aPoint;
					aPoint.value = conc;
					aPoint.t = time;
					aPoint.x = (double) nXe + k;
					myPoints->push_back(aPoint);
				}

				// update nXe
				nXe += width;
			}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		}

		// Get the data provider and give it the points
		scatterPlot1D->getDataProvider()->setPoints(myPoints);

<<<<<<< HEAD
		// Get the iCluster cluster to have access to its name
		auto reactants = network->getAll();
		auto cluster = (PSICluster *) reactants->at(iCluster);

		// Change the title of the plot and the name of the data
		std::stringstream title;
		title << cluster->getName();
		scatterPlot1D->getDataProvider()->setDataName(title.str());
		title << " concentration";
=======
		// Change the title of the plot and the name of the data
		std::stringstream title;
		title << "Size Distribution";
		scatterPlot1D->getDataProvider()->setDataName(title.str());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		scatterPlot1D->plotLabelProvider->titleLabel = title.str();
		// Give the time to the label provider
		std::stringstream timeLabel;
		timeLabel << "time: " << std::setprecision(4) << time << "s";
		scatterPlot1D->plotLabelProvider->timeLabel = timeLabel.str();
		// Get the current time step
		PetscReal currentTimeStep;
<<<<<<< HEAD
		ierr = TSGetTimeStep(ts, &currentTimeStep);CHKERRQ(ierr);
=======
		ierr = TSGetTimeStep(ts, &currentTimeStep);
		CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Give the timestep to the label provider
		std::stringstream timeStepLabel;
		timeStepLabel << "dt: " << std::setprecision(4) << currentTimeStep
				<< "s";
		scatterPlot1D->plotLabelProvider->timeStepLabel = timeStepLabel.str();

		// Render and save in file
		std::stringstream fileName;
<<<<<<< HEAD
		fileName << cluster->getName() << "_scatter_TS" << timestep << ".pnm";
=======
		fileName << "Scatter_TS" << timestep << ".pnm";
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		scatterPlot1D->write(fileName.str());
	}

	else {
<<<<<<< HEAD
		// Send the value of the local grid size to the master process
		MPI_Send(&xm, 1, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD);

		// Loop on the grid
		for (xi = xs; xi < xs + xm; xi++) {
			// Dump x
			x = (double) xi * hx;

			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Send the value of the local position to the master process
			MPI_Send(&x, 1, MPI_DOUBLE, 0, 11, MPI_COMM_WORLD);

			// Send the value of the concentration to the master process
			MPI_Send(&gridPointSolution[iCluster], 1, MPI_DOUBLE, 0, 12,
					MPI_COMM_WORLD);
=======
		// If the middle is on this process
		if (ix >= xs && ix < xs + xm) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[ix];

			for (int i = 0; i < networkSize - superClusters.size(); i++) {
				// Send the value of each concentration to the master process
				MPI_Send(&gridPointSolution[i], 1, MPI_DOUBLE, 0, 10,
						MPI_COMM_WORLD);
			}
			int nXe = networkSize - superClusters.size() + 1;
			for (int i = 0; i < superClusters.size(); i++) {
				// Get the cluster
				auto cluster = (NESuperCluster *) superClusters[i];
				// Get the width
				int width = cluster->getSectionWidth();
				// Loop on the width
				for (int k = 0; k < width; k++) {
					// Compute the distance
					double dist = cluster->getDistance(nXe + k);
					double conc = cluster->getConcentration(dist);
					// Send the value of each concentration to the master process
					MPI_Send(&conc, 1, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD);
				}

				// update nXe
				nXe += width;
			}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		}
	}

	// Restore the solutionArray
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorSeries1D")
/**
 * This is a monitoring method that will save 1D plots of many concentrations
 */
PetscErrorCode monitorSeries1D(TS ts, PetscInt timestep, PetscReal time,
<<<<<<< HEAD
		Vec solution, void *ictx) {
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;
	double x;

	PetscFunctionBeginUser;

=======
		Vec solution, void *) {
	// Initial declarations
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;
	double x = 0.0;

	PetscFunctionBeginUser;

	// Don't do anything if it is not on the stride
	if (timestep % 10 != 0)
		PetscFunctionReturn(0);

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID (important when it is running in parallel)
	int procId;
<<<<<<< HEAD
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);
=======
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto network = solverHandler->getNetwork();
	const int networkSize = network->size();

<<<<<<< HEAD
	// Setup step size variable
	double hx = solverHandler->getStepSizeX();
=======
	// Get the physical grid
	auto grid = solverHandler->getXGrid();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// To plot a maximum of 18 clusters of the whole benchmark
	const int loopSize = std::min(18, networkSize);

	if (procId == 0) {
		// Create a Point vector to store the data to give to the data provider
		// for the visualization
		std::vector<std::vector<xolotlViz::Point> > myPoints(loopSize);

		// Loop on the grid
		for (xi = xs; xi < xs + xm; xi++) {
			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			for (int i = 0; i < loopSize; i++) {
<<<<<<< HEAD
				// Create a Point with the concentration[iCluster] as the value
=======
				// Create a Point with the concentration[i] as the value
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				// and add it to myPoints
				xolotlViz::Point aPoint;
				aPoint.value = gridPointSolution[i];
				aPoint.t = time;
<<<<<<< HEAD
				aPoint.x = xi * hx;
=======
				aPoint.x = grid[xi];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				myPoints[i].push_back(aPoint);
			}
		}

		// Loop on the other processes
		for (int i = 1; i < worldSize; i++) {
			// Get the size of the local grid of that process
			int localSize = 0;
<<<<<<< HEAD
			MPI_Recv(&localSize, 1, MPI_INT, i, 20, MPI_COMM_WORLD,
=======
			MPI_Recv(&localSize, 1, MPI_INT, i, 20, PETSC_COMM_WORLD,
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					MPI_STATUS_IGNORE);

			// Loop on their grid
			for (int k = 0; k < localSize; k++) {
				// Get the position
<<<<<<< HEAD
				MPI_Recv(&x, 1, MPI_DOUBLE, i, 21, MPI_COMM_WORLD,
=======
				MPI_Recv(&x, 1, MPI_DOUBLE, i, 21, PETSC_COMM_WORLD,
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
						MPI_STATUS_IGNORE);

				for (int j = 0; j < loopSize; j++) {
					// and the concentrations
<<<<<<< HEAD
					double conc;
					MPI_Recv(&conc, 1, MPI_DOUBLE, i, 22, MPI_COMM_WORLD,
							MPI_STATUS_IGNORE);

					// Create a Point with the concentration[iCluster] as the value
=======
					double conc = 0.0;
					MPI_Recv(&conc, 1, MPI_DOUBLE, i, 22, PETSC_COMM_WORLD,
							MPI_STATUS_IGNORE);

					// Create a Point with the concentration[i] as the value
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					// and add it to myPoints
					xolotlViz::Point aPoint;
					aPoint.value = conc; // He
					aPoint.t = time;
					aPoint.x = x;
					myPoints[j].push_back(aPoint);
				}
			}
		}

		// Get all the reactants to have access to their names
		auto reactants = network->getAll();

		for (int i = 0; i < loopSize; i++) {
<<<<<<< HEAD
			auto cluster = (PSICluster *) reactants->at(i);
=======
			auto cluster = reactants->at(i);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// Get the data provider and give it the points
			auto thePoints = std::make_shared<std::vector<xolotlViz::Point> >(
					myPoints[i]);
			seriesPlot1D->getDataProvider(i)->setPoints(thePoints);
			seriesPlot1D->getDataProvider(i)->setDataName(cluster->getName());
		}

		// Change the title of the plot
		std::stringstream title;
		title << "Concentrations";
		seriesPlot1D->plotLabelProvider->titleLabel = title.str();
		// Give the time to the label provider
		std::stringstream timeLabel;
		timeLabel << "time: " << std::setprecision(4) << time << "s";
		seriesPlot1D->plotLabelProvider->timeLabel = timeLabel.str();
		// Get the current time step
		PetscReal currentTimeStep;
<<<<<<< HEAD
		ierr = TSGetTimeStep(ts, &currentTimeStep);CHKERRQ(ierr);
=======
		ierr = TSGetTimeStep(ts, &currentTimeStep);
		CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Give the timestep to the label provider
		std::stringstream timeStepLabel;
		timeStepLabel << "dt: " << std::setprecision(4) << currentTimeStep
				<< "s";
		seriesPlot1D->plotLabelProvider->timeStepLabel = timeStepLabel.str();

		// Render and save in file
		std::stringstream fileName;
<<<<<<< HEAD
		fileName << "log_series_TS" << timestep << ".pnm";
=======
//		fileName << "log_series_TS" << timestep << ".pnm";
		fileName << "series_TS" << timestep << ".pnm";
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		seriesPlot1D->write(fileName.str());
	}

	else {
		// Send the value of the local grid size to the master process
<<<<<<< HEAD
		MPI_Send(&xm, 1, MPI_DOUBLE, 0, 20, MPI_COMM_WORLD);
=======
		MPI_Send(&xm, 1, MPI_DOUBLE, 0, 20, PETSC_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Loop on the grid
		for (xi = xs; xi < xs + xm; xi++) {
			// Dump x
<<<<<<< HEAD
			x = xi * hx;
=======
			x = grid[xi];
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Send the value of the local position to the master process
<<<<<<< HEAD
			MPI_Send(&x, 1, MPI_DOUBLE, 0, 21, MPI_COMM_WORLD);
=======
			MPI_Send(&x, 1, MPI_DOUBLE, 0, 21, PETSC_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

			for (int i = 0; i < loopSize; i++) {
				// Send the value of the concentrations to the master process
				MPI_Send(&gridPointSolution[i], 1, MPI_DOUBLE, 0, 22,
<<<<<<< HEAD
						MPI_COMM_WORLD);
=======
						PETSC_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			}
		}
	}

	// Restore the solutionArray
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);
=======
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorSurface1D")
/**
 * This is a monitoring method that will save 2D plots for each depths of
 * the concentration as a function of the cluster composition.
 */
PetscErrorCode monitorSurface1D(TS ts, PetscInt timestep, PetscReal time,
<<<<<<< HEAD
		Vec solution, void *ictx) {
=======
		Vec solution, void *) {
	// Initial declarations
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;

	PetscFunctionBeginUser;

<<<<<<< HEAD
	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);
=======
	// Don't do anything if it is not on the stride
	if (timestep % 10 != 0)
		PetscFunctionReturn(0);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();
<<<<<<< HEAD

	// Setup step size variable
	double hx = solverHandler->getStepSizeX();

	// Get the maximum size of HeV clusters
	auto psiNetwork = (PSIClusterReactionNetwork *) network;
	std::map<std::string, std::string> props = psiNetwork->getProperties();
	int maxHeVClusterSize = std::stoi(props["maxHeVClusterSize"]);
	int maxVClusterSize = std::stoi(props["maxVClusterSize"]);

	// Loop on the grid points
	for (xi = xs; xi < xs + xm; xi++) {
=======
	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();

	// Get the maximum size of HeV clusters
	auto psiNetwork = dynamic_cast<PSIClusterReactionNetwork*>(network);
	int maxHeVClusterSize = psiNetwork->getMaxHeVClusterSize();
	int maxVClusterSize = psiNetwork->getMaxVClusterSize();

	// Loop on the grid points
	for (xi = xs; xi < xs + xm; xi++) {

		if (xi != 5)
			continue;

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Create a Point vector to store the data to give to the data provider
		// for the visualization
		auto myPoints = std::make_shared<std::vector<xolotlViz::Point> >();

		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];

		// A pointer for the clusters used below
<<<<<<< HEAD
		PSICluster * cluster;
=======
		IReactant * cluster;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

		// Loop on Y = V number
		for (int i = 0; i <= maxVClusterSize; i++) {
			// Loop on X = He number
			for (int j = 0; j <= maxHeVClusterSize - maxVClusterSize; j++) {
				double conc = 0.0;
				// V clusters
				if (j == 0) {
<<<<<<< HEAD
					cluster = (PSICluster *) network->get("V",
							i);
=======
					cluster = network->get("V", i);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					if (cluster) {
						// Get the ID of the cluster
						int id = cluster->getId() - 1;
						conc = gridPointSolution[id];
					}
				}
				// He clusters
				else if (i == 0) {
<<<<<<< HEAD
					cluster = (PSICluster *) network->get(
							"He", j);
=======
					cluster = network->get("He", j);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					if (cluster) {
						// Get the ID of the cluster
						int id = cluster->getId() - 1;
						conc = gridPointSolution[id];
					}
				}
				// HeV clusters
				else {
<<<<<<< HEAD
					cluster =
							(PSICluster *) network->getCompound(
									"HeV", { j, i, 0 });
=======
					cluster = network->getCompound("HeV", { j, i, 0 });
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					if (cluster) {
						// Get the ID of the cluster
						int id = cluster->getId() - 1;
						conc = gridPointSolution[id];
					}
<<<<<<< HEAD
				}

				// Create a Point with the concentration as the value
				// and add it to myPoints
				xolotlViz::Point aPoint;
				aPoint.value = conc;
				aPoint.t = time;
				aPoint.x = (double) j;
				aPoint.y = (double) i;
				myPoints->push_back(aPoint);
			}
		}

		// Get the data provider and give it the points
		surfacePlot1D->getDataProvider()->setPoints(myPoints);
		surfacePlot1D->getDataProvider()->setDataName("brian");

		// Change the title of the plot
		std::stringstream title;
		title << "Concentration at Depth: " << xi * hx << " nm";
		surfacePlot1D->plotLabelProvider->titleLabel = title.str();
		// Give the time to the label provider
		std::stringstream timeLabel;
		timeLabel << "time: " << std::setprecision(4) << time << "s";
		surfacePlot1D->plotLabelProvider->timeLabel = timeLabel.str();
		// Get the current time step
		PetscReal currentTimeStep;
		ierr = TSGetTimeStep(ts, &currentTimeStep);CHKERRQ(ierr);
		// Give the timestep to the label provider
		std::stringstream timeStepLabel;
		timeStepLabel << "dt: " << std::setprecision(4) << currentTimeStep
				<< "s";
		surfacePlot1D->plotLabelProvider->timeStepLabel = timeStepLabel.str();

		// Render and save in file
		std::stringstream fileName;
		fileName << "Brian_TS" << timestep << "_D" << xi << ".pnm";
		surfacePlot1D->write(fileName.str());
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);
=======

					else {
						// Look for superClusters !
						PSISuperCluster * superCluster = nullptr;
						// Loop on the super clusters
						for (int l = 0; l < superClusters.size(); l++) {
							// Get the super cluster
							superCluster = (PSISuperCluster *) superClusters[l];
							// Get its boundaries
							auto boundaries = superCluster->getBoundaries();
							// Is it the right one?
							if (j >= boundaries[0] && j <= boundaries[1]
									&& i >= boundaries[2]
									&& i <= boundaries[3]) {
								conc = superCluster->getConcentration(
										superCluster->getHeDistance(j),
										superCluster->getVDistance(i));
								break;
							}
						}
					}
				}

				// Create a Point with the concentration as the value
				// and add it to myPoints
				xolotlViz::Point aPoint;
				aPoint.value = conc;
				aPoint.t = time;
				aPoint.x = (double) j;
				aPoint.y = (double) i;
				myPoints->push_back(aPoint);
			}
		}

		// Get the data provider and give it the points
		surfacePlot1D->getDataProvider()->setPoints(myPoints);
		surfacePlot1D->getDataProvider()->setDataName("brian");

		// Change the title of the plot
		std::stringstream title;
		title << "Concentration at Depth: " << grid[xi] << " nm";
		surfacePlot1D->plotLabelProvider->titleLabel = title.str();
		// Give the time to the label provider
		std::stringstream timeLabel;
		timeLabel << "time: " << std::setprecision(4) << time << "s";
		surfacePlot1D->plotLabelProvider->timeLabel = timeLabel.str();
		// Get the current time step
		PetscReal currentTimeStep;
		ierr = TSGetTimeStep(ts, &currentTimeStep);
		CHKERRQ(ierr);
		// Give the timestep to the label provider
		std::stringstream timeStepLabel;
		timeStepLabel << "dt: " << std::setprecision(4) << currentTimeStep
				<< "s";
		surfacePlot1D->plotLabelProvider->timeStepLabel = timeStepLabel.str();

		// Render and save in file
		std::stringstream fileName;
		fileName << "Brian_TS" << timestep << "_D" << xi << ".pnm";
		surfacePlot1D->write(fileName.str());
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorMeanSize1D")
/**
 * This is a monitoring method that will create files with the mean
 * helium size as a function of depth at each time step.
 */
PetscErrorCode monitorMeanSize1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	// Initial declaration
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;
	double x = 0.0;

	PetscFunctionBeginUser;

	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();

	// Create the output file
	std::ofstream outputFile;
	if (procId == 0) {
		std::stringstream name;
		name << "heliumSizeMean_" << timestep << ".dat";
		outputFile.open(name.str());
	}

	// Loop on the full grid
	for (xi = 0; xi < grid.size(); xi++) {
		// Wait for everybody at each grid point
		MPI_Barrier(PETSC_COMM_WORLD);

		// Get the x position
		x = grid[xi];

		// Initialize the values to write in the file
		double heliumMean = 0.0;

		// If this is the locally owned part of the grid
		if (xi >= xs && xi < xs + xm) {
			// Compute the mean and standard deviation of helium cluster size

			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[xi];

			// Initialize the total helium and concentration before looping
			double concTot = 0.0, heliumTot = 0.0;

			// Loop on all the indices to compute the mean
			for (int i = 0; i < indices1D.size(); i++) {
				concTot += gridPointSolution[indices1D[i]];
				heliumTot += gridPointSolution[indices1D[i]] * weights1D[i];
			}

			// Loop on all the super clusters
			for (int i = 0; i < superClusters.size(); i++) {
				auto cluster = (xolotlCore::PSISuperCluster *) superClusters[i];
				concTot += cluster->getTotalConcentration();
				heliumTot += cluster->getTotalHeliumConcentration();
			}

			// Compute the mean size of helium at this depth
			heliumMean = heliumTot / concTot;

			// If this is not the master process, send the values
			if (procId != 0) {
				MPI_Send(&heliumMean, 1, MPI_DOUBLE, 0, 5, PETSC_COMM_WORLD);
			}
		}
		// If this process is not in charge of xi but is the master one, receive the value
		else if (procId == 0) {
			MPI_Recv(&heliumMean, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 5,
					PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		// The master process writes in the file
		if (procId == 0) {
			outputFile << x << " " << heliumMean << std::endl;
		}
	}

	// Close the file
	if (procId == 0) {
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorMaxClusterConc1D")
<<<<<<< HEAD
PetscErrorCode monitorMaxClusterConc1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
=======
/**
 * This is a monitoring method that will print a message when the biggest cluster
 * in the network reaches a non-negligible concentration value.
 */
PetscErrorCode monitorMaxClusterConc1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;

	PetscFunctionBeginUser;

	// Don't do anything if it was already printed
<<<<<<< HEAD
	if (!printMaxClusterConc1D) PetscFunctionReturn(0);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);
=======
	if (!printMaxClusterConc1D)
		PetscFunctionReturn(0);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Get the maximum size of HeV clusters
<<<<<<< HEAD
	auto psiNetwork = (PSIClusterReactionNetwork *) network;
	std::map<std::string, std::string> props = psiNetwork->getProperties();
	int maxHeVClusterSize = std::stoi(props["maxHeVClusterSize"]);
	// Get the maximum size of V clusters
	int maxVClusterSize = std::stoi(props["maxVClusterSize"]);
	// Get the number of He in the max HeV cluster
	int maxHeSize = (maxHeVClusterSize - maxVClusterSize);
	// Get the maximum stable HeV cluster
	PSICluster * maxHeV;
	maxHeV = (PSICluster *) network->getCompound(
			"HeV", { maxHeSize, maxVClusterSize, 0 });

	// Boolean to know if the concentration is too big
	bool maxHeVTooBig = false;
=======
	auto psiNetwork = dynamic_cast<PSIClusterReactionNetwork*>(network);
	int maxHeVClusterSize = psiNetwork->getMaxHeVClusterSize();
	// Get the maximum size of V clusters
	int maxVClusterSize = psiNetwork->getMaxVClusterSize();
	// Get the number of He in the max HeV cluster
	int maxHeSize = (maxHeVClusterSize - maxVClusterSize);
	// Get the maximum stable HeV cluster
	IReactant * maxCluster;
	maxCluster = network->getCompound(heVType,
			{ maxHeSize, maxVClusterSize, 0 });
	if (!maxCluster) {
		// Get the maximum size of Xe clusters
		auto neNetwork = dynamic_cast<NEClusterReactionNetwork*>(network);
		int maxXeClusterSize = neNetwork->getMaxXeClusterSize();
		maxCluster = network->get(xeType, maxXeClusterSize);
	}

	// Boolean to know if the concentration is too big
	bool maxClusterTooBig = false;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Check the concentration of the biggest cluster at each grid point
	for (xi = xs; xi < xs + xm; xi++) {
		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];

		// Get the concentration of the maximum HeV cluster
<<<<<<< HEAD
		auto maxHeVConc = gridPointSolution[maxHeV->getId() - 1];

		if (maxHeVConc > 1.0e-16) maxHeVTooBig = true;
=======
		auto maxClusterConc = gridPointSolution[maxCluster->getId() - 1];

		if (maxClusterConc > 1.0e-16)
			maxClusterTooBig = true;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Get the current process ID
	int procId;
<<<<<<< HEAD
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);

	// Is the concentration too big on any process?
	bool tooBig = false;
	MPI_Reduce(&maxHeVTooBig, &tooBig, 1, MPI_C_BOOL, MPI_LOR, 0, MPI_COMM_WORLD);
=======
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Is the concentration too big on any process?
	bool tooBig = false;
	MPI_Reduce(&maxClusterTooBig, &tooBig, 1, MPI_C_BOOL, MPI_LOR, 0,
			PETSC_COMM_WORLD);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Main process
	if (procId == 0) {
		// Print if tooBig is true
		if (tooBig) {
			std::cout << std::endl;
			std::cout << "At time step: " << timestep << " and time: " << time
<<<<<<< HEAD
					<< " the biggest cluster: " << *maxHeV
=======
					<< " the biggest cluster: " << maxCluster->getName()
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					<< " reached a concentration above 1.0e-16 at at least one grid point."
					<< std::endl << std::endl;

			// Don't print anymore
			printMaxClusterConc1D = false;
		}
	}

	// Broadcast the information about printMaxClusterConc1D to the other processes
<<<<<<< HEAD
	MPI_Bcast(&printMaxClusterConc1D, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);
=======
	MPI_Bcast(&printMaxClusterConc1D, 1, MPI_C_BOOL, 0, PETSC_COMM_WORLD);

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

#undef __FUNCT__
<<<<<<< HEAD
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorInterstitial1D")
/**
 * This is a monitoring method that will compute the flux of interstitials
 * at the surface
 */
PetscErrorCode monitorInterstitial1D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;

	PetscFunctionBeginUser;

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);CHKERRQ(ierr);

	// Return if the grid point 1 is not on this process
	if (xs > 1) PetscFunctionReturn(0);
=======
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorMovingSurface1D")
/**
 * This is a monitoring method that will move the surface depending on the
 * interstitial flux
 */
PetscErrorCode monitorMovingSurface1D(TS ts, PetscInt, PetscReal time,
		Vec solution, void *) {
	// Initial declaration
	PetscErrorCode ierr;
	double **solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi;
	bool surfaceHasMoved = false;

	PetscFunctionBeginUser;

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();
	xi = surfacePos + 1;

	// Get the network
	auto network = solverHandler->getNetwork();
	int dof = network->getDOF();

	// Get the physical grid
	auto grid = solverHandler->getXGrid();

	// Get the flux handler to know the flux amplitude.
	auto fluxHandler = solverHandler->getFluxHandler();
	double heliumFluxAmplitude = fluxHandler->getFluxAmplitude();

	// Value to now on which processor is the location of the surface,
	// for MPI usage
	int surfaceProc = 0;

	// if xi is on this process
	if (xi >= xs && xi < xs + xm) {
		// Get the concentrations at xi = surfacePos + 1
		gridPointSolution = solutionArray[xi];

		// Get the delta time from the previous timestep to this timestep
		double dt = time - previousTime;

		// Compute the total density of intersitials that escaped from the
		// surface since last timestep using the stored flux
		nInterstitial1D += previousIFlux1D * dt;

		// Remove the sputtering yield since last timestep
		nInterstitial1D -= sputteringYield1D * heliumFluxAmplitude * dt;

		// Initialize the value for the flux
		double newFlux = 0.0;

		// Get all the interstitial clusters
		auto interstitials = network->getAll("I");
		// Loop on them
		for (unsigned int i = 0; i < interstitials.size(); i++) {
			// Get the cluster
			auto cluster = interstitials.at(i);
			// Get its id and concentration
			int id = cluster->getId() - 1;
			double conc = gridPointSolution[id];
			// Get its size and diffusion coefficient
			int size = cluster->getSize();
			double coef = cluster->getDiffusionCoefficient();

			// Factor for finite difference
			double hxLeft = grid[xi] - grid[xi - 1];
			double hxRight = grid[xi + 1] - grid[xi];
			double factor = 2.0 / (hxLeft * (hxLeft + hxRight));
			// Compute the flux going to the left
			newFlux += (double) size * factor * coef * conc * hxLeft;
		}

		// Update the previous flux
		previousIFlux1D = newFlux;

		// Set the surface processor
		surfaceProc = procId;
	}

	// Get which processor will send the information
	int surfaceId = 0;
	MPI_Allreduce(&surfaceProc, &surfaceId, 1, MPI_INT, MPI_SUM,
			PETSC_COMM_WORLD);

	// Send the information about nInterstitial1D and previousFlux1D
	// to the other processes
	MPI_Bcast(&nInterstitial1D, 1, MPI_DOUBLE, surfaceId, PETSC_COMM_WORLD);
	MPI_Bcast(&previousIFlux1D, 1, MPI_DOUBLE, surfaceId, PETSC_COMM_WORLD);

	// Now that all the processes have the same value of nInterstitials, compare
	// it to the threshold to now if we should move the surface

	// Get the initial vacancy concentration
	double initialVConc = solverHandler->getInitialVConc();

	// The density of tungsten is 62.8 atoms/nm3, thus the threshold is
	double threshold = (62.8 - initialVConc) * (grid[xi] - grid[xi - 1]);
	if (nInterstitial1D > threshold) {
		// The surface is moving
		surfaceHasMoved = true;
		// Compute the number of grid points to move the surface of
		int nGridPoints = (int) (nInterstitial1D / threshold);
		// Remove the number of interstitials we just transformed in new material
		// from nInterstitial1D
		nInterstitial1D = nInterstitial1D - threshold * (double) nGridPoints;

		// Compute the new surface position
		surfacePos -= nGridPoints;

		// Throw an exception if the position is negative
		if (surfacePos < 0) {
			throw std::string(
					"\nxolotlSolver::Monitor1D: The surface is trying to go outside of the grid!!");
		}

		// Printing information about the extension of the material
		if (procId == 0) {
			std::cout << "Adding " << nGridPoints
					<< " points to the grid at time: " << time << " s."
					<< std::endl;
		}

		// Set it in the solver
		solverHandler->setSurfacePosition(surfacePos);

		// Initialize the vacancy concentration on the new grid points
		// Get the single vacancy ID
		auto singleVacancyCluster = network->get(xolotlCore::vType, 1);
		int vacancyIndex = -1;
		if (singleVacancyCluster)
			vacancyIndex = singleVacancyCluster->getId() - 1;
		// Loop on the new grid points
		while (nGridPoints > 0) {
			// Position of the newly created grid point
			xi = surfacePos + nGridPoints;

			// If xi is on this process
			if (xi >= xs && xi < xs + xm && vacancyIndex > 0) {
				// Get the concentrations
				gridPointSolution = solutionArray[xi];
				// Initialize the vacancy concentration
				gridPointSolution[vacancyIndex] = initialVConc;
			}

			// Decrease the number of grid points
			--nGridPoints;
		}
	}

	// Moving the surface back
	else if (nInterstitial1D < -threshold / 10.0) {
		// The surface is moving
		surfaceHasMoved = true;

		// Move it back as long as the number of interstitials in negative
		while (nInterstitial1D < 0.0) {
			// Compute the threshold to a deeper grid point
			threshold = (62.8 - initialVConc) * (grid[xi + 1] - grid[xi]);
			// Set all the concentrations to 0.0 at xi = surfacePos + 1
			// if xi is on this process
			if (xi >= xs && xi < xs + xm) {
				// Get the concentrations at xi = surfacePos + 1
				gridPointSolution = solutionArray[xi];
				// Loop on DOF
				for (int i = 0; i < dof; i++) {
					gridPointSolution[i] = 0.0;
				}
			}

			// Move the surface deeper
			surfacePos++;
			xi = surfacePos + 1;
			// Update the number of interstitials
			nInterstitial1D += threshold;
		}

		// Printing information about the extension of the material
		if (procId == 0) {
			std::cout << "Removing grid points to the grid at time: " << time
					<< " s." << std::endl;
		}

		// Set it in the solver
		solverHandler->setSurfacePosition(surfacePos);
	}

	// Reinitialize the physics handlers if the surface has moved
	if (surfaceHasMoved) {
		// Set the new surface location in the surface advection handler
		auto advecHandler = solverHandler->getAdvectionHandler();
		advecHandler->setLocation(grid[surfacePos]);

		// Get the flux handler to reinitialize it
		auto fluxHandler = solverHandler->getFluxHandler();
		fluxHandler->initializeFluxHandler(network, surfacePos, grid);

		// Get the modified trap-mutation handler to reinitialize it
		auto mutationHandler = solverHandler->getMutationHandler();
		auto advecHandlers = solverHandler->getAdvectionHandlers();
		mutationHandler->initializeIndex1D(surfacePos, network, advecHandlers,
				grid);
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorBursting1D")
/**
 * This is a monitoring method that bursts bubbles.
 */
PetscErrorCode monitorBursting1D(TS ts, PetscInt, PetscReal time, Vec solution,
		void *) {
	// Initial declarations
	PetscErrorCode ierr;
	double **solutionArray, *gridPointSolution;
	int xs, xm, xi;

	PetscFunctionBeginUser;

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, NULL, NULL, &xm, NULL, NULL);
	CHKERRQ(ierr);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

<<<<<<< HEAD
	// Get the network
	auto network = solverHandler->getNetwork();

	// Setup step size variables
	double hx = solverHandler->getStepSizeX();
	double s = 1.0 / (hx * hx);

	// Get the concentrations at xi = 1
	xi = 1;
	gridPointSolution = solutionArray[xi];

	// Get the delta time from the previous timestep to this timestep
	//double dt = time - previousTime;

	// Compute the total density of intersitials that escaped from the
	// surface since last timestep using the stored flux
	//double nInterstitial = previousIFlux1D * dt;

//	// Uncomment to write the interstitial flux in a file
//	std::ofstream outputFile;
//	outputFile.open("interstitialOut.txt", ios::app);
//	outputFile << time << " "
//			<< nInterstitial << std::endl;
//	outputFile.close();

	// Initialize the value for the flux
	double newFlux = 0.0;

	// Get all the interstitial clusters
	auto interstitials = network->getAll("I");
	// Loop on them
	for (int i = 0; i < interstitials.size(); i++) {
		// Get the cluster
		auto cluster = (PSICluster *) interstitials.at(i);
		// Get its id and concentration
		int id = cluster->getId() - 1;
		double conc = gridPointSolution[id];
		// Get its size and diffusion coefficient
		int size = cluster->getSize();
		double coef = cluster->getDiffusionCoefficient();

		// Compute the flux
		newFlux += (double) size * s * coef * conc;
	}

	previousIFlux1D = newFlux;

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);CHKERRQ(ierr);

    PetscFunctionReturn(0);
}

/**
 * This operation sets up a monitor that will call monitorSolve
=======
	// Get the position of the surface
	int surfacePos = solverHandler->getSurfacePosition();

	// Get the network
	auto network = solverHandler->getNetwork();
	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();

	// Get the flux handler to know the flux amplitude.
	auto fluxHandler = solverHandler->getFluxHandler();
	double fluxAmplitude = fluxHandler->getFluxAmplitude();

	// Get the delta time from the previous timestep to this timestep
	double dt = time - previousTime;

	// Compute the prefactor for the probability (arbitrary)
	double prefactor = fluxAmplitude * dt * 0.05;

	// Loop on the grid
	for (xi = xs; xi < xs + xm; xi++) {
		// Skip everything before the surface
		if (xi <= surfacePos)
			continue;

		// Get the pointer to the beginning of the solution data for this grid point
		gridPointSolution = solutionArray[xi];
		// Update the concentration in the network
		network->updateConcentrationsFromArray(gridPointSolution);

		// Get the distance from the surface
		double distance = grid[xi] - grid[surfacePos];

		// Compute the helium density at this grid point
		double heDensity = network->getTotalAtomConcentration();

		// Compute the radius of the bubble from the number of helium
		double nV = heDensity * (grid[xi] - grid[xi - 1]) / 4.0;
		double radius = (sqrt(3.0) / 4.0) * xolotlCore::tungstenLatticeConstant
				+ pow(
						(3.0 * pow(xolotlCore::tungstenLatticeConstant, 3.0)
								* nV) / (8.0 * xolotlCore::pi), (1.0 / 3.0))
				- pow(
						(3.0 * pow(xolotlCore::tungstenLatticeConstant, 3.0))
								/ (8.0 * xolotlCore::pi), (1.0 / 3.0));

		// Check if it should burst
		bool burst = false;
		// If the radius is larger than the distance to the surface, burst
		if (radius > distance)
			burst = true;
		// Add randomness
		double prob = prefactor * (1.0 - (distance - radius) / distance);
		double test = (double) rand() / (double) RAND_MAX;
		if (prob > test)
			burst = true;

		// Burst
		if (burst) {

			std::cout << "bursting at: " << distance << " " << prob << " "
					<< test << std::endl;

			// Get all the helium clusters
			auto clusters = network->getAll(heType);
			// Loop on them to reset their concentration at this grid point
			for (int i = 0; i < clusters.size(); i++) {
				auto cluster = clusters[i];
				int id = cluster->getId() - 1;
				gridPointSolution[id] = 0.0;
			}

			// Get all the HeV clusters
			clusters = network->getAll(heVType);
			// Loop on them to transfer their concentration to the V cluster of the
			// same size at this grid point
			for (int i = 0; i < clusters.size(); i++) {
				auto cluster = clusters[i];
				// Get the V cluster of the same size
				auto comp = cluster->getComposition();
				auto vCluster = network->get(vType, comp[vType]);
				int vId = vCluster->getId() - 1;
				int id = cluster->getId() - 1;
				gridPointSolution[vId] = gridPointSolution[id];
				gridPointSolution[id] = 0.0;
			}

			// Loop on the super clusters to transfer their concentration to the V cluster of the
			// same size at this grid point
			for (int i = 0; i < superClusters.size(); i++) {
				auto cluster = (PSISuperCluster *) superClusters[i];
				// Get the V cluster of the same size
				double numV = cluster->getNumV();
				int truncV = (int) numV;
				auto vCluster = network->get(vType, truncV);
				int vId = vCluster->getId() - 1;
				int id = cluster->getId() - 1;
				double conc = cluster->getTotalConcentration();
				gridPointSolution[vId] = conc * numV / (double) truncV;
				gridPointSolution[id] = 0.0;
				id = cluster->getHeMomentumId() - 1;
				gridPointSolution[id] = 0.0;
				id = cluster->getVMomentumId() - 1;
				gridPointSolution[id] = 0.0;
			}
		}
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

/**
 * This operation sets up different monitors
 *  depending on the options.
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
 * @param ts The time stepper
 * @return A standard PETSc error code
 */
PetscErrorCode setupPetsc1DMonitor(TS ts) {
	PetscErrorCode ierr;

	// Get the process ID
	int procId;
<<<<<<< HEAD
	MPI_Comm_rank(MPI_COMM_WORLD, &procId);
=======
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get xolotlViz handler registry
	auto vizHandlerRegistry = xolotlFactory::getVizHandlerRegistry();

	// Flags to launch the monitors or not
<<<<<<< HEAD
	PetscBool flag2DPlot, flag1DPlot, flagSeries, flagPerf, flagRetention,
			flagStatus, flagMaxClusterConc, flagInterstitial;

	// Check the option -plot_perf
	ierr = PetscOptionsHasName(NULL, "-plot_perf", &flagPerf);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-plot_perf) failed.");

	// Check the option -plot_series
	ierr = PetscOptionsHasName(NULL, "-plot_series", &flagSeries);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-plot_series) failed.");

	// Check the option -plot_1d
	ierr = PetscOptionsHasName(NULL, "-plot_1d", &flag1DPlot);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-plot_1d) failed.");

	// Check the option -plot_2d
	ierr = PetscOptionsHasName(NULL, "-plot_2d", &flag2DPlot);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-plot_2d) failed.");

	// Check the option -helium_retention
	ierr = PetscOptionsHasName(NULL, "-helium_retention", &flagRetention);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-helium_retention) failed.");

	// Check the option -start_stop
	ierr = PetscOptionsHasName(NULL, "-start_stop", &flagStatus);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-start_stop) failed.");

	// Check the option -max_cluster_conc
	ierr = PetscOptionsHasName(NULL, "-max_cluster_conc", &flagMaxClusterConc);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-max_cluster_conc) failed.");

	// Check the option -interstitial_diff
	ierr = PetscOptionsHasName(NULL, "-interstitial_diff", &flagInterstitial);
	checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsHasName (-interstitial_diff) failed.");
=======
	PetscBool flag2DPlot, flag1DPlot, flagSeries, flagPerf, flagHeRetention,
			flagStatus, flagMaxClusterConc, flagCumul, flagMeanSize, flagConc,
			flagXeRetention, flagTRIDYN, flagBoundaryFlux;

	// Check the option -boundary_flux
	ierr = PetscOptionsHasName(NULL, NULL, "-boundary_flux", &flagBoundaryFlux);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-boundary_flux) failed.");

	// Check the option -plot_perf
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_perf", &flagPerf);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-plot_perf) failed.");

	// Check the option -plot_series
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_series", &flagSeries);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-plot_series) failed.");

	// Check the option -plot_1d
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_1d", &flag1DPlot);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-plot_1d) failed.");

	// Check the option -plot_2d
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_2d", &flag2DPlot);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-plot_2d) failed.");

	// Check the option -helium_retention
	ierr = PetscOptionsHasName(NULL, NULL, "-helium_retention",
			&flagHeRetention);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-helium_retention) failed.");

	// Check the option -helium_retention
	ierr = PetscOptionsHasName(NULL, NULL, "-xenon_retention",
			&flagXeRetention);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-xenon_retention) failed.");

	// Check the option -start_stop
	ierr = PetscOptionsHasName(NULL, NULL, "-start_stop", &flagStatus);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-start_stop) failed.");

	// Check the option -max_cluster_conc
	ierr = PetscOptionsHasName(NULL, NULL, "-max_cluster_conc",
			&flagMaxClusterConc);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-max_cluster_conc) failed.");

	// Check the option -helium_cumul
	ierr = PetscOptionsHasName(NULL, NULL, "-helium_cumul", &flagCumul);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-helium_cumul) failed.");

	// Check the option -helium_conc
	ierr = PetscOptionsHasName(NULL, NULL, "-helium_conc", &flagConc);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-helium_conc) failed.");

	// Check the option -mean_size
	ierr = PetscOptionsHasName(NULL, NULL, "-mean_size", &flagMeanSize);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-mean_size) failed.");

	// Check the option -tridyn
	ierr = PetscOptionsHasName(NULL, NULL, "-tridyn", &flagTRIDYN);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: PetscOptionsHasName (-tridyn) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto network = solverHandler->getNetwork();
	const int networkSize = network->size();

<<<<<<< HEAD
	// Set the monitor to save 1D plot of one concentration
=======
	// Compute the fluence for He
	if (flagHeRetention || flagBoundaryFlux) {
		// computeFluence will be called at each timestep
		ierr = TSMonitorSet(ts, computeFluence, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeFluence) failed.");
	}

	// Set the monitor to compute the helium flux at the boundary
	if (flagBoundaryFlux) {
		// computeBoundaryFlux1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeBoundaryFlux1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeBoundaryFlux1D) failed.");

		std::ofstream outputFile;
		outputFile.open("thds.txt");
		outputFile.close();
	}

	// Set the monitor to save the status of the simulation in hdf5 file
	if (flagStatus) {
		// Find the stride to know how often the HDF5 file has to be written
		PetscBool flag;
		ierr = PetscOptionsGetReal(NULL, NULL, "-start_stop", &hdf5Stride1D,
				&flag);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: PetscOptionsGetInt (-start_stop) failed.");
		if (!flag)
			hdf5Stride1D = 1.0;

		PetscInt Mx;
		PetscErrorCode ierr;

		// Get the da from ts
		DM da;
		ierr = TSGetDM(ts, &da);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSGetDM failed.");

		// Get the size of the total grid
		ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE);
		checkPetscError(ierr, "setupPetsc1DMonitor: DMDAGetInfo failed.");

		// Initialize the HDF5 file for all the processes
		xolotlCore::HDF5Utils::initializeFile(hdf5OutputName1D);

		// Get the solver handler
		auto solverHandler = PetscSolver::getSolverHandler();

		// Get the physical grid
		auto grid = solverHandler->getXGrid();

		// Save the header in the HDF5 file
		xolotlCore::HDF5Utils::fillHeader(Mx, grid[1] - grid[0]);

		// Save the network in the HDF5 file
		xolotlCore::HDF5Utils::fillNetwork(solverHandler->getNetworkName());

		// Finalize the HDF5 file
		xolotlCore::HDF5Utils::finalizeFile();

		// startStop1D will be called at each timestep
		ierr = TSMonitorSet(ts, startStop1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (startStop1D) failed.");
	}

	// If the user wants the surface to be able to move
	if (solverHandler->moveSurface()) {

		// Get the last time step written in the HDF5 file
		int tempTimeStep = -2;
		std::string networkName = solverHandler->getNetworkName();
		bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
				networkName, tempTimeStep);

		// Get the interstitial information at the surface if concentrations were stored
		if (hasConcentrations) {
			// Get the interstitial quantity from the HDF5 file
			nInterstitial1D = xolotlCore::HDF5Utils::readNInterstitial1D(
					networkName, tempTimeStep);
			// Get the previous I flux from the HDF5 file
			previousIFlux1D = xolotlCore::HDF5Utils::readPreviousIFlux1D(
					networkName, tempTimeStep);
			// Get the previous time from the HDF5 file
			previousTime = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
		}

		// Compute the sputtering yield
		sputteringYield1D = solverHandler->getSputteringYield();

		// Set the monitor on moving surface
		// monitorMovingSurface1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorMovingSurface1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorMovingSurface1D) failed.");

//		// Uncomment to clear the file where the interstitial will be written
//		std::ofstream outputFile;
//		outputFile.open("interstitialOut.txt");
//		outputFile.close();
	}

	// If the user wants bubble bursting
	if (solverHandler->burstBubbles()) {
		// Set the monitor on the bubble bursting
		// monitorBursting1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorBursting1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorBursting1D) failed.");
		std::srand(time(NULL));
	}

	// Set the monitor to save 1D plot of xenon distribution
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	if (flag1DPlot) {
		// Only the master process will create the plot
		if (procId == 0) {
			// Create a ScatterPlot
			scatterPlot1D = vizHandlerRegistry->getPlot("scatterPlot1D",
					xolotlViz::PlotType::SCATTER);

<<<<<<< HEAD
			// Create and set the label provider
			auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
					"labelProvider");
			labelProvider->axis1Label = "x Position on the Grid";
=======
//			scatterPlot1D->setLogScale();

			// Create and set the label provider
			auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
					"labelProvider");
			labelProvider->axis1Label = "Xenon Size";
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			labelProvider->axis2Label = "Concentration";

			// Give it to the plot
			scatterPlot1D->setLabelProvider(labelProvider);

			// Create the data provider
			auto dataProvider = std::make_shared<xolotlViz::CvsXDataProvider>(
					"dataProvider");

			// Give it to the plot
			scatterPlot1D->setDataProvider(dataProvider);
		}

<<<<<<< HEAD
		// monitorSolve will be called at each timestep
		ierr = TSMonitorSet(ts, monitorScatter1D, NULL, NULL);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorScatter1D) failed.");
=======
		// monitorScatter1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorScatter1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorScatter1D) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Set the monitor to save 1D plot of many concentrations
	if (flagSeries) {
		// Only the master process will create the plot
		if (procId == 0) {
			// Create a ScatterPlot
			seriesPlot1D = vizHandlerRegistry->getPlot("seriesPlot1D",
					xolotlViz::PlotType::SERIES);

			// set the log scale
			seriesPlot1D->setLogScale();

			// Create and set the label provider
			auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
					"labelProvider");
			labelProvider->axis1Label = "x Position on the Grid";
			labelProvider->axis2Label = "Concentration";

			// Give it to the plot
			seriesPlot1D->setLabelProvider(labelProvider);

			// To plot a maximum of 18 clusters of the whole benchmark
			const int loopSize = std::min(18, networkSize);

			// Create a data provider for each cluster in the network
			for (int i = 0; i < loopSize; i++) {
				// Set the name for Identifiable
				std::stringstream dataProviderName;
				dataProviderName << "dataprovider" << i;
				// Create the data provider
<<<<<<< HEAD
				auto dataProvider = std::make_shared<xolotlViz::CvsXDataProvider>(
						dataProviderName.str());
=======
				auto dataProvider =
						std::make_shared<xolotlViz::CvsXDataProvider>(
								dataProviderName.str());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

				// Give it to the plot
				seriesPlot1D->addDataProvider(dataProvider);
			}
		}

		// monitorSeries1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorSeries1D, NULL, NULL);
<<<<<<< HEAD
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorSeries1D) failed.");
=======
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorSeries1D) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Set the monitor to save surface plots of clusters concentration
	// for each depth
	if (flag2DPlot) {
		// Create a SurfacePlot
		surfacePlot1D = vizHandlerRegistry->getPlot("surfacePlot1D",
				xolotlViz::PlotType::SURFACE);

		// Create and set the label provider
		auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
				"labelProvider");
		labelProvider->axis1Label = "He number";
		labelProvider->axis2Label = "V number";
		labelProvider->axis3Label = "Concentration";

		// Give it to the plot
		surfacePlot1D->setLabelProvider(labelProvider);

		// Create the data provider
		auto dataProvider = std::make_shared<xolotlViz::CvsXYDataProvider>(
				"dataProvider");

		// Give it to the plot
		surfacePlot1D->setDataProvider(dataProvider);

		// monitorSurface1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorSurface1D, NULL, NULL);
<<<<<<< HEAD
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorSurface1D) failed.");
=======
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorSurface1D) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	}

	// Set the monitor to save performance plots (has to be in parallel)
	if (flagPerf) {
		// Only the master process will create the plot
		if (procId == 0) {
			// Create a ScatterPlot
			perfPlot = vizHandlerRegistry->getPlot("perfPlot",
					xolotlViz::PlotType::SCATTER);

			// Create and set the label provider
			auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
					"labelProvider");
			labelProvider->axis1Label = "Process ID";
			labelProvider->axis2Label = "Solver Time";

			// Give it to the plot
			perfPlot->setLabelProvider(labelProvider);

			// Create the data provider
			auto dataProvider = std::make_shared<xolotlViz::CvsXDataProvider>(
					"dataProvider");

			// Give it to the plot
			perfPlot->setDataProvider(dataProvider);
		}

		// monitorPerf will be called at each timestep
		ierr = TSMonitorSet(ts, monitorPerf, NULL, NULL);
<<<<<<< HEAD
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorPerf) failed.");
	}

	// Set the monitors to compute the helium fluence for the retention calculation
	if (flagRetention) {
=======
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorPerf) failed.");
	}

	// Initialize indices1D and weights1D if we want to compute the
	// retention or the cumulative value and others
	if (flagMeanSize || flagConc || flagHeRetention) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		// Get all the helium clusters
		auto heClusters = network->getAll(heType);

		// Get all the helium-vacancy clusters
		auto heVClusters = network->getAll(heVType);

		// Loop on the helium clusters
<<<<<<< HEAD
		for (int i = 0; i < heClusters.size(); i++) {
			auto cluster = (PSICluster *) heClusters[i];
			int id = cluster->getId() - 1;
			// Add the Id to the vector
			heIndices1D.push_back(id);
			// Add the number of heliums of this cluster to the weight
			heWeights1D.push_back(cluster->getSize());
		}

		// Loop on the helium-vacancy clusters
		for (int i = 0; i < heVClusters.size(); i++) {
			auto cluster = (PSICluster *) heVClusters[i];
			int id = cluster->getId() - 1;
			// Add the Id to the vector
			heIndices1D.push_back(id);
			// Add the number of heliums of this cluster to the weight
			auto comp = cluster->getComposition();
			heWeights1D.push_back(comp[heType]);
		}

		if (heIndices1D.size() == 0) {
			throw std::string(
					"PetscSolver Exception: Cannot compute the retention because there is no helium "
					"or helium-vacancy cluster in the network.");
		}

		// computeHeliumFluence will be called at each timestep
		ierr = TSMonitorSet(ts, computeHeliumFluence, NULL, NULL);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (computeHeliumFluence) failed.");

		// computeHeliumRetention1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeHeliumRetention1D, NULL, NULL);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (computeHeliumRetention1D) failed.");

//		// Uncomment to clear the file where the retention will be written
//		std::ofstream outputFile;
//		outputFile.open("retentionOut.txt");
//		outputFile.close();
	}

	// Set the monitor to save the status of the simulation in hdf5 file
	if (flagStatus) {
		// Find the stride to know how often the HDF5 file has to be written
		PetscBool flag;
		ierr = PetscOptionsGetInt(NULL, "-start_stop", &hdf5Stride1D, &flag);
		checkPetscError(ierr, "setupPetsc1DMonitor: PetscOptionsGetInt (-start_stop) failed.");
		if (!flag)
			hdf5Stride1D = 1;

		PetscInt Mx;
		PetscErrorCode ierr;

		// Get the da from ts
		DM da;
		ierr = TSGetDM(ts, &da);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSGetDM failed.");

		// Get the size of the total grid
		ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE);
		checkPetscError(ierr, "setupPetsc1DMonitor: DMDAGetInfo failed.");

		// Initialize the HDF5 file for all the processes
		xolotlCore::HDF5Utils::initializeFile(hdf5OutputName1D, networkSize);

		// Get the solver handler
		auto solverHandler = PetscSolver::getSolverHandler();

		// Setup step size variable
		double hx = solverHandler->getStepSizeX();

		// Save the header in the HDF5 file
		xolotlCore::HDF5Utils::fillHeader(Mx, hx);

		// Save the network in the HDF5 file
		xolotlCore::HDF5Utils::fillNetwork(network);

		// Finalize the HDF5 file
		xolotlCore::HDF5Utils::finalizeFile();

		// startStop1D will be called at each timestep
		ierr = TSMonitorSet(ts, startStop1D, NULL, NULL);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (startStop1D) failed.");
	}

	// Set the monitor to output information about when the maximum stable HeV
=======
		for (unsigned int i = 0; i < heClusters.size(); i++) {
			auto cluster = heClusters[i];
			int id = cluster->getId() - 1;
			// Add the Id to the vector
			indices1D.push_back(id);
			// Add the number of heliums of this cluster to the weight
			weights1D.push_back(cluster->getSize());
			radii1D.push_back(cluster->getReactionRadius());
		}

		// Loop on the helium-vacancy clusters
		for (unsigned int i = 0; i < heVClusters.size(); i++) {
			auto cluster = heVClusters[i];
			int id = cluster->getId() - 1;
			// Add the Id to the vector
			indices1D.push_back(id);
			// Add the number of heliums of this cluster to the weight
			auto comp = cluster->getComposition();
			weights1D.push_back(comp[heType]);
			radii1D.push_back(cluster->getReactionRadius());
		}
	}

	// Set the monitor to compute the helium fluence and the retention
	// for the retention calculation
	if (flagHeRetention) {

		// Get the last time step written in the HDF5 file
		int tempTimeStep = -2;
		std::string networkName = solverHandler->getNetworkName();
		bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
				networkName, tempTimeStep);

		// Get the previous time if concentrations were stored and initialize the fluence
		if (hasConcentrations) {
			// Get the previous time from the HDF5 file
			double time = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
			// Initialize the fluence
			auto fluxHandler = solverHandler->getFluxHandler();
			// The length of the time step
			double dt = time;
			// Increment the fluence with the value at this current timestep
			fluxHandler->incrementFluence(dt);
			// Get the previous time from the HDF5 file
			previousTime = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
		}

		// computeHeliumRetention1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeHeliumRetention1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeHeliumRetention1D) failed.");

		// Uncomment to clear the file where the retention will be written
		std::ofstream outputFile;
		outputFile.open("retentionOut.txt");
		outputFile.close();
	}

	// Set the monitor to compute the xenon fluence and the retention
	// for the retention calculation
	if (flagXeRetention) {

		// Get all the xenon clusters
		auto xeClusters = network->getAll(xeType);

		// Loop on the xenon clusters
		for (unsigned int i = 0; i < xeClusters.size(); i++) {
			auto cluster = xeClusters[i];
			int id = cluster->getId() - 1;
			// Add the Id to the vector
			indices1D.push_back(id);
			// Add the number of heliums of this cluster to the weight
			weights1D.push_back(cluster->getSize());
			radii1D.push_back(cluster->getReactionRadius());
		}

		// Get the last time step written in the HDF5 file
		int tempTimeStep = -2;
		std::string networkName = solverHandler->getNetworkName();
		bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
				networkName, tempTimeStep);

		// Get the previous time if concentrations were stored and initialize the fluence
		if (hasConcentrations) {
			// Get the previous time from the HDF5 file
			double time = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
			// Initialize the fluence
			auto fluxHandler = solverHandler->getFluxHandler();
			// The length of the time step
			double dt = time;
			// Increment the fluence with the value at this current timestep
			fluxHandler->incrementFluence(dt);
			// Get the previous time from the HDF5 file
			previousTime = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
		}

		// computeFluence will be called at each timestep
		ierr = TSMonitorSet(ts, computeFluence, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeFluence) failed.");

		// computeXenonRetention1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeXenonRetention1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeXenonRetention1D) failed.");

		// Uncomment to clear the file where the retention will be written
		std::ofstream outputFile;
		outputFile.open("retentionOut.txt");
		outputFile.close();
	}

	// Set the monitor to compute the cumulative helium concentration
	if (flagCumul) {

		// computeCumulativeHelium1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeCumulativeHelium1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeCumulativeHelium1D) failed.");
	}

	// Set the monitor to save text file of the mean helium size
	if (flagMeanSize) {
		// monitorMeanSize1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorMeanSize1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorMeanSize1D) failed.");
	}

	// Set the monitor to output information about when the maximum stable
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// cluster in the network first becomes greater than 1.0e-16
	if (flagMaxClusterConc) {
		// monitorMaxClusterConc1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorMaxClusterConc1D, NULL, NULL);
<<<<<<< HEAD
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorMaxClusterConc1D) failed.");
	}

	// Set the monitor on the outgoing flux of interstitials at the surface
	if (flagInterstitial) {
		// monitorInterstitial1D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorInterstitial1D, NULL, NULL);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorInterstitial1D) failed.");

//		// Uncomment to clear the file where the interstitial flux will be written
//		std::ofstream outputFile;
//		outputFile.open("interstitialOut.txt");
//		outputFile.close();
	}

	// Set the monitor to simply change the previous time to the new time
	if (flagRetention || flagInterstitial) {
		// monitorTime will be called at each timestep
		ierr = TSMonitorSet(ts, monitorTime, NULL, NULL);
		checkPetscError(ierr, "setupPetsc1DMonitor: TSMonitorSet (monitorTime) failed.");
	}
=======
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (monitorMaxClusterConc1D) failed.");
	}

	// Set the monitor to compute the helium concentrations
	if (flagConc) {
		// computeHeliumConc1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeHeliumConc1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeHeliumConc1D) failed.");
	}

	// Set the monitor to output data for TRIDYN
	if (flagTRIDYN) {
		// computeTRIDYN1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeTRIDYN1D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc1DMonitor: TSMonitorSet (computeTRIDYN1D) failed.");
	}

	// Set the monitor to simply change the previous time to the new time
	// monitorTime will be called at each timestep
	ierr = TSMonitorSet(ts, monitorTime, NULL, NULL);
	checkPetscError(ierr,
			"setupPetsc1DMonitor: TSMonitorSet (monitorTime) failed.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	PetscFunctionReturn(0);
}

}

/* end namespace xolotlSolver */
