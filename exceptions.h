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
#pragma  once
#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using namespace std;

/**
 * This class defines the protocol for syntax errors.  It contains a data member that stores the
 * message associated with said error. It also overrides the 'what' standard function with our
 * own function.
 */
class SyntaxError : public exception {

	private:

		/**
		 * This data member contains the error message that is passed through the constructor
		 * method.
		 * @var     string      Message     Error message
		 */
		string Message;

	public:

		/**
		 * The constructor takes in a line number and column number, as well as an error message
		 * and constructs a string stream that will later be stored within the Message data member
		 * in the class.
		 * @param   int     line    Line number associated with error
		 * @param   int     column  Column number associated with error
		 * @param   string  error   Error message to display
		 * @return  void
		 */
		SyntaxError ( int line, int column, string error );

		/**
		 * This function simply returns the error message that is stored privatively and
		 * internally. This function overrides the default standard library function
		 * 'std::what()'.
		 * @return  string  SyntaxError::Message
		 */
		virtual const char * what () const noexcept;

};

/**
 * This class defines the protocol for semantic errors.  It contains a data member that stores the
 * message associated with said error. It also overrides the 'what' standard function with our
 * own function.
 */
class SemanticError : public exception {

	private:

		/**
		 * This data member contains the error message that is passed through the constructor
		 * method.
		 * @var     string      Message     Error message
		 */
		string Message;

	public:

		/**
		 * The constructor takes in a line number and column number, as well as an error message
		 * and constructs a string stream that will later be stored within the Message data member
		 * in the class.
		 * @param   int     line    Line number associated with error
		 * @param   int     column  Column number associated with error
		 * @param   string  error   Error message to display
		 * @return  void
		 */
		SemanticError ( int line, int column, string error );

		/**
		 * This function simply returns the error message that is stored privatively and
		 * internally. This function overrides the default standard library function
		 * 'std::what()'.
		 * @return  string  Semantic::Message
		 */
		virtual const char * what () const noexcept;

};

/**
 * This class defines the protocol for usage errors.  It contains a data member that stores the
 * message associated with said error. It also overrides the 'what' standard function with our
 * own function.
 */
class UsageError : public exception {

	private:

		/**
		 * This data member contains the error message that is passed through the constructor
		 * method.
		 * @var     string      Message     Error message
		 */
		string Message;

	public:

		/**
		 * The constructor takes in a line number and column number, as well as an error message
		 * and constructs a string stream that will later be stored within the Message data member
		 * in the class.
		 * @param   string  error   Error message to display
		 * @return  void
		 */
		UsageError ( string error );

		/**
		 * This function simply returns the error message that is stored privatively and
		 * internally. This function overrides the default standard library function
		 * 'std::what()'.
		 * @return  string Usage::Message
		 */
		virtual const char *what() const noexcept;

};

/**
 * This class defines the protocol for internal errors.  It contains a data member that stores the
 * message associated with said error. It also overrides the 'what' standard function with our
 * own function.
 */
class InternalError : public exception {

	private:

		/**
		 * This data member contains the error message that is passed through the constructor
		 * method.
		 * @var     string      Message     Error message
		 */
		string Message;

	public:

		/**
		 * The constructor takes in a line number and column number, as well as an error message
		 * and constructs a string stream that will later be stored within the Message data member
		 * in the class.
		 * @param   string  error   Error message to display
		 * @return  void
		 */
		InternalError ( string error );

		/**
		 * This function simply returns the error message that is stored privatively and
		 * internally. This function overrides the default standard library function
		 * 'std::what()'.
		 * @return  string  Internal::Message
		 */
		virtual const char *what() const noexcept;

};