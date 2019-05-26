/*
 * Ian O'Brien
 *
 * this program parses and evaluates a series of of mathematical expressions from a text file, you can
 * change the number of expressions you can handle by changing the const_int num_data_items on line 22
 *
 * data is read in from a file of choice and parser will work as long as it is in correct format
 * current support for strings of length 3, 7, and 11 in the form of
 *
 * let op = +,-,*,/
 * num op num
 * (num op num) op num
 * num op (num op num)
 * (num op num) op (num op num)
 *
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
const int num_data_items = 100;


// this is the main class for the program that handles all of the parsing and evaluating
class parser
{
  public:
    parser();
    int set_expression();
    int parse_and_evaluate();
    int load_data(string filepath);
    int parse3();
    int parse7();
    int parse11();
  private:
    string expression;
    string data[num_data_items];
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

  if (data[count] == "")
    return 0;
  else
    expression = data[count];
    count++;
    return 1;
}


// parse and evaluate expression
int parser::parse_and_evaluate()
{
  // check length of string to determine operation
  int str_len = expression.length();
  int error_check;

  // check for 3 character long expression ex. 1+1
  if(str_len == 3)
    error_check = parse3();
  // check for 7 character long expression ex. (1+4)/2
  else if(str_len == 7)
    error_check = parse7();
  // check for 11 character long expression ex. (1+4)/(4-3)
  else if(str_len == 11)
    error_check = parse11();
  //no implemenatation for this string length yet
  else
    return 0;

  // error check for operators that were not implemented
  if(error_check == 0)
  {
    cout << "\n\t" << expression << "\n\tERROR: invalid expression not yet implemented";
    return 0;
  }

  // successful parse
  return 1;
}


// handles parsing and evaluating expressions 3 characters long
int parser::parse3()
{
  // get the values/"tokens" of the expression
  float result;
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
  else
    return 0;

  // if printing division result print float else print int result
  cout << expression << "= " << result << endl;
  return 1;
}


// handles parsing and evaluating expressions 7 characters long
int parser::parse7()
{
  float sub_result, result;

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
    else
      return 0;

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
    else
      return 0;
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
    else return 0;

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
    else return 0;
  }
  cout << expression << "= " << result << endl;
  return 1;
}


// handles parsing expressions of length 11 ex. (1+3) - (5*4)
int parser::parse11()
{
  float left_subresult, right_subresult, result;

  ll = atoi(&expression[1]);
  op1 = expression[2];
  lr = atoi(&expression[3]);
  op2 = expression[5];
  rl = atoi(&expression[7]);
  op3 = expression[8];
  rr = atoi(&expression[9]);

  // handle LHS
  if (op1 == '+')
    left_subresult = ll + lr;
  else if (op1 ==  '-')
    left_subresult = ll - lr;
  else if (op1 == '*')
    left_subresult = ll * lr;
  else if (op1 == '/')
    left_subresult = float(ll) / float(lr);
  else
    return 0;


  // handle RHS
  if (op3 == '+')
    right_subresult = rl + rr;
  else if (op3 ==  '-')
    right_subresult = rl - rr;
  else if (op3 == '*')
    right_subresult = rl * rr;
  else if (op3 == '/')
    right_subresult = float(rl) / float(rr);
  else
    return 0;

  // handle LHS  and RHS
  if (op2 == '+')
    result = left_subresult + right_subresult;
  else if (op2 ==  '-')
    result = left_subresult - right_subresult;
  else if (op2 == '*')
    result = left_subresult * right_subresult;
  else if (op2 == '/')
    result = float(left_subresult) / float(right_subresult);
  else
    return 0;

  cout << expression << "= " << result << endl;
  return 1;
}


// load data from a text file to be parsed and evaluated
int parser::load_data(string filepath)
{
  fstream inFile;
  string data_item;
  int count = 0;


  // open data file and read data from it
  inFile.open(filepath.c_str());
  if(!inFile.is_open())
    return 0;
  else
  {
    inFile >> data_item;
    //// eat white space
    //int temp = 0;
    //for (int i = 0; data_item[i]; i++)
    //{
    //  if (data_item[i] != ' ')
    //    data_item[temp++] = data_item[i];
    //}
    //data_item[temp] = '\0';
    data[count] = data_item;
    while(!inFile.eof())
    {
      count++;
      inFile >> data_item;
      data[count] = data_item;
    }
    data[count] = "";
    return 1;
  }
}
