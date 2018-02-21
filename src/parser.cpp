/**
 * Parsing implementation for Expression Language Compiler - This package file contains the Parser
 * class which is responsible for determining if there are any syntactic errors in our EL code.
 * The parse function doesn't return anything and it determines if there were any syntactic
 * errors in the code.  If there were, then we throw an exception, otherwise it's return type is
 * void.
 * @version 1.0
 * @package Compiler
 * @category Parsing
 * @author Rafael Grigorian
 * @license MIT License <LICENSE.md>
 */

// Set included libraries and define our namespace
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <string>
#include "../include/parser.h"
#include "../include/exceptions.h"
#include "../include/lexer.h"
#include "../include/token.h"

using namespace std;

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::program () {
	// Output the default wrapper for a standard C++ program
	cppfile << "#include <iostream>" << endl;
	cppfile << "#include <cmath>" << endl << endl;
	cppfile << "using namespace std;" << endl << endl;
	cppfile << "int main()\n{" << endl;
	// Run the derivatives
	statements ();
	more_stmts ();
	// Finish off C++ wrapper template
	cppfile << "}\n";
}

/**
 * This function is derived from a CFL that was built in HW01.
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
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::statements () {
	// Check to see if next token is associated with an input
	if ( CurrentToken.ID == TokenID::INPUT ) {
		input ();
		match ( TokenID::SEMICOLON );
	}
	// Check to see if next token is associated with an output
	else if ( CurrentToken.ID == TokenID::OUTPUT ) {
		cppfile << "\tcout << ";
		output ();
		match ( TokenID::SEMICOLON );
		cppfile << endl;
	}
	// Check to see if next token is associated with an assignment
	else if ( CurrentToken.ID == TokenID::VAR ) {
		// Check if we should push the Token onto the stack
		if ( !declared ( CurrentToken.Value ) ) {
			Variables.push_back ( CurrentToken );
			cppfile << "\tdouble " << CurrentToken.Value << ";" << endl;
		}
		// Continue evaluating our derivative
		assignment ();
		match ( TokenID::SEMICOLON );
		// Append semicolon to the outfile
		cppfile << ";" << endl;
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
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::input () {
	// Run the required derivatives
	input_op ();
	more_input ();
}

/**
 * This function is derived from a CFL that was built in HW01.
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
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::input_op () {
	// Match the INPUT token
	match ( TokenID::INPUT );
	// Check if that variable was previously declared
	if ( !declared ( CurrentToken.Value ) ) {
		cppfile << "\tdouble " << CurrentToken.Value << ";" << endl;
	}
	// Output C++ equivalent for std::cin
	cppfile << "\tcin >> " << CurrentToken.Value << ";" << endl;
	// Add this variable to the "stack" so we can keep track of it
	Variables.push_back ( CurrentToken );
	// Match the VAR token
	match ( TokenID::VAR );
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::output () {
	// Run the derivatives
	output_op ();
	more_output ();
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::more_output () {
	// Check to see if the current Token is the OUTPUT token
	if ( CurrentToken.ID == TokenID::OUTPUT ) {
		// Run derivative
		cppfile << "\n\tcout << ";
		output ();
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::output_op () {
	// Match the OUTPUT token and run the next directive
	match ( TokenID::OUTPUT );
	output_val ();
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::output_val () {
	// Try to match a variable token
	if ( CurrentToken.ID == TokenID::VAR ) {
		// Throw if the variable is not declared
		if ( !declared ( CurrentToken.Value ) ) {
			// Throw a semantic error stating that an uninitialized variable is being used
			throw SemanticError::SemanticError (
				CurrentToken.Line,
				CurrentToken.Column,
				"variable '" + CurrentToken.Value + "' undefined"
			);
		}
		cppfile << CurrentToken.Value << ";";
		match ( TokenID::VAR );
	}
	// Try to match the numerical literal token
	else if ( CurrentToken.ID == TokenID::NUMERIC_LITERAL ) {
		cppfile << CurrentToken.Value << ";";
		match ( TokenID::NUMERIC_LITERAL );
	}
	// Try to match the string literal
	else if ( CurrentToken.ID == TokenID::STRING_LITERAL ) {
		cppfile << CurrentToken.Value << ";";
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
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::assignment () {
	// See if variable is on the stack and was declared
	if ( !declared ( CurrentToken.Value ) ) {
		Variables.push_back ( CurrentToken );
		cppfile << "\tdouble " << CurrentToken.Value << ";" << endl;
	}
	// Put the assignment into cpp file
	cppfile << "\t" << CurrentToken.Value << " = ";
	// Match the variable and equals tokens and then recurse through directive
	match ( TokenID::VAR );
	match ( TokenID::EQUAL );
	// Reset Expression string
	Expression = "";
	// Call expression parsing recursively
	expr ();
	// Output string into cppfile
	cppfile << Expression;
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::expr () {
	// Initialize the position counter to the length of the string
	int position = Expression.length ();
	// Call the directives
	md_expr ();
	// Recursively call the directive while passing th position variable
	expr2 ( position );
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::expr2 ( int position ) {
	// Try to match the ADD Token
	if ( CurrentToken.ID == TokenID::ADD ) {
		// Append and match current token value
		Expression += "+";
		match ( TokenID::ADD );
		// Since we matched an operator, insert '(' back in time ;)
		Expression.insert ( position, "(" );
		// Recursively call derivatives
		md_expr ();
		// Complete expression parenthesis match
		Expression += ")";
		// Complete running derivatives
		expr2 ( position );
	}
	// Try to match the SUBTRACT Token
	else if ( CurrentToken.ID == TokenID::SUBTRACT ) {
		// Append and match current token value
		Expression += "-";
		match ( TokenID::SUBTRACT );
		// Since we matched an operator, insert '(' back in time ;)
		Expression.insert ( position, "(" );
		// Recursively call derivatives
		md_expr ();
		// Complete expression parenthesis match
		Expression += ")";
		// Complete running derivatives
		expr2 ( position );
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::md_expr () {
	// Initialize the position variable to the length of the expression data member
	int position = Expression.length ();
	// Call the directives
	pow_expr ();
	md_expr2 ( position );
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::md_expr2 ( int position ) {
	// Try to match the MULTIPLY Token
	if ( CurrentToken.ID == TokenID::MULTIPLY ) {
		// Append token value and match token
		Expression += "*";
		match ( TokenID::MULTIPLY );
		// Since we matched an operator, go back in time and insert '('
		Expression.insert ( position, "(" );
		// Continue running derivatives
		pow_expr ();
		// Match the previously open parenthesis
		Expression += ")";
		// Finish running derivatives
		md_expr2 ( position );
	}
	// Try to match the DIVIDE Token
	else if ( CurrentToken.ID == TokenID::DIVIDE ) {
		// Append token value and match token
		Expression += "/";
		match ( TokenID::DIVIDE );
		// Since we matched an operator, go back in time and insert '('
		Expression.insert ( position, "(" );
		// Continue running derivatives
		pow_expr ();
		// Match the previously open parenthesis
		Expression += ")";
		// Finish running derivatives
		md_expr2 ( position );
	}
	// Allow epsilon
	else { ; }
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::pow_expr () {
	// Initialize the position to the length of the expression string data member
	int position = Expression.length ();
	// This statement will be called in either case
	base_expr ();
	// Check to see if the next token token is POWER, if so then recursively call next definition
	if ( CurrentToken.ID == TokenID::POWER ) {
		// Match the POWER token
		match ( TokenID::POWER );
		// Since we matched an operator, insert back in time a '('
		Expression.insert ( position, "pow(" );
		// Append a comma
		Expression += ",";
		// Get the RHS
		pow_expr ();
		// Match the previously open parenthesis
		Expression += ")";
	}
}

/**
 * This function is derived from a CFL that was built in HW01.
 * @return 	void
 */
