#include "StandardHandlerRegistry.h"
#include <Plot.h>
#include <ScatterPlot.h>
#include <SeriesPlot.h>
#include <SurfacePlot.h>
#include <VideoPlot.h>
#include <DataProvider.h>
#include <LabelProvider.h>

namespace xolotlViz {

StandardHandlerRegistry::StandardHandlerRegistry() {
}

StandardHandlerRegistry::~StandardHandlerRegistry() {
}

<<<<<<< HEAD
<<<<<<< HEAD
std::shared_ptr<IPlot> StandardHandlerRegistry::getPlot(const std::string& name,
		PlotType type) {
	switch (type) {
	case PlotType::SCATTER:
		return std::make_shared<ScatterPlot>(name);
	case PlotType::SERIES:
		return std::make_shared<SeriesPlot>(name);
	case PlotType::SURFACE:
		return std::make_shared<SurfacePlot>(name);
	case PlotType::VIDEO:
		return std::make_shared<VideoPlot>(name);
	default:
		return std::make_shared<Plot>(name);
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
std::shared_ptr<IPlot> StandardHandlerRegistry::getPlot(std::string name, PlotType type) {
	switch(type) {
	case PlotType::SCATTER: return std::make_shared <ScatterPlot> (name);
	case PlotType::SERIES: return std::make_shared <SeriesPlot> (name);
	case PlotType::SURFACE: return std::make_shared <SurfacePlot> (name);
	case PlotType::VIDEO: return std::make_shared <VideoPlot> (name);
	default: return std::make_shared <Plot> (name);
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	}
}

}    //end namespace xolotlViz

