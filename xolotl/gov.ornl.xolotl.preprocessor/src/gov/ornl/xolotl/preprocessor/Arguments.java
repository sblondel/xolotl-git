package gov.ornl.xolotl.preprocessor;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
import uk.co.flamingpenguin.jewel.cli.Option;

/**
 * This interface creates command line options for the parameters that are
 * needed to run Xolotl. If the options are not specified via the command line,
 * then the default values are used.
<<<<<<< HEAD
 */
public interface Arguments {

	/**
	 * This Option annotation corresponds to the '--maxHeSize' option which
	 * defines a default value of 8 and additionally provides a brief
	 * description of this option.
	 * 
	 * @param defaultValue
	 *            The default value for the maximum size of a helium cluster in
	 *            the network if this option is not specified via the command
	 *            line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "8", description = "The maximum size of a helium cluster in the network "
			+ "satisfying the condition 0 <= maxHeSize < 9. (default = 8)")
	/**
	 * This operation produces the required command line option '--maxHeSize'
	 * which takes a single integer value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The maximum size of a helium cluster in the network satisfying
	 *         the condition 0 <= maxHeSize < 9
	 */
	int getMaxHeSize();

	/**
	 * This Option annotation corresponds to the '--maxxeSize' option which
	 * defines a default value of 0 and additionally provides a brief
	 * description of this option.
	 * 
	 * @param defaultValue
	 *            The default value for the maximum size of a xenon cluster in
	 *            the network if this option is not specified via the command
	 *            line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "0", description = "The maximum size of a xenon cluster in the network "
			+ "satisfying the condition 0 <= maxXeSize. (default = 0)")
	/**
	 * This operation produces the required command line option '--maxXeSize'
	 * which takes a single integer value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The maximum size of a xenon cluster in the network satisfying the
	 *         condition 0 <= maxXeSize
	 */
	int getMaxXeSize();

	/**
	 * This Option annotation corresponds to the '--maxVSize' option which
	 * defines a default value of 29 and additionally provides a brief
	 * description of this option.
	 * 
	 * @param defaultValue
	 *            The default value for the maximum size of a vacancy cluster in
	 *            the network if this option is not specified via the command
	 *            line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "29", description = "The maximum size of a vacancy cluster in the network "
			+ "satisfying the condition 0 <= maxVSize.. (default = 29)")
	/**
	 * This operation produces the required command line option '--maxVSize'
	 * which takes a single integer value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The maximum size of a vacancy cluster in the network
	 */
	int getMaxVSize();

	/**
	 * This Option annotation corresponds to the '--maxISize' option which
	 * defines a default value of 6 and additionally provides a brief
	 * description of this option.
	 * 
	 * @param defaultValue
	 *            The default value for the maximum size of an interstitial
	 *            cluster in the network if this option is not specified via the
	 *            command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "6", description = "The maximum size of an interstitial cluster in the network "
			+ "satisfying the condition 0 <= maxISize. (default = 6)")
	/**
	 * This operation produces the required command line option '--maxISize'
	 * which takes a single integer value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The maximum size of an interstitial cluster in the network
	 *         satisfying the condition 0 <= maxISize
	 */
	int getMaxISize();

	/**
	 * This Option annotation corresponds to the '--phaseCut' option which
	 * doesn't have a default value because it is used as a flag.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "Should the network be reduced with the phase-cut method?")
	/**
	 * This operation produces the required command line option '--phaseCut'
	 * which doesn't take a value and is defined by the previous Option
	 * annotation
	 * 
	 * @return Whether we use the phase cut or not
	 */
	boolean isPhaseCut();

	/**
	 * This Option annotation corresponds to the '--startTemp' option which
	 * defines a default value of 1000 and additionally provides a brief
	 * description of this option.
	 * 
	 * @param defaultValue
	 *            The default, string, value for the constant starting
	 *            temperature (in Kelvin) if this option is not specified via
	 *            the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "1000", description = "The temperature (in Kelvin) will be the constant "
			+ "value specified (default = 1000). If a second value is given this value will be used "
			+ "for a temperature gradient")
	/**
	 * This operation produces the required command line option '--startTemp'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The constant starting temperature as a string
	 */
	String getStartTemp();

	/**
	 * This Option annotation corresponds to the '--perfHandler' option which
	 * defines the default value to use the standard performance handlers and
	 * additionally provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default performance handler that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "std", description = "{dummy, std, io, papi}  Which set of performance handlers to use (default = std)")
	/**
	 * This operation produces the required command line option '--perfHandler'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The performance handler, as a string, that will be used
	 */
	String getPerfHandler();

