// Implementation of ADT Dictionary
//     data object: a bunch of texting abbreviations and their meanings 
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename dictionary.cpp
#include "dictionary.h"
#include "stack.h"
#include <iostream>


struct DictionaryRecord
{
	Stack* hashTablePtr;
	int numberOfItems;
};


const int TABLESIZE = 11;

//Hashes a key value
//
//pre	key value exists in an item object
//post	returns the key's integer value modulo(%) TABLESIZE to hash to an address
//usage	hashAddress = hashFunction(aKey);
int hashFunction(const Key& theKey)
{
	return (theKey.convertToInteger() % TABLESIZE);
}

//prints a single stack
//
//pre	stack of item objects exists
//post	a deep copy of the passed stack is made, printed, then deleted
//usage	printSingleStack(output, stack);
void printSingleStack(ostream& output, Stack stackCopy)
{
	Item topItem;
	while(not stackCopy.isEmpty())
	{
		stackCopy.getTop(topItem);
		output << "	->	" << topItem << endl;
		stackCopy.pop();
	}	
}

// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.
//       for example (caveat: these texts may hash to a different address)
//       address       text  meaning
//           0:
//                ->   lol   laugh out loud  
//                ->   ttyl  talk to you later
//           1:
//                ->   smh   shake my head 
// usage: outfile << myDictionary;    

ostream& operator<< (ostream& output, const Dictionary& rightHandSideDictionary)
{
	
	cout << "Address		Text	Meaning" <<endl;
	for (int i = 0 ; i < TABLESIZE; i++)
	{
		cout << " " << i << ":" << endl;
		printSingleStack(output, rightHandSideDictionary.dictionaryPtr->hashTablePtr[i]);
		cout << endl;
	}
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, Dictionary& rightHandSideDictionary)
{
	bool isFull;
	bool isAlreadyThere;
	int numberOfItems = 0;
	input >> numberOfItems;
	for (int i = 0 ; (i < numberOfItems and not isFull); i++)
	{
		Item anItem;
		input >> anItem;
		if (not anItem.isEmpty())
		{
			rightHandSideDictionary.addNewEntry(anItem, isFull, isAlreadyThere);
		}
	}
	return input;
}

// creates a new dictionary
// post: Dictionary object exists but is empty
// usage: Dictionary myDictionary;	
Dictionary::Dictionary(){
	dictionaryPtr = new DictionaryRecord;
	dictionaryPtr->numberOfItems = 0; 
	dictionaryPtr->hashTablePtr = new Stack[TABLESIZE];
}

// destroys a dictionary
// pre: Dictionary object exists
// post: all memory for Dictionary object has been freed
// usage: automatically done at the end of scope
Dictionary::~Dictionary()
{
	delete [] dictionaryPtr->hashTablePtr;
	dictionaryPtr->hashTablePtr = nullptr;
	delete dictionaryPtr;
	dictionaryPtr = nullptr;
}

// searchs for a meaning with a given text
// pre targetText has been assigned 
// post if an item with texting abbreviation the same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void Dictionary::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	int address;
	int hashIndex;
	address = hashFunction(targetText);
	hashIndex = address;
	Item topItem;
	Stack copyStack(dictionaryPtr->hashTablePtr[hashIndex]);
	
	while (not copyStack.isEmpty() and not isFound)
	{
		copyStack.getTop(topItem);
		if (topItem == targetText)
		{
			isFound = true;
			anItem = topItem;
		}
		else
		{
			copyStack.pop();
		}
		
	}
}

// inserts a new text' item into the dictionary
// pre: newItem has been assigned and is not already there
// post: if there is room in the Dictionary object isFull is false
//            and newItem is appropriately added
//       else either isFull is true or isAlreadyThere is true, depending
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void Dictionary::addNewEntry(const Item& newItem, bool& isFull, bool& isAlreadyThere)
{
	int address;
	isAlreadyThere = false;
	bool isAdded;
	isFull = (dictionaryPtr->numberOfItems == TABLESIZE);
	address = hashFunction(newItem);
	
	dictionaryPtr->hashTablePtr[address].push(newItem, isAdded);
	dictionaryPtr->numberOfItems++;
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if Dictionary object is not empty and 
//           targetText is found in Dictionary object, isFound is true
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else isFound is false or isEmpty is true depending
// usage: myDictionary.deleteEntry(myText, isEmpty, isFound);
void Dictionary::deleteEntry(const Key& targetText, bool& isEmpty, bool& isFound)
{
	bool isAdded;
	int address;
	int hashIndex;
	Item topItem;
	Stack newStack;
	address = hashFunction(targetText);
	hashIndex = address;
	if (not isEmpty) 
	{
		dictionaryPtr->hashTablePtr[hashIndex].getTop(topItem);
		while (not (dictionaryPtr->hashTablePtr[hashIndex].isEmpty()) and not (topItem == targetText))
		{
			//dictionaryPtr->hashTablePtr[hashIndex].getTop(topItem);
			newStack.push(topItem, isAdded);
			dictionaryPtr->hashTablePtr[hashIndex].pop();
			dictionaryPtr->hashTablePtr[hashIndex].getTop(topItem);
		}
		dictionaryPtr->hashTablePtr[hashIndex].pop();
		while (not newStack.isEmpty())
		{
			newStack.getTop(topItem);
			dictionaryPtr->hashTablePtr[hashIndex].push(topItem, isAdded);
			newStack.pop();
		}
	}
}
