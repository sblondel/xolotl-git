package gov.ornl.xolotl.preprocessor.test;

import static org.junit.Assert.*;

import java.util.Enumeration;
import java.util.Properties;
import java.util.ArrayList;
import java.io.*;

import gov.ornl.xolotl.preprocessor.Preprocessor;
import gov.ornl.xolotl.preprocessor.Arguments;
import gov.ornl.xolotl.preprocessor.Cluster;

import org.junit.Test;
<<<<<<< HEAD
import org.junit.rules.ExpectedException;
=======
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624

import uk.co.flamingpenguin.jewel.cli.ArgumentValidationException;
import uk.co.flamingpenguin.jewel.cli.CliFactory;

/**
 * This class is responsible for testing the Preprocessor class
 */
public class PreprocessorTest {

	/**
<<<<<<< HEAD
	 * This operation checks that the default parameters will be used along with
	 * writeParameterFile and loadParameterFile.
	 */
	@Test
	public void testParameterFile() {
=======
	 * This operation checks the generateParameters function.
	 */
	@Test
	public void testGenerateParameters() {

>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		// Local Declarations
		Arguments parsedArgs = null;

		try {
<<<<<<< HEAD
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] {});
=======
			parsedArgs = CliFactory.parseArguments(Arguments.class,
					new String[] {});
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

<<<<<<< HEAD
				// Write the parameter file
				preprocessor.writeParameterFile("paramsTest", preprocessor.xolotlParams);

				// Load the properties from the parameter file to check they
				// were written correctly
				Properties inProps = preprocessor.loadParameterFile("paramsTest");

				// Enumeration to hold the parameter names
				Enumeration<?> paramNames = inProps.propertyNames();
				while (paramNames.hasMoreElements()) {
					String key = (String) paramNames.nextElement();
					String value = inProps.getProperty(key);
					// Check that the default parameter values were used
					assertEquals(preprocessor.xolotlParams.getProperty(key), value);
				}

				// Delete the parameter file
				new File("paramsTest").delete();
			}
		} catch (ArgumentValidationException e) {
			// Complain and fail
			e.printStackTrace();
			fail();
		}

		return;
	}

	/**
	 * This operation checks that the options specified via the command line
	 * will override the default values.
	 */
	@Test
	public void testCLOptionOverride() {
		// Local Declarations
		Arguments parsedArgs = null;

		try {
			parsedArgs = CliFactory.parseArguments(Arguments.class,
					new String[] { "--perfHandler", "dummy", "--petscArgs=" + "-da_grid_x 8 -ts_final_time 2" });

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

				// Write the parameter file
				preprocessor.writeParameterFile("clOptionsTest", preprocessor.xolotlParams);

				// Load the properties from the parameter file to check they
				// were written correctly
				Properties inProps = preprocessor.loadParameterFile("clOptionsTest");

				// Enumeration to hold the parameter names
				Enumeration<?> paramNames = inProps.propertyNames();
				while (paramNames.hasMoreElements()) {
					String key = (String) paramNames.nextElement();
					String value = inProps.getProperty(key);
					// Check that the default parameter values were used
					assertEquals(preprocessor.xolotlParams.getProperty(key), value);
				}

				// Delete the parameter file
				new File("clOptionsTest").delete();
			}
		} catch (ArgumentValidationException e) {
			// Complain and fail
			e.printStackTrace();
			fail();
		}