void Parser::base_expr () {
	// See if the current token is a left parenthesis
	if ( CurrentToken.ID == TokenID::LEFT_PAREN ) {
		// Call the expr function in between matching the pair of parenthesis
		match ( TokenID::LEFT_PAREN );
		Expression += "(";
		expr ();
		match ( TokenID::RIGHT_PAREN );
		Expression += ")";
	}
	// See if current token is of variable type
	else if ( CurrentToken.ID == TokenID::VAR ) {
		// Throw if the variable is not declared
		if ( !declared ( CurrentToken.Value ) ) {
			// Throw a semantic error stating that an uninitialized variable is being used
			throw SemanticError::SemanticError (
				CurrentToken.Line,
				CurrentToken.Column,
				"variable '" + CurrentToken.Value + "' undefined"
			);
		}
		// Append current value to expression string
		Expression += CurrentToken.Value;
		// Match the VAR token id
		match ( TokenID::VAR );
	}
	// See if current token is a numerical literal
	else if ( CurrentToken.ID == TokenID::NUMERIC_LITERAL ) {
		// Append current value to expression string
		Expression += CurrentToken.Value;
		// Match the NUMERIC_LITERAL token id
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
 * This function iterates through our "stack" of declared variables and sees if the target
 * name matches any of the Tokens values.  This will be used to see if we need to put
 * another declaration into the C++ outfile.
 * @param 	string 		target 		The target string that we will try to match
 * @return 	bool					Whether the target was matched
 */
bool Parser::declared ( string target ) {
	// Loop through our "stack" of variables
	for ( auto variable : Variables ) {
		// If the value of the Token matches our target value
		if ( variable.Value == target ) {
			// Return that it is was declared
			return true;
		}
	}
	// Otherwise, we will say that it wasn't declared
	return false;
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
	// Initialize Expression string
	Expression = "";
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
