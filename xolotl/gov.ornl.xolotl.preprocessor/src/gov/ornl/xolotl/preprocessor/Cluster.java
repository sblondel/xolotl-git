/**
 * 
 */
package gov.ornl.xolotl.preprocessor;

/**
 * A simple, all public constructor that represents a cluster. It overwrites
 * toString() to write itself according to the specification needed by Xolotl.
 * 
 * @author jaybilly
 * 
 */
public class Cluster {

<<<<<<< HEAD
<<<<<<< HEAD
	// The number of helium atoms in the cluster. Default value is 0.
	public int nHe = 0;

	// The number of xenon atoms in the cluster. Default value is 0.
	public int nXe = 0;

=======
	// The number of Helium atoms in the cluster. Default value is 0.
	public int nHe = 0;

>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
	// The number of Helium atoms in the cluster. Default value is 0.
	public int nHe = 0;

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	// The number of vacancies in the cluster. Default value is 0.
	public int nV = 0;

	// The number of interstitials in the cluster. Default value is 0.
	public int nI = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	// The formation energy of this cluster
	public double E_f = 0.0;
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	// The binding energy of the cluster with He_1. Default value is infinity so
	// that the cluster does not dissociate.
	public double E_He = Double.POSITIVE_INFINITY;

	// The binding energy of the cluster with V_1. Default value is infinity so
	// that the cluster does not dissociate.
	public double E_V = Double.POSITIVE_INFINITY;

	// The binding energy of the cluster with I_1. Default value is infinity so
	// that the cluster does not dissociate.
	public double E_I = Double.POSITIVE_INFINITY;
<<<<<<< HEAD
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

	// The migration energy with which the cluster diffuses. Default value is
	// infinity so that the cluster is immobile.
	public double E_m = Double.POSITIVE_INFINITY;

	// The diffusion factor that sets the scale of the diffusion. Default value
	// is infinity so that the cluster is immobile.
	// is 0.
	public double D_0 = 0.0;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	/**
	 * This operation returns the cluster as a string of the form
	 * 
	 * nHe nV nI E_He E_V E_I E_migration D_0
	 */
	public String toString() {

		// Convert infinite energies
		String EHeAsString = (!Double.isInfinite(E_He)) ? String.valueOf(E_He)
				: "Infinity";
		String EVAsString = (!Double.isInfinite(E_V)) ? String.valueOf(E_V)
				: "Infinity";
		String EIAsString = (!Double.isInfinite(E_I)) ? String.valueOf(E_I)
				: "Infinity";
		String EMAsString = (!Double.isInfinite(E_m)) ? String.valueOf(E_m)
				: "Infinity";

		return nHe + " " + nV + " " + nI + " " + EHeAsString + " " + EVAsString
				+ " " + EIAsString + " " + EMAsString + " " + D_0;
	}

<<<<<<< HEAD
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}
