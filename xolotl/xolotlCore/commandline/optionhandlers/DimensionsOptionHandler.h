#ifndef DIMENSIONSOPTIONHANDLER_H
#define DIMENSIONSOPTIONHANDLER_H

// Includes
#include "OptionHandler.h"

namespace xolotlCore {

/**
 * DimensionsOptionHandler handles the number of dimensions option.
 */
<<<<<<< HEAD
class DimensionsOptionHandler : public OptionHandler {
=======
class DimensionsOptionHandler: public OptionHandler {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
    DimensionsOptionHandler() :
    	OptionHandler("dimensions",
    			"dimensions <dimNumber>            "
    			"This option allows the user to switch between a 1, 2, or 3 "
    			"dimensions simulation.  \n"
    			"                                    Only 1 can be used for now.\n")
	{}
=======
	DimensionsOptionHandler() :
			OptionHandler("dimensions",
					"dimensions <dimNumber>            "
							"This option allows the user to switch between a 1, 2, or 3 "
							"dimensions simulation.  \n") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The destructor
	 */
<<<<<<< HEAD
    ~DimensionsOptionHandler() {}

    /**
     * This method will set the IOptions dimensionNumber
     * to the value given as the argument.
     *
     * @param opt The pointer to the option that will be modified.
     * @param arg The number of dimensions.
     */
    bool handler(IOptions *opt, const std::string& arg) {
    	// Convert to integer
    	int number = strtol(arg.c_str(), NULL, 10);
    	// Set the number of dimensions
    	opt->setDimensionNumber(number);

    	return true;
    }

};//end class DimensionsOptionHandler
=======
	~DimensionsOptionHandler() {
	}

	/**
	 * This method will set the IOptions dimensionNumber
	 * to the value given as the argument.
	 *
	 * @param opt The pointer to the option that will be modified.
	 * @param arg The number of dimensions.
	 */
	bool handler(IOptions *opt, const std::string& arg) {
		// Convert to integer
		int number = strtol(arg.c_str(), NULL, 10);
		// Set the number of dimensions
		opt->setDimensionNumber(number);

		return true;
	}

};
//end class DimensionsOptionHandler
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

} /* namespace xolotlCore */

#endif
