// Includes
#include "HCluster.h"

using namespace xolotlCore;

<<<<<<< HEAD
HCluster::HCluster(int nH, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(registry) {
	// Set the size appropriately
	size = nH;
	// Set the reactant name appropriately
	name = "Hydrogen";
}

HCluster::~HCluster() { }
=======
HCluster::HCluster(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(registry) {
	// Don't do anything

	return;
}
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
