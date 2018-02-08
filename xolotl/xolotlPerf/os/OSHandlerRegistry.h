#ifndef OSHANDLERREGISTRY_H
#define OSHANDLERREGISTRY_H

#include "xolotlPerf/standard/StdHandlerRegistry.h"

<<<<<<< HEAD

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
namespace xolotlPerf {

/**
 * Factory for building performance data collection objects that 
 * use an OS/runtime timer API.  No hardware performance counters
 * are available.
 */
<<<<<<< HEAD
class OSHandlerRegistry : public StdHandlerRegistry
{
public:

    /// Construct a handler registry.
    OSHandlerRegistry( void ) { }

    /// Destroy the handler registry.
    virtual ~OSHandlerRegistry( void ) { }


    /**
     * Look up and return a named timer.
     * Create the timer if it does not already exist.
     *
     * @param name The object's name.
     * @return The object with the given name.
     */
	virtual std::shared_ptr<ITimer> getTimer(const std::string& name);


    /**
     * Look up and return a hardware counter set in the current scope.
     * Create the event counter set if it does not already exist.
     *
     * @param name The object's name.
     * @return The object with the given name.
     */
	virtual std::shared_ptr<IHardwareCounter> getHardwareCounter( const std::string& name,
                        const IHardwareCounter::SpecType& ctrSpec );
=======
class OSHandlerRegistry: public StdHandlerRegistry {
public:

	/// Construct a handler registry.
	OSHandlerRegistry(void) {
	}

	/// Destroy the handler registry.
	virtual ~OSHandlerRegistry(void) {
	}

	/**
	 * Look up and return a named timer.
	 * Create the timer if it does not already exist.
	 *
	 * @param name The object's name.
	 * @return The object with the given name.
	 */
	virtual std::shared_ptr<ITimer> getTimer(const std::string& name);

	/**
	 * Look up and return a hardware counter set in the current scope.
	 * Create the event counter set if it does not already exist.
	 *
	 * @param name The object's name.
	 * @return The object with the given name.
	 */
	virtual std::shared_ptr<IHardwareCounter> getHardwareCounter(
			const std::string& name, const IHardwareCounter::SpecType& ctrSpec);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
};

} // namespace xolotlPerf

#endif // OSHandlerRegistry
