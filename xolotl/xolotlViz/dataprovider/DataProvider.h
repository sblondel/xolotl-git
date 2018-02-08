#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

// Includes
#include "IDataProvider.h"
#include <Identifiable.h>

namespace xolotlViz {

/**
 *  Realization of the IDataProvider interface. This is a general class with general methods,
 *  to actually get data from the data provider, one needs to use the subclasses.
 */
class DataProvider: public virtual IDataProvider, public xolotlCore::Identifiable {

protected:

	/**
     * Declare the constructor as private to force the use of a name
	 */
    DataProvider() : xolotlCore::Identifiable("unused") {}

	/**
	 * Collection of data points.
	 */
	std::shared_ptr< std::vector<Point> > dataPoints;

public:

	/**
	 * Name of the data contained in the data attribute.
	 */
	std::string dataName;

	/**
	 * The default constructor.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	DataProvider(const std::string& name);
=======
	DataProvider(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	DataProvider(std::string name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor.
	 */
	~DataProvider();

	/**
	 * Returns a collection of the data points.
	 * \see IDataProvider.h
	 */
	std::shared_ptr< std::vector<Point> > getDataPoints() const;

	/**
	 * Method filling the data collection.
	 * \see IDataProvider.h
	 */
	void setPoints(std::shared_ptr< std::vector<Point> > points);

	/**
	 * Returns the value of the mean of all the data points.
	 * \see IDataProvider.h
	 */
	double getDataMean() const;

	/**
	 * Method that has to be overwritten by subclasses.
	 * Should return the vector of quantity that will be plotted on the X axis.
	 * Quantity being x, y, z, t, or value.
	 * \see IDataProvider.h
	 */
	virtual std::vector<double> getAxis1Vector() const {
		return std::vector<double>();
	}

	/**
	 * Method that has to be overwritten by subclasses.
	 * Should return the vector of quantity that will be plotted on the Y axis.
	 * Quantity being x, y, z, t, or value.
	 * \see IDataProvider.h
	 */
	virtual std::vector<double> getAxis2Vector() const {
		return std::vector<double>();
	}

	/**
	 * Method that has to be overwritten by subclasses.
	 * Should return the vector of quantity that will be plotted on the Z axis.
	 * Quantity being x, y, z, t, or value.
	 * \see IDataProvider.h
	 */
	virtual std::vector<double> getAxis3Vector() const {
		return std::vector<double>();
	}

	/**
	 * Method that has to be overwritten by subclasses.
	 * Should return the vector of time steps that will be used for the VideoPlots.
	 * \see IDataProvider.h
	 */
	virtual std::vector<double> getAxis4Vector() const {
		return std::vector<double>();
	}


	/**
 	 * This operation returns the name of the data.
 	 * @return the name
 	 */
	virtual std::string getDataName() const {
                return dataName;
        }

        /**
 	 * This operation sets the name of the data.
 	 * @param name the name of the data
 	 */ 
<<<<<<< HEAD
<<<<<<< HEAD
	virtual void setDataName(const std::string& name) {
=======
	virtual void setDataName(std::string name) {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	virtual void setDataName(std::string name) {
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
                dataName = name;
        }

};

//end class DataProvider

} /* namespace xolotlViz */
#endif
