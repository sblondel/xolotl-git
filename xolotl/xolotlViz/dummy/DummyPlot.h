#ifndef DUMMYPLOT_H
#define DUMMYPLOT_H

#include <string>
#include <Identifiable.h>
#include <IPlot.h>

namespace xolotlViz {

/**
 * The DummyPlot class is instantiated by the DummyHandlerRegistry
 * class and realizes the IPlot interface.
 */
<<<<<<< HEAD
class DummyPlot: public IPlot, public xolotlCore::Identifiable {
=======
class DummyPlot : public IPlot, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

private:

	/**
	 * Declare the constructor as private to force the use of a name.
	 */
<<<<<<< HEAD
	DummyPlot() :
			xolotlCore::Identifiable("unused") {
	}
=======
    DummyPlot() : xolotlCore::Identifiable("unused") {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Data provider used for the plot.
	 */
	std::shared_ptr<IDataProvider> plotDataProvider;

<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
	DummyPlot(const std::string& name);
=======
	DummyPlot(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor.
	 */
	~DummyPlot();

	/**
	 * Method managing everything that is related to the rendering of a plot.
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	void render(const std::string& fileName = "fileName");
=======
	void render(std::string fileName = "fileName");
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Method that will save the plotted plot in a file.
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	void write(const std::string& fileName);
=======
	void write(std::string fileName);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Method allowing the user to set the PlottingStyle.
	 * \see IPlot.h
	 */
	void setPlottingStyle(PlottingStyle style);

	/**
	 * Method getting the PlottingStyle.
	 * \see IPlot.h
	 */
	PlottingStyle getPlottingStyle();

	/**
	 * Sets the data provider used for the plots.
	 * \see IPlot.h
	 */
	void setDataProvider(std::shared_ptr<IDataProvider> dataProvider);

	/**
	 * Method adding one data provider to the vector plotDataProviders
	 * \see IPlot.h
	 */
	void addDataProvider(std::shared_ptr<IDataProvider> dataProvider);

	/**
	 * Gets the data provider used.
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	std::shared_ptr<IDataProvider> getDataProvider() const;
=======
	std::shared_ptr<IDataProvider> getDataProvider() const ;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Method getting the i-th data provider for SeriesPlot
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	std::shared_ptr<IDataProvider> getDataProvider(int i) const;
=======
	std::shared_ptr<IDataProvider> getDataProvider(int i) const ;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Method getting the total number of data providers
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	int getDataProviderNumber() const;
=======
	int getDataProviderNumber() const ;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Sets the label provider used for the plots.
	 * \see IPlot.h
	 */
	void setLabelProvider(std::shared_ptr<LabelProvider> labelProvider);

	/**
	 * Gets the label provider used.
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	std::shared_ptr<LabelProvider> getLabelProvider() const;
=======
	std::shared_ptr<LabelProvider> getLabelProvider() const ;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Method that enables the rendering of the legend.
	 * \see IPlot.h
	 */
	void showLegend(bool legendShow = true);

	/**
	 * Method getting the legend.
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	std::string getLegend() const;
=======
	std::string getLegend() const ;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Method that enables the log scale.
	 * \see IPlot.h
	 */
	void setLogScale(bool logScale = true);

<<<<<<< HEAD
};
//end class DummyPlot

}//end namespace xolotlViz
=======

};  //end class DummyPlot

}  //end namespace xolotlViz
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

#endif
