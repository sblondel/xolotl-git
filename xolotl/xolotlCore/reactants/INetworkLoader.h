#ifndef INETWORKLOADER_H
#define INETWORKLOADER_H

#include "IReactionNetwork.h"
#include <IOptions.h>

namespace xolotlCore {

/**
 *  This class is the interface for the netowrk loader.
 */
class INetworkLoader {

public:

	/**
	 * The destructor.
	 */
	virtual ~INetworkLoader() {
	}

	/**
	 * This operation specifies the inputstream from which cluster data should
	 * be loaded.
	 *
	 * @param stream The inputstream from which the cluster data should be
	 * loaded
	 */
	virtual void setInputstream(const std::shared_ptr<std::istream> stream) = 0;

	/**
	 * This operation will load the reaction network from the input file in
	 * the format specified previously. The network will be empty if it can not
	 * be loaded.
	 *
<<<<<<< HEAD
	 * @return network The reaction network
	 */
	virtual std::shared_ptr<IReactionNetwork> load() = 0;
=======
	 * @param options The command line options.
	 * @return network The reaction network
	 */
	virtual std::unique_ptr<IReactionNetwork> load(
			const IOptions& options) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will generate the reaction network from options.
	 * The network will be empty if it can not be loaded.
	 *
	 * @param options The command line options
	 * @return network The reaction network
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<IReactionNetwork> generate(IOptions &options) = 0;
=======
	virtual std::unique_ptr<IReactionNetwork> generate(
			const IOptions &options) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will set the name of the file where to take the network from.
	 *
	 * @param name The name of the file
	 */
<<<<<<< HEAD
	virtual void setFilename (const std::string& name) = 0;
=======
	virtual void setFilename(const std::string& name) = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will get the name of the file where to take the network from.
	 *
	 * @return The name of the file
	 */
<<<<<<< HEAD
	virtual std::string getFilename () const = 0;
=======
	virtual std::string getFilename() const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * This operation will set the reactions to dummy reactions.
	 */
<<<<<<< HEAD
	virtual void setDummyReactions () = 0;
=======
	virtual void setDummyReactions() = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};

}

#endif
