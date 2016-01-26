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
 * @license GNU Public License <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

// Set included libraries and define our namespace
#pragma  once
#include <iostream>
#include <string>
#include <fstream>
#include "lexer.h"

using namespace std;

/**
 * The Parser class includes definitions for an instance of the Lexer class as well as the most up
 * to date Token that the Lexer has produced.  This class also holds the output file stream that it
 * will use to output into.  There also exist private functions which were derived from the CFG
 * that we made for our language. This class also includes a match function which will get the next
 * Token available using the private data member Lexer.  The purpose of this object would be to
 * make sure that the source code that was inputed is syntacticly valid based on out languages
 * definition.
 */
class Parser {

	private:

		/**
		 * This variable will hold the Lexer object and it will be able to access the Lexer
		 * functions privately within the objects scope.
		 * @var 	Lexer
		 */
		Lexer Lexer;

		/**
		 * This variable will keep track of the current Token that out Lexer has parsed out.
		 * @var 	Token
		 */
		Token CurrentToken;

		/**
		 * This is an instance of ofstream and it will be initialized within the constructor.  It
		 * will be used to direct output into the output file.
		 * @var 	ofstream
		 */
		ofstream cppfile;

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void program ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void more_stmts ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void statements ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void input ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void more_input ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void input_op ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void output ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void more_output ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void output_op ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void output_val ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void assignment ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void expr ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void expr2 ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void md_expr ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void md_expr2 ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void pow_expr ();

		/**
		 * This function is derived from a CFL that was built in HW03.
		 * @return 	void
		 */
		void base_expr ();

		/**
		 * This function makes sure that the passed token id is equal to the current token id saved
		 * internally within the instance of the object.  If the Token is equal, it proceeds to get
		 * the next token that is available and saves it into the CurrentToken private data member,
		 * otherwise if they are not equal then the function throws an exception.
		 * @param 	TokenID 	passed 		The Token id to match it against the current one
		 * @throw 	exception 				Will throw a syntax error
		 * @return 	void
		 */
		void match ( TokenID passed );

	public:

		/**
		 * This constructor takes in the infile and outfile as strings and then uses them to pass
		 * the source file to the Lexer, and also to open up an ofstream and write in the results
		 * to the outfile.  This ofstream is known internally as cppfile.
		 * @param 	string 		infile 		The input file containing the source script
		 * @param 	string 		outfile 	The output file that this parser will print to
		 * @return 	void
		 */
		Parser ( string infile, string outfile );

		/**
		 * This function is called after the constructor is ran.  This function tries to parse the
		 * source file and validate its syntacticly.
		 * @return 	void
		 */
		void parse ();

};