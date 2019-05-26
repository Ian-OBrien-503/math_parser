# math_parser
parses and evaluates simple mathematical expressions handles operators +, -, *, and /
handles expressions in the form of...  
let # = +, -, *, /  
num # num  
(num # num) # num  
num # (num # num)  
(num # num) # (num # num)  

if allowed more time to work on would make parser much more modular and handle expressions of any length, would start with these operators again and then move onto to exponents and modulus operators.


# instructions to run...
1) clone repo into a local directory (should only be one .cpp file, one .h file, and one data.txt file)
2) run g++ *.cpp to compile and then execute
3) when prompted for a file to input use "data.txt" or anthoer one provided it is formatted the same as data.txt
