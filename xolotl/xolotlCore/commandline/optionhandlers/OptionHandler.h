#ifndef OPTIONHANDLER_H
#define OPTIONHANDLER_H

// Includes
#include "IOptionHandler.h"

namespace xolotlCore {

/**
 * OptionHandler realizes the IOptionHandler interface.
 * There will be an implementation for each different option.
 */
<<<<<<< HEAD
class OptionHandler : public IOptionHandler {
=======
class OptionHandler: public IOptionHandler {
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a
protected:

	/**
	 * The default constructor
	 */
<<<<<<< HEAD
    OptionHandler();

=======
	OptionHandler();
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

public:

	/**
	 * The constructor to use.
	 * @param keyName The name for the key.
	 * @param msg The help message.
	 */
<<<<<<< HEAD
    OptionHandler(const std::string& keyName, const std::string& msg) {
    	key = keyName;
    	helpMessage = msg;
    }
=======
	OptionHandler(const std::string& keyName, const std::string& msg) {
		key = keyName;
		helpMessage = msg;
	}
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

	/**
	 * The destructor
	 */
<<<<<<< HEAD
    ~OptionHandler() {}

    /**
     * The function that will handle the specific option.
     * Every subclass will have to implement this function.
     *
     * @param opt The pointer to the option that will be modified.
     * @param arg The argument for the option.
     */
    virtual bool handler(IOptions *opt, const std::string& arg) {return false;}

};//end class OptionHandler
=======
	~OptionHandler() {
	}

	/**
	 * The function that will handle the specific option.
	 * Every subclass will have to implement this function.
	 *
	 * @param opt The pointer to the option that will be modified.
	 * @param arg The argument for the option.
	 */
	virtual bool handler(IOptions * opt, const std::string& arg) {
		return false;
	}

};
//end class OptionHandler
>>>>>>> f67313bf226aed355571bfbfe00456ece9e8a58a

} /* namespace xolotlCore */

#endif
