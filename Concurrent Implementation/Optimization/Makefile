#Author: Eamonn Gaynor & Peter Cronin                                                         
#Date created: 4/5/2018                                                       
#Bugs: N/A                                                                      
#Purpose: Makefile to run main.cpp (Wator Simulator)                        
#File: Makefile                                                                 
#License: GPL - General Public License   

  
CC=g++
CPPFLAGS= -std=c++11 -pthread -fopenmp
CPPFILES=main.cpp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS) $(DEBUGFLAGS)

ALL: $(HFILES) $(CPPFILES)
	$(CC) -o main $(CPPFLAGS) $(CPPFILES) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
