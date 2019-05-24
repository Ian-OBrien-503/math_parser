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
    int set_expression();
    int parse_and_evaluate();
    void remove_spaces();
    int load_data(string filepath);
  private:
    string expression;
    string data[100];
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
int parser::set_expression()
{
  static int count = 0;

  if (data[count] == "empty expression")
    return 0;
  else
    expression = data[count];
    count++;
    return 1;
}


// removes all white space from the expression
void parser::remove_spaces()
{
  expression.erase(remove(expression.begin(), expression.end(), ' '), expression.end());
}


// parse and evaluate expression
int parser::parse_and_evaluate()
{
  // check length of string to determine operation
  int str_len = expression.length();
  float result;
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
      result = float(l) / float(r);

    // if printing division result print float else print int result
    cout << expression << "= " << result << endl;
  }

  // if the form of (num +|*|-|/ num) +|*|-|/ num
  // or in the form of num +|-|*|/ (num +|*|-|/ num)
  else if(str_len == 7)
  {
    float sub_result;

    // case where paren is on LHS
    if(expression[0] == '(')
    {
      // get tokens
      ll = atoi(&expression[1]);
      op1 = expression[2];
      lr = atoi(&expression[3]);
      op2 = expression[5];
      r = atoi(&expression[6]);

      // handle LHS
      if (op1 == '+')
        sub_result = ll + lr;
      else if (op1 ==  '-')
        sub_result = ll - lr;
      else if (op1 == '*')
        sub_result = ll * lr;
      else if (op1 == '/')
        sub_result = float(ll) / float(lr);

      // handle LHS + RHS
      if (op2 == '+')
        result = sub_result + r;
      else if (op2 ==  '-')
        result = sub_result - r;
      else if (op2 == '*')
        result = sub_result * r;
      else if (op2 == '/' && op1 != '/')
        result = float(sub_result) / float(r);
      else if (op2 == '/' && op1 == '/')
        result = sub_result / float(r);
    }
    // case where paren is on RHS
    else
    {
      // get tokens
      l = atoi(&expression[0]);
      op1 = expression[1];
      rl = atoi(&expression[3]);
      op2 = expression[4];
      rr = atoi(&expression[5]);

      // handle RHS
      if (op2 == '+')
        sub_result = rl + rr;
      else if (op2 ==  '-')
        sub_result = rl - rr;
      else if (op2 == '*')
        sub_result = rl * rr;
      else if (op2 == '/')
        sub_result = float(rl) / float(rr);

      // handle LHS  and RHS
      if (op1 == '+')
        result = sub_result + l;
      else if (op1 ==  '-')
        result = l - sub_result;
      else if (op1 == '*')
        result = sub_result * l;
      else if (op1 == '/' && op2 != '/')
        result = float(l) / float(sub_result);
      else if (op1 == '/' && op2 == '/')
        result = float(l) / sub_result;
    }

    cout << expression << "= " << result << endl;
    return 1;
  }
}


// load data from a text file
int parser::load_data(string filepath)
{
  fstream inFile;
  string data_item;
  int count = 0;

  for(int i = 0; i < 100; i++)
  {
    data[i] = "empty";
  }

  inFile.open(filepath.c_str());
  if(!inFile.is_open())
    return 0;
  else
  {
    inFile >> data_item;
    data[count] = data_item;
    while(!inFile.eof())
    {
      count++;
      inFile >> data_item;
      data[count] = data_item;
    }
    return 1;
  }
}
