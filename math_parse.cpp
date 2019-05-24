// include header file
#include "math_parse.h"


//  function prototypes


int main()
{
  // local variables
  int error_check, result;
  string str1 = "1+6";
  string str2 = "";
  string str3 = "  1  /     4   ";
  string str4 = "(4*3)    - 9";
  string str5 = "9 - (4*3)";

  // instantiate a parser object
  parser my_parser;

  cout << endl << "Welcome to Ian's mathematical expression parser\n";

  // check for empty string and return error if present
  error_check = my_parser.set_expression(str4);
  if (error_check == 0)
    cout << "\n\t ERROR: empty expression detected\n\n";

  // remove all white space from string if any to # of characters
  my_parser.set_expression(my_parser.remove_spaces());

  // parse and evaluate the string
  result = my_parser.parse_and_evaluate();

  // end of program
  return 0;
}



// function definitions

