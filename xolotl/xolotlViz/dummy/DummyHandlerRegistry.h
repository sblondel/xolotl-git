#ifndef DUMMYHANDLERREGISTRY_H
#define DUMMYHANDLERREGISTRY_H

#include "IVizHandlerRegistry.h"
#include <DummyPlot.h>

namespace xolotlViz {

/**
 * Factory for creating plots that are dummies, meaning that they have the
 * same structure as IPlot but don't actually do anything. This is so that
 * the code can be written to use the visualization infrastructure without
 * regard to whether visualization is active or disabled.
 */
<<<<<<< HEAD
<<<<<<< HEAD
class DummyHandlerRegistry: public IVizHandlerRegistry {
public:

	/**
	 * Construct a DummyHandlerRegistry.
	 */
	DummyHandlerRegistry();

	/**
	 * Clean up a DummyHandlerRegistry.
	 */
	virtual ~DummyHandlerRegistry();

	/**
	 * Obtain a Plot by name.
	 *
	 * @param name The name of the Plot.
	 * @return A shared pointer to the newly-created Plot.
	 */
	virtual std::shared_ptr<IPlot> getPlot(const std::string& name,
			PlotType type);

};
//end class DummyHandlerRegistry
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
class DummyHandlerRegistry : public IVizHandlerRegistry
{
public:

    /**
     * Construct a DummyHandlerRegistry.
     */
    DummyHandlerRegistry();

    /**
     * Clean up a DummyHandlerRegistry.
     */
    virtual ~DummyHandlerRegistry();

    /**
     * Obtain a Plot by name.
     *
     * @param name The name of the Plot.
     * @return A shared pointer to the newly-created Plot.
     */
    virtual std::shared_ptr<IPlot> getPlot(std::string name, PlotType type);

};  //end class DummyHandlerRegistry
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

}//end namespace xolotlViz

#endif
