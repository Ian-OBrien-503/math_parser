// include header file
#include "math_parse.h"


int main()
{
  // local variables
  int error_check, result;
  string temp_string;
  string filepath;
  parser my_parser;

  cout << endl << "Welcome to Ian's mathematical expression parser\n";
  cout << "\n\nwhat input file would you like to use?\n";
  cin >> filepath;

  // load data and check for errors
  error_check = my_parser.load_data(filepath);
  if (error_check == 0)
    cout << "\n\t ERROR: was not able to open file... " << filepath << endl;

  for(int i = 0; i < num_data_items; i++)
  {
    // check for empty string and return error if present
    error_check = my_parser.set_expression();
    if(error_check == 0)
      break;

    // parse and evaluate the string
    error_check = my_parser.parse_and_evaluate();
    if(error_check == 0)
      cout << "\n\tstrings of this type are not supported by this program yet\n";

  }

  // end of program
  return 1;
}
