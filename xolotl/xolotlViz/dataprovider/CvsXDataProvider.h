#ifndef CVSXDATAPROVIDER_H
#define CVSXDATAPROVIDER_H

// Includes
#include "DataProvider.h"
#include <vector>

namespace xolotlViz {

/**
 * Subclass of DataProvider that will provide the methods to give the value (concentration here)
 * and X data to a ScatterPlot.
 */
class CvsXDataProvider: public DataProvider {

private:

	/**
     * Declare the constructor as private to force the use of a name
	 */
    CvsXDataProvider() : DataProvider() {}

public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	CvsXDataProvider(const std::string& name);
=======
	CvsXDataProvider(std::string name);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	CvsXDataProvider(std::string name);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
	~CvsXDataProvider();

	/**
	 * Method returning a vector containing the 'x' field of the collection of Point of the DataProvider.
	 * @return The vector of Point x value.
	 */
	virtual std::vector<double> getAxis1Vector() const;

	/**
	 * Method returning a vector containing the 'value' field of the collection of Point of the DataProvider.
	 * @return The vector of Point value.
	 */
	virtual std::vector<double> getAxis2Vector() const;

};

//end class CvsXDataProvider

} /* namespace xolotlViz */

#endif
