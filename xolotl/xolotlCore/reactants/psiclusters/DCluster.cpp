#include "DCluster.h"
<<<<<<< HEAD

using namespace xolotlCore;

DCluster::DCluster(int nH, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		HCluster(nH, registry) {
	// Set the reactant name appropriately
	name = "Deuterium";
}
DCluster::~DCluster() {
=======
#include <Constants.h>

using namespace xolotlCore;

DCluster::DCluster(int nD,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		HCluster(registry) {
	// Set the size
	size = nD;
	// Update the composition map
	compositionMap[dType] = size;

	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "D_" << size;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = dType;

	// Compute the reaction radius
	reactionRadius = 0.3;

	return;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
}
