
#pragma once
#include "Pair.h"
#include "IllegalCoordinateException.h"
#include "IllegalCharException.h"
#include <sstream>
#include <fstream>
#include <cassert>
#include <string>
#include <cmath>
using namespace std;


class Board{

    Pair** array2D;


public:
    int tsize;
    bool **box;
    char *name=new char[200];
    int boardsize;
    Board(): Board(0){};
    Board(int length);
    Board(const Board& other);
    ~Board();
    Pair& operator[](const Pair& pt) ; //const std::pair<int,int>& Index
    Board& operator=(char chr);
    Board& operator=(const Board& other);
    void initial();
    void create(int size);
    void free();
    friend ostream& operator<<(ostream& os, const Board& br);
    friend void operator>> (istream& is, Board & br);

    void readfile();

    void createlines(int size);

    void createX(int startx, int endx, int starty, int endy);

    char* draw(int size);

    void createO(int startx, int endx, int starty, int endy);
};