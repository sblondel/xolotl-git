// Includes
#include "HeInterstitialCluster.h"

using namespace xolotlCore;

HeInterstitialCluster::HeInterstitialCluster(int numHelium, int numInterstitial) : PSICluster(1) {
	numHe = numHelium;
	numI = numInterstitial;
	size = numHe + numI;
	name = "He-Interstitial Cluster";
}

HeInterstitialCluster::HeInterstitialCluster(std::map<std::string, int> speciesMap) :
		PSICluster(1) {
	numHe = speciesMap["He"];
	numI = speciesMap["I"];
	size = numHe + numI;
	// Set the reactant name appropriately
	name = "He-Interstitial Cluster";
}

HeInterstitialCluster::~HeInterstitialCluster() {
}

double HeInterstitialCluster::getGenByEm() {
	return 0;
}

double HeInterstitialCluster::getAnnByEm() {
	return 0;
}

int HeInterstitialCluster::getSpeciesSize(const std::string speciesName) {
	return 0;
}

double HeInterstitialCluster::getDissociationFlux(const double temperature) {

	// Local Declarations
	int vIndex = -1, iIndex = -1, heIndex = -1;
	int thisIndex = network->toClusterIndex(getClusterMap());
	std::map<std::string, int> oneHe;
	std::map<std::string, int> oneV;
	std::map<std::string, int> oneI;

	// Set the cluster map data for 1 of each species
	oneHe["He"] = 1; oneHe["V"] = 0; oneHe["I"] = 0;
	oneV["He"] = 0; oneV["V"] = 1; oneV["I"] = 0;
	oneI["He"] = 0; oneI["V"] = 0; oneI["I"] = 1;

	// Get their indices in the array
	int oneHeIndex = network->toClusterIndex(oneHe);
	int oneVIndex = network->toClusterIndex(oneV);
	int oneIIndex = network->toClusterIndex(oneI);

	// Find the indices such that they are the index of the
	// concentration in C_bar that contain one additional species
	// than this reactant
	for (int k = 0; k < network->reactants->size(); k++) {
		if ((network->toClusterMap(k)["He"] - numHe) == 1 && heIndex == -1) {
			heIndex = k;
		}
		if (network->toClusterMap(k)["V"] == 1 && vIndex == -1) {
			vIndex = k;
		}
		if ((network->toClusterMap(k)["I"] - numI) == 1 && iIndex == -1) {
			iIndex = k;
		}
	}

	// Calculate and return the dissociation constant
	return calculateDissociationConstant(vIndex, oneVIndex, temperature)
			* network->reactants->at(vIndex)->getConcentration()
			+ calculateDissociationConstant(iIndex, oneIIndex, temperature)
					* network->reactants->at(iIndex)->getConcentration()
			+ calculateDissociationConstant(heIndex, oneHeIndex, temperature)
					* network->reactants->at(heIndex)->getConcentration()
			- (calculateDissociationConstant(thisIndex, oneVIndex, temperature)
					+ calculateDissociationConstant(thisIndex, oneIIndex,
							temperature)
					+ calculateDissociationConstant(thisIndex, oneHeIndex,
							temperature)) * getConcentration();
}

std::vector<int> HeInterstitialCluster::getConnectivity() {
	
	// Local Declarations
	std::map<std::string, std::string> &properties = *network->properties;
	
	int numHeClusters = std::stoi(properties["numHeClusters"]);
	int numVClusters = std::stoi(properties["numVClusters"]);
	int numIClusters = std::stoi(properties["numIClusters"]);
	int numSingleSpeciesClusters = numHeClusters + numVClusters + numIClusters;
	
	int maxMixedClusterSize = std::stoi(properties["maxMixedClusterSize"]);
	
	// Initialize the return array with zeroes
	std::vector<int> connectivityArray(network->reactants->size(), 0);
	
	
	// This cluster is involved in the following interactions:
	
	// Growth through helium absorption
	// xHe * yI + zHe --> (x+z)He * yI
	// under the condition that x + y + z <= maxSize
	for (int numHeOther = 1; numHe + numI + numHeOther <= numHeClusters;
		numHeOther++) {
		
		std::map<std::string, int> speciesMap;
		speciesMap["He"] = numHeOther;
		int indexOther = network->toClusterIndex(speciesMap);
		connectivityArray[indexOther] = 1;
	}
	
	// Interstitial absorption (single)
	// xHe * yI + I --> xHe * (y + 1)I
	// if x + y + 1 <= maxSize
	if (numHe + numI + 1 <= maxMixedClusterSize) {
		
		std::map<std::string, int> speciesMap;
		speciesMap["I"] = 1;
		int indexOther = network->toClusterIndex(speciesMap);
		connectivityArray[indexOther] = 1;
	}
	
	// Reduction through vacancy absorption
	// xHe * yI + zV --> xHe * (y - z)I
	for (int numVOther = 1; numI - numVOther >= 1; numVOther++) {
		
		std::map<std::string, int> speciesMap;
		speciesMap["V"] = numVOther;
		int indexOther = network->toClusterIndex(speciesMap);
		connectivityArray[indexOther] = 1;
	}
	
	
	return connectivityArray;
}

std::map<std::string, int> HeInterstitialCluster::getClusterMap() {
	// Local Declarations
	std::map<std::string, int> clusterMap;

	// Set the number of each species
	clusterMap["He"] = numHe;
	clusterMap["V"] = 0;
	clusterMap["I"] = numI;

	// Return it
	return clusterMap;
}