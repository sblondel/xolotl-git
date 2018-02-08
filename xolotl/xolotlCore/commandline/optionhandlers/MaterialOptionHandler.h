#ifndef MATERIALOPTIONHANDLER_H
#define MATERIALOPTIONHANDLER_H

// Includes
#include "OptionHandler.h"

namespace xolotlCore {

/**
 * MaterialOptionHandler handles the material option.
 */
class MaterialOptionHandler: public OptionHandler {
public:

	/**
	 * The default constructor
	 */
	MaterialOptionHandler() :
			OptionHandler("material",
					"material <material>               "
							"This option allows the user to change the profile of "
							"the helium flux corresponding to the material.  \n"
							"                                    The material options are as follows: "
<<<<<<< HEAD
							"{W100, W110, W111, W211, Fuel, TRIDYN}, where W is for \n"
=======
							"{W100, W110, W111, W211, Fuel, TRIDYN, Fe}, where W is for \n"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
							"                                    tungsten and the numbers correspond to "
							"the surface orientation.\n") {
	}

	/**
	 * The destructor
	 */
	~MaterialOptionHandler() {
	}

	/**
	 * This method will set the IOptions materialFlag and materialName
	 * to the value given as the argument.
	 *
	 * @param opt The pointer to the option that will be modified.
	 * @param arg The name of the material.
	 */
	bool handler(IOptions *opt, const std::string& arg) {
		// Set the material name
		opt->setMaterial(arg);
		return true;
	}

};
//end class MaterialOptionHandler

} /* namespace xolotlCore */

#endif
