// Includes
#include "DummyPlot.h"

using namespace xolotlViz;

<<<<<<< HEAD
DummyPlot::DummyPlot(const std::string& name) : xolotlCore::Identifiable("unused") {
=======
DummyPlot::DummyPlot(const std::string&) :
		xolotlCore::Identifiable("unused") {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

DummyPlot::~DummyPlot() {
}

<<<<<<< HEAD
void DummyPlot::render(const std::string& fileName) {
	return;
}

void DummyPlot::write(const std::string& fileName) {
	return;
}

void DummyPlot::setPlottingStyle(PlottingStyle style) {
=======
void DummyPlot::render(const std::string&) {
	return;
}

void DummyPlot::write(const std::string&) {
	return;
}

void DummyPlot::setPlottingStyle(PlottingStyle) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
void DummyPlot::showLegend(bool legendShow) {
=======
void DummyPlot::showLegend(bool) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	return;
}

std::string DummyPlot::getLegend() const {
	return " ";
}

<<<<<<< HEAD
void DummyPlot::setLogScale(bool logScale) {
	return;
}

void DummyPlot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider){
	plotDataProvider = dataProvider;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider(int i) const {
=======
void DummyPlot::setLogScale(bool) {
	return;
}

void DummyPlot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	plotDataProvider = dataProvider;
}

std::shared_ptr<IDataProvider> DummyPlot::getDataProvider(int) const {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	return plotDataProvider;
}

int DummyPlot::getDataProviderNumber() const {
	return 0;
}
