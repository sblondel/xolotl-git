// Includes
#include "YGBAdvectionHandler.h"

namespace xolotlCore {

<<<<<<< HEAD
void YGBAdvectionHandler::initialize(IReactionNetwork *network,
		int *ofill) {
	// Get all the reactants and their number
	auto reactants = network->getAll();
	int networkSize = reactants->size();
	int dof = network->getDOF();

	// Clear the index and sink strength vectors
	indexVector.clear();
	sinkStrengthVector.clear();

	// Loop on all the reactants
	for (int i = 0; i < networkSize; i++) {
		// Get the i-th cluster
		auto cluster = (PSICluster *) reactants->at(i);
		// Get its diffusion coefficient
		double diffFactor = cluster->getDiffusionFactor();
=======
void YGBAdvectionHandler::initialize(const IReactionNetwork& network,
		int *ofill) {

	int dof = network.getDOF();

	// Clear the index and sink strength vectors
	advectingClusters.clear();
	sinkStrengthVector.clear();

	// Loop on all the reactants
	for (IReactant const& currReactant : network.getAll()) {

		auto const& cluster = static_cast<PSICluster const&>(currReactant);

		// Get its diffusion coefficient
		double diffFactor = cluster.getDiffusionFactor();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Don't do anything if the diffusion factor is 0.0
		if (xolotlCore::equal(diffFactor, 0.0))
			continue;

		// Keep only the helium clusters
<<<<<<< HEAD
		if (cluster->getType() != heType)
			continue;

		// Get its size
		int heSize = cluster->getSize();
=======
		if (cluster.getType() != ReactantType::He)
			continue;

		// Get its size
		int heSize = cluster.getSize();
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Switch on the size to get the sink strength (in eV.nm3)
		double sinkStrength = 0.0;
		switch (heSize) {
		case 1:
			sinkStrength = 0.54e-3;
			break;
		case 2:
			sinkStrength = 1.01e-3;
			break;
		case 3:
			sinkStrength = 3.03e-3;
			break;
		case 4:
			sinkStrength = 3.93e-3;
			break;
		case 5:
			sinkStrength = 7.24e-3;
			break;
		case 6:
			sinkStrength = 10.82e-3;
			break;
		case 7:
			sinkStrength = 19.26e-3;
			break;
		}

		// If the sink strength is still 0.0, this cluster is not advecting
		if (xolotlCore::equal(sinkStrength, 0.0))
			continue;

<<<<<<< HEAD
		// Add its index (i) to the vector of indices
		indexVector.push_back(i);
=======
		// Note that the current cluster is advecting.
		advectingClusters.emplace_back(cluster);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// Add the sink strength to the vector
		sinkStrengthVector.push_back(sinkStrength);

		// Set the off-diagonal part for the Jacobian to 1
		// Get its id
<<<<<<< HEAD
		int index = cluster->getId() - 1;
=======
		int index = cluster.getId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		// Set the ofill value to 1 for this cluster
		ofill[index * dof + index] = 1;
	}

	return;
}

<<<<<<< HEAD
void YGBAdvectionHandler::computeAdvection(IReactionNetwork *network,
		std::vector<double> &pos, double **concVector,
		double *updatedConcOffset, double hxLeft, double hxRight, int ix,
		double hy, int iy, double hz, int iz) {
	// Get all the reactant
	auto reactants = network->getAll();
	// Get the number of advecting cluster
	int nAdvec = indexVector.size();

	// Loop on the advecting clusters
	for (int i = 0; i < nAdvec; i++) {
		// Get a specific one and its index
		auto cluster = (PSICluster *) reactants->at(indexVector[i]);
		int index = cluster->getId() - 1;
=======
void YGBAdvectionHandler::computeAdvection(const IReactionNetwork& network,
		const Point3D& pos, double **concVector, double *updatedConcOffset,
		double hxLeft, double hxRight, int ix, double hy, int iy, double hz,
		int iz) const {

	// Consider each advecting cluster.
	// TODO Maintaining a separate index assumes that advectingClusters is
	// visited in same order as advectionGrid array for given point
	// and the sinkStrengthVector.
	// Currently true with C++11, but we'd like to be able to visit the
	// advecting clusters in any order (so that we can parallelize).
	// Maybe with a zip? or a std::transform?
	int advClusterIdx = 0;
	for (IReactant const& currReactant : advectingClusters) {

		auto const& cluster = static_cast<PSICluster const&>(currReactant);
		int index = cluster.getId() - 1;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// If we are on the sink, the behavior is not the same
		// Both sides are giving their concentrations to the center
		if (isPointOnSink(pos)) {
			double oldBottomConc = concVector[3][index]; // bottom
			double oldTopConc = concVector[4][index]; // top

<<<<<<< HEAD
			double conc = (3.0 * sinkStrengthVector[i]
					* cluster->getDiffusionCoefficient())
					* ((oldBottomConc / pow(hy, 5)) + (oldTopConc / pow(hy, 5)))
					/ (xolotlCore::kBoltzmann * cluster->getTemperature());
=======
			double conc = (3.0 * sinkStrengthVector[advClusterIdx]
					* cluster.getDiffusionCoefficient())
					* ((oldBottomConc / pow(hy, 5)) + (oldTopConc / pow(hy, 5)))
					/ (xolotlCore::kBoltzmann * cluster.getTemperature());
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Update the concentration of the cluster
			updatedConcOffset[index] += conc;
		}
		// Here we are NOT on the GB sink
		else {
			// Get the initial concentrations
			double oldConc = concVector[0][index]; // middle
			double oldRightConc = concVector[4 * (pos[1] > location)
					+ 3 * (pos[1] < location)][index]; // top or bottom

			// Get the a=d and b=d+h positions
			double a = fabs(location - pos[1]);
			double b = fabs(location - pos[1]) + hy;

			// Compute the concentration as explained in the description of the method
<<<<<<< HEAD
			double conc = (3.0 * sinkStrengthVector[i]
					* cluster->getDiffusionCoefficient())
					* ((oldRightConc / pow(b, 4)) - (oldConc / pow(a, 4)))
					/ (xolotlCore::kBoltzmann * cluster->getTemperature() * hy);
=======
			double conc = (3.0 * sinkStrengthVector[advClusterIdx]
					* cluster.getDiffusionCoefficient())
					* ((oldRightConc / pow(b, 4)) - (oldConc / pow(a, 4)))
					/ (xolotlCore::kBoltzmann * cluster.getTemperature() * hy);
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

			// Update the concentration of the cluster
			updatedConcOffset[index] += conc;
		}
<<<<<<< HEAD
=======

		++advClusterIdx;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

void YGBAdvectionHandler::computePartialsForAdvection(
<<<<<<< HEAD
		IReactionNetwork *network, double *val, int *indices,
		std::vector<double> &pos, double hxLeft, double hxRight, int ix,
		double hy, int iy, double hz, int iz) {
	// Get all the reactant
	auto reactants = network->getAll();
	// Get the number of advecting cluster
	int nAdvec = indexVector.size();

	// Loop on the advecting clusters
	for (int i = 0; i < nAdvec; i++) {
		// Get a specific one and its index
		auto cluster = (PSICluster *) reactants->at(indexVector[i]);
		int index = cluster->getId() - 1;
		// Get the diffusion coefficient of the cluster
		double diffCoeff = cluster->getDiffusionCoefficient();
		// Get the sink strength value
		double sinkStrength = sinkStrengthVector[i];

		// Set the cluster index that will be used by PetscSolver
		// to compute the row and column indices for the Jacobian
		indices[i] = index;
=======
		const IReactionNetwork& network, double *val, int *indices,
		const Point3D& pos, double hxLeft, double hxRight, int ix, double hy,
		int iy, double hz, int iz) const {

	// Consider each advecting cluster.
	// TODO Maintaining a separate index assumes that advectingClusters is
	// visited in same order as advectionGrid array for given point
	// and the sinkStrengthVector.
	// Currently true with C++11, but we'd like to be able to visit the
	// advecting clusters in any order (so that we can parallelize).
	// Maybe with a zip? or a std::transform?
	int advClusterIdx = 0;
	for (IReactant const& currReactant : advectingClusters) {

		auto const& cluster = static_cast<PSICluster const&>(currReactant);

		int index = cluster.getId() - 1;
		// Get the diffusion coefficient of the cluster
		double diffCoeff = cluster.getDiffusionCoefficient();
		// Get the sink strength value
		double sinkStrength = sinkStrengthVector[advClusterIdx];

		// Set the cluster index that will be used by PetscSolver
		// to compute the row and column indices for the Jacobian
		indices[advClusterIdx] = index;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487

		// If we are on the sink, the partial derivatives are not the same
		// Both sides are giving their concentrations to the center
		if (isPointOnSink(pos)) {
<<<<<<< HEAD
			val[i * 2] = (3.0 * sinkStrength * diffCoeff)
					/ (xolotlCore::kBoltzmann * cluster->getTemperature()
							* pow(hy, 5)); // top or bottom
			val[(i * 2) + 1] = val[i * 2]; // top or bottom
=======
			val[advClusterIdx * 2] = (3.0 * sinkStrength * diffCoeff)
					/ (xolotlCore::kBoltzmann * cluster.getTemperature()
							* pow(hy, 5)); // top or bottom
			val[(advClusterIdx * 2) + 1] = val[advClusterIdx * 2]; // top or bottom
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
		}
		// Here we are NOT on the GB sink
		else {
			// Get the a=d and b=d+h positions
			double a = fabs(location - pos[1]);
			double b = fabs(location - pos[1]) + hy;

			// Compute the partial derivatives for advection of this cluster as
			// explained in the description of this method
<<<<<<< HEAD
			val[i * 2] = -(3.0 * sinkStrength * diffCoeff)
					/ (xolotlCore::kBoltzmann * cluster->getTemperature()
							* hy * pow(a, 4)); // middle
			val[(i * 2) + 1] = (3.0 * sinkStrength * diffCoeff)
					/ (xolotlCore::kBoltzmann * cluster->getTemperature()
							* hy * pow(b, 4)); // top or bottom
		}
=======
			val[advClusterIdx * 2] = -(3.0 * sinkStrength * diffCoeff)
					/ (xolotlCore::kBoltzmann * cluster.getTemperature() * hy
							* pow(a, 4)); // middle
			val[(advClusterIdx * 2) + 1] = (3.0 * sinkStrength * diffCoeff)
					/ (xolotlCore::kBoltzmann * cluster.getTemperature() * hy
							* pow(b, 4)); // top or bottom
		}

		++advClusterIdx;
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	}

	return;
}

<<<<<<< HEAD
std::vector<int> YGBAdvectionHandler::getStencilForAdvection(
		std::vector<double> &pos) {
=======
std::array<int, 3> YGBAdvectionHandler::getStencilForAdvection(
		const Point3D& pos) const {

>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
	// The second index is positive by convention if we are on the sink
	if (isPointOnSink(pos))
		return {0, 1, 0};
	// The second index is positive if pos[1] > location
	// negative if pos[1] < location
	return {0, (pos[1] > location) - (pos[1] < location), 0};
}

<<<<<<< HEAD
bool YGBAdvectionHandler::isPointOnSink(std::vector<double> &pos) {
	// Return true if pos[1] is equal to location
	return fabs(location - pos[1]) < 0.001;
}

=======
>>>>>>> f34969426039f232c45728e88f3cb03a131ca487
}/* end namespace xolotlCore */
