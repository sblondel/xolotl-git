// Includes
#include "SurfacePlot.h"
#include "eavl.h"
#include "eavlDataSet.h"
#include "eavlColor.h"
#include "eavlRenderSurfaceOSMesa.h"
#include "eavlScene.h"
#include "eavl2DWindow.h"
#include <iostream>

using namespace xolotlViz;

#define W_WIDTH 1024
#define W_HEIGHT 1024

<<<<<<< HEAD
<<<<<<< HEAD
SurfacePlot::SurfacePlot(const std::string& name) :
		Plot(name) {
=======
SurfacePlot::SurfacePlot(std::string name) : Plot(name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
SurfacePlot::SurfacePlot(std::string name) : Plot(name) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

SurfacePlot::~SurfacePlot() {
}

<<<<<<< HEAD
<<<<<<< HEAD
void SurfacePlot::render(const std::string& fileName) {

	// Check if the label provider is set
	if (!plotLabelProvider) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
void SurfacePlot::render(std::string fileName) {

	// Check if the label provider is set
	if (!plotLabelProvider){
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		std::cout << "The LabelProvider is not set!!" << std::endl;
		return;
	}

	// Check if the data provider is set
<<<<<<< HEAD
<<<<<<< HEAD
	if (!plotDataProvider) {
=======
	if (!plotDataProvider){
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	if (!plotDataProvider){
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		std::cout << "The DataProvider is not set!!" << std::endl;
		return;
	}

	// Get the value that will be plotted on X, Y, and Z
	auto xVector = plotDataProvider->getAxis1Vector();
	auto yVector = plotDataProvider->getAxis2Vector();
	auto zVector = plotDataProvider->getAxis3Vector();

	// Create the eavlDataSet
<<<<<<< HEAD
<<<<<<< HEAD
	eavlDataSet *data = new eavlDataSet();
	data->SetNumPoints(zVector.size());

	// Give it the xVector and yVector
	std::vector<std::vector<double> > coords;
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
    eavlDataSet *data = new eavlDataSet();
    data->SetNumPoints(zVector.size());

    // Give it the xVector and yVector
	std::vector< std::vector<double> > coords;
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	coords.push_back(xVector);
	coords.push_back(yVector);
	std::vector<std::string> coordNames;
	coordNames.push_back("xcoord");
	coordNames.push_back("ycoord");
	AddRectilinearMesh(data, coords, coordNames, true, "RectilinearGridCells");

	// Give the zVector to the axisValues
<<<<<<< HEAD
<<<<<<< HEAD
	eavlArray *axisValues = new eavlFloatArray(plotDataProvider->getDataName(),
			1);
	axisValues->SetNumberOfTuples(data->GetNumPoints());
	for (unsigned int i = 0; i < zVector.size(); i++) {
=======
	eavlArray *axisValues = new eavlFloatArray(plotDataProvider->getDataName(), 1);
	axisValues->SetNumberOfTuples(data->GetNumPoints());
	for (int i = 0; i < zVector.size(); i++){
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	eavlArray *axisValues = new eavlFloatArray(plotDataProvider->getDataName(), 1);
	axisValues->SetNumberOfTuples(data->GetNumPoints());
	for (int i = 0; i < zVector.size(); i++){
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		axisValues->SetComponentFromDouble(i, 0, zVector.at(i));
	}

	// Add the axisValues to a field of the data set
<<<<<<< HEAD
<<<<<<< HEAD
	eavlField *field = new eavlField(0, axisValues, eavlField::ASSOC_CELL_SET,
			"RectilinearGridCells");
	data->AddField(field);

	// Create an offscreen render surface
	eavlRenderSurface *surface = new eavlRenderSurfaceOSMesa;

	// Pick a background color
//    eavlColor bg(0.15, 0.05, 0.1, 1.0);
	eavlColor bg(0.5, 0.5, 0.5, 0.5);

	// Create a 2D scene
	eavlScene *scene = new eavl2DGLScene();

	// Create the window
	eavl2DWindow *window = new eavl2DWindow(bg, surface, scene);
	window->Initialize();
	window->Resize(W_WIDTH, W_HEIGHT);

	// Print the title
	auto titleAnnotation = new eavlScreenTextAnnotation(window,
			plotLabelProvider->titleLabel, eavlColor::white, 0.065, 0.0, 0.96);
	window->AddAnnotation(titleAnnotation);

	// Print the axis labels
	auto axis1Annotation = new eavlScreenTextAnnotation(window,
			plotLabelProvider->axis1Label, eavlColor::white, 0.05, 0.0, -0.9);
	window->AddAnnotation(axis1Annotation);
	auto axis2Annotation = new eavlScreenTextAnnotation(window,
			plotLabelProvider->axis2Label, eavlColor::white, 0.05, -0.9, 0.0,
			90.0);
	window->AddAnnotation(axis2Annotation);
	auto axis3Annotation = new eavlScreenTextAnnotation(window,
			plotLabelProvider->axis3Label, eavlColor::white, 0.05, 0.0, 0.78);
	window->AddAnnotation(axis3Annotation);

	// Add the time information
	auto timeAnnotation = new eavlScreenTextAnnotation(window,
			plotLabelProvider->timeLabel, eavlColor::white, 0.055, 0.8, -0.85);
	window->AddAnnotation(timeAnnotation);
	auto timeStepAnnotation = new eavlScreenTextAnnotation(window,
			plotLabelProvider->timeStepLabel, eavlColor::white, 0.055, 0.8,
			-0.91);
	window->AddAnnotation(timeStepAnnotation);

	// Set up a plot for the data set
	eavlRenderer *plot;
	plot = new eavlPseudocolorRenderer(data, NULL, "temperature", false,
			data->GetCellSet(0)->GetName(), plotDataProvider->getDataName());
	scene->plots.push_back(plot);

	// Set the view
	scene->ResetView(window);

	// Paint
	window->Paint();

	// Save the final buffer as an image
	window->SaveWindowAsPNM(fileName);
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	eavlField *field = new eavlField(1, axisValues, eavlField::ASSOC_POINTS);
	data->AddField(field);

    // Create an offscreen render surface
    eavlRenderSurface *surface = new eavlRenderSurfaceOSMesa;

    // Pick a background color
//    eavlColor bg(0.15, 0.05, 0.1, 1.0);
    eavlColor bg(0.5, 0.5, 0.5, 0.5);

    // Create a 2D scene
    eavlScene *scene = new eavl2DGLScene();

    // Create the window
    eavl2DWindow *window = new eavl2DWindow(bg, surface, scene);
    window->Initialize();
    window->Resize(W_WIDTH,W_HEIGHT);

    // Print the title
    auto titleAnnotation = new eavlScreenTextAnnotation(window, plotLabelProvider->titleLabel,
    		eavlColor::white, 0.065, 0.0, 0.96);
    window->AddAnnotation(titleAnnotation);

    // Print the axis labels
    auto axis1Annotation = new eavlScreenTextAnnotation(window, plotLabelProvider->axis1Label,
    		eavlColor::white, 0.05, 0.0, -0.9);
    window->AddAnnotation(axis1Annotation);
    auto axis2Annotation = new eavlScreenTextAnnotation(window, plotLabelProvider->axis2Label,
    		eavlColor::white, 0.05, -0.9, 0.0, 90.0);
    window->AddAnnotation(axis2Annotation);
    auto axis3Annotation = new eavlScreenTextAnnotation(window, plotLabelProvider->axis3Label,
    		eavlColor::white, 0.05, 0.0, 0.78);
    window->AddAnnotation(axis3Annotation);

    // Add the time information
    auto timeAnnotation = new eavlScreenTextAnnotation(window, plotLabelProvider->timeLabel,
    		eavlColor::white, 0.055, 0.8, -0.85);
    window->AddAnnotation(timeAnnotation);
    auto timeStepAnnotation = new eavlScreenTextAnnotation(window, plotLabelProvider->timeStepLabel,
    		eavlColor::white, 0.055, 0.8, -0.91);
    window->AddAnnotation(timeStepAnnotation);

    // Set up a plot for the data set
    eavlRenderer *plot;
    plot = new eavlPseudocolorRenderer(data, NULL,
                                       "temperature",
                                       false,
                                       data->GetCellSet(0)->GetName(),
                                       plotDataProvider->getDataName());
    scene->plots.push_back(plot);

    // Set the view
    scene->ResetView(window);

    // Paint
    window->Paint();

    // Save the final buffer as an image
    char fn[25];
    sprintf(fn, (fileName).c_str());
    window->SaveWindowAsPNM(fn);
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	return;
}
