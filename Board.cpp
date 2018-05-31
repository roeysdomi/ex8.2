#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <thread>
#include "Board.h"
#include "IllegalCoordinateException.h"
#include "IllegalCharException.h"

using namespace std;


Board::Board(int size) {
    create(size);

}

Board::Board(const Board& other){
    create(other.tsize);

    for (int i = 0; i < other.tsize; i++)
        for (int j = 0; j < other.tsize; j++)
            array2D[i][j] = other.array2D[i][j];
}

Board::~Board() {
    free();
}

void Board::create(int size) {

        tsize = size;
        array2D = new Pair *[tsize];
        for (int i = 0; i < tsize; ++i)
            array2D[i] = new Pair[tsize];


}

ostream& operator<<(ostream& os, const Board& br) {
    for (int i = 0; i < br.tsize; i++) {
        for (int j = 0; j < br.tsize; j++) {
            os << br.array2D[i][j].getChar();
        }
        os << "" << endl;
    }
    return os;
}

void operator>> (istream& is, Board & br)
{

    is>> br.name;
    br.readfile();
    return;
}


Pair& Board::operator[](const Pair& pt) {
    if (pt.getX() < 0 || pt.getX() >= tsize || pt.getY() < 0 || pt.getY() >= tsize)
        throw IllegalCoordinateException(pt.getX(), pt.getY());
    return array2D[pt.getX()][pt.getY()];

}

Board& Board::operator=(char chr) {
    if (chr != '.')
        throw IllegalCharException(chr);
    initial();
    return *this;

}

Board& Board::operator=(const Board& other) {
    if(this != &other){
        if (tsize != other.tsize) {
            free();
            create(other.tsize);

        }
        for (int i = 0; i < other.tsize; i++)
            for (int j = 0; j < other.tsize; j++)
                array2D[i][j] = other.array2D[i][j];


    }
    return *this;
}

void Board::free() {
    for (int i = 0; i < tsize; i++)
        delete[] array2D[i]; // delete array within matrix
    delete[] array2D;  // delete actual matrix

}

void Board::initial() {
    for (int i = 0; i < tsize; i++)
        for (int j = 0; j < tsize; j++)
            array2D[i][j].setChar('.');
}

void Board::createlines(int size) {
    box = new bool *[size];
    for (int i = 0; i < size; ++i)
        box[i] = new bool[size];
    /////-----intalize-----
    for (int j = 0; j < size; ++j)
    {
        for (int i = 0; i < size; ++i)
        {
            box[j][i] = false;
        }
    }
    //----------create lines-----
    int part=size/tsize;
    for(int z=0;z<size;z=z+part)
    {
        for (int j = 0; j < size; ++j)  {
            for (int i = 0; i < size; ++i) {

                if(i==z||j==z)
                {
                    box[j][i]=true;

                }
                if(i==size-1||j==size-1)
                {
                    box[j][i]=true;

                }
            }
        }
    }

}
void Board ::createX(int startx,int endx,int starty,int endy)
{
    int q=startx;
    int w=endx;
    int e=starty;
    int r=endy;

    for(int i=starty;i<endy;i++)
    {

            box[e][q]=true;
            box[r][q]=true;
            e++;q++;
            r--;

    }


}
void Board ::createO(int startx,int endx,int starty,int endy)
{

    int midx=(startx+endx)/2;
    int midy=(starty+endy)/2;
    int dist=(abs(startx-endx))/tsize;

    for(int i=startx;i<endx;i++)
    {

        for(int j=starty;j<endy;j++)
        {

            int dist2=sqrt((midx-i)*(midx-i)+(midy-j)*(midy-j));

            if(dist==dist2)
            {
                box[j][i]=true;

            }
        }

    }
}
 char* Board::draw(int size)
{   int q=0;
    int w=0;
    size=size+5;
    createlines(size);
    int part=size/tsize;
    for(int i=0;i<size;i=i+part)
    {
         for(int j=0;j<size;j=j+part)
        {
            if(j+part<=size&&i+part<=size)
            {

                if(array2D[q][w]=='X')
                {createX(i,i+part,j,j+part);}
                if(array2D[q][w]=='O')
                {createO(i,i+part,j,j+part);}
            }
            w++;
        }
         q++;
    }

    ofstream imageFile("pic_result.ppm");
    imageFile << "P6" << endl << size <<" " << size << endl << 255 << endl;
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {

            char red = 0;
            char green = 0;
            char blue = 0;
            if (box[j][i]) { red = 255; }

            imageFile << red << green << blue;

        }

    }
    imageFile.close();

  return "pic_result.ppm";
}

void Board::readfile()

{
    int size;
    ifstream myReadFile;
    myReadFile.open(this->name);
    string output;
    if (myReadFile.is_open()) {
       if (!myReadFile.eof()) {


            myReadFile >> output;
            create(output.length());
            size=output.length();

        }
    }
    myReadFile.close();
    /////////
    ifstream myReadFile2;

    myReadFile2.open(this->name);
    string output2;
    int i=0;
    if (myReadFile2.is_open()) {
        while (!myReadFile2.eof()&&i<size) {
            myReadFile2 >> output2;
            const char*line=output2.c_str();
            for(int j=0;j<size;j++)
            {
                array2D[i][j]=line[j];

            }

           i++;
        }
    }

    myReadFile2.close();

}
///---305170490 roeysdomi