#include <IMaterialFactory.h>
#include <W100MaterialFactory.h>
#include <W110MaterialFactory.h>
#include <W111MaterialFactory.h>
<<<<<<< HEAD
=======
#include <W211MaterialFactory.h>
#include <FuelMaterialFactory.h>
#include <TRIDYNMaterialFactory.h>
#include <WSRIMMaterialFactory.h>
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

namespace xolotlFactory {

static std::shared_ptr<IMaterialFactory> theMaterialFactory;

<<<<<<< HEAD
std::shared_ptr<IMaterialFactory> IMaterialFactory::createMaterialFactory(const std::string& materialType,
		int dimension) {
	// W100 case
	if (materialType == "W100") theMaterialFactory = std::make_shared<W100MaterialFactory>(dimension);
	// W110 case
	else if (materialType == "W110") theMaterialFactory = std::make_shared<W110MaterialFactory>(dimension);
	// W111 case
	else if (materialType == "W111") theMaterialFactory = std::make_shared<W111MaterialFactory>(dimension);
	// The type is not supported
	else {
		throw std::string(
				"\nThe material type is not known: \"" + materialType
				+ "\"");
	}
	return theMaterialFactory;
}

};  // end namespace xolotlFactory
=======
std::shared_ptr<IMaterialFactory> IMaterialFactory::createMaterialFactory(
		const std::string& materialType, int dimension) {
	// W100 case
	if (materialType == "W100")
		theMaterialFactory = std::make_shared<W100MaterialFactory>(dimension);
	// W110 case
	else if (materialType == "W110")
		theMaterialFactory = std::make_shared<W110MaterialFactory>(dimension);
	// W111 case
	else if (materialType == "W111")
		theMaterialFactory = std::make_shared<W111MaterialFactory>(dimension);
	// W211 case
	else if (materialType == "W211")
		theMaterialFactory = std::make_shared<W211MaterialFactory>(dimension);
	// Fuel case
	else if (materialType == "Fuel")
		theMaterialFactory = std::make_shared<FuelMaterialFactory>(dimension);
	// TRIDYN case
	else if (materialType == "TRIDYN")
		theMaterialFactory = std::make_shared<TRIDYNMaterialFactory>(dimension);
	// WSRIM case
	else if (materialType == "WSRIM")
		theMaterialFactory = std::make_shared<WSRIMMaterialFactory>(dimension);
	// The type is not supported
	else {
		throw std::string(
				"\nThe material type is not known: \"" + materialType + "\"");
	}

	return theMaterialFactory;
}

} // end namespace xolotlFactory
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
