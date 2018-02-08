#ifndef IDENTIFIABLE_H
#define IDENTIFIABLE_H

#include "IIdentifiable.h"

namespace xolotlCore {

/**
 * An Identifiable implements the IIdentifiable interface, so
 * that classes derived from Identifiable will be able to identify
 * themselves.
 */
<<<<<<< HEAD
class Identifiable : public virtual IIdentifiable
{
private:

    std::string name;

public:

    Identifiable( const std::string& _name )
      : name( _name )
    { }

    virtual ~Identifiable( void ) { }

    /**
     * Obtain the object's given name.
     */
    virtual std::string getName( void ) const   { return name; }
=======
class Identifiable: public virtual IIdentifiable {
private:

	std::string name;

public:

	Identifiable(const std::string& _name) :
			name(_name) {
	}

	virtual ~Identifiable(void) {
	}

	/**
	 * Obtain the object's given name.
	 */
	virtual std::string getName(void) const {
		return name;
	}
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
};

} // end namespace xolotlCore

#endif // IDENTIFIABLE_H
