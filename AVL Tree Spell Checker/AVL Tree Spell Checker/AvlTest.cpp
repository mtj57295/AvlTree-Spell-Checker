// spellcheck.cpp 
// This doesn't do any spell checking yet; it's just a simple test of the AVL-based Table ADT.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "AvlTree.h"
#include <list>
using namespace std;

const string ITEM_NOT_FOUND = "999";
ofstream outFile;
string filename;
int totalOccurence;

void traverseandprint(string & s, int t, list<int> lines, list<int> pages)
{
	outFile << "Word: " << s << "\nOccurences: " << t << endl;
	outFile << "Misspelled word occurs on lines: ";
	for (list<int>::iterator itr = lines.begin(); itr != lines.end(); ++itr)
			outFile << *itr << "  ";
	outFile << endl <<  "Pages word occurs:  ";
	for (list<int>::iterator itr = pages.begin(); itr != pages.end(); ++itr)
		outFile << *itr << "  ";
	outFile << endl << endl;
	totalOccurence += t;
}

int main()
{   // constructs an empty tree of ints// that returns 99999 when find fails
	AvlTree<string> words(ITEM_NOT_FOUND);
	ifstream inFile;
	string line;
	string word="";
	
	cout << "Type in name of file to add to Avl Tree(fileName.txt): " << endl << flush;
	cin >> filename;
	inFile.open(filename);
	
	if (inFile.fail())
	{
		cout << "Error: couldn't open that file. \nPress enter to abort." << flush;
		cin.get();
		exit(EXIT_FAILURE);
	}
	int lineNumber = 1;
	while (getline(inFile, line))
	{
		for (int c = 0; c < line.length(); ++c)
		{
			if ((line[c] >= 'a' && line[c] <= 'z') || (line[c] >= 'A' && line[c] <= 'Z'))
			{
				if (line[c] >= 'A' && line[c] <= 'Z')
					line[c] += 32;
				word += line[c];
			}
			else if (word.length() >= 1)
			{
				if (words.find(word) != ITEM_NOT_FOUND)
					words.incOccurence(word);
				words.insert(word);
				words.setLines(lineNumber, word);
				words.setPages(lineNumber, word);
				word = "";
			}
		}
		if (word.length() >= 1) 
		{
			if (words.find(word) != ITEM_NOT_FOUND)
				words.incOccurence(word);
			words.insert(word);
			words.setLines(lineNumber, word);
			words.setPages(lineNumber, word);
			word = "";
		}
		++lineNumber;
	}
	inFile.close();
	
	cout << "Type in the dictionary so your file can be spelled checked (fileName.dct): " << endl << flush;
	cin >> filename;
	inFile.open(filename);
	
	if (inFile.fail())
	{
		cout << "Error: couldn't open that file. \nPress enter to abort." << flush;
		cin.get();
		exit(EXIT_FAILURE);
	}
	while (getline(inFile, word))
	{
		if (word[0] >= 'A' && word[0] <= 'Z')
			word[0] += 32;
		if (words.find(word) != ITEM_NOT_FOUND)
		{			
			words.remove(word);
		}
	}
	inFile.close();

	cout << "Type in error file (fileName.txt): " << endl;
	cin >> filename;
	outFile.open("error.txt");
	if (outFile.fail())
	{
		cout << "Error: couldn't open that file. \nPress enter to abort." << flush;
		cin.get();
		exit(EXIT_FAILURE);
	}
	
	outFile << "The total amount of distinct misspelled words: " << words.size() << endl << endl;
	words.traverse(traverseandprint);
	outFile << "The total amount of misspelled words: " << totalOccurence << endl << endl;
	
	cout << "Check error.txt file in folder: " << endl;
	
	char s;
	cin >> s;
	// wait for enter key
	return EXIT_SUCCESS;
}

