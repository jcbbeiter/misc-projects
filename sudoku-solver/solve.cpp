#include <iostream>
#include "Cell.h"
#include "Board.h"
using namespace std;

//Data Structures - Lab 04: Cell.cpp
//Author: Jacob Beiter
//2-14-2017
//Main class for sudoku solver

int main(int argc, char *argv[])
{
    Board myboard;
    if(!myboard.read(argv[1]))
    {
        cout << "Error opening file '" << argv[1] << "'" << endl;
        return 1;
    }
    myboard.solve();
    myboard.print();

    return 0;
}
