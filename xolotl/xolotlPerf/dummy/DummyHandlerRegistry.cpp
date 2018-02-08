#include "DummyHandlerRegistry.h"

<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
namespace xolotlPerf
{

// Obtain a Timer by name.
std::shared_ptr<ITimer>
DummyHandlerRegistry::getTimer( std::string name )
{
    // TODO is there a need for us to retain access to this Timer?
    // TODO do we need to check whether client has already created
    // an object with this name and return that object?
    return std::make_shared<DummyTimer>( name );
}


// Obtain an EventCounter by name.
std::shared_ptr<IEventCounter>
DummyHandlerRegistry::getEventCounter( std::string name )
{
    // TODO is there a need for us to retain access to this Timer?
    // TODO do we need to check whether client has already created
    // an object with this name and return that object?
    return std::make_shared<DummyEventCounter>( name );
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}

// Obtain a HardwareCounter object by name and by the
// counter data it collects.
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
std::shared_ptr<IHardwareCounter>
DummyHandlerRegistry::getHardwareCounter( std::string name, 
                                        std::vector<HardwareQuantities> hwq )
{
    // TODO is there a need for us to retain access to this Timer?
    // TODO do we need to check whether client has already created
    // an object with this name and return that object?
    return std::make_shared<DummyHardwareCounter>( name, hwq );
}

// Output any collected performance data to the given output stream.
void DummyHandlerRegistry::dump( std::ostream& /* os */ ) const
{
    // do nothing
}

void DummyHandlerRegistry::dump( int rank) const
{
    // do nothing
}

};  // end namespace xolotlPerf
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