	/**
	 * This Option annotation corresponds to the '--vizHandler' option which
	 * defines the default value to use the dummy visualization handlers and
	 * additionally provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default visualization handler that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "dummy", description = "{dummy, std}  Which set of visualization handlers to use")
	/**
	 * This operation produces the required command line option '--vizHandler'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The performance handler, as a string, that will be used
	 */
	String getVizHandler();

	/**
	 * This Option annotation corresponds to the '--petscArgs' option which
	 * defines the default value to be the single string of Petsc arguments and
	 * additionally provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The single string of PETSc arguments that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "-ts_final_time 1.0 -ts_dt 1.0e-12 "
			+ "-ts_max_steps 100 -ts_adapt_dt_max 1.0e-6 -ts_max_snes_failures 200 "
			+ "-pc_type fieldsplit -pc_fieldsplit_detect_coupling -fieldsplit_0_pc_type sor "
			+ "-fieldsplit_1_pc_type redundant -ts_monitor -ts_exact_final_time stepover", description = "List of arguments to be passed to PETSc")
	/**
	 * This operation produces the required command line option '--petscArgs'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The single string of PETSc arguments
	 */
	String getPetscArgs();

	/**
	 * This Option annotation corresponds to the '--networkFile' option which
	 * defines a default network file name of networkInit.h5 and additionally
	 * provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default network file name that will be used if this option
	 *            is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "networkInit.h5", description = "<fileName>  The HDF5 file containing the network (default = networkInit.h5)")
	/**
	 * This operation produces the required command line option '--networkFile'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The name of the network file
	 */
	String getNetworkFile();

	/**
	 * This Option annotation corresponds to the '--dimensions' option which
	 * defines a default 1D and additionally provides a brief description of the
	 * option.
	 * 
	 * @param defaultValue
	 *            The default number of dimensions that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "1", description = "<dimensionNumber> The number of dimensions for the simulation (default = 1)")
	/**
	 * This operation produces the required command line option '--dimensions'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The number of dimensions
	 */
	String getDimensions();

	/**
	 * This Option annotation corresponds to the '--nxGrid' option which defines
	 * a default number of grid points in the x directions and additionally
	 * provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default number of grid points that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "20", description = "<nxGrid> The number of grid points in the x direction "
			+ "(default = 20)")
	/**
	 * This operation produces the required command line option '--nxGrid' which
	 * takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The number of grid points in the x direction
	 */
	int getNxGrid();

	/**
	 * This Option annotation corresponds to the '--nyGrid' option which defines
	 * a default number of grid points in the y directions and additionally
	 * provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default number of grid points that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "0", description = "<nyGrid> The number of grid points in the y direction "
			+ "(default = 0)")
	/**
	 * This operation produces the required command line option '--nyGrid' which
	 * takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The number of grid points in the y direction
	 */
	int getNyGrid();

	/**
	 * This Option annotation corresponds to the '--nzGrid' option which defines
	 * a default number of grid points in the z directions and additionally
	 * provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default number of grid points that will be used if this
	 *            option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "0", description = "<nzGrid> The number of grid points in the z direction "
			+ "(default = 0)")
	/**
	 * This operation produces the required command line option '--nzGrid' which
	 * takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The number of grid points in the z direction
	 */
	int getNzGrid();

	/**
	 * This Option annotation corresponds to the '--xStepSize' option which
	 * defines a default step size in the x direction and additionally provides
	 * a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default step size that will be used if this option is not
	 *            specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "1.0", description = "<value>  The value of the step size in the x direction"
			+ " in nm (default = 1.0)")
	/**
	 * This operation produces the required command line option '--xStepSize'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The value of the step size
	 */
	double getXStepSize();

	/**
	 * This Option annotation corresponds to the '--yStepSize' option which
	 * defines a default step size in the y direction and additionally provides
	 * a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default step size that will be used if this option is not
	 *            specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "0.0", description = "<value>  The value of the step size in the y direction"
			+ " in nm (default = 0.0)")
	/**
	 * This operation produces the required command line option '--yStepSize'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The value of the step size
	 */
	double getYStepSize();

	/**
	 * This Option annotation corresponds to the '--zStepSize' option which
	 * defines a default step size in the z direction and additionally provides
	 * a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The default step size that will be used if this option is not
	 *            specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "0.0", description = "<value>  The value of the step size in the z direction"
			+ " in nm (default = 0.0)")
	/**
	 * This operation produces the required command line option '--zStepSize'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The value of the step size
	 */
	double getZStepSize();

	/**
	 * This Option annotation corresponds to the '--material' option and
	 * provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "W100", description = "{W100, W110, W111, W211, Fuel} "
			+ "The option declaring which material will be used "
			+ "(W is for tungsten and the numbers correspond to the surface orientation)")
	/**
	 * This operation produces the optional command line option '--material'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The material
	 */
	String getMaterial();

