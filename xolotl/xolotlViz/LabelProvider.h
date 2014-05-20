#ifndef LABELPROVIDER_H
#define LABELPROVIDER_H

// Includes
#include <Identifiable.h>
#include <string>

namespace xolotlViz {

/**
 * LabelProvider provides a series of labels to print on the plots.
 * One Plot must have only one LabelProvider.
 */
class LabelProvider: public xolotlCore::Identifiable {

private:

	/**
     * Declare the constructor as private to force the use of a name
	 */
    LabelProvider() : xolotlCore::Identifiable("unused") {};

public:

	/**
	 * The label of the X axis of the plot.
	 */
<<<<<<< HEAD
	std::string axis1Label;
=======
	std::string axis1Label = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The label of the Y axis of the plot.
	 */
<<<<<<< HEAD
	std::string axis2Label;
=======
	std::string axis2Label = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The label of the Z axis of the plot.
	 */
<<<<<<< HEAD
	std::string axis3Label;
=======
	std::string axis3Label = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The label for the time steps.
	 */
<<<<<<< HEAD
	std::string axis4Label;
=======
	std::string axis4Label = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Title label for the plot.
	 */
<<<<<<< HEAD
	std::string titleLabel;
=======
	std::string titleLabel = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Unit label for the plot.
	 */
<<<<<<< HEAD
	std::string unitLabel;
=======
	std::string unitLabel = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Time label for the plot.
	 */
<<<<<<< HEAD
	std::string timeLabel;
=======
	std::string timeLabel = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * Time step label for the plot.
	 */
<<<<<<< HEAD
	std::string timeStepLabel;
=======
	std::string timeStepLabel = " ";
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
	LabelProvider(const std::string& name) :
		xolotlCore::Identifiable(name),
		axis1Label(" "),
		axis2Label(" "),
		axis3Label(" "),
		axis4Label(" "),
		titleLabel(" "),
		unitLabel(" "),
		timeLabel(" "),
		timeStepLabel(" ")	{}
=======
	LabelProvider(std::string name) : xolotlCore::Identifiable(name) {};
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	~LabelProvider() {}
=======
	~LabelProvider() {};
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

};

//end class LabelProvider

} /* namespace xolotlViz */

#endif
