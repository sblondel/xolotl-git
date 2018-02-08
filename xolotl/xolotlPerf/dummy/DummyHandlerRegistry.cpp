#include "DummyHandlerRegistry.h"

<<<<<<< HEAD
namespace xolotlPerf
{

// Obtain a Timer by name.
std::shared_ptr<ITimer>
DummyHandlerRegistry::getTimer( const std::string& name )
{
    // TODO is there a need for us to retain access to this Timer?
    // TODO do we need to check whether client has already created
    // an object with this name and return that object?
    return std::make_shared<DummyTimer>( name );
}

// Obtain an EventCounter by name.
std::shared_ptr<IEventCounter>
DummyHandlerRegistry::getEventCounter( const std::string& name )
{
    // TODO is there a need for us to retain access to this Timer?
    // TODO do we need to check whether client has already created
    // an object with this name and return that object?
    return std::make_shared<DummyEventCounter>( name );
=======
namespace xolotlPerf {

// Obtain a Timer by name.
std::shared_ptr<ITimer> DummyHandlerRegistry::getTimer(
		const std::string& name) {
	// TODO is there a need for us to retain access to this Timer?
	// TODO do we need to check whether client has already created
	// an object with this name and return that object?
	return std::make_shared < DummyTimer > (name);
}

// Obtain an EventCounter by name.
std::shared_ptr<IEventCounter> DummyHandlerRegistry::getEventCounter(
		const std::string& name) {
	// TODO is there a need for us to retain access to this Timer?
	// TODO do we need to check whether client has already created
	// an object with this name and return that object?
	return std::make_shared < DummyEventCounter > (name);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}

// Obtain a HardwareCounter object by name and by the
// counter data it collects.
<<<<<<< HEAD
std::shared_ptr<IHardwareCounter>
DummyHandlerRegistry::getHardwareCounter( const std::string& name,
                                        const IHardwareCounter::SpecType& ctrSpec )
{
    // TODO is there a need for us to retain access to this Timer?
    // TODO do we need to check whether client has already created
    // an object with this name and return that object?
    return std::make_shared<DummyHardwareCounter>( name, ctrSpec );
}

void 
DummyHandlerRegistry::collectStatistics( PerfObjStatsMap<ITimer::ValType>& timerStats,
                    PerfObjStatsMap<IEventCounter::ValType>& counterStats,
                    PerfObjStatsMap<IHardwareCounter::CounterType>& hwCounterStats )
{
    // do nothing
}


void 
DummyHandlerRegistry::reportStatistics( std::ostream& os, 
                    const PerfObjStatsMap<ITimer::ValType>& timerStats,
                    const PerfObjStatsMap<IEventCounter::ValType>& counterStats,
                    const PerfObjStatsMap<IHardwareCounter::CounterType>& hwCounterStats ) const
{
    // do nothing
}



};  // namespace xolotlPerf
=======
std::shared_ptr<IHardwareCounter> DummyHandlerRegistry::getHardwareCounter(
		const std::string& name, const IHardwareCounter::SpecType& ctrSpec) {
	// TODO is there a need for us to retain access to this Timer?
	// TODO do we need to check whether client has already created
	// an object with this name and return that object?
	return std::make_shared < DummyHardwareCounter > (name, ctrSpec);
}

void DummyHandlerRegistry::collectStatistics(
		PerfObjStatsMap<ITimer::ValType>&,
		PerfObjStatsMap<IEventCounter::ValType>&,
		PerfObjStatsMap<IHardwareCounter::CounterType>&) {
	// do nothing
	return;
}

void DummyHandlerRegistry::reportStatistics(std::ostream&,
		const PerfObjStatsMap<ITimer::ValType>&,
		const PerfObjStatsMap<IEventCounter::ValType>&,
		const PerfObjStatsMap<IHardwareCounter::CounterType>&) const {
	// do nothing
	return;
}

} // namespace xolotlPerf
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