	/**
	 * This Option annotation corresponds to the '--process' option which
	 * defines the default value to be the single string of physical processes
	 * and additionally provides a brief description of the option.
	 * 
	 * @param defaultValue
	 *            The single string of physical processes that will be used if
	 *            this option is not specified via the command line
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "reaction diff advec", description = "List of physical processes for the simulation "
			+ "(reaction, diff, advec, modifiedTM, movingSurface, bursting, attenuation)")
	/**
	 * This operation produces the required command line option '--process'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The single string of processes
	 */
	String getProcess();

	/**
	 * This Option annotation corresponds to the '--flux' option and provides a
	 * brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(defaultValue = "4.0e7", description = "This option allows the user to change the flux by "
			+ "the factor specified (in nm).")

	/**
	 * This operation produces the optional command line option '--heFlux' which
	 * takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The flux amplitude
	 */
	String getFlux();

	/**
	 * This Option annotation corresponds to the optional '--tempFile' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "<tempFileName>  A temperature profile is given "
			+ "by the specified file, then linear interpolation is used to fit the data")
	/**
	 * This operation produces the optional command line option '--tempFile'
	 * which takes a single string value and is defined by the previous Option
	 * annotation. NOTE: This option should only be used when the user wishes to
	 * pass a file containing a temperature profile to Xolotl.
	 * 
	 * @return The name of the temperature file
	 */
	String getTempFile();

	/**
	 * This operation makes the command line option '--tempFile' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isTempFile();

	/**
	 * This Option annotation corresponds to the optional '--heat' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "<surfaceTemp> <bulkTemp> Two temperatures are given "
			+ "to then solve the heat equation")
	/**
	 * This operation produces the optional command line option '--heat'
	 * which takes a single string value and is defined by the previous Option
	 * annotation. NOTE: This option should only be used when the user wishes to
	 * use heat equation in Xolotl.
	 * 
	 * @return The string of temperatures
	 */
	String getHeat();

	/**
	 * This operation makes the command line option '--heat' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isHeat();

	/**
	 * This Option annotation corresponds to the optional '--fluxFile' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "<fluxFileName>  A time profile is given for the flux "
			+ "by the specified file, then linear interpolation is used to fit the data")
	/**
	 * This operation produces the optional command line option '--fluxFile'
	 * which takes a single string value and is defined by the previous Option
	 * annotation. NOTE: This option should only be used when the user wishes to
	 * pass a file containing a time profile profile for the flux to Xolotl.
	 * 
	 * @return The name of the flux file
	 */
	String getFluxFile();

	/**
	 * This operation makes the command line option '--fluxFile' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isFluxFile();

	/**
	 * This Option annotation corresponds to the optional '--checkpoint' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "<HDF5FileName>  Start the solver with the concentrations, time, "
			+ "and step size present in the HDF5 file")
	/**
	 * This operation produces the optional command line option '--checkpoint'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The name of the file to read from to create the new HDF5 network
	 *         file
	 */
	String getCheckpoint();

	/**
	 * This operation makes the command line option '--checkpoint' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isCheckpoint();

	/**
	 * This Option annotation corresponds to the optional '--voidPortion' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "The portion of the grid (in %) that won't be material at "
			+ "the start of the simulation. It is room for the surface to grow.")

	/**
	 * This operation produces the optional command line option '--voidPortion'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The portion of the grid that is NOT the material
	 */
	String getVoidPortion();

	/**
	 * This operation makes the command line option '--voidPortion' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isVoidPortion();

	/**
	 * This Option annotation corresponds to the optional '--initialV' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "The initial concentration of vacancies in the material (in #/nm3) " + "that will be used.")

	/**
	 * This operation produces the optional command line option '--initialV'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The initial vacancy concentration of the material
	 */
	String getInitialV();

	/**
	 * This operation makes the command line option '--initialV' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isInitialV();

	/**
	 * This Option annotation corresponds to the optional '--regularGrid' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "If the user wants to use a regular grid in the x direction or not.")

	/**
	 * This operation produces the optional command line option '--regularGrid'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return If the user wants to use a regular grid
	 */
	String getRegularGrid();

	/**
	 * This operation makes the command line option '--regularGrid' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isRegularGrid();

	/**
	 * This Option annotation corresponds to the optional '--grain' option
	 * provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "List of arguments for the grain boundaries. "
			+ "For instance Y 3.0 means that there will a GB in the Y direction at 3.0 nm.")

	/**
	 * This operation produces the optional command line option '--grain' which
	 * takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The single string of grain boundaries
	 */
	String getGrain();

