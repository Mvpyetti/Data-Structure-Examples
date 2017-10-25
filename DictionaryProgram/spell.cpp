//  CS 302 Assignment #8
// Tommy Bonetti Section 1002
// Date: 10/26/2016
//  Main program for text-based spell check.

#include <iostream>
#include <fstream>
#include <string>

#include "spellCheck.h"

using namespace std;

int main(int argc, char* argv[])
{

// *****************************************************************
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');
	string	dictionaryFile;
	string	textFile;
	spellCheck	myDoc;
	bool	showMisspelledWords = false;

	cout << bars << endl << "CS 302 - Assignment #7" << endl;
	cout << endl;

// ------------------------------------------------------------------
//  Verify command line arguments.
//	Error out if bad, set user selection if good.
//	Note, -p option only used for testing.

	if (argc == 1) {
		cout << "Usage: words -d <dictionaryFile> -t <inputTextFile> <sh|ns>" << endl;
		return 0;
	}

	if (argc != 6) {
		cout << "Error, invalid command line options." << endl;
		return	0;
	}

	if (string(argv[1]) != "-d") {
		cout << "Error, invalid dictionary file specifier." << endl;
		return	0;
	}

	if (string(argv[3]) != "-f") {
		cout << "Error, invalid text file specifier." << endl;
		return	0;
	}

	if (string(argv[5]) == "-sh" || string(argv[5]) == "-ns") {
		if (string(argv[5]) == "-sh")
			showMisspelledWords = true;
	} else {
		cout << "Error, invalid show misspelled words file specifier." << endl;
		return	0;
	}

	dictionaryFile = string(argv[2]);
	if (!myDoc.readDictionary(dictionaryFile) ) {
		cout << "Error, read dictionary file: " << textFile << " ." << endl;
		return	0;
	}

	textFile = string(argv[4]);
	if (!myDoc.setDocumentFileName(textFile)) {
		cout << "Error, unable to open: " << textFile << " ." << endl;
		return	0;
	}

	// Show stats for reference.

	myDoc.showHashStats();

// ------------------------------------------------------------------
//  Do the spellcheck.

	cout << endl;
	myDoc.checkSpelling(showMisspelledWords);
	cout << endl;
	myDoc.showMisspellCount();
	cout << endl;

// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}

