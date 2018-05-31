#pragma once

#include<iostream>
using namespace std;


class Pair {
    int x;
    int y;
    char chr;

public:

    Pair();
    Pair(int x, int y); // , char chr);
    Pair& operator=(char chr);
    bool operator==(char other) const;
    operator char() const;
    int getX() const;
    int getY() const;
    char getChar() const;
    void setChar(const char chr) ;

};