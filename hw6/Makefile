# HW6 Makefile
# The *only* change you should make is choosing the appropriate
# dependencies for calc.o according to whether you implemented
# the calculator in C or C++.

PROGRAMS = calcTest calcInteractive calcServer
CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=gnu11

#CXX = g++
#CXXFLAGS = -D__USE_POSIX -g -Wall -Wextra -pedantic -std=gnu++11

.PHONY : solution.zip clean

%.o : %.c
	$(CC) $(CFLAGS) -c $<

#%.o : %.cpp
#	$(CXX) $(CXXFLAGS) -c $<

all : $(PROGRAMS)

# Use this target to create solution.zip that you can submit to Gradescope
solution.zip :
	zip -9r solution.zip *.c *.cpp *.h Makefile

calcTest : calcTest.o calc.o tctest.o
	$(CXX) -o $@ calcTest.o calc.o tctest.o

calcInteractive : calcInteractive.o calc.o csapp.o
	$(CXX) -o $@ calcInteractive.o calc.o csapp.o -lpthread

calcServer : calcServer.o calc.o csapp.o
	$(CXX) -o $@ calcServer.o calc.o csapp.o -lpthread

# Targets for .o files with correct dependencies.
# Note that no commands are needed because of the pattern rules above.

# This one is appropriate if you used C++ for the calculator implementation
# calc.o : calc.cpp calc.h

# This one is appropriate if you used C for the calculator implementation
calc.o : calc.c calc.h

calcTest.o : calcTest.c tctest.h

tctest.o : tctest.c tctest.h

calcInteractive.o : calcInteractive.c calc.h csapp.h

csapp.o : csapp.c csapp.h

calcServer.o : calcServer.c calc.h csapp.h

clean :
	rm -f *.o $(PROGRAMS) solution.zip
