/*
 * File:    HashedSplays.h
 * Project: CSCE 221 - Project 3 - Word Frequency
 * Author : Ian Stephenson
 * Date   : 04/09/2020
 * Section: 517
 * E-mail: ims43@tamu.edu
 * Hashed Splay Tree Data Structure implementation
 */

#ifndef PROJ3_HASHEDSPLAYS_H
#define PROJ3_HASHEDSPLAYS_H

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "SplayTree.h"
#include "dsexceptions.h"
#include "Node.h"
#include "Util.h"
#define ALPHABET_SIZE 26

class HashedSplays {

public:
    /**********************************************************************
     * Name: HashedSplays (Constructor)
     * PreCondition: Size initializes number of spaces in the array
     *
     *
     * PostCondition:  Vector of m_tree number of SplayTrees
     *********************************************************************/
    HashedSplays(int size)
    {
        m_trees = size;

        // set table containing splay trees to size of alphabet given
        table.resize(m_trees);
    }

    /**********************************************************************
     * Name: ~HashedSplays
     * PreCondition: Constructed HashedSplay vector
     *
     * PostCondition:  Table vector will be emptied
     *********************************************************************/
    ~HashedSplays();

    /**********************************************************************
     * Name: FileReader
     * PreCondition: Passed value inFileName = input file
     *
     *
     * PostCondition: HashedSplay table filled with values from input file
     *********************************************************************/
    void FileReader(string inFileName);

    /**********************************************************************
     * Name: PrintTree (given index)
     * PreCondition: Passed value index referring to index in HashedSplay table
     *
     * PostCondition: Infix ordered tree referenced printed to cout
     *********************************************************************/
    void PrintTree(int index);

    /**********************************************************************
     * Name: PrintTree (given letter)
     * PreCondition: Passed value letter referring to tree beginning with that letter
     *
     * PostCondition: Infix ordered tree referenced printed to cout
     *********************************************************************/
    void PrintTree(string letter);

    /**********************************************************************
     * Name: PrintHashCountResults
     * PreCondition: None, nothing needed to output values in table
     *
     * PostCondition: Word at Root of each tree output to cout, along with
     *                its frequency, and the number of splays
     *********************************************************************/
    void PrintHashCountResults();

    /**********************************************************************
     * Name: FindAll
     * PreCondition: Passed a segment of a word as inPart
     *
     * PostCondition: Outputs all words beginning with that substring,
     *                along with the frequency of the word
     *********************************************************************/
    void FindAll(string inPart);

    int m_trees;

private:
    vector<SplayTree<Node>> table;

    /**********************************************************************
     * Name: Node (Constructor)
     * PreCondition: None.  Non parameter constructor requried for
     * container storage
     *
     * PostCondition:  Empty node object.
     *********************************************************************/
    int GetIndex(string inLetter);
};

// Destructor
HashedSplays::~HashedSplays()
{
    // iterate through indices of table, call makeEmpty on the trees
    for (int i = 0; i < m_trees; ++i)
    {
        table.at(i).makeEmpty();
    }

    // built in vector function clear will empty the vector object
    table.clear();
}

// File Reader
void HashedSplays::FileReader(string inFileName)
{

    // open fstream with input file and define word and firstLetter, variable declarations
    string lowerWord;
    string strippedWord;
    char firstLetter;
    int index = 0;
    fstream ifs;
    string word;

    // open the file and ensure its valid
    ifs.open(inFileName);
    if (!ifs)
    {
        // invalid file, file does not exist, terminate
        throw IllegalArgumentException();
    }
    else
    {
        // iterate through file as long as word can still be parsed from fstream
        while (ifs >> word)
        {
            // use util strip to remove punctuation and numbers
            strippedWord = Util::Strip(word);

            // check that strip didnt leave the string empty, empty string meant word was not alphabet data
            if (strippedWord.length() == 0)
            {
                continue;
            }

            // set word to lowercase for easier math operation
            lowerWord = Util::Lower(strippedWord);

            // variable holding firstLetter in word, determine position in vector
            firstLetter = lowerWord.at(0);

            // index equals ascii value - 97, 'a' = 97, 'a' - 97 = 0
            index = int(firstLetter) - 97;

            // declare new node to hold word to check equality
            // Node* wordNode = new Node(lowerWord, 1);
            Node wordNode(strippedWord, 1);

            // check that the table at pos=index contains the word found
            if (table.at(index).contains(wordNode))
            {
                // increment frequency of word, word already in tree
                table.at(index).getRootElement().IncrementFrequency();
            }
            else
            {
                // if the node isnt found, insert it and increment splay counter and nodeCounter
                table.at(index).insert(wordNode);
            }
        }
    }
    ifs.close();
}

