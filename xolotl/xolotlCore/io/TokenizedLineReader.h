#ifndef TOKENIZEDLINEREADER_H
#define TOKENIZEDLINEREADER_H

// Includes
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include <vector>
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
#include <vector>
>>>>>>> Merged the preprocessor branch into the HDF5 branch. SB 20140624
=======
#include <vector>
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
#include <memory>
#include <iostream>
#include <sstream>

namespace xolotlCore {

/**
 * This is a simple class for parsing lines from an input stream and
 * splitting that line to retrieve delimiters. A line in this case is defined as any
 * sequence of characters that terminates with an end-of-line character such
 * as \r, \n or \r\n. The default delimiter is a single space and the delimiter can be
 * changed by calling the setDelimiter() operation. Delimiters found at the beginning
 * and end of the lines are removed. Lines that are meant to be
 * comments will be skipped and this includes lines that start with a "#" by
 * default. The comment delimiter can be changed by calling setCommentDelimiter().
 * "In-line comments" where the comment starts at some later point in the line
 * are not allowed and will be parsed as data. This class is templated so
 * that conversion to primitive types can be handled automatically for the
 * client class. This class is only meant to be templated with primitive types
 * and it will fail for classes or interfaces.
 */
template<class dataType>
class TokenizedLineReader {

private:

	//!The delimiter or "delimiter" that separates elements in the line.
	std::string dataDelimiter;

	//!The character that represents a line that is a comment and should not be parsed.
	std::string commentDelimiter;

	//!The inputstream from which data should be read.
	std::shared_ptr<std::istream> inputstream;

<<<<<<< HEAD
<<<<<<< HEAD
	/**
	 * This operation load the subline into the data when the dataType is a string.
	 * This function is different from the other ones that overriding it for it to work
	 * when the data delimiter is different than the space but some of the strings
	 * are still separated by a space. For instance, loadData("one two", data);
	 * will load "one two" in data and not just "one".
	 *
	 * See the last test of the TokenizedLineReaderTester to see the use of this function.
	 *
	 * @param subline the subline to load in the data.
	 * @param data the reference to the data to be loaded.
	 */
	static void loadData(const std::string& subline, std::string &data) {
		data = subline;

		return;
	}

	/**
	 * This operation load the subline into the data when the dataType is a char.
	 *
	 * @param subline the subline to load in the data.
	 * @param data the reference to the data to be loaded.
	 */
	static void loadData(const std::string& subline, char &data) {
		std::istringstream dataStream;
		dataStream.str(subline);
		dataStream >> data;

		return;
	}

	/**
	 * This operation load the subline into the data when the dataType is a bool.
	 *
	 * @param subline the subline to load in the data.
	 * @param data the reference to the data to be loaded.
	 */
	static void loadData(const std::string& subline, bool &data) {
		std::istringstream dataStream;
		dataStream.str(subline);
		dataStream >> data;

		return;
	}

	/**
	 * This operation load the subline into the data when the dataType is a double.
	 *
	 * @param subline the subline to load in the data.
	 * @param data the reference to the data to be loaded.
	 */
	static void loadData(const std::string& subline, double &data) {
		std::istringstream dataStream;
		dataStream.str(subline);
		dataStream >> data;

		return;
	}

	/**
	 * This operation load the subline into the data when the dataType is a int.
	 *
	 * @param subline the subline to load in the data.
	 * @param data the reference to the data to be loaded.
	 */
	static void loadData(const std::string& subline, int &data) {
		std::istringstream dataStream;
		dataStream.str(subline);
		dataStream >> data;

		return;
	}

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
public:

	//!The constructor
	TokenizedLineReader() :
			dataDelimiter(" "), commentDelimiter("#") {
	}

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * This operation sets the string (delimiter) that represents the delimiter
	 * separating the different data elements in the line.
	 *
	 * @param delimiter The delimiter
	 */
	void setDelimiter(const std::string& delimiter) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * This operation sets the string (delimiter) that represents the delimiter separating the different data elements in the line.
	 *
	 */
	void setDelimiter(std::string delimiter) {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

		dataDelimiter = delimiter;

		return;
	}

