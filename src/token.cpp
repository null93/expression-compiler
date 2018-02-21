/**
 * Token definition for Expression Language Compiler - This header file defines the Token class.
 * This package includes a class object that is used to initially parse the language and separate
 * it into identifiable parts for actual parser to use and then compile into the C++ language. It
 * contains all the definitions for the TokenID enum and debugging functions.
 * @version 1.0
 * @package Compiler
 * @category Lexer
 * @author Rafael Grigorian
 * @license MIT License <LICENSE.md>
 */

// Set included libraries and define our namespace
#include "../include/token.h"
#include "../include/exceptions.h"

using namespace std;

/**
 * This constructor takes in a variable argument which makes it unique.  This argument is a
 * string and it is set as the tokens value.
 * @param   TokenID   id    Defined by the TokenID enum
 * @param   string    value   This is set as the Token's value
 * @param   int     line  Line number of found Token.
 * @param   int     column  Column number of found Token.
 * @return  void
 */
Token::Token ( TokenID id, string value, int line, int column )
	: ID ( id ), Value ( value ), Line ( line ), Column ( column ) {
}

/**
 * This constructor takes in a variable argument which makes it unique.  This argument is a
 * character and it is set as the tokens value.
 * @param   TokenID   id    Defined by the TokenID enum
 * @param   char    value   This is set as the Token's value
 * @param   int     line  Line number of found Token.
 * @param   int     column  Column number of found Token.
 * @return  void
 */
Token::Token ( TokenID id, char c, int line, int column )
	: Token ( id, string ( 1, c ), line, column ) {
}

/**
 * This constructor doesn't take the variable argument that is unique.  Instead it switches
 * through all the enums based on the TokenID and sets the value of the token to be the
 * literal translation of said enum value.
 * @param   TokenID   id    Defined by the TokenID enum
 * @param   int     line  Line number of found Token.
 * @param   int     column  Column number of found Token.
 * @return  void
 */
Token::Token ( TokenID id, int line, int column )
	: ID ( id ), Line ( line ), Column ( column ) {
	// Switch between enum values and convert TokenID to a string literal given the Token's tag.
	switch ( id ) {
		case TokenID::EOT:
			Value = "EOT";
			break;
		case TokenID::UNKNOWN:
			Value = "UNKNOWN";
			break;
		case TokenID::SEMICOLON:
			Value = ";";
			break;
		case TokenID::ADD:
			Value = "+";
			break;
		case TokenID::SUBTRACT:
			Value = "-";
			break;
		case TokenID::MULTIPLY:
			Value = "*";
			break;
		case TokenID::DIVIDE:
			Value = "/";
			break;
		case TokenID::POWER:
			Value = "^";
			break;
		case TokenID::EQUAL:
			Value = "=";
			break;
		case TokenID::INPUT:
			Value = ">>";
			break;
		case TokenID::OUTPUT:
			Value = "<<";
			break;
		case TokenID::VAR:
			Value = "VAR";
			break;
		case TokenID::STRING_LITERAL:
			Value = "STRING_LITERAL";
			break;
		case TokenID::NUMERIC_LITERAL:
			Value = "NUMERIC_LITERAL";
			break;
		case TokenID::LEFT_PAREN:
			Value = "(";
			break;
		case TokenID::RIGHT_PAREN:
			Value = ")";
			break;
		// By default, throw an error exception
		default:
			throw InternalError (
				"Unknown token id passed in Token ( TokenID id )"
			);
	}
}

/**
 * These functions are declared here and will be used to debug the Lexer. They can be removed later
 * when everything runs smoothly.
 * @param   pointer     output      This points to an ostream object
 * @param   pointer     TokenID     This points to a TokenID data member inside the Token class
 * @return  ostream     output      The ostream object is returned
 */
ostream& operator << ( ostream& output, const TokenID& id ) {
	// Cast as int and output to stream
	output << (int) id;
	// Return stream
	return output;
}

/**
 * These functions are declared here and will be used to debug the Lexer. They can be removed later
 * when everything runs smoothly.
 * @param   pointer     output      This points to an ostream object
 * @param   pointer     Token       This points to a Token object
 * @return  ostream     output      The ostream object is returned
 */
ostream& operator << ( ostream& output, const Token& token ) {
	// Output string to stream
	output
		<< token.ID
		<< ": " << token.Value << " "
		<< "@(" << token.Line << "," << token.Column << ")";
	// Return stream
	return output;
}
