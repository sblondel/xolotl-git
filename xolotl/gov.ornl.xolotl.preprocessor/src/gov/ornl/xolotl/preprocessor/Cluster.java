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
	// The number of Helium atoms in the cluster. Default value is 0.
	public int nHe = 0;

=======
	// The number of helium atoms in the cluster. Default value is 0.
	public int nHe = 0;

	// The number of xenon atoms in the cluster. Default value is 0.
	public int nXe = 0;

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
	// The number of vacancies in the cluster. Default value is 0.
	public int nV = 0;

	// The number of interstitials in the cluster. Default value is 0.
	public int nI = 0;

	// The formation energy of this cluster
	public double E_f = 0.0;

	// The migration energy with which the cluster diffuses. Default value is
	// infinity so that the cluster is immobile.
	public double E_m = Double.POSITIVE_INFINITY;

	// The diffusion factor that sets the scale of the diffusion. Default value
	// is infinity so that the cluster is immobile.
	// is 0.
	public double D_0 = 0.0;

<<<<<<< HEAD
	/**
	 * This operation returns the cluster as a string of the form
	 * 
	 * nHe nV nI E_f E_migration D_0
	 */
	public String toString() {

		// Convert infinite energies
		String EfAsString = (!Double.isInfinite(E_f)) ? String.valueOf(E_f)
				: "Infinity";
		String EMAsString = (!Double.isInfinite(E_m)) ? String.valueOf(E_m)
				: "Infinity";

		return nHe + " " + nV + " " + nI + " " + EfAsString + " " + EMAsString + " " + D_0;
	}

=======
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
}
