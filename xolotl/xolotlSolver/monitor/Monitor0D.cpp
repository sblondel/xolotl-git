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
#include <NESuperCluster.h>
#include <PSISuperCluster.h>
<<<<<<< HEAD
#include <NEClusterReactionNetwork.h>
#include <PSIClusterReactionNetwork.h>
=======
#include <FeSuperCluster.h>
#include <NEClusterReactionNetwork.h>
#include <PSIClusterReactionNetwork.h>
#include <FeClusterReactionNetwork.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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

//! The pointer to the plot used in monitorScatter0D.
std::shared_ptr<xolotlViz::IPlot> scatterPlot0D;
//! How often HDF5 file is written
PetscReal hdf5Stride0D = 0.0;
//! Previous time for HDF5
PetscInt hdf5Previous0D = 0;
//! HDF5 output file name
std::string hdf5OutputName0D = "xolotlStop.h5";
<<<<<<< HEAD
// Declare the vector that will store the Id of the vacancy clusters
std::vector<int> indices0D;
// Declare the vector that will store the weight of the vacancy clusters
// (their V composition)
std::vector<int> weights0D;
// Declare the vector that will store the radii of bubbles
std::vector<double> radii0D;
=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "startStop0D")
/**
 * This is a monitoring method that update an hdf5 file at each time step.
 */
PetscErrorCode startStop0D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declaration
	PetscErrorCode ierr;
	const double **solutionArray, *gridPointSolution;

	PetscFunctionBeginUser;

	// Don't do anything if it is not on the stride
<<<<<<< HEAD
<<<<<<< HEAD
	if ((int) (time / hdf5Stride0D) == hdf5Previous0D)
=======
	if ((int) ((time + time / 1000.0) / hdf5Stride0D) == hdf5Previous0D)
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
	if ((int) ((time + time / 1000.0) / hdf5Stride0D) == hdf5Previous0D)
