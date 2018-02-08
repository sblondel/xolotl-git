#ifndef DUMMYEVENTCOUNTER_H
#define DUMMYEVENTCOUNTER_H

#include <string>
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IEventCounter.h"

using namespace std;

<<<<<<< HEAD
namespace xolotlPerf{
=======
namespace xolotlPerf {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * The DummyEventCounter class is instantiated by the DummyHandlerRegistry
 * class and realizes the DummyEventCounter interface.
 */
<<<<<<< HEAD
class DummyEventCounter : public IEventCounter, public xolotlCore::Identifiable
{
=======
class DummyEventCounter: public IEventCounter, public xolotlCore::Identifiable {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

private:

	/**
	 * The default constructor is declared private since all EventCounters
	 *  must be initialized with a name.
	 */
<<<<<<< HEAD
    DummyEventCounter(void)
      : xolotlCore::Identifiable("unused")
    { }

=======
	DummyEventCounter(void) :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
<<<<<<< HEAD
	 * DummyEventCounter constructor that takes the argument name
	 *
	 * @param name The DummyEventCounter's name
	 */
	DummyEventCounter(const std::string& name)
      : xolotlCore::Identifiable("unused")
    { }

=======
	 * DummyEventCounter constructor that takes the argument name but
	 * doesn't do anything with it
	 */
	DummyEventCounter(const std::string& name) :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~DummyEventCounter() { }
=======
	virtual ~DummyEventCounter() {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * This operation returns the value of the DummyEventCounter,
	 * the frequency of the specified event.
	 */
<<<<<<< HEAD
	virtual IEventCounter::ValType getValue() const  { return 0; }

=======
	virtual IEventCounter::ValType getValue() const {
		return 0;
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * This operation increments the DummyEventCounter.
	 */
<<<<<<< HEAD
	virtual void increment()    {  }


};  //end class DummyEventCounter

}  //end namespace xolotlPerf
=======
	virtual void increment() {
	}

};
//end class DummyEventCounter

}//end namespace xolotlPerf
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

#endif
