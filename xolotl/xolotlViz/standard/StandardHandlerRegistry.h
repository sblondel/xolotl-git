#ifndef STANDARDHANDLERREGISTRY_H
#define STANDARDHANDLERREGISTRY_H

#include <iostream>
#include <string>
#include <map>
#include "IVizHandlerRegistry.h"

<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
namespace xolotlViz {

/**
 * Factory for creating standard plots using EAVL and MESA libraries.
 * This is used only if the libraries are present and if the user uses
 * the standard registry.
 */
<<<<<<< HEAD
class StandardHandlerRegistry: public IVizHandlerRegistry {
public:

	/**
	 * Construct a StandardHandlerRegistry.
	 */
	StandardHandlerRegistry();

	/**
	 * Clean up a StandardHandlerRegistry.
	 */
	virtual ~StandardHandlerRegistry();

	/**
	 * Obtain a Plot by name.
	 *
	 * @param name The name of the Plot.
	 * @param type The type of plot to return.
	 * @return A shared pointer to the newly-created Plot.
	 */
	virtual std::shared_ptr<IPlot> getPlot(const std::string& name,
			PlotType type);

};
//end class StandardHandlerRegistry
=======
class StandardHandlerRegistry : public IVizHandlerRegistry
{
public:

    /**
     * Construct a StandardHandlerRegistry.
     */
    StandardHandlerRegistry();

    /**
     * Clean up a StandardHandlerRegistry.
     */
    virtual ~StandardHandlerRegistry();

    /**
     * Obtain a Plot by name.
     *
     * @param name The name of the Plot.
     * @param type The type of plot to return.
     * @return A shared pointer to the newly-created Plot.
     */
    virtual std::shared_ptr<IPlot> getPlot(std::string name, PlotType type);

};  //end class StandardHandlerRegistry
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

}//end namespace xolotlViz

#endif
