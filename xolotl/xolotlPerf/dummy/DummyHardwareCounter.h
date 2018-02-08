#ifndef DUMMYHARDWARECOUNTER_H
#define DUMMYHARDWARECOUNTER_H

#include <string>
#include <vector>
#include <memory>
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IHardwareCounter.h"

<<<<<<< HEAD

namespace xolotlPerf{
=======
namespace xolotlPerf {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * The DummyHardwareCounter class is instantiated by the DummyHandlerRegistry class
 * and realizes the DummyHardwareCounter interface.
 */
<<<<<<< HEAD
class DummyHardwareCounter : public IHardwareCounter, public xolotlCore::Identifiable
{

private:

    /**
     * An empty collection of values, used by getValues to avoid
     * returning a reference to a temporary.
     */
    static IHardwareCounter::ValType dummyVals;

    /**
     * An empty HardwareCounter specification, used by getSpecification 
     * to avoid returning a reference to a temporary.
     */
    static IHardwareCounter::SpecType dummySpec;

=======
class DummyHardwareCounter: public IHardwareCounter,
		public xolotlCore::Identifiable {

private:

	/**
	 * An empty collection of values, used by getValues to avoid
	 * returning a reference to a temporary.
	 */
	static IHardwareCounter::ValType dummyVals;

	/**
	 * An empty HardwareCounter specification, used by getSpecification
	 * to avoid returning a reference to a temporary.
	 */
	static IHardwareCounter::SpecType dummySpec;
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The default constructor is private because HardwareCounters
	 * must always be given a name and a vector of quantities to
	 * be monitored.
	 */
<<<<<<< HEAD
	DummyHardwareCounter()
		: xolotlCore::Identifiable("unused")
	{ }
=======
	DummyHardwareCounter() :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
	 * DummyHardwareCounter constructor that takes the name and a
	 * list of the different quantities it should monitor.
	 *
	 * @param counterName The DummyHardwareCounter's name
	 * @param counterQuantities The vector of quantities the DummyHardwareCounter will monitor
	 */
	DummyHardwareCounter(const std::string& counterName,
<<<<<<< HEAD
                            const IHardwareCounter::SpecType& ctrSpec)
		: xolotlCore::Identifiable("unused")
	{ }
=======
			const IHardwareCounter::SpecType& ctrSpec) :
			xolotlCore::Identifiable("unused") {
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The destructor
	 */
<<<<<<< HEAD
	virtual ~DummyHardwareCounter() { }


    /**
     * Start collecting performance counter data.
     * This class' implementation is a stub.
     */
    virtual void start(void)
    {
        // nothing to do - this is a stub
    }


    /**
     * Stop collecting performance counter data.
     * This class' implementation is a stub.
     */
    virtual void stop(void)
    {
        // nothing to do - this is a stub
    }


    /**
     * Retrieve the values of the hardware counters that have been collected.
     * This class' implementation is a stub.
     * @return An empty collection of values.
     */
    virtual const ValType& getValues(void) const
    {
        // nothing to do - this is a stub
        return dummyVals;
    }


    /**
     * Retrieve the hardware counters we monitor.
     * This class' implementation is a stub.
     * @return Any empty collection of specifications.
     */
    virtual const SpecType& getSpecification(void) const
    {
        return dummySpec;
    }


    /**
     * Retrieve the name of the given hardware counter.
     * This class' implementation is a stub.
     * @return An empty string.
     */
    virtual std::string getCounterName(IHardwareCounter::CounterSpec cs) const
    {
        return std::string();
    }
=======
	virtual ~DummyHardwareCounter() {
	}

	/**
	 * Start collecting performance counter data.
	 * This class' implementation is a stub.
	 */
	virtual void start(void) {
		// nothing to do - this is a stub
	}

	/**
	 * Stop collecting performance counter data.
	 * This class' implementation is a stub.
	 */
	virtual void stop(void) {
		// nothing to do - this is a stub
	}

	/**
	 * Retrieve the values of the hardware counters that have been collected.
	 * This class' implementation is a stub.
	 *
	 * @return An empty collection of values.
	 */
	virtual const ValType& getValues(void) const {
		// nothing to do - this is a stub
		return dummyVals;
	}

	/**
	 * Retrieve the hardware counters we monitor.
	 * This class' implementation is a stub.
	 *
	 * @return Any empty collection of specifications.
	 */
	virtual const SpecType& getSpecification(void) const {
		return dummySpec;
	}

	/**
	 * Retrieve the name of the given hardware counter.
	 * This class' implementation is a stub.
	 *
	 * @return An empty string.
	 */
	virtual std::string getCounterName(IHardwareCounter::CounterSpec cs) const {
		return std::string();
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
};

}  //end namespace xolotlPerf

#endif
