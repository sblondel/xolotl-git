#ifndef W211FITFLUXHANDLER_H
#define W211FITFLUXHANDLER_H

<<<<<<< HEAD
#include "FluxHandler.h"
=======
#include "PSIFluxHandler.h"
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
#include <cmath>

namespace xolotlCore {

/**
 * This class realizes the IFluxHandler interface to calculate the incident helium flux
 * for a (211) oriented tungsten material.
 */
<<<<<<< HEAD
class W211FitFluxHandler: public FluxHandler {
=======
class W211FitFluxHandler: public PSIFluxHandler {
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
private:

	/**
	 * Function that calculate the flux at a given position x (in nm).
	 * This function is not normalized. The surface is supposed to be (211).
	 *
	 * @param x The position where to evaluate the fit
	 * @return The evaluated value
	 */
	double FitFunction(double x) {
		// Value at which the flux goes to 0
		double x1 = 10.0;

<<<<<<< HEAD
		if (x > x1) return 0.0;

		// Compute the fit
		double value = 4.07203818 + 5.34773722 * x - 4.98297871 * pow(x, 2)
		+ 1.55833787 * pow(x, 3) - 0.234772157 * pow(x, 4) + 0.0165912511 * pow(x, 5)
		- 2.38031874e-04 * pow(x, 6) - 3.18871642e-05 * pow(x, 7) + 1.27931311e-06 * pow(x, 8);
=======
		if (x > x1)
			return 0.0;

		// Compute the fit
		double value = 4.07203818 + 5.34773722 * x - 4.98297871 * pow(x, 2)
				+ 1.55833787 * pow(x, 3) - 0.234772157 * pow(x, 4)
				+ 0.0165912511 * pow(x, 5) - 2.38031874e-04 * pow(x, 6)
				- 3.18871642e-05 * pow(x, 7) + 1.27931311e-06 * pow(x, 8);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		return value;
	}

public:

	/**
	 * The constructor
	 */
<<<<<<< HEAD
	W211FitFluxHandler() {}
=======
	W211FitFluxHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The Destructor
	 */
<<<<<<< HEAD
	~W211FitFluxHandler() {}
=======
	~W211FitFluxHandler() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

<<<<<<< HEAD
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

		// Set the flux index corresponding the the single helium cluster here
<<<<<<< HEAD
		auto fluxCluster = network->get(heType, 1);
=======
		auto fluxCluster = network.get(Species::He, 1);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Check that the helium cluster is present in the network
		if (!fluxCluster) {
			throw std::string(
					"\nThe single helium cluster is not present in the network, "
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

=======
>>>>>>> 7cf9ae32b097519084e68d78956d40940ee03e3d
};
//end class W211FitFluxHandler

}

#endif
