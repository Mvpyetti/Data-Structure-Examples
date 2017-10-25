//Tommy Bonetti Assignment 7
//This is the implementation file for spellCheck

#include "spellCheck.h"
#include "hashTable.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

//Constructor will initialize well perform all applicable initializations
spellCheck::spellCheck() {
    docFileName = "";
    dicFileName = "";
    misspellCount = 0;
    /*
    NOTE: myWords hashTable is not initialized.
    */
}

//The function readDictionary will attempt to open the dictionary File name, and if
//the file is successfully read, the function will insert the words in the file to
//the hashTable "myWords." If the file is read unsuccessfully, the function will
//return false. The function will later close the file.
bool spellCheck::readDictionary(const string inDictWord) {
    //Create the ifstream file using the inDictWord as its name.
    ifstream dictFile(inDictWord);
    //Create the variable used to represent each word to be inserted into dictionary table
    string inWord;
    //Check if the file exists,
    if(dictFile.good()) {
        cout <<"dictfile exists" << endl;
        //dictFile.open(inDictWord.c_str());
        cout << "dictfile opened" << endl;
        dicFileName = inDictWord;
        //Begin looping through each and every word, and insert the words into myWord hashTable
        while(dictFile>>inWord) {
            myWords.insert(inWord);
            wordCount++;
            inWord = "";
        }
        dictFile.close();
        //Since the file was read successfully, return true
        return true;
    }
    else {
        //Unsuccessful file load
        return false;
    }
}

//setDocumentFileName will set the document file name.
//If the file exists the function will return true, if not
//it will return false.
bool spellCheck::setDocumentFileName(const string indocFileName) {
    //Check if the file exists, and if it exists set the document file name then return true.
    //otherwise return false.
    ifstream inFile(indocFileName.c_str());
    if(inFile) {
        docFileName = indocFileName;
        return true;
    }
    else
        return false;
}

//Spell Check will open the document file, and check each word. If there is an error opening,
//reading, or writing to either file, the function will display an error message. Function will
//read the input file one word at a time, look it up in the dictionary file, and check if it exists
//in the hashtable "Dictionary". If it does exists, then it is spelled right, otherwise it's incorrect.
//The bool "showMisspelledWrds" will act as a switch. If it is true then the function will show each misspelled
//word, if it false it will not show each word. Function will also show the count of mispelled words.
void spellCheck::checkSpelling(const bool showMisspelledWrds) {
    //Create variables necessary to check the words
    string checkWord = "";
    ifstream docFile(docFileName.c_str());

    //Begin the input While loop to check the words in the document file
    while(docFile >> checkWord) {

        //***********************************************************************************************
        //MAKE INTO CORRECT FORMAT
        //Make sure the word is lowercase and the symbols are removed by iterating through each character
        for(int i=0; i<checkWord.length(); i++) {
            //Check if its an alphabetical character
            if(isalpha(checkWord[i])) {
                //Check if its an uppercase
                if(isupper(checkWord[i]))
                    //if its uppercase, convert it to lowercase
                    checkWord[i] = tolower(checkWord[i]);
            }
            //if not an alphabetical character
            else {
               //if its the first character remove it
               if(i==0) {
                    checkWord.erase(0);
               }
               //now Check if the next character after it is also nonalphabetical.
               //if its nonalphabetical then it is training, so remove both.
               //and increment i to skip the next character.
               else {
                    if(i == (checkWord.length()-1)) {
                        checkWord.erase(i,1);
                    }
                    else {

                        checkWord.erase(i,1);
                         if(!(isalpha(checkWord[i+1]))) {
                            checkWord.erase(i+1,1);
                        }
                    }
               }
            }
        }
        //**************************************************************************************************

        //Lookup the word in the dictionary to see if it's spelled right
        //If the word is not found, then it is spelled incorrectly.
        if(!myWords.lookup(checkWord)) {
            //increment incorrectly spelled words counter
            misspellCount++;
            //if the showMisspelled word is true then display the incorrectly spelled word.
            if(showMisspelledWrds) {
                cout << "Not Found: " << checkWord << endl;
            }
        }
    }
}

//Function will display the current value for the document file name
void spellCheck::showDocumentFilename(string documentName) {
    cout << "Value for document:" << documentName << endl;
}

//Function will display the current value for word count
void spellCheck::showTotalWordCount() const {
    cout << "Total Words: " << wordCount << endl;
}

//Function will display the hash stats for the hash table
void spellCheck::showHashStats() const {
    myWords.showHashStats();
}

//Function will show the amount of misspelled words in the document
void spellCheck::showMisspellCount() const {
    cout << "Misspelled Word Count: " << misspellCount << endl;
}

//Function will print the hash stats of the dictionary file.
void spellCheck::printHash() const {
    myWords.printHash();
}


