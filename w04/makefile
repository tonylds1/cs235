###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother JonesL, CS235
# Author:
#     Maximiliano Correa, Esteban Cabrera and Tony Moraes
# Summary:
#     The deque is the double-ended queue. Now serving will
#     use the deque in order to give students with "emergencies"
#     to go after the person that is currently being served.  
#		
# Time:
#     6.00 hs
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
