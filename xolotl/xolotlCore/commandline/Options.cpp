<<<<<<< HEAD
#include <cassert>
#include <limits>
#include <fstream>
#include <TokenizedLineReader.h>
#include <NetworkOptionHandler.h>
#include <PetscOptionHandler.h>
#include <ConstTempOptionHandler.h>
#include <TempProfileOptionHandler.h>
#include <HeatOptionHandler.h>
#include <FluxOptionHandler.h>
#include <FluxProfileOptionHandler.h>
#include <PerfOptionHandler.h>
#include <VizOptionHandler.h>
#include <MaterialOptionHandler.h>
#include <VConcentrationOptionHandler.h>
#include <VoidPortionOptionHandler.h>
#include <DimensionsOptionHandler.h>
#include <RegularGridOptionHandler.h>
#include <ProcessOptionHandler.h>
#include <GrainBoundariesOptionHandler.h>
#include <GroupingOptionHandler.h>
#include <SputteringOptionHandler.h>
#include <NetworkParamOptionHandler.h>
#include <GridParamOptionHandler.h>
#include "Options.h"

namespace xolotlCore {

Options::Options() :
		shouldRunFlag(true),
		exitCode(EXIT_SUCCESS),
		petscArgc(0),
		petscArgv(NULL),
		networkFilename(""),
		constTempFlag(false),
		constTemperature(1000.0),
		temperatureGradient(0.0),
		tempProfileFlag(false),
		tempProfileFilename(""),
		heatFlag(false),
		bulkTemperature(0.0),
		fluxFlag(false),
		fluxAmplitude(0.0),
		fluxProfileFlag(false),
		perfRegistryType(xolotlPerf::IHandlerRegistry::std),
		vizStandardHandlersFlag(false),
		materialName(""),
		initialVConcentration(0.0),
		voidPortion(50.0),
		dimensionNumber(1),
		useRegularGridFlag(true), 
		gbList(""),
		groupingMin(std::numeric_limits<int>::max()),
		groupingWidthA(1),
		groupingWidthB(1),
		sputteringYield(0.0),
		useHDF5Flag(true),
		usePhaseCutFlag(false),
		maxImpurity(8), maxV(20), maxI(6),
		nX(10), nY(0), nZ(0),
		xStepSize(0.5), yStepSize(0.0), zStepSize(0.0) {

	// Create the network option handler
	auto networkHandler = new NetworkOptionHandler();
	// Create the PETSc option handler
	auto petscHandler = new PetscOptionHandler();
	// Create the constant temperature option handler
	auto constTempHandler = new ConstTempOptionHandler();
	// Create the temperature profile option handler
	auto tempProfileHandler = new TempProfileOptionHandler();
	// Create the heat equation option handler
	auto heatHandler = new HeatOptionHandler();
	// Create the flux option handler
	auto fluxHandler = new FluxOptionHandler();
	// Create the flux time profile option handler
	auto fluxProfileHandler = new FluxProfileOptionHandler();
	// Create the performance handler option handler
	auto perfHandler = new PerfOptionHandler();
	// Create the visualization handler option handler
	auto vizHandler = new VizOptionHandler();
	// Create the material option handler
	auto materialHandler = new MaterialOptionHandler();
	// Create the initial vacancy concentration option handler
	auto vConcHandler = new VConcentrationOptionHandler();
	// Create the void portion option handler
	auto voidHandler = new VoidPortionOptionHandler();
	// Create the dimensions option handler
	auto dimHandler = new DimensionsOptionHandler();
	// Create the regular grid option handler
	auto gridHandler = new RegularGridOptionHandler();
	// Create the physical processes option handler
	auto procHandler = new ProcessOptionHandler();
	// Create the GB option handler
	auto gbHandler = new GrainBoundariesOptionHandler();
	// Create the grouping option handler
	auto groupingHandler = new GroupingOptionHandler();
	// Create the sputtering option handler
	auto sputteringHandler = new SputteringOptionHandler();
	// Create the network param option handler
	auto netParamHandler = new NetworkParamOptionHandler();
	// Create the grid option handler
	auto gridParamHandler = new GridParamOptionHandler();

	// Add our notion of which options we support.
	optionsMap[networkHandler->key] = networkHandler;
	optionsMap[petscHandler->key] = petscHandler;
	optionsMap[constTempHandler->key] = constTempHandler;
	optionsMap[tempProfileHandler->key] = tempProfileHandler;
	optionsMap[heatHandler->key] = heatHandler;
	optionsMap[fluxHandler->key] = fluxHandler;
	optionsMap[fluxProfileHandler->key] = fluxProfileHandler;
	optionsMap[perfHandler->key] = perfHandler;
	optionsMap[vizHandler->key] = vizHandler;
	optionsMap[materialHandler->key] = materialHandler;
	optionsMap[vConcHandler->key] = vConcHandler;
	optionsMap[voidHandler->key] = voidHandler;
	optionsMap[dimHandler->key] = dimHandler;
	optionsMap[gridHandler->key] = gridHandler;
	optionsMap[procHandler->key] = procHandler;
	optionsMap[gbHandler->key] = gbHandler;
	optionsMap[groupingHandler->key] = groupingHandler;
	optionsMap[sputteringHandler->key] = sputteringHandler;
	optionsMap[netParamHandler->key] = netParamHandler;
	optionsMap[gridParamHandler->key] = gridParamHandler;
}

Options::~Options(void) {
	// Release the items in our map of potential options.
	for (auto iter = optionsMap.begin(); iter != optionsMap.end(); ++iter) {
		auto currOpt = iter->second;
		delete currOpt;
	}
	optionsMap.clear();

	// release the dynamically-allocated PETSc arguments
	for (int i = 0; i < petscArgc; ++i) {
		delete[] petscArgv[i];
	}
	delete[] petscArgv;
	petscArgv = NULL;
}

void Options::readParams(char* argv[]) {
	// All the options are read from an ASCII file that is parsed
	// with the TokenizedLineReader.
	// We assume that the name of this file is the first and only
	// argument.

	// Load the content of the file in a stream
	// Create the param stream
	std::shared_ptr<std::ifstream> paramStream;
	paramStream = std::make_shared < std::ifstream > (argv[0]);

	if (!paramStream->good()) {
		// The file is empty.
		std::cerr << "The parameter file is empty. Aborting!" << std::endl;
		showHelp(std::cerr);
		shouldRunFlag = false;
		exitCode = EXIT_FAILURE;

		return;
	}

	// Declare the TokenizedLineReader to read the lines
	xolotlCore::TokenizedLineReader<std::string> reader;
	reader.setInputStream(paramStream);
	// Set the delimiter to "="
	reader.setDelimiter("=");

	// Load the first line
	auto line = reader.loadLine();
	// And start looping on the lines
	while (line.size() > 0) {
		auto iter = optionsMap.find(line[0]);
		// If the option is found
		if (iter != optionsMap.end()) {
			// Call the option's handler
			auto currOpt = iter->second;
			if (currOpt == nullptr) {
				// Something went wrong.
				std::cerr
						<< "\nOption: No handler associated to the option: "
						<< line[0] << " !"
						<< std::endl;
				shouldRunFlag = false;
				exitCode = EXIT_FAILURE;
				break;
			}
			// Continue to read if everything went well with the current option
			bool continueReading = currOpt->handler(this, line[1]);

			if (!continueReading) {
				// Something went wrong.
				std::cerr
						<< "\nOption: Something went wrong while setting the options."
						<< std::endl;
				shouldRunFlag = false;
				exitCode = EXIT_FAILURE;
				break;
			}
		}

		else {
			// We did not recognize the option.
			std::cerr
					<< "\nOption: Unrecognized option in the parameter file:  "
					<< line[0] << "\n" << std::endl;
			showHelp(std::cerr);
			shouldRunFlag = false;
			exitCode = EXIT_FAILURE;
			break;
		}

		line = reader.loadLine();
	}

	return;
}

void Options::showHelp(std::ostream& os) const {
	os << "Usage: xolotl param_file_name \n\n"
			<< "See the Xolotl documentation for PETSc options. \n"
			<< "Supported options:\n";

	// Loop on each option help message
	for (OptionsMap::const_iterator iter = optionsMap.begin();
			iter != optionsMap.end(); ++iter) {
		os << "  " << iter->second->helpMessage << '\n';
	}
	os << std::endl;
}

} // end namespace xolotlCore
=======
#include <string>
#include <cassert>
#include "xolotlCore/commandline/Options.h"


