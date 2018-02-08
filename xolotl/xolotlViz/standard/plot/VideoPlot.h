#ifndef VIDEOPLOT_H
#define VIDEOPLOT_H

// Includes
#include "Plot.h"
#include <vector>
#include <Identifiable.h>

namespace xolotlViz {

/**
 * Plot the data value as a function of two different spatial dimensions for each time step
 * and change the time step with time to have a video-like rendering, each frame being a SurfacePlot.
 * The available PlottingStyle are POINTS, LINE, COLORMAP, and SURFACE.
 * It can be associated to QvsXYTimeDataProvider, QvsXZTimeDataProvider, or QvsYZTimeDataProvider.
 */
class VideoPlot: public Plot {

private:

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * Declare the constructor as private to force the use of a name
	 */
	VideoPlot() :
			Plot() {
	}
=======
     * Declare the constructor as private to force the use of a name
	 */
    VideoPlot() : Plot() {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
     * Declare the constructor as private to force the use of a name
	 */
    VideoPlot() : Plot() {}
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

private:

	/**
	 * Number of frames shown per second.
	 */
	double frameRate;

public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	VideoPlot(const std::string& name);
=======
	VideoPlot(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	VideoPlot(std::string name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
	~VideoPlot();

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

	/**
	 * Sets the frame rate for VideoPlot.
	 */
	void setFrameRate(double frameRate);

	/**
	 * Get the frame rate from VideoPlot.
	 */
	double getFrameRate() const;

};

//end class VideoPlot

} /* namespace xolotlViz */

#endif
