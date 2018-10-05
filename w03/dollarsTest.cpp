/***********************************************************************
 * Program:
 *    DOLLARS TEST
 * Summary:
 *    This file will test the Dollars class
 * Author
 *    Br. Helfrich
 ************************************************************************/

#include <iostream>
#include "dollars.h"
using namespace std;

/*****************************************
 * MAIN - simple driver program
 *****************************************/
int main()
{
   // for ever
   for (;;)
   {
      Dollars d;
      cout << "> ";
      cin  >> d;
      cout << '\t' << d << endl;
   }

   return 0;
}
