#include "IllegalCharException.h"




IllegalCharException::IllegalCharException(char chr):chr(chr)
{};


char IllegalCharException::theChar() const{
    return this->chr;
}