	/**
<<<<<<< HEAD
<<<<<<< HEAD
	 * This operation sets the character that represents the comment character.
	 *
	 * @param cdelimiter The comment delimiter
	 *
	 */
	void setCommentDelimiter(const std::string& cdelimiter) {
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 * This operation sets the character (delimiter) that represents the comment character.
	 *
	 */
	void setCommentDelimiter(std::string cdelimiter) {
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

		commentDelimiter = cdelimiter;

		return;
	}

	/**
	 * This operation sets the input stream that should be parsed.
<<<<<<< HEAD
<<<<<<< HEAD
	 *
	 * @param stream The input stream
=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
	 */
	void setInputStream(std::shared_ptr<std::istream> stream) {
		inputstream = stream;
		return;
	}

	/**
	 * This operation loads the next line from the stream and returns an array
	 * of its elements by splitting on the delimiter or a vector of size zero
	 * if there are no more lines in the stream.
	 */
	std::vector<dataType> loadLine() {
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======

>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
		// Local Declarations
		size_t lastDelimiterPos = 0, nextDelimiterPos = 0, finalDelimiterPos =
				std::string::npos;
		std::vector<dataType> dataVector;
		std::string subLine;
		std::istringstream dataStream;
		dataType data;

		// Check the inputstream before reading from it
		if (!inputstream->eof() && inputstream->good()) {
			// Get the line
			std::string line;
			std::getline(*inputstream, line);
<<<<<<< HEAD
<<<<<<< HEAD

			// Handle the case where there is a carriage return (\r) before
			// the newline (\n)
			if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
			// Split it if it is not empty and does not start with the comment
			// character
			if (!line.empty()) {
				// If this line is a comment, skip it by calling this operation
				// again - FIXME! - Update compiler to support C++11 and use
				// std::string.front()!
				if (line.find(commentDelimiter) == 0)
					return loadLine();
<<<<<<< HEAD
<<<<<<< HEAD

				// Remove delimiters at the beginning of the string
				if (line.find(dataDelimiter) == 0)
					line = line.substr(1);

=======
				// Remove delimiters at the beginning of the string
				if (line.find(dataDelimiter) == 0)
					line = line.substr(1);
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
				// Remove delimiters at the beginning of the string
				if (line.find(dataDelimiter) == 0)
					line = line.substr(1);
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
				// Remove delimiters at the end of the string
				if (line.find(dataDelimiter, line.size() - 2)
						== line.size() - 1)
					line = line.erase(line.size() - 1);
				// Find the first instance of the delimiter
				nextDelimiterPos = line.find(dataDelimiter);
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
				// Only split the line if it contains the delimiter
				if (nextDelimiterPos != finalDelimiterPos) {
					// Walk across each piece of data in the line stopping only
					// when the end of the string is reached.
					while (lastDelimiterPos != finalDelimiterPos) {
						// Create the substring that holds the single piece of
						// data between the delimiters
						subLine = line.substr(lastDelimiterPos,
								nextDelimiterPos - lastDelimiterPos);
<<<<<<< HEAD
<<<<<<< HEAD
						// Load the subLine in the data
						// This function is defined only for string, bool, char, int double
						loadData(subLine, data);
						// Add it to the vector
=======
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
						// Clear the stream, reset the substring, load the data
						dataStream.clear();
						dataStream.str(subLine);
						dataStream >> data;
<<<<<<< HEAD
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
						dataVector.push_back(data);
						// Switch the delimiter positions and find the next
						lastDelimiterPos =
								(nextDelimiterPos != finalDelimiterPos) ?
										nextDelimiterPos + 1 : nextDelimiterPos;
						nextDelimiterPos = line.find(dataDelimiter,
								lastDelimiterPos);
					}
<<<<<<< HEAD
<<<<<<< HEAD
				}
				// Otherwise just put the whole line in the array
				else {
					// Load the line in the data
					// This function is defined only for string, bool, char, int double
					loadData(line, data);
=======
				} else {
					// Otherwise just put the whole line in the array
					dataStream >> data;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
				} else {
					// Otherwise just put the whole line in the array
					dataStream >> data;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7
					dataVector.push_back(data);
				}
			}
		} else {
			std::cout << "TokenizedLineReader Message: "
					<< " Stream is empty or closed." << std::endl;
			return dataVector;
		}

		return dataVector;
	}

};
//end class TokenizedLineReader

}// end namespace xolotCore.io

#endif
