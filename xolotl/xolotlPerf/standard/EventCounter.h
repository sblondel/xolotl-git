#ifndef EVENTCOUNTER_H
#define EVENTCOUNTER_H

<<<<<<< HEAD
<<<<<<< HEAD
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IEventCounter.h"

namespace xolotlPerf {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include "Identifiable.h"
#include "IEventCounter.h"

namespace xolotlPerf{
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

/**
 * An EventCounter keeps a count.  Code using an EventCounter can
 * increment the counter whenever an event of interest occurs, and
 * retrieve the count whenever it is desired.
 */
<<<<<<< HEAD
<<<<<<< HEAD
class EventCounter: public IEventCounter, public xolotlCore::Identifiable {
=======
class EventCounter : public IEventCounter, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
class EventCounter : public IEventCounter, public xolotlCore::Identifiable
{
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
private:

	/**
	 * The value of this IEventCounter.
	 */
<<<<<<< HEAD
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
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	unsigned long value;

	/**
     * We declare a private default constructor to force 
     * client code to provide a name when creating EventCounters.
	 */
    EventCounter( void )
      : xolotlCore::Identifiable( "unused" ),
        value( 0 )
    { }

<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
	 * EventCounter constructor that takes the argument name
	 *
	 * @param name The EventCounter's name
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	EventCounter(const std::string& name) :
			xolotlCore::Identifiable(name), value(0) {
	}
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	EventCounter(std::string name)
      : xolotlCore::Identifiable( name ),
        value( 0 )
    { }
    
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * The destructor
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual ~EventCounter() {
	}
=======
	virtual ~EventCounter() { }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	virtual ~EventCounter() { }
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation returns the value of the EventCounter,
	 * the frequency of the specified event.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual IEventCounter::ValType getValue() const {
		return value;
	}
=======
	virtual unsigned long getValue() const  { return value; }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	virtual unsigned long getValue() const  { return value; }
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation increments the EventCounter.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual void increment() {
		++value;
	}

};
//end class EventCounter

}//end namespace xolotlPerf
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	virtual void increment()    { ++value; }

};  //end class EventCounter

}  //end namespace xolotlPerf
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#endif
