/**
 * 
 */
package gov.ornl.xolotl.preprocessor;

import java.util.ArrayList;

import uk.co.flamingpenguin.jewel.cli.ArgumentValidationException;
import uk.co.flamingpenguin.jewel.cli.CliFactory;

/**
 * This class launches the Xolotl preprocessor.
 * 
 * @author Jay Jay Billings
 * 
 */
public class Main {

	/**
	 * This operation launches the preprocessor and creates the initial
	 * conditions for Xolotl.
	 * 
	 * @param args
	 *            Command line arguments.
	 */
	public static void main(String[] args) {
		// Local Declarations
		Arguments myArgs = null;

		// Print some information to let the user know what is happening.
		System.out.println("Starting Xolotl Preprocessor...");

		// Get command line arguments
		try {
			// Parse the command line arguments.
			myArgs = CliFactory.parseArguments(Arguments.class, args);
			System.out.println("Command line arguments loaded.");

			// Generate the input if the arguments are valid.
			if (myArgs != null) {
				// Create the Preprocessor
				Preprocessor preprocessor = new Preprocessor(myArgs);

				// Generate the network of clusters
<<<<<<< HEAD
				ArrayList<Cluster> clusters = preprocessor
						.generateNetwork();
				System.out.println("Network generated.");
				
=======
				ArrayList<Cluster> clusters = preprocessor.generateNetwork();
				System.out.println("Network generated.");

>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				// Get the name of the networkFile from xolotlParams
				String networkFileName = preprocessor.xolotlParams.getProperty("networkFile");

				// Create the HDF5 file
				preprocessor.createHDF5(networkFileName);

				// Write the network in it
				preprocessor.writeNetwork(networkFileName, clusters);

				if (myArgs.isCheckpoint()) {
					String HDF5FileName = myArgs.getCheckpoint();
<<<<<<< HEAD
					// Read the header and the concentration from this file 
					// and copy them to the network file
					int[] gridSize = preprocessor.copyHeader(HDF5FileName, networkFileName);
					preprocessor.copyConcentration(HDF5FileName, networkFileName, 
							gridSize, clusters);
				}
				else {
					// Write the header in it with the size options from the preprocessor
=======
					// Read the header and the concentration from this file
					// and copy them to the network file
					int[] gridSize = preprocessor.copyHeader(HDF5FileName, networkFileName);
					preprocessor.copyConcentration(HDF5FileName, networkFileName, gridSize, clusters);
				} else {
					// Write the header in it with the size options from the
					// preprocessor
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
					preprocessor.writeHeader(networkFileName, myArgs);
				}

				System.out.println("HDF5 file generated.");

				// Write the file containing the parameters that are needed
				// to run Xolotl
<<<<<<< HEAD
				preprocessor.writeParameterFile("params.txt",
						preprocessor.xolotlParams);
=======
				preprocessor.writeParameterFile("params.txt", preprocessor.xolotlParams);
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
				System.out.println("Parameters written.");
			}
		} catch (ArgumentValidationException e1) {
			System.err.println("Unable to print input arguments. Aborting.");
			e1.printStackTrace();
			return;
		} catch (Exception e) {
<<<<<<< HEAD
			System.err.println("Exception caught while generating input. "
					+ "Aborting.");
=======
			System.err.println("Exception caught while generating input. " + "Aborting.");
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
			e.printStackTrace();
			return;
		}

		// Say goodbye
		System.out.println("Finished.");

		return;
	}
}
