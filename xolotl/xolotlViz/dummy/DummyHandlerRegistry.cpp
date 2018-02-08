#include "DummyHandlerRegistry.h"

namespace xolotlViz {

DummyHandlerRegistry::DummyHandlerRegistry() {
}

DummyHandlerRegistry::~DummyHandlerRegistry() {
}

<<<<<<< HEAD
<<<<<<< HEAD
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(const std::string& name,
		PlotType) {
	return std::make_shared<DummyPlot>(name);
=======
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(std::string name, PlotType type) {
	return std::make_shared <DummyPlot> (name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(std::string name, PlotType type) {
	return std::make_shared <DummyPlot> (name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

}    //end namespace xolotlViz

