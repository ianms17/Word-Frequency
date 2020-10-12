//
// Created by ianms on 3/25/2020.
//

#ifndef PROJ3_DSEXCEPTIONS_H
#define PROJ3_DSEXCEPTIONS_H

#include <iostream>
#include <string>
#include <stdexcept>
#include "Exceptions.h"

using namespace std;

/*
 * Class Underflow Exception
 * Error found when trying to perform operations on empty trees
 */
class UnderflowException : public Exceptions {
public:
    UnderflowException() : Exceptions("Underflow Exception") {}
};

/*
 * Class Illegal Argument Exception
 * Error found if argument passes is of the wrong type, or has invalid attributes
 */
class IllegalArgumentException : public Exceptions {
public:
    IllegalArgumentException() : Exceptions("Illegal Argument Exception") {}

};

/*
 * Class Array Index Out Of Bounds Exception
 * Error found when accessing table vector at invalid position
 */
class ArrayIndexOutOfBoundsException : public Exceptions {
public:
    ArrayIndexOutOfBoundsException() : Exceptions("Array Index Out of Bounds Exception") {}
};

/*
 * Class Iterator Out of Bounds Exception
 */
class IteratorOutOfBoundsException : public Exceptions {
public:
    IteratorOutOfBoundsException() : Exceptions("Iterator Out of Bounds Exception") {}
};

/*
 * Class Iterator Mismatch Exception
 */
class IteratorMismatchException : public Exceptions {
public:
    IteratorMismatchException() : Exceptions("Iterator Mismatch Exception") {}
};

/*
 * Class Iterator Unitialized Exception
 */
class IteratorUnitializedException : public Exceptions {
public:
    IteratorUnitializedException() : Exceptions("Illegal Argument Exception") {}
};

#endif //PROJ3_DSEXCEPTIONS_H
