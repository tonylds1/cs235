/***********************************************************************
 * Module:
 *    Assignment 02, Stack
 *    Brother JonesL, CS 235
 * Author:
 *    Maximiliano Correa, Esteban Cabrera, Tony Moraes
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
#include "infix.h"     // for INFIX
#include <cctype>      // for isalpha isdigit isspace
#include <sstream>     // for stringstream
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using std::stringstream;
using std::cerr;
using std::vector;
//using namespace std;
using namespace custom;



/*******************************************
 * DISPLAY
 * Display the contents of the stack. We will
 * assume that T is a data-type that has the
 * insertion operator defined.
 *******************************************/
template <class T>
ostream & operator << (ostream & out, stack <T> rhs) throw (const char *)
{
   // we need to make a copy of the stack that is backwards
   stack <T> backwards;
   while (!rhs.empty())
   {
      backwards.push(rhs.top());
      rhs.pop();
   }

   // now we will display this one
   out << "{ ";
   while (!backwards.empty())
   {
      out << backwards.top() << ' ';
      backwards.pop();
   }
   out << '}';

   return out;
}
/*****************************************************
 * IS CHARACTER: ( ) ^ * / % + -
 * Checks to see if character is one of these operators
 *****************************************************/
bool isOperator (const char a) {
   char operators[] = "()^*/%+-";
   for (int i = 0; i < 8; i++) {
      if (a == operators[i])
         return true;
   }
   return false;
}

/**********************************
 * Return the operator prioroty number
 ***********************************/
int orderOfOperators(char op){
   switch(op){
      case '+':
         return 1;
         break;
      case '-':
         return 1;
         break;
      case '*':
         return 2;
         break;
      case '/':
         return 2;
         break;
      case '^':
         return 3;
         break;

   }
   return 0;
}

/*****************************************************
 * CONVERT STRING TO STACK
 * Convert each word or number in a string
 * into a stack, for better processing.
 *****************************************************/
stack <string> convertStringToStack(const string str)
{

   stack <string> tempStack;
   stack <string> revStack;
   int i = 0;
   // traverse through the string, processing each word
   while ( i < str.length() ) {
      if ( isspace( str[i]) ) {
         i++;
      }
      else if ( isalpha( str[i] ) ) {
         string tempString;
         stringstream ss;
         //push variable to stack
         for ( ; i < str.length() && !isOperator( str[i] ); i++ ){
            ss << str[i];
         }
         ss >> tempString;
         tempStack.push( tempString );
      }
      else if ( isdigit( str[i] ) || ( str[i] == '-' && isdigit( str[i+1] ) ) || ( str[i] == '.' && isdigit( str[i+1] ) ) ) {
         string tempString;
         stringstream ss;
         //push number to stack
         ss << str[i];
         i++;
         for ( ; i < str.length() && ( isdigit( str[i] ) || str[i] == '.'); i++ ){
            ss << str[i];
         }
         ss >> tempString;
         tempStack.push( tempString );
      }
      else if ( isOperator( str[i]) ){
         string tempString;
         stringstream ss;
         // push operator to stack
         ss << str[i];
         ss >> tempString;
         tempStack.push( tempString );
         i++;
      }
      else {
         cerr << "Invalid Infix ";
         i++;
      }
   }
   //cout << tempStack;
   int size = tempStack.size();
   // reverse stack
   for (int i = 0; i < size; i++) {
      revStack.push (tempStack.top());
      tempStack.pop();
   }
   //cout << revStack;
   return revStack;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   vector <string> postfix;
   stack <string> reverseInfix( convertStringToStack(infix) );
   // stack for the operators
   stack <string> op;
   int size = reverseInfix.size();
   for (int i = 0; i < size; i++){
      string tempStr = reverseInfix.top();
      if ( tempStr.length() > 1 || isdigit(tempStr[0]) || isalpha(tempStr[0]) ){
         postfix.push_back(tempStr);
      }
      else if (tempStr[0] == '('){
         op.push(tempStr);
      }
      else if (tempStr[0] == ')'){
         while (op.top()[0] != '('){
            postfix.push_back(op.top());
            op.pop();
         }
         op.pop();
      }
      
      else{
         while (!op.empty() && orderOfOperators(tempStr[0]) <= orderOfOperators(op.top()[0])){
            postfix.push_back( op.top());
            op.pop();
         }
         op.push(tempStr);
      }
      reverseInfix.pop();
   }
   while (!op.empty()){
      postfix.push_back(op.top());
      op.pop();
   }
   string postfixStr = " ";
   for (int i = 0; i < postfix.size(); i++) {
      postfixStr += postfix[i];
      if ( i < postfix.size() - 1)
         postfixStr += " ";
   }
   return postfixStr;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

      do
      {
         // prompt for infix
         cout << "infix > ";
         getline(cin, input);

         // handle errors
         if (cin.fail())
         {
            cin.clear();
            cin.ignore(256, '\n');
         }

         // generate postfix
         if (input != "quit")
         {
            string postfix = convertInfixToPostfix(input);
            cout << "\tpostfix: " << postfix << endl << endl;
         }
      }
      while (input != "quit");
}

/**********************************
 * Return the operator prioroty number
 ***********************************/
string getAssemblyOperation(string value) {
   switch(value) {
      case '+':
         return 'SAV';
         break;
      case '-':
         return 'LOAD';
         break;
      case '*':
         return 'MUL';
         break;
      case '/':
         return 2;
         break;
      case '^':
         return 3;
         break;

   }
   return 0;
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{

   string assembly;
   string rhs;
   string lhs;
   char actualVariable = 'A';

   stack <string> assembly;
   stack <string> reversePostfix( convertStringToStack(postfix) );

   for (int i = 0; i < reversePostfix.size(); i++) {
      string tempStr = reversePostfix.top();
      if ( tempStr.length() > 1 || isdigit(tempStr[0]) || isalpha(tempStr[0]) ){
         assembly.push(tempStr);
         continue;
      }

      rhs = 

   }
   
   return "need to complete algorithm";//assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

      do
      {
         // prompt for infix
         cout << "infix > ";
         getline(cin, input);

         // handle errors
         if (cin.fail())
         {
            cin.clear();
            cin.ignore(256, '\n');
         }

         // generate postfix
         if (input != "quit")
         {
            string postfix = convertInfixToPostfix(input);
            string assembly = convertPostfixToAssembly(postfix);
            cout << "\tassembly: " << assembly << endl << endl;
         }
      }
      while (input != "quit");
}