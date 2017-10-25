# Make file for assignment 11

OBJS	= pageRank.o directedGraph.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS	= directedGraph.h

all: pageRank 

pageRank: $(OBJS)
	$(CC) -o pageRank $(OBJS)

directedGraph.o: directedGraph.cpp $(DEPS)
	$(CC) -c directedGraph.cpp

pageRank.o: pageRank.cpp $(DEPS)
	$(CC) -c pageRank.cpp

# -----
# clean by removing object files.

clean:

	rm	$(OBJS)

