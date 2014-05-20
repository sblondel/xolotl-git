<<<<<<< HEAD
#define BOOST_TEST_MODULE Regression

#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/dummy/DummyHardwareCounter.h"
=======
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Regression

#include <boost/test/included/unit_test.hpp>
#include <DummyHardwareCounter.h>
#include <string>
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

using namespace std;
using namespace xolotlPerf;

<<<<<<< HEAD
const IHardwareCounter::SpecType test_hwCtrSpec =
		{ IHardwareCounter::Instructions, IHardwareCounter::Cycles,
				IHardwareCounter::FPOps, IHardwareCounter::FPInstructions,
				IHardwareCounter::L1CacheMisses,
				IHardwareCounter::L2CacheMisses,
				IHardwareCounter::L3CacheMisses,
				IHardwareCounter::BranchMispredictions };
=======
const std::vector<HardwareQuantities> test_hardwareQuantities = {L1_CACHE_MISS,L2_CACHE_MISS,L3_CACHE_MISS,
			BRANCH_MISPRED,TOTAL_CYCLES,TOTAL_INSTRUC,FLPT_INSTRUC};
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

/**
 * This suite is responsible for testing the DummyHardwareCounter.
 */
BOOST_AUTO_TEST_SUITE (DummyHardwareCounter_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

<<<<<<< HEAD
	DummyHardwareCounter tester("test", test_hwCtrSpec);
=======
	DummyHardwareCounter tester("test",test_hardwareQuantities);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

	BOOST_REQUIRE_EQUAL("unused", tester.getName());
}

BOOST_AUTO_TEST_CASE(check_getValues) {

<<<<<<< HEAD
	DummyHardwareCounter tester("test", test_hwCtrSpec);

	BOOST_TEST_MESSAGE(
			"\n" << "DummyHardwareCounter Message: \n" << "tester.getValues().size() = " << tester.getValues().size());

	BOOST_REQUIRE_EQUAL(0U, tester.getValues().size());

}

BOOST_AUTO_TEST_CASE(check_getSpecification) {

	DummyHardwareCounter tester("test", test_hwCtrSpec);

	BOOST_TEST_MESSAGE(
			"\n" << "DummyHardwareCounter Message: \n" << "tester.getSpecification().size() = " << tester.getSpecification().size());

	BOOST_REQUIRE_EQUAL(0U, tester.getSpecification().size());
=======
	DummyHardwareCounter tester("test",test_hardwareQuantities);

	BOOST_TEST_MESSAGE("\n" << "DummyHardwareCounter Message: \n"
							<< "tester.getValues().size() = " << tester.getValues().size());

	BOOST_REQUIRE_EQUAL(0, tester.getValues().size());

}

BOOST_AUTO_TEST_CASE(check_getHardwareQuantities) {

	DummyHardwareCounter tester("test",test_hardwareQuantities);

	BOOST_TEST_MESSAGE("\n" << "DummyHardwareCounter Message: \n"
							<< "tester.getHardwareQuantities().size() = " << tester.getHardwareQuantities().size());

	BOOST_REQUIRE_EQUAL(0, tester.getHardwareQuantities().size());
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

}

BOOST_AUTO_TEST_SUITE_END()

