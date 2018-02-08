#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <PSICluster.h>
#include "SimpleReactionNetwork.h"
<<<<<<< HEAD
#include <HeVCluster.h>
#include <HeCluster.h>
#include <VCluster.h>
#include <InterstitialCluster.h>
#include <HeInterstitialCluster.h>
=======
#include <PSIHeVCluster.h>
#include <PSIHeCluster.h>
#include <PSIVCluster.h>
#include <PSIInterstitialCluster.h>
#include <PSIHeInterstitialCluster.h>
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
#include <xolotlPerf.h>

using namespace std;
using namespace xolotlCore;
using namespace testUtils;

static std::shared_ptr<xolotlPerf::IHandlerRegistry> registry =
		std::make_shared<xolotlPerf::DummyHandlerRegistry>();

/**
 * This suite is responsible for testing the ReactionNetwork
 */
BOOST_AUTO_TEST_SUITE(PSIReactionNetwork_testSuite)

BOOST_AUTO_TEST_CASE(checkReactants) {
	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

	// Add a few He, V and I PSIClusters
<<<<<<< HEAD
	auto heCluster = make_shared<HeCluster>(10, registry);
	auto vCluster = make_shared<VCluster>(4, registry);
	auto interstitialCluster = make_shared<InterstitialCluster>(48, registry);
	psiNetwork->add(heCluster);
	psiNetwork->add(vCluster);
	psiNetwork->add(interstitialCluster);

	// Check the network, He first
	auto retHeCluster = (PSICluster *) psiNetwork->get("He", 10);
=======
	auto heCluster = std::unique_ptr<PSIHeCluster>(
			new PSIHeCluster(10, *(psiNetwork.get()), registry));
	auto vCluster = std::unique_ptr<PSIVCluster>(
			new PSIVCluster(4, *(psiNetwork.get()), registry));
	auto interstitialCluster = std::unique_ptr<PSIInterstitialCluster>(
			new PSIInterstitialCluster(48, *(psiNetwork.get()), registry));
	psiNetwork->add(std::move(heCluster));
	psiNetwork->add(std::move(vCluster));
	psiNetwork->add(std::move(interstitialCluster));

	// Check the network, He first
	auto retHeCluster = (PSICluster *) psiNetwork->get(Species::He, 10);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	BOOST_REQUIRE(retHeCluster);
	BOOST_REQUIRE_EQUAL("He_10", retHeCluster->getName());
	BOOST_REQUIRE_EQUAL(10, retHeCluster->getSize());
	// V
<<<<<<< HEAD
	auto retVCluster = (PSICluster *) psiNetwork->get("V", 4);
=======
	auto retVCluster = (PSICluster *) psiNetwork->get(Species::V, 4);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	BOOST_REQUIRE(retVCluster);
	BOOST_REQUIRE_EQUAL(4, retVCluster->getSize());
	BOOST_REQUIRE_EQUAL("V_4", retVCluster->getName());
	// I
<<<<<<< HEAD
	auto retICluster = (PSICluster *) psiNetwork->get("I", 48);
=======
	auto retICluster = (PSICluster *) psiNetwork->get(Species::I, 48);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	BOOST_REQUIRE(retICluster);
	BOOST_REQUIRE_EQUAL(48, retICluster->getSize());
	BOOST_REQUIRE_EQUAL("I_48", retICluster->getName());

	// Check the getter for all reactants
<<<<<<< HEAD
	auto clusters = psiNetwork->getAll();
	BOOST_REQUIRE_EQUAL(3U, clusters->size());
=======
	auto& clusters = psiNetwork->getAll();
	BOOST_REQUIRE_EQUAL(3U, clusters.size());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
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
<<<<<<< HEAD
			shared_ptr<HeVCluster> cluster = std::make_shared<HeVCluster>(numHe,
					numV, registry);
			psiNetwork->add(cluster);
=======
			auto cluster = std::unique_ptr<PSIHeVCluster>(
					new PSIHeVCluster(numHe, numV, *(psiNetwork.get()),
							registry));
			psiNetwork->add(std::move(cluster));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			counter++;
		}
	}

	BOOST_TEST_MESSAGE("Added " << counter << " HeV clusters");

	// Add a whole bunch of HeI clusters to make sure that the network can
	// handle large numbers of them properly too. Use a different max cluster
	// size to throw a little variability at the network.
	counter = 0;
	maxClusterSize = 9;
	for (int numI = 1; numI <= maxClusterSize; numI++) {
		for (int numHe = 1; numHe + numI <= maxClusterSize; numHe++) {
<<<<<<< HEAD
			shared_ptr<HeInterstitialCluster> cluster(
					new HeInterstitialCluster(numHe, numI, registry));
			psiNetwork->add(cluster);
=======
			auto cluster = std::unique_ptr<PSIHeInterstitialCluster>(
					new PSIHeInterstitialCluster(numHe, numI,
							*(psiNetwork.get()), registry));
			psiNetwork->add(std::move(cluster));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			counter++;
		}
	}

	BOOST_TEST_MESSAGE("Added " << counter << " HeI clusters");

	// Try adding a duplicate HeV and catch the exception
