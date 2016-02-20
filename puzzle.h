//Daniel Jasek
//cse20212 lab4

#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include<string>
#include<sstream> // for parsing string with commas
#include<stdlib.h>
#include<ctype.h>

using namespace std;

template<typename T>
class Puzzle
{
   public:
      Puzzle();
      void display();
      void getMove();
      int areCoordinatesValid();
      void play();
      void updateBoard();
      int isValidEntry();
      int hasWon();
   private:
      vector<vector<T> > board;
      vector<vector<T> > origBoard;
      int size;
      int row;
      int col;
      int number;
};

template<typename T>
Puzzle<T>::Puzzle()
{
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

   origBoard = board;
   
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

template<typename T>
void Puzzle<T>::display()
{
   cout << "SUDOKU" << endl;
   cout << "======" << endl << endl;
   for(int i=0; i<9; i++)
   {
      if(((i%3) == 0) & i !=0 )
      {
         for(int k=0; k<18; k++)
         {
            cout << "-";
         }
         cout << endl;
      }
      for(int j=0; j<9; j++)
      {
         if(((j%3) == 0) & j !=0 )
         {
            cout << "|";
            cout << board[i][j]; 
         }
         else
            cout << " " << board[i][j]; 
      }
      cout << endl;
   }
}

template<typename T>
void Puzzle<T>::getMove()
{
   string entry;
   cout << endl << "Row and column of entry (separated by a comma): ";
   cin >> entry;
   
   stringstream ss(entry);
   
   ss >> row;
   ss.ignore();
   ss >> col;

   while(!areCoordinatesValid())
   {
      cout << "Please enter two integers between 1 and " << size << ": ";
      cin >> entry;
   
      stringstream ss(entry);
   
      ss >> row;
      ss.ignore();
      ss >> col;
   }

   cout << "Entry number (1-9): ";
   cin >> number;

   //cout << "row: " << row;
   //cout << "column: " << col;
}

template<typename T>
int Puzzle<T>::areCoordinatesValid()
{
   /*if(!isdigit(row) | !isdigit(col))
   {
      cout << "First return" << endl;
      return 0;
   }
   else*/ if(row > size | col > size | row < 1 | col < 1)
   {
      //cout << "second return" << endl;
      return 0;
   }
   else if(origBoard[row-1][col-1] != 0)
   {
      cout << "Cannot override previous value" << endl;
      return 0;
   }
   else
   {
      //cout << "third return" << endl;
      return 1;
   }
}

template<typename T>
void Puzzle<T>::updateBoard()
{
   //cout << "row " << row  << "col " << col << "entry " << number;
   //cout << "old: >" << board[row][col] << "<";
   //T num2 = number;
   board[row-1][col-1] = number;
   //cout << "new: >" << board[row][col] << "<";
   //display();
}

template<typename T>
int Puzzle<T>::isValidEntry()
{
   //check in row
   for(int j=0; j<size; j++)
   {
      if(board[row-1][j] == number)
         return 0;
   }

   //check in column
   for(int i=0; i<size; i++)
   {
      if(board[col-1][i] == number)
         return 0;
   }

   //check in square
   int searchRow, searchCol;

   if(row >= 6)
      searchRow = 6;
   else if(row >= 3)
      searchRow = 3;
   else
      searchRow = 0;

   if(col >= 6)
      searchCol = 6;
   else if(col >= 3)
      searchCol = 3;
   else
      searchCol = 0;

   for(int a=searchRow; a<searchRow+3; a++)
   {
      for(int b=searchCol; b<searchCol+3; b++)
      {
         if(board[a][b] == number)
            return 0;
      }
   }

   return 1;
}

template<typename T>
int Puzzle<T>::hasWon()
{
   //check if board is full
   for(int i=0; i<size; i++)
   {
      for(int j=0; j<size; j++)
      {
         if(board[i][j] == 0)
            return 0;
      }
   }
   return 1;
}


template<typename T>
void Puzzle<T>::play()
{
   while(!hasWon())
   {
      system("clear");
      display();
      getMove();
      while(!isValidEntry())
      {
         cout << "Invalid entry. Check your numbers. " << endl;
         getMove();
      }
      updateBoard();
   }
   cout << "Congratulations, you have won!" << endl;
}


#endif
