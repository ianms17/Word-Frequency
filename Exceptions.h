//
// Created by ianms on 3/25/2020.
//

#ifndef PROJ3_EXCEPTIONS_H
#define PROJ3_EXCEPTIONS_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Exceptions {

public:
    Exceptions(string message) : m_message(message) {}

    string GetMessage()
    {
        return m_message;
    }

private:
    string m_message;
};

#endif //PROJ3_EXCEPTIONS_H
