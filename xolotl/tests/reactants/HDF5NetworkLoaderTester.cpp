#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <HDF5Utils.h>
#include <PSIClusterReactionNetwork.h>
#include <DummyHandlerRegistry.h>
#include <HDF5NetworkLoader.h>
#include <XolotlConfig.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <mpi.h>
=======
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
=======
#include <mpi.h>
>>>>>>> Modifying the way HDF5 files are written and read: append a concentration group at each time step instead of a new file, and read from the concentration only if the group exists in the file. Adding a stride to write HDF5 file only every "stride" time step. Updating the associated steps. SB 20140616
#include <memory>

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
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> Modifying the way HDF5 files are written and read: append a concentration group at each time step instead of a new file, and read from the concentration only if the group exists in the file. Adding a stride to write HDF5 file only every "stride" time step. Updating the associated steps. SB 20140616
	// Initialize MPI for HDF5
	int argc = 0;
	char **argv;
	MPI_Init(&argc, &argv);

<<<<<<< HEAD
	// Create the network loader
	HDF5NetworkLoader loader = HDF5NetworkLoader(
			make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
	string pathToFile("/tests/testfiles/tungsten_diminutive.h5");
=======
=======
>>>>>>> Modifying the way HDF5 files are written and read: append a concentration group at each time step instead of a new file, and read from the concentration only if the group exists in the file. Adding a stride to write HDF5 file only every "stride" time step. Updating the associated steps. SB 20140616
	// Create the network loader
	HDF5NetworkLoader loader =
			HDF5NetworkLoader(make_shared<xolotlPerf::DummyHandlerRegistry>());
	// Define the filename to load the network from
	string sourceDir(XolotlSourceDirectory);
<<<<<<< HEAD
	string pathToFile("/tests/reactants/testfiles/tungsten_small.h5");
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);

	// Load the network
	auto network = loader.load();

	// Get the size of the network
	int networkSize = network->size();
	// Check the value
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(networkSize, 9);

	// Check the properties
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
=======
	string pathToFile("/tests/reactants/testfiles/tungsten_diminutive.h5");
>>>>>>> The test for the HDF5NetworkLoader is now more complete, using the tungsten_diminutive benchmark. SB 20140523
	string filename = sourceDir + pathToFile;
	// Give the filename to the network loader
	loader.setFilename(filename);
	// Set grouping parameters
	loader.setVMin(28);
	loader.setHeWidth(4);
	loader.setVWidth(2);

	// Load the network
	auto network = loader.load();

	// Get the size of the network
	int networkSize = network->size();
	// Check the value
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(networkSize, 1869);

	// Get the dof of the network
	int dof = network->getDOF();
	// Check the value
	BOOST_REQUIRE_EQUAL(dof, 1930);

	// Check the properties
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
	BOOST_REQUIRE_EQUAL(psiNetwork->getNumSuperClusters(), 30);

	// Finalize MPI
	MPI_Finalize();

	return;
=======
	BOOST_REQUIRE_EQUAL(networkSize, 100);
