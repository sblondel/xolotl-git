#ifndef FUELFITFLUXHANDLER_H
#define FUELFITFLUXHANDLER_H

#include "FluxHandler.h"
#include <cmath>

namespace xolotlCore {

/**
 * This class realizes the IFluxHandler interface to calculate the incident xenon flux
 * for nuclear fuel.
 */
class FuelFitFluxHandler: public FluxHandler {
private:

	/**
	 * Function that calculate the flux at a given position x (in nm).
	 * This function is not normalized. The surface is supposed to be (100).
	 *
	 * @param x The position where to evaluate he fit
	 * @return The evaluated value
	 */
	double FitFunction(double x) {
		return 1.0;
	}

public:

	/**
	 * The constructor
	 */
<<<<<<< HEAD
	FuelFitFluxHandler() {}
=======
	FuelFitFluxHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The Destructor
	 */
<<<<<<< HEAD
	~FuelFitFluxHandler() {}
=======
	~FuelFitFluxHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Compute and store the incident flux values at each grid point.
	 * \see IFluxHandler.h
	 */
<<<<<<< HEAD
	void initializeFluxHandler(IReactionNetwork *network,
			int surfacePos, std::vector<double> grid) {
=======
	void initializeFluxHandler(const IReactionNetwork& network, int surfacePos,
			std::vector<double> grid) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Call the general method
		FluxHandler::initializeFluxHandler(network, surfacePos, grid);

		// Set the flux index corresponding the the single xenon cluster here
<<<<<<< HEAD
		auto fluxCluster = network->get(xeType, 1);
=======
		auto fluxCluster = network.get(Species::Xe, 1);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Check that the helium cluster is present in the network
		if (!fluxCluster) {
			throw std::string(
					"\nThe single xenon cluster is not present in the network, "
<<<<<<< HEAD
					"cannot use the flux option!");
		}
		fluxIndex = fluxCluster->getId() - 1;
=======
							"cannot use the flux option!");
		}
		fluxIndices.push_back(fluxCluster->getId() - 1);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		return;
	}

};
//end class FuelFitFluxHandler

}

#endif
