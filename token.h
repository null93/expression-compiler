/**
 * Token definition for Expression Language Compiler - This header file defines the Token class.
 * This package includes a class object that is used to initially parse the language and separate
 * it into identifiable parts for actual parser to use and then compile into the C++ language. It
 * contains all the definitions for the TokenID enum and debugging functions.
 * @version 1.0
 * @package Compiler
 * @category Lexer
 * @author Rafael Grigorian
 * @license GNU Public License <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

// Set directive and include libraries and define our namespace
#pragma  once
#include <iostream>
#include <string>
#include "exceptions.h"

using namespace std;

/**
 * This enum is used to associate a token's ID to its descriptive property.
 */
enum class TokenID {
	EOT,
	UNKNOWN,
	SEMICOLON,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	POWER,
	EQUAL,
	LEFT_PAREN,
	RIGHT_PAREN,
	INPUT,
	OUTPUT,
	VAR,
	STRING_LITERAL,
	NUMERIC_LITERAL
};

/**
 * This is the actual Token class and it contains the data members necessary to identify a Token
 * fully.  It also includes overloaded function in order to portray different data types.
 */
class Token {

	public:

		/**
		 * This variable is identified as an integer associated with the TokenID enum.
		 * @var     TokenID     Describes ID
		 */
		TokenID ID;

		/**
		 * This variable identifies the Token's value as a string literal.
		 * @var     string      Describes value
		 */
		string Value;

		/**
		 * This variable identifies the Token's line number associated with where in the source
		 * file it is found.  This value starts at 1.
		 * @var     int         Line number in source file
		 */
		int Line;

		/**
		 * This variable identifies the Token's column associated with where in the source
		 * file it is found. This value starts at 1.
		 * @var     int         Column number in source file
		 */
		int Column;

		/**
		 * This constructor takes in a variable argument which makes it unique.  This argument is a
		 * string and it is set as the tokens value.
		 * @param   TokenID     id      Defined by the TokenID enum
		 * @param   string      value   This is set as the Token's value
		 * @param   int         line    Line number of found Token.
		 * @param   int         column  Column number of found Token.
		 * @return  void
		 */
		Token ( TokenID id, string value, int line, int column );

		/**
		 * This constructor takes in a variable argument which makes it unique.  This argument is a
		 * character and it is set as the tokens value.
		 * @param   TokenID     id      Defined by the TokenID enum
		 * @param   char        value   This is set as the Token's value
		 * @param   int         line    Line number of found Token.
		 * @param   int         column  Column number of found Token.
		 * @return  void
		 */
		Token ( TokenID id, char c, int line, int column );

		/**
		 * This constructor doesn't take the variable argument that is unique.  Instead it switches
		 * through all the enums based on the TokenID and sets the value of the token to be the
		 * literal translation of said enum value.
		 * @param   TokenID     id      Defined by the TokenID enum
		 * @param   int         line    Line number of found Token.
		 * @param   int         column  Column number of found Token.
		 * @return  void
		 */
		Token ( TokenID id, int line, int column );

};

/**
 * These functions are declared here and will be used to debug the Lexer. They can be removed later
 * when everything runs smoothly.
 * @param   pointer     output      This points to an ostream object
 * @param   pointer     TokenID     This points to a TokenID data member inside the Token class
 * @return  ostream     output      The ostream object is returned
 */
ostream& operator << ( ostream& output, const TokenID& id );

/**
 * These functions are declared here and will be used to debug the Lexer. They can be removed later
 * when everything runs smoothly.
 * @param   pointer     output      This points to an ostream object
 * @param   pointer     Token       This points to a Token object
 * @return  ostream     output      The ostream object is returned
 */
ostream& operator << ( ostream& output, const Token& t );