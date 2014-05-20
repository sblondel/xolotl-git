#ifndef IEVENTCOUNTER_H
#define IEVENTCOUNTER_H

<<<<<<< HEAD
#include "mpi.h"
#include <limits.h>
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
#include "../xolotlCore/IIdentifiable.h"

namespace xolotlPerf {

/**
 * Realizations of this interface are responsible for the collection
 * of event performance counter data.
 */
<<<<<<< HEAD
class IEventCounter: public virtual xolotlCore::IIdentifiable {

public:
	/**
	 * Type of the counter.
	 */
	typedef unsigned long ValType;

	/**
	 * MPI type used when transmitting a ValType.
	 */
	static constexpr MPI_Datatype MPIValType = MPI_UNSIGNED_LONG;

	/**
	 * The minimum value possible.
	 */
	static const ValType MinValue = 0;

	/**
	 * The maximum value possible.
	 */
	static const ValType MaxValue = ULONG_MAX;
=======
class IEventCounter : public virtual xolotlCore::IIdentifiable {

public:
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~IEventCounter() {
	}
=======
	virtual ~IEventCounter(){}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns the value of the IEventCounter, the frequency
	 * of the specified event.
	 */
<<<<<<< HEAD
	virtual ValType getValue() const = 0;
=======
	virtual unsigned long getValue() const = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation increments the IEventCounter.
	 */
	virtual void increment() = 0;

<<<<<<< HEAD
};
//end class IEventCounter

}//end namespace xolotlPerf
=======
}; //end class IEventCounter

} //end namespace xolotlPerf
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

#endif
