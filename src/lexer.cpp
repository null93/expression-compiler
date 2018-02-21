/**
 * Lexer implementation for Expression Language Compiler - This package contains the Lexer class
 * alongside the Position class which is used to keep track of our parse position relative
 * to the source file.  The Lexer class works by returning Tokens until the end of the file
 * is reached.  After that point, the Lexer object will always return an End Of Token (EOT)
 * token.
 * @version 1.0
 * @package Compiler
 * @category Lexer
 * @author Rafael Grigorian
 * @license MIT License <LICENSE.md>
 */

// Include libraries and define namespace
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <regex>
#include "../include/exceptions.h"
#include "../include/token.h"
#include "../include/lexer.h"

using namespace std;

/**
 * This constructor takes in a line number and a column number and sets the internal public
 * data accordingly.
 * @note    The arguments are not indexes, they are line numbers starting from 1.
 * @param   int     line    Line number
 * @param   int     column  Column number
 * @return  void
 */
Position::Position ( int line, int column )
	: Line ( line ), Column ( column ), LineIndex ( line - 1 ), ColumnIndex ( column - 1 ) {
}

/**
 * This function increments the indexes and the position number based of the index by a
 * variable amount.
 * @param   int     increment       The number to add to the line index and position
 * @return  int                     Returns the previous position
 */
int Position::line ( int increment ) {
	// Save previous value of position
	int previous = Line;
	// Add to line position and line index
	Line += increment;
	LineIndex += increment;
	// Reset column and index
	Column = 1;
	ColumnIndex = 0;
	// Get line length and return previous value
	LineLength = Lines [ LineIndex ].length ();
	return previous;
}

/**
 * This function increments the indexes and the position number based of the column by a
 * variable amount.
 * @param   int     increment       The number to add to the column index and position
 * @return  int                     Returns the previous position
 */
int Position::column ( int increment ) {
	// Save previous value of position
	int previous = Column;
	// Add to column and return previous value
	Column += increment;
	ColumnIndex += increment;
	// Check to see if we need to go to the next line
	if ( Column > LineLength ) {
		// Reset column and increment line, also reset line length
		line ( 1 );
		LineLength = Lines [ LineIndex ].length ();
	}
	// Return the previous value
	return previous;
}

/**
 * Based on the other data members, this function returns a boolean that specifies whether
 * or not it is safe to loop ahead.
 * @return  bool                    Can we look ahead? True or False
 */
bool Position::available () {
	// Check if we are in bounds
	if ( Column >= LineLength ) {
		return false;
	}
	// By default we return false
	return true;
}

/**
 * This function will look ahead one character and return the contents.  If there is
 * nothing past the current character, then a null byte will be returned.  This value will
 * not be saved by the cursor.
 * @return  char                    Character ahead of current one
 */
char Position::next () {
	// Check to see if there is one ahead
	if ( available () ) {
		return Lines [ LineIndex ] [ Column ];
	}
	// Return NULL byte by default
	return '\0';
}

/**
 * This function searches for the ending to a string given the fact that the current
 * position is at the start of the string.  It will update Cursor positioning and indexing
 * accordingly.
 * @return  Token                   Returns Token if valid string literal is matched
 * @throw   SyntaxError             If all goes wrong this exception will be thrown
 */
Token Position::matchString () {
	// Backup variables
	string build = "\"";
	int backupLine = Line;
	int backupColumn = Column;
	// Initialize current character
	char character = Lines [ LineIndex ] [ ColumnIndex ];
	// Loop while there is a next character available
	while ( LineIndex != LineCount && Column <= LineLength && LineIndex < backupLine ) {
		// Increment loop and add to string
		character = next ();
		build += character;
		column ( 1 );
		// Check to see if current character matches string literal
		if ( character == '"' ) {
			// Get the next character before exiting
			column ( 1 );
			// Return a string literal Token
			return Token ( TokenID::STRING_LITERAL, build, backupLine, backupColumn );
		}
	}
	// By default, we will send a syntax error
	throw SyntaxError::SyntaxError ( backupLine, backupColumn, "invalid string literal" );
}

/**
 * This function searches from the point of the cursor and determines if there is a numeric
 * literal.  If there is one, then it will update the cursor and return the Token.
 * Otherwise, if there is an invalid numeric literal, then a syntax error will be thrown.
 * @param   bool        force       Whether or not to force a syntax error
 * @return  Token                   Returns Token if valid numeric literal is matched
 * @throw   SyntaxError             If all goes wrong this exception will be thrown
 */
Token Position::matchNumericalLiteral ( bool force ) {
	// If force is true and the next character is a number, then throw error
	if ( force && available () && isdigit ( next () ) ) {
		throw SyntaxError::SyntaxError ( Line, Column, "invalid numeric literal" );
	}
	else if ( force ) {
		return Token ( TokenID::UNKNOWN, '.', Line, column ( 1 ) );
	}
	// Define constants in order to preform regular expression search
	string subject ( &Lines [ LineIndex ] [ ColumnIndex ] );
	string result;
	smatch match;
	// Define our regular expression
	regex re ("(^[0-9]+(\\.)?[0-9]*).*");
	// Preform regular expression search and if we get a result, then save it
	if ( regex_search ( subject, match, re ) && match.size () > 1 ) {
		// Get the result
		result = match.str ( 1 );
		// Throw an error if the next character is '.'
		if ( result [ result.length () - 1 ] == '.' || force ) {
			throw SyntaxError::SyntaxError ( Line, Column, "invalid numeric literal" );
		}
	}
	// Increment based on the size of the string
	column ( result.length () );
	// Return Token
	return Token ( TokenID::NUMERIC_LITERAL, result, Line, Column - result.length () );
}

