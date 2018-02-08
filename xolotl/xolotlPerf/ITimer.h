#ifndef ITIMER_H
#define ITIMER_H

#include "mpi.h"
#include <string>
#include <float.h>
#include "../xolotlCore/IIdentifiable.h"

using namespace std;

namespace xolotlPerf {

/**
 * Realizations of this interface are responsible for the collection
 * of performance timing statistics.
 */
<<<<<<< HEAD
class ITimer : public virtual xolotlCore::IIdentifiable {

public:
    
    /**
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

=======
class ITimer: public virtual xolotlCore::IIdentifiable {

public:

	/**
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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Destroy the timer.
	 */
<<<<<<< HEAD
	virtual ~ITimer(void) { }


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
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

};
//end class ITimer

}//end namespace xolotlPerf

#endif
