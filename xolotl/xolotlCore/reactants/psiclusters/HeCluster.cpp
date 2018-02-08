// Includes
#include "HeCluster.h"
<<<<<<< HEAD
#include "PSIClusterReactionNetwork.h"
#include <Constants.h>
#include <iostream>
=======
#include <Constants.h>
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d

using namespace xolotlCore;

HeCluster::HeCluster(int nHe,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(registry) {
	// Set the size
	size = nHe;
	// Update the composition map
	compositionMap[heType] = size;

	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "He_" << size;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = heType;

	// Compute the reaction radius
	double FourPi = 4.0 * xolotlCore::pi;
	double aCubed = pow(xolotlCore::tungstenLatticeConstant, 3);
	double termOne = pow((3.0 / FourPi) * (1.0 / 10.0) * aCubed * size,
			(1.0 / 3.0));
	double termTwo = pow((3.0 / FourPi) * (1.0 / 10.0) * aCubed, (1.0 / 3.0));
	reactionRadius = 0.3 + termOne - termTwo;

	return;
}
