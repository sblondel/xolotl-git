#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

// Includes
#include "Point.h"
#include <vector>
#include <string>
#include <memory>
#include <IIdentifiable.h>

namespace xolotlViz {

/**
 * IDataProvider describes the structure needed as a link between Xololt outputs
 * and quantities that the user wants to plot.
 */
class IDataProvider : public virtual xolotlCore::IIdentifiable {

public:

	/**
	 * The destructor
	 */
	virtual ~IDataProvider() { }

	/**
	 * Returns a collection of the data points.
	 * @return The collection of Point.
	 */
	virtual std::shared_ptr< std::vector<Point> > getDataPoints() const = 0;

	/**
	 * Returns the value of the mean of all the data points.
	 * @return The mean of all the values of the data.
	 */
	virtual double getDataMean() const = 0;

	/**
	 * Method filling the data collection.
	 * @param points A collection of Point.
	 */
	virtual void setPoints(std::shared_ptr< std::vector<Point> > points) = 0;

	/**
	 * Method returning the vector of quantity that will be plotted on the X axis.
	 * Quantity being x, y, z, t, or value.
	 * @return The vector of quantity.
	 */
	virtual std::vector<double> getAxis1Vector() const = 0;

	/**
	 * Method returning the vector of quantity that will be plotted on the Y axis.
	 * Quantity being x, y, z, t, or value.
	 * @return The vector of quantity.
	 */
	virtual std::vector<double> getAxis2Vector() const = 0;

	/**
	 * Method returning the vector of quantity that will be plotted on the Z axis.
	 * Quantity being x, y, z, t, or value.
	 * @return The vector of quantity.
	 */
	virtual std::vector<double> getAxis3Vector() const = 0;

	/**
	 * Method returning the vector of time steps that will be used for the VideoPlots.
	 * @return The vector of time steps.
	 */
	virtual std::vector<double> getAxis4Vector() const = 0;

	/**
 	 * This operation returns the name of the data.
 	 * @return the name
 	 */
	virtual std::string getDataName() const = 0;

        /**
 	 * This operation sets the name of the data.
 	 * @param name the name of the data
 	 */ 
<<<<<<< HEAD
	virtual void setDataName(const std::string& name) = 0;
=======
	virtual void setDataName(std::string name) = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

};

//end class IDataProvider

} /* namespace xolotlViz */
#endif