>>>>>>> Updating the input file used in the HDF5UtilsTester. Adding HDF5NetworkLoaderTester that might need more complete tests. SB 20140521
=======
	BOOST_REQUIRE_EQUAL(networkSize, 5);

	// Get the properties
	auto props = network->getProperties();

	// Check the properties
	BOOST_REQUIRE_EQUAL(strtol(props["maxHeClusterSize"].c_str(),NULL,10), 2);
	BOOST_REQUIRE_EQUAL(strtol(props["maxVClusterSize"].c_str(),NULL,10), 1);
	BOOST_REQUIRE_EQUAL(strtol(props["maxIClusterSize"].c_str(),NULL,10), 1);
	BOOST_REQUIRE_EQUAL(strtol(props["maxHeVClusterSize"].c_str(),NULL,10), 3);
	BOOST_REQUIRE_EQUAL(strtol(props["numHeClusters"].c_str(),NULL,10), 2);
	BOOST_REQUIRE_EQUAL(strtol(props["numVClusters"].c_str(),NULL,10), 1);
	BOOST_REQUIRE_EQUAL(strtol(props["numIClusters"].c_str(),NULL,10), 1);

	// Get all the reactants
	auto reactants = network->getAll();

	// Get the first one of the network
	auto reactant = (PSICluster *) reactants->at(0);
	// Check the composition
	auto composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 0);
	BOOST_REQUIRE_EQUAL(composition["V"], 1);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);
	// Check the binding energies
	auto bindingEnergies = reactant->getBindingEnergies();
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(0), numeric_limits<double>::infinity()); // Helium binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(1), numeric_limits<double>::infinity()); // Vacancy binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(2), numeric_limits<double>::infinity()); // Interstitial binding energy
	// Check the migration energy
	auto migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 1.66);
	// Check the diffusion factor
	auto diffusionFactor = reactant->getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 2.41e+11);

	// Get the second reactant of the network
	reactant = (PSICluster *) reactants->at(1);
	// Check the composition
	composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 2);
	BOOST_REQUIRE_EQUAL(composition["V"], 0);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);
	// Check the binding energies
	bindingEnergies = reactant->getBindingEnergies();
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(0), 0.864); // Helium binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(1), numeric_limits<double>::infinity()); // Vacancy binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(2), numeric_limits<double>::infinity()); // Interstitial binding energy
	// Check the migration energy
	migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 0.2);
	// Check the diffusion factor
	diffusionFactor = reactant->getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 3.24e+10);

	// Get the third reactant of the network
	reactant = (PSICluster *) reactants->at(2);// Check the composition
	composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 1);
	BOOST_REQUIRE_EQUAL(composition["V"], 0);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);
	// Check the binding energies
	bindingEnergies = reactant->getBindingEnergies();
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(0), numeric_limits<double>::infinity()); // Helium binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(1), numeric_limits<double>::infinity()); // Vacancy binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(2), numeric_limits<double>::infinity()); // Interstitial binding energy
	// Check the migration energy
	migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 0.13);
	// Check the diffusion factor
	diffusionFactor = reactant->getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 2.95e+10);

	// Get the fourth reactant of the network
	reactant = (PSICluster *) reactants->at(3);
	// Check the composition
	composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 0);
	BOOST_REQUIRE_EQUAL(composition["V"], 0);
	BOOST_REQUIRE_EQUAL(composition["I"], 1);
	// Check the binding energies
	bindingEnergies = reactant->getBindingEnergies();
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(0), numeric_limits<double>::infinity()); // Helium binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(1), numeric_limits<double>::infinity()); // Vacancy binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(2), numeric_limits<double>::infinity()); // Interstitial binding energy
	// Check the migration energy
	migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, 0.013);
	// Check the diffusion factor
	diffusionFactor = reactant->getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 2.13e+10);

	// Get the last and fifth reactant of the network
	reactant = (PSICluster *) reactants->at(4);
	// Check the composition
	composition = reactant->getComposition();
	BOOST_REQUIRE_EQUAL(composition["He"], 2);
	BOOST_REQUIRE_EQUAL(composition["V"], 1);
	BOOST_REQUIRE_EQUAL(composition["I"], 0);
	// Check the binding energies
	bindingEnergies = reactant->getBindingEnergies();
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(0), 3.02); // Helium binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(1), 7.25); // Vacancy binding energy
	BOOST_REQUIRE_EQUAL(bindingEnergies.at(2), numeric_limits<double>::infinity()); // Interstitial binding energy
	// Check the migration energy
	migrationEnergy = reactant->getMigrationEnergy();
	BOOST_REQUIRE_EQUAL(migrationEnergy, numeric_limits<double>::infinity());
	// Check the diffusion factor
	diffusionFactor = reactant->getDiffusionFactor();
	BOOST_REQUIRE_EQUAL(diffusionFactor, 0.0);
<<<<<<< HEAD
>>>>>>> The test for the HDF5NetworkLoader is now more complete, using the tungsten_diminutive benchmark. SB 20140523
=======

	// Finalize MPI
	MPI_Finalize();
>>>>>>> Modifying the way HDF5 files are written and read: append a concentration group at each time step instead of a new file, and read from the concentration only if the group exists in the file. Adding a stride to write HDF5 file only every "stride" time step. Updating the associated steps. SB 20140616
}

BOOST_AUTO_TEST_SUITE_END()
