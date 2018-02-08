// Includes
#include "DummyPlot.h"

using namespace xolotlViz;

<<<<<<< HEAD
<<<<<<< HEAD
DummyPlot::DummyPlot(const std::string&) :
		xolotlCore::Identifiable("unused") {
=======
DummyPlot::DummyPlot(std::string name) : xolotlCore::Identifiable("unused") {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
DummyPlot::DummyPlot(std::string name) : xolotlCore::Identifiable("unused") {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

DummyPlot::~DummyPlot() {
}

<<<<<<< HEAD
<<<<<<< HEAD
void DummyPlot::render(const std::string&) {
	return;
}

void DummyPlot::write(const std::string&) {
	return;
}

void DummyPlot::setPlottingStyle(PlottingStyle) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
void DummyPlot::render(std::string fileName) {
	return;
}

void DummyPlot::write(std::string fileName) {
	return;
}

void DummyPlot::setPlottingStyle(PlottingStyle style) {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
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
<<<<<<< HEAD
void DummyPlot::showLegend(bool) {
=======
void DummyPlot::showLegend(bool legendShow) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
void DummyPlot::showLegend(bool legendShow) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	return;
}

std::string DummyPlot::getLegend() const {
	return " ";
}

<<<<<<< HEAD
<<<<<<< HEAD
void DummyPlot::setLogScale(bool) {
	return;
}

void DummyPlot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	plotDataProvider = dataProvider;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider(int) const {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
void DummyPlot::setLogScale(bool logScale) {
	return;
}

void DummyPlot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider){
	plotDataProvider = dataProvider;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider(int i) const {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	return plotDataProvider;
}

int DummyPlot::getDataProviderNumber() const {
	return 0;
}
