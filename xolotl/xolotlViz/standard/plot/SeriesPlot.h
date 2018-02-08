#ifndef SERIESPLOT_H
#define SERIESPLOT_H

// Includes
#include "Plot.h"
#include <vector>
#include <Identifiable.h>

namespace xolotlViz {

/**
 * Plot the different data values as a function of one dimension. Available PlottingStyle are POINTS or LINE.
 * It can be associated to CvsXDataProvider.
 */
class SeriesPlot: public Plot {

private:

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * Declare the constructor as private to force the use of a name
	 */
	SeriesPlot() :
			Plot() {
	}
=======
     * Declare the constructor as private to force the use of a name
	 */
    SeriesPlot() : Plot() {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
     * Declare the constructor as private to force the use of a name
	 */
    SeriesPlot() : Plot() {}
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

private:

	/**
	 * Container of data providers used for the plot.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	std::shared_ptr<std::vector<std::shared_ptr<IDataProvider> > > plotDataProviders;
=======
	std::shared_ptr< std::vector< std::shared_ptr<IDataProvider> > > plotDataProviders;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	std::shared_ptr< std::vector< std::shared_ptr<IDataProvider> > > plotDataProviders;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	SeriesPlot(const std::string& name);
=======
	SeriesPlot(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	SeriesPlot(std::string name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
	~SeriesPlot();

	/**
	 * Method managing everything that is related to the rendering of a plot.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	void render(const std::string& fileName = "fileName");
=======
	void render(std::string fileName = "fileName");
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	void render(std::string fileName = "fileName");
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * Method adding one data provider to the vector plotDataProviders
	 * @ param dataProvider The data provider to add.
	 */
	void addDataProvider(std::shared_ptr<IDataProvider> dataProvider);

	/**
	 * Method getting the i-th data provider
	 * @ param i The number of the data provider to be returned.
	 * @ return The ith data provider.
	 */
	std::shared_ptr<IDataProvider> getDataProvider(int i) const;

	/**
	 * Method getting the total number of data providers
	 * @ return The total number of data providers.
	 */
	int getDataProviderNumber() const;

};

//end class SeriesPlot

} /* namespace xolotlViz */

#endif
