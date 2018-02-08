// Includes
#include "Plot.h"

using namespace xolotlViz;

<<<<<<< HEAD
<<<<<<< HEAD
Plot::Plot(const std::string& name) :
		xolotlCore::Identifiable(name), plotStyle(PlottingStyle::LINE) {
=======
Plot::Plot(std::string name) : xolotlCore::Identifiable(name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
Plot::Plot(std::string name) : xolotlCore::Identifiable(name) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

Plot::~Plot() {
}

<<<<<<< HEAD
<<<<<<< HEAD
void Plot::render(const std::string&) {
	return;
}

void Plot::write(const std::string& fileName) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
void Plot::render(std::string fileName) {
	return;
}

void Plot::write(std::string fileName) {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	render(fileName);
	return;
}

void Plot::setPlottingStyle(PlottingStyle style) {
	plotStyle = style;
	return;
}

PlottingStyle Plot::getPlottingStyle() {
	return plotStyle;
}

void Plot::setDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	plotDataProvider = dataProvider;
	return;
}

std::shared_ptr<IDataProvider> Plot::getDataProvider() const {
	return plotDataProvider;
}

void Plot::setLabelProvider(std::shared_ptr<LabelProvider> labelProvider) {
	plotLabelProvider = labelProvider;
	return;
}

std::shared_ptr<LabelProvider> Plot::getLabelProvider() const {
	return plotLabelProvider;
}

void Plot::showLegend(bool legendShow) {
	enableLegend = legendShow;
	return;
}

std::string Plot::getLegend() const {
	return " ";
}

void Plot::setLogScale(bool logScale) {
	enableLogScale = logScale;
	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
void Plot::addDataProvider(std::shared_ptr<IDataProvider>) {
	return;
}

std::shared_ptr<IDataProvider> Plot::getDataProvider(int) const {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
void Plot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	return;
}

std::shared_ptr<IDataProvider> Plot::getDataProvider(int i) const {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	return plotDataProvider;
}

int Plot::getDataProviderNumber() const {
	return 0;
}
