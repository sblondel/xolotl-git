#ifndef EVENTCOUNTER_H
#define EVENTCOUNTER_H

#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IEventCounter.h"

<<<<<<< HEAD
namespace xolotlPerf{
=======
namespace xolotlPerf {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * An EventCounter keeps a count.  Code using an EventCounter can
 * increment the counter whenever an event of interest occurs, and
 * retrieve the count whenever it is desired.
 */
<<<<<<< HEAD
class EventCounter : public IEventCounter, public xolotlCore::Identifiable
{
=======
class EventCounter: public IEventCounter, public xolotlCore::Identifiable {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
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
    EventCounter( void )
      : xolotlCore::Identifiable( "unused" ),
        value( 0 )
    { }

=======
	IEventCounter::ValType value;

	/**
	 * We declare a private default constructor to force
	 * client code to provide a name when creating EventCounters.
	 */
	EventCounter(void) :
			xolotlCore::Identifiable("unused"), value(0) {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
	 * EventCounter constructor that takes the argument name
	 *
	 * @param name The EventCounter's name
	 */
<<<<<<< HEAD
	EventCounter(const std::string& name)
      : xolotlCore::Identifiable( name ),
        value( 0 )
    { }
    
=======
	EventCounter(const std::string& name) :
			xolotlCore::Identifiable(name), value(0) {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~EventCounter() { }
=======
	virtual ~EventCounter() {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * This operation returns the value of the EventCounter,
	 * the frequency of the specified event.
	 */
<<<<<<< HEAD
	virtual IEventCounter::ValType getValue() const  { return value; }
=======
	virtual IEventCounter::ValType getValue() const {
		return value;
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * This operation increments the EventCounter.
	 */
<<<<<<< HEAD
	virtual void increment()    { ++value; }

};  //end class EventCounter

}  //end namespace xolotlPerf
=======
	virtual void increment() {
		++value;
	}

};
//end class EventCounter

}//end namespace xolotlPerf
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

#endif
