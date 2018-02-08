#ifndef W211TRAPMUTATIONHANDLER_H
#define W211TRAPMUTATIONHANDLER_H

#include "TrapMutationHandler.h"

namespace xolotlCore {

/**
 * This class realizes the ITrapMutationHandler interface responsible for the modified
 * trap-mutation of small helium clusters close to the surface for a (211) oriented
 * tungsten material.
 */
class W211TrapMutationHandler: public TrapMutationHandler {
private:

	/**
	 * Method initializing the depth vector, the size vector,
	 * and desorption information.
	 */
	void initializeDepthSize() {
		depthVec = {0.5, 0.8, 1.0, 1.0, 1.3, 1.3, 1.2};
		sizeVec = {1, 1, 1, 2, 1, 2, 3};

		// He1 desorpts with 59%
		desorp = Desorption(1, 0.59);

		return;
	}

public:

	/**
	 * The constructor
	 */
	W211TrapMutationHandler() {}

	/**
	 * The Destructor
	 */
	~W211TrapMutationHandler() {}

};
//end class W211TrapMutationHandler

}

#endif
