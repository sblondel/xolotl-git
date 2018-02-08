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
<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
public:

	/**
	 * The time step.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	double t;
=======
	double t = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	double t = 0.0;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The X position on the grid.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	double x;
=======
	double x = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	double x = 0.0;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The Y position on the grid.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	double y;
=======
	double y = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	double y = 0.0;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The Z position on the grid.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	double z;
=======
	double z = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	double z = 0.0;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * Value of the quantity of interest at the time step t and position on the grid x,y,z.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	double value;
=======
	double value = 0.0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	double value = 0.0;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	Point() :
			t(0.0), x(0.0), y(0.0), z(0.0), value(0.0) {}
=======
	Point() {}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	Point() {}
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
	~Point() {}

};

//end class Point

} /* namespace xolotlViz */

#endif
