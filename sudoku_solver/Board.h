#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

//Data Structures - Lab 04: Board.h
//Author: Jacob Beiter
//2-14-2017
//Header file for a board class for a sudoku solver

class Board
{
    public:
    Board();
    void print();
    bool read(char*);
    void update(Cell**);
    void solve();
    bool isSolved();

    private:
    Cell board[9][9];

     
};

#endif
