// Includes
#include <TrapMutationHandler.h>
#include <MathUtils.h>
#include <iostream>
#include <algorithm>

namespace xolotlCore {

<<<<<<< HEAD
void TrapMutationHandler::initialize(IReactionNetwork *network,
=======
void TrapMutationHandler::initialize(const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		std::vector<double> grid, int ny, double hy, int nz, double hz) {
	// Add the needed reaction (dissociation) connectivity
	// Each (He_i)(V) cluster and I clusters are connected to He_i

<<<<<<< HEAD
	// Get all the He clusters from the network
	auto heClusters = network->getAll(heType);
	// Get all the HeV bubbles from the network
	auto bubbles = network->getAll(heVType);
	// Get the single interstitial cluster
	auto singleInterstitial = (PSICluster *) network->get(iType, 1);
	// Get the double interstitial cluster
	auto doubleInterstitial = (PSICluster *) network->get(iType, 2);
	// Get the triple interstitial cluster
	auto tripleInterstitial = (PSICluster *) network->get(iType, 3);
=======
	// Get the single interstitial cluster
	auto singleInterstitial = (PSICluster *) network.get(Species::I, 1);
	// Get the double interstitial cluster
	auto doubleInterstitial = (PSICluster *) network.get(Species::I, 2);
	// Get the triple interstitial cluster
	auto tripleInterstitial = (PSICluster *) network.get(Species::I, 3);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// If the I clusters are not in the network,
	// there is no trap-mutation
	if (!singleInterstitial || !doubleInterstitial || !tripleInterstitial) {
		// Clear the vector of HeV indices created by He undergoing trap-mutation
		// at each grid point
<<<<<<< HEAD
		indexVector.clear();
=======
		tmBubbles.clear();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Change the value of ny and nz in 1D and 2D so that the same loop
		// works in every case
		if (nz == 0)
			nz = 1;
		if (ny == 0)
			ny = 1;

		// Loop on the grid points in the Z direction
<<<<<<< HEAD
		for (int k = 0; k < nz; k++) {
			// Create the temporary 2D vector
			std::vector<std::vector<std::vector<int> > > temp2DVector;
			// Loop on the grid points in the Y direction
			for (int j = 0; j < ny; j++) {
				// Create the temporary 1D vector
				std::vector<std::vector<int> > temp1DVector;
				// Loop on the grid points in the depth direction
				for (int i = 0; i < grid.size() - 2; i++) {
					// Create the list (vector) of indices at this grid point
					std::vector<int> indices;
					// And give it empty to the 1D vector
					temp1DVector.push_back(indices);
				}

				// Give the 1D vector to the 2D vector
				temp2DVector.push_back(temp1DVector);
			}

			// Give the 2D vector to the final vector
			indexVector.push_back(temp2DVector);
=======
		// TODO even with the reserve ops, this might involve lots of
		// separate memory allocations.
		tmBubbles.reserve(nz);
		for (int k = 0; k < nz; k++) {
			// Create the temporary 2D vector
			ReactantRefVector2D temp2DVector;

			// Loop on the grid points in the Y direction
			temp2DVector.reserve(ny);
			for (int j = 0; j < ny; j++) {
				// Create the temporary 1D vector
				ReactantRefVector1D temp1DVector;

				// Loop on the grid points in the depth direction
				temp1DVector.reserve(grid.size() - 2);
				for (int i = 0; i < grid.size() - 2; i++) {
					// Indicate no bubbles at this grid point.
					temp1DVector.emplace_back();
				}

				// Give the 1D vector to the 2D vector
				temp2DVector.emplace_back(temp1DVector);
			}

			// Give the 2D vector to the final vector
			tmBubbles.emplace_back(temp2DVector);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
		// Inform the user
		std::cout << "The modified trap-mutation won't happen because "
				"the interstitial clusters are missing." << std::endl;

		return;
	}

	// Loop on the He clusters
<<<<<<< HEAD
	for (int i = 0; i < heClusters.size(); i++) {
		// Get the cluster and its size
		auto cluster = (PSICluster *) heClusters[i];
		int heSize = cluster->getSize();

		// The helium cluster is connected to itself
		cluster->setDissociationConnectivity(cluster->getId());

		// The single and double interstitial clusters are connected to He
		singleInterstitial->setDissociationConnectivity(cluster->getId());
		doubleInterstitial->setDissociationConnectivity(cluster->getId());
		tripleInterstitial->setDissociationConnectivity(cluster->getId());

		// Loop on the bubbles
		for (int j = 0; j < bubbles.size(); j++) {
			// Get the bubble and its composition
			auto bubble = (PSICluster *) bubbles[j];
			auto comp = bubble->getComposition();

			// We are only interested in bubbles with one, two, or three vacancies
			if (comp[vType] > 3)
				continue;

			// Connect with He if the number of helium in the bubble is the same
			if (comp[heType] == heSize) {
				bubble->setDissociationConnectivity(cluster->getId());
=======
	for (const auto& heMapItem : network.getAll(ReactantType::He)) {

		// Get the cluster and its size
		auto& cluster = static_cast<PSICluster&>(*(heMapItem.second));
		int heSize = cluster.getSize();

		// The helium cluster is connected to itself
		cluster.setDissociationConnectivity(cluster.getId());

		// The single and double interstitial clusters are connected to He
		singleInterstitial->setDissociationConnectivity(cluster.getId());
		doubleInterstitial->setDissociationConnectivity(cluster.getId());
		tripleInterstitial->setDissociationConnectivity(cluster.getId());

		// Loop on the bubbles
		for (const auto& hevMapItem : network.getAll(ReactantType::HeV)) {

			// Get the bubble and its composition
			auto& bubble = static_cast<PSICluster&>(*(hevMapItem.second));
			auto& comp = bubble.getComposition();

			// We are only interested in bubbles with one, two, or three vacancies
			if (comp[toCompIdx(Species::V)] > 3)
				continue;

			// Connect with He if the number of helium in the bubble is the same
			if (comp[toCompIdx(Species::He)] == heSize) {
				bubble.setDissociationConnectivity(cluster.getId());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			}
		}
	}

	// This method fills two vectors to define the modified trap-mutation: for the first one,
	// the first value corresponds to the depth at which the He1 cluster undergo trap-mutation
	// (if the value is negative it means that it doesn't TM), the second value correspond
	// to He2, etc.; the second vector gives the size of the vacancies into which He
	// trap-mutates. Information about desorption is also initialized here.
<<<<<<< HEAD
	initializeDepthSize(network->getTemperature());
=======
	initializeDepthSize(network.getTemperature());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Update the bubble bursting rate
	updateTrapMutationRate(network);

	return;
}

void TrapMutationHandler::initializeIndex1D(int surfacePos,
<<<<<<< HEAD
		IReactionNetwork *network,
=======
		const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid) {
	// Clear the vector of HeV indices created by He undergoing trap-mutation
	// at each grid point
<<<<<<< HEAD
	indexVector.clear();

	// Get all the He clusters from the network
	auto heClusters = network->getAll(heType);
	// Get all the HeV bubbles from the network
	auto bubbles = network->getAll(heVType);
	// No GB trap mutation handler in 1D for now

	// Create the temporary 2D vector
	std::vector<std::vector<std::vector<int> > > temp2DVector;
	// Create the temporary 1D vector
	std::vector<std::vector<int> > temp1DVector;

	// Loop on the grid points in the depth direction
	for (int i = 0; i < grid.size() - 2; i++) {
		// Create the list (vector) of indices at this grid point
		std::vector<int> indices;

		// If we are on the left side of the surface there is no
		// modified trap-mutation
		if (i <= surfacePos) {
			temp1DVector.push_back(indices);
=======
	tmBubbles.clear();

	// No GB trap mutation handler in 1D for now

	// Create the temporary 2D vector
	ReactantRefVector2D temp2DVector;
	// Create the temporary 1D vector
	ReactantRefVector1D temp1DVector;

	// Loop on the grid points in the depth direction
	for (int i = 0; i < grid.size() - 2; i++) {
		// If we are on the left side of the surface there is no
		// modified trap-mutation
		if (i <= surfacePos) {
			temp1DVector.emplace_back();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			continue;
		}

		// Get the depth
<<<<<<< HEAD
		double depth = grid[i+1] - grid[surfacePos+1];
		double previousDepth = grid[i] - grid[surfacePos+1];

		// Loop on the depth vector
=======
		double depth = grid[i + 1] - grid[surfacePos + 1];
		double previousDepth = grid[i] - grid[surfacePos + 1];

		// Loop on the depth vector
		std::vector<std::reference_wrapper<IReactant> > indices;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		for (int l = 0; l < depthVec.size(); l++) {
			// Check if a helium cluster undergo TM at this depth
			if (std::fabs(depth - depthVec[l]) < 0.01
					|| (depthVec[l] - 0.01 < depth
							&& depthVec[l] - 0.01 > previousDepth)) {
				// Add the bubble of size l+1 to the indices
				// Loop on the bubbles
<<<<<<< HEAD
				for (int m = 0; m < bubbles.size(); m++) {
					// Get the bubble and its composition
					auto bubble = (PSICluster *) bubbles[m];
					auto comp = bubble->getComposition();
					// Get the correct bubble
					if (comp[heType] == l + 1 && comp[vType] == sizeVec[l]) {
						// Add this bubble to the indices
						indices.push_back(m);
=======
				for (auto const& heVMapItem : network.getAll(ReactantType::HeV)) {
					// Get the bubble and its composition
					auto& bubble =
							static_cast<PSICluster&>(*(heVMapItem.second));
					auto const& comp = bubble.getComposition();
					// Get the correct bubble
					if (comp[toCompIdx(Species::He)] == l + 1
							&& comp[toCompIdx(Species::V)] == sizeVec[l]) {
						// Add this bubble to the indices
						indices.emplace_back(bubble);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					}
				}
			}
		}

		// Add indices to the index vector
<<<<<<< HEAD
		temp1DVector.push_back(indices);
	}

	// Give the 1D vector to the 2D vector
	temp2DVector.push_back(temp1DVector);

	// Give the 2D vector to the final vector
	indexVector.push_back(temp2DVector);
=======
		temp1DVector.emplace_back(indices);
	}

	// Give the 1D vector to the 2D vector
	temp2DVector.emplace_back(temp1DVector);

	// Give the 2D vector to the final vector
	tmBubbles.emplace_back(temp2DVector);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void TrapMutationHandler::initializeIndex2D(std::vector<int> surfacePos,
<<<<<<< HEAD
		IReactionNetwork *network,
=======
		const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid, int ny, double hy) {
	// Clear the vector of HeV indices created by He undergoing trap-mutation
	// at each grid point
<<<<<<< HEAD
	indexVector.clear();

	// Get all the He clusters from the network
	auto heClusters = network->getAll(heType);
	// Get all the HeV bubbles from the network
	auto bubbles = network->getAll(heVType);
=======
	tmBubbles.clear();

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Create a Sigma 3 trap mutation handler because it is the
	// only one available right now
	auto sigma3Handler = new Sigma3TrapMutationHandler();
	auto sigma3DistanceVec = sigma3Handler->getDistanceVector();
	auto sigma3SizeVec = sigma3Handler->getSizeVector();

	// Create the temporary 2D vector
<<<<<<< HEAD
	std::vector<std::vector<std::vector<int> > > temp2DVector;
	// Loop on the grid points in the Y direction
	for (int j = 0; j < ny; j++) {
		// Create the temporary 1D vector
		std::vector<std::vector<int> > temp1DVector;
		// Loop on the grid points in the depth direction
		for (int i = 0; i < grid.size() - 2; i++) {
			// Create the list (vector) of indices at this grid point
			std::vector<int> indices;
=======
	ReactantRefVector2D temp2DVector;

	// Loop on the grid points in the Y direction
	temp2DVector.reserve(ny);
	for (int j = 0; j < ny; j++) {

		// Create the temporary 1D vector
		ReactantRefVector1D temp1DVector;

		// Loop on the grid points in the depth direction
		for (int i = 0; i < grid.size() - 2; i++) {
			// Create the list (vector) of indices at this grid point
			std::vector<std::reference_wrapper<IReactant> > indices;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// If we are on the left side of the surface there is no
			// modified trap-mutation
			if (i <= surfacePos[j]) {
				temp1DVector.push_back(indices);
				continue;
			}

			// Get the depth
<<<<<<< HEAD
			double depth = grid[i+1] - grid[surfacePos[j]+1];
			double previousDepth = grid[i] - grid[surfacePos[j]+1];
=======
			double depth = grid[i + 1] - grid[surfacePos[j] + 1];
			double previousDepth = grid[i] - grid[surfacePos[j] + 1];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Loop on the depth vector
			for (int l = 0; l < depthVec.size(); l++) {
				// Check if a helium cluster undergo TM at this depth
				if (std::fabs(depth - depthVec[l]) < 0.01
						|| (depthVec[l] - 0.01 < depth
								&& depthVec[l] - 0.01 > previousDepth)) {
					// Add the bubble of size l+1 to the indices
					// Loop on the bubbles
<<<<<<< HEAD
					for (int m = 0; m < bubbles.size(); m++) {
						// Get the bubble and its composition
						auto bubble = (PSICluster *) bubbles[m];
						auto comp = bubble->getComposition();
						// Get the correct bubble
						if (comp[heType] == l + 1
								&& comp[vType] == sizeVec[l]) {
							// Add this bubble to the indices
							indices.push_back(m);
=======
					for (auto const& heVMapItem : network.getAll(
							ReactantType::HeV)) {
						// Get the bubble and its composition
						auto& bubble =
								static_cast<PSICluster&>(*(heVMapItem.second));
						auto const& comp = bubble.getComposition();
						// Get the correct bubble
						if (comp[toCompIdx(Species::He)] == l + 1
								&& comp[toCompIdx(Species::V)] == sizeVec[l]) {
							// Add this bubble to the indices
							indices.emplace_back(bubble);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
						}
					}
				}
			}

			// Get the Y position
			double yPos = (double) j * hy;
			// Loop on the GB advection handlers
			for (int n = 1; n < advectionHandlers.size(); n++) {
				// Get the location of the GB
				double location = advectionHandlers[n]->getLocation();
				// Get the current distance from the GB
				double distance = fabs(yPos - location);
				// Loop on the sigma 3 distance vector
				for (int l = 0; l < sigma3DistanceVec.size(); l++) {
					// Check if a helium cluster undergo TM at this depth
					if (std::fabs(distance - sigma3DistanceVec[l]) < 0.01) {
						// Add the bubble of size l+1 to the indices
						// Loop on the bubbles
<<<<<<< HEAD
						for (int m = 0; m < bubbles.size(); m++) {
							// Get the bubble and its composition
							auto bubble = (PSICluster *) bubbles[m];
							auto comp = bubble->getComposition();
							// Get the correct bubble
							if (comp[heType] == l + 1
									&& comp[vType] == sigma3SizeVec[l]) {
								// Check if this bubble is already in the indices
								if (std::find(indices.begin(), indices.end(), m)
										== indices.end()) {
									// Add this bubble to the indices
									indices.push_back(m);
=======
						for (auto const& heVMapItem : network.getAll(
								ReactantType::HeV)) {
							// Get the bubble and its composition
							auto& bubble =
									static_cast<PSICluster&>(*(heVMapItem.second));
							auto const& comp = bubble.getComposition();
							// Get the correct bubble
							if (comp[toCompIdx(Species::He)] == l + 1
									&& comp[toCompIdx(Species::V)]
											== sigma3SizeVec[l]) {
								// Check if this bubble is already 
								// associated with this grid point.
								auto biter =
										std::find_if(indices.begin(),
												indices.end(),
												[&bubble](const IReactant& testReactant) {
													return testReactant.getId() == bubble.getId();
												});
								if (biter == indices.end()) {
									// Add this bubble to the indices
									indices.emplace_back(bubble);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
								}
							}
						}
					}
				}
			}

			// Add indices to the index vector
			temp1DVector.push_back(indices);
		}

		// Give the 1D vector to the 2D vector
		temp2DVector.push_back(temp1DVector);
	}

	// Give the 2D vector to the final vector
<<<<<<< HEAD
	indexVector.push_back(temp2DVector);
=======
	tmBubbles.push_back(temp2DVector);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Clear the memory
	delete sigma3Handler;

	return;
}

void TrapMutationHandler::initializeIndex3D(
<<<<<<< HEAD
		std::vector<std::vector<int> > surfacePos, IReactionNetwork *network,
=======
		std::vector<std::vector<int> > surfacePos,
		const IReactionNetwork& network,
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		std::vector<IAdvectionHandler *> advectionHandlers,
		std::vector<double> grid, int ny, double hy, int nz, double hz) {
	// Clear the vector of HeV indices created by He undergoing trap-mutation
	// at each grid point
<<<<<<< HEAD
	indexVector.clear();

	// Get all the He clusters from the network
	auto heClusters = network->getAll(heType);
	// Get all the HeV bubbles from the network
	auto bubbles = network->getAll(heVType);
=======
	tmBubbles.clear();

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// Create a Sigma 3 trap mutation handler because it is the
	// only one available right now
	auto sigma3Handler = new Sigma3TrapMutationHandler();
	auto sigma3DistanceVec = sigma3Handler->getDistanceVector();
	auto sigma3SizeVec = sigma3Handler->getSizeVector();

	// Loop on the grid points in the Z direction
<<<<<<< HEAD
	for (int k = 0; k < nz; k++) {
		// Create the temporary 2D vector
		std::vector<std::vector<std::vector<int> > > temp2DVector;
		// Loop on the grid points in the Y direction
		for (int j = 0; j < ny; j++) {
			// Create the temporary 1D vector
			std::vector<std::vector<int> > temp1DVector;
			// Loop on the grid points in the depth direction
			for (int i = 0; i < grid.size() - 2; i++) {
				// Create the list (vector) of indices at this grid point
				std::vector<int> indices;
=======
	tmBubbles.reserve(nz);
	for (int k = 0; k < nz; k++) {

		// Create the temporary 2D vector
		ReactantRefVector2D temp2DVector;

		// Loop on the grid points in the Y direction
		temp2DVector.reserve(ny);
		for (int j = 0; j < ny; j++) {
			// Create the temporary 1D vector
			ReactantRefVector1D temp1DVector;

			// Loop on the grid points in the depth direction
			for (int i = 0; i < grid.size() - 2; i++) {
				// Create the list (vector) of indices at this grid point
				std::vector<std::reference_wrapper<IReactant> > indices;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

				// If we are on the left side of the surface there is no
				// modified trap-mutation
				if (i <= surfacePos[j][k]) {
<<<<<<< HEAD
					temp1DVector.push_back(indices);
=======
					temp1DVector.emplace_back(indices);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
					continue;
				}

				// Get the depth
<<<<<<< HEAD
				double depth = grid[i+1] - grid[surfacePos[j][k]+1];
				double previousDepth = grid[i] - grid[surfacePos[j][k]+1];
=======
				double depth = grid[i + 1] - grid[surfacePos[j][k] + 1];
				double previousDepth = grid[i] - grid[surfacePos[j][k] + 1];
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

				// Loop on the depth vector
				for (int l = 0; l < depthVec.size(); l++) {
					// Check if a helium cluster undergo TM at this depth
					if (std::fabs(depth - depthVec[l]) < 0.01
							|| (depthVec[l] - 0.01 < depth
									&& depthVec[l] - 0.01 > previousDepth)) {
						// Add the bubble of size l+1 to the indices
						// Loop on the bubbles
<<<<<<< HEAD
						for (int m = 0; m < bubbles.size(); m++) {
							// Get the bubble and its composition
							auto bubble = (PSICluster *) bubbles[m];
							auto comp = bubble->getComposition();
							// Get the correct bubble
							if (comp[heType] == l + 1
									&& comp[vType] == sizeVec[l]) {
								// Add this bubble to the indices
								indices.push_back(m);
=======
						for (auto const& heVMapItem : network.getAll(
								ReactantType::HeV)) {
							// Get the bubble and its composition
							auto& bubble =
									static_cast<PSICluster&>(*(heVMapItem.second));
							auto const& comp = bubble.getComposition();
							// Get the correct bubble
							if (comp[toCompIdx(Species::He)] == l + 1
									&& comp[toCompIdx(Species::V)]
											== sizeVec[l]) {
								// Add this bubble to the indices
								indices.emplace_back(bubble);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
							}
						}
					}
				}

				// Get the Y position
				double yPos = (double) j * hy;
				// Loop on the GB advection handlers
				for (int n = 1; n < advectionHandlers.size(); n++) {
					// Get the location of the GB
					double location = advectionHandlers[n]->getLocation();
					// Get the current distance from the GB
					double distance = fabs(yPos - location);

					// Loop on the sigma 3 distance vector
					for (int l = 0; l < sigma3DistanceVec.size(); l++) {
						// Check if a helium cluster undergo TM at this depth
						if (std::fabs(distance - sigma3DistanceVec[l]) < 0.01) {
							// Add the bubble of size l+1 to the indices
							// Loop on the bubbles
<<<<<<< HEAD
							for (int m = 0; m < bubbles.size(); m++) {
								// Get the bubble and its composition
								auto bubble = (PSICluster *) bubbles[m];
								auto comp = bubble->getComposition();
								// Get the correct bubble
								if (comp[heType] == l + 1
										&& comp[vType] == sigma3SizeVec[l]) {
									// Check if this bubble is already in the indices
									if (std::find(indices.begin(),
											indices.end(), m)
											== indices.end()) {
										// Add this bubble to the indices
										indices.push_back(m);
=======
							for (auto const& heVMapItem : network.getAll(
									ReactantType::HeV)) {
								// Get the bubble and its composition
								auto& bubble =
										static_cast<PSICluster&>(*(heVMapItem.second));
								auto const& comp = bubble.getComposition();
								// Get the correct bubble
								if (comp[toCompIdx(Species::He)] == l + 1
										&& comp[toCompIdx(Species::V)]
												== sigma3SizeVec[l]) {
									// Check if this bubble is already
									// associated with this grid point.
									auto biter =
											std::find_if(indices.begin(),
													indices.end(),
													[&bubble](const IReactant& testReactant) {
														return testReactant.getId() == bubble.getId();
													});
									if (biter == indices.end()) {
										// Add this bubble to the indices
										indices.emplace_back(bubble);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
									}
								}
							}
						}
					}
				}

				// Add indices to the index vector
				temp1DVector.push_back(indices);
			}

			// Give the 1D vector to the 2D vector
			temp2DVector.push_back(temp1DVector);
		}

		// Give the 2D vector to the final vector
<<<<<<< HEAD
		indexVector.push_back(temp2DVector);
=======
		tmBubbles.push_back(temp2DVector);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	// Clear the memory
	delete sigma3Handler;

	return;
}

<<<<<<< HEAD
void TrapMutationHandler::updateTrapMutationRate(IReactionNetwork *network) {
	// Multiply the biggest rate in the network by 1000.0
	// so that trap-mutation overcomes any other reaction
	kMutation = 1000.0 * network->getBiggestRate();
=======
void TrapMutationHandler::updateTrapMutationRate(
		const IReactionNetwork& network) {
	// Multiply the biggest rate in the network by 1000.0
	// so that trap-mutation overcomes any other reaction
	kMutation = 1000.0 * network.getBiggestRate();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	return;
}

void TrapMutationHandler::setAttenuation(bool isAttenuation) {
	attenuation = isAttenuation;

	return;
}

void TrapMutationHandler::updateDisappearingRate(double conc) {
	// Set the rate to have an exponential decrease
	if (attenuation)
		kDis = exp(-4.0 * conc);

	return;
}

<<<<<<< HEAD
void TrapMutationHandler::computeTrapMutation(IReactionNetwork *network,
		double *concOffset, double *updatedConcOffset, int xi, int yj, int zk) {
	// Get all the HeV bubbles
	auto bubbles = network->getAll(heVType);
	// Initialyze the pointers to interstitial and helium clusters and their ID
	PSICluster * iCluster = nullptr, *heCluster = nullptr, *bubble = nullptr;
	int iIndex = -1, heIndex = -1, bubbleIndex = -1;
=======
void TrapMutationHandler::computeTrapMutation(const IReactionNetwork& network,
		double *concOffset, double *updatedConcOffset, int xi, int yj, int zk) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Initialize the rate of the reaction
	double rate = 0.0;

<<<<<<< HEAD
	// Get the pointer to list of indices at this grid point
	std::vector<int> * indices = &indexVector[zk][yj][xi];

	// Loop on the list
	for (int i = 0; i < indices->size(); i++) {
		// Get the stored bubble and its ID
		bubble = (PSICluster *) bubbles[indices->at(i)];
		bubbleIndex = bubble->getId() - 1;

		// Get the helium cluster with the same number of He and its ID
		auto comp = bubble->getComposition();
		heCluster = (PSICluster *) network->get(heType, comp[heType]);
		heIndex = heCluster->getId() - 1;

		// Get the interstitial cluster with the same number of I as the number
		// of vacancies in the bubble and its ID
		iCluster = (PSICluster *) network->get(iType, comp[vType]);
		iIndex = iCluster->getId() - 1;
=======
	// Loop on the list
	for (IReactant const& currReactant : tmBubbles[zk][yj][xi]) {

		// Get the stored bubble and its ID
		auto const& bubble = static_cast<PSICluster const&>(currReactant);
		auto bubbleIndex = bubble.getId() - 1;

		// Get the helium cluster with the same number of He and its ID
		// Note this composition has nonzero entries for both He and I,
		// so we can't use the network's get function that takes a composition.
		auto& comp = bubble.getComposition();
		auto heCluster = (PSICluster *) network.get(Species::He,
				comp[toCompIdx(Species::He)]);
		auto heIndex = heCluster->getId() - 1;

		// Get the interstitial cluster with the same number of I as the number
		// of vacancies in the bubble and its ID
		auto iCluster = (PSICluster *) network.get(Species::I,
				comp[toCompIdx(Species::V)]);
		auto iIndex = iCluster->getId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Get the initial concentration of helium
		double oldConc = concOffset[heIndex];

		// Check the desorption
<<<<<<< HEAD
		if (comp[heType] == desorp.size) {
=======
		if (comp[toCompIdx(Species::He)] == desorp.size) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Get the left side rate (combination + emission)
			double totalRate = heCluster->getLeftSideRate();
			// Define the trap-mutation rate taking into account the desorption
			rate = kDis * totalRate * (1.0 - desorp.portion) / desorp.portion;
		} else {
			rate = kDis * kMutation;
		}

		// Update the concentrations (the helium cluster loses its concentration)
		updatedConcOffset[heIndex] -= rate * oldConc;
		updatedConcOffset[bubbleIndex] += rate * oldConc;
		updatedConcOffset[iIndex] += rate * oldConc;
	}

	return;
}

int TrapMutationHandler::computePartialsForTrapMutation(
<<<<<<< HEAD
		IReactionNetwork *network, double *val, int *indices, int xi, int yj,
		int zk) {
	// Get all the HeV bubbles
	auto bubbles = network->getAll(heVType);
	// Initialyze the pointers to interstitial and helium clusters and their ID
	PSICluster * iCluster = nullptr, *heCluster = nullptr, *bubble = nullptr;
	int iIndex = -1, heIndex = -1, bubbleIndex = -1;
=======
		const IReactionNetwork& network, double *val, int *indices, int xi,
		int yj, int zk) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

	// Initialize the rate of the reaction
	double rate = 0.0;

<<<<<<< HEAD
	// Get the pointer to list of indices at this grid point
	std::vector<int> * clusterIndices = &indexVector[zk][yj][xi];
	// Loop on the list
	for (int i = 0; i < clusterIndices->size(); i++) {
		// Get the stored bubble and its ID
		bubble = (PSICluster *) bubbles[clusterIndices->at(i)];
		bubbleIndex = bubble->getId() - 1;

		// Get the helium cluster with the same number of He and its ID
		auto comp = bubble->getComposition();
		heCluster = (PSICluster *) network->get(heType, comp[heType]);
		heIndex = heCluster->getId() - 1;

		// Get the interstitial cluster with the same number of I as the number
		// of vacancies in the bubble and its ID
		iCluster = (PSICluster *) network->get(iType, comp[vType]);
		iIndex = iCluster->getId() - 1;

		// Check the desorption
		if (comp[heType] == desorp.size) {
=======
	// Consider all bubbles at this grid point.
	// TODO Relying on convention for indices in indices/vals arrays is
	// error prone - could be done with multiple parallel arrays.
	uint32_t i = 0;
	for (IReactant const& currReactant : tmBubbles[zk][yj][xi]) {

		// Get the stored bubble and its ID
		auto const& bubble = static_cast<PSICluster const&>(currReactant);
		auto bubbleIndex = bubble.getId() - 1;

		// Get the helium cluster with the same number of He and its ID
		// Note this composition has non-zero entries for both He and I.
		// so we can't use the network's get function that takes a composition.
		auto const& comp = bubble.getComposition();
		auto heCluster = (PSICluster *) network.get(Species::He,
				comp[toCompIdx(Species::He)]);
		auto heIndex = heCluster->getId() - 1;

		// Get the interstitial cluster with the same number of I as the number
		// of vacancies in the bubble and its ID
		auto iCluster = (PSICluster *) network.get(Species::I,
				comp[toCompIdx(Species::V)]);
		auto iIndex = iCluster->getId() - 1;

		// Check the desorption
		if (comp[toCompIdx(Species::He)] == desorp.size) {
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
			// Get the left side rate (combination + emission)
			double totalRate = heCluster->getLeftSideRate();
			// Define the trap-mutation rate taking into account the desorption
			rate = kDis * totalRate * (1.0 - desorp.portion) / desorp.portion;
		} else {
			rate = kDis * kMutation;
		}

		// Set the helium cluster partial derivative
<<<<<<< HEAD
		indices[i * 3] = heIndex;
		val[i * 3] = -rate;

		// Set the bubble cluster partial derivative
		indices[(i * 3) + 1] = bubbleIndex;
		val[(i * 3) + 1] = rate;

		// Set the interstitial cluster partial derivative
		indices[(i * 3) + 2] = iIndex;
		val[(i * 3) + 2] = rate;
	}

	return clusterIndices->size();
=======
		auto baseIndex = i * 3;
		indices[baseIndex] = heIndex;
		val[baseIndex] = -rate;

		// Set the bubble cluster partial derivative
		indices[(baseIndex) + 1] = bubbleIndex;
		val[(baseIndex) + 1] = rate;

		// Set the interstitial cluster partial derivative
		indices[(baseIndex) + 2] = iIndex;
		val[(baseIndex) + 2] = rate;

		// Advance to next indices/vals index.
		++i;
	}

	return (tmBubbles[zk][yj][xi]).size();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}

}/* end namespace xolotlCore */

