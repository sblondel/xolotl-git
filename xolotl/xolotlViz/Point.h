#ifndef POINT_H
#define POINT_H

// Includes
#include <string>

namespace xolotlViz {

/**
 * Class describing the structure of data points.
 * The attributes are the three spatial dimensions, the time, and the value of the quantity
 * under consideration at this position.
 */
class Point {

<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
public:

	/**
	 * The time step.
	 */
<<<<<<< HEAD
	double t;
=======
	double t = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The X position on the grid.
	 */
<<<<<<< HEAD
	double x;
=======
	double x = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The Y position on the grid.
	 */
<<<<<<< HEAD
	double y;
=======
	double y = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The Z position on the grid.
	 */
<<<<<<< HEAD
	double z;
=======
	double z = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Value of the quantity of interest at the time step t and position on the grid x,y,z.
	 */
<<<<<<< HEAD
	double value;
=======
	double value = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
	Point() :
			t(0.0), x(0.0), y(0.0), z(0.0), value(0.0) {}
=======
	Point() {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor
	 */
	~Point() {}

};

//end class Point

} /* namespace xolotlViz */

#endif
