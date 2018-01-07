#ifndef CELL_H
#define CELL_H

//Data Structures - Lab 04: Cell.h
//Author: Jacob Beiter
//2-14-2017
//File defining Cell struct for a sudoku solver

struct Cell
{
    public:
    int value;
    /*	0 or 1 to represent if given number is possible
	only need 9, but use 10 for simplicity
	so that you don't need to shift by one for every access.
	Obviously this isn't completely ideal, but fine for a small
	project like this.
    */

    int poss[10];
};

#endif
