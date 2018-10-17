/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE
#include <string>
using namespace std;

struct helpRequest
{
   string className;
   string studentName;
   int minutesleft;
   bool emergency;

};


// the interactive nowServing program
void nowServing();
void newEmergencyHelpRequest();
helpRequest handleCurrentStudent(helpRequest currentStudent);
void addToHelpRequest(string className);
void display(helpRequest currentStudent);


#endif // NOW_SERVING_H
