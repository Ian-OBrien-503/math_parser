// include header file
#include "math_parse.h"


int main()
{
  // local variables
  int error_check, result;
  string filepath;
  parser my_parser;

  cout << endl << "Welcome to Ian's mathematical expression parser\n";
  cout << "\n\nwhat input file would you like to use?\n";
  cin >> filepath;

  // load data and check for errors
  error_check = my_parser.load_data(filepath);

  for(int i = 0; i < 20; i++)
  {
    // check for empty string and return error if present
    error_check = my_parser.set_expression();
    if (error_check == 0)
      cout << "\n\t ERROR: empty expression detected\n\n";

    // remove all white space from string if any to # of characters
    //my_parser.remove_spaces();

    // parse and evaluate the string
    result = my_parser.parse_and_evaluate();
  }

  // end of program
  return 1;
}
