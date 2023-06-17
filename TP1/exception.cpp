#include <iostream>
#include <string>
#include "exception.h"

using namespace std;
HorasExcedidas::HorasExcedidas(const string& msg, int line):
    msg(msg), line(line) {}
HorasExcedidas::~HorasExcedidas(){}
string HorasExcedidas::what() const {
    return this->msg + " on line " + to_string(this->line);
}
