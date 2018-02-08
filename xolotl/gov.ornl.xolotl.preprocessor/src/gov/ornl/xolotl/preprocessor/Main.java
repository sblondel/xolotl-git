/**
 * 
 */
package gov.ornl.xolotl.preprocessor;

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
import java.io.File;
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
import java.util.ArrayList;

import uk.co.flamingpenguin.jewel.cli.ArgumentValidationException;
import uk.co.flamingpenguin.jewel.cli.CliFactory;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
import ncsa.hdf.object.FileFormat;
import ncsa.hdf.object.h5.H5File;
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

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
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
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

				if (!myArgs.isNetParam()) {
					// Generate the network of clusters
					ArrayList<Cluster> clusters = preprocessor.generateNetwork();
					System.out.println("Network generated.");

					// Get the name of the networkFile from xolotlParams
					String networkFileName = preprocessor.xolotlParams.getProperty("networkFile");

					// Create the HDF5 file
					preprocessor.createHDF5(networkFileName);

					// Write the network in it
					preprocessor.writeNetwork(networkFileName, clusters);

					if (myArgs.isCheckpoint()) {
						String HDF5FileName = myArgs.getCheckpoint();
						// Read the header and the concentration from this file
						// and copy them to the network file
						int[] gridSize = preprocessor.copyHeader(HDF5FileName, networkFileName, myArgs);
						preprocessor.copyConcentration(HDF5FileName, networkFileName, gridSize);
					} else {
						// Write the header in it with the size options from the
						// preprocessor
						preprocessor.writeHeader(networkFileName, myArgs);
					}

					System.out.println("HDF5 file generated.");
				}

				// Write the file containing the parameters that are needed
				// to run Xolotl
				preprocessor.writeParameterFile("params.txt", preprocessor.xolotlParams);
				System.out.println("Parameters written.");
			}
		} catch (ArgumentValidationException e1) {
			System.err.println("Unable to print input arguments. Aborting.");
			e1.printStackTrace();
			return;
		} catch (Exception e) {
			System.err.println("Exception caught while generating input. " + "Aborting.");
			e.printStackTrace();
			return;
		}

		// Say goodbye
		System.out.println("Finished.");

		return;
	}
=======

=======
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		// Local Declarations
		Arguments myArgs = null;

		// Get command line arguments
		try {

			myArgs = CliFactory.parseArguments(Arguments.class, args);

			if (myArgs != null) {
				try {
					// Create the Preprocessor
					Preprocessor preprocessor = new Preprocessor(myArgs);

					// Generate the network of clusters
					ArrayList<Cluster> clusters = preprocessor
							.generateNetwork(args);

					// Create the HDF5 file
					preprocessor.createHDF5("networkInit.h5");

					// Write the header in it
					int[] dim = { 8 };
					int[] refinement = { 0 };
					preprocessor.writeHeader("networkInit.h5", dim, refinement);

					// Write the network in it
					preprocessor.writeNetwork("networkInit.h5", clusters);

					// Write the file containing the parameters that are needed
					// to run Xolotl
					preprocessor.writeParameterFile("params.txt",
							preprocessor.xolotlParams);

				} catch (Exception e) {
					e.printStackTrace();
				}
			}

		} catch (ArgumentValidationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		return;
	}

<<<<<<< HEAD
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
}
