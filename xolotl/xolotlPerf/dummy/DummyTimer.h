#ifndef DUMMYTIMER_H
#define DUMMYTIMER_H

<<<<<<< HEAD
<<<<<<< HEAD
#include "xolotlPerf/ITimer.h"
#include "xolotlCore/Identifiable.h"

using namespace std;

namespace xolotlPerf {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include "ITimer.h"
#include "Identifiable.h"

using namespace std;

namespace xolotlPerf{
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

/**
 * The DummyTimer class is instantiated by the DummerHandlerRegistry class
 * and realizes the DummyTimer interface.
 */
<<<<<<< HEAD
<<<<<<< HEAD
class DummyTimer: public ITimer, public xolotlCore::Identifiable {
=======
class DummyTimer : public ITimer, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
class DummyTimer : public ITimer, public xolotlCore::Identifiable
{
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
private:

	/**
	 * The default constructor is declared as private since Timers
	 *  must be initialized with a name.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	DummyTimer(void) :
			xolotlCore::Identifiable("unused") {
	}
=======
    DummyTimer()
      : xolotlCore::Identifiable("unused")
    { }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
    DummyTimer()
      : xolotlCore::Identifiable("unused")
    { }
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

public:

	/**
	 * DummyTimer constructor that takes the argument timerName
	 * to distinguish specific DummyTimer.
	 *
<<<<<<< HEAD
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
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
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
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

#endif
