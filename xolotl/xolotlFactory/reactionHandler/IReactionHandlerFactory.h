#ifndef IREACTIONHANDLERFACTORY_H
#define IREACTIONHANDLERFACTORY_H

#include <Options.h>
#include <INetworkLoader.h>
#include <IReactionNetwork.h>

namespace xolotlFactory {

/**
 * Realizations of this interface are responsible for handling the flux and the advection.
 * they are both dependent on the type of material under study.
 */
class IReactionHandlerFactory {
public:

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	~IReactionHandlerFactory() {}
=======
	~IReactionHandlerFactory() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Initialize the reaction network.
	 *
	 * @param options The options.
	 * @param registry The performance registry.
	 */
	virtual void initializeReactionNetwork(xolotlCore::Options &options,
			std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) = 0;

	/**
	 * Return the network loader.
	 *
	 * @return The network loader.
	 */
	virtual std::shared_ptr<xolotlCore::INetworkLoader> getNetworkLoaderHandler() const = 0;

	/**
	 * Return the network.
	 *
	 * @return The network.
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<xolotlCore::IReactionNetwork> getNetworkHandler() const = 0;
=======
	virtual xolotlCore::IReactionNetwork& getNetworkHandler() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * Function that create the wanted reaction handler factory depending on the given type.
	 *
<<<<<<< HEAD
	 * @param problemType The type of wanted problem (PSI or NE).
	 * @return The reaction factory.
	 */
	static std::shared_ptr<IReactionHandlerFactory> createNetworkFactory(const std::string& problemType);
=======
	 * @param problemType The type of wanted problem (PSI, NE, or Fe).
	 * @return The reaction factory.
	 */
	static std::shared_ptr<IReactionHandlerFactory> createNetworkFactory(
			const std::string& problemType);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};

} // end namespace xolotlFactory

#endif // IREACTIONHANDLERFACTORY_H
