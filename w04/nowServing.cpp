/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

Deque<helpRequest> helpRequestList;

/************************************************
 * NOW SERVING
 * Displays instructions for the user to input
 * either a normal help request, an emergency
 * help request, or no new help request (this minute).
 * Then execute the instruction.
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   string instr;
   int instructionCount = 0;
   helpRequest currentStudent;

   //There isn't anyone in the queue right now so there are no minutes left to wait.
   currentStudent.minutesleft = 0;
      do
      {

         cout << "<" << instructionCount << "> ";
         instructionCount++;
         cin >> instr;

         if (instr == "cs124" || instr == "cs165" || instr == "cs235")
         {
            addToHelpRequest(instr);
            currentStudent = handleCurrentStudent(currentStudent);
         }

         else if (instr == "!!")
         {

            newEmergencyHelpRequest();
            currentStudent = handleCurrentStudent(currentStudent);
         }
         else if (instr == "none")
         {

            currentStudent = handleCurrentStudent(currentStudent);
         }
         else if (instr != "finished")
         {
            cout << "Incorrect instruction. Please try again." << endl;

            cin.ignore(256, '\n');
            // cin.clear();
         }



      } while (instr != "finished");

      // end
      cout << "End of simulation\n";
      return;
}

/************************************************
 * ADDTOHELPREQUEST
 * Adds a normal request to the end of the deque
 * and labeled as not an emergency
 ***********************************************/
void addToHelpRequest(string className)
{
   string studentName;
   int minutesNeeded;
   cin >> studentName;
   cin >> minutesNeeded;
   helpRequest newHelpRequest;
   newHelpRequest.className = className;
   newHelpRequest.studentName = studentName;
   newHelpRequest.minutesleft = minutesNeeded;
   newHelpRequest.emergency = false;

   helpRequestList.push_back(newHelpRequest);
}

/************************************************
 * NEWEMERGENCYHELPREQUEST
 * Adds an emergency request to the front of the
 * deque and labels as an emergency.
 ***********************************************/
void newEmergencyHelpRequest()
{
   string className;
   string studentName;
   int minutesNeeded;
   cin >> className;
   cin >> studentName;
   cin >> minutesNeeded;
   helpRequest newHelpRequest;
   newHelpRequest.className = className;
   newHelpRequest.studentName = studentName;
   newHelpRequest.minutesleft = minutesNeeded;
   newHelpRequest.emergency = true;

   helpRequestList.push_front(newHelpRequest);
}

/************************************************
 * HANDLECURRENTSTUDENT
 * Determines if the Current student has used up his
 * alloted time. If so, check for the next student in the
 * deque. If there isn't one, do nothing. Return
 * the Current Student.
 ***********************************************/
helpRequest handleCurrentStudent(helpRequest currentStudent)
{
   //This function does nothing if the deque is empty and the current
   //student has no more time.
   if (!helpRequestList.empty() || currentStudent.minutesleft > 0)
   {
      //If the student has more time,
      //display his information and take a minute away.
      if (currentStudent.minutesleft > 0)
      {
         display(currentStudent);
         currentStudent.minutesleft--;
      }

      //Start serving the next student when
      //the current student has no more time left.
      else if(!helpRequestList.empty())
      {
         currentStudent = helpRequestList.front();
         helpRequestList.pop_front();
         display(currentStudent);
         currentStudent.minutesleft--;
      }
   }
   return currentStudent;
}

/************************************************
 * DISPLAY
 * Sends the current student's information on
 * the screen after each prompt. Information
 * includes student's name, class name, and
 * minutes left to be served.
 ***********************************************/
void display(helpRequest currentStudent)
{
   if (currentStudent.emergency)
   {
      cout << "\tEmergency for " << currentStudent.studentName
           << " for class " << currentStudent.className
           << ". Time left: " << currentStudent.minutesleft
           << endl;
   }
   else if (!currentStudent.emergency)
   {
      cout << "\tCurrently serving " << currentStudent.studentName
           << " for class " << currentStudent.className
           << ". Time left: " << currentStudent.minutesleft
           << endl;
   }
}
