#ifndef IHARDWARECOUNTER_H
#define IHARDWARECOUNTER_H

#include "mpi.h"
#include <vector>
#include <limits.h>
#include "../xolotlCore/IIdentifiable.h"

using namespace std;

<<<<<<< HEAD
namespace xolotlPerf{
=======
namespace xolotlPerf {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * A counter that can sample hardware counter values.
 */
<<<<<<< HEAD
class IHardwareCounter : public virtual xolotlCore::IIdentifiable {

public:

    /// The types of hardware counters we can collect
    enum CounterSpec
    {
        Instructions,
        Cycles,
        FPOps,
        FPInstructions,
        L1CacheMisses,
        L2CacheMisses,
        L3CacheMisses,
        BranchMispredictions,
    };

    /// Type of an individual IHardwareCounter value.
    typedef long long CounterType;

    /// Type of the IHardwareCounter's collection of values.
    typedef std::vector<CounterType> ValType;

    /// Type of the IHardwareCounter's configuration
    typedef std::vector<CounterSpec> SpecType;


    /**
     * The MPI type to use when transferring a component of the ValType
     * when aggregating values.
     */
    static constexpr MPI_Datatype MPIValType = MPI_LONG_LONG_INT;


    /**
     * The minimum value possible for an individual counter.
     */
    static constexpr CounterType MinValue = 0;

    /**
     * The maximum value possible for an individual counter.
     */
    static constexpr CounterType MaxValue = LLONG_MAX;



=======
class IHardwareCounter: public virtual xolotlCore::IIdentifiable {

public:

	/// The types of hardware counters we can collect
	enum CounterSpec {
		Instructions,
		Cycles,
		FPOps,
		FPInstructions,
		L1CacheMisses,
		L2CacheMisses,
		L3CacheMisses,
		BranchMispredictions,
	};

	/// Type of an individual IHardwareCounter value.
	typedef long long CounterType;

	/// Type of the IHardwareCounter's collection of values.
	typedef std::vector<CounterType> ValType;

	/// Type of the IHardwareCounter's configuration
	typedef std::vector<CounterSpec> SpecType;

	/**
	 * The MPI type to use when transferring a component of the ValType
	 * when aggregating values.
	 */
	static constexpr MPI_Datatype MPIValType = MPI_LONG_LONG_INT;

	/**
	 * The minimum value possible for an individual counter.
	 */
	static constexpr CounterType MinValue = 0;

	/**
	 * The maximum value possible for an individual counter.
	 */
	static constexpr CounterType MaxValue = LLONG_MAX;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * Destroy th ecounter set.
	 */
<<<<<<< HEAD
	virtual ~IHardwareCounter() { }


    /**
     * Start collecting performance counter data.
     * Throws a xolotlPerf::runtime_error if already collecting.
     */
    virtual void start(void) = 0;


    /**
     * Stop collecting performance counter data.
     * Throws a xolotlPerf::runtime_error if not collecting.
     */
    virtual void stop(void) = 0;


    /**
     * Retrieve the values of the hardware counters that have been collected.
     * The values are only valid if the counter set is not currently counting.
     * @return The current values for our configured hardware counters.
     */
    virtual const ValType& getValues(void) const = 0;


    /**
     * Retrieve the hardware counters we monitor.
     * @return The collection of hardware counters we are configured to monitor.
     */
    virtual const SpecType& getSpecification(void) const = 0;


    /**
     * Retrieve the name of the given hardware counter.
     * @return The name of the given hardware counter.
     */
    virtual std::string getCounterName(IHardwareCounter::CounterSpec cs) const = 0;
=======
	virtual ~IHardwareCounter() {
	}

	/**
	 * Start collecting performance counter data.
	 * Throws a xolotlPerf::runtime_error if already collecting.
	 */
	virtual void start(void) = 0;

	/**
	 * Stop collecting performance counter data.
	 * Throws a xolotlPerf::runtime_error if not collecting.
	 */
	virtual void stop(void) = 0;

	/**
	 * Retrieve the values of the hardware counters that have been collected.
	 * The values are only valid if the counter set is not currently counting.
	 * @return The current values for our configured hardware counters.
	 */
	virtual const ValType& getValues(void) const = 0;

	/**
	 * Retrieve the hardware counters we monitor.
	 * @return The collection of hardware counters we are configured to monitor.
	 */
	virtual const SpecType& getSpecification(void) const = 0;

	/**
	 * Retrieve the name of the given hardware counter.
	 * @return The name of the given hardware counter.
	 */
	virtual std::string getCounterName(
			IHardwareCounter::CounterSpec cs) const = 0;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
};

}  //end namespace xolotlPerf

#endif
