// Includes
#include "VideoPlot.h"

using namespace xolotlViz;

<<<<<<< HEAD
VideoPlot::VideoPlot(const std::string& name) :
		Plot(name), frameRate(0.0) {
=======
VideoPlot::VideoPlot(std::string name) : Plot(name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

VideoPlot::~VideoPlot() {
}

<<<<<<< HEAD
void VideoPlot::render(const std::string&) {
=======
void VideoPlot::render(std::string fileName) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

void VideoPlot::setFrameRate(double fRate) {
	frameRate = fRate;
	return;
}

double VideoPlot::getFrameRate() const {
	return frameRate;
}