<<<<<<< HEAD
	shared_ptr<HeVCluster> duplicateCluster = std::make_shared<HeVCluster>(5, 3,
			registry);
	try {
		psiNetwork->add(duplicateCluster);
=======
	auto duplicateCluster = std::unique_ptr<PSIHeVCluster>(
			new PSIHeVCluster(5, 3, *(psiNetwork.get()), registry));
	try {
		psiNetwork->add(std::move(duplicateCluster));
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		BOOST_FAIL(
				"Test failed because adding a duplicate" << " to the network was allowed.");
	} catch (const std::string& /* e */) {
		// Do nothing. It was supposed to fail.
	}

	// Make sure that everything was added
<<<<<<< HEAD
	auto reactants = psiNetwork->getAll();
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
	auto& reactants = psiNetwork->getAll();
	BOOST_REQUIRE_EQUAL(84U, reactants.size());

	// Get the clusters by type and check them. Start with He.
	auto& heReactants = psiNetwork->getAll(ReactantType::He);
	auto& heReactant = heReactants.begin()->second;
	BOOST_REQUIRE_EQUAL(1U, heReactants.size());
	BOOST_REQUIRE_EQUAL("He_10", heReactant->getName());
	// V
	auto& vReactants = psiNetwork->getAll(ReactantType::V);
	auto& vReactant = vReactants.begin()->second;
	BOOST_REQUIRE_EQUAL(1U, vReactants.size());
	BOOST_REQUIRE_EQUAL("V_4", vReactant->getName());
	// I
	auto& iReactants = psiNetwork->getAll(ReactantType::I);
	auto& iReactant = iReactants.begin()->second;
	BOOST_REQUIRE_EQUAL(1U, iReactants.size());
	BOOST_REQUIRE_EQUAL("I_48", iReactant->getName());

	// HeV
	auto& heVReactants = psiNetwork->getAll(ReactantType::HeV);
	BOOST_REQUIRE_EQUAL(45U, heVReactants.size());
	// HeI
	auto& heIReactants = psiNetwork->getAll(ReactantType::HeI);
	BOOST_REQUIRE_EQUAL(36U, heIReactants.size());

	// Add the required He_1, V_1, I_1 clusters to the network.
	heCluster = std::unique_ptr<PSIHeCluster>(
			new PSIHeCluster(1, *(psiNetwork.get()), registry));
	vCluster = std::unique_ptr<PSIVCluster>(
			new PSIVCluster(1, *(psiNetwork.get()), registry));
	interstitialCluster = std::unique_ptr<PSIInterstitialCluster>(
			new PSIInterstitialCluster(1, *(psiNetwork.get()), registry));
	psiNetwork->add(std::move(heCluster));
	psiNetwork->add(std::move(vCluster));
	psiNetwork->add(std::move(interstitialCluster));

	// Try changing the temperature and make sure it works
	psiNetwork->setTemperature(1000.0);
	IReactant& reactant = reactants.at(0);
	BOOST_REQUIRE_CLOSE(1000.0, reactant.getTemperature(), 0.0001);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

BOOST_AUTO_TEST_CASE(checkProperties) {
	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

<<<<<<< HEAD
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

	// Add a couple of clusters
	auto heCluster = make_shared<HeCluster>(5, registry);
	psiNetwork->add(heCluster);
	auto heVCluster = make_shared<HeVCluster>(5, 3, registry);
	psiNetwork->add(heVCluster);

	// Grab the properties afresh
	numHeClusters = psiNetwork->getNumHeClusters();
	maxHeClusterSize = psiNetwork->getMaxHeClusterSize();
	numHeVClusters = psiNetwork->getNumHeVClusters();
	maxHeVClusterSize = psiNetwork->getMaxHeVClusterSize();

	// Check the properties again
	BOOST_REQUIRE_EQUAL(1, numHeClusters);
	BOOST_REQUIRE_EQUAL(1, numHeVClusters);
	BOOST_REQUIRE_EQUAL(5, maxHeClusterSize);
	BOOST_REQUIRE_EQUAL(8, maxHeVClusterSize);
=======
	// Check the properties
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::He), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::V), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::I), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::HeV), 0);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::HeI), 0);

	// Add a couple of clusters
	auto heCluster = std::unique_ptr<PSIHeCluster>(
			new PSIHeCluster(5, *(psiNetwork.get()), registry));
	psiNetwork->add(std::move(heCluster));
	auto heVCluster = std::unique_ptr<PSIHeVCluster>(
			new PSIHeVCluster(5, 3, *(psiNetwork.get()), registry));
	psiNetwork->add(std::move(heVCluster));

	// Check the properties again
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::He), 5);
	BOOST_REQUIRE_EQUAL(psiNetwork->getMaxClusterSize(ReactantType::HeV), 8);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

