#define BOOST_TEST_MODULE Regression

#include <string>
#include <boost/test/included/unit_test.hpp>
#include "xolotlPerf/dummy/DummyHardwareCounter.h"

using namespace std;
using namespace xolotlPerf;

<<<<<<< HEAD

const IHardwareCounter::SpecType test_hwCtrSpec = 
{
    IHardwareCounter::Instructions,
    IHardwareCounter::Cycles,
    IHardwareCounter::FPOps,
    IHardwareCounter::FPInstructions,
    IHardwareCounter::L1CacheMisses,
    IHardwareCounter::L2CacheMisses,
    IHardwareCounter::L3CacheMisses,
    IHardwareCounter::BranchMispredictions
};



=======
const IHardwareCounter::SpecType test_hwCtrSpec =
		{ IHardwareCounter::Instructions, IHardwareCounter::Cycles,
				IHardwareCounter::FPOps, IHardwareCounter::FPInstructions,
				IHardwareCounter::L1CacheMisses,
				IHardwareCounter::L2CacheMisses,
				IHardwareCounter::L3CacheMisses,
				IHardwareCounter::BranchMispredictions };
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

/**
 * This suite is responsible for testing the DummyHardwareCounter.
 */
BOOST_AUTO_TEST_SUITE (DummyHardwareCounter_testSuite)

BOOST_AUTO_TEST_CASE(checkName) {

<<<<<<< HEAD
	DummyHardwareCounter tester("test",test_hwCtrSpec);
=======
	DummyHardwareCounter tester("test", test_hwCtrSpec);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	BOOST_REQUIRE_EQUAL("unused", tester.getName());
}

BOOST_AUTO_TEST_CASE(check_getValues) {

<<<<<<< HEAD
	DummyHardwareCounter tester("test",test_hwCtrSpec);

	BOOST_TEST_MESSAGE("\n" << "DummyHardwareCounter Message: \n"
							<< "tester.getValues().size() = " << tester.getValues().size());

	BOOST_REQUIRE_EQUAL(0, tester.getValues().size());
=======
	DummyHardwareCounter tester("test", test_hwCtrSpec);

	BOOST_TEST_MESSAGE(
			"\n" << "DummyHardwareCounter Message: \n" << "tester.getValues().size() = " << tester.getValues().size());

	BOOST_REQUIRE_EQUAL(0U, tester.getValues().size());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

}

BOOST_AUTO_TEST_CASE(check_getSpecification) {

<<<<<<< HEAD
	DummyHardwareCounter tester("test",test_hwCtrSpec);

	BOOST_TEST_MESSAGE("\n" << "DummyHardwareCounter Message: \n"
							<< "tester.getSpecification().size() = " << tester.getSpecification().size());

	BOOST_REQUIRE_EQUAL(0, tester.getSpecification().size());
=======
	DummyHardwareCounter tester("test", test_hwCtrSpec);

	BOOST_TEST_MESSAGE(
			"\n" << "DummyHardwareCounter Message: \n" << "tester.getSpecification().size() = " << tester.getSpecification().size());

	BOOST_REQUIRE_EQUAL(0U, tester.getSpecification().size());
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

}

BOOST_AUTO_TEST_SUITE_END()

