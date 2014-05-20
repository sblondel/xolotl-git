#ifndef IHANDLERREGISTRY_H
#define IHANDLERREGISTRY_H

// Includes
#include <string>
#include <vector>
#include <memory>
#include "ITimer.h"
#include "IEventCounter.h"
#include "IHardwareCounter.h"
<<<<<<< HEAD
#include "PerfObjStatistics.h"
=======
#include "HardwareQuantities.h"

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

namespace xolotlPerf {

/**
 * Factory for building performance data collection objects, such
 * as timers and counters.
 */
class IHandlerRegistry {

public:

<<<<<<< HEAD
	/// Possible types of performance handler registries.
	enum RegistryType {
		dummy,     //< Use stub classes that do not collect any performance data
		std,        //< Use the best available API.
		os,         //< Use operating system/runtime API.
		papi,       //< Use PAPI to collect performance data.
	};

	/**
	 * The destructor
	 */
	virtual ~IHandlerRegistry() {
	}
=======
	/**
	 * The destructor
	 */
	virtual ~IHandlerRegistry(){}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns the ITimer specified by the parameter.
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<ITimer> getTimer(const std::string& name) = 0;
=======
	virtual std::shared_ptr<ITimer> getTimer(std::string name) = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns the IEventCounter specified by the parameter.
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<IEventCounter> getEventCounter(
			const std::string& name) = 0;
=======
	virtual std::shared_ptr<IEventCounter> getEventCounter( std::string name) = 0;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	/**
	 * This operation returns the specified IHardwareCounter.
	 */
<<<<<<< HEAD
	virtual std::shared_ptr<IHardwareCounter> getHardwareCounter(
			const std::string& name,
			const IHardwareCounter::SpecType& ctrSpec) = 0;

	/**
	 * Collect statistics about any performance data collected by
	 * processes of the program.
	 *
	 * @param timerStats Map of timer statistics, keyed by timer name.
	 * @param counterStats Map of counter statistics, keyed by counter name.
	 * @param hwCounterStats Map of hardware counter statistics, keyed by IHardwareCounter name + ':' + hardware counter name.
	 *
	 */
	virtual void collectStatistics(PerfObjStatsMap<ITimer::ValType>& timerStats,
			PerfObjStatsMap<IEventCounter::ValType>& counterStats,
			PerfObjStatsMap<IHardwareCounter::CounterType>& hwCounterStats) = 0;

	/**
	 * Report performance data statistics to the given stream.
	 *
	 * @param os Stream on which to output statistics.
	 * @param timerStats Map of timer statistics, keyed by timer name.
	 * @param counterStats Map of counter statistics, keyed by counter name.
	 * @param hwCounterStats Map of hardware counter statistics, keyed by IHardwareCounter name + ':' + hardware counter name.
	 *
	 */
	virtual void reportStatistics(std::ostream& os,
			const PerfObjStatsMap<ITimer::ValType>& timerStats,
			const PerfObjStatsMap<IEventCounter::ValType>& counterStats,
			const PerfObjStatsMap<IHardwareCounter::CounterType>& hwCounterStats) const = 0;

};
=======
	virtual std::shared_ptr<IHardwareCounter> getHardwareCounter( std::string name,
			            std::vector<HardwareQuantities> quantities) = 0;

	/**
	 * This operation outputs the information gathered to the given
	 * output stream.
	 */
	virtual void dump(std::ostream& os) const = 0;

	/**
	 * This operation outputs the information gathered to the given
	 * output stream.
	 */
	virtual void dump(int rank) const = 0;

}; //end class IHandlerRegistry
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

} //end namespace xolotlPerf

#endif
