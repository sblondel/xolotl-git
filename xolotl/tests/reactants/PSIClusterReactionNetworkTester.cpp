<<<<<<< HEAD
=======
/*
 * PSIClusterTester.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Jay Jay Billings
 */
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSICluster.h>
<<<<<<< HEAD
=======
#include <map>
#include <memory>
#include <typeinfo>
#include <limits>
#include <math.h>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include "SimpleReactionNetwork.h"
#include <HeVCluster.h>
#include <HeCluster.h>
#include <VCluster.h>
#include <InterstitialCluster.h>
#include <HeInterstitialCluster.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <xolotlPerf.h>
=======
#include "../../xolotlPerf/HandlerRegistryFactory.h"
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include <xolotlPerf/HandlerRegistryFactory.h>
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618

using namespace std;
using namespace xolotlCore;
using namespace testUtils;

<<<<<<< HEAD
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();

/**
 * This suite is responsible for testing the ReactionNetwork
 */
BOOST_AUTO_TEST_SUITE(PSIReactionNetwork_testSuite)

BOOST_AUTO_TEST_CASE(checkReactants) {
=======
static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry = std::make_shared<xolotlPerf::DummyHandlerRegistry>();

/**
 * This suite is responsible for testing the ReactionNetwork
 */BOOST_AUTO_TEST_SUITE(PSIReactionNetwork_testSuite)

BOOST_AUTO_TEST_CASE(checkCompositionCreation) {

	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

	// Get an HeV cluster with sizes 5,10
	auto heVComp = psiNetwork->getCompositionVector(5, 10, 0);
	BOOST_REQUIRE_EQUAL(3, heVComp.size());
	BOOST_REQUIRE_EQUAL(5, heVComp[0]);
	BOOST_REQUIRE_EQUAL(10, heVComp[1]);
	BOOST_REQUIRE_EQUAL(0, heVComp[2]);

	// Get an interstitial cluster with size 99
	auto intComp = psiNetwork->getCompositionVector(0, 0, 99);
	BOOST_REQUIRE_EQUAL(3, intComp.size());
	BOOST_REQUIRE_EQUAL(0, intComp[0]);
	BOOST_REQUIRE_EQUAL(0, intComp[1]);
	BOOST_REQUIRE_EQUAL(99, intComp[2]);

	// Try to get something bad
	auto badComp = psiNetwork->getCompositionVector(-1, -8, -3);
	// Make sure that it gives you single species helium back
	BOOST_REQUIRE_EQUAL(3, badComp.size());
	BOOST_REQUIRE_EQUAL(0, badComp[0]);
	BOOST_REQUIRE_EQUAL(0, badComp[1]);
	BOOST_REQUIRE_EQUAL(0, badComp[2]);
	// Try to get something else bad
	badComp = psiNetwork->getCompositionVector(1, 3, -3);
	// Make sure that it gives you single species helium back
	BOOST_REQUIRE_EQUAL(3, badComp.size());
	BOOST_REQUIRE_EQUAL(0, badComp[0]);
	BOOST_REQUIRE_EQUAL(0, badComp[1]);
	BOOST_REQUIRE_EQUAL(0, badComp[2]);

	return;
}

BOOST_AUTO_TEST_CASE(checkReactants) {

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

	// Add a few He, V and I PSIClusters
	auto heCluster = make_shared<HeCluster>(10, registry);
	auto vCluster = make_shared<VCluster>(4, registry);
	auto interstitialCluster = make_shared<InterstitialCluster>(48, registry);
	psiNetwork->add(heCluster);
	psiNetwork->add(vCluster);
	psiNetwork->add(interstitialCluster);

	// Check the network, He first
<<<<<<< HEAD
<<<<<<< HEAD
	auto retHeCluster = (PSICluster *) psiNetwork->get("He", 10);
	BOOST_REQUIRE(retHeCluster);
	BOOST_REQUIRE_EQUAL("He_10", retHeCluster->getName());
	BOOST_REQUIRE_EQUAL(10, retHeCluster->getSize());
	// V
	auto retVCluster = (PSICluster *) psiNetwork->get("V", 4);
	BOOST_REQUIRE(retVCluster);
	BOOST_REQUIRE_EQUAL(4, retVCluster->getSize());
	BOOST_REQUIRE_EQUAL("V_4", retVCluster->getName());
	// I
	auto retICluster = (PSICluster *) psiNetwork->get("I", 48);
	BOOST_REQUIRE(retICluster);
	BOOST_REQUIRE_EQUAL(48, retICluster->getSize());
	BOOST_REQUIRE_EQUAL("I_48", retICluster->getName());

	// Check the getter for all reactants
	auto clusters = psiNetwork->getAll();
	BOOST_REQUIRE_EQUAL(3U, clusters->size());
=======
	auto retHeCluster = dynamic_pointer_cast<PSICluster>(
			psiNetwork->get("He", 10));
=======
	auto retHeCluster = (PSICluster *)
			psiNetwork->get("He", 10);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
	BOOST_REQUIRE(retHeCluster);
	BOOST_REQUIRE_EQUAL("He_10", retHeCluster->getName());
	BOOST_REQUIRE_EQUAL(10, retHeCluster->getSize());
	// V
	auto retVCluster = (PSICluster *)
			psiNetwork->get("V", 4);
	BOOST_REQUIRE(retVCluster);
	BOOST_REQUIRE_EQUAL(4, retVCluster->getSize());
	BOOST_REQUIRE_EQUAL("V_4", retVCluster->getName());
	// I
	auto retICluster = (PSICluster *)
			psiNetwork->get("I", 48);
	BOOST_REQUIRE(retICluster);
	BOOST_REQUIRE_EQUAL(48, retICluster->getSize());
	BOOST_REQUIRE_EQUAL("I_48", retICluster->getName());

	// Check the getter for all reactants
	auto clusters = psiNetwork->getAll();
	BOOST_REQUIRE_EQUAL(3, clusters->size());
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	// Check the size of the network
	BOOST_REQUIRE_EQUAL(3, psiNetwork->size());

	// Check the cluster ids. All we can do is check that they are between 1
	// and 5. Start with the He cluster
	int id = retHeCluster->getId();
	BOOST_REQUIRE(id > 0 && id <= 5);
	// V
	id = retVCluster->getId();
	BOOST_REQUIRE(id > 0 && id <= 5);
	// I
	id = retICluster->getId();
	BOOST_REQUIRE(id > 0 && id <= 5);

	// Add a whole bunch of HeV clusters to make sure that the network can
	// handle large numbers of them properly.
	int counter = 0;
	int maxClusterSize = 10;
	for (int numV = 1; numV <= maxClusterSize; numV++) {
		for (int numHe = 1; numHe + numV <= maxClusterSize; numHe++) {
			shared_ptr<HeVCluster> cluster = std::make_shared<HeVCluster>(numHe,
					numV, registry);
			psiNetwork->add(cluster);
			counter++;
		}
	}
<<<<<<< HEAD

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	BOOST_TEST_MESSAGE("Added " << counter << " HeV clusters");

	// Add a whole bunch of HeI clusters to make sure that the network can
	// handle large numbers of them properly too. Use a different max cluster
	// size to throw a little variability at the network.
	counter = 0;
	maxClusterSize = 9;
	for (int numI = 1; numI <= maxClusterSize; numI++) {
		for (int numHe = 1; numHe + numI <= maxClusterSize; numHe++) {
			shared_ptr<HeInterstitialCluster> cluster(
					new HeInterstitialCluster(numHe, numI, registry));
			psiNetwork->add(cluster);
			counter++;
		}
	}
<<<<<<< HEAD

	BOOST_TEST_MESSAGE("Added " << counter << " HeI clusters");

	// Try adding a duplicate HeV and catch the exception
	shared_ptr<HeVCluster> duplicateCluster = std::make_shared<HeVCluster>(5, 3,
			registry);
	try {
		psiNetwork->add(duplicateCluster);
		BOOST_FAIL(
				"Test failed because adding a duplicate" << " to the network was allowed.");
	} catch (const std::string& /* e */) {
=======
	BOOST_TEST_MESSAGE("Added " << counter << " HeI clusters");

	// Try adding a duplicate HeV and catch the exception
	shared_ptr<HeVCluster> duplicateCluster = std::make_shared<HeVCluster>(5,
			3, registry);
	try {
		psiNetwork->add(duplicateCluster);
		BOOST_FAIL(
				"Test failed because adding a duplicate"
						<< " to the network was allowed.");
	} catch (const std::string & e) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
		// Do nothing. It was supposed to fail.
	}

	// Make sure that everything was added
	auto reactants = psiNetwork->getAll();
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(84U, reactants->size());
	// Get the clusters by type and check them. Start with He.
	auto heReactants = psiNetwork->getAll("He");
	BOOST_REQUIRE_EQUAL(1U, heReactants.size());
	BOOST_REQUIRE_EQUAL("He_10", heReactants[0]->getName());
	// V
	auto vReactants = psiNetwork->getAll("V");
	BOOST_REQUIRE_EQUAL(1U, vReactants.size());
	BOOST_REQUIRE_EQUAL("V_4", vReactants[0]->getName());
	// I
	auto iReactants = psiNetwork->getAll("I");
	BOOST_REQUIRE_EQUAL(1U, iReactants.size());
	BOOST_REQUIRE_EQUAL("I_48", iReactants[0]->getName());
	// HeV
	auto heVReactants = psiNetwork->getAll("HeV");
	BOOST_REQUIRE_EQUAL(45U, heVReactants.size());

	// HeI
	auto heIReactants = psiNetwork->getAll("HeI");
	BOOST_REQUIRE_EQUAL(36U, heIReactants.size());

	// Add the required He_1, V_1, I_1 clusters to the network.
	psiNetwork->add(make_shared<HeCluster>(1, registry));
	psiNetwork->add(make_shared<VCluster>(1, registry));
	psiNetwork->add(make_shared<InterstitialCluster>(1, registry));

	// Set the reaction networks for all of the clusters
	for (unsigned int i = 0; i < reactants->size(); i++) {
		reactants->at(i)->setReactionNetwork(psiNetwork);
	}

	// Try changing the temperature and make sure it works
	psiNetwork->setTemperature(1000.0);
	BOOST_REQUIRE_CLOSE(1000.0, reactants->at(0)->getTemperature(), 0.0001);
=======
	BOOST_REQUIRE_EQUAL(84, reactants->size());
	// Get the clusters by type and check them. Start with He.
	auto heReactants = psiNetwork->getAll("He");
	BOOST_REQUIRE_EQUAL(1, heReactants.size());
	BOOST_REQUIRE_EQUAL("He_10", heReactants[0]->getName());
	// V
	auto vReactants = psiNetwork->getAll("V");
	BOOST_REQUIRE_EQUAL(1, vReactants.size());
	BOOST_REQUIRE_EQUAL("V_4", vReactants[0]->getName());
	// I
	auto iReactants = psiNetwork->getAll("I");
	BOOST_REQUIRE_EQUAL(1, iReactants.size());
	BOOST_REQUIRE_EQUAL("I_48", iReactants[0]->getName());
	// HeV
	auto heVReactants = psiNetwork->getAll("HeV");
	BOOST_REQUIRE_EQUAL(45, heVReactants.size());

	// HeI
	auto heIReactants = psiNetwork->getAll("HeI");
	BOOST_REQUIRE_EQUAL(36, heIReactants.size());

	// Add the required He_1, V_1, I_1 clusters to the network.
	psiNetwork->add(make_shared<HeCluster>(1,registry));
	psiNetwork->add(make_shared<VCluster>(1,registry));
	psiNetwork->add(make_shared<InterstitialCluster>(1,registry));

	// Set the reaction networks for all of the clusters
	for (int i = 0; i < reactants->size(); i++) {
		reactants->at(i)->setReactionNetwork(psiNetwork);
	}

<<<<<<< HEAD
	// Try to get something that obviously isn't there
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	// Try changing the temperature and make sure it works
	psiNetwork->setTemperature(1000.0);
	BOOST_REQUIRE_CLOSE(1000.0,reactants->at(0)->getTemperature(),0.0001);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618

	return;
}

BOOST_AUTO_TEST_CASE(checkProperties) {
<<<<<<< HEAD
	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

	// Access the network "properties."
	auto numHeClusters = psiNetwork->getNumHeClusters();
	auto numVClusters = psiNetwork->getNumVClusters();
	auto numIClusters = psiNetwork->getNumIClusters();
	auto numHeVClusters = psiNetwork->getNumHeVClusters();
	auto numHeIClusters = psiNetwork->getNumHeIClusters();
	auto maxHeVClusterSize = psiNetwork->getMaxHeVClusterSize();
	auto maxHeIClusterSize = psiNetwork->getMaxHeIClusterSize();
	auto maxHeClusterSize = psiNetwork->getMaxHeClusterSize();
	auto maxVClusterSize = psiNetwork->getMaxVClusterSize();
	auto maxIClusterSize = psiNetwork->getMaxIClusterSize();
=======

	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

	// Grab the map of properties from the network
	auto props = psiNetwork->getProperties();
	// Convert the property strings so we can use them
	auto numHeClusters = stoi(props["numHeClusters"]);
	auto numVClusters = stoi(props["numVClusters"]);
	auto numIClusters = stoi(props["numIClusters"]);
	auto numHeVClusters = stoi(props["numHeVClusters"]);
	auto numHeIClusters = stoi(props["numHeIClusters"]);
	auto maxHeVClusterSize = stoi(props["maxHeVClusterSize"]);
	auto maxHeIClusterSize = stoi(props["maxHeIClusterSize"]);
	auto maxHeClusterSize = stoi(props["maxHeClusterSize"]);
	auto maxVClusterSize = stoi(props["maxVClusterSize"]);
	auto maxIClusterSize = stoi(props["maxIClusterSize"]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	// Check the properties
	BOOST_REQUIRE_EQUAL(0, numHeClusters);
	BOOST_REQUIRE_EQUAL(0, numVClusters);
	BOOST_REQUIRE_EQUAL(0, numIClusters);
	BOOST_REQUIRE_EQUAL(0, numHeVClusters);
	BOOST_REQUIRE_EQUAL(0, numHeIClusters);
	BOOST_REQUIRE_EQUAL(0, maxHeVClusterSize);
	BOOST_REQUIRE_EQUAL(0, maxHeIClusterSize);
	BOOST_REQUIRE_EQUAL(0, maxHeClusterSize);
	BOOST_REQUIRE_EQUAL(0, maxVClusterSize);
	BOOST_REQUIRE_EQUAL(0, maxIClusterSize);

<<<<<<< HEAD
=======
	// Set a couple of properties
	psiNetwork->setProperty("rangePenalty", "5");
	psiNetwork->setProperty("agility", "d8");

	// Grab the properties afresh
	auto modifiedProps = psiNetwork->getProperties();

	// Check for the new properties
	auto rangePenalty = modifiedProps["rangePenalty"];
	auto agility = modifiedProps["agility"];
	BOOST_REQUIRE_EQUAL("5", rangePenalty);
	BOOST_REQUIRE_EQUAL("d8", agility);

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	// Add a couple of clusters
	auto heCluster = make_shared<HeCluster>(5, registry);
	psiNetwork->add(heCluster);
	auto heVCluster = make_shared<HeVCluster>(5, 3, registry);
	psiNetwork->add(heVCluster);

	// Grab the properties afresh
<<<<<<< HEAD
	numHeClusters = psiNetwork->getNumHeClusters();
	maxHeClusterSize = psiNetwork->getMaxHeClusterSize();
	numHeVClusters = psiNetwork->getNumHeVClusters();
	maxHeVClusterSize = psiNetwork->getMaxHeVClusterSize();
=======
	auto propsWithClusters = psiNetwork->getProperties();
	numHeClusters = stoi(propsWithClusters["numHeClusters"]);
	maxHeClusterSize = stoi(propsWithClusters["maxHeClusterSize"]);
	numHeVClusters = stoi(propsWithClusters["numHeVClusters"]);
	maxHeVClusterSize = stoi(propsWithClusters["maxHeVClusterSize"]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	// Check the properties again
	BOOST_REQUIRE_EQUAL(1, numHeClusters);
	BOOST_REQUIRE_EQUAL(1, numHeVClusters);
	BOOST_REQUIRE_EQUAL(5, maxHeClusterSize);
	BOOST_REQUIRE_EQUAL(8, maxHeVClusterSize);
<<<<<<< HEAD

	return;
}

BOOST_AUTO_TEST_CASE(checkNames) {
=======
}

BOOST_AUTO_TEST_CASE(checkNames) {

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

	// Check the names of the regular cluster types. Use a simple counting
	// system to look over the list since there is no way to check exact
	// containment with a vector.
	auto names = psiNetwork->getNames();
<<<<<<< HEAD
	unsigned int marker = 0;
	for (unsigned int i = 0; i < names.size(); i++) {
=======
	int marker = 0;
	for (int i = 0; i < names.size(); i++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
		if (names[i] == "He")
			++marker;
		else if (names[i] == "V")
			++marker;
		else if (names[i] == "I")
			++marker;
	}
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(3U, marker);
=======
	BOOST_REQUIRE_EQUAL(3, marker);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	BOOST_REQUIRE_EQUAL(marker, names.size());

	// Check the names of the compound cluster types. Use the same counting
	// system as above.
	auto compoundNames = psiNetwork->getCompoundNames();
	marker = 0;
<<<<<<< HEAD
	for (unsigned int i = 0; i < compoundNames.size(); i++) {
=======
	for (int i = 0; i < compoundNames.size(); i++) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
		if (compoundNames[i] == "HeV")
			++marker;
		else if (compoundNames[i] == "HeI")
			++marker;
<<<<<<< HEAD
		else if (compoundNames[i] == "PSISuper")
			++marker;
	}
	BOOST_REQUIRE_EQUAL(3U, marker);
	BOOST_REQUIRE_EQUAL(marker, compoundNames.size());

	return;
=======
	}
	BOOST_REQUIRE_EQUAL(2, marker);
	BOOST_REQUIRE_EQUAL(marker, compoundNames.size());
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

/**
 * This operation tests the copy constructor.
<<<<<<< HEAD
 */
BOOST_AUTO_TEST_CASE(checkCopying) {
=======
 */BOOST_AUTO_TEST_CASE(checkCopying) {

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	//PSIClusterReactionNetwork network;
	PSIClusterReactionNetwork network(registry);

	// Add a reactant
	shared_ptr<Reactant> heCluster(new HeCluster(1, registry));
	heCluster->setConcentration(50.0);
	network.add(heCluster);

	// Copy the network
	PSIClusterReactionNetwork networkCopy = network;

	// Check that the ReactionNetwork fields are copied
<<<<<<< HEAD
	BOOST_REQUIRE_EQUAL(network.getNumHeClusters(),
			networkCopy.getNumHeClusters());
=======
	auto properties = network.getProperties();
	auto copiedProperties = networkCopy.getProperties();
	BOOST_REQUIRE_EQUAL(properties.size(), copiedProperties.size());
	BOOST_REQUIRE_EQUAL(properties["numHeClusters"],
			copiedProperties["numHeClusters"]);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	// Check that changing the concentration of a copy does not update the
	// original. Start by updating the copy.
	auto copiedHeCluster = networkCopy.get("He", 1);
	copiedHeCluster->setConcentration(7.0);
	BOOST_REQUIRE_CLOSE(7.0, copiedHeCluster->getConcentration(), 1.0e-5);
	// Make sure the original wasn't changed.
	BOOST_REQUIRE_CLOSE(50.0, heCluster->getConcentration(), 1.0e-5);

	// Check the size of the network
	BOOST_REQUIRE_EQUAL(1, networkCopy.size());
<<<<<<< HEAD

	return;
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

/**
 * This operation tests the operations of the ReactionNetwork that copy the
 * concentrations to and from a client array.
<<<<<<< HEAD
 */
BOOST_AUTO_TEST_CASE(checkArrayOperations) {
	// Local Declarations
	shared_ptr<ReactionNetwork> network = getSimplePSIReactionNetwork();
=======
 */BOOST_AUTO_TEST_CASE(checkArrayOperations) {

	// Local Declarations
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork();
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	int size = network->size();
	double * concentrations = new double[size];

	// Set default values
	for (int i = 0; i < size; i++) {
		concentrations[i] = 1.0;
	}

	// Set the array to the values in the Reaction network, which should
	// all be zero.
	network->fillConcentrationsArray(concentrations);
	for (int i = 0; i < size; i++) {
		BOOST_REQUIRE_CLOSE(0.0, concentrations[i], 1.0e-15);
	}

	// Reset values to something else
	for (int i = 0; i < size; i++) {
		concentrations[i] = 1.0;
	}

	// Update the network and check it
	network->updateConcentrationsFromArray(concentrations);
	auto reactants = network->getAll();
	for (int i = 0; i < size; i++) {
<<<<<<< HEAD
<<<<<<< HEAD
		BOOST_REQUIRE_CLOSE(1.0, reactants->at(0)->getConcentration(), 1.0e-15);
	}

	// Clear memory
	delete[] concentrations;

	return;
}

BOOST_AUTO_TEST_CASE(checkRefCounts) {
	// Obtain a network to work with.
	// This network was built programmatically.
	shared_ptr<ReactionNetwork> network = getSimplePSIReactionNetwork();

	// Because each Reactant in the network is given a pointer
	// (a shared_ptr) to the network, and we have one shared_ptr to it,
	// its reference count should be network's size + 1.
	BOOST_TEST_MESSAGE("After creation, network size: " << network->size());
	BOOST_TEST_MESSAGE(
			"After creation, network ref count: " << network.use_count());
	BOOST_REQUIRE_EQUAL(network.use_count(), network->size() + 1);

	// Tell the network to break dependency cycles between
	// the Reactants in the network and the network itself.
	// In a "real" use, this allows the network and Reactants
	// to be destroyed gracefully when the shared_ptr pointing
	// to the network goes out of scope, because it allows
	// the network's reference count to reach zero.
	network->askReactantsToReleaseNetwork();

	// All objects from within the network should have released their
	// shared_ptr to the network, so our shared_ptr should be the
	// only remaining shared_ptr.  Thus, the network's reference
	// count should be 1 at this point.
	// If it is, when our shared_ptr goes out of scope the network will
	// be destroyed.  We can't easily test that it is destroyed.
	BOOST_TEST_MESSAGE(
			"After releasing network refs, network size: " << network->size());
	BOOST_TEST_MESSAGE(
			"After releasing network refs, network ref count: " << network.use_count());
	BOOST_REQUIRE_EQUAL(network.use_count(), 1);

	return;
}

=======
		BOOST_REQUIRE_CLOSE(1.0, reactants->at(i)->getConcentration(), 1.0e-15);
=======
		BOOST_REQUIRE_CLOSE(1.0, reactants->at(0)->getConcentration(), 1.0e-15);
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
	}
}
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======


BOOST_AUTO_TEST_CASE(checkRefCounts) {

    // Obtain a network to work with.
    // This network was built programmatically.
	shared_ptr<ReactionNetwork> network = getSimpleReactionNetwork();
    
    // Because each Reactant in the network is given a pointer
    // (a shared_ptr) to the network, and we have one shared_ptr to it,
    // its reference count should be network's size + 1.
	BOOST_TEST_MESSAGE("After creation, network size: " << network->size());
	BOOST_TEST_MESSAGE("After creation, network ref count: " << network.use_count());
    BOOST_REQUIRE_EQUAL(network.use_count(), network->size() + 1);
    
    // Tell the network to break dependency cycles between 
    // the Reactants in the network and the network itself.
    // In a "real" use, this allows the network and Reactants
    // to be destroyed gracefully when the shared_ptr pointing
    // to the network goes out of scope, because it allows
    // the network's reference count to reach zero.
    network->askReactantsToReleaseNetwork();

    // All objects from within the network should have released their
    // shared_ptr to the network, so our shared_ptr should be the
    // only remaining shared_ptr.  Thus, the network's reference
    // count should be 1 at this point.
    // If it is, when our shared_ptr goes out of scope the network will 
    // be destroyed.  We can't easily test that it is destroyed.
	BOOST_TEST_MESSAGE("After releasing network refs, network size: " << network->size());
	BOOST_TEST_MESSAGE("After releasing network refs, network ref count: " << network.use_count());
    BOOST_REQUIRE_EQUAL(network.use_count(), 1);
}

>>>>>>> Pulling "break circular dependencies of network and reactant objects" into the HDF5 branch. SB 20140624
BOOST_AUTO_TEST_SUITE_END()
