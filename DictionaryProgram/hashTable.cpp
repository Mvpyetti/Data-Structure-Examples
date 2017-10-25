#include "hashTable.h"
#include <string>
#include <array>
#include <iostream>

using namespace std;

//hashTable Constructor will be used to initialize the hash table to an empty state
//hashSize will be initialized, and other variables will be initialized to 0.
//wordList will be dynamically allocated.
hashTable::hashTable() {
    //initialize hashSize and allocate wordList array.
    hashSize = initialHashSize;
    wordList = new string[initialHashSize];

    //Initialize every location in the array to "*"
    for(unsigned int i=0; i<hashSize; i++)
        wordList[i] = "";

    //Initialize count variables to 0
    reSizeCount = 0;
    collisionCount = 0;
    wordCount = 0;
    counter = 0;
}

//hashTable destructor will recover the dynamically allocated array.
hashTable::~hashTable()
{
    delete[] wordList;
}

//Insert function will insert the passed word into the hash table and return true.
//If the hash table exceeds the load factor, the table will be rehashed via rehash function.
//Collisions will be accounted for as well as quadratic probing if it occurs.
bool hashTable::insert(const string inWord) {
    //hash the word in order to find the initial location in table to insert the word.
    int insertLocation = hash(inWord);
    bool successful = false;

    //Begin Loop for quadratic probing
    //Function will continue using quadratic probing until a suitable location has been found for the word.
    for(unsigned int i=1; i<=hashSize; i++) {
        //Check if the location is empty
        if(wordList[insertLocation] == "*" || wordList[insertLocation].std::string::empty()){
            //Since the location is empty, simply insert the word into the array then stop the loop.
            wordList[insertLocation] = inWord;
            //Since word was successfully inserted, increment the wordCount and exit the Loop.
            wordCount++;
            successful = true;
            break;
        }
        //If the hashLocation is not empty, then a collision occurs. Perform quadratic probing
        //and increment the collision counter until the word is inserted.
        else {
            //Increment the counter, since collision occurred.
            collisionCount++;

            //Use the quadratic probing algorithm to find the next available location.
            insertLocation = (insertLocation + i*i) % hashSize;
        }
    }

    //Begin checking to make sure the loadFactor of the table is less than required
    if((wordCount*1.0)/hashSize > loadFactor)
        rehash();

    if(successful) {
        //cout << "Success insert" << endl;
        return true;
    }
    else
        return false;
}

//lookup function will search the table for the passed string, and if found will return true.
//If the item is not found in the location, quadratic probing will be used. If the requested
//word to find is not found, the function will return false.

bool hashTable::lookup(const string lkupWord) const {
    //Hash the word in order to find the probable location of where it might be located
    int lkupLocation = hash(lkupWord);

    //Begin the quadratic probing loop in case the word isn't found initially
    for(unsigned int i=1; i<=hashSize; i++) {
        //If the word is found in the location, then return true since it has been found.
        if(wordList[lkupLocation]==lkupWord)
            return true;
        //If the word has not been found in the location then try looking it up using the next
        //available spot using quadratic probing.
        else
            lkupLocation = (lkupLocation + i*i) % hashSize;
    }

    //Since the word was not found in every possible location, return false
    return false;
}


//showHashStats will print the current hash size, current resize count, and the collision count.
void hashTable::showHashStats() const {
    cout << "Hash Stats" << endl;
    cout << "  Current Word Count: " << wordCount << endl;
    cout << "  Current Hash Size: " << hashSize << endl;
    cout << "  Hash Resize Operations: " << reSizeCount << endl;
    cout << "  Hash Collisions: " << collisionCount << endl;
}

//printHash will print all non-empty and non-tombstone entries in the hash table.
void hashTable::printHash() const {
    //Begin the loop for hashing
    for(unsigned int i=0; i<hashSize; i++) {
        //If the word does not contain a '*'(not tombstoned) and is not empty, then print it
        if(wordList[i] != "*" && wordList[i] != "")
            cout << wordList[i] << endl;
    }
}

//Function will a return a hash from the passed string using Fowler-Noll-Vo FNV1a hash
unsigned int hashTable::hash(string inWord) const {
    //Implement appropriate values for the 32-bit FVN1
    unsigned int FNV_prime = 16777619;
    unsigned int FNV_offset_basis = 2166136261;

    //The Fowler algorithm code:
    unsigned int returnhash = FNV_offset_basis;
    for(unsigned int i=0; i<inWord.length(); i++) {
        //XOR for each byte of data to be hashed
        returnhash = returnhash ^ inWord[i];
        returnhash = returnhash * FNV_prime;
    }

    //Return the return hash mod the table size to prevent segmentation fault.
    return (returnhash % hashSize);
}

//Function will search the hashTable for the passed string, and if its found
//remove it by marking it with a '*'. If collision occurs quadratic probing will be used
//Collision and Word count will be changed as appropriate.
bool hashTable::remove(const string rmvWord) {
    //Hash the word in order to find the initial probable location
    int rmvLocation = hash(rmvWord);

    if(!lookup(rmvWord)) {
        cout << "error doesn't exist" <<endl;
        return false;
    }

    //Begin loop for quadratic probing in case the word isn't found initially.
    for(unsigned int i=1; i<=hashSize; i++) {
        //Word has been found so then replace it with a tombstone "*" and decrease the word count.
        if(wordList[rmvLocation] == rmvWord) {
            wordList[rmvLocation] = '*';
            wordCount--;
            return true;
        }
        //Quadratically probe the location until the word has been found as well as increase collision count
        //if the spot is not empty.
        else {
            collisionCount++;
            rmvLocation = (rmvLocation + i*i) % hashSize;
        }
    }
    return false;
}

//Function rehash will create a new hash table of the next larger size in the array
// of hashsizes, and extract all entries from the current hash table, insert them into the new table, and delete
//the old hash table.
void hashTable::rehash() {
    reSizeCount++;
    string *newHash, *temp;
    int oldHashSize = hashSize;
    temp = wordList;

    //newSize will represent the next available size in the sizeArray
    unsigned int newsize;
    constexpr unsigned int hashSizes[12] = {30011, 60013, 120017, 240089, 480043, 960017, 1920013, 3840037, 7680103, 30720299, 15360161, 61440629};

    //Look for the location of the current hashSize, and make the newsize = hashSize location+1
    if(hashSize == initialHashSize) {
        newHash = new string[hashSizes[0]];
        hashSize = hashSizes[0];
    }
    else {
        newHash = new string[hashSizes[counter]];
        hashSize = hashSizes[counter];
    }
    counter++;
    wordList = newHash;
    wordCount = 0;

    //Go through every single non empty value in the original word list and rehash to the
    //bigger word list array.
    for(int i=0; i<oldHashSize; i++) {
        if(temp[i] != "*" && !(temp[i].std::string::empty()))
            insert(temp[i]);
    }

    delete [] temp;
}


