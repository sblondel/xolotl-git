#ifndef TEMPERATUREHANDLERFACTORY_H
#define TEMPERATUREHANDLERFACTORY_H

#include <memory>
#include <ITemperatureHandler.h>
#include <Options.h>

namespace xolotlFactory {

/**
 * Build the desired type of handler registry.
 *
 * @param options Options for the program
 * @return True iff the handler registry was created successfully.
 */
bool initializeTempHandler(xolotlCore::Options &options);

/**
 * Access the handler registry.
 *
 *  @return The handler registry object.
 */
std::shared_ptr<xolotlCore::ITemperatureHandler> getTemperatureHandler();

<<<<<<< HEAD
}; // end namespace xolotlPerf
=======
} // end namespace xolotlPerf
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

#endif /* TEMPERATUREHANDLERFACTORY_H */
