#ifndef SURFACEPLOT_H
#define SURFACEPLOT_H

// Includes
#include "Plot.h"
#include <vector>
#include <Identifiable.h>

namespace xolotlViz {

/**
 * Plot the data value as a function of two different dimensions.
 * The available PlottingStyle are POINTS, LINE, COLORMAP, and SURFACE.
 * It can be associated to QvsXYDataProvider, QvsXZDataProvider, or QvsYZDataProvider.
 */
class SurfacePlot: public Plot {

private:

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * Declare the constructor as private to force the use of a name
	 */
	SurfacePlot() :
			Plot() {
	}
=======
     * Declare the constructor as private to force the use of a name
	 */
    SurfacePlot() : Plot() {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
     * Declare the constructor as private to force the use of a name
	 */
    SurfacePlot() : Plot() {}
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	SurfacePlot(const std::string& name);
=======
	SurfacePlot(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	SurfacePlot(std::string name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
	~SurfacePlot();

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

//end class SurfacePlot

} /* namespace xolotlViz */

#endif
