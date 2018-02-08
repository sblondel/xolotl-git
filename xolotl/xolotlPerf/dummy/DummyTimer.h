#ifndef DUMMYTIMER_H
#define DUMMYTIMER_H

#include "xolotlPerf/ITimer.h"
#include "xolotlCore/Identifiable.h"

using namespace std;

<<<<<<< HEAD
namespace xolotlPerf{
=======
namespace xolotlPerf {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * The DummyTimer class is instantiated by the DummerHandlerRegistry class
 * and realizes the DummyTimer interface.
 */
<<<<<<< HEAD
class DummyTimer : public ITimer, public xolotlCore::Identifiable
{
=======
class DummyTimer: public ITimer, public xolotlCore::Identifiable {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
private:

	/**
	 * The default constructor is declared as private since Timers
	 *  must be initialized with a name.
	 */
<<<<<<< HEAD
    DummyTimer(void)
      : xolotlCore::Identifiable("unused")
    { }
=======
	DummyTimer(void) :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
	 * DummyTimer constructor that takes the argument timerName
	 * to distinguish specific DummyTimer.
	 *
<<<<<<< HEAD
	 * @param timerName The DummyTimer's name
	 */
	DummyTimer(const std::string& name)
      : xolotlCore::Identifiable("unused")
    { }
=======
	 * @param name The DummyTimer's name
	 */
	DummyTimer(const std::string& name) :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Destroy the timer.
	 */
<<<<<<< HEAD
	virtual ~DummyTimer(void) { }

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
=======
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Obtain a string describing the units of the timer's value.
	 */
<<<<<<< HEAD
    virtual std::string getUnits(void) const;

};  //end class DummyTimer

}  //end namespace xolotlPerf
=======
	virtual std::string getUnits(void) const;

};
//end class DummyTimer

}//end namespace xolotlPerf
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

#endif