BOOST_AUTO_TEST_CASE(checkNames) {
	// Create the network
	auto psiNetwork = make_shared<PSIClusterReactionNetwork>(registry);

<<<<<<< HEAD
	// Check the names of the regular cluster types. Use a simple counting
	// system to look over the list since there is no way to check exact
	// containment with a vector.
	auto names = psiNetwork->getNames();
	unsigned int marker = 0;
	for (unsigned int i = 0; i < names.size(); i++) {
		if (names[i] == "He")
			++marker;
		else if (names[i] == "V")
			++marker;
		else if (names[i] == "I")
			++marker;
	}
	BOOST_REQUIRE_EQUAL(3U, marker);
	BOOST_REQUIRE_EQUAL(marker, names.size());

	// Check the names of the compound cluster types. Use the same counting
	// system as above.
	auto compoundNames = psiNetwork->getCompoundNames();
	marker = 0;
	for (unsigned int i = 0; i < compoundNames.size(); i++) {
		if (compoundNames[i] == "HeV")
			++marker;
		else if (compoundNames[i] == "HeI")
			++marker;
		else if (compoundNames[i] == "PSISuper")
			++marker;
	}
	BOOST_REQUIRE_EQUAL(3U, marker);
	BOOST_REQUIRE_EQUAL(marker, compoundNames.size());

	return;
}

/**
 * This operation tests the copy constructor.
 */
BOOST_AUTO_TEST_CASE(checkCopying) {
	//PSIClusterReactionNetwork network;
	PSIClusterReactionNetwork network(registry);

	// Add a reactant
	shared_ptr<Reactant> heCluster(new HeCluster(1, registry));
	heCluster->setConcentration(50.0);
	network.add(heCluster);

	// Copy the network
	PSIClusterReactionNetwork networkCopy = network;

	// Check that the ReactionNetwork fields are copied
	BOOST_REQUIRE_EQUAL(network.getNumHeClusters(),
			networkCopy.getNumHeClusters());

	// Check that changing the concentration of a copy does not update the
	// original. Start by updating the copy.
	auto copiedHeCluster = networkCopy.get("He", 1);
	copiedHeCluster->setConcentration(7.0);
	BOOST_REQUIRE_CLOSE(7.0, copiedHeCluster->getConcentration(), 1.0e-5);
	// Make sure the original wasn't changed.
	BOOST_REQUIRE_CLOSE(50.0, heCluster->getConcentration(), 1.0e-5);

	// Check the size of the network
	BOOST_REQUIRE_EQUAL(1, networkCopy.size());
=======
	// Check the names of all cluster types. Use a simple counting
	// system to look over the list.
	auto names = psiNetwork->getKnownReactantTypes();
	unsigned int marker = 0;
	for (auto name : names) {
		if (name == ReactantType::He)
			++marker;
		else if (name == ReactantType::V)
			++marker;
		else if (name == ReactantType::I)
			++marker;
		else if (name == ReactantType::PSISuper)
			++marker;
		else if (name == ReactantType::HeV)
			++marker;
		else if (name == ReactantType::HeI)
			++marker;
	}
	BOOST_REQUIRE_EQUAL(6U, marker);
	BOOST_REQUIRE_EQUAL(marker, names.size());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

/**
 * This operation tests the operations of the ReactionNetwork that copy the
 * concentrations to and from a client array.
 */
BOOST_AUTO_TEST_CASE(checkArrayOperations) {
	// Local Declarations
	shared_ptr<ReactionNetwork> network = getSimplePSIReactionNetwork();
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
		BOOST_REQUIRE_CLOSE(1.0, reactants->at(0)->getConcentration(), 1.0e-15);
=======
		IReactant& reactant = reactants.at(i);
		BOOST_REQUIRE_CLOSE(1.0, reactant.getConcentration(), 1.0e-15);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Clear memory
	delete[] concentrations;

	return;
}

<<<<<<< HEAD
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
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
BOOST_AUTO_TEST_SUITE_END()
