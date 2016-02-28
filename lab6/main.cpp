//Daniel Jasek
//cse20212 lab6
//driver program for sudoku solver

#include <iostream>
#include "puzzle.h"

using namespace std;

int main()
{
   Puzzle<int> intPuz; // declares templated int board
   
   // display original puzzle
   cout << "Original Puzzle" << endl;
   cout << "===============" << endl;
   intPuz.display();

   // solve puzzle using the scan and singleton method
   intPuz.AIscan();
   intPuz.singleton();

   // display solved puzzle
   cout << endl << "Solved Puzzle" << endl;
   cout << "=============" << endl;
   intPuz.display();
} 
