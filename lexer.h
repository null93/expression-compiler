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
 * @license GNU Public License <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

// Include libraries and define namespace
#pragma  once
#include <string>
#include <vector>
#include "token.h"
#include "exceptions.h"

using namespace std;

/**
 * This class holds position information that the Lexer uses internally.  This information includes
 * the current line number as well as the current column number.  This class also holds the
 * corresponding index numbers to said line and column numbers.  There are useful functions to get
 * the index and to increment the row and column position.
 */
class Position {

	public:

		/**
		 * A vector of lines which correspond to the lines in the constructors passed source file.
		 * @var     string      lines       A vector of string
		 */
		vector <string> Lines;

		/**
		 * This is the current line number.
		 * @var     int     Line    Line number
		 */
		int Line;

		/**
		 * This is the current column number.
		 * @var     int     Column  Column number
		 */
		int Column;

		/**
		 * This is the current line number index.
		 * @var     int     LineIndex   Line number index
		 */
		int LineIndex;

		/**
		 * This is the current column number index.
		 * @var     int     ColumnIndex     Column number index
		 */
		int ColumnIndex;

		/**
		 * This contains the length of the line as an integer representation.
		 * @var     int     LineLength      Length of current line
		 */
		int LineLength;

		/**
		 * The number of lines in our Lines vector array.
		 * @var     int         LineCount   Number of string entries in Lexer::Lines
		 */
		int LineCount;

		/**
		 * This constructor takes in a line number and a column number and sets the internal public
		 * data accordingly.
		 * @note    The arguments are not indexes, they are line numbers starting from 1.
		 * @param   int     line    Line number
		 * @param   int     column  Column number
		 * @return  void
		 */
		Position ( int line, int column );

		/**
		 * This function increments the indexes and the position number based of the index by a
		 * variable amount.
		 * @param   int     increment       The number to add to the line index and position
		 * @return  int                     Returns the previous position
		 */
		int line ( int increment );

		/**
		 * This function increments the indexes and the position number based of the column by a
		 * variable amount.
		 * @param   int     increment       The number to add to the column index and position
		 * @return  int                     Returns the previous position
		 */
		int column ( int increment );

		/**
		 * Based on the other data members, this function returns a boolean that specifies whether
		 * or not it is safe to loop ahead.
		 * @return  bool                    Can we look ahead? True or False
		 */
		bool available ();

		/**
		 * This function will look ahead one character and return the contents.  If there is
		 * nothing past the current character, then a null byte will be returned.  This value will
		 * not be saved by the cursor.
		 * @return  char                    Character ahead of current one
		 */
		char next ();

		/**
		 * This function searches for the ending to a string given the fact that the current
		 * position is at the start of the string.  It will update Cursor positioning and indexing
		 * accordingly.
		 * @return  Token                   Returns Token if valid string literal is matched
		 * @throw   SyntaxError             If all goes wrong this exception will be thrown
		 */
		Token matchString ();

		/**
		 * This function searches from the point of the cursor and determines if there is a numeric
		 * literal.  If there is one, then it will update the cursor and return the Token.
		 * Otherwise, if there is an invalid numeric literal, then a syntax error will be thrown.
		 * @param   bool        force       Whether or not to force a syntax error
		 * @return  Token                   Returns Token if valid numeric literal is matched
		 * @throw   SyntaxError             If all goes wrong this exception will be thrown
		 */
		Token matchNumericalLiteral ( bool force );

		/**
		 * This function searches to see when a variable definition ends.  Once it finds an ending,
		 * then it returns a token.  Unlike the other matching functions, this function will not
		 * throw an error, because it is logically impossible to create one in this situation.
		 * @return  Token                   Returns Token of the variable matched
		 */
		Token matchVariable ();

};

/**
 * The Lexer class parses a specified source file and creates tokens based on the contents of said
 * source file.  The Lexer class uses the exceptions package as well to throw errors.  This class
 * also contains helper functions that are useful when parsing the source code.
 */
class Lexer {

	private:

		/**
		 * This object stores the current cursor's position and index.
		 * @var     Position    cursor      A vector of string
		 * @see                             Position class
		 */
		Position Cursor;

	public:

		/**
		 * This constructor takes in the name of the source file and attempts to open it.  If
		 * unsuccessful it will throw a Usage error.  This constructor also reads in all the source
		 * file's data and populates a string vector with it.
		 * @param   string      infile      Path to input source file
		 */
		Lexer ( string infile );

		/**
		 * This function returns the next Token that is available during parsing of the source
		 * file. If any improper literals are seen, then this function will throw a Syntax error.
		 * @return  Token                   Returns Token object with populated data members
		 */
		Token nextToken ();

};