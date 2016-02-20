//Daniel Jasek
//cse20212 lab4
//class interface and implementation for the Puzzle class - enables a game of sudoku to be played

#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // for parsing string with commas
#include <stdlib.h>
#include <ctype.h> 

using namespace std;

template<typename T>
class Puzzle
{
   public:
      Puzzle();
      void display(); // display board to user
      void getMove(); // user enters coordinates
      int areCoordinatesValid(); // checks if coordinates are on board
      void play(); // general play method
      void updateBoard(); // update cell
      int isValidEntry(); // checks if move is valid sudoku move
      int hasWon(); // checks if board is full
   private:
      vector<vector<T> > board; // 2-d array of vectors
      vector<vector<T> > origBoard; // copy of original board
      int size; // nxn grid
      int row; // currenty row coordinate
      int col; // current column
      int number; // current user entry
};

// templated constructor - lets user set parameters and sets up 2-d vector
template<typename T>
Puzzle<T>::Puzzle()
{
   cout << "Enter the size of the board: ";
   cin >> size;

   string name;
   cout << "Enter name of input file: ";
   cin >> name;

   // sets of file reader
   ifstream inputFile(name.c_str());   

   T tmp; // temporary templated variable

   // allocates and pushes entries into vector
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

   origBoard = board; // keeps copy of original board
}

// displays board to user with smaller grids marked off
template<typename T>
void Puzzle<T>::display()
{
   cout << "SUDOKU" << endl;
   cout << "======" << endl << endl;
   for(int i=0; i<9; i++)
   {
      if(((i%3) == 0) & i !=0 ) // horizontal dividers
      {
         for(int k=0; k<18; k++)
         {
            cout << "-";
         }
         cout << endl;
      }
      for(int j=0; j<9; j++)
      {
         if(((j%3) == 0) & j !=0 ) // vertical dividers
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

// gets coordinates of move from user and checks if they are valid
template<typename T>
void Puzzle<T>::getMove()
{
   string entry;
   cout << endl << "Row and column of entry (separated by a comma): ";
   cin >> entry;
   
   stringstream ss(entry); // parse entry to ignore comma separator
   
   ss >> row;
   ss.ignore();
   ss >> col;

   while(!areCoordinatesValid()) // calls function to check if move is on the board - if not, asks for another set of coordinates
   {
      cout << "Please enter two integers between 1 and " << size << ": ";
      cin >> entry;
   
      stringstream ss(entry);
   
      ss >> row;
      ss.ignore();
      ss >> col;
   }

   // entry number
   cout << "Entry number (1-9): ";
   cin >> number;
}

// checks if move is on the board or if the space was already filled in by the original board
template<typename T>
int Puzzle<T>::areCoordinatesValid()
{
   if(row > size | col > size | row < 1 | col < 1) // on board
   {
      return 0;
   }
   else if(origBoard[row-1][col-1] != 0) // space taken already
   {
      cout << "Cannot override previous value" << endl;
      return 0;
   }
   else
   {
      return 1;
   }
}

// updates board with new entry
template<typename T>
void Puzzle<T>::updateBoard()
{
   board[row-1][col-1] = number;
}

// checks if entry is a valid sudoku move
template<typename T>
int Puzzle<T>::isValidEntry()
{
   //check for repeat in row
   for(int j=0; j<size; j++)
   {
      if(board[row-1][j] == number)
      {
         cout << "Repeat in row." << endl;
         return 0;
      }
   }

   //check for repeat in column
   for(int i=0; i<size; i++)
   {
      if(board[i][col-1] == number)
      {
         cout << "Repeat in column." << endl;
         return 0;
      }
   }

   //check for repeat in mini-grid
   int searchRow, searchCol; // first row and column of mini-grid

   if(row > 6)
      searchRow = 6;
   else if(row > 3)
      searchRow = 3;
   else
      searchRow = 0;

   if(col > 6)
      searchCol = 6;
   else if(col > 3)
      searchCol = 3;
   else
      searchCol = 0;

   for(int a=searchRow; a<searchRow+3; a++)
   {
      for(int b=searchCol; b<searchCol+3; b++)
      {
         if(board[a][b] == number)
         {
            cout << "Repeat in mini-grid" << endl;
            return 0;
         }
      }
   }

   return 1;
}

// checks if board is full to see if the user has won
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

// general play method that calls the other methods for an interactive game
template<typename T>
void Puzzle<T>::play()
{
   while(!hasWon()) // while the board still has empty spaces
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
   system("clear");
   display();
   cout << endl << "Congratulations, you have won!" << endl; // board is full
}

#endif