	/**
	 * This operation makes the command line option '--grain' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isGrain();

	/**
	 * This Option annotation corresponds to the optional '--sputter' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "The sputtering yield (in atoms/ion) that will be used.")

	/**
	 * This operation produces the optional command line option '--sputter'
	 * which takes a single string value and is defined by the previous Option
	 * annotation
	 * 
	 * @return The sputtering yield of the material
	 */
	String getSputter();

	/**
	 * This operation makes the command line option '--sputter' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isSputter();

	/**
	 * This Option annotation corresponds to the optional '--netParam' option
	 * and provides a brief description of the option.
	 * 
	 * @param description
	 *            Brief description of this option
	 */
	@Option(description = "The network parameters will be written instead of creating the HDF5 file.")

	/**
	 * This operation makes the command line option '--netParam' optional.
	 * 
	 * @return Returns true if the option has been specified and false if it has
	 *         not
	 */
	boolean isNetParam();

	/**
	 * This produces the command line arguments '--help' or '-h' either of which
	 * can be used to print usage help
	 * 
	 * @return True if the help message has been requested or false if it has
	 *         not
	 */
	@Option(helpRequest = true, description = "display help", shortName = "h")
	boolean getHelp();

}
=======
=======
 * 
 * Each Option is constructed with a name (longName), a default value, and a
 * help description. E.g.
 * 
 * @Option(longName="heFlux", defaultValue = "2.5e27", description =
 *                            "The Helium insertion flux") The above example
 *                            creates the command line option '--heFlux'. If
 *                            this option is not specified, then the default
 *                            value is used.
 * 
 */
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
public interface Arguments {

	@Option(longName = "material", // defaultValue = "W",
			description = "{W, Fe}  Which material will be used, Tungsten or Iron")
	String getMaterial();

	// Makes this option optional because this functionality has not yet been
	// merged into the trunk
	boolean isMaterial();

	@Option(longName = "startTemp", // defaultValue = "1000",
			description = "The temperature (in Kelvin) will be the constant"
			+ "value specified")
	String getStartTemp();

	// Makes this option optional because this functionality has not yet been
	// merged into the trunk
	boolean isStartTemp();

	// The tempFile option is optional and should only be used when the user
	// wishes to pass a file containing a temperature profile to Xolotl
	@Option(longName = "tempFile", 
			description = "<tempFileName>  A temperature profile is given "
			+ "by the specified file, then linear interpolation is used to fit the data")
	String getTempFile();
	
	boolean isTempFile();

	@Option(longName = "heFlux", // defaultValue = "2.5e27",
			description = "The Helium insertion flux")
	String getHeFlux();

	// Makes this option optional because this functionality has not yet been
	// merged into the trunk
	boolean isHeFlux();

	@Option(longName = "heFluence", // defaultValue = "1.0e19",
			description = "The Helium fluence value that will be used")
	String getHeFluence();

	// Makes this option optional because this functionality has not yet been
	// merged into the trunk
	boolean isHeFluence();

	@Option(longName = "perfHandler", defaultValue = "dummy", 
			description = "{dummy, std}  Which set of performance handlers to use")
	String getPerfHandler();

	@Option(longName = "vizHandler", // defaultValue = "dummy",
			description = "{dummy, std}  Which set of visualization handlers to use")
	String getVizHandler();

	// Makes this option optional because this functionality has not yet been
	// merged into the trunk
	boolean isVizHandler();

	// TODO make this a List<String>?
	@Option(longName = "petscArgs", defaultValue = "-da_grid_x 10 -ts_final_time 1000 "
			+ "-ts_max_steps 3 -ts_adapt_dt_max 10 -ts_max_snes_failures 200 "
			+ "-pc_type fieldsplit -pc_fieldsplit_detect_coupling -fieldsplit_0_pc_type redundant "
			+ "-fieldsplit_1_pc_type sor -snes_monitor -ksp_monitor -ts_monitor", 
			description = "List of arguments to be passed to PETSc")
	String getPetscArgs();

	@Option(longName = "networkFile", defaultValue = "networkInit.h5", 
			description = "<fileName>  The HDF5 file containing the network")
	String getNetworkFile();

	@Option(longName = "checkpoint", // defaultValue = "false",
			description = "{true, false}  Start the solver with the concentrations, time, "
			+ "and step size from the HDF5 file")
	String getCheckpoint();

	// Makes this option optional because this functionality is currently being
	// taken care of in the HDF5 file
	boolean isCheckpoint();

	// Print usage help
	@Option(helpRequest = true, description = "display help", shortName = "h")
	boolean getHelp();

}
>>>>>>> Pulling the trunk into the HDF5 branch to make it easier to merge back later. SB 20140618
