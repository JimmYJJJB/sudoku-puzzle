# sudoku-puzzle

This is a sudoku program for my Fundamentals of Computing II class. The user can either solve the puzzle manually or use the AI to solve it. The AI works by first using a "scanning" algorithm - playing a move if it is the only possible move for that square. The AI then finishes harder puzzles by using a "singleton" algorithm - playing a move if no other square in the row, column, or mini-grid can make the same move.

BUILD
=====

`% make`

RUN
====
`% ./main`

CLEAN
=====
`% make clean`
