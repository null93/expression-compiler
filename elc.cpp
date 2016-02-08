/**
 * Main driver for Expression Language Compiler - This header file contains classes
 * that will be used to handle errors within our compiler.  There are four different types of
 * errors: Syntax, Semantic, Usage, and Internal.  These errors are handled differently.
 * @version 1.0
 * @package Compiler
 * @category Main Wrapper
 * @author Rafael Grigorian
 * @license GNU Public License <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

// Include libraries and declare standard namespace
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "exceptions.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

using namespace std;

/**
 * This function parses arguments and handles errors dealing with the correct way to run this
 * program.
 * @param 	int 		argC 		Argument count
 * @param 	pointer 	argV 		Pointer to a char array
 * @param 	pointer 	infile 		pointer to a string
 * @param 	pointer 	outfile 	pointer to a string
 */
void arguments ( int argC, char * argV [], string& infile, string& outfile ) {
	// Check to see that we have two arguments passed
	if ( argC != 2 ) {
		// If we don't throw a usage error
		throw UsageError ("elc source_file.el");
	}
	// Set the infile name in main's scope
	infile = argV [ 1 ];
	// Change the extension for the outfile
	auto position = infile.rfind ('.');
	if ( position == string::npos) {
    	throw UsageError ("elc sourcefile.el");
	}
	// Replace extension to CPP
	string base = infile.substr ( 0, position );
	outfile = base + ".cpp";
}

int main ( int argC, char * argV [] ) {
	// Declare our infile and our outfile names
	string infile, outfile;
	// Attempt to compile
	try {
		// Parse arguments
		arguments ( argC, argV, infile, outfile );
		// output infile and outfile
		cout << "compiling '" << infile << "' -> '" << outfile << "'" << endl;
		// Initiate Parser class
		Parser Parser ( infile, outfile );
		// Parse the source file
		Parser.parse ();
	}
	catch ( exception& num ) {
		// Print out which error happened
		cout << num.what () << endl;
		// Truncate file and print exception
		ofstream cppfile ( outfile, ofstream::trunc );
		cppfile << num.what () << endl;
	}
	// Return with no errors
	return 0;
}