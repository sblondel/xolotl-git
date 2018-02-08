#ifndef IVIZHANDLERREGISTRY_H
#define IVIZHANDLERREGISTRY_H

// Includes
#include <string>
#include <vector>
#include <memory>
#include "IPlot.h"
#include "PlotType.h"


namespace xolotlViz {

/**
 * Factory for building plots, dataprovider, and labelprovider.
 */
class IVizHandlerRegistry {

public:

	/**
	 * The destructor
	 */
	virtual ~IVizHandlerRegistry(){}

	/**
	 * This operation returns the IPlot specified by the parameter.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual std::shared_ptr<IPlot> getPlot(const std::string& name, PlotType type) = 0;
=======
	virtual std::shared_ptr<IPlot> getPlot(std::string name, PlotType type) = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	virtual std::shared_ptr<IPlot> getPlot(std::string name, PlotType type) = 0;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

}; //end class IVizHandlerRegistry

} //end namespace xolotlViz

#endif
