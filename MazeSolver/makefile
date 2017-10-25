# Make file for assignment 8

OBJS	= maze.o mazeSolver.o
#pqTest.o 
CC	= g++ -Wall -pedantic -g -std=c++11
DEPS	= priorityQueue.h mazeSolver.h

all: maze

maze: $(OBJS)
	$(CC) -o maze $(OBJS)

maze.o: maze.cpp   $(DEPS)
	$(CC) -c maze.cpp

mazeSolver.o: mazeSolver.cpp $(DEPS)
	$(CC) -c mazeSolver.cpp

#pqTest.o: pqTest.cpp  $(DEPS)
#	$(CC) -o pqTest.cpp




# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

