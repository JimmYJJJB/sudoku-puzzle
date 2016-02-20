//Daniel Jasek
//cse20212 lab4
//driver program for part 1, instantiates 2 puzzle objects and displays their boards at the start

#include <iostream>
#include "puzzle.h"

using namespace std;

int main()
{
   // int board
   cout << "Int Puzzle" << endl;
   Puzzle<int> intPuz;
   intPuz.display();

   // char board
   cout << "Char Puzzle" << endl;
   Puzzle<char> charPuz;
   charPuz.display();
} 
