#include "DummyHandlerRegistry.h"

namespace xolotlViz {

DummyHandlerRegistry::DummyHandlerRegistry() {
}

DummyHandlerRegistry::~DummyHandlerRegistry() {
}

<<<<<<< HEAD
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(const std::string& name, PlotType type) {
	return std::make_shared <DummyPlot> (name);
=======
std::shared_ptr<IPlot> DummyHandlerRegistry::getPlot(const std::string& name,
		PlotType) {
	return std::make_shared<DummyPlot>(name);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

}    //end namespace xolotlViz

