// Includes
#include "HCluster.h"

using namespace xolotlCore;

HCluster::HCluster(int nH, std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
<<<<<<< HEAD
<<<<<<< HEAD
		PSICluster(registry) {
	// Set the size appropriately
	size = nH;
=======
		PSICluster(nH, registry) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
		PSICluster(nH, registry) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	// Set the reactant name appropriately
	name = "Hydrogen";
}

HCluster::~HCluster() { }
