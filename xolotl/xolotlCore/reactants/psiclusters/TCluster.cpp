#include "TCluster.h"
<<<<<<< HEAD

using namespace xolotlCore;

TCluster::TCluster(int nT, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		HCluster(nT, registry) {
	// Set the reactant name appropriately
	name = "Tritium";
}
TCluster::~TCluster() {
=======
#include <Constants.h>

using namespace xolotlCore;

TCluster::TCluster(int nT,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		HCluster(registry) {
	// Set the size
	size = nT;
	// Update the composition map
	compositionMap[tType] = size;

	// Set the reactant name appropriately
	std::stringstream nameStream;
	nameStream << "T_" << size;
	name = nameStream.str();
	// Set the typename appropriately
	typeName = tType;

	// Compute the reaction radius
	reactionRadius = 0.3;

	return;
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
}
