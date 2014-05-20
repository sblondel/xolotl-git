#ifndef DUMMYEVENTCOUNTER_H
#define DUMMYEVENTCOUNTER_H

#include <string>
<<<<<<< HEAD
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IEventCounter.h"

using namespace std;

namespace xolotlPerf {
=======
#include "Identifiable.h"
#include "IEventCounter.h"

using namespace std;

namespace xolotlPerf{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

/**
 * The DummyEventCounter class is instantiated by the DummyHandlerRegistry
 * class and realizes the DummyEventCounter interface.
 */
<<<<<<< HEAD
class DummyEventCounter: public IEventCounter, public xolotlCore::Identifiable {
=======
class DummyEventCounter : public IEventCounter, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

private:

	/**
	 * The default constructor is declared private since all EventCounters
	 *  must be initialized with a name.
	 */
<<<<<<< HEAD
	DummyEventCounter(void) :
			xolotlCore::Identifiable("unused") {
	}
=======
    DummyEventCounter(void)
      : xolotlCore::Identifiable("unused")
    { }

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
<<<<<<< HEAD
	 * DummyEventCounter constructor that takes the argument name but
	 * doesn't do anything with it
	 */
	DummyEventCounter(const std::string& name) :
			xolotlCore::Identifiable("unused") {
	}
=======
	 * DummyEventCounter constructor that takes the argument name
	 *
	 * @param name The DummyEventCounter's name
	 */
	DummyEventCounter(std::string name)
      : xolotlCore::Identifiable("unused")
    { }

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~DummyEventCounter() {
	}
=======
	virtual ~DummyEventCounter() { }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns the value of the DummyEventCounter,
	 * the frequency of the specified event.
	 */
<<<<<<< HEAD
	virtual IEventCounter::ValType getValue() const {
		return 0;
	}
=======
	virtual unsigned long getValue() const  { return 0; }

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation increments the DummyEventCounter.
	 */
<<<<<<< HEAD
	virtual void increment() {
	}

};
//end class DummyEventCounter

}//end namespace xolotlPerf
=======
	virtual void increment()    {  }


};  //end class DummyEventCounter

}  //end namespace xolotlPerf
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

#endif
