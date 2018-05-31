#pragma once


class IllegalCharException{

    char chr;

public:
    IllegalCharException(char chr);
    char theChar() const;


};