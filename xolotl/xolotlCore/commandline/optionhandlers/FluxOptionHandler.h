#ifndef FLUXOPTIONHANDLER_H
#define FLUXOPTIONHANDLER_H

// Includes
#include <stdlib.h>
#include "OptionHandler.h"

namespace xolotlCore {

/**
 * FluxOptionHandler handles the flux option.
 */
<<<<<<< HEAD
class FluxOptionHandler : public OptionHandler {
=======
class FluxOptionHandler: public OptionHandler {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
public:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
    FluxOptionHandler() :
    	OptionHandler("flux",
    			"flux <value>                      "
    			"This option allows the user to change the flux "
    			"by the factor specified (in nm).\n") {}
=======
	FluxOptionHandler() :
			OptionHandler("flux", "flux <value>                      "
					"This option allows the user to change the flux "
					"by the factor specified (in nm).\n") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The destructor
	 */
<<<<<<< HEAD
    ~FluxOptionHandler() {}

    /**
     * This method will set the IOptions fluxFlag and fluxAmplitude
     * to the value given as the argument.
     *
     * @param opt The pointer to the option that will be modified.
     * @param arg The value for the helium flux.
     */
    bool handler(IOptions *opt, const std::string& arg) {
    	// Set the corresponding flag to true
    	opt->setFluxFlag(true);

    	// Set the value for the flux
    	double flux = strtod(arg.c_str(), NULL);

    	opt->setFluxAmplitude(flux);
    	return true;
    }

};//end class FluxOptionHandler
=======
	~FluxOptionHandler() {
	}

	/**
	 * This method will set the IOptions fluxFlag and fluxAmplitude
	 * to the value given as the argument.
	 *
	 * @param opt The pointer to the option that will be modified.
	 * @param arg The value for the helium flux.
	 */
	bool handler(IOptions *opt, const std::string& arg) {
		// Set the corresponding flag to true
		opt->setFluxFlag(true);

		// Set the value for the flux
		double flux = strtod(arg.c_str(), NULL);

		opt->setFluxAmplitude(flux);
		return true;
	}

};
//end class FluxOptionHandler
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

} /* namespace xolotlCore */

#endif
