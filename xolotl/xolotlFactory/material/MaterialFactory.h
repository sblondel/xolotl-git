#ifndef MATERIALHANDLERFACTORY_H
#define MATERIALHANDLERFACTORY_H

#include <memory>
#include <IMaterialFactory.h>
<<<<<<< HEAD
=======
#include <DummyDiffusionHandler.h>
#include <DummyAdvectionHandler.h>
#include <DummyTrapMutationHandler.h>
#include <TokenizedLineReader.h>
#include <XGBAdvectionHandler.h>
#include <YGBAdvectionHandler.h>
#include <ZGBAdvectionHandler.h>
#include <Td40FitDisplacementHandler.h>
#include <Td80FitDisplacementHandler.h>
#include <Td120FitDisplacementHandler.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

namespace xolotlFactory {

/**
<<<<<<< HEAD
 * Realizes the IMaterialFactory interface. Handles the flux and the advection
 * for a specific material.
=======
 * Realizes the IMaterialFactory interface. Handles the flux, the advection, modified
 * trap mutation, and for a specific material.
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
 */
class MaterialFactory: public IMaterialFactory {
protected:

	//! The flux handler
	std::shared_ptr<xolotlCore::IFluxHandler> theFluxHandler;

	//! The advection handler
<<<<<<< HEAD
	std::shared_ptr<xolotlCore::IAdvectionHandler> theAdvectionHandler;
=======
	std::vector<std::shared_ptr<xolotlCore::IAdvectionHandler> > theAdvectionHandler;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	//! The diffusion handler
	std::shared_ptr<xolotlCore::IDiffusionHandler> theDiffusionHandler;

<<<<<<< HEAD
=======
	//! The modified trap-mutation handler
	std::shared_ptr<xolotlCore::ITrapMutationHandler> theTrapMutationHandler;

	//! The displacement handler
	std::shared_ptr<xolotlCore::IDisplacementHandler> theDisplacementHandler;

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
public:

	/**
	 * The constructor creates the handlers.
	 */
	MaterialFactory() {
	}

	/**
	 * The destructor
	 */
	~MaterialFactory() {
	}

	/**
	 * Initialize the material conditions with the different given options.
	 *
	 * @param options The Xolotl options.
	 */
	void initializeMaterial(xolotlCore::Options &options) {
		// Wrong if both he flux and time profile options are used
		if (options.useFluxAmplitude() && options.useFluxTimeProfile()) {
			// A constant flux value AND a time profile cannot both be given.
			throw std::string(
					"\nA constant flux value AND a time profile cannot both be given.");
<<<<<<< HEAD
		}
		else if (options.useFluxAmplitude()) {
			// Set the constant value of the flux
			theFluxHandler->setFluxAmplitude(options.getFluxAmplitude());
		}
		else if (options.useFluxTimeProfile()) {
=======
		} else if (options.useFluxAmplitude()) {
			// Set the constant value of the flux
			theFluxHandler->setFluxAmplitude(options.getFluxAmplitude());
		} else if (options.useFluxTimeProfile()) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			// Initialize the time profile
			theFluxHandler->initializeTimeProfile(options.getFluxProfileName());
		}

<<<<<<< HEAD
=======
		// Get the process map
		auto map = options.getProcesses();
		// Set dummy handlers when needed
		if (!map["diff"])
			theDiffusionHandler = std::make_shared<
					xolotlCore::DummyDiffusionHandler>();
		if (!map["advec"]) {
			// Clear the advection handler
			theAdvectionHandler.clear();
			// To replace it by a dummy one
			theAdvectionHandler.push_back(
					std::make_shared<xolotlCore::DummyAdvectionHandler>());
		}
		if (!map["modifiedTM"])
			theTrapMutationHandler = std::make_shared<
					xolotlCore::DummyTrapMutationHandler>();
		if (!map["attenuation"])
			theTrapMutationHandler->setAttenuation(false);

		// Get the number of dimensions
		int dim = options.getDimensionNumber();

