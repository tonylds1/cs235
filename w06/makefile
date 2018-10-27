###############################################################
# Program:
#     Assignment 06, NODE
#     Brother JonesL, CS235
# Author:
#     Maximiliano Correa, Esteban Cabrera and Tony Moraes
# Summary:
#     The Node to be used in a linked list and some methods.
#     We tried to implement the InsertSorted but some thing was wrong 
#     with the pointer to insert after.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o  -g -std=c++11
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g -std=c++11
