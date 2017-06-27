Sudoku Solver
=============

One of the labs for the Data Structures class I took was to implement a sudoku solver in C++. This is my solution to the problem, which implements both elimination (cell only has one possible value) and singelton (only one cell in group could contain certain value) strategies.

Three example puzzles of varying difficulty are in the /puzzles directory, and their corresponding solutions in /solutions.

Building and testing:

``> make``

``> make test``

Running a puzzle:

``> ./solve $puzzle ``

e.g.

``> ./solve /puzzles/easy.txt``
