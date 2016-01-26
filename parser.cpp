/**
 * Parsing implementation for Expression Language Compiler - This package file contains the Parser
 * class which is responsible for determining if there are any syntactic errors in our EL code.
 * The parse function doesn't return anything and it determines if there were any syntactic
 * errors in the code.  If there were, then we throw an exception, otherwise it's return type is
 *voidParser::.
 * @version 1.0
 * @package Compiler
 * @category Parsing
 * @author Rafael Grigorian
 * @license GNU Public License <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

// Set included libraries and define our namespace
#include <iostream>
#include <string>
#include <fstream>
#include "parser.h"
#include "exceptions.h"
#include "Lexer.h"
#include "Token.h"

using namespace std;

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::program () {
	// Run the derivatives
	statements ();
	more_stmts ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::more_stmts () {
	// Check that there is either INPUT, OUTPUT, or ASSIGNMENT Token
	if ( CurrentToken.ID == TokenID::INPUT 
		 || CurrentToken.ID == TokenID::OUTPUT 
		 || CurrentToken.ID == TokenID::VAR ) {
		statements ();
		more_stmts ();
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::statements () {
	// Check to see if next token is associated with an input
	if ( CurrentToken.ID == TokenID::INPUT ) {
		input ();
		match ( TokenID::SEMICOLON );
		cout << "statement!" << endl;
		cppfile << "statement!" << endl;
	}
	// Check to see if next token is associated with an output
	else if ( CurrentToken.ID == TokenID::OUTPUT ) {
		output ();
		match ( TokenID::SEMICOLON );
		cout << "statement!" << endl;
		cppfile << "statement!" << endl;
	}
	// Check to see if next token is associated with an assignment
	else if ( CurrentToken.ID == TokenID::VAR ) {
		assignment ();
		match ( TokenID::SEMICOLON );
		cout << "statement!" << endl;
		cppfile << "statement!" << endl;
	}
	// Other wise throw an exception
	else {
		// Throw our exception
		throw SyntaxError::SyntaxError (
			CurrentToken.Line,
			CurrentToken.Column,
			"expecting >>, <<, or VAR"
		);
	}
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::input () {
	// Run the required derivatives
	input_op ();
	more_input ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::more_input () {
	// Check to see that there is an INPUT token
	if ( CurrentToken.ID == TokenID::INPUT ) {
		// Run derivative
		input ();
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::input_op () {
	// Match the INPUT token and the VAR token
	match ( TokenID::INPUT );
	match ( TokenID::VAR );
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::output () {
	// Run the derivatives
	output_op ();
	more_output ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::more_output () {
	// Check to see if the current Token is the OUTPUT token
	if ( CurrentToken.ID == TokenID::OUTPUT ) {
		// Run derivative
		output ();
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::output_op () {
	// Match the OUTPUT token and run the next directive
	match ( TokenID::OUTPUT );
	output_val ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::output_val () {
	// Try to match a variable token
	if ( CurrentToken.ID == TokenID::VAR ) {
		match ( TokenID::VAR );
	}
	// Try to match the numerical literal token
	else if ( CurrentToken.ID == TokenID::NUMERIC_LITERAL ) {
		match ( TokenID::NUMERIC_LITERAL );
	}
	// Try to match the string literal
	else if ( CurrentToken.ID == TokenID::STRING_LITERAL ) {
		match ( TokenID::STRING_LITERAL );
	}
	// Otherwise throw an error
	else {
		// Throw our exception
		throw SyntaxError::SyntaxError (
			CurrentToken.Line,
			CurrentToken.Column,
			"Expecting VAR or NUMERIC_LITERAL or STRING_LITERAL"
		);
	}
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::assignment () {
	// Match the variable and equals tokens and then recurse through directive
	match ( TokenID::VAR );
	match ( TokenID::EQUAL );
	expr ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::expr () {
	// Call the directives
	md_expr ();
	expr2 ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::expr2 () {
	// Try to match the ADD Token
	if ( CurrentToken.ID == TokenID::ADD ) {
		// Match the add and call function definitions
		match ( TokenID::ADD );
		md_expr ();
		expr2 ();
	}
	// Try to match the SUBTRACT Token
	else if ( CurrentToken.ID == TokenID::SUBTRACT ) {
		// Match the subtract and call function definitions
		match ( TokenID::SUBTRACT );
		md_expr ();
		expr2 ();
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::md_expr () {
	// Call the directives
	pow_expr ();
	md_expr2 ();
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::md_expr2 () {
	// Try to match the MULTIPLY Token
	if ( CurrentToken.ID == TokenID::MULTIPLY ) {
		// Match the multiply and call function definitions
		match ( TokenID::MULTIPLY );
		pow_expr ();
		md_expr2 ();
	}
	// Try to match the DIVIDE Token
	else if ( CurrentToken.ID == TokenID::DIVIDE ) {
		// Match the divide and call function definitions
		match ( TokenID::DIVIDE );
		pow_expr ();
		md_expr2 ();
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::pow_expr () {
	// This statement will be called in either case
	base_expr ();
	// Check to see if the next token token is POWER, if so then recursively call next definition
	if ( CurrentToken.ID == TokenID::POWER ) {
		// Match the POWER token and call pow_expr
		match ( TokenID::POWER );
		pow_expr ();
	}
}

/**
 * This function is derived from a CFL that was built in HW03.
 * @return 	void
 */
