#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <HDF5Utils.h>
#include <PSIClusterReactionNetwork.h>
#include <DummyHandlerRegistry.h>
#include <HDF5NetworkLoader.h>
#include <XolotlConfig.h>
#include <mpi.h>
#include <memory>
<<<<<<< HEAD
=======
#include <Options.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

using namespace std;
using namespace xolotlCore;

/**
 * This suite is responsible for testing the HDF5NetworkLoader.
 */
BOOST_AUTO_TEST_SUITE(HDF5NetworkLoader_testSuite)

/**
 * Method checking the loading of the network from the HDF5 file.
 */
BOOST_AUTO_TEST_CASE(checkLoad) {
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

<<<<<<< HEAD
	// Load the network
	auto network = loader.load();
=======
	// Create the options needed to load the network
	Options opts;
	// Load the network
	auto network = loader.load(opts);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the size of the network
	int networkSize = network->size();
	// Check the value
	BOOST_REQUIRE_EQUAL(networkSize, 9);

	// Check the properties
<<<<<<< HEAD
	auto psiNetwork = std::dynamic_pointer_cast<PSIClusterReactionNetwork>(
			network);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxHeClusterSize(), 8);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxVClusterSize(), 1);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxIClusterSize(), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxHeVClusterSize(), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumHeClusters(), 8);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumVClusters(), 1);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumIClusters(), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumHeVClusters(), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumSuperClusters(), 0);

	// Get all the reactants
	auto reactants = network->getAll();

	// Get the first one of the network
	auto reactant = (PSICluster *) reactants->at(0);
	// Check the composition
	auto composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 1);
	BOOST_REQUIRE_EQUAL(composition["V"], 0);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);
	// Check the formation energy
	auto formationEnergy = reactant->getFormationEnergy();
	BOOST_REQUIRE_EQUAL(formationEnergy, 6.15);
	// Check the migration energy
	auto migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 0.13);
	// Check the diffusion factor
	auto diffusionFactor = reactant->getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 2.9e+10);

	// Get the last reactant of the network
	reactant = (PSICluster *) reactants->at(8);
	// Check the composition
	composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 0);
	BOOST_REQUIRE_EQUAL(composition["V"], 1);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);
	// Check the formation energy
	formationEnergy = reactant->getFormationEnergy();
	BOOST_REQUIRE_EQUAL(formationEnergy, 3.6);
	// Check the migration energy
	migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 1.3);
	// Check the diffusion factor
	diffusionFactor = reactant->getDiffusionFactor();
=======
	auto psiNetwork = (PSIClusterReactionNetwork*) network.get();
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::He) == 8);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::V) == 1);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::I) == 0);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::HeV) == 0);

	// Get all the reactants
	auto& reactants = network->getAll();

	// Get the first one of the network
	IReactant& reactant = reactants.at(0);
	// Check the composition
	auto composition = reactant.getComposition();
	BOOST_REQUIRE_EQUAL(composition[toCompIdx(Species::He)], 1);
	BOOST_REQUIRE_EQUAL(composition[toCompIdx(Species::V)], 0);
	BOOST_REQUIRE_EQUAL(composition[toCompIdx(Species::I)], 0);
	// Check the formation energy
	auto formationEnergy = reactant.getFormationEnergy();
	BOOST_REQUIRE_EQUAL(formationEnergy, 6.15);
	// Check the migration energy
	auto migrationEnergy = reactant.getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 0.13);
	// Check the diffusion factor
	auto diffusionFactor = reactant.getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 2.9e+10);

	// Get the last reactant of the network
	IReactant& reactantBis = reactants.at(8);
	// Check the composition
	composition = reactantBis.getComposition();
	BOOST_REQUIRE_EQUAL(composition[toCompIdx(Species::He)], 0);
	BOOST_REQUIRE_EQUAL(composition[toCompIdx(Species::V)], 1);
	BOOST_REQUIRE_EQUAL(composition[toCompIdx(Species::I)], 0);
	// Check the formation energy
	formationEnergy = reactantBis.getFormationEnergy();
	BOOST_REQUIRE_EQUAL(formationEnergy, 3.6);
	// Check the migration energy
	migrationEnergy = reactantBis.getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 1.3);
	// Check the diffusion factor
	diffusionFactor = reactantBis.getDiffusionFactor();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	BOOST_REQUIRE_EQUAL(diffusionFactor, 1.8e+12);

	return;
}

/**
 * Method checking the loading of the network from the HDF5 file and
 * the apply sectional method.
 */
BOOST_AUTO_TEST_CASE(checkApplySectional) {

	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten.h5");
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);
	// Set grouping parameters
	loader.setVMin(28);
	loader.setHeWidth(4);
	loader.setVWidth(2);

<<<<<<< HEAD
	// Load the network
	auto network = loader.load();
=======
	// Create default options
	Options opts;

	// Load the network
	auto network = loader.load(opts);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Get the size of the network
	int networkSize = network->size();
	// Check the value
	BOOST_REQUIRE_EQUAL(networkSize, 1870);

	// Get the dof of the network
	int dof = network->getDOF();
	// Check the value
	BOOST_REQUIRE_EQUAL(dof, 1933);

	// Check the properties
<<<<<<< HEAD
	auto psiNetwork = std::dynamic_pointer_cast<PSIClusterReactionNetwork>(
			network);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxHeClusterSize(), 8);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxVClusterSize(), 29);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxIClusterSize(), 6);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxHeVClusterSize(), 145);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumHeClusters(), 8);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumVClusters(), 29);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumIClusters(), 6);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumHeVClusters(), 1796);
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumSuperClusters(), 31);
=======
	auto psiNetwork = (PSIClusterReactionNetwork*) network.get();

	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::He) == 8);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::V) == 29);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::I) == 6);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::HeV) == 137);
	BOOST_REQUIRE(psiNetwork->getMaxClusterSize(ReactantType::PSISuper) == 145);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Finalize MPI
	MPI_Finalize();

	return;
}

BOOST_AUTO_TEST_SUITE_END()
