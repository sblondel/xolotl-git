#ifndef SCATTERPLOT_H
#define SCATTERPLOT_H

// Includes
#include "Plot.h"
#include <vector>
#include <Identifiable.h>

namespace xolotlViz {

/**
 * Plot the data value as a function of one dimension. Available PlottingStyle are POINTS or LINE.
 * It can be associated to QvsXDataProvider, QvsYDataProvider, QvsZDataProvider, or QvsTimeDataProvider.
 */
<<<<<<< HEAD
class ScatterPlot: public Plot{
=======
class ScatterPlot: public Plot {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

private:

	/**
<<<<<<< HEAD
     * Declare the constructor as private to force the use of a name
	 */
	ScatterPlot() : Plot() {}
=======
	 * Declare the constructor as private to force the use of a name
	 */
	ScatterPlot() :
			Plot() {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
	 * The default constructor
	 */
	ScatterPlot(const std::string& name);

	/**
	 * The destructor
	 */
	~ScatterPlot();

	/**
	 * Method managing everything that is related to the rendering of a plot.
	 */
	void render(const std::string& fileName = "fileName");

};

//end class ScatterPlot

} /* namespace xolotlViz */

#endif