		// Set-up the grain boundaries from the options
		std::string gbString = options.getGbString();
		// Build an input stream from the GB string.
		xolotlCore::TokenizedLineReader<std::string> reader;
		auto argSS = std::make_shared<std::istringstream>(gbString);
		reader.setInputStream(argSS);
		// Break the string into tokens.
		auto tokens = reader.loadLine();
		// Loop on them
		for (int i = 0; i < tokens.size(); i++) {
			// Switch on the type of grain boundaries
			if (tokens[i] == "X") {
				auto GBAdvecHandler = std::make_shared<
						xolotlCore::XGBAdvectionHandler>();
				GBAdvecHandler->setLocation(
						strtod(tokens[i + 1].c_str(), NULL));
				GBAdvecHandler->setDimension(dim);
				theAdvectionHandler.push_back(GBAdvecHandler);
			} else if (tokens[i] == "Y") {
				if (dim < 2)
					// A Y grain boundary cannot be used in 1D.
					throw std::string(
							"\nA Y grain boundary CANNOT be used in 1D. Switch to 2D or 3D or remove it.");

				auto GBAdvecHandler = std::make_shared<
						xolotlCore::YGBAdvectionHandler>();
				GBAdvecHandler->setLocation(
						strtod(tokens[i + 1].c_str(), NULL));
				GBAdvecHandler->setDimension(dim);
				theAdvectionHandler.push_back(GBAdvecHandler);
			} else if (tokens[i] == "Z") {
				if (dim < 3)
					// A Z grain boundary cannot be used in 1D/2D.
					throw std::string(
							"\nA Z grain boundary CANNOT be used in 1D/2D. Switch to 3D or remove it.");

				auto GBAdvecHandler = std::make_shared<
						xolotlCore::ZGBAdvectionHandler>();
				GBAdvecHandler->setLocation(
						strtod(tokens[i + 1].c_str(), NULL));
				GBAdvecHandler->setDimension(dim);
				theAdvectionHandler.push_back(GBAdvecHandler);
			} else {
				// Wrong GB type
				throw std::string(
						"\nThe type of grain boundary is not known: \""
								+ tokens[i] + "\"");
			}

			i++;
		}

		// Switch on the threshold energy for displacement handler
		switch (options.getDispEnergy()) {
		case 40:
			theDisplacementHandler = std::make_shared<
					xolotlCore::Td40FitDisplacementHandler>();
			break;
		case 80:
			theDisplacementHandler = std::make_shared<
					xolotlCore::Td80FitDisplacementHandler>();
			break;
		case 120:
			theDisplacementHandler = std::make_shared<
					xolotlCore::Td120FitDisplacementHandler>();
			break;
		default:
			// The asked threshold energy is not good (choose 40, 80, or 120)
			throw std::string(
					"\nxolotlFactory: Bad threshold energy for material factory.");
		}

		theDisplacementHandler->setKrFluenceAmplitude(
				options.getKrFluenceAmplitude());
//		theDisplacementHandler->setDispEnergy(options.getDispEnergy());

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		return;
	}

	/**
	 * Return the flux handler.
	 *
	 *  @return The flux handler.
	 */
	std::shared_ptr<xolotlCore::IFluxHandler> getFluxHandler() const {
		return theFluxHandler;
	}

	/**
	 * Return the advection handler.
	 *
	 *  @return The advection handler.
	 */
<<<<<<< HEAD
	std::shared_ptr<xolotlCore::IAdvectionHandler> getAdvectionHandler() const {
=======
	std::vector<std::shared_ptr<xolotlCore::IAdvectionHandler> > getAdvectionHandler() const {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
		return theAdvectionHandler;
	}

	/**
	 * Return the diffusion handler.
	 *
	 *  @return The diffusion handler.
	 */
	std::shared_ptr<xolotlCore::IDiffusionHandler> getDiffusionHandler() const {
		return theDiffusionHandler;
	}
<<<<<<< HEAD
=======

	/**
	 * Return the modified trap-mutation handler.
	 *
	 *  @return The trap-mutation handler.
	 */
	std::shared_ptr<xolotlCore::ITrapMutationHandler> getTrapMutationHandler() const {
		return theTrapMutationHandler;
	}

	/**
	 * Return the displacement handler.
	 *
	 *  @return The displacement handler.
	 */
	std::shared_ptr<xolotlCore::IDisplacementHandler> getDisplacementHandler() const {
		return theDisplacementHandler;
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
};

} // end namespace xolotlFactory

#endif // MATERIALHANDLERFACTORY_H
