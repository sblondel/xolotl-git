#ifndef HDF5NETWORKLOADER_H_
#define HDF5NETWORKLOADER_H_

//Includes
#include <PSIClusterNetworkLoader.h>

namespace xolotlCore {

/**
<<<<<<< HEAD
 * This class overwrites the load() methods of PSIClusterNetworkLoader
 * for HDF5 files.
 */
class HDF5NetworkLoader: public PSIClusterNetworkLoader {
private:
=======
 * This class overwrites load() for HDF5 files
 */
class HDF5NetworkLoader: public PSIClusterNetworkLoader {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
private:

	std::string fileName;
>>>>>>> Xolotl starts with the HDF5 file named xolotlStart.h5. Fixing of number of clusters plotted for seriesPlot. SB 20140521

	/**
	 * Private nullary constructor.
	 */
<<<<<<< HEAD
	HDF5NetworkLoader() {}
=======
	HDF5NetworkLoader() {
	};
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
<<<<<<< HEAD
	 * The default constructor.
	 */
	HDF5NetworkLoader(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		PSIClusterNetworkLoader(registry) {}

	/**
	 * The destructor.
=======
	 * The default constructor. The setInputstream() operation must be called
	 * if this constructor is used.
	 */
	HDF5NetworkLoader(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) {
		handlerRegistry = registry;
	}

	/**
	 * Destructor
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 */
	virtual ~HDF5NetworkLoader() {
	}

	/**
<<<<<<< HEAD
	 * This operation will load the reaction network from the HDF5 file in
	 * the format specified previously. The network will be empty if it can not
	 * be loaded.
	 *
	 * @return The reaction network.
	 */
	std::shared_ptr<IReactionNetwork> load();

};

} /* namespace xolotlCore */

=======
	 * This operation will load the reaction network from the HDF5 file xolotlStart.h5 in
	 * the format specified previously. The network will be empty if it can not
	 * be loaded.
	 * @return The reaction network.
	 */
	std::shared_ptr<PSIClusterReactionNetwork> load();

	/**
	 * This operation will set the name of the file where to take the network from.
	 * @param name The name of the file.
	 */
	void setFilename (std::string name);

	/**
	 * This operation will get the name of the file where to take the network from.
	 * @return The name of the file.
	 */
	std::string getFilename () const;
};

} /* namespace xolotlCore */
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#endif /* HDF5NETWORKLOADER_H_ */
