// Includes
#include "HCluster.h"

using namespace xolotlCore;

HCluster::HCluster(int nH, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
<<<<<<< HEAD
		PSICluster(registry) {
	// Set the size appropriately
	size = nH;
=======
		PSICluster(nH, registry) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	// Set the reactant name appropriately
	name = "Hydrogen";
}

HCluster::~HCluster() { }