void Parser::base_expr () {
	// See if the current token is a left parenthesis
	if ( CurrentToken.ID == TokenID::LEFT_PAREN ) {
		// Call the expr function in between matching the pair of parenthesis
		match ( TokenID::LEFT_PAREN );
		expr ();
		match ( TokenID::RIGHT_PAREN );
	}
	// See if current token is of variable type
	else if ( CurrentToken.ID == TokenID::VAR ) {
		// Match the VAR token id
		match ( TokenID::VAR );
	}
	// See if current token is a numerical literal
	else if ( CurrentToken.ID == TokenID::NUMERIC_LITERAL ) {
		// Match the numeric literal
		match ( TokenID::NUMERIC_LITERAL );
	}
	// If all else fails, throw a syntax error
	else {
		// Throw our exception
		throw SyntaxError::SyntaxError (
			CurrentToken.Line,
			CurrentToken.Column,
			"expecting (, VAR, or NUMERIC_LITERAL"
		);
	}
}

/**
 * This function makes sure that the passed token id is equal to the current token id saved
 * internally within the instance of the object.  If the Token is equal, it proceeds to get
 * the next token that is available and saves it into the CurrentToken private data member,
 * otherwise if they are not equal then the function throws an exception.
 * @param 	TokenID 	passed 		The Token id to match it against the current one
 * @throw 	exception 				Will throw a syntax error
 * @return 	void
 */
void Parser::match ( TokenID passed ) {
	// Check if the current Token matches to the passed token id, if so save next token
	if ( CurrentToken.ID == passed ) {
		CurrentToken = Lexer.nextToken ();
	}
	// Otherwise throw an error
	else {
		// Throw our exception
		throw SyntaxError::SyntaxError (
			CurrentToken.Line,
			CurrentToken.Column,
			"expecting " + Token ( passed, CurrentToken.Line, CurrentToken.Column ).Value
		);
	}
}

/**
 * This constructor takes in the infile and outfile as strings and then uses them to pass
 * the source file to the Lexer, and also to open up an ofstream and write in the results
 * to the outfile.  This ofstream is known internally as cppfile.
 * @param 	string 		infile 		The input file containing the source script
 * @param 	string 		outfile 	The output file that this parser will print to
 * @return 	void
 */
Parser::Parser ( string infile, string outfile )
	: Lexer ( infile ), CurrentToken ( Lexer.nextToken () ), cppfile ( outfile, ofstream::trunc ) {
}

/**
 * This function is called after the constructor is ran.  This function tries to parse the
 * source file and validate its syntacticly.
 * @return 	void
 */
void Parser::parse () {
	// Start evaluating the constructed grammar
	program ();
	// Match the last token to be an EOT Token
	match ( TokenID::EOT );
}