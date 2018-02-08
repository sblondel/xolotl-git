#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSIClusterNetworkLoader.h>
#include <memory>
#include <typeinfo>
#include <limits>
<<<<<<< HEAD
#include <PSIClusterReactionNetwork.h>
#include <DummyHandlerRegistry.h>
=======
#include <DummyHandlerRegistry.h>
#include <PSIClusterReactionNetwork.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

using namespace std;
using namespace xolotlCore;

/**
 * This suite is responsible for testing the PSIClusterNetworkLoader. It
 * creates a string stream that contains each of the available PSICluster types
 * and checks that the loader returns a list with each type in it.
 */
BOOST_AUTO_TEST_SUITE(PSIClusterNetworkLoader_testSuite)

/** This operation checks the loader. */
BOOST_AUTO_TEST_CASE(checkLoading) {
	// Local Declarations
	shared_ptr<stringstream> networkStream(
			new stringstream(stringstream::in | stringstream::out));
	string singleHeString = "1 0 0 6.15 0.999 1.34\n";
<<<<<<< HEAD
	string singleVString =
			"0 50 0 3.6 0.888 2.345\n";
	string singleIString = "0 0 1 5.0 0.7777 3.456\n";
	string mixedString =
			"1 50 0 2.49 6.789 4.5678\n";
	// This string is bad because it is one value short
	string badString = "1 2 3\n";
	bool caughtFlag = false;
	PSIClusterNetworkLoader loader = PSIClusterNetworkLoader(std::make_shared<xolotlPerf::DummyHandlerRegistry>());
	
	
=======
	string singleVString = "0 50 0 3.6 0.888 2.345\n";
	string singleIString = "0 0 1 5.0 0.7777 3.456\n";
	string mixedString = "1 50 0 2.49 6.789 4.5678\n";
	// This string is bad because it is one value short
	string badString = "1 2 3\n";
	bool caughtFlag = false;
	PSIClusterNetworkLoader loader = PSIClusterNetworkLoader(
			std::make_shared<xolotlPerf::DummyHandlerRegistry>());

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// Load the network stream. This simulates a file with single He, single
	// V, single I and one mixed-species cluster. They are mixed up here to test
	// the ability of the loader to order them.
	*networkStream << singleVString << mixedString << singleHeString
			<< singleIString;

	// Diagnostic information
	// @formatter:off
<<<<<<< HEAD
	BOOST_TEST_MESSAGE("CLUSTER DATA"
			<< "\nHe: "
			<< singleHeString
			<< "\nV: "
			<< singleVString
			<< "\nI: "
			<< singleIString
			<< "\n Mixed: "
			<< mixedString
			<< "\nFull Network data: \n"
			<< (*networkStream).str());
=======
	BOOST_TEST_MESSAGE(
			"CLUSTER DATA" << "\nHe: " << singleHeString << "\nV: " << singleVString << "\nI: " << singleIString << "\n Mixed: " << mixedString << "\nFull Network data: \n" << (*networkStream).str());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// @formatter:off

	// Setup the Loader
	loader.setInputstream(networkStream);

	// Load the network
<<<<<<< HEAD
	shared_ptr<PSIClusterReactionNetwork> network = loader.load();

	// Check the network. It should not be empty
	auto props = network->getProperties();
	BOOST_TEST_MESSAGE("Number of properties = " << props.size());
	BOOST_REQUIRE(!props.empty());
	
	// Print the properties list to debug
	for (auto it = props.begin(); it != props.end(); ++it) {
		printf("\"%s\" => \"%s\"\n", it->first.c_str(), it->second.c_str());
	}

	// Check the properties
	BOOST_TEST_MESSAGE("Maximum He Cluster Size = " << props["maxHeClusterSize"]);
	BOOST_REQUIRE(strtol(props["maxHeClusterSize"].c_str(),NULL,10) == 1);
	BOOST_TEST_MESSAGE("Maximum V Cluster Size = " << props["maxVClusterSize"]);
	BOOST_REQUIRE(strtol(props["maxVClusterSize"].c_str(),NULL,10) == 50);
	BOOST_TEST_MESSAGE("Maximum Interstitial Cluster Size = " << props["maxIClusterSize"]);
	BOOST_REQUIRE(strtol(props["maxIClusterSize"].c_str(),NULL,10) == 1);
	BOOST_TEST_MESSAGE("Maximum Mixed Species Cluster Size = " << props["maxMixedClusterSize"]);
	BOOST_REQUIRE(strtol(props["maxHeVClusterSize"].c_str(),NULL,10) == 51);
	BOOST_TEST_MESSAGE("Number of He clusters = " << props["numHeClusters"]);
	BOOST_REQUIRE(strtol(props["numHeClusters"].c_str(),NULL,10) == 1);
	BOOST_TEST_MESSAGE("Number of V clusters = " << props["numVClusters"]);
	BOOST_REQUIRE(strtol(props["numVClusters"].c_str(),NULL,10) == 1);
	BOOST_TEST_MESSAGE("Number of I clusters = " << props["numIClusters"]);
	BOOST_REQUIRE(strtol(props["numIClusters"].c_str(),NULL,10) == 1);

	// Check the reactants - He first
	auto heCluster = (PSICluster *) network->get("He",1);
=======
	auto network = loader.load();
	auto psiNetwork = std::dynamic_pointer_cast<PSIClusterReactionNetwork>(
			network);

	// Check the properties
	BOOST_TEST_MESSAGE(
			"Maximum He Cluster Size = " << psiNetwork->getMaxHeClusterSize());
	BOOST_REQUIRE(psiNetwork->getMaxHeClusterSize() == 1);
	BOOST_TEST_MESSAGE(
			"Maximum V Cluster Size = " << psiNetwork->getMaxVClusterSize());
	BOOST_REQUIRE(psiNetwork->getMaxVClusterSize() == 50);
	BOOST_TEST_MESSAGE(
			"Maximum Interstitial Cluster Size = " << psiNetwork->getMaxIClusterSize());
	BOOST_REQUIRE(psiNetwork->getMaxIClusterSize() == 1);
	BOOST_REQUIRE(psiNetwork->getMaxHeVClusterSize() == 51);
	BOOST_TEST_MESSAGE(
			"Number of He clusters = " << psiNetwork->getNumHeClusters());
	BOOST_REQUIRE(psiNetwork->getNumHeClusters() == 1);
	BOOST_TEST_MESSAGE(
			"Number of V clusters = " << psiNetwork->getNumVClusters());
	BOOST_REQUIRE(psiNetwork->getNumVClusters() == 1);
	BOOST_TEST_MESSAGE(
			"Number of I clusters = " << psiNetwork->getNumIClusters());
	BOOST_REQUIRE(psiNetwork->getNumIClusters() == 1);

	// Check the reactants - He first
	auto heCluster = (PSICluster *) network->get("He", 1);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	BOOST_REQUIRE(heCluster->getSize() == 1);
	double formationEnergy = heCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy, 6.15, 0.001);
	// V