// Print Hash Count Results
void HashedSplays::PrintHashCountResults()
{
    cout << "***************PRINT HASH COUNT RESULTS********************" << endl;
    for (int i = 0; i < m_trees; ++i)
    {
        // error check for empty tree, return special message
        if (table.at(i).isEmpty())
        {
            cout << "The tree at position " << i << " has no elements" << endl;
        }
        // tree has values, cout << TYPE=Node will format print statement properly
        else {
            cout << "The tree at position " << i << " starts with ";
            cout << table.at(i).getRootElement();
            cout << " and has " << table.at(i).GetNodeCounter() << " nodes" << endl;
        }
    }
    cout << endl << endl;
}

// Print Tree given Index
void HashedSplays::PrintTree(int index)
{
    cout << "**********PRINT TREE GIVEN INDEX************" << endl;
    // index greater than number of spaces in the array, terminate program
    if (index > m_trees)
    {
        throw ArrayIndexOutOfBoundsException();
    }
    else
    {
        // call printTree function from SplayTree.h, cout << Node will format the output
        table.at(index).printTree();
        cout << "This tree has had " << table.at(index).GetSplayCounter() << " splays" << endl;
    }
    cout << endl << endl;
}

// Print tree given letter
void HashedSplays::PrintTree(string letter)
{
    cout << "*************PRINT TREE GIVEN LETTER***************" << endl;
    // passed non single letter string
    if (letter.length() > 1)
    {
        throw IllegalArgumentException();
    }
    else
    {
        // call getIndex, if index is greater than the number of trees, index out of bounds thrown
        int index = GetIndex(letter);
        if (index >= m_trees)
        {
            throw ArrayIndexOutOfBoundsException();
        }
        else
        {
            // call printTree from SplayTree.h, cout << Node will format output
            table.at(index).printTree();
            cout << "This tree has had " << table.at(index).GetSplayCounter() << " splays" << endl;
        }
    }
    cout << endl << endl;
}

// Find All
void HashedSplays::FindAll(string inPart)
{
    cout << "************FIND ALL*************" << endl;
    // index given from the first letter of inPart
    int index = GetIndex(inPart.substr(0, 1));

    // cast string to Node object for comparison
    Node keyNode(inPart, 1);

    // index must be smaller than size of array
    if (index >= m_trees)
    {
        throw ArrayIndexOutOfBoundsException();
    }
    else
    {
        // call PrintSubstringNodes, outputs Node objects formatted with string and frequency
        cout << "Printing Nodes beginning with substring \'" << inPart << "\'" << endl;
        table.at(index).PrintSubstringNodes(keyNode);
    }
}

// GetIndex
int HashedSplays::GetIndex(string inLetter)
{
    // inLetter must be a single letter, not a substring
    if (inLetter.length() > 1)
    {
        throw IllegalArgumentException();
    }
    else
    {
        // convert string to lowercase, index = ascii value of letter - 97, 97 = ascii value of 'a'
        string lowerLetter = Util::Lower(inLetter);
        char tableLetter = lowerLetter.at(0);
        int index = int(tableLetter);
        return index - 97;
    }
}

#endif //PROJ3_HASHEDSPLAYS_H
