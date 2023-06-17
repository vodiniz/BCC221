#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;
class HorasExcedidas{
    string msg;
    int line;

public:
    HorasExcedidas(const string& msg, int line);
    ~HorasExcedidas();
    string what() const;
};

#endif