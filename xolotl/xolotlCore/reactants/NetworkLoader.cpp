// Includes
#include "NetworkLoader.h"

// Namespaces
using namespace xolotlCore;

<<<<<<< HEAD
NetworkLoader::NetworkLoader() : networkStream(nullptr), handlerRegistry(nullptr),
		fileName(""),
		dummyReactions(false) {}

NetworkLoader::NetworkLoader(std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		networkStream(nullptr), handlerRegistry(registry), fileName(""),
		dummyReactions(false) {}

NetworkLoader::NetworkLoader(const std::shared_ptr<std::istream> stream,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		networkStream(stream), handlerRegistry(registry), fileName(""),
		dummyReactions(false) {}

void NetworkLoader::setInputstream(
		const std::shared_ptr<std::istream> stream) {
=======
NetworkLoader::NetworkLoader() :
		networkStream(nullptr), handlerRegistry(nullptr), fileName(""), dummyReactions(
				false) {
}

NetworkLoader::NetworkLoader(
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		networkStream(nullptr), handlerRegistry(registry), fileName(""), dummyReactions(
				false) {
}

NetworkLoader::NetworkLoader(const std::shared_ptr<std::istream> stream,
		std::shared_ptr<xolotlPerf::IHandlerRegistry> registry) :
		networkStream(stream), handlerRegistry(registry), fileName(""), dummyReactions(
				false) {
}

void NetworkLoader::setInputstream(const std::shared_ptr<std::istream> stream) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	networkStream = stream;

	return;
}

<<<<<<< HEAD
void NetworkLoader::setFilename (const std::string& name) {
=======
void NetworkLoader::setFilename(const std::string& name) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	fileName = name;

	return;
}

<<<<<<< HEAD
std::string NetworkLoader::getFilename () const {
	return fileName;
}

void NetworkLoader::setDummyReactions () {
=======
std::string NetworkLoader::getFilename() const {
	return fileName;
}

void NetworkLoader::setDummyReactions() {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	dummyReactions = true;

	return;
}
