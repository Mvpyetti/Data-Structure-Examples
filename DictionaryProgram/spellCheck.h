//Tommy Bonetti Section 1002
//Assignment 7
//The following is the header file that will use
//a hash table to spell check everything in the file from the
//given dictionary.
#include "hashTable.h"
#ifndef SPELLCHECK_H
#define SPELLCHECK_H

using namespace std;

class spellCheck
{
    public:
        spellCheck();                               //Will Initialize all applicable variables
        bool readDictionary(const string);          //Function will attempt to open the dictionary file name, and insert them into dictonary
        void showHashStats() const;                 //Function will call the hashTable function: showHashStats()
        bool setDocumentFileName(const string);     //Function will set the document file name.
        void showDocumentFilename(const string);    //Function will display the current value for the document file name
        void printHash() const;                     //Function will call the hashtable printHash()function to print hash numbers
        void checkSpelling(const bool);             //Function open the document file and check each word.
        void showTotalWordCount() const;            //Function should display current value for the word count.
        void showMisspellCount() const;             //Function should display the current value for the misspelled word count.'

    private:
        string docFileName;                         //Will Represent the document file name
        string dicFileName;                         //Will Represent the dictionary file name.
        unsigned int misspellCount;                 //Will Represent the amount of misspelled words
        unsigned int wordCount;                     //Will Represent the total amount of words.
        hashTable myWords;                          //Will Represent the hashTable for the dictionary words.
};

#endif // SPELLCHECK_H
