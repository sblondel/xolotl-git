/*
 * PSIClusterTester.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Jay Jay Billings
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
<<<<<<< HEAD
<<<<<<< HEAD
#include <xolotlPerf.h>
#include <DummyHandlerRegistry.h>
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
#include "../../xolotlPerf/dummy/DummyHandlerRegistry.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
#include "../../xolotlPerf/dummy/DummyHandlerRegistry.h"
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include <PSICluster.h>
#include <PSIClusterReactionNetwork.h>
#include <memory>
#include <typeinfo>
#include <limits>
#include <math.h>

using namespace std;
using namespace xolotlCore;

<<<<<<< HEAD
<<<<<<< HEAD
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();
=======
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>();
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

/**
 * This suite is responsible for testing the PSICluster.
 */
BOOST_AUTO_TEST_SUITE (PSICluster_testSuite)

/** This operation checks the loader. */
BOOST_AUTO_TEST_CASE(checkDiffusionCoefficient) {
<<<<<<< HEAD
<<<<<<< HEAD
	// Local Declarations
	PSICluster cluster(registry);
=======

	// Local Declarations
	PSICluster cluster(1, registry);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

	// Local Declarations
	PSICluster cluster(1, registry);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Check E_m = 0.0
	cluster.setMigrationEnergy(0.0);
	cluster.setDiffusionFactor(1.0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	cluster.setTemperature(1.0);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), exp(0.0), 0.00001);
	BOOST_REQUIRE_CLOSE(1.0, cluster.getTemperature(), 0.0001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(1.0),exp(0.0),0.00001);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	cluster.setTemperature(1.0);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),exp(0.0),0.00001);
	BOOST_REQUIRE_CLOSE(1.0,cluster.getTemperature(),0.0001);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	cluster.setTemperature(1.0);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),exp(0.0),0.00001);
	BOOST_REQUIRE_CLOSE(1.0,cluster.getTemperature(),0.0001);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Make sure the diffusion coefficient is 0.0 if E_m is infinite
	cluster.setMigrationEnergy(numeric_limits<double>::infinity());
	cluster.setDiffusionFactor(1.0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 0.0, 0.000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(1.0),0.0,0.00000);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),0.0,0.00000);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),0.0,0.00000);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Make sure the diffusion coefficient is zero if the diffusion factor is zero
	cluster.setMigrationEnergy(5.0);
	cluster.setDiffusionFactor(0.0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 0.0, 0.000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(1.0),0.0,0.00000);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),0.0,0.00000);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),0.0,0.00000);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Make sure the diffusion coefficient is equal to the diffusion factor
	// if the temperature is infinite
	cluster.setMigrationEnergy(5.0);
	cluster.setDiffusionFactor(1.0);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	cluster.setTemperature(numeric_limits<double>::infinity());
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 1.0, 0.000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(
					numeric_limits<double>::infinity()),1.0,0.00000);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	cluster.setTemperature(numeric_limits<double>::infinity());
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),1.0,0.00000);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	cluster.setTemperature(numeric_limits<double>::infinity());
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),1.0,0.00000);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Throw something random in there to be certain
	cluster.setMigrationEnergy(0.013);
	cluster.setDiffusionFactor(1.08E10);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	cluster.setTemperature(1500.0);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 9766651101.800613,
			0.0000001);
=======
	cluster.setTemperature(1500.0);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),9766651101.800613,0.0000001);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	cluster.setTemperature(1500.0);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),9766651101.800613,0.0000001);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Do the same test, but make sure the order of the calls doesn't affect the outcome.
	cluster.setTemperature(1500.0);
	cluster.setDiffusionFactor(1.08E10);
	cluster.setMigrationEnergy(0.013);
<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 9766651101.800613,
			0.0000001);

	return;
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(1500.0),9766651101.800613,0.0000001);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),9766651101.800613,0.0000001);

>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),9766651101.800613,0.0000001);

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

/**
 * This operation tests the copy constructor.
 */
BOOST_AUTO_TEST_CASE(checkCopying) {
<<<<<<< HEAD
<<<<<<< HEAD
	// Local Declarations
	PSICluster cluster(registry);
=======

	// Local Declarations
	PSICluster cluster(1, registry);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

	// Local Declarations
	PSICluster cluster(1, registry);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	cluster.setDiffusionFactor(1.0);
	cluster.setMigrationEnergy(2.0);

	PSICluster copiedCluster(cluster);

	// Check Reactant copying
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionFactor(),
			copiedCluster.getDiffusionFactor(), 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getMigrationEnergy(),
			copiedCluster.getMigrationEnergy(), 1e-5);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),
			copiedCluster.getDiffusionCoefficient(), 1e-5);

	// Modify some values to ensure a deep copy is occurring
	copiedCluster.setDiffusionFactor(0.5);	// This should not happen!
=======
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),
			copiedCluster.getDiffusionCoefficient(), 1e-5);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618

	// Modify some values to ensure a deep copy is occurring
	copiedCluster.setDiffusionFactor(0.5);// This should not happen!
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),
			copiedCluster.getDiffusionCoefficient(), 1e-5);

	// Modify some values to ensure a deep copy is occurring
	copiedCluster.setDiffusionFactor(0.5);// This should not happen!
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	copiedCluster.setMigrationEnergy(7.0);

	// Check the diffusion factor
	BOOST_REQUIRE_CLOSE(copiedCluster.getDiffusionFactor(), 0.5, 1e-5);
	BOOST_REQUIRE_CLOSE(copiedCluster.getMigrationEnergy(), 7.0, 1e-5);

	// Check that the original is not modified
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionFactor(), 1.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getMigrationEnergy(), 2.0, 1e-5);

	// Check the migration energy
	cluster.setMigrationEnergy(1.0);
	copiedCluster.setMigrationEnergy(3.0);
<<<<<<< HEAD
<<<<<<< HEAD
	BOOST_REQUIRE(
			fabs(
					cluster.getMigrationEnergy()
							- copiedCluster.getMigrationEnergy()) > 2.0 - 1e-5);
=======
	BOOST_REQUIRE(abs(cluster.getMigrationEnergy() -
					copiedCluster.getMigrationEnergy()) > 2.0 - 1e-5);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	BOOST_REQUIRE(abs(cluster.getMigrationEnergy() -
					copiedCluster.getMigrationEnergy()) > 2.0 - 1e-5);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Check cloning. Note that clone returns a shared_ptr!
	auto clusterClone = cluster.clone();
	BOOST_REQUIRE_EQUAL(cluster.getName(), clusterClone->getName());
<<<<<<< HEAD
<<<<<<< HEAD

	return;
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

/**
 * This operation tests the default values returned by select flux routines.
 */
BOOST_AUTO_TEST_CASE(checkDefaultFluxes) {
<<<<<<< HEAD
<<<<<<< HEAD
	// Local Declarations
	PSICluster cluster(registry);

	// Check the default values of the fluxes
	BOOST_REQUIRE_CLOSE(cluster.getProductionFlux(), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getCombinationFlux(), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getDissociationFlux(), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getTotalFlux(), 0.0, 1e-5);

	return;
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// Local Declarations
	PSICluster cluster(1, registry);

	// Check the default values of the fluxes
	BOOST_REQUIRE_CLOSE(cluster.getProductionFlux(273.0), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getCombinationFlux(273.0), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getDissociationFlux(273.0), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getTotalFlux(273.0), 0.0, 1e-5);

<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

BOOST_AUTO_TEST_SUITE_END()
