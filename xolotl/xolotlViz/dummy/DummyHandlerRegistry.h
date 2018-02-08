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
    virtual std::shared_ptr<IPlot> getPlot(const std::string& name, PlotType type);

};  //end class DummyHandlerRegistry
=======
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

}//end namespace xolotlViz

#endif