/**
 * This function searches to see when a variable definition ends.  Once it finds an ending,
 * then it returns a token.  Unlike the other matching functions, this function will not
 * throw an error, because it is logically impossible to create one in this situation.
 * @return  Token                   Returns Token of the variable matched
 */
Token Position::matchVariable () {
	// Initiate string and push first character
	char character = Lines [ LineIndex ] [ ColumnIndex ];
	string result = "";
	// Loop through until invalid character shows up
	while ( character != '\n' && ( isalnum ( character ) || character == '_' ) ) {
		// Push onto result and increment cursor position
		result += character;
		column ( 1 );
		character = Lines [ LineIndex ] [ ColumnIndex ];
	}
	// Return the variable Token
	return Token ( TokenID::VAR, result, Line, Column - result.length () );
}

/**
 * This constructor takes in the name of the source file and attempts to open it.  If
 * unsuccessful it will throw a Usage error.  This constructor also reads in all the source
 * file's data and populates a string vector with it.
 * @param   string      infile      Path to input source file
 */
Lexer::Lexer ( string infile )
	: Cursor ( Position ( 1, 1 ) ) {
	// Declare file stream and initiate file descriptor
	ifstream sourcefile ( infile );
	// Check to see if file exists
	if ( sourcefile.good () ) {
		// Initiate temporary line string variable
		string line;
		// Read from the file, line by line
		while ( getline ( sourcefile, line ) ) {
			// Append line to the back of our list
			Cursor.Lines.push_back ( line );
		}
		// Close the file after we are done reading from it
		sourcefile.close ();
		// Store how many lines the input program has and how many characters the line is
		Cursor.LineCount = Cursor.Lines.size ();
		Cursor.LineLength = Cursor.Lines [ 0 ].length ();
	}
	else {
		// Usage error: file doesn't exist
		throw UsageError::UsageError ( "unable to open '" + infile + "'" );
	}
}

/**
 * This function returns the next Token that is available during parsing of the source
 * file. If any improper literals are seen, then this function will throw a Syntax error.
 * @return  Token                   Returns Token object with populated data members
 */
Token Lexer::nextToken () {
	// Initialize looped variables
	string line;
	char character;
	// Loop through until all lines are processed
	while ( Cursor.LineIndex < Cursor.LineCount ) {
		// Define the current line in looped scope
		line = Cursor.Lines [ Cursor.LineIndex ];
		character = line [ Cursor.ColumnIndex ];
		// Check to see if the current character is whitespace
		if ( character == ' ' || character == '\t' || character == '\r' || character == '\n' || character == '\0' ) {
			// Skip this character
			Cursor.column ( 1 );
		}
		// Check if this is the start of a comment
		else if ( character == '/' && Cursor.available () && Cursor.next () == '/' ) {
			Cursor.line ( 1 );
		}
		// Check to see if this is a string
		else if ( character == '"' ) {
			return Cursor.matchString ();
		}
		// Check if there is a variable
		else if ( isalpha ( character ) ) {
			return Cursor.matchVariable ();
		}
		// Check if there is a numerical literal
		else if ( isdigit ( character ) || character == '.' ) {
			return Cursor.matchNumericalLiteral ( character == '.' );
		}
		// Check to see if this is an output
		else if ( character == '<' && Cursor.available () && Cursor.next () == '<' ) {
			return Token ( TokenID::OUTPUT, Cursor.Line, Cursor.column ( 2 ) );
		}
		// Check to see if this is an input
		else if ( character == '>' && Cursor.available () && Cursor.next () == '>' ) {
			return Token ( TokenID::INPUT, Cursor.Line, Cursor.column ( 2 ) );
		}
		// Case switch between all possible characters in current line that are simple to identify
		else {
			switch ( character ) {
				case ';' :
					return Token ( TokenID::SEMICOLON, Cursor.Line, Cursor.column ( 1 ) );
				case '*' :
					return Token ( TokenID::MULTIPLY, Cursor.Line, Cursor.column ( 1 ) );
				case '/' :
					return Token ( TokenID::DIVIDE, Cursor.Line, Cursor.column ( 1 ) );
				case '+' :
					return Token ( TokenID::ADD, Cursor.Line, Cursor.column ( 1 ) );
				case '-' :
					return Token ( TokenID::SUBTRACT, Cursor.Line, Cursor.column ( 1 ) );
				case '^' :
					return Token ( TokenID::POWER, Cursor.Line, Cursor.column ( 1 ) );
				case '=' :
					return Token ( TokenID::EQUAL, Cursor.Line, Cursor.column ( 1 ) );
				case '(' :
					return Token ( TokenID::LEFT_PAREN, Cursor.Line, Cursor.column ( 1 ) );
				case ')' :
					return Token ( TokenID::RIGHT_PAREN, Cursor.Line, Cursor.column ( 1 ) );
				default :
					return Token ( TokenID::UNKNOWN, character, Cursor.Line, Cursor.column ( 1 ) );
			}
		}
	}
	// Once every line was traversed, return an EOT Token
	return Token ( TokenID::EOT, Cursor.Line, Cursor.Column );
}
