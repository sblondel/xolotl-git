#ifndef GROUPINGOPTIONHANDLER_H
#define GROUPINGOPTIONHANDLER_H

// Includes
#include "OptionHandler.h"

namespace xolotlCore {

/**
 * GroupingOptionHandler handles the grouping scheme options.
 */
class GroupingOptionHandler: public OptionHandler {
public:

	/**
	 * The default constructor
	 */
	GroupingOptionHandler() :
			OptionHandler("grouping",
					"grouping <vMin> <heWidth> <vWidth>               "
					"This option allows the use a grouping scheme starting at the HeV cluster "
					"with 'vMin' V clusters and with the given widths.  \n") {
	}

	/**
	 * The destructor
	 */
	~GroupingOptionHandler() {
	}

	/**
	 * This method will set the IOptions materialFlag and materialName
	 * to the value given as the argument.
	 *
	 * @param opt The pointer to the option that will be modified.
	 * @param arg The options for the grouping scheme.
	 */
	bool handler(IOptions *opt, const std::string& arg) {
		// Build an input stream from the argument
		xolotlCore::TokenizedLineReader<std::string> reader;
		auto argSS = std::make_shared < std::istringstream > (arg);
		reader.setInputStream(argSS);
		// Break the string into tokens.
		auto tokens = reader.loadLine();

		// Set grouping minimum size
		opt->setGroupingVMin(strtol(tokens[0].c_str(), NULL, 10));
		// Set the grouping widths
		opt->setGroupingHeWidth(strtol(tokens[1].c_str(), NULL, 10));
		opt->setGroupingVWidth(strtol(tokens[2].c_str(), NULL, 10));

		return true;
	}

};
//end class GroupingOptionHandler

} /* namespace xolotlCore */

#endif