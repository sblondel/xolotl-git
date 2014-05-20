#include "DummyHandlerRegistry.h"

namespace xolotlViz {

DummyHandlerRegistry::DummyHandlerRegistry() {
}

DummyHandlerRegistry::~DummyHandlerRegistry() {
}

<<<<<<< HEAD
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(const std::string& name,
		PlotType) {
	return std::make_shared<DummyPlot>(name);
=======
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(std::string name, PlotType type) {
	return std::make_shared <DummyPlot> (name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

}    //end namespace xolotlViz

