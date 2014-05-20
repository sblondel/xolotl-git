#ifndef EVENTCOUNTER_H
#define EVENTCOUNTER_H

<<<<<<< HEAD
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IEventCounter.h"

namespace xolotlPerf {
=======
#include "Identifiable.h"
#include "IEventCounter.h"

namespace xolotlPerf{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

/**
 * An EventCounter keeps a count.  Code using an EventCounter can
 * increment the counter whenever an event of interest occurs, and
 * retrieve the count whenever it is desired.
 */
<<<<<<< HEAD
class EventCounter: public IEventCounter, public xolotlCore::Identifiable {
=======
class EventCounter : public IEventCounter, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
private:

	/**
	 * The value of this IEventCounter.
	 */
<<<<<<< HEAD
	IEventCounter::ValType value;

	/**
	 * We declare a private default constructor to force
	 * client code to provide a name when creating EventCounters.
	 */
	EventCounter(void) :
			xolotlCore::Identifiable("unused"), value(0) {
	}
=======
	unsigned long value;

	/**
     * We declare a private default constructor to force 
     * client code to provide a name when creating EventCounters.
	 */
    EventCounter( void )
      : xolotlCore::Identifiable( "unused" ),
        value( 0 )
    { }

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
	 * EventCounter constructor that takes the argument name
	 *
	 * @param name The EventCounter's name
	 */
<<<<<<< HEAD
	EventCounter(const std::string& name) :
			xolotlCore::Identifiable(name), value(0) {
	}
=======
	EventCounter(std::string name)
      : xolotlCore::Identifiable( name ),
        value( 0 )
    { }
    
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~EventCounter() {
	}
=======
	virtual ~EventCounter() { }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns the value of the EventCounter,
	 * the frequency of the specified event.
	 */
<<<<<<< HEAD
	virtual IEventCounter::ValType getValue() const {
		return value;
	}
=======
	virtual unsigned long getValue() const  { return value; }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation increments the EventCounter.
	 */
<<<<<<< HEAD
	virtual void increment() {
		++value;
	}

};
//end class EventCounter

}//end namespace xolotlPerf
=======
	virtual void increment()    { ++value; }

};  //end class EventCounter

}  //end namespace xolotlPerf
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

#endif
