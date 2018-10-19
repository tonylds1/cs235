/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

/********************************************
 * READ
 * Read the fish's name.
 * Return FALSE for error and TRUE for success
 *******************************************/
bool read(char fileName[], custom::set <Card> & cards)
{
   // open the file for reading
   ifstream fin(fileName);              // connect to "fileName"
   if (fin.fail())                      // never forget to check for errors
   {
      cout << "Unable to open file "    // inform user of the error
           << fileName
           << endl;
      return false;                     // return and report
   }

   // do the work
   char fishName[256];
   // keep reading as long as not at the end of the file
   while (!fin.eof())
   {
      // note that if this fails to rad anything (such as when there
      // is nothing bug a white space between the file pointer and the
      // end of the file), then text will keep the same value as the
      // previous execution of the loop
      fin >> fishName;
      Card card(fishName);
      cards.insert(card);
   }

   // close
   fin.close();

   return true;                         // return and report
}

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
    custom::set <Card> cards;
    read("/home/cs235/week05/hand.txt", cards);

    char fishName[256];
    int size = cards.size();
    int matches = 0;

    cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand" << endl;

    for (int i = 1; i < 6; i++) {
        cout << "round " << i << ": ";
        cin >> fishName;

        Card card(fishName);
        cards.erase(card);

        if (size != cards.size())
        {
            cout << "\tYou got a match!" << endl;
            matches++;
            size = cards.size();

            continue;
        }

        cout << "\tGo Fish!" << endl;
    }

    cout << "You have " << matches << " matches!" << endl;
    cout << "The remaining cards: ";

    for (int i = 0; i < cards.size(); i++)
    {
        cout << cards[i];

        if (i != cards.size() - 1)
        {
            cout << ", ";
        }
    }

    cout << endl;

    return ;
}

