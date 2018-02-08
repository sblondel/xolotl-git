/*
 * PSIClusterTester.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Jay Jay Billings
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <xolotlPerf.h>
#include <DummyHandlerRegistry.h>
#include <PSICluster.h>
#include <PSIClusterReactionNetwork.h>
#include <memory>
#include <typeinfo>
#include <limits>
#include <math.h>

using namespace std;
using namespace xolotlCore;

<<<<<<< HEAD
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>();
=======
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * This suite is responsible for testing the PSICluster.
 */
BOOST_AUTO_TEST_SUITE (PSICluster_testSuite)

/** This operation checks the loader. */
BOOST_AUTO_TEST_CASE(checkDiffusionCoefficient) {
	// Local Declarations
<<<<<<< HEAD
	PSICluster cluster(1, registry);
=======
	PSICluster cluster(registry);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Check E_m = 0.0
	cluster.setMigrationEnergy(0.0);
	cluster.setDiffusionFactor(1.0);
	cluster.setTemperature(1.0);
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),exp(0.0),0.00001);
	BOOST_REQUIRE_CLOSE(1.0,cluster.getTemperature(),0.0001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), exp(0.0), 0.00001);
	BOOST_REQUIRE_CLOSE(1.0, cluster.getTemperature(), 0.0001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Make sure the diffusion coefficient is 0.0 if E_m is infinite
	cluster.setMigrationEnergy(numeric_limits<double>::infinity());
	cluster.setDiffusionFactor(1.0);
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),0.0,0.000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 0.0, 0.000001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Make sure the diffusion coefficient is zero if the diffusion factor is zero
	cluster.setMigrationEnergy(5.0);
	cluster.setDiffusionFactor(0.0);
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),0.0,0.000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 0.0, 0.000001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Make sure the diffusion coefficient is equal to the diffusion factor
	// if the temperature is infinite
	cluster.setMigrationEnergy(5.0);
	cluster.setDiffusionFactor(1.0);
	cluster.setTemperature(numeric_limits<double>::infinity());
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),1.0,0.000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 1.0, 0.000001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Throw something random in there to be certain
	cluster.setMigrationEnergy(0.013);
	cluster.setDiffusionFactor(1.08E10);
	cluster.setTemperature(1500.0);
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),9766651101.800613,0.0000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 9766651101.800613,
			0.0000001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Do the same test, but make sure the order of the calls doesn't affect the outcome.
	cluster.setTemperature(1500.0);
	cluster.setDiffusionFactor(1.08E10);
	cluster.setMigrationEnergy(0.013);
<<<<<<< HEAD
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),9766651101.800613,0.0000001);
=======
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(), 9766651101.800613,
			0.0000001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	return;
}

/**
 * This operation tests the copy constructor.
 */
BOOST_AUTO_TEST_CASE(checkCopying) {
	// Local Declarations
<<<<<<< HEAD
	PSICluster cluster(1, registry);
=======
	PSICluster cluster(registry);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	cluster.setDiffusionFactor(1.0);
	cluster.setMigrationEnergy(2.0);

	PSICluster copiedCluster(cluster);

	// Check Reactant copying
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionFactor(),
			copiedCluster.getDiffusionFactor(), 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getMigrationEnergy(),
			copiedCluster.getMigrationEnergy(), 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getDiffusionCoefficient(),
			copiedCluster.getDiffusionCoefficient(), 1e-5);

	// Modify some values to ensure a deep copy is occurring
<<<<<<< HEAD
	copiedCluster.setDiffusionFactor(0.5);// This should not happen!
=======
	copiedCluster.setDiffusionFactor(0.5);	// This should not happen!
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
	BOOST_REQUIRE(abs(cluster.getMigrationEnergy() -
					copiedCluster.getMigrationEnergy()) > 2.0 - 1e-5);
=======
	BOOST_REQUIRE(
			fabs(
					cluster.getMigrationEnergy()
							- copiedCluster.getMigrationEnergy()) > 2.0 - 1e-5);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Check cloning. Note that clone returns a shared_ptr!
	auto clusterClone = cluster.clone();
	BOOST_REQUIRE_EQUAL(cluster.getName(), clusterClone->getName());

	return;
}

/**
 * This operation tests the default values returned by select flux routines.
 */
BOOST_AUTO_TEST_CASE(checkDefaultFluxes) {
	// Local Declarations
<<<<<<< HEAD
	PSICluster cluster(1, registry);
=======
	PSICluster cluster(registry);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Check the default values of the fluxes
	BOOST_REQUIRE_CLOSE(cluster.getProductionFlux(), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getCombinationFlux(), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getDissociationFlux(), 0.0, 1e-5);
	BOOST_REQUIRE_CLOSE(cluster.getTotalFlux(), 0.0, 1e-5);

<<<<<<< HEAD
=======
	return;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

BOOST_AUTO_TEST_SUITE_END()
