#ifndef ITIMER_H
#define ITIMER_H

<<<<<<< HEAD
#include "mpi.h"
#include <string>
#include <float.h>
=======
#include <string>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include "../xolotlCore/IIdentifiable.h"

using namespace std;

namespace xolotlPerf {

/**
 * Realizations of this interface are responsible for the collection
 * of performance timing statistics.
 */
<<<<<<< HEAD
class ITimer: public virtual xolotlCore::IIdentifiable {
=======
class ITimer : public virtual xolotlCore::IIdentifiable {
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
<<<<<<< HEAD
	 * The type of a timer value.
	 */
	typedef double ValType;

	/**
	 * The MPI type to use when transferring a ValType.
	 */
	static constexpr MPI_Datatype MPIValType = MPI_DOUBLE;

	/**
	 * The minimum value possible.
	 */
	static constexpr ValType MinValue = 0.0;

	/**
	 * The maximum value possible.
	 */
	static constexpr ValType MaxValue = DBL_MAX;

	/**
	 * Destroy the timer.
	 */
	virtual ~ITimer(void) {
	}

	/**
	 * Start the timer.
	 */
	virtual void start(void) = 0;

	/**
	 * Stop the timer.
	 */
	virtual void stop(void) = 0;

	/**
	 * Access the timer's value.  (Only valid if timer is not running.)
	 */
	virtual ValType getValue(void) const = 0;

	/**
	 * Reset the timer's value.  Only valid if timer is not running.
	 */
	virtual void reset(void) = 0;

	/**
	 * Obtain a string describing the units of the timer's value.
	 */
	virtual std::string getUnits(void) const = 0;
=======
	 * The destructor
	 */
	virtual ~ITimer() { }


    /**
     * This operations starts the ITimer.
     */
    virtual void start() = 0;

    /**
     * This operation stops the ITimer.
     */
    virtual void stop() = 0;

    /**
     * This operation returns the value of the ITimer.
     */
    virtual double getValue() const = 0;

    /**
     * This operation returns the units of the ITimer.
     */
    virtual std::string getUnits() const = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

};
//end class ITimer

}//end namespace xolotlPerf

#endif
