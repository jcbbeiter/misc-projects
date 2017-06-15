#include <iostream>
#include <fstream>
#include "Board.h"
#include "Cell.h"
using namespace std;

//Data Structures - Lab 04: Board.cpp
//Author: Jacob Beiter
//2-14-2017
//implementation for Board class for sudoku solver
//uses Cell struct

//constructor - initializes board to blank
Board::Board()
{
    //initializes all Cells
    for(int r = 0; r < 9; r++)
        for(int c = 0; c < 9; c++)
        {
            board[r][c].value = 0;
            //all values are possible
            for(int i = 0; i < 10; i++)
	    {
                board[r][c].poss[i] = 1;
		//except 0
		board[r][c].poss[0] = 0;
	    }

        }
}

//print function - display board
void Board::print()
{
    for(int r = 0; r < 9; r++)
    {
        for(int c = 0; c < 9; c++)
            cout << board[r][c].value << ' ';
        cout << endl;
    }

}

//read in puzzle from file 
bool Board::read(char* filename)
{
    ifstream ifs;
    ifs.open(filename);

    if(!ifs)
        return false;
    
    //input is whitespace delimited, so can just use plain cin
    for(int i = 0; i < 9; i++)
        for(int n = 0; n < 9; n++)
            ifs >> board[i][n].value;
    ifs.close();

    //clears all possibilites for cells that have values
    for(int r = 0; r < 9; r++)
        for(int c = 0; c < 9; c++)
            if(board[r][c].value != 0)
                for(int n = 0; n < 10; n++)
                    board[r][c].poss[n] = 0;
    return true;
}

//update possibility vectors in given group
//after, check all cells - if only one possibility, set value - elimination
//Also, if only one cell has given possible value, set it - singleton
void Board::update(Cell** group)
{
    //if one cell has a value, no other cells in group can have it: scan through cells...
    for(int i = 0; i < 9; i++)
    {
        //if cell has a nonzero value...
        if(group[i]->value != 0)
        {
            //set that possibility to false for all cells
            for(int x = 0; x < 9; x++)
                group[x]->poss[group[i]->value] = 0;
        }
    }

    //check cells in group again - elimination
    for(int i = 0; i < 9; i++) //iterate over cells
    {
        //check possibilites for cell
        int sum = 0, val;
        for(int n = 1; n < 10; n++)
        {
            sum += group[i]->poss[n];
            //remember non-zero value in case it's the only one
            if(group[i]->poss[n] == 1)
                val = n;
        }

        //if there's only one 1 possibility
        if (sum == 1 && group[i]->value == 0)
        {
            //set the value of the cell equal to it
            group[i]->value = val;
            //set all possibilities for that cell to zero
            for(int n = 0; n < 10; n++)
                group[i]->poss[n] = 0;
            //remove that possibility from each cell in the group
            for(int x = 0; x < 9; x++)
                group[x]->poss[val] = 0;
        }
    }

    //check all values to see if only one cell has given possibility - singletons
    for(int n = 1; n < 10; n++) //iterate over values 1-9
    {
        int count = 0, index;
        //check all cells to see how many have this possibility set to true
        for(int i = 0; i < 9; i++)
        {
            count += group[i]->poss[n];
            //remember non-zero value in case it's the only one
            if(group[i]->poss[n] == 1)
                index = i;
        }

        //if only one does and the cell is unset
        if(count == 1 && group[index]->value == 0)
        {
            //set the value of the cell equal to it
            group[index]->value = n;
            //set all possibilities for that cell to zero
            for(int num = 0; num < 10; num++)
                group[index]->poss[num] = 0;
            //remove that possibility from each cell in the group
            for(int x = 0; x < 9; x++)
                group[x]->poss[n] = 0;
        }
    }
}

//function to check if the board is solved - i.e. if every cell has a non-zero value
bool Board::isSolved()
{
    for(int r = 0; r < 9; r++)
        for(int c = 0; c < 9; c++)
            if(board[r][c].value == 0)
                return false;

    return true;
}

//solving process is the same across rows, cols, and minigrids
//the only thing that changes is the shape of the group of cells
//So, with arrays of pointers to reference different groupings of cells
//we can use the exact same function across rows, columns, and minigrids
void Board::solve()
{
    //groups for using solve function
    Cell *col[9][9]; 
    for(int c = 0; c < 9; c++)
        for(int r = 0; r < 9; r++)
            col[c][r] = &board[r][c];

    Cell *row[9][9]; 
    for(int r = 0; r < 9; r++)
        for(int c = 0; c < 9; c++)
            row[r][c] = &board[r][c];

    Cell *grid[9][9]; 
    for(int g = 0; g < 9; g++)
        for(int n = 0; n < 9; n++)
            grid[g][n] = &board[3*(g/3)+n/3][3*(g%3)+n%3];
            //this line is a bit complicated, but in essence fills grid[][] such that
            //each row has the address of nine cells in a given minigrid

    //count iterations for early exit if infinite loop
    int count = 0;

    //until it's solved...
    while(!isSolved())
    {
        //update on each row, col, and minigrid
        for(int i = 0; i < 9; i++)
        {
            update(row[i]);
            update(col[i]);
            update(grid[i]);
        }
        //increment and early exit if necessary
        count++;
        if(count > 10000)
        {
            cout << "Early exit: " << endl;
            break;
        }
    }
}
