//Tommy Bonetti Section 1002
//HashTable using quadratic probing.
//The following class will be used to implement hash data structure


#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

using namespace std;

class hashTable
{
    public:
        hashTable();                                                     //Will Initialize the Hash Table to an empty State. hashSize = 0, hash table dynamically allocated
        ~hashTable();                                                    //Recover Dynamically allocated Memory
        bool insert(string const);                                       //Insert the passed word into the hash table and return true.
        bool lookup(string const) const;                                 //Search the hash table for the passed string
        bool remove(string const);                                       //Search the hash table for the string, and if found remove it.
        void printHash() const;                                          //Print all non-empty and non-tombstone entries in the hash Table
        void showHashStats() const;                                      //Print the current hash size, current table resize count, and collision count.

    private:
        unsigned int hashSize;                                           //Represents the size of the Table
        unsigned int reSizeCount;                                        //Represents the amount of times the table has been resized
        unsigned int collisionCount;                                     //Represents the amount of collisions in the hash Table
        unsigned int wordCount;                                          //Represents the amount of words that aren't tombstoned.
        unsigned int counter;                                            //Represents the sizeCounter
        string * wordList;                                               //Dynamic array that will be used as the array to store the words.
        static constexpr double loadFactor = 0.65;                       //Represents the loadFactor, in which the table will have to be rehashed if it exceeds this number.
        static constexpr unsigned int initialHashSize = 1013;            //Represents the initial size of the HashTable

        unsigned int hash(string) const;                                //The hash function will return a hash from a passed string using Fowler-Noll-Vo FNV1
        void rehash();                                                  //Function should create a new hash table of the next larger size, and extract all entries from the current hash table.
};

#endif // HASHTABLE_H
