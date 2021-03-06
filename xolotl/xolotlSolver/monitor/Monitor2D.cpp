// Includes
#include "PetscSolver.h"
#include <xolotlPerf.h>
#include <VizHandlerRegistryFactory.h>
#include <PlotType.h>
#include <CvsXDataProvider.h>
#include <CvsXYDataProvider.h>
#include <LabelProvider.h>
#include <Constants.h>
#include <petscts.h>
#include <petscsys.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <HDF5Utils.h>
#include <PSISuperCluster.h>
#include <NESuperCluster.h>
#include <MathUtils.h>

namespace xolotlSolver {

// Declaration of the functions defined in Monitor.cpp
extern PetscErrorCode checkTimeStep(TS ts);
extern PetscErrorCode monitorTime(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx);
extern PetscErrorCode computeFluence(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx);
extern PetscErrorCode monitorPerf(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx);

// Declaration of the variables defined in Monitor.cpp
extern std::shared_ptr<xolotlViz::IPlot> perfPlot;
extern double previousTime;
extern double timeStepThreshold;

//! How often HDF5 file is written
PetscReal hdf5Stride2D = 0.0;
//! Previous time for HDF5
PetscInt hdf5Previous2D = 0;
//! HDF5 output file name
std::string hdf5OutputName2D = "xolotlStop.h5";
//! The pointer to the 2D plot used in MonitorSurface.
std::shared_ptr<xolotlViz::IPlot> surfacePlot2D;
//! The variable to store the interstitial flux at the previous time step.
std::vector<double> previousIFlux2D;
//! The variable to store the total number of interstitials going through the surface.
std::vector<double> nInterstitial2D;

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "startStop2D")
/**
 * This is a monitoring method that will update an hdf5 file at each time step.
 */
PetscErrorCode startStop2D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declaration
	PetscErrorCode ierr;
	const double ***solutionArray, *gridPointSolution;
	PetscInt xs, xm, Mx, ys, ym, My;

	PetscFunctionBeginUser;

	// Don't do anything if it is not on the stride
<<<<<<< HEAD
<<<<<<< HEAD
	if ((int) (time / hdf5Stride2D) == hdf5Previous2D)
=======
	if ((int) ((time + time / 1000.0) / hdf5Stride2D) == hdf5Previous2D)
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	if ((int) ((time + time / 1000.0) / hdf5Stride2D) == hdf5Previous2D)
>>>>>>> master
		PetscFunctionReturn(0);

	// Update the previous time
	hdf5Previous2D++;

	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID (important when it is running in parallel)
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
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);
	// Get the size of the total grid
