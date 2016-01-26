/*main.cpp*/

//
// Main program file for ELC: Expression Language Compiler
//
// Original Author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS473, Spring 2016
// Project 1
//

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <vector>

#include "exceptions.h"
#include "parser.h"

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::ofstream;


//
// processArgs:
//
// Processes cmd-line args to the compiler.  We are expecting 2:  elc filename.el.
// Returns back filename.el as the infile, and then filename.cpp as outfile.
// Throws a "UsageError" if the cmd-line arguments are not as expected.
//
void processArgs(int argc, char *argv[], string& infile, string& outfile)
{
  if (argc != 2)
    throw UsageError("elc sourcefile.el");

  // argv[0] is our program name
  // argv[1] is the file we are compiling:
  infile = argv[1];

  // we want outfile to be infile with .cpp extension:
  auto pos = infile.rfind('.');
  if (pos == string::npos)
    throw UsageError("elc sourcefile.el");

  string base = infile.substr(0, pos);
  outfile = base + ".cpp";

  //cout << "infile:  " << infile << endl;
  //cout << "outfile: " << outfile << endl;
}


//
// main:  for testing parser
//
int _main(int argc, char *argv[])
{
  string infile, outfile;

  try
  {
    processArgs(argc, argv, infile, outfile);

    cout << "compiling '" << infile << "' -> '" << outfile << "'" << endl;

    //
    // create parser and parse the input program to check for legality: 
    // 
    Parser parser(infile, outfile);

    parser.parse();
  }
  catch (exception& ex)
  {
    cout << ex.what() << endl;

    //
    // empty C++ file since we have an error, and write error msg instead:
    //
    std::ofstream  cppfile(outfile, std::ofstream::trunc);
    cppfile << ex.what() << endl;
  }

  return 0;
}


//
// Safely reads a line from a text file that came from an unknown 
// platform (i.e. it deals with different EOL sequences).
//
// Reference: http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
//
std::istream& safeGetline(std::istream& is, std::string& t)
{
  t.clear();

  // The characters in the stream are read one-by-one using a std::streambuf.
  // That is faster than reading them one-by-one using the std::istream.
  // Code that uses streambuf this way must be guarded by a sentry object.
  // The sentry object performs various tasks,
  // such as thread synchronization and updating the stream state.

  std::istream::sentry se(is, true);
  std::streambuf* sb = is.rdbuf();

  for (;;) {
    int c = sb->sbumpc();
    switch (c) {
    case '\n':
      return is;
    case '\r':
      if (sb->sgetc() == '\n')
        sb->sbumpc();
      return is;
    case EOF:
      // Also handle the case when the last line has no line ending
      if (t.empty())
        is.setstate(std::ios::eofbit);
      return is;
    default:
      t += (char)c;
    }
  }
}


//
// _identical:
//
// Returns 0 if the files are identical, otherwise it returns the line # where
// the files first differ.
//
size_t _identical(string outfile, string correctfile)
{
  std::vector<string> cppCode;
  std::vector<string> correctCode;
  string line;

  std::ifstream cppfile(outfile);
  std::ifstream correct(correctfile);

  //
  // let's make sure the correctness file can be found, otherwise there's
  // a problem with the installation probably:
  //
  if (!correct.good())
  {
    cout << "**ERROR: unable to open correctness file '"
      << correctfile
      << "'"
      << endl;
    cout << "**ERROR: are test files installed properly?"
      << endl;

    return 1;
  }
  
  //
  // okay, input files into 2 vectors.  Note that "safeGetline" is used
  // so that each line is input properly regardless of what platform we
  // are on vs. what type of input file we are reading.
  //
  while (safeGetline(cppfile, line))
    cppCode.push_back(line);

  while (safeGetline(correct, line))
    correctCode.push_back(line);

  //
  // now let's compare and see if identical:
  //
  size_t  i;

  for (i = 0; i < cppCode.size() && i < correctCode.size(); ++i)
  {
    if (cppCode[i] != correctCode[i])
      return (i + 1);  // line #'s start at 1:
  }

  //
  // if get here, make sure vectors are the same size, otherwise files differ:
  //
  if (cppCode.size() != correctCode.size())  // not the same size, so differ:
  {
    return (i + 1);  // line #'s start at 1:
  }
  
  //
  // if get here, files are identical!
  //
  return 0;
}


//
// main:  test harness for automatic testing
//
int main()
{
  int   argc = 2;
  char *argv[] = { "_main", "test01.el" };

  std::vector<string> cases{
    "./Tests-Parser/test01",  // working cases:
    "./Tests-Parser/test02",
    "./Tests-Parser/test03",
    "./Tests-Parser/test04",
    "./Tests-Parser/test05",

    "./Tests-Parser/test10",  // error cases:
    "./Tests-Parser/test11",
    "./Tests-Parser/test12",
    "./Tests-Parser/test13",
    "./Tests-Parser/test14",
    "./Tests-Parser/test15",
    "./Tests-Parser/test16",
    "./Tests-Parser/test17",
    "./Tests-Parser/test18",
    "./Tests-Parser/test19",
    "./Tests-Parser/test20",
    "./Tests-Parser/test21"
  };

  //
  // let's try to open the first test case to make sure the test files
  // are installed correctly:
  //
  {
    std::string    test1 = cases[0] + ".el";
    std::ifstream  infile(test1.c_str());

    if (!infile.good())
    {
      cout << endl
        << "**ERROR: cannot open first test case '"
        << test1
        << "'"
        << endl
        << endl;
      cout << "Are the test files installed properly?" 
        << endl
        << endl;

      return 0;
    }
  }

  int correct = 0;
  int incorrect = 0;

  //
  // Tests:
  //
  for (string base : cases)
  {
    string infile = base + ".el";
    string outfile = base +".cpp";
    string corfile = base + ".txt";

    {
      //
      // let's open and close C++ file to discard any previous output:
      //
      std::ofstream  cppfile(outfile, std::ofstream::trunc);
    }

    //
    // setup command-line args for this test case, and run compiler:
    //
    argv[1] = (char *) infile.c_str();

    _main(argc, argv);

    //
    // did it work?  Compare against correct output in .txt file:
    //
    size_t  lineNum = _identical(outfile, corfile);

    if (lineNum == 0)
    {
      correct++;
      cout << "**correct" << endl;
    }
    else
    {
      incorrect++;
      cout << "!!incorrect, first diff on line #" << lineNum << endl;
    }

    cout << endl;
  }//foreach

  //
  // done
  //
  cout << "Results:" << endl;
  cout << "  correct:   " << correct << endl;
  cout << "  incorrect: " << incorrect << endl;
  cout << endl;
  return 0;
}
