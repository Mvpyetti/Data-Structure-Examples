# Make file for hashTable.

OBJS	= spell.o hashTable.o spellCheck.o
CC	= g++ -Wall -pedantic -g -std=c++11
DEPS	= hashTable.h spellCheck.h

all: spell

spell: $(OBJS) $(DEPS)
	$(CC) -o spell $(OBJS)

hashTable.o: hashTable.cpp $(DEPS)
	$(CC) -c hashTable.cpp

spellCheck.o: spellCheck.cpp $(DEPS)
	$(CC) -c spellCheck.cpp

spell.o: spell.cpp $(DEPS)
	$(CC) -c spell.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

