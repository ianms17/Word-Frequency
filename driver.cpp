/**************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 3 - Word Frequency
 * Author : 
 * Date   : 04-November-2014
 * Section: Lecture-02
 * E-mail:  
 *
 * HashedSplays Class implementation.
 *
 *************************************************************/
#include "HashedSplays.h"  // Includes constants
// #include "dsexceptions.h"
#include "Exceptions.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {

    try {
        // Instatiate the main object
        HashedSplays wordFrequecy(ALPHABET_SIZE);
        // Build the trees
        wordFrequecy.FileReader(argv[1]);

        // Test methods to show hashed splay trees work
        wordFrequecy.PrintHashCountResults();
        wordFrequecy.PrintTree(19); // Prints the "T" tree
        wordFrequecy.PrintTree("F");
        wordFrequecy.PrintTree("K"); // should be mpty running input1
        wordFrequecy.FindAll("The"); // should find all the's (ignoring case)
        cout << endl << endl;
    }
    // Error catching
    catch (Exceptions &cException) {
        cout << "EXCEPTION: " << cException.GetMessage() << endl;
        return 1;
    }
    
    //Uncomment for number of seconds running.
    cout << "*********RUNNING TIME*************" << endl;
    cout << clock() / (float)(CLOCKS_PER_SEC) << endl;
    return 0;
}
