// Includes
#include "VideoPlot.h"

using namespace xolotlViz;

<<<<<<< HEAD
VideoPlot::VideoPlot(const std::string& name) : Plot(name), frameRate(0.0) {
=======
VideoPlot::VideoPlot(const std::string& name) :
		Plot(name), frameRate(0.0) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

VideoPlot::~VideoPlot() {
}

<<<<<<< HEAD
void VideoPlot::render(const std::string& fileName) {
=======
void VideoPlot::render(const std::string&) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

void VideoPlot::setFrameRate(double fRate) {
	frameRate = fRate;
	return;
}

double VideoPlot::getFrameRate() const {
	return frameRate;
}