>>>>>>> master
		PetscFunctionReturn(0);

	// Update the previous time
	hdf5Previous0D++;

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network and dof
	auto network = solverHandler->getNetwork();
	const int dof = network->getDOF();
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network and dof
	auto& network = solverHandler.getNetwork();
	const int dof = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Open the already created HDF5 file
	xolotlCore::HDF5Utils::openFile(hdf5OutputName0D);

	// Get the current time step
	double currentTimeStep;
	ierr = TSGetTimeStep(ts, &currentTimeStep);
	CHKERRQ(ierr);

	// Add a concentration sub group
	xolotlCore::HDF5Utils::addConcentrationSubGroup(timestep, time,
			previousTime, currentTimeStep);

	// Size of the concentration that will be stored
	int concSize = -1;
	// Vector for the concentrations
	std::vector<std::vector<double> > concVector;

	// Get the pointer to the beginning of the solution data for this grid point
	gridPointSolution = solutionArray[0];

	// Loop on the concentrations
	concVector.clear();
	for (int l = 0; l < dof; l++) {
		if (gridPointSolution[l] > 1.0e-16 || gridPointSolution[l] < -1.0e-16) {
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

	if (concSize > 0) {
		// All processes must create the dataset
		xolotlCore::HDF5Utils::addConcentrationDataset(concSize, 0);

		// Fill the dataset
		xolotlCore::HDF5Utils::fillConcentrations(concVector, 0);
	}

	// Finalize the HDF5 file
	xolotlCore::HDF5Utils::closeFile();

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorScatter0D")
/**
 * This is a monitoring method that will save 1D plots of the xenon concentration
 * distribution.
 */
PetscErrorCode monitorScatter0D(TS ts, PetscInt timestep, PetscReal time,
		Vec solution, void *) {
	// Initial declarations
	PetscErrorCode ierr;
	double **solutionArray, *gridPointSolution;

	PetscFunctionBeginUser;

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

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto network = solverHandler->getNetwork();
	int networkSize = network->size();
	auto superClusters = network->getAll(NESuperType);
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto& network = solverHandler.getNetwork();
	int networkSize = network.size();
	auto& superClusters = network.getAll(ReactantType::NESuper);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Create a Point vector to store the data to give to the data provider
	// for the visualization
	auto myPoints = std::make_shared<std::vector<xolotlViz::Point> >();

	// Get the pointer to the beginning of the solution data for this grid point
	gridPointSolution = solutionArray[0];

	// Update the concentration in the network
<<<<<<< HEAD
	network->updateConcentrationsFromArray(gridPointSolution);
=======
	network.updateConcentrationsFromArray(gridPointSolution);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

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
<<<<<<< HEAD
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
=======
	// Loop on the super clusters
	for (auto const& superMapItem : superClusters) {
		// Get the cluster
		auto const& cluster =
				static_cast<NESuperCluster&>(*(superMapItem.second));
		// Get the width
		int width = cluster.getSectionWidth();
		// Loop on the width
		for (int k = 0; k < width; k++) {
			// Compute the distance
			double dist = cluster.getDistance(nXe + k);
			// Create a Point with the concentration[i] as the value
			// and add it to myPoints
			xolotlViz::Point aPoint;
			aPoint.value = cluster.getConcentration(dist);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			aPoint.t = time;
			aPoint.x = (double) nXe + k;
			myPoints->push_back(aPoint);
		}

		// update nXe
		nXe += width;
	}

	// Get the data provider and give it the points
	scatterPlot0D->getDataProvider()->setPoints(myPoints);

	// Change the title of the plot and the name of the data
	std::stringstream title;
	title << "Size Distribution";
	scatterPlot0D->getDataProvider()->setDataName(title.str());
	scatterPlot0D->plotLabelProvider->titleLabel = title.str();
	// Give the time to the label provider
	std::stringstream timeLabel;
	timeLabel << "time: " << std::setprecision(4) << time << "s";
	scatterPlot0D->plotLabelProvider->timeLabel = timeLabel.str();
	// Get the current time step
	PetscReal currentTimeStep;
	ierr = TSGetTimeStep(ts, &currentTimeStep);
	CHKERRQ(ierr);
	// Give the timestep to the label provider
	std::stringstream timeStepLabel;
	timeStepLabel << "dt: " << std::setprecision(4) << currentTimeStep << "s";
	scatterPlot0D->plotLabelProvider->timeStepLabel = timeStepLabel.str();

	// Render and save in file
	std::stringstream fileName;
	fileName << "Scatter_TS" << timestep << ".png";
	scatterPlot0D->write(fileName.str());

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

#undef __FUNCT__
<<<<<<< HEAD
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorMeanSize0D")
/**
 * This is a monitoring method that will create files with the mean
 * vacancy size at each time step.
 */
PetscErrorCode monitorMeanSize0D(TS ts, PetscInt timestep, PetscReal time,
=======
#define __FUNCT__ Actual__FUNCT__("xolotlSolver", "monitorBubble0D")
/**
 * This is a monitoring method that will create files with the mean
 * concentration of each bubble at each time step.
 */
PetscErrorCode monitorBubble0D(TS ts, PetscInt timestep, PetscReal time,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		Vec solution, void *ictx) {
	// Initial declaration
	PetscErrorCode ierr;
	double **solutionArray, *gridPointSolution;

	PetscFunctionBeginUser;

<<<<<<< HEAD
	// Don't do anything if it is not on the stride
	if (timestep % 10 != 0)
		PetscFunctionReturn(0);
=======
//	// Don't do anything if it is not on the stride
//	if (timestep % 10 != 0)
//		PetscFunctionReturn(0);
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

	// Get the da from ts
	DM da;
	ierr = TSGetDM(ts, &da);
	CHKERRQ(ierr);

	// Get the solutionArray
	ierr = DMDAVecGetArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	// Get the solver handler
<<<<<<< HEAD
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto network = solverHandler->getNetwork();
	int dof = network->getDOF();
<<<<<<< HEAD
=======
	auto reactants = network->getAll();
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

	// Get all the super clusters
	auto superClusters = network->getAll(PSISuperType);
=======
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network
	auto& network = solverHandler.getNetwork();
	int dof = network.getDOF();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Create the output file
	std::ofstream outputFile;
	std::stringstream name;
<<<<<<< HEAD
	name << "voidDiam_" << timestep << ".dat";
=======
	name << "hydrogen_" << timestep << ".dat";
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
	outputFile.open(name.str());

	double constantMulti = xolotlCore::pi
			/ std::pow(xolotlCore::tungstenLatticeConstant, 3.0);

	// Get the pointer to the beginning of the solution data for this grid point
	gridPointSolution = solutionArray[0];

<<<<<<< HEAD
//			for (int i = 0; i < dof; i++) {
//				std::cout << i << " " << gridPointSolution[i] << std::endl;
//			}

	// Update the concentration in the network
	network->updateConcentrationsFromArray(gridPointSolution);
=======
	name << "bubble_" << timestep << ".dat";
	outputFile.open(name.str());

	// Get the pointer to the beginning of the solution data for this grid point
	gridPointSolution = solutionArray[0];

	// Update the concentration in the network
	network.updateConcentrationsFromArray(gridPointSolution);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Initialize the total helium and concentration before looping
	double concTot = 0.0, heliumTot = 0.0;

<<<<<<< HEAD
	// Loop on all the indices to compute the mean
	for (int i = 0; i < indices0D.size(); i++) {
		outputFile << 2.0 * radii0D[i] << " "
				<< gridPointSolution[indices0D[i]] * constantMulti * 4.0
						* radii0D[i] * radii0D[i] << std::endl;
	}

=======
	for (int i = 0; i < dof - 1; i++) {
		auto cluster = reactants->at(i);
		auto comp = cluster->getComposition();
		outputFile << comp[tType] << " " << comp[dType] << " " << comp[heType] << " " << comp[vType] << " "
				<< gridPointSolution[i] << std::endl;
	}

//	// Update the concentration in the network
//	network->updateConcentrationsFromArray(gridPointSolution);
//
//	// Initialize the total helium and concentration before looping
//	double concTot = 0.0, heliumTot = 0.0;
//
//	// Loop on all the indices to compute the mean
//	for (int i = 0; i < indices0D.size(); i++) {
//		outputFile << 2.0 * radii0D[i] << " "
//				<< gridPointSolution[indices0D[i]] * constantMulti * 4.0
//						* radii0D[i] * radii0D[i] << std::endl;
//	}

>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
//	// Loop on the super clusters
//	for (int l = 0; l < superClusters.size(); l++) {
//		// Get the super cluster
//		auto superCluster = (PSISuperCluster *) superClusters[l];
//		// Get its diameter
//		double diam = 2.0 * superCluster->getReactionRadius();
//		// Get its concentration
//		double conc = superCluster->getTotalConcentration()
//				/ (double) superCluster->getNTot();
//		outputFile << diam << " " << conc * constantMulti * diam * diam
//				<< std::endl;
//	}

=======
	// Consider each super cluster.
	for (auto const& superMapItem : network.getAll(ReactantType::FeSuper)) {
		// Get the super cluster
		auto const& superCluster =
				static_cast<FeSuperCluster&>(*(superMapItem.second));
		// Get its boundaries
		auto const& heBounds = superCluster.getHeBounds();
		auto const& vBounds = superCluster.getVBounds();
		// Get its diameter
		double diam = 2.0 * superCluster.getReactionRadius();
		// Get its concentration
		double conc = superCluster.getConcentration(0.0, 0.0);

		// For compatibility with previous versions, we output
		// the value of a closed upper bound of the He and V intervals.
		outputFile << *(heBounds.begin()) << " " << *(heBounds.end()) - 1 << " "
				<< *(vBounds.begin()) << " " << *(vBounds.end()) - 1 << " "
				<< conc << std::endl;
	}

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Close the file
	outputFile.close();

	// Restore the solutionArray
	ierr = DMDAVecRestoreArrayDOFRead(da, solution, &solutionArray);
	CHKERRQ(ierr);

	PetscFunctionReturn(0);
}

/**
 * This operation sets up different monitors
 *  depending on the options.
 * @param ts The time stepper
 * @return A standard PETSc error code
 */
PetscErrorCode setupPetsc0DMonitor(TS ts) {
	PetscErrorCode ierr;

	// Get xolotlViz handler registry
	auto vizHandlerRegistry = xolotlFactory::getVizHandlerRegistry();

	// Flags to launch the monitors or not
<<<<<<< HEAD
	PetscBool flagCheck, flag1DPlot, flagMeanSize, flagPerf, flagStatus;
=======
	PetscBool flagCheck, flag1DPlot, flagBubble, flagPerf, flagStatus;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Check the option -check_collapse
	ierr = PetscOptionsHasName(NULL, NULL, "-check_collapse", &flagCheck);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: PetscOptionsHasName (-check_collapse) failed.");

	// Check the option -plot_perf
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_perf", &flagPerf);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: PetscOptionsHasName (-plot_perf) failed.");

	// Check the option -plot_1d
	ierr = PetscOptionsHasName(NULL, NULL, "-plot_1d", &flag1DPlot);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: PetscOptionsHasName (-plot_1d) failed.");

	// Check the option -start_stop
	ierr = PetscOptionsHasName(NULL, NULL, "-start_stop", &flagStatus);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: PetscOptionsHasName (-start_stop) failed.");

<<<<<<< HEAD
	// Check the option -mean_size
	ierr = PetscOptionsHasName(NULL, NULL, "-mean_size", &flagMeanSize);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: PetscOptionsHasName (-mean_size) failed.");

	// Get the solver handler
	auto solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto network = solverHandler->getNetwork();
	const int networkSize = network->size();
=======
	// Check the option -bubble
	ierr = PetscOptionsHasName(NULL, NULL, "-bubble", &flagBubble);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: PetscOptionsHasName (-bubble) failed.");

	// Get the solver handler
	auto& solverHandler = PetscSolver::getSolverHandler();

	// Get the network and its size
	auto& network = solverHandler.getNetwork();
	const int networkSize = network.size();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Set the post step processing to stop the solver if the time step collapses
	if (flagCheck) {
		// Find the threshold
		PetscBool flag;
		ierr = PetscOptionsGetReal(NULL, NULL, "-check_collapse",
				&timeStepThreshold, &flag);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: PetscOptionsGetInt (-check_collapse) failed.");
		if (!flag)
			timeStepThreshold = 1.0e-16;

		// Set the post step process that tells the solver when to stop if the time step collapse
		ierr = TSSetPostStep(ts, checkTimeStep);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: TSSetPostStep (checkTimeStep) failed.");
	}

	// Set the monitor to save the status of the simulation in hdf5 file
	if (flagStatus) {
		// Find the stride to know how often the HDF5 file has to be written
		PetscBool flag;
		ierr = PetscOptionsGetReal(NULL, NULL, "-start_stop", &hdf5Stride0D,
				&flag);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: PetscOptionsGetInt (-start_stop) failed.");
		if (!flag)
			hdf5Stride0D = 1.0;

		PetscInt Mx;
		PetscErrorCode ierr;

		// Get the da from ts
		DM da;
		ierr = TSGetDM(ts, &da);
		checkPetscError(ierr, "setupPetsc0DMonitor: TSGetDM failed.");

		// Get the size of the total grid
		ierr = DMDAGetInfo(da, PETSC_IGNORE, &Mx, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE, PETSC_IGNORE,
		PETSC_IGNORE);
		checkPetscError(ierr, "setupPetsc0DMonitor: DMDAGetInfo failed.");

		// Initialize the HDF5 file for all the processes
		xolotlCore::HDF5Utils::initializeFile(hdf5OutputName0D);

		// Get the solver handler
<<<<<<< HEAD
		auto solverHandler = PetscSolver::getSolverHandler();
=======
		auto& solverHandler = PetscSolver::getSolverHandler();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Save the header in the HDF5 file
		xolotlCore::HDF5Utils::fillHeader(Mx, 0.0);

		// Save the network in the HDF5 file
<<<<<<< HEAD
<<<<<<< HEAD
		xolotlCore::HDF5Utils::fillNetwork(solverHandler->getNetworkName());
=======
		if (!solverHandler->getNetworkName().empty())
			xolotlCore::HDF5Utils::fillNetwork(solverHandler->getNetworkName());
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
=======
		if (!solverHandler->getNetworkName().empty())
			xolotlCore::HDF5Utils::fillNetwork(solverHandler->getNetworkName());
=======
		if (!solverHandler.getNetworkName().empty())
			xolotlCore::HDF5Utils::fillNetwork(solverHandler.getNetworkName());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
>>>>>>> master

		// Finalize the HDF5 file
		xolotlCore::HDF5Utils::finalizeFile();

		// startStop0D will be called at each timestep
		ierr = TSMonitorSet(ts, startStop0D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: TSMonitorSet (startStop0D) failed.");
	}

	// Set the monitor to save 1D plot of xenon distribution
	if (flag1DPlot) {
		// Create a ScatterPlot
		scatterPlot0D = vizHandlerRegistry->getPlot("scatterPlot0D",
				xolotlViz::PlotType::SCATTER);

//		scatterPlot0D->setLogScale();

		// Create and set the label provider
		auto labelProvider = std::make_shared<xolotlViz::LabelProvider>(
				"labelProvider");
		labelProvider->axis1Label = "Xenon Size";
		labelProvider->axis2Label = "Concentration";

		// Give it to the plot
		scatterPlot0D->setLabelProvider(labelProvider);

		// Create the data provider
		auto dataProvider = std::make_shared<xolotlViz::CvsXDataProvider>(
				"dataProvider");

		// Give it to the plot
		scatterPlot0D->setDataProvider(dataProvider);

		// monitorScatter0D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorScatter0D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: TSMonitorSet (monitorScatter0D) failed.");
	}

	// Set the monitor to save performance plots (has to be in parallel)
	if (flagPerf) {
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

		// monitorPerf will be called at each timestep
		ierr = TSMonitorSet(ts, monitorPerf, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: TSMonitorSet (monitorPerf) failed.");
	}

<<<<<<< HEAD
	// Initialize indices0D and weights0D if we want to compute the
	// retention or the cumulative value and others
	if (flagMeanSize) {
		// Get all the vacancy clusters
		auto vClusters = network->getAll(vType);

		// Loop on the helium clusters
		for (unsigned int i = 0; i < vClusters.size(); i++) {
			auto cluster = vClusters[i];
			int id = cluster->getId() - 1;
			// Add the Id to the vector
			indices0D.push_back(id);
			// Add the number of heliums of this cluster to the weight
			weights0D.push_back(cluster->getSize());
			radii0D.push_back(cluster->getReactionRadius());
		}
	}

	// Set the monitor to save text file of the mean helium size
	if (flagMeanSize) {
		// monitorMeanSize0D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorMeanSize0D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: TSMonitorSet (monitorMeanSize0D) failed.");
=======
	// Set the monitor to save text file of the mean concentration of bubbles
	if (flagBubble) {
		// monitorBubble0D will be called at each timestep
		ierr = TSMonitorSet(ts, monitorBubble0D, NULL, NULL);
		checkPetscError(ierr,
				"setupPetsc0DMonitor: TSMonitorSet (monitorBubble0D) failed.");
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Set the monitor to simply change the previous time to the new time
	// monitorTime will be called at each timestep
	ierr = TSMonitorSet(ts, monitorTime, NULL, NULL);
	checkPetscError(ierr,
			"setupPetsc0DMonitor: TSMonitorSet (monitorTime) failed.");

	PetscFunctionReturn(0);
}

}

/* end namespace xolotlSolver */
