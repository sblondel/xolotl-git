#include "DummyHardwareCounter.h"

<<<<<<< HEAD
namespace xolotlPerf {

IHardwareCounter::ValType DummyHardwareCounter::dummyVals;
IHardwareCounter::SpecType DummyHardwareCounter::dummySpec;

} // namespace xolotlPerf

=======
using namespace xolotlPerf;


std::vector<double> DummyHardwareCounter::getValues(void) const {
    return std::vector<double>();
}

std::vector<std::string> DummyHardwareCounter::getHardwareQuantities() const {

	return std::vector<std::string>();
}
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
