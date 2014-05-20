#ifndef DUMMYHARDWARECOUNTER_H
#define DUMMYHARDWARECOUNTER_H

#include <string>
#include <vector>
#include <memory>
<<<<<<< HEAD
#include "xolotlCore/Identifiable.h"
#include "xolotlPerf/IHardwareCounter.h"

namespace xolotlPerf {
=======
#include "Identifiable.h"
#include "IHardwareCounter.h"
#include "HardwareQuantities.h"


namespace xolotlPerf{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

/**
 * The DummyHardwareCounter class is instantiated by the DummyHandlerRegistry class
 * and realizes the DummyHardwareCounter interface.
 */
<<<<<<< HEAD
class DummyHardwareCounter: public IHardwareCounter,
		public xolotlCore::Identifiable {
=======
class DummyHardwareCounter : public IHardwareCounter, public xolotlCore::Identifiable
{
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

private:

	/**
<<<<<<< HEAD
	 * An empty collection of values, used by getValues to avoid
	 * returning a reference to a temporary.
	 */
	static IHardwareCounter::ValType dummyVals;

	/**
	 * An empty HardwareCounter specification, used by getSpecification
	 * to avoid returning a reference to a temporary.
	 */
	static IHardwareCounter::SpecType dummySpec;

	/**
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	 * The default constructor is private because HardwareCounters
	 * must always be given a name and a vector of quantities to
	 * be monitored.
	 */
<<<<<<< HEAD
	DummyHardwareCounter() :
			xolotlCore::Identifiable("unused") {
	}
=======
	DummyHardwareCounter()
		: xolotlCore::Identifiable("unused")
	{ }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

public:

	/**
	 * DummyHardwareCounter constructor that takes the name and a
	 * list of the different quantities it should monitor.
	 *
	 * @param counterName The DummyHardwareCounter's name
	 * @param counterQuantities The vector of quantities the DummyHardwareCounter will monitor
	 */
<<<<<<< HEAD
	DummyHardwareCounter(const std::string& counterName,
			const IHardwareCounter::SpecType& ctrSpec) :
			xolotlCore::Identifiable("unused") {
	}
=======
	DummyHardwareCounter(std::string counterName,
			const std::vector<HardwareQuantities> &counterQuantities)
		: xolotlCore::Identifiable("unused")
	{ }
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * The destructor
	 */
<<<<<<< HEAD
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
};
=======
	virtual ~DummyHardwareCounter() { }

    /**
     * This operation returns a list of values of the, initially specified,
     * hardware quantities monitored by the DummyHardwareCounter.
     */
    std::vector<double> getValues(void) const;


	/**
	 * This operation returns the list of hardware
	 * quantities monitored by the GPTLHardwareCounter.
	 */
	virtual std::vector<std::string> getHardwareQuantities() const;

};  //end class DummyHardwareCounter
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

}  //end namespace xolotlPerf

#endif