=======
				// Generate the parameters
				Properties defaults = preprocessor.generateParameters();

				// Check that the default material is W
				assertEquals("W", defaults.getProperty("material"));

				// Check that the default startTemp is 1000
				assertEquals("1000", defaults.getProperty("startTemp"));

				// Check that the default tempFile is tempFile
				assertEquals("tempFile", defaults.getProperty("tempFile"));

				// Check that the default heFlux is 2.5e27
				assertEquals("2.5e27", defaults.getProperty("heFlux"));

				// Check that the default perfHandler is dummy
				assertEquals("dummy", defaults.getProperty("perfHandler"));

				// Check that the default vizHandler is dummy
				assertEquals("dummy", defaults.getProperty("vizHandler"));

				// Check that the default checkpoint is true
				assertEquals("false", defaults.getProperty("checkpoint"));

				// Check that the default networkFile is networkInit.h5
				assertEquals("networkInit.h5",
						defaults.getProperty("networkFile"));

				// Check the default petscArgs
				assertEquals(
						"-da_grid_x 10 -ts_final_time 1000 "
								+ "-ts_max_steps 3 -ts_adapt_dt_max 10 -ts_max_snes_failures 200 "
								+ "-pc_type fieldsplit -pc_fieldsplit_detect_coupling -fieldsplit_0_pc_type redundant "
								+ "-fieldsplit_1_pc_type sor -snes_monitor -ksp_monitor -ts_monitor",
						defaults.getProperty("petscArgs"));
			}
		} catch (ArgumentValidationException e1) {
			e1.printStackTrace();
		}
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		return;
	}

	/**
<<<<<<< HEAD
	 * This operation checks if the optional options are specified via the
	 * command line, that they will be included in the parameter file.
	 */
	@Test
	public void testOptionalOptions() {
=======
	 * This operation checks writeParameterFile and loadParameterFile.
	 */
	@Test
	public void testParameterFile() {

>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		// Local Declarations
		Arguments parsedArgs = null;

		try {
			parsedArgs = CliFactory.parseArguments(Arguments.class,
<<<<<<< HEAD
					new String[] { "--startTemp", "900", "--flux", "1.5" });
=======
					new String[] {});
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

				// Write the parameter file
<<<<<<< HEAD
				preprocessor.writeParameterFile("optionalOpsTest", preprocessor.xolotlParams);

				// Load the properties from the parameter file to check they
				// were written correctly
				Properties inProps = preprocessor.loadParameterFile("optionalOpsTest");

=======
				preprocessor.writeParameterFile("paramsTest",
						preprocessor.xolotlParams);

				// Load the properties from the parameter file to check they
				// were written correctly
				Properties inProps = preprocessor
						.loadParameterFile("paramsTest");
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
				// Enumeration to hold the parameter names
				Enumeration<?> paramNames = inProps.propertyNames();
				while (paramNames.hasMoreElements()) {
					String key = (String) paramNames.nextElement();
					String value = inProps.getProperty(key);
<<<<<<< HEAD
					// Check that the default parameter values were used
					assertEquals(preprocessor.xolotlParams.getProperty(key), value);
				}

				// Delete the parameter file
				new File("optionalOpsTest").delete();
			}
		} catch (ArgumentValidationException e) {
			// Complain and fail
			e.printStackTrace();
			fail();
=======
					assertEquals(preprocessor.xolotlParams.getProperty(key),
							value);
				}

			}
		} catch (ArgumentValidationException e1) {
			e1.printStackTrace();
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		}

		return;
	}

	/**
<<<<<<< HEAD
	 * This operation checks that it is not possible to give wrong sizes for He,
	 * I, and V.
	 */
	@Test(expected = IllegalArgumentException.class)
	public void testBadMaxClusterSizeOptions() {

		// Local Declarations
		Arguments parsedArgs = null;

		try {
			// Try a number of helium that is too big
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] { "--maxHeSize", "10" });

			// Check that the max helium cluster size is 10
			assertEquals(10, parsedArgs.getMaxHeSize());

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);
				fail("Should have thrown an IllegalArgumentException because "
						+ "the maximum He size is out of range.");
			}
		} catch (ArgumentValidationException e) {
			e.printStackTrace();
		}

		try {
			// Try a number of vacancy that is negative
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] { "--maxVSize", "-1" });

			// Check that the max interstitial cluster size is -1
			assertEquals(-2, parsedArgs.getMaxVSize());

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);
				fail("Should have thrown an IllegalArgumentException because " + "the maximum V size is out of range.");
			}
		} catch (ArgumentValidationException e) {
			e.printStackTrace();
		}

		try {
			// Try a number of interstitial that is negative
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] { "--maxISize", "-2" });

			// Check that the max interstitial cluster size is -2
			assertEquals(-2, parsedArgs.getMaxISize());

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);
				fail("Should have thrown an IllegalArgumentException because " + "the maximum I size is out of range.");
			}
		} catch (ArgumentValidationException e) {
			e.printStackTrace();
		}

		return;
	}

	/**
	 * This operation checks the generation of the network.
	 */
	@Test
	public void testNetworkGeneration() {
=======
	 * This operation checks generateGrid.
	 */
	@Test
	public void testGenerateGrid() {

>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		// Local Declarations
		Arguments parsedArgs = null;

		try {
<<<<<<< HEAD
			// Keep the default arguments
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] {});
=======
			parsedArgs = CliFactory.parseArguments(Arguments.class,
					new String[] {});
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

<<<<<<< HEAD
				// Generate the network
				ArrayList<Cluster> network = preprocessor.generateNetwork();

				// Check the size of the network
				assertEquals(network.size(), 2067);
			}

			// Change the number of V clusters
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] { "--maxVSize", "60" });

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

				// Generate the network
				ArrayList<Cluster> network = preprocessor.generateNetwork();

				// Check the size of the network
				assertEquals(network.size(), 7678);
			}

			// Use the phase-cut method
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] { "--phaseCut" });

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

				// Generate the network
				ArrayList<Cluster> network = preprocessor.generateNetwork();

				// Check the size of the network
				assertEquals(network.size(), 447);
			}
		} catch (ArgumentValidationException e) {
			// Complain and fail
			e.printStackTrace();
			fail();
=======
				// Create the known grid array
				double[] knownGrid = new double[15];

				// Fill it with known values
				for (int i = 0; i < 15; i++) {
					knownGrid[i] = (double) i * 0.57142857142;
				}

				try {
					// Generate a grid
					double[] newGrid = preprocessor.generateGrid(8, 1);

					// Check the length of it
					assertEquals(newGrid.length, knownGrid.length);

					// Check all the values
					for (int i = 0; i < newGrid.length; i++) {
						assertEquals(newGrid[i], knownGrid[i], 1.0e-5);
					}

				} catch (Exception e) {
					// Complain and fail
					e.printStackTrace();
					fail();
				}

			}
		} catch (ArgumentValidationException e1) {
			e1.printStackTrace();
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		}

		return;
	}

	/**
	 * This operation checks the writing of the HDF5 file.
	 */
	@Test
	public void testHDF5Writing() {
<<<<<<< HEAD
=======

>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		// Local Declarations
		Arguments parsedArgs = null;

		try {
<<<<<<< HEAD
			parsedArgs = CliFactory.parseArguments(Arguments.class, new String[] {});
=======
			parsedArgs = CliFactory.parseArguments(Arguments.class,
					new String[] {});
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624

			if (parsedArgs != null) {
				Preprocessor preprocessor = new Preprocessor(parsedArgs);

				// Create an empty cluster array
				ArrayList<Cluster> clusters = new ArrayList<Cluster>();

				// Create a cluster
				Cluster cluster = new Cluster();
<<<<<<< HEAD
				cluster.nXe = 1;
				cluster.nV = 23;
				cluster.nI = 52;
				cluster.E_f = 12.3;
=======
				cluster.nHe = 1;
				cluster.nV = 23;
				cluster.nI = 52;
				cluster.E_He = 9.325;
				cluster.E_V = 34.2346;
				cluster.E_I = 3326424.2323543;
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
				cluster.E_m = 0.04;
				cluster.D_0 = 1.1;

				// Add it to clusters
				clusters.add(cluster);

<<<<<<< HEAD
				// Create the HDF5 file
				preprocessor.createHDF5("test.h5");

				// Write the header in it
				preprocessor.writeHeader("test.h5", parsedArgs);

				// Write the network in it
				preprocessor.writeNetwork("test.h5", clusters);

				// Check that the file was created
				File f = new File("test.h5");
				boolean fileExists = (f.exists() && !f.isDirectory());
				assertEquals(fileExists, true);
			}
		} catch (ArgumentValidationException e) {
			// Complain and fail
			e.printStackTrace();
			fail();
=======
				try {
					// Create the HDF5 file
					preprocessor.createHDF5("test.h5");

					// Write the header in it
					int[] dim = { 4 };
					int[] refinement = { 0 };
					preprocessor.writeHeader("test.h5", dim, refinement);

					// Write the network in it
					preprocessor.writeNetwork("test.h5", clusters);

					// Check that the file was created
					File f = new File("test.h5");
					boolean fileExists = (f.exists() && !f.isDirectory());
					assertEquals(fileExists, true);

				} catch (Exception e) {
					// Complain and fail
					e.printStackTrace();
					fail();
				}

			}
		} catch (ArgumentValidationException e1) {
			e1.printStackTrace();
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
		}

		return;
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
