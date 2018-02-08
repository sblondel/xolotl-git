#include "IReactionHandlerFactory.h"
#include "PSIReactionHandlerFactory.h"
#include "NEReactionHandlerFactory.h"
<<<<<<< HEAD
=======
#include "FeReactionHandlerFactory.h"
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

namespace xolotlFactory {

static std::shared_ptr<IReactionHandlerFactory> theReactionFactory;

<<<<<<< HEAD
std::shared_ptr<IReactionHandlerFactory> IReactionHandlerFactory::createNetworkFactory(const std::string& problemType) {
	// PSI case
	if (problemType == "W100" || problemType == "W110" || problemType == "W111" || problemType == "W211" || problemType == "TRIDYN")
		theReactionFactory = std::make_shared<PSIReactionHandlerFactory>();
	// NE case
	else if (problemType == "Fuel") theReactionFactory = std::make_shared<NEReactionHandlerFactory>();
	// The type is not supported
	else {
		throw std::string(
				"\nThe problem type is not known: \"" + problemType
				+ "\"");
=======
std::shared_ptr<IReactionHandlerFactory> IReactionHandlerFactory::createNetworkFactory(
		const std::string& problemType) {
	// PSI case
	if (problemType == "W100" || problemType == "W110" || problemType == "W111"
			|| problemType == "W211" || problemType == "TRIDYN")
		theReactionFactory = std::make_shared<PSIReactionHandlerFactory>();
	// NE case
	else if (problemType == "Fuel")
		theReactionFactory = std::make_shared<NEReactionHandlerFactory>();
	// Fe case
	else if (problemType == "Fe")
		theReactionFactory = std::make_shared<FeReactionHandlerFactory>();
	// The type is not supported
	else {
		throw std::string(
				"\nThe problem type is not known: \"" + problemType + "\"");
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return theReactionFactory;
}

} // end namespace xolotlFactory
