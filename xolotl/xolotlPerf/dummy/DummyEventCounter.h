#ifndef DUMMYEVENTCOUNTER_H
#define DUMMYEVENTCOUNTER_H

#include <string>
<<<<<<< HEAD
<<<<<<< HEAD
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IEventCounter.h"

using namespace std;

namespace xolotlPerf {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include "Identifiable.h"
#include "IEventCounter.h"

using namespace std;

namespace xolotlPerf{
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

/**
 * The DummyEventCounter class is instantiated by the DummyHandlerRegistry
 * class and realizes the DummyEventCounter interface.
 */
<<<<<<< HEAD
<<<<<<< HEAD
class DummyEventCounter: public IEventCounter, public xolotlCore::Identifiable {
=======
class DummyEventCounter : public IEventCounter, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
class DummyEventCounter : public IEventCounter, public xolotlCore::Identifiable
{
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

private:

	/**
	 * The default constructor is declared private since all EventCounters
	 *  must be initialized with a name.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	DummyEventCounter(void) :
			xolotlCore::Identifiable("unused") {
	}
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
    DummyEventCounter(void)
      : xolotlCore::Identifiable("unused")
    { }

<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * DummyEventCounter constructor that takes the argument name but
	 * doesn't do anything with it
	 */
	DummyEventCounter(const std::string& name) :
			xolotlCore::Identifiable("unused") {
	}
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * DummyEventCounter constructor that takes the argument name
	 *
	 * @param name The DummyEventCounter's name
	 */
	DummyEventCounter(std::string name)
      : xolotlCore::Identifiable("unused")
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
	virtual ~DummyEventCounter() {
	}
=======
	virtual ~DummyEventCounter() { }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	virtual ~DummyEventCounter() { }
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation returns the value of the DummyEventCounter,
	 * the frequency of the specified event.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual IEventCounter::ValType getValue() const {
		return 0;
	}
=======
	virtual unsigned long getValue() const  { return 0; }

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
	virtual unsigned long getValue() const  { return 0; }

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	/**
	 * This operation increments the DummyEventCounter.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	virtual void increment() {
	}

};
//end class DummyEventCounter

}//end namespace xolotlPerf
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	virtual void increment()    {  }


};  //end class DummyEventCounter

}  //end namespace xolotlPerf
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#endif
