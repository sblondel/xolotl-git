// Includes
#include "VideoPlot.h"

using namespace xolotlViz;

<<<<<<< HEAD
<<<<<<< HEAD
VideoPlot::VideoPlot(const std::string& name) :
		Plot(name), frameRate(0.0) {
=======
VideoPlot::VideoPlot(std::string name) : Plot(name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
VideoPlot::VideoPlot(std::string name) : Plot(name) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

VideoPlot::~VideoPlot() {
}

<<<<<<< HEAD
<<<<<<< HEAD
void VideoPlot::render(const std::string&) {
=======
void VideoPlot::render(std::string fileName) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
void VideoPlot::render(std::string fileName) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

void VideoPlot::setFrameRate(double fRate) {
	frameRate = fRate;
	return;
}

double VideoPlot::getFrameRate() const {
	return frameRate;
}
