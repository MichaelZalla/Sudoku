CC = g++
#CFLAGS = -c -Wall -ggdb -I.
CFLAGS = -c -ggdb -I.
LDFLAGS =
SOURCES = lib/Sudoku.cpp utils/utils.cpp
EXECUTABLE = bin/Sudoku
TESTS = tests/SudokuTest.h

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTSTEST = lib/Sudoku.o utils/utils.o

FLAGS = -Iinclude

all: $(SOURCES) $(EXECUTABLE)

# These next lines do a bit of magic found from http://stackoverflow.com/questions/2394609/makefile-header-dependencies
# Essentially it asks the compiler to read the .cpp files and generate the needed .h dependencies.
# This way if any .h file changes the correct .cpp files will be recompiled
depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
# End .h file magic

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -rf *o $(EXECUTABLE)
	-rm -f testrunner testrunner.cpp
	-rm -f ./.depend
	#-rm -f bin/*o
	#-rm -f lib/*o

# CXX Testing	
CXXTESTGEN = ./cxxtest/bin/cxxtestgen

test: testrunner
	./testrunner

testrunner: testrunner.cpp $(OBJECTSTEST)
	g++ -I. -I./cxxtest/ -o testrunner $(OBJECTSTEST) testrunner.cpp

testrunner.cpp: $(HEADERS) $(SOURCES) $(TESTS)
	$(CXXTESTGEN) --error-printer -o testrunner.cpp $(TESTS)

