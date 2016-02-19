//Daniel Jasek
//cse20212 lab4

#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include<string>

using namespace std;

template<typename T>
class Puzzle
{
   public:
      Puzzle();
      void display();
   private:
      //vector<T> v(9);
      vector<vector<T> > board;
};

template<typename T>
Puzzle<T>::Puzzle()
{
   int size;
   /*cout << "Enter the size of the rows and columns: ";
   cin >> size;*/

   size=9;

   ifstream inputFile("board.txt");   

   T tmp;

   for(int i=0; i<size; i++)
   {
      vector<T> row;
      for(int j=0; j<size; j++)
      {
         inputFile >> tmp;
         row.push_back(tmp);
      }
      board.push_back(row);
   }
   
   /*vector<T> temp;
   if(inputFile.is_open())
   {
      while(!inputFile.eof())
      {
         //inputFile >> temp;
         //cout << temp << endl;
      }
   }
   inputFile.close();*/
}

template<typename T>void Puzzle<T>::display()
{
   for(int i=0; i<9; i++)
   {
      for(int j=0; j<9; j++)
      {
         cout << board[i][j] << " "; 
      }
      cout << endl;
   }
}


#endif