<<<<<<< HEAD
	auto vCluster = (PSICluster *) network->get("V",50);
	BOOST_REQUIRE(vCluster->getSize() == 50);
	formationEnergy = vCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy,3.6, 0.001);
	BOOST_REQUIRE_CLOSE(vCluster->getMigrationEnergy(),0.888,0.001);
	BOOST_REQUIRE_CLOSE(vCluster->getDiffusionFactor(),2.345,0.001);
	// I
	auto iCluster = (PSICluster *) network->get("I",1);
	BOOST_REQUIRE(iCluster->getSize() == 1);
	formationEnergy = iCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy,5.0, 0.001);
	BOOST_REQUIRE_CLOSE(iCluster->getMigrationEnergy(),0.7777,0.0001);
	BOOST_REQUIRE_CLOSE(iCluster->getDiffusionFactor(),3.456,0.001);
=======
	auto vCluster = (PSICluster *) network->get("V", 50);
	BOOST_REQUIRE(vCluster->getSize() == 50);
	formationEnergy = vCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy, 3.6, 0.001);
	BOOST_REQUIRE_CLOSE(vCluster->getMigrationEnergy(), 0.888, 0.001);
	BOOST_REQUIRE_CLOSE(vCluster->getDiffusionFactor(), 2.345, 0.001);
	// I
	auto iCluster = (PSICluster *) network->get("I", 1);
	BOOST_REQUIRE(iCluster->getSize() == 1);
	formationEnergy = iCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy, 5.0, 0.001);
	BOOST_REQUIRE_CLOSE(iCluster->getMigrationEnergy(), 0.7777, 0.0001);
	BOOST_REQUIRE_CLOSE(iCluster->getDiffusionFactor(), 3.456, 0.001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// HeV
	vector<int> composition;
	composition.push_back(1);
	composition.push_back(50);
	composition.push_back(0);
<<<<<<< HEAD
	auto heVCluster = (PSICluster *) network->getCompound("HeV",composition);
	BOOST_REQUIRE(heVCluster->getSize() == 51);
	formationEnergy = heVCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy, 2.49, 0.001);
	BOOST_REQUIRE_CLOSE(heVCluster->getMigrationEnergy(),6.789,0.001);
	BOOST_REQUIRE_CLOSE(heVCluster->getDiffusionFactor(),4.5678,0.0001);
=======
	auto heVCluster = (PSICluster *) network->getCompound("HeV", composition);
	BOOST_REQUIRE(heVCluster->getSize() == 51);
	formationEnergy = heVCluster->getFormationEnergy();
	BOOST_REQUIRE_CLOSE(formationEnergy, 2.49, 0.001);
	BOOST_REQUIRE_CLOSE(heVCluster->getMigrationEnergy(), 6.789, 0.001);
	BOOST_REQUIRE_CLOSE(heVCluster->getDiffusionFactor(), 4.5678, 0.0001);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	// Reload the network stream with the bad string
	(*networkStream).clear();
	*networkStream << badString;
	// Make sure the exception is caught when loading the bad string
	try {
		loader.load();
	} catch (const string& /* error */) {
		// Do nothing but flip the flag
		caughtFlag = true;
	}
	BOOST_REQUIRE(caughtFlag);
}

BOOST_AUTO_TEST_SUITE_END()
