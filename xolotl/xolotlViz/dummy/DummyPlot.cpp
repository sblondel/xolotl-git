// Includes
#include "DummyPlot.h"

using namespace xolotlViz;

<<<<<<< HEAD
DummyPlot::DummyPlot(const std::string&) :
		xolotlCore::Identifiable("unused") {
=======
DummyPlot::DummyPlot(std::string name) : xolotlCore::Identifiable("unused") {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
}

DummyPlot::~DummyPlot() {
}

<<<<<<< HEAD
void DummyPlot::render(const std::string&) {
	return;
}

void DummyPlot::write(const std::string&) {
	return;
}

void DummyPlot::setPlottingStyle(PlottingStyle) {
=======
void DummyPlot::render(std::string fileName) {
	return;
}

void DummyPlot::write(std::string fileName) {
	return;
}

void DummyPlot::setPlottingStyle(PlottingStyle style) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	return;
}

PlottingStyle DummyPlot::getPlottingStyle() {
	return PlottingStyle();
}

void DummyPlot::setDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	plotDataProvider = dataProvider;
	return;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider() const {
	return plotDataProvider;
}

void DummyPlot::setLabelProvider(std::shared_ptr<LabelProvider> labelProvider) {
	plotLabelProvider = labelProvider;
	return;
}

std::shared_ptr<LabelProvider> DummyPlot::getLabelProvider() const {
	return plotLabelProvider;
}

<<<<<<< HEAD
void DummyPlot::showLegend(bool) {
=======
void DummyPlot::showLegend(bool legendShow) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	return;
}

std::string DummyPlot::getLegend() const {
	return " ";
}

<<<<<<< HEAD
void DummyPlot::setLogScale(bool) {
	return;
}

void DummyPlot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	plotDataProvider = dataProvider;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider(int) const {
=======
void DummyPlot::setLogScale(bool logScale) {
	return;
}

void DummyPlot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider){
	plotDataProvider = dataProvider;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider(int i) const {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	return plotDataProvider;
}

int DummyPlot::getDataProviderNumber() const {
	return 0;
}
