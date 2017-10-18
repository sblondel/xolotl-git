// Includes
#include "VCluster.h"
#include <iostream>
#include <Constants.h>
#include <PSIClusterReactionNetwork.h>

using namespace xolotlCore;

VCluster::VCluster(int nV,
        IReactionNetwork& _network,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSICluster(_network, registry, buildName(nV)) {

	// Set the size
	size = nV;
	// Set the typename appropriately
	type = ReactantType::V;

	// Update the composition map
	composition[toCompIdx(Species::V)] = size;

	// Compute the reaction radius
	// It is the same formula for HeV clusters
	reactionRadius = xolotlCore::tungstenLatticeConstant
			* pow((3.0 * size) / xolotlCore::pi, (1.0 / 3.0)) * 0.5;

	// Bounds on He and V
	heBounds = IntegerRange<IReactant::SizeType>(
			static_cast<IReactant::SizeType>(0),
			static_cast<IReactant::SizeType>(1));
	vBounds = IntegerRange<IReactant::SizeType>(
			static_cast<IReactant::SizeType>(size),
			static_cast<IReactant::SizeType>(size+1));

	return;
}

double VCluster::getEmissionFlux() const {
	// Initial declarations
	double flux = PSICluster::getEmissionFlux();

	// Compute the loss to dislocation sinks
	if (size < 5) {
		// k^2 * D * C
		flux += xolotlCore::sinkStrength * diffusionCoefficient * concentration;
	}

	return flux;
}

void VCluster::getEmissionPartialDerivatives(
		std::vector<double> & partials) const {
	// Initial declarations
	PSICluster::getEmissionPartialDerivatives(partials);

	// Compute the loss to dislocation sinks
	if (size < 5) {
		// k^2 * D * C
		partials[id - 1] -= xolotlCore::sinkStrength * diffusionCoefficient;
	}

	return;
}
