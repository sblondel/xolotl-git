#include <cassert>
#include <memory>
#include <iostream>
#include <sstream>
#include <TokenizedLineReader.h>
#include "XolotlOptions.h"

namespace xolotlCore {


XolotlOptions::XolotlOptions( void )
  : usePerfStdHandlers( true ),  // by default, use "standard" handlers for performance
    useVizStdHandlers( false ) // and "dummy" handlers for visualization
{
    // Add our notion of which options we support.
    optionsMap["networkFile"] = new OptInfo(
        "networkFile                 The network will be loaded from this file.",
        handleNetworkOptionCB );
    optionsMap["perfHandler"] = new OptInfo(
        "perfHandler {std,dummy}     Which set of handlers to use for the performances.",
        handlePerfHandlersOptionCB );
    optionsMap["vizHandler"] = new OptInfo(
        "vizHandler {std,dummy}      Which set of handlers to use for the visualization.",
        handleVizHandlersOptionCB );
    optionsMap["petscArgs"] = new OptInfo(
        "petscArgs                   All the arguments that will be given to PETSc",
        handlePetscOptionCB );
}


void
XolotlOptions::readParams( int argc, char* argv[] )
{
	// Check if we were given at least our positional arguments.
    if( argc < 1 )
    {
        std::cerr << "Insufficient input provided! Aborting!" << std::endl;
        showHelp( std::cerr );
        shouldRunFlag = false;
        exitCode = EXIT_FAILURE;

        return;
    }
    else
    {
        // Try to interpret first argument as the parameters file name.
        // If it starts with a dash, it's probably not.
        // But it is a common thing to try to get help by passing
        // only a help flag, so we check for that special case.
        std::string currArg = argv[0];
        if( currArg == "--help" )
        {
        	// Print the help message asked by the user
        	showHelp( std::cout );
            shouldRunFlag = false;
        }
        else if( currArg[0] == '-' )
        {
            // this looks like an option, not the required filename.
            std::cerr << "No parameter file provided.  Aborting!" << std::endl;
            showHelp( std::cerr );
            shouldRunFlag = false;
            exitCode = EXIT_FAILURE;

            return;
        }
        else
        {
            // Let the base Options class handle our options.
            Options::readParams(argc, argv);
        }
    }

    return;
}


void
XolotlOptions::showHelp( std::ostream& os ) const
{
    os << "usage: xolotl param_file_name \n\n"
        << "See the Xolotl documentation for PETSc options. \n"
        << "param_file_name should contain:"
        << std::endl;
    Options::showHelp( os );
}


bool
XolotlOptions::handleNetworkOption( std::string arg )
{
    bool ret = true;

    // The base class should check for situations where
    // we expect an argument but don't get one.
    assert( !arg.empty() );

    // Set the name of the network file
    networkFileName = arg;

    return ret;
}

bool
XolotlOptions::handleNetworkOptionCB( Options* opts, std::string arg )
{
    return static_cast<XolotlOptions*>( opts )->handleNetworkOption( arg );
}


bool
XolotlOptions::handlePerfHandlersOption( std::string arg )
{
    bool ret = true;

    // The base class should check for situations where
    // we expect an argument but don't get one.
    assert( !arg.empty() );

    // Determine the type of handlers we are being asked to use
    if( arg == "std" )
    {
        usePerfStdHandlers = true;
    }
    else if( arg == "dummy" )
    {
        usePerfStdHandlers = false;
    }
    else
    {
        std::cerr << "Options: unrecognized argument " << arg << std::endl;
        showHelp( std::cerr );
        shouldRunFlag = false;
        exitCode = EXIT_FAILURE;
        ret = false;
    }

    return ret;
}

bool
XolotlOptions::handlePerfHandlersOptionCB( Options* opts, std::string arg )
{
    return static_cast<XolotlOptions*>( opts )->handlePerfHandlersOption( arg );
}


bool
XolotlOptions::handleVizHandlersOption( std::string arg )
{
    bool ret = true;

    // The base class should check for situations where
    // we expect an argument but don't get one.
    assert( !arg.empty() );

    // Determine the type of handlers we are being asked to use
    if( arg == "std" )
    {
        useVizStdHandlers = true;
    }
    else if( arg == "dummy" )
    {
        useVizStdHandlers = false;
    }
    else
    {
        std::cerr << "Options: unrecognized argument " << arg << std::endl;
        showHelp( std::cerr );
        shouldRunFlag = false;
        exitCode = EXIT_FAILURE;
        ret = false;
    }

    return ret;
}

bool
XolotlOptions::handleVizHandlersOptionCB( Options* opts, std::string arg )
{
    return static_cast<XolotlOptions*>( opts )->handleVizHandlersOption( arg );
}


bool
XolotlOptions::handlePetscOption( std::string arg )
{
    bool ret = true;
    assert( !arg.empty() );

	// Local Declarations
	TokenizedLineReader<std::string> reader;

	// Load the stream from the argument
	auto argSS = std::make_shared<std::stringstream>();
	(*argSS) << arg;

	reader.setInputStream(argSS);

	// Find out the number of strings in the argument
	auto line = reader.loadLine();

	// Set the PETSc options
	petscArgc = line.size();
	// Construct the PETSc argv
	// Have to create the vectors with new() to be sure that petscArgv won't be overwritten later
	std::istringstream ss(arg);
	std::string tmp;
	std::vector<std::string> *tmpStr = new std::vector<std::string>();
	std::vector<char*> *tmpArgv = new std::vector<char*>();
	while (ss >> tmp)
	{
	   (*tmpStr).push_back(tmp);
	   (*tmpArgv).push_back(const_cast<char*>((*tmpStr).back().c_str()));
	}
	// null pointer to terminate
	(*tmpArgv).push_back(0);

	petscArgv = &(*tmpArgv)[0];

    return ret;
}


bool
XolotlOptions::handlePetscOptionCB( Options* opts, std::string arg )
{
    return static_cast<XolotlOptions*>( opts )->handlePetscOption( arg );
}

}; // end namespace xolotlCore


