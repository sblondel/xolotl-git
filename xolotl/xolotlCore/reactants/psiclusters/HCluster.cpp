// Includes
#include "HCluster.h"

using namespace xolotlCore;

HCluster::HCluster(int nH, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
<<<<<<< HEAD
		PSICluster(nH, registry) {
=======
		PSICluster(registry) {
	// Set the size appropriately
	size = nH;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Set the reactant name appropriately
	name = "Hydrogen";
}

HCluster::~HCluster() { }
