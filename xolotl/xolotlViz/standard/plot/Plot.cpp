// Includes
#include "Plot.h"

using namespace xolotlViz;

<<<<<<< HEAD
Plot::Plot(const std::string& name) : xolotlCore::Identifiable(name) {
=======
Plot::Plot(const std::string& name) :
		xolotlCore::Identifiable(name), plotStyle(PlottingStyle::LINE) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

Plot::~Plot() {
}

<<<<<<< HEAD
void Plot::render(const std::string& fileName) {
=======
void Plot::render(const std::string&) {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	return;
}

void Plot::write(const std::string& fileName) {
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
void Plot::addDataProvider(std::shared_ptr<IDataProvider> dataProvider) {
	return;
}

std::shared_ptr<IDataProvider> Plot::getDataProvider(int i) const {
=======
void Plot::addDataProvider(std::shared_ptr<IDataProvider>) {
	return;
}

std::shared_ptr<IDataProvider> Plot::getDataProvider(int) const {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	return plotDataProvider;
}

int Plot::getDataProviderNumber() const {
	return 0;
}