namespace xolotlCore {


Options::Options( void )
  : shouldRunFlag( true ),
    exitCode( EXIT_SUCCESS )
{
    // Construct our notion of which options we support.
    optionsMap["--help"] = new OptInfo( false,
        "--help                     Show this help message.",
        Options::handleHelpOptionCB );
}


Options::~Options( void )
{
    // Release the items in our map of potential options.
    for( auto iter = optionsMap.begin(); iter != optionsMap.end(); iter++ )
    {
        OptInfo* currOptInfo = iter->second;
        delete currOptInfo;
    }
    optionsMap.clear();
}



void
Options::showHelp( std::ostream& os ) const
{
    os << "Supported options:\n";

    for( OptionsMap::const_iterator iter = optionsMap.begin(); iter != optionsMap.end(); iter++ )
    {
        os << "  " << iter->second->helpMessage << '\n';
    }
    os << std::endl;
}


int
Options::parseCommandLine( int argc, char* argv[] )
{
    // We are not using any command line parsing library,
    // so our parsing approach is a fairly brute force one.
    // 
    // We expect the command line to contain lots of options
    // that do not pertain to us (e.g., PETSc options).  But
    // we expect that those options will come after an 
    // option that tells us our options are done.
    unsigned int i = 0;
    while( i < argc )
    {
        std::string currArg = argv[i++];

        auto iter = optionsMap.find( currArg );
        if( iter != optionsMap.end() )
        {
            // We recognized the option.
            // Call the option's handler.
            OptInfo* currOptInfo = iter->second;
            assert( currOptInfo != NULL );

            std::string optArg;
            if( currOptInfo->argRequired )
            {
                if( i < argc )
                {
                    optArg = argv[i++];
                }
                else
                {
                    std::cerr << "Option: required argument missing for " << currArg << std::endl;
                    shouldRunFlag = false;
                    exitCode = EXIT_FAILURE;
                    break;
                }
            }
            bool continueParsing = (*currOptInfo->optHandler)( this, optArg );
            if( !continueParsing )
            {
                break;
            }
        }
        else
        {
            // We did not recognize the option.
            std::cerr << "Option: unrecognized option " << currArg << std::endl;
            shouldRunFlag = false;
            exitCode = EXIT_FAILURE;
            break;
        }
    }

    return i;
}


//
// Methods for handling specific options we support.
//

bool
Options::handleHelpOption( std::string arg )
{
    // Show the help message to standard output (since it
    // was requested via command line switch).
    showHelp( std::cout );

    // Indicate that the program shouldn't try to run.
    shouldRunFlag = false;

    // Stop parsing.
    return false;
}


bool
Options::handleHelpOptionCB( Options* opts, std::string arg )
{
    return opts->handleHelpOption( arg );
}

}; // end namespace xolotlCore


>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
