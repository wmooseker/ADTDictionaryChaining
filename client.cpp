//Client test program for ADT Dictionary
//     data object: a bunch of texting abbreviations and their meanings 
//    
// filename client.cpp
//date September 25, 2018

#include "dictionary.h"

#include <iostream>
#include <fstream>
using namespace std;

void openTheFile(ifstream& inFile);

void closeTheFile(ifstream& inFile);

void inputToDictionary(ifstream& inFile ,Dictionary& theDictionary);

void inputToRepeatedAddress(ifstream& inFile ,Dictionary& theDictionary);

void searchForTwoItems(ifstream& inFile ,Dictionary& theDictionary);

void deleteAnItem(ifstream& inFile, Dictionary& theDictionary);

void searchForLastItem(ifstream& inFile, Dictionary& theDictionary);

//main function for running the testing client
int main() 
{
	ifstream inFile;
	Dictionary theDictionary;
	openTheFile(inFile);
	inputToDictionary(inFile, theDictionary);
	inputToRepeatedAddress(inFile, theDictionary);
	searchForTwoItems(inFile, theDictionary);
	deleteAnItem(inFile, theDictionary);
	searchForLastItem(inFile, theDictionary);
	closeTheFile(inFile);
	return 0;
}

//opens the input file for the client test items and keys
//
//pre	inputFile exists but is not opened
//post	inputFile opened
//usage	closeTheFile(inFile);
void openTheFile(ifstream& inFile)
{
	inFile.open("in.dat");
}
	
//closes the input file for the client test items and keys
//
//pre	inputFile exists and is open
//post	inputFile closed
//usage closeTheFile(inFile);
void closeTheFile(ifstream& inFile)
{
	inFile.close();
}

//inputs 4 items into the dictionary hash table, then displays the dictionary
//
//pre	inFile is open and has 4 items to be read from the first section for entry
//post	4 items read from the inFile and hashed to unique addresses, then output the dictionary
//usage	inputToDictionary(inFile, theDictionary);
void inputToDictionary(ifstream& inFile ,Dictionary& theDictionary)
{
	cout << "---------------------------------------------------------------------" << endl;
	cout << "	TASK A: input 4 Items to a unique hash address" << endl;
	cout << "---------------------------------------------------------------------" << endl;
	inFile >> theDictionary;//read first 4 Items from file
	cout << theDictionary << endl; // print Dictionary
}

//reads three fake texting abbreviations and their meanings to ONE address entered to in taskA
//
//pre	3 more items ready to be input from inFile that hash to the same address
//post	the 3 items are read to the same address and are pushed onto the stack
//usage	inputToRepeatedAddress(inFile, theDictionary);
void inputToRepeatedAddress(ifstream& inFile ,Dictionary& theDictionary)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK B: Read 3 fake Items to ONE address(rofl)" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	inFile >> theDictionary; //read next 3 fake text items
	cout << theDictionary << endl; // print dictionary to show successful linear probing
}

//reads two keys from a file, searches for them in the dictionary (one that takes one look,
//		and the first fake abbreviation in TaskB, then displays the Items found
//pre	two keys exist in the inFile to be searched
//post	two keys read into key objects, key objects searched in dictionary
//			by calling .searchForMeaning() and printed the Items found in the searches
//usage	searchForTwoItems(inFile, theDictionary);
void searchForTwoItems(ifstream& inFile ,Dictionary& theDictionary)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK C: Searching for two keys(in one look and while traversing the stack)" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	bool isFound = false;
	Key searchKeyOne, searchKeyTwo;
	cout << "Searching for the key 'brb' and made up key 'rolf'..." << endl;
	inFile >> searchKeyOne >> searchKeyTwo;
	Item searchedResultItemOne, searchedResultItemTwo;
	theDictionary.searchForMeaning(searchKeyOne, searchedResultItemOne, isFound);
	cout <<"	Item found by first search: " << searchedResultItemOne << endl;
	isFound = false;
	theDictionary.searchForMeaning(searchKeyTwo, searchedResultItemTwo, isFound);
	cout <<"	Item found by second search: " << searchedResultItemTwo << endl;
}

//deletes(marks) middle key from task B
//
//pre	key exists in inFile and is the same as second item read in taskB
//post	key read from inFile and after search, deleted
//usage	deleteAnItem(inFile, theDictionary);
void deleteAnItem(ifstream& inFile, Dictionary& theDictionary)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK D: Deleting an item 'rfol'" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	bool isEmpty = false;
	bool isFound = false;
	Key keyToBeDeleted;
	inFile >> keyToBeDeleted;
	theDictionary.deleteEntry(keyToBeDeleted, isEmpty, isFound);
	cout << theDictionary << endl;	
}	

//searches for the last key read in task B after an item has been deleted
//pre	key exists and can be read from inFile, same key as last read in task B
//post	key in inFile read into key object, then searched for and prints the found Item
//usage searchForLastItem(inFile, theDictionary)
void searchForLastItem(ifstream& inFile, Dictionary& theDictionary)
{	
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << "	TASK E: Searching for last key of taskB" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	bool isFound = false;
	Key searchKeyThree;
	inFile >> searchKeyThree;
	Item searchedResultItemThree;
	cout << "Searching for made up key 'rolf'" << endl;
	theDictionary.searchForMeaning(searchKeyThree, searchedResultItemThree, isFound);
	cout << "	Item found by third search: " << searchedResultItemThree << endl;
	cout << "-----------------------------------------------------------------------------" << endl;		
}

	