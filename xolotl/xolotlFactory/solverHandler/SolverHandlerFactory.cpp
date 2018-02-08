<<<<<<< HEAD
=======
#include <cassert>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <SolverHandlerFactory.h>
#include <PetscSolver0DHandler.h>
#include <PetscSolver1DHandler.h>
#include <PetscSolver2DHandler.h>
#include <PetscSolver3DHandler.h>
#include <fstream>
#include <iostream>
#include <mpi.h>

namespace xolotlFactory {

<<<<<<< HEAD
static std::shared_ptr<xolotlSolver::ISolverHandler> theSolverHandler;

// Create the desired type of handler registry.
bool initializeDimension(xolotlCore::Options &options) {
=======
static std::unique_ptr<xolotlSolver::ISolverHandler> theSolverHandler;

// Create the desired type of handler registry.
bool initializeDimension(xolotlCore::Options &options,
		xolotlCore::IReactionNetwork& network) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	bool ret = true;

	// Get the wanted dimension
	int dim = options.getDimensionNumber();

	// Switch on the dimension
<<<<<<< HEAD
	switch (dim) {
	case 0:
		theSolverHandler =
				std::make_shared<xolotlSolver::PetscSolver0DHandler>();
		break;
	case 1:
		theSolverHandler =
				std::make_shared<xolotlSolver::PetscSolver1DHandler>();
		break;
	case 2:
		theSolverHandler =
				std::make_shared<xolotlSolver::PetscSolver2DHandler>();
		break;
	case 3:
		theSolverHandler =
				std::make_shared<xolotlSolver::PetscSolver3DHandler>();
=======
	// TODO Once we have widespread C++14 support, use std::make_unique
	// instead of this two-step construction.
	xolotlSolver::ISolverHandler* rawSolverHandler = nullptr;
	switch (dim) {
	case 0:
		rawSolverHandler = new xolotlSolver::PetscSolver0DHandler(network);
		break;
	case 1:
		rawSolverHandler = new xolotlSolver::PetscSolver1DHandler(network);
		break;
	case 2:
		rawSolverHandler = new xolotlSolver::PetscSolver2DHandler(network);
		break;
	case 3:
		rawSolverHandler = new xolotlSolver::PetscSolver3DHandler(network);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		break;
	default:
		// The asked dimension is not good (e.g. -1, 4)
		throw std::string(
				"\nxolotlFactory: Bad dimension for the solver handler.");
	}
<<<<<<< HEAD
=======
	assert(rawSolverHandler != nullptr);
	theSolverHandler = std::unique_ptr<xolotlSolver::ISolverHandler>(
			rawSolverHandler);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return ret;
}

// Provide access to our handler registry.
<<<<<<< HEAD
std::shared_ptr<xolotlSolver::ISolverHandler> getSolverHandler() {
=======
xolotlSolver::ISolverHandler& getSolverHandler() {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	if (!theSolverHandler) {
		// We have not yet been initialized.
		throw std::string("\nxolotlFactory: solver requested but "
				"it has not been initialized.");
	}

<<<<<<< HEAD
	return theSolverHandler;
=======
	return *theSolverHandler;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

} // end namespace xolotlFactory