<<<<<<< HEAD
<<<<<<< HEAD
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> master
	CHKERRQ(ierr);

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Network size
	const int dof = network->getDOF();
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto& network = solverHandler.getNetwork();

	// Network size
	const int dof = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the vector of positions of the surface
	std::vector<int> surfaceIndices;
	for (PetscInt i = 0; i < My; i++) {
<<<<<<< HEAD
		surfaceIndices.push_back(solverHandler->getSurfacePosition(i));
=======
		surfaceIndices.push_back(solverHandler.getSurfacePosition(i));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Open the already created HDF5 file
	xolotlCore::HDF5Utils::openFile(hdf5OutputName2D);

	// Get the current time step
	double currentTimeStep;
	ierr = TSGetTimeStep(ts, &currentTimeStep);
	CHKERRQ(ierr);

	// Add a concentration sub group
	xolotlCore::HDF5Utils::addConcentrationSubGroup(timestep, time,
			previousTime, currentTimeStep);

	// Write the surface positions and the associated interstitial quantities
	// in the concentration sub group
	xolotlCore::HDF5Utils::writeSurface2D(timestep, surfaceIndices,
			nInterstitial2D, previousIFlux2D);

	// Loop on the full grid
	for (PetscInt j = 0; j < My; j++) {
		for (PetscInt i = 0; i < Mx; i++) {
			// Wait for all the processes
			MPI_Barrier(PETSC_COMM_WORLD);
			// Size of the concentration that will be stored
			int concSize = -1;
			// Vector for the concentrations
			std::vector<std::vector<double> > concVector;

			// If it is the locally owned part of the grid
			if (i >= xs && i < xs + xm && j >= ys && j < ys + ym) {
				// Get the pointer to the beginning of the solution data for this grid point
				gridPointSolution = solutionArray[j][i];

				// Loop on the concentrations
				concVector.clear();
				for (int l = 0; l < dof; l++) {
					if (gridPointSolution[l] > 1.0e-16
							|| gridPointSolution[l] < -1.0e-16) {
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
					MPI_Send(&concSize, 1, MPI_INT, l, 0, PETSC_COMM_WORLD);
				}
			}

			// Else: only receive the conc size
			else {
				MPI_Recv(&concSize, 1, MPI_INT, MPI_ANY_SOURCE, 0,
						PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
			}

			// Skip the grid point if the size is 0
			if (concSize == 0)
				continue;

<<<<<<< HEAD
<<<<<<< HEAD
			// All processes must create the dataset
			xolotlCore::HDF5Utils::addConcentrationDataset(concSize, i, j);

			// If it is the locally owned part of the grid
=======
			// Transfer the data everywhere from the local grid
>>>>>>> master
			if (i >= xs && i < xs + xm && j >= ys && j < ys + ym) {
				// Loop on all the processes
				for (int l = 0; l < worldSize; l++) {
					// Skip its own
					if (l == procId)
						continue;
					// Loop on the size of the vector
					for (int k = 0; k < concSize; k++) {
						// Send both information
						MPI_Send(&concVector[k][0], 1, MPI_DOUBLE, l, 1,
								PETSC_COMM_WORLD);
						MPI_Send(&concVector[k][1], 1, MPI_DOUBLE, l, 2,
								PETSC_COMM_WORLD);
					}
				}
			} else {
				// Receive the data from the local grid so that all processes have the same data
				double index = 0, conc = 0;
				for (int k = 0; k < concSize; k++) {
					std::vector<double> vec;
					MPI_Recv(&index, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1,
							PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
					MPI_Recv(&conc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2,
							PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
					vec.push_back(index);
					vec.push_back(conc);
					concVector.push_back(vec);
				}
			}
<<<<<<< HEAD
=======
			// Transfer the data everywhere from the local grid
			if (i >= xs && i < xs + xm && j >= ys && j < ys + ym) {
				// Loop on all the processes
				for (int l = 0; l < worldSize; l++) {
					// Skip its own
					if (l == procId)
						continue;
					// Loop on the size of the vector
					for (int k = 0; k < concSize; k++) {
						// Send both information
						MPI_Send(&concVector[k][0], 1, MPI_DOUBLE, l, 1,
								PETSC_COMM_WORLD);
						MPI_Send(&concVector[k][1], 1, MPI_DOUBLE, l, 2,
								PETSC_COMM_WORLD);
					}
				}
			} else {
				// Receive the data from the local grid so that all processes have the same data
				double index = 0, conc = 0;
				for (int k = 0; k < concSize; k++) {
					std::vector<double> vec;
					MPI_Recv(&index, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1,
							PETSC_COMM_WORLD,
							MPI_STATUS_IGNORE);
					MPI_Recv(&conc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 2,
							PETSC_COMM_WORLD,
							MPI_STATUS_IGNORE);
					vec.push_back(index);
					vec.push_back(conc);
					concVector.push_back(vec);
				}
			}
=======
>>>>>>> master

			// All processes create the dataset and fill it
			xolotlCore::HDF5Utils::addConcentrationDataset(concSize, i, j);
			xolotlCore::HDF5Utils::fillConcentrations(concVector, i, j);
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
		}
	}

	// Finalize the HDF5 file
	xolotlCore::HDF5Utils::closeFile();

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeHeliumRetention2D")
/**
 * This is a monitoring method that will compute the helium retention
 */
PetscErrorCode computeHeliumRetention2D(TS ts, PetscInt, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
	PetscErrorCode ierr;
	PetscInt xs, xm, ys, ym, Mx, My;

	PetscFunctionBeginUser;

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the flux handler that will be used to compute fluxes.
	auto fluxHandler = solverHandler->getFluxHandler();
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the flux handler that will be used to compute fluxes.
	auto fluxHandler = solverHandler.getFluxHandler();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);
	// Get the size of the total grid
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
	CHKERRQ(ierr);

	// Get the physical grid in the x direction
<<<<<<< HEAD
	auto grid = solverHandler->getXGrid();

	// Setup step size variables
	double hy = solverHandler->getStepSizeY();

	// Get the network
	auto network = solverHandler->getNetwork();
=======
	auto grid = solverHandler.getXGrid();

	// Setup step size variables
	double hy = solverHandler.getStepSizeY();

	// Get the network
	auto& network = solverHandler.getNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the array of concentration
	double ***solutionArray, *gridPointSolution;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Store the concentration over the grid
	double heConcentration = 0.0;

	// Loop on the grid
	for (PetscInt yj = ys; yj < ys + ym; yj++) {
		// Get the surface position
<<<<<<< HEAD
		int surfacePos = solverHandler->getSurfacePosition(yj);
=======
		int surfacePos = solverHandler.getSurfacePosition(yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		for (PetscInt xi = xs; xi < xs + xm; xi++) {

			// Boundary conditions
<<<<<<< HEAD
<<<<<<< HEAD
			if (xi <= surfacePos || xi == grid.size() - 1)
=======
			if (xi <= surfacePos)
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
			if (xi < surfacePos || xi == Mx - 1)
>>>>>>> master
				continue;

			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[yj][xi];

			// Update the concentration in the network
<<<<<<< HEAD
			network->updateConcentrationsFromArray(gridPointSolution);

			// Get the total helium concentration at this grid point
<<<<<<< HEAD
<<<<<<< HEAD
			heConcentration += network->getTotalAtomConcentration() * (grid[xi] - grid[xi - 1]) * hy;
=======
			heConcentration += network->getTotalAtomConcentration()
					* (grid[xi] - grid[xi - 1]) * hy;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
			heConcentration += network->getTotalAtomConcentration()
=======
			network.updateConcentrationsFromArray(gridPointSolution);

			// Get the total helium concentration at this grid point
			heConcentration += network.getTotalAtomConcentration()
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					* (grid[xi + 1] - grid[xi]) * hy;
>>>>>>> master
		}
	}

	// Get the current process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Sum all the concentrations through MPI reduce
	double totalHeConcentration = 0.0;
	MPI_Reduce(&heConcentration, &totalHeConcentration, 1, MPI_DOUBLE, MPI_SUM,
			0, PETSC_COMM_WORLD);

	// Master process
	if (procId == 0) {
		// Get the total size of the grid rescale the concentrations
		PetscInt Mx, My;
		ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
<<<<<<< HEAD
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE);
=======
				PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
				PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
				PETSC_IGNORE);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
		CHKERRQ(ierr);

		// Compute the total surface irradiated by the helium flux
		double surface = (double) My * hy;

		// Rescale the concentration
		totalHeConcentration = totalHeConcentration / surface;

		// Get the fluence
		double heliumFluence = fluxHandler->getFluence();

		// Print the result
		std::cout << "\nTime: " << time << std::endl;
		std::cout << "Helium retention = "
				<< 100.0 * (totalHeConcentration / heliumFluence) << " %"
				<< std::endl;
		std::cout << "Helium mean concentration = " << totalHeConcentration
				<< std::endl;
		std::cout << "Helium fluence = " << heliumFluence << "\n" << std::endl;

		// Uncomment to write the retention and the fluence in a file
		std::ofstream outputFile;
		outputFile.open("retentionOut.txt", ios::app);
		outputFile << heliumFluence << " "
				<< 100.0 * (totalHeConcentration / heliumFluence) << std::endl;
		outputFile.close();
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "computeTRIDYN2D")
/**
 * This is a monitoring method that will compute the data to send to TRIDYN
 */
PetscErrorCode computeTRIDYN2D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	// Initial declarations
	PetscErrorCode ierr;
	PetscInt xs, xm, ys, ym;

	PetscFunctionBeginUser;

	// Get the number of processes
	int worldSize;
	MPI_Comm_size(PETSC_COMM_WORLD, &worldSize);

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the solver handler
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> master
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();
<<<<<<< HEAD
=======
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto& network = solverHandler.getNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);

	// Get the total size of the grid rescale the concentrations
	PetscInt Mx, My;
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
<<<<<<< HEAD
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
	CHKERRQ(ierr);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();
=======
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
	CHKERRQ(ierr);

	// Get the physical grid
<<<<<<< HEAD
	auto grid = solverHandler->getXGrid();
=======
	auto grid = solverHandler.getXGrid();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

	// Get the array of concentration
	double ***solutionArray, *gridPointSolution;
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Create the output file
	std::ofstream outputFile;
	if (procId == 0) {
		std::stringstream name;
		name << "TRIDYN_" << timestep << ".dat";
		outputFile.open(name.str());
	}

	// Loop on the entire grid
	for (int xi = 0; xi < Mx; xi++) {
		// Wait for everybody at each grid point
		MPI_Barrier(PETSC_COMM_WORLD);

		// Set x
<<<<<<< HEAD
		double x = grid[xi];
=======
		double x = grid[xi + 1] - grid[1];
>>>>>>> master

		// Initialize the concentrations at this grid point
		double heLocalConc = 0.0, vLocalConc = 0.0, iLocalConc = 0.0;

		// Loop on the y
		for (PetscInt yj = ys; yj < ys + ym; yj++) {
			// Get the surface position
<<<<<<< HEAD
			int surfacePos = solverHandler->getSurfacePosition(yj);
			// Boundary conditions
			if (xi <= surfacePos)
=======
<<<<<<< HEAD
			int surfacePos = solverHandler->getSurfacePosition(yj);
=======
			int surfacePos = solverHandler.getSurfacePosition(yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Boundary conditions
			if (xi < surfacePos)
>>>>>>> master
				continue;

			// If it is the locally owned part of the grid
			if (xi >= xs && xi < xs + xm) {
				// Get the pointer to the beginning of the solution data for this grid point
				gridPointSolution = solutionArray[yj][xi];

				// Update the concentration in the network
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> master
				network->updateConcentrationsFromArray(gridPointSolution);

				// Get the total helium concentration at this grid point
				heLocalConc += network->getTotalAtomConcentration();
				vLocalConc += network->getTotalVConcentration();
				iLocalConc += network->getTotalIConcentration();
<<<<<<< HEAD
=======
=======
				network.updateConcentrationsFromArray(gridPointSolution);

				// Get the total helium concentration at this grid point
				heLocalConc += network.getTotalAtomConcentration();
				vLocalConc += network.getTotalVConcentration();
				iLocalConc += network.getTotalIConcentration();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
			}
		}

		double heConc = 0.0, vConc = 0.0, iConc = 0.0;
		MPI_Allreduce(&heLocalConc, &heConc, 1, MPI_DOUBLE, MPI_SUM,
				PETSC_COMM_WORLD);
		MPI_Allreduce(&vLocalConc, &vConc, 1, MPI_DOUBLE, MPI_SUM,
				PETSC_COMM_WORLD);
		MPI_Allreduce(&iLocalConc, &iConc, 1, MPI_DOUBLE, MPI_SUM,
				PETSC_COMM_WORLD);

		// The master process writes computes the cumulative value and writes in the file
		if (procId == 0) {
<<<<<<< HEAD
			outputFile << x - grid[solverHandler->getSurfacePosition(0)] << " "
					<< heConc / My << " " << vConc / My << " " << iConc / My
					<< std::endl;
=======
			outputFile
					<< x
<<<<<<< HEAD
							- (grid[solverHandler->getSurfacePosition(0) + 1]
=======
							- (grid[solverHandler.getSurfacePosition(0) + 1]
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
									- grid[1]) << " " << heConc / My << " "
					<< vConc / My << " " << iConc / My << std::endl;
>>>>>>> master
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
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorSurface2D")
/**
 * This is a monitoring method that will save 2D plots of the concentration of
 * a specific cluster at each grid point.
 */
PetscErrorCode monitorSurface2D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
	PetscErrorCode ierr;
	const double ***solutionArray, *gridPointSolution;
	PetscInt xs, xm, Mx, ys, ym, My;
	double x = 0.0, y = 0.0;

	PetscFunctionBeginUser;

	// Don't do anything if it is not on the stride
	if (timestep % 10 != 0)
		PetscFunctionReturn(0);

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
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);
	// Get the size of the total grid
<<<<<<< HEAD
<<<<<<< HEAD
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> master
	CHKERRQ(ierr);

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Get the physical grid in the x direction
	auto grid = solverHandler->getXGrid();

	// Setup step size variables
	double hy = solverHandler->getStepSizeY();
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto& network = solverHandler.getNetwork();

	// Get the physical grid in the x direction
	auto grid = solverHandler.getXGrid();

	// Setup step size variables
	double hy = solverHandler.getStepSizeY();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Choice of the cluster to be plotted
	int iCluster = 19;

	// Create a Point vector to store the data to give to the data provider
	// for the visualization
	auto myPoints = std::make_shared<std::vector<xolotlViz::Point> >();
	// Create a point here so that it is not created and deleted in the loop
	xolotlViz::Point thePoint;

	// Loop on the full grid
	for (PetscInt j = 0; j < My; j++) {
		for (PetscInt i = 0; i < Mx; i++) {
			// If it is the locally owned part of the grid
			if (i >= xs && i < xs + xm && j >= ys && j < ys + ym) {
				// Get the pointer to the beginning of the solution data for this grid point
				gridPointSolution = solutionArray[j][i];
				// Compute x and y
				x = grid[i + 1] - grid[1];
				y = (double) j * hy;

				// If it is procId 0 just store the value in the myPoints vector
				if (procId == 0) {
					// Modify the Point with the gridPointSolution[iCluster] as the value
					// and add it to myPoints
					thePoint.value = gridPointSolution[iCluster];
					thePoint.t = time;
					thePoint.x = x;
					thePoint.y = y;
					myPoints->push_back(thePoint);
				}
				// Else, the values must be sent to procId 0
				else {
					// Send the value of the local position to the master process
					MPI_Send(&x, 1, MPI_DOUBLE, 0, 10, PETSC_COMM_WORLD);
					// Send the value of the local position to the master process
					MPI_Send(&y, 1, MPI_DOUBLE, 0, 11, PETSC_COMM_WORLD);

					// Send the value of the concentration to the master process
					MPI_Send(&gridPointSolution[iCluster], 1, MPI_DOUBLE, 0, 12,
							PETSC_COMM_WORLD);
				}
			}
			// Else if it is NOT the locally owned part of the grid but still procId == 0,
			// it should receive the values for the point and add them to myPoint
			else if (procId == 0) {
				// Get the position
				MPI_Recv(&x, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 10,
						PETSC_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(&y, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 11,
						PETSC_COMM_WORLD, MPI_STATUS_IGNORE);

				// and the concentration
				double conc = 0.0;
				MPI_Recv(&conc, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 12,
						PETSC_COMM_WORLD, MPI_STATUS_IGNORE);

				// Modify the Point with the received values and add it to myPoints
				thePoint.value = conc;
				thePoint.t = time;
				thePoint.x = x;
				thePoint.y = y;
				myPoints->push_back(thePoint);
			}

			// Wait for everybody at each grid point
			MPI_Barrier(PETSC_COMM_WORLD);
		}
	}

	// Plot everything from procId == 0
	if (procId == 0) {
		// Get the data provider and give it the points
		surfacePlot2D->getDataProvider()->setPoints(myPoints);

		// Get the iCluster cluster to have access to its name
<<<<<<< HEAD
		auto reactants = network->getAll();
		auto cluster = reactants->at(iCluster);

		// Change the title of the plot and the name of the data
		std::stringstream title;
		title << cluster->getName();
=======
		auto const& reactants = network.getAll();
		IReactant const& cluster = reactants.at(iCluster);

		// Change the title of the plot and the name of the data
		std::stringstream title;
		title << cluster.getName();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		surfacePlot2D->getDataProvider()->setDataName(title.str());
		title << " concentration";
		surfacePlot2D->plotLabelProvider->titleLabel = title.str();
		// Give the time to the label provider
		std::stringstream timeLabel;
		timeLabel << "time: " << std::setprecision(4) << time << "s";
		surfacePlot2D->plotLabelProvider->timeLabel = timeLabel.str();
		// Get the current time step
		PetscReal currentTimeStep;
		ierr = TSGetTimeStep(ts, &currentTimeStep);
		CHKERRQ(ierr);
		// Give the timestep to the label provider
		std::stringstream timeStepLabel;
		timeStepLabel << "dt: " << std::setprecision(4) << currentTimeStep
				<< "s";
		surfacePlot2D->plotLabelProvider->timeStepLabel = timeStepLabel.str();

		// Render and save in file
		std::stringstream fileName;
<<<<<<< HEAD
		fileName << cluster->getName() << "_surface_TS" << timestep << ".png";
=======
		fileName << cluster.getName() << "_surface_TS" << timestep << ".png";
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		surfacePlot2D->write(fileName.str());
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

/**
 * This is a monitoring method that will compute the flux of interstitials
 * at the surface and move the position of the surface if necessary.
 */
PetscErrorCode monitorMovingSurface2D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *ictx) {
	// Initial declarations
	PetscErrorCode ierr;
	double ***solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi, ys, ym, yj, Mx, My;
	bool surfaceHasMoved = false;

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
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);

	// Get the size of the total grid
<<<<<<< HEAD
<<<<<<< HEAD
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> master
	CHKERRQ(ierr);

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();

	// Get all the interstitial clusters
	auto interstitials = network->getAll("I");
	// Get the single vacancy ID
	auto singleVacancyCluster = network->get(xolotlCore::vType, 1);
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto& network = solverHandler.getNetwork();

	// Get the single vacancy ID
	auto singleVacancyCluster = network.get(Species::V, 1);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	int vacancyIndex = -1;
	if (singleVacancyCluster)
		vacancyIndex = singleVacancyCluster->getId() - 1;

	// Get the physical grid
<<<<<<< HEAD
	auto grid = solverHandler->getXGrid();
=======
	auto grid = solverHandler.getXGrid();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Write the initial surface positions
	if (procId == 0 && xolotlCore::equal(time, 0.0)) {
		std::ofstream outputFile;
		outputFile.open("surface.txt", ios::app);
		outputFile << time << " ";

		// Loop on the possible yj
		for (yj = 0; yj < My; yj++) {
			// Get the position of the surface at yj
<<<<<<< HEAD
			int surfacePos = solverHandler->getSurfacePosition(yj);
=======
			int surfacePos = solverHandler.getSurfacePosition(yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			outputFile << grid[surfacePos + 1] - grid[1] << " ";
		}
		outputFile << std::endl;
		outputFile.close();
	}

<<<<<<< HEAD
=======
	// Write the initial surface positions
	if (procId == 0 && timestep == 0) {
		std::ofstream outputFile;
		outputFile.open("surface.txt", ios::app);
		outputFile << time << " ";

		// Loop on the possible yj
		for (yj = 0; yj < My; yj++) {
			// Get the position of the surface at yj
			int surfacePos = solverHandler->getSurfacePosition(yj);
			outputFile << grid[surfacePos] << " ";
		}
		outputFile << std::endl;
		outputFile.close();
	}

>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	// Setup step size variables
<<<<<<< HEAD
	double hy = solverHandler->getStepSizeY();

	// Get the initial vacancy concentration
	double initialVConc = solverHandler->getInitialVConc();
=======
	double hy = solverHandler.getStepSizeY();

	// Get the initial vacancy concentration
	double initialVConc = solverHandler.getInitialVConc();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the delta time from the previous timestep to this timestep
	double dt = time - previousTime;

	// Loop on the possible yj
	for (yj = 0; yj < My; yj++) {
		// Get the position of the surface at yj
<<<<<<< HEAD
		int surfacePos = solverHandler->getSurfacePosition(yj);
=======
		int surfacePos = solverHandler.getSurfacePosition(yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		xi = surfacePos + 1;

		// Value to now on which processor is the location of the surface,
		// for MPI usage
		int surfaceProc = 0;

		// if xi, yj are on this process
		if (xi >= xs && xi < xs + xm && yj >= ys && yj < ys + ym) {
			// Get the concentrations at xi = surfacePos + 1
			gridPointSolution = solutionArray[yj][xi];

			// Compute the total density of intersitials that escaped from the
			// surface since last timestep using the stored flux
			nInterstitial2D[yj] += previousIFlux2D[yj] * dt;

			// Initialize the value for the flux
			double newFlux = 0.0;

			// Loop on all the interstitial clusters
<<<<<<< HEAD
			for (int i = 0; i < interstitials.size(); i++) {
				// Get the cluster
				auto cluster = interstitials.at(i);
				// Get its id and concentration
				int id = cluster->getId() - 1;
				double conc = gridPointSolution[id];
				// Get its size and diffusion coefficient
				int size = cluster->getSize();
				double coef = cluster->getDiffusionCoefficient();
=======
			for (auto const& iMapItem : network.getAll(ReactantType::I)) {
				// Get the cluster
				auto const& cluster = *(iMapItem.second);
				// Get its id and concentration
				int id = cluster.getId() - 1;
				double conc = gridPointSolution[id];
				// Get its size and diffusion coefficient
				int size = cluster.getSize();
				double coef = cluster.getDiffusionCoefficient();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

				// Factor for finite difference
				double hxLeft = grid[xi + 1] - grid[xi];
				double hxRight = grid[xi + 2] - grid[xi + 1];
				double factor = 2.0 / (hxLeft * (hxLeft + hxRight));
				// Compute the flux going to the left
				newFlux += (double) size * factor * coef * conc * hxLeft;
			}

			// Update the previous flux at this position
			previousIFlux2D[yj] = newFlux;

			// Set the surface processor
			surfaceProc = procId;
		}

		// Get which processor will send the information
		int surfaceId = 0;
		MPI_Allreduce(&surfaceProc, &surfaceId, 1, MPI_INT, MPI_SUM,
				PETSC_COMM_WORLD);

		// Send the information about nInterstitial2D and previousFlux2D
		// to the other processes
		MPI_Bcast(&nInterstitial2D[yj], 1, MPI_DOUBLE, surfaceId,
				PETSC_COMM_WORLD);
		MPI_Bcast(&previousIFlux2D[yj], 1, MPI_DOUBLE, surfaceId,
				PETSC_COMM_WORLD);

		// Now that all the processes have the same value of nInterstitials, compare
		// it to the threshold to now if we should move the surface

		// The density of tungsten is 62.8 atoms/nm3, thus the threshold is
		double threshold = (62.8 - initialVConc) * (grid[xi + 1] - grid[xi]);
		if (nInterstitial2D[yj] > threshold) {
			// The surface is moving
			surfaceHasMoved = true;
			// Compute the number of grid points to move the surface of
			int nGridPoints = (int) (nInterstitial2D[yj] / threshold);

			// Remove the number of interstitials we just transformed in new material
			// from nInterstitial2D
			nInterstitial2D[yj] = nInterstitial2D[yj]
					- threshold * (double) nGridPoints;

			// Compute the new surface position
			surfacePos -= nGridPoints;

			// Throw an exception if the position is negative
			if (surfacePos < 0) {
				throw std::string(
						"\nxolotlSolver::Monitor2D: The surface is trying to go outside of the grid!!");
			}

			// Printing information about the extension of the material
			if (procId == 0) {
				std::cout << "Adding " << nGridPoints
						<< " points to the grid on yj = " << yj << " at time: "
						<< time << " s." << std::endl;
			}

			// Set it in the solver
<<<<<<< HEAD
			solverHandler->setSurfacePosition(surfacePos, yj);
=======
			solverHandler.setSurfacePosition(surfacePos, yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Initialize the vacancy concentration on the new grid points
			// Loop on the new grid points
			while (nGridPoints > 0) {
				// Position of the newly created grid point
				xi = surfacePos + nGridPoints;

				// If xi and yj are on this process
				if (xi >= xs && xi < xs + xm && yj >= ys && yj < ys + ym
						&& vacancyIndex > 0) {
					// Get the concentrations
					gridPointSolution = solutionArray[yj][xi];
					// Initialize the vacancy concentration
					gridPointSolution[vacancyIndex] = initialVConc;
				}

				// Decrease the number of grid points
				--nGridPoints;
			}
		}
	}

	// Reinitialize the modified trap-mutation handler if the surface has moved
	if (surfaceHasMoved) {
		// Get the modified trap-mutation handler to reinitialize it
<<<<<<< HEAD
		auto mutationHandler = solverHandler->getMutationHandler();
		auto advecHandlers = solverHandler->getAdvectionHandlers();
=======
		auto mutationHandler = solverHandler.getMutationHandler();
		auto advecHandlers = solverHandler.getAdvectionHandlers();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Get the vector of positions of the surface
		std::vector<int> surfaceIndices;
		for (PetscInt i = 0; i < My; i++) {
<<<<<<< HEAD
			surfaceIndices.push_back(solverHandler->getSurfacePosition(i));
=======
			surfaceIndices.push_back(solverHandler.getSurfacePosition(i));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}

		mutationHandler->initializeIndex2D(surfaceIndices, network,
				advecHandlers, grid, My, hy);
<<<<<<< HEAD
<<<<<<< HEAD
=======

		// Write the updated surface positions
		if (procId == 0 && timestep == 0) {
=======

		// Write the updated surface positions
		if (procId == 0) {
>>>>>>> master
			std::ofstream outputFile;
			outputFile.open("surface.txt", ios::app);
			outputFile << time << " ";

			// Loop on the possible yj
			for (yj = 0; yj < My; yj++) {
				// Get the position of the surface at yj
<<<<<<< HEAD
				int surfacePos = solverHandler->getSurfacePosition(yj);
				outputFile << grid[surfacePos] << " ";
=======
<<<<<<< HEAD
				int surfacePos = solverHandler->getSurfacePosition(yj);
=======
				int surfacePos = solverHandler.getSurfacePosition(yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
				outputFile << grid[surfacePos + 1] - grid[1] << " ";
>>>>>>> master
			}
			outputFile << std::endl;
			outputFile.close();
		}
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
	}

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorBursting2D")
/**
 * This is a monitoring method that bursts bubbles
 */
<<<<<<< HEAD
<<<<<<< HEAD
PetscErrorCode monitorBursting2D(TS ts, PetscInt, PetscReal time,
		Vec solution, void *) {
=======
PetscErrorCode monitorBursting2D(TS ts, PetscInt, PetscReal time, Vec solution,
		void *) {
>>>>>>> master
	// Initial declarations
	PetscErrorCode ierr;
	double ***solutionArray, *gridPointSolution;
	int xs, xm, xi, ys, ym, yj;
=======
PetscErrorCode monitorBursting2D(TS ts, PetscInt, PetscReal time, Vec solution,
		void *) {
	// Initial declarations
	PetscErrorCode ierr;
	double ***solutionArray, *gridPointSolution;
	PetscInt xs, xm, xi, ys, ym, yj;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

	PetscFunctionBeginUser;

	// Gets the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the da from ts
	DM da;
<<<<<<< HEAD
<<<<<<< HEAD
	ierr = TSGetDM(ts, &da);CHKERRQ(ierr);
=======
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);
>>>>>>> master

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
<<<<<<< HEAD
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);CHKERRQ(ierr);
=======
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the corners of the grid
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	ierr = DMDAGetCorners(da, &xs, &ys, NULL, &xm, &ym, NULL);
	CHKERRQ(ierr);
>>>>>>> master

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();
=======
	auto& solverHandler = PetscSolver::getSolverHandler();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the position of the surface
	int surfacePos = 0;
	// Setup step size variables
<<<<<<< HEAD
	double hy = solverHandler->getStepSizeY();

	// Get the network
	auto network = solverHandler->getNetwork();
	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);

	// Get the physical grid
	auto grid = solverHandler->getXGrid();

	// Get the flux handler to know the flux amplitude.
	auto fluxHandler = solverHandler->getFluxHandler();
=======
	double hy = solverHandler.getStepSizeY();

	// Get the network
	auto& network = solverHandler.getNetwork();

	// Get the physical grid
	auto grid = solverHandler.getXGrid();

	// Get the flux handler to know the flux amplitude.
	auto fluxHandler = solverHandler.getFluxHandler();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	double fluxAmplitude = fluxHandler->getFluxAmplitude();

	// Get the delta time from the previous timestep to this timestep
	double dt = time - previousTime;

	// Compute the prefactor for the probability (arbitrary)
<<<<<<< HEAD
<<<<<<< HEAD
	double prefactor = fluxAmplitude * dt * 0.05;
=======
	double prefactor = fluxAmplitude * dt * 0.1;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	double prefactor = fluxAmplitude * dt * 0.1;
>>>>>>> master

	// Loop on the grid
	for (yj = ys; yj < ys + ym; yj++) {
		// Get the surface position
<<<<<<< HEAD
		surfacePos = solverHandler->getSurfacePosition(yj);
=======
		surfacePos = solverHandler.getSurfacePosition(yj);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		for (xi = xs; xi < xs + xm; xi++) {
			// Skip everything before the surface
<<<<<<< HEAD
<<<<<<< HEAD
			if (xi <= surfacePos) continue;
=======
			if (xi <= surfacePos)
				continue;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
			if (xi < surfacePos)
				continue;
>>>>>>> master

			// Get the pointer to the beginning of the solution data for this grid point
			gridPointSolution = solutionArray[yj][xi];
			// Update the concentration in the network
<<<<<<< HEAD
			network->updateConcentrationsFromArray(gridPointSolution);
=======
			network.updateConcentrationsFromArray(gridPointSolution);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Get the distance from the surface
			double distance = grid[xi + 1] - grid[surfacePos + 1];

			// Compute the helium density at this grid point
<<<<<<< HEAD
			double heDensity = network->getTotalAtomConcentration();
=======
			double heDensity = network.getTotalAtomConcentration();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Compute the radius of the bubble from the number of helium
<<<<<<< HEAD
<<<<<<< HEAD
			double nV = heDensity * (grid[xi] - grid[xi-1]) * hy / 4.0;
			double radius = (sqrt(3.0) / 4.0) * xolotlCore::tungstenLatticeConstant
					+ pow(
							(3.0 * pow(xolotlCore::tungstenLatticeConstant, 3.0) * nV)
									/ (8.0 * xolotlCore::pi), (1.0 / 3.0))
					- pow(
							(3.0 * pow(xolotlCore::tungstenLatticeConstant, 3.0))
									/ (8.0 * xolotlCore::pi), (1.0 / 3.0));
=======
			double nV = heDensity * (grid[xi] - grid[xi - 1]) * hy / 4.0;
=======
			double nV = heDensity * (grid[xi + 1] - grid[xi]) * hy / 4.0;
>>>>>>> master
			double radius =
					(sqrt(3.0) / 4.0) * xolotlCore::tungstenLatticeConstant
							+ pow(
									(3.0
											* pow(
													xolotlCore::tungstenLatticeConstant,
													3.0) * nV)
											/ (8.0 * xolotlCore::pi),
									(1.0 / 3.0))
							- pow(
									(3.0
											* pow(
													xolotlCore::tungstenLatticeConstant,
													3.0))
											/ (8.0 * xolotlCore::pi),
									(1.0 / 3.0));
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master

			// Check if it should burst
			bool burst = false;
			// If the radius is larger than the distance to the surface, burst
<<<<<<< HEAD
<<<<<<< HEAD
			if (radius > distance) burst = true;
			// Add randomness
			double prob = prefactor * (1.0 - (distance - radius) / distance);
			double test = (double) rand() / (double) RAND_MAX;
			if (prob > test) burst = true;
=======
			if (radius > distance)
				burst = true;
			// Add randomness
			double prob = prefactor * (1.0 - (distance - radius) / distance);
			double test = (double) rand() / (double) RAND_MAX;
			if (prob > test)
				burst = true;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
			if (radius > distance)
				burst = true;
			// Add randomness
			double prob = prefactor * (1.0 - (distance - radius) / distance);
			double test = (double) rand() / (double) RAND_MAX;
			if (prob > test)
				burst = true;
>>>>>>> master

			// Burst
			if (burst) {

<<<<<<< HEAD
<<<<<<< HEAD
				std::cout << "bursting at: " << yj << " " << distance << " " << prob << " " << test << std::endl;
=======
				std::cout << "bursting at: " << yj << " " << distance << " "
						<< prob << " " << test << std::endl;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
				std::cout << "bursting at: " << yj << " " << distance << " "
						<< prob << " " << test << std::endl;
>>>>>>> master

<<<<<<< HEAD
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
=======
				// Consider each He to reset their concentration at this grid point
				for (auto const& heMapItem : network.getAll(ReactantType::He)) {
					auto const& cluster = *(heMapItem.second);

					int id = cluster.getId() - 1;
					gridPointSolution[id] = 0.0;
				}

				// Consider each HeV cluster to transfer their concentration to the V cluster of the
				// same size at this grid point
				for (auto const& heVMapItem : network.getAll(ReactantType::HeV)) {
					auto const& cluster = *(heVMapItem.second);

					// Get the V cluster of the same size
					auto const & comp = cluster.getComposition();
					auto vCluster = network.get(Species::V,
							comp[toCompIdx(Species::V)]);
					int vId = vCluster->getId() - 1;
					int id = cluster.getId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					gridPointSolution[vId] += gridPointSolution[id];
					gridPointSolution[id] = 0.0;
				}

				// Loop on the super clusters to transfer their concentration to the V cluster of the
				// same size at this grid point
<<<<<<< HEAD
				for (int i = 0; i < superClusters.size(); i++) {
					auto cluster = (PSISuperCluster *) superClusters[i];

					// Get its boundaries
					auto boundaries = cluster->getBoundaries();
					// Loop on the V boundaries
					for (int j = boundaries[2]; j <= boundaries[3]; j++) {
						// Get the total concentration at this v
						double conc = cluster->getIntegratedVConcentration(j);
						// Get the corresponding V cluster and its Id
						auto vCluster = network->get(vType, j);
=======
				for (auto const& superMapItem : network.getAll(
						ReactantType::PSISuper)) {
					auto const& cluster =
							static_cast<PSISuperCluster&>(*(superMapItem.second));

					// Loop on the V boundaries
					for (auto const& j : cluster.getVBounds()) {
						// Get the total concentration at this v
						double conc = cluster.getIntegratedVConcentration(j);
						// Get the corresponding V cluster and its Id
						auto vCluster = network.get(Species::V, j);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
						int vId = vCluster->getId() - 1;
						// Add the concentration
						gridPointSolution[vId] += conc;
					}

					// Reset the super cluster concentration
<<<<<<< HEAD
					int id = cluster->getId() - 1;
					gridPointSolution[id] = 0.0;
					id = cluster->getHeMomentumId() - 1;
					gridPointSolution[id] = 0.0;
					id = cluster->getVMomentumId() - 1;
=======
					int id = cluster.getId() - 1;
					gridPointSolution[id] = 0.0;
					id = cluster.getHeMomentumId() - 1;
					gridPointSolution[id] = 0.0;
					id = cluster.getVMomentumId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					gridPointSolution[id] = 0.0;
				}
			}
		}
	}

	// Restore the solutionArray
<<<<<<< HEAD
<<<<<<< HEAD
	ierr = DMDAVecRestoreArrayDOF(da, solution, &solutionArray);CHKERRQ(ierr);
=======
	ierr = DMDAVecRestoreArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	ierr = DMDAVecRestoreArrayDOF(da, solution, &solutionArray);
	CHKERRQ(ierr);
>>>>>>> master

	PetscFunctionReturn(0);
}

/**
 * This operation sets up different monitors
 *  depending on the options.
 * @param ts The time stepper
 * @return A standard PETSc error code
 */
PetscErrorCode setupPetsc2DMonitor(TS ts) {
	PetscErrorCode ierr;

	// Get the process ID
	int procId;
	MPI_Comm_rank(PETSC_COMM_WORLD, &procId);

	// Get the xolotlViz handler registry
	auto vizHandlerRegistry = xolotlFactory::getVizHandlerRegistry();

	// Flags to launch the monitors or not
<<<<<<< HEAD
<<<<<<< HEAD
	PetscBool flagPerf, flagRetention, flagStatus, flag2DPlot;
=======
	PetscBool flagPerf, flagRetention, flagStatus, flag2DPlot, flagTRIDYN;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	PetscBool flagCheck, flagPerf, flagRetention, flagStatus, flag2DPlot,
			flagTRIDYN;

	// Check the option -check_collapse
	ierr = PetscOptionsHasName(NULL, NULL, "-check_collapse", &flagCheck);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: PetscOptionsHasName (-check_collapse) failed.");
>>>>>>> master

	// Check the option -plot_perf
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_perf", &flagPerf);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: PetscOptionsHasName (-plot_perf) failed.");

	// Check the option -plot_2d
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_2d", &flag2DPlot);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: PetscOptionsHasName (-plot_2d) failed.");

	// Check the option -helium_retention
	ierr = PetscOptionsHasName(NULL, NULL, "-helium_retention", &flagRetention);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: PetscOptionsHasName (-helium_retention) failed.");

	// Check the option -start_stop
	ierr = PetscOptionsHasName(NULL, NULL, "-start_stop", &flagStatus);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: PetscOptionsHasName (-start_stop) failed.");

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
	// Check the option -tridyn
	ierr = PetscOptionsHasName(NULL, NULL, "-tridyn", &flagTRIDYN);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: PetscOptionsHasName (-tridyn) failed.");

<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto network = solverHandler->getNetwork();
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto& network = solverHandler.getNetwork();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);
	checkPetscError(ierr, "setupPetsc2DMonitor: TSGetDM failed.");

	// Get the total size of the grid
	PetscInt Mx, My;
<<<<<<< HEAD
<<<<<<< HEAD
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE);
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
			PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, &My, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
	PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE);
>>>>>>> master
	CHKERRQ(ierr);
	checkPetscError(ierr, "setupPetsc2DMonitor: DMDAGetInfo failed.");

	// Set the post step processing to stop the solver if the time step collapses
	if (flagCheck) {
		// Find the threshold
		PetscBool flag;
		ierr = PetscOptionsGetReal(NULL, NULL, "-check_collapse",
				&timeStepThreshold, &flag);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: PetscOptionsGetInt (-check_collapse) failed.");
		if (!flag)
			timeStepThreshold = 1.0e-16;

		// Set the post step process that tells the solver when to stop if the time step collapse
		ierr = TSSetPostStep(ts, checkTimeStep);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSSetPostStep (checkTimeStep) failed.");
	}

	// Set the monitor to save the status of the simulation in hdf5 file
	if (flagStatus) {
		// Find the stride to know how often the HDF5 file has to be written
		PetscBool flag;
		ierr = PetscOptionsGetReal(NULL, NULL, "-start_stop", &hdf5Stride2D,
				&flag);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: PetscOptionsGetInt (-start_stop) failed.");
		if (!flag)
			hdf5Stride2D = 1.0;

<<<<<<< HEAD
<<<<<<< HEAD
		// Initialize the HDF5 file for all the processes
		xolotlCore::HDF5Utils::initializeFile(hdf5OutputName2D);

		// Get the solver handler
		auto solverHandler = PetscSolver::getSolverHandler();

		// Get the physical grid in the x direction
		auto grid = solverHandler->getXGrid();

		// Setup step size variables
		double hy = solverHandler->getStepSizeY();

		// Save the header in the HDF5 file
		xolotlCore::HDF5Utils::fillHeader(Mx, grid[1] - grid[0], My, hy);

		// Save the network in the HDF5 file
		xolotlCore::HDF5Utils::fillNetwork(solverHandler->getNetworkName());

		// Finalize the HDF5 file
		xolotlCore::HDF5Utils::finalizeFile();
=======
		// Don't do anything if both files have the same name
		if (hdf5OutputName2D != solverHandler->getNetworkName()) {
=======
		// Don't do anything if both files have the same name
<<<<<<< HEAD
		if (hdf5OutputName2D != solverHandler->getNetworkName()) {
=======
		if (hdf5OutputName2D != solverHandler.getNetworkName()) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

			// Initialize the HDF5 file for all the processes
			xolotlCore::HDF5Utils::initializeFile(hdf5OutputName2D);

			// Get the solver handler
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> master
			auto solverHandler = PetscSolver::getSolverHandler();

			// Get the physical grid in the x direction
			auto grid = solverHandler->getXGrid();

			// Setup step size variables
			double hy = solverHandler->getStepSizeY();
<<<<<<< HEAD
=======
=======
			auto& solverHandler = PetscSolver::getSolverHandler();

			// Get the physical grid in the x direction
			auto grid = solverHandler.getXGrid();

			// Setup step size variables
			double hy = solverHandler.getStepSizeY();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

			// Save the header in the HDF5 file
			xolotlCore::HDF5Utils::fillHeader(Mx, grid[1] - grid[0], My, hy);

			// Save the network in the HDF5 file
<<<<<<< HEAD
			if (!solverHandler->getNetworkName().empty())
				xolotlCore::HDF5Utils::fillNetwork(
						solverHandler->getNetworkName());
=======
<<<<<<< HEAD
			if (!solverHandler->getNetworkName().empty())
				xolotlCore::HDF5Utils::fillNetwork(
						solverHandler->getNetworkName());
=======
			if (!solverHandler.getNetworkName().empty())
				xolotlCore::HDF5Utils::fillNetwork(
						solverHandler.getNetworkName());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

			// Finalize the HDF5 file
			xolotlCore::HDF5Utils::finalizeFile();
		}
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master

		// startStop2D will be called at each timestep
		ierr = TSMonitorSet(ts, startStop2D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (startStop2D) failed.");
	}

	// If the user wants the surface to be able to move
<<<<<<< HEAD
	if (solverHandler->moveSurface()) {
=======
	if (solverHandler.moveSurface()) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Initialize nInterstitial2D and previousIFlux2D before monitoring the
		// interstitial flux
		for (PetscInt j = 0; j < My; j++) {
			nInterstitial2D.push_back(0.0);
			previousIFlux2D.push_back(0.0);
		}

		// Get the last time step written in the HDF5 file
		int tempTimeStep = -2;
<<<<<<< HEAD
		std::string networkName = solverHandler->getNetworkName();
<<<<<<< HEAD
<<<<<<< HEAD
		bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
				networkName, tempTimeStep);
=======
=======
=======
		std::string networkName = solverHandler.getNetworkName();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
		bool hasConcentrations = false;
		if (!networkName.empty())
			hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
					networkName, tempTimeStep);
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master

		// Get the interstitial information at the surface if concentrations were stored
		if (hasConcentrations) {
			// Get the interstitial quantity from the HDF5 file
			nInterstitial2D = xolotlCore::HDF5Utils::readNInterstitial2D(
					networkName, tempTimeStep);
			// Get the previous I flux from the HDF5 file
			previousIFlux2D = xolotlCore::HDF5Utils::readPreviousIFlux2D(
					networkName, tempTimeStep);
			// Get the previous time from the HDF5 file
			previousTime = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
		}

		// Set the monitor on the outgoing flux of interstitials at the surface
		// monitorMovingSurface2D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorMovingSurface2D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (monitorMovingSurface2D) failed.");
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master

		// Clear the file where the surface will be written
		std::ofstream outputFile;
		outputFile.open("surface.txt");
		outputFile.close();
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
	}

	// If the user wants bubble bursting
<<<<<<< HEAD
	if (solverHandler->burstBubbles()) {
=======
	if (solverHandler.burstBubbles()) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Set the monitor on the bubble bursting
		// monitorBursting2D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorBursting2D, NULL, NULL);
<<<<<<< HEAD
<<<<<<< HEAD
		checkPetscError(ierr, "setupPetsc2DMonitor: TSMonitorSet (monitorBursting2D) failed.");
		std::srand (time(NULL) + procId);
=======
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (monitorBursting2D) failed.");
		std::srand(time(NULL) + procId);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (monitorBursting2D) failed.");
		std::srand(time(NULL) + procId);
>>>>>>> master
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
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (monitorPerf) failed.");
	}

	// Set the monitor to compute the helium fluence for the retention calculation
	if (flagRetention) {

		// Get the last time step written in the HDF5 file
		int tempTimeStep = -2;
<<<<<<< HEAD
		std::string networkName = solverHandler->getNetworkName();
<<<<<<< HEAD
<<<<<<< HEAD
		bool hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
				networkName, tempTimeStep);
=======
=======
=======
		std::string networkName = solverHandler.getNetworkName();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master
		bool hasConcentrations = false;
		if (!networkName.empty())
			hasConcentrations = xolotlCore::HDF5Utils::hasConcentrationGroup(
					networkName, tempTimeStep);
<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master

		// Get the previous time if concentrations were stored and initialize the fluence
		if (hasConcentrations) {
			// Get the previous time from the HDF5 file
			double time = xolotlCore::HDF5Utils::readPreviousTime(networkName,
					tempTimeStep);
			// Initialize the fluence
<<<<<<< HEAD
			auto fluxHandler = solverHandler->getFluxHandler();
=======
			auto fluxHandler = solverHandler.getFluxHandler();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
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
				"setupPetsc2DMonitor: TSMonitorSet (computeFluence) failed.");

		// computeHeliumRetention2D will be called at each timestep
		ierr = TSMonitorSet(ts, computeHeliumRetention2D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (computeHeliumRetention2D) failed.");

		// Uncomment to clear the file where the retention will be written
		std::ofstream outputFile;
		outputFile.open("retentionOut.txt");
		outputFile.close();
	}

	// Set the monitor to save surface plots of clusters concentration
	if (flag2DPlot) {
		// Only the master process will create the plot
		if (procId == 0) {
			// Create a SurfacePlot
			surfacePlot2D = vizHandlerRegistry->getPlot("surfacePlot2D",
					xolotlViz::PlotType::SURFACE);

			// Create and set the label provider
			auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
					"labelProvider");
			labelProvider->axis1Label = "Depth (nm)";
			labelProvider->axis2Label = "Y (nm)";
			labelProvider->axis3Label = "Concentration";

			// Give it to the plot
			surfacePlot2D->setLabelProvider(labelProvider);

			// Create the data provider
			auto dataProvider = std::make_shared<xolotlViz::CvsXYDataProvider>(
					"dataProvider");

			// Give it to the plot
			surfacePlot2D->setDataProvider(dataProvider);
		}

		// monitorSurface2D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorSurface2D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (monitorSurface2D) failed.");
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> master
	// Set the monitor to output data for TRIDYN
	if (flagTRIDYN) {
		// computeTRIDYN1D will be called at each timestep
		ierr = TSMonitorSet(ts, computeTRIDYN2D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc2DMonitor: TSMonitorSet (computeTRIDYN2D) failed.");
	}

<<<<<<< HEAD
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
>>>>>>> master
	// Set the monitor to simply change the previous time to the new time
	// monitorTime will be called at each timestep
	ierr = TSMonitorSet(ts, monitorTime, NULL, NULL);
	checkPetscError(ierr,
			"setupPetsc2DMonitor: TSMonitorSet (monitorTime) failed.");

	PetscFunctionReturn(0);
}

}

/* end namespace xolotlSolver */
