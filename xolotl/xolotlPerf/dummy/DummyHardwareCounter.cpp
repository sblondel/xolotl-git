#include "DummyHardwareCounter.h"

<<<<<<< HEAD
<<<<<<< HEAD
namespace xolotlPerf {

IHardwareCounter::ValType DummyHardwareCounter::dummyVals;
IHardwareCounter::SpecType DummyHardwareCounter::dummySpec;

} // namespace xolotlPerf

=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
using namespace xolotlPerf;


std::vector<double> DummyHardwareCounter::getValues(void) const {
    return std::vector<double>();
}

std::vector<std::string> DummyHardwareCounter::getHardwareQuantities() const {

	return std::vector<std::string>();
}
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
