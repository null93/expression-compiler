/**
 * Exception implementations for Expression Language Compiler - This header file contains classes
 * that will be used to handle errors within our compiler.  There are four different types of
 * errors: Syntax, Semantic, Usage, and Internal.  These errors are handled differently.
 * @version 1.0
 * @package Compiler
 * @category Error Handling
 * @author Rafael Grigorian
 * @license GNU Public License <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

// Set included libraries and define our namespace
#include "exceptions.h"

using namespace std;

/**
 * The constructor takes in a line number and column number, as well as an error message
 * and constructs a string stream that will later be stored within the Message data member
 * in the class.
 * @param   int     line    Line number associated with error
 * @param   int     column  Column number associated with error
 * @param   string  error   Error message to display
 * @return  void
 */
SyntaxError::SyntaxError ( int line, int column, string error ) {
	stringstream  ss;
	ss << "syntax error @ (" << line << "," << column << "): " << error;
	Message = ss.str ();
}

/**
 * This function simply returns the error message that is stored privatively and
 * internally. This function overrides the default standard library function
 * 'std::what()'.
 * @return  string  SyntaxError::Message
 */
const char * SyntaxError::what () const noexcept {
	return Message.c_str ();
}

/**
 * The constructor takes in a line number and column number, as well as an error message
 * and constructs a string stream that will later be stored within the Message data member
 * in the class.
 * @param   int     line    Line number associated with error
 * @param   int     column  Column number associated with error
 * @param   string  error   Error message to display
 * @return  void
 */
SemanticError::SemanticError ( int line, int column, string error ) {
	stringstream  ss;
	ss << "semantic error @ (" << line << "," << column << "): " << error;
	Message = ss.str ();
}

/**
 * This function simply returns the error message that is stored privatively and
 * internally. This function overrides the default standard library function
 * 'std::what()'.
 * @return  string  Semantic::Message
 */
const char * SemanticError::what () const noexcept {
	return Message.c_str ();
}

/**
 * The constructor takes in a line number and column number, as well as an error message
 * and constructs a string stream that will later be stored within the Message data member
 * in the class.
 * @param   string  error   Error message to display
 * @return  void
 */
UsageError::UsageError ( string error ) {
	Message = "usage: " + error;
}

/**
 * This function simply returns the error message that is stored privatively and
 * internally. This function overrides the default standard library function
 * 'std::what()'.
 * @return  string Usage::Message
 */
const char * UsageError::what () const noexcept {
	return Message.c_str ();
}

/**
 * The constructor takes in a line number and column number, as well as an error message
 * and constructs a string stream that will later be stored within the Message data member
 * in the class.
 * @param   string  error   Error message to display
 * @return  void
 */
InternalError::InternalError ( string error ) {
	Message = "**internal error: " + error;
}

/**
 * This function simply returns the error message that is stored privatively and
 * internally. This function overrides the default standard library function
 * 'std::what()'.
 * @return  string  Internal::Message
 */
const char * InternalError::what () const noexcept {
	return Message.c_str ();
}