/**
 * 
 */
package gov.ornl.xolotl.preprocessor;

<<<<<<< HEAD
=======
import java.io.File;
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
import java.util.ArrayList;

import uk.co.flamingpenguin.jewel.cli.ArgumentValidationException;
import uk.co.flamingpenguin.jewel.cli.CliFactory;
<<<<<<< HEAD
=======
import ncsa.hdf.object.FileFormat;
import ncsa.hdf.object.h5.H5File;
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618

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

		// Local Declarations
		Arguments myArgs = null;
		
		// Get command line arguments
		try {
			myArgs = CliFactory.parseArguments(Arguments.class, args);
		} catch (ArgumentValidationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		// Create a file from the uri
		File file = new File("test.hdf5");

		// Retrieve an instance of the HDF5 format
		FileFormat fileFormat = FileFormat
				.getFileFormat(FileFormat.FILE_TYPE_HDF5);

		// Create an H5 file. If it exists already, then delete it.
		try {
			H5File h5File = (H5File) fileFormat.createFile(file.getPath(),
					FileFormat.FILE_CREATE_DELETE);
		} catch (Exception e) {
			// Complain
			e.printStackTrace();
		}
		
		// Create the Preprocessor - FIXME! Check myArgs != null
		Preprocessor preprocessor = new Preprocessor(myArgs);

		// Generate the clusters
		ArrayList<Cluster> clusters = preprocessor.generate(args);

		// Dump the clusters to stdout
		for (Cluster cluster : clusters) {
			System.out.println(cluster.toString());
		}

		return;
	}

>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
}
