#ifndef HDF5NETWORKLOADER_H_
#define HDF5NETWORKLOADER_H_

//Includes
#include <PSIClusterNetworkLoader.h>

namespace xolotlCore {

/**
 * This class overwrites the load() methods of PSIClusterNetworkLoader
 * for HDF5 files.
 */
class HDF5NetworkLoader: public PSIClusterNetworkLoader {
private:

	/**
	 * Private nullary constructor.
	 */
<<<<<<< HEAD
	HDF5NetworkLoader() {}
=======
	HDF5NetworkLoader() {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

public:

	/**
	 * The default constructor.
	 */
	HDF5NetworkLoader(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
<<<<<<< HEAD
		PSIClusterNetworkLoader(registry) {}
=======
			PSIClusterNetworkLoader(registry) {
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	/**
	 * The destructor.
	 */
	virtual ~HDF5NetworkLoader() {
	}

	/**
	 * This operation will load the reaction network from the HDF5 file in
	 * the format specified previously. The network will be empty if it can not
	 * be loaded.
	 *
	 * @return The reaction network.
	 */
<<<<<<< HEAD
	std::shared_ptr<IReactionNetwork> load();
=======
	std::unique_ptr<IReactionNetwork> load(const IOptions& options) override;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

};

} /* namespace xolotlCore */

#endif /* HDF5NETWORKLOADER_H_ */
