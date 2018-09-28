###############################################################
# Program:
#     Assignment 01, Vector
#     Brother JonesL, CS235
# Author:
#     Tony Moraes
# Summary:
#     Use of the First structure of the course, Templates, to implement
#     my own version of the vector class.
# Time:
#     first version 1 hour
#     second version 6 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment01.o
	g++ -o a.out assignment01.o -std=c++11
	tar -cf assignment01.tar vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: vector.h assignment01.cpp
	g++ -c assignment01.cpp -std=c++11

