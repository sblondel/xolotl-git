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
<<<<<<< HEAD
class ScatterPlot: public Plot {
=======
class ScatterPlot: public Plot{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
class ScatterPlot: public Plot{
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

private:

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * Declare the constructor as private to force the use of a name
	 */
	ScatterPlot() :
			Plot() {
	}
=======
     * Declare the constructor as private to force the use of a name
	 */
	ScatterPlot() : Plot() {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
     * Declare the constructor as private to force the use of a name
	 */
	ScatterPlot() : Plot() {}
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	ScatterPlot(const std::string& name);
=======
	ScatterPlot(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	ScatterPlot(std::string name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
	~ScatterPlot();

	/**
	 * Method managing everything that is related to the rendering of a plot.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	void render(const std::string& fileName = "fileName");
=======
	void render(std::string fileName = "fileName");
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	void render(std::string fileName = "fileName");
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

};

//end class ScatterPlot

} /* namespace xolotlViz */

#endif
