#ifndef IIDENTIFIABLE_H
#define IIDENTIFIABLE_H

#include <string>

namespace xolotlCore {

/**
 * An Identifiable is an object that has some identification (e.g., a name
 * and/or an ID).
 */
<<<<<<< HEAD
class IIdentifiable
{
public:

    /**
     * Obtain the object's given name.
     */
    virtual std::string getName( void ) const = 0;
=======
class IIdentifiable {
public:

	/**
	 * Obtain the object's given name.
	 */
	virtual std::string getName(void) const = 0;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
};

} // end namespace xolotlCore

#endif // IIDENTIFIABLE_H
