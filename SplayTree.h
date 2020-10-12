/*
 * File:    SplayTree.h
 * Project: CSCE 221 - Project 3 - Word Frequency
 * Author : Ian Stephenson
 * Date   : 04/09/2020
 * Section: 517
 * E-mail: ims43@tamu.edu
 * Splay Tree Data Structure implementation
 *
 * CHANGELOG: Alterations from given file
 *         Data members nodeCounter and splayCounter added, updated constructor to set to 0
 *         insert changed to increment nodeCounter
 *         remove changed to decrement nodeCounter
 *         splayCounter incremented after every call to splay function
 *         Functions added (functions can be found at the bottom of the public and private sections)
 *              GetSize (Bootstrap and Worker)
 *              GetRootElement
 *              GetNodeCounter
 *              GetSplayCounter
 *              PrintSubstringNodes (Bootstrap and Worker)
 */

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "dsexceptions.h"
#include <iostream>        // For NULL

using namespace std;

// SplayTree class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class SplayTree
{

    // friend class HashedSplays;

  public:
    SplayTree( )
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        splayCounter = 0;
        nodeCounter = 0;
    }

    SplayTree( const SplayTree & rhs )
    {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
        splayCounter = 0;
        nodeCounter = 0;
        *this = rhs;
    }

    ~SplayTree( )
    {
        makeEmpty( );
        delete nullNode;
    }

    /**
     * Find the smallest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     smaller than any item in the tree, then call findMin.
     * Return the smallest item or throw UnderflowException if empty.
     */
    const Comparable & findMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        BinaryNode *ptr = root;

        while( ptr->left != nullNode )
            ptr = ptr->left;

        splay( ptr->element, root );
        splayCounter++;
        return ptr->element;
    }

    /**
     * Find the largest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     larger than any item in the tree, then call findMax.
     * Return the largest item or throw UnderflowException if empty.
     */
    const Comparable & findMax( )
    {
        if( isEmpty( ) )
            throw UnderflowException( );

        BinaryNode *ptr = root;

        while( ptr->right != nullNode )
            ptr = ptr->right;

        splay( ptr->element, root );
        splayCounter++;
        return ptr->element;
    }


    bool contains( const Comparable & x )
    {
        if( isEmpty( ) )
            return false;
        splay( x, root );
        splayCounter++;
        return root->element == x;
    }

    bool isEmpty( ) const
    {
        return root == nullNode;
    }

    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    void makeEmpty( )
    {
    /******************************
     * Comment this out, because it is prone to excessive
     * recursion on degenerate trees. Use alternate algorithm.
        
        reclaimMemory( root );
        root = nullNode;
     *******************************/
        while( !isEmpty( ) )
        {
            findMax( );        // Splay max item to root
            remove( root->element );
        }
    }

    void insert( const Comparable & x )
    {
        static BinaryNode *newNode = NULL;

        if( newNode == NULL )
            newNode = new BinaryNode;
        newNode->element = x;

        if( root == nullNode )
        {
            newNode->left = newNode->right = nullNode;
            root = newNode;
            nodeCounter++;
        }
        else
        {
            splay( x, root );
            splayCounter++;
            if( x < root->element )
            {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
                nodeCounter++;
            }
            else
            if( root->element < x )
            {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullNode;
                root = newNode;
                nodeCounter++;
            }
            else
                return;
        }
        newNode = NULL;   // So next insert will call new
    }

    void remove( const Comparable & x )
    {
        BinaryNode *newTree;

            // If x is found, it will be at the root
        if( !contains( x ) )
            return;   // Item not found; do nothing

        if( root->left == nullNode )
        {
            newTree = root->right;
            nodeCounter--;
        }
        else
        {
            // Find the maximum in the left subtree
            // Splay it to the root; and then attach right child
            newTree = root->left;
            splay( x, newTree );
            splayCounter++;
            nodeCounter--;
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
    }

    const SplayTree & operator=( const SplayTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }

        return *this;
    }

    /*
     * Implemented Helper Function GetSize, returns number of nodes in tree
     */
    int GetSize()
    {
        // bootstrap call to getSize
        return GetSize(root);
    }

    /*
     * Implemented helper getNodeCounter
     */
    int GetNodeCounter()
    {
        // get number of nodes, data member incremented in insert, decremented in remove
        return nodeCounter;
    }
    /*
     * Implemented helper getSplayCounter
     */
    int GetSplayCounter()
    {
        // get number of splays that occurred, data member incremented after each call to splay function
        return splayCounter;
    }

    /*
     * Implemented helper function getRootElement, returns node element stored in root
     */
    Comparable& getRootElement()
    {
        // gets root, root=Node type at runtime
        return root->element;
    }

    /*
     * Print Substring Nodes, print tree function that only prints nodes containing a partition of the word
     */
    void PrintSubstringNodes(Comparable& key)
    {
        // cant output an empty tree
        if (isEmpty())
        {
            cout << "Tree contains no Nodes" << endl;
        }
        else
        {
            // bootstrap call to function
            PrintSubstringNodes(root, key);
        }
    }


private:
    struct BinaryNode
    {
        Comparable  element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( ) : left( NULL ), right( NULL ) { }
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
            : element( theElement ), left( lt ), right( rt ) { }
    };

    BinaryNode *root;
    BinaryNode *nullNode;
    int splayCounter;
    int nodeCounter;

    /**
     * Internal method to reclaim internal nodes in subtree t.
     * WARNING: This is prone to running out of stack space.
     */
    void reclaimMemory( BinaryNode * t )
    {
        if( t != t->left )
        {
            reclaimMemory( t->left );
            reclaimMemory( t->right );
            delete t;
        }
    }
    
    /**
     * Internal method to print a subtree t in sorted order.
     * WARNING: This is prone to running out of stack space.
     */
   void printTree( BinaryNode *t ) const
    {
        if( t != t->left )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     * WARNING: This is prone to running out of stack space.
     */
    BinaryNode * clone( BinaryNode * t ) const
    {
        if( t == t->left )  // Cannot test against nullNode!!!
            return nullNode;
        else
            return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }

        // Tree manipulations
    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    /**
     * Internal method to perform a top-down splay.
     * The last accessed node becomes the new root.
     * This method may be overridden to use a different
     * splaying algorithm, however, the splay tree code
     * depends on the accessed item going to the root.
     * x is the target item to splay around.
     * t is the root of the subtree to splay.
     */
    void splay( const Comparable & x, BinaryNode * & t )
    {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;   // Guarantee a match

        for( ; ; )
            if( x < t->element )
            {
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                if( t->left == nullNode )
                    break;
                // Link Right
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            }
            else if( t->element < x )
            {
                if( t->right->element < x )
                    rotateWithRightChild( t );
                if( t->right == nullNode )
                    break;
                // Link Left
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            }
            else
                break;

        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }

    /*
     * Get Size, used to find the size of the entire tree
     */
    int GetSize (BinaryNode* t)
    {
        int count = 0;
        if (t != NULL)
        {
            GetSize(t->left);
            count++;
            GetSize(t->right);
        }
        return count;
    }

    /*
     * Print Substring Nodes, print tree function that only prints nodes containing a partitition of the word
     */
    void PrintSubstringNodes (BinaryNode* t, Comparable& key)
    {
        if( t != t->left )
        {
            PrintSubstringNodes(t->left, key);
            // overloaded % returns boolean if Node contains substring, recursive calls to left and right children
            if (key % t->element)
            {
                cout << t->element << endl;
            }
            PrintSubstringNodes(t->right, key);
        }
    }
};

#endif
