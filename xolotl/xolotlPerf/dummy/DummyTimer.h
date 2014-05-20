#ifndef DUMMYTIMER_H
#define DUMMYTIMER_H

<<<<<<< HEAD
#include "xolotlPerf/ITimer.h"
#include "xolotlCore/Identifiable.h"

using namespace std;

namespace xolotlPerf {
=======
#include "ITimer.h"
#include "Identifiable.h"

using namespace std;

namespace xolotlPerf{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

/**
 * The DummyTimer class is instantiated by the DummerHandlerRegistry class
 * and realizes the DummyTimer interface.
 */
<<<<<<< HEAD
class DummyTimer: public ITimer, public xolotlCore::Identifiable {
=======
class DummyTimer : public ITimer, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
private:

	/**
	 * The default constructor is declared as private since Timers
	 *  must be initialized with a name.
	 */
<<<<<<< HEAD
	DummyTimer(void) :
			xolotlCore::Identifiable("unused") {
	}
=======
    DummyTimer()
      : xolotlCore::Identifiable("unused")
    { }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
	 * DummyTimer constructor that takes the argument timerName
	 * to distinguish specific DummyTimer.
	 *
<<<<<<< HEAD
	 * @param name The DummyTimer's name
	 */
	DummyTimer(const std::string& name) :
			xolotlCore::Identifiable("unused") {
	}

	/**
	 * Destroy the timer.
	 */
	virtual ~DummyTimer(void) {
	}

	/**
	 * Start the timer.
	 */
	virtual void start(void);

	/**
	 * Stop the timer.
	 */
	virtual void stop(void);

	/**
	 * Reset the timer's value.
	 */
	virtual void reset(void);

	/**
	 * Obtain the timer's value.
	 */
	virtual ITimer::ValType getValue(void) const;

	/**
	 * Obtain a string describing the units of the timer's value.
	 */
	virtual std::string getUnits(void) const;

};
//end class DummyTimer

}//end namespace xolotlPerf
=======
	 * @param timerName The DummyTimer's name
	 */
	DummyTimer(std::string name)
      : xolotlCore::Identifiable("unused")
    { }

	/**
	 * The destructor.
	 */
	virtual ~DummyTimer() { }

    /**
     * This operations starts the ITimer.
     */
	virtual void start();

    /**
     * This operation stops the ITimer.
     */
	virtual void stop();

    /**
     * This operation returns the value of the DummyTimer.
     */
    virtual double getValue() const;

	/**
	 * This operation returns the units of the GPTLTimer.
	 */
    virtual std::string getUnits() const;

};  //end class DummyTimer

}  //end namespace xolotlPerf
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

#endif
