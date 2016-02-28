//Daniel Jasek
//cse20212 lab6
//driver program for part 2 - instantiates a Puzzle object and plays a game of Sudoku

#include <iostream>
#include "puzzle.h"

using namespace std;

int main()
{
   Puzzle<int> intPuz;
   
   cout << "Original Puzzle" << endl;
   cout << "===============" << endl;
   intPuz.display();

   intPuz.AIscan();
   intPuz.singleton();

   cout << endl << "Solved Puzzle" << endl;
   cout << "=============" << endl;

   intPuz.display();
} 
