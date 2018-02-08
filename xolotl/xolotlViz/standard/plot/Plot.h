#ifndef PLOT_H
#define PLOT_H

// Includes
#include <IPlot.h>
#include <Identifiable.h>

namespace xolotlViz {

/**
 * Plot is the class that realizes the interface IPlot.
 * It is a general class that provides general methods, but to actual plot anything,
 * the user needs to use one of its subclasses.
 */
class Plot: public IPlot, public xolotlCore::Identifiable {

protected:

	/**
<<<<<<< HEAD
     * Declare the constructor as private to force the use of a name
	 */
    Plot() : xolotlCore::Identifiable("unused") {}
=======
	 * Declare the constructor as private to force the use of a name
	 */
	Plot() :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Choice of PlottingStyle.
	 */
	PlottingStyle plotStyle;

	/**
	 * If it is equal to True, the legend will be displayed.
	 */
	bool enableLegend = false;

	/**
	 * If it is equal to True, a log scale will be used (for 1D plot for now).
	 */
	bool enableLogScale = false;

	/**
	 * Data provider used for the plot.
	 */
	std::shared_ptr<IDataProvider> plotDataProvider;

public:

	/**
	 * The default constructor
	 */
	Plot(const std::string& name);

	/**
	 * The destructor.
	 */
	~Plot();

	/**
	 * Method managing everything that is related to the rendering of a plot.
	 * \see IPlot.h
	 */
	void render(const std::string& fileName = "fileName");

	/**
	 * Method that will save the plotted plot in a file.
	 * \see IPlot.h
	 */
	void write(const std::string& fileName);

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
	std::shared_ptr<IDataProvider> getDataProvider() const ;
=======
	std::shared_ptr<IDataProvider> getDataProvider() const;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Method getting the i-th data provider for SeriesPlot
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	std::shared_ptr<IDataProvider> getDataProvider(int i) const ;
=======
	std::shared_ptr<IDataProvider> getDataProvider(int i) const;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Method getting the total number of data providers
	 * \see IPlot.h
	 */
<<<<<<< HEAD
	int getDataProviderNumber() const ;
=======
	int getDataProviderNumber() const;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

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
	std::shared_ptr<LabelProvider> getLabelProvider() const ;
=======
	std::shared_ptr<LabelProvider> getLabelProvider() const;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

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
	std::string getLegend() const ;
=======
	std::string getLegend() const;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Method that enables the log scale.
	 * \see IPlot.h
	 */
	void setLogScale(bool logScale = true);

};

//end class Plot

} /* namespace xolotlViz */

#endif
