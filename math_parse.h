/*
 * Ian O'Brien
 *
 * This program parses mathematical expressions in the form of...
 * (([0-9] +|* [0-9])|([0-9] +|* [0-9])) +|*  (([0-9] +|* [0-9])|([0-9] +|* [0-9]))
 * and evaluates the expression
*/

// pre-processor directives
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
// for removing whitespace from strings
#include <algorithm>
using namespace std;

// global constants
const int strSize = 25;

// this is the main class for the program that handles all of the parsing and evaluating
class parser
{
  public:
    parser();
    int set_expression(string str);           // done
    int parse_and_evaluate();
    string remove_spaces();
  private:
    string expression;
    int l, r, ll, lr, rl, rr;
    char op1, op2, op3;
};


// constructor
parser::parser()
{
  expression = "";
  int l, r, ll, lr, rl, rr = 0;
  char op1, op2, op3 = '0';
}


// set expression and stick it in the parser object to do operations on it
int parser::set_expression(string str)
{
  if (str == "")
    return 0;
  else
    expression = str;
    return 1;
}


// removes all white space from the expression
string parser::remove_spaces()
{
  expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
  return expression;
}


// parse and evaluate expression
int parser::parse_and_evaluate()
{
  // check length of string to determine operation
  int str_len = expression.length();
  int result;
  float f_result;

  // in the form of num +|-|*|/ num
  if(str_len == 3)
  {
    // get the values/"tokens" of the expression
    l = atoi(&expression[0]);
    op1 = expression[1];
    r = atoi(&expression[2]);

    // determine the operation to be performed
    if (op1 == '+')
      result = l + r;
    else if (op1 ==  '-')
      result = l - r;
    else if (op1 == '*')
      result = l * r;
    else if (op1 == '/')
      f_result = float(l) / float(r);

    // if printing division result print float else print int result
    if(op1 = '/')
      cout << expression << "= " << f_result << endl;
    else
      cout << expression << "= " << result << endl;
  }

  // if the form of (num +|*|-|/ num) +|*|-|/ num
  // or in the form of num +|-|*|/ (num +|*|-|/ num)
  if(str_len ==
    return result;
}

