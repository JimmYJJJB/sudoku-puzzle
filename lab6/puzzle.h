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
      void solve();
      void print3D();
      void findPossibilities();
      void AIscan();
      void singleton();

   private:
      vector<vector<T> > board; // 2-d array of vectors
      vector<vector<T> > origBoard; // copy of original board
      vector<vector<vector<T> > > scanBoard; 
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
   cout << endl;

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

   for(int i=0; i<size; i++) // each row
   {
      vector<vector<T> > vec2;
      for(int j=0; j<size; j++) // each column
      {
         vector<T> thirdDim;
         for(int k=0; k<size; k++) // 3rd dim
         {
            thirdDim.push_back(1);
         }
         vec2.push_back(thirdDim);
      }
      scanBoard.push_back(vec2);
   }
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

template<typename T>
void Puzzle<T>::solve()
{
   //check for repeat in row
   for(int j=0; j<size; j++)
   {
      if(board[row-1][j] == number)
      {
         scanBoard[row-1][j].push_back(number);
      }
   }

   //check for repeat in column
   for(int i=0; i<size; i++)
   {
      if(board[i][col-1] == number)
      {
         cout << "Repeat in column." << endl;
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
         }
      }
   }

}

template<typename T>
void Puzzle<T>::print3D()
{
   for(int i=0; i<size; i++) // each row
   {
      //vector<T> row;
      for(int j=0; j<size; j++) // each column
      {
         //vector<T> thirdDim;
         for(int k=0; k<size; k++) // 3rd dim
         {
            cout << scanBoard[i][j][k];
         }
         cout << " | ";
         //row.push_back(thirdDim);
      }
      //board.push_back(row);
      cout << endl;
   }
}

template<typename T>
void Puzzle<T>::findPossibilities()
{
   for(int r=0; r<size; r++) // each row
   {
      for(int c=0; c<size; c++) // each column
      {


            //check for repeat in mini-grid
            int searchRow, searchCol; // first row and column of mini-grid

            if(r >= 6)
               searchRow = 6;
            else if(r >= 3)
               searchRow = 3;
            else
               searchRow = 0;

            if(c >= 6)
               searchCol = 6;
            else if(c >= 3)
               searchCol = 3;
            else
               searchCol = 0;

         
         for(int num=1; num<=size; num++) // each number 1-9
         {


            for(int x=0; x<size; x++) // check in the row
            {
               if(board[r][x] == num)
               {
                  scanBoard[r][c][num-1] = 0;
                  break;
               }
            }

            for(int x=0; x<size; x++) // check in the column
            {
               if(board[x][c] == num)
               {
                  scanBoard[r][c][num-1] = 0;
                  break;
               }
            }

            for(int a=searchRow; a<searchRow+3; a++) // check in minigrid
            {
               for(int b=searchCol; b<searchCol+3; b++)
               {
                  if(board[a][b] == num)
                  {
                     //if(r==0 & c==0)
                        //cout << "number repeated in minigrid: " << num << endl;
                     scanBoard[r][c][num-1] = 0;
                  }
               }
            }


         }



      }
   }
}

template<typename T>
void Puzzle<T>::AIscan()
{
   int i=0;
   while(i<500)
   {
      i++;
      findPossibilities();

      for(int i=0; i<size; i++) // each row
      {
         for(int j=0; j<size; j++) // each column
         {


            if(board[i][j] == 0)
            {
               int onesCounter=0;
               int index=0;

               for(int k=0; k<size; k++) // 3rd dim
               {
                  if(scanBoard[i][j][k] == 1)
                  {
                     onesCounter++;
                     index = k;
                  }
               }

               if(onesCounter == 1)
               {
                  //cout << i << ", " << j << "index: " << index+1 << endl;
                  board[i][j] = index+1;
                  //return 0;
               }
            }

         }
      }
   
   }

   //return 0;
   
}

template<typename T>
void Puzzle<T>::singleton()
{
   // singleton
   int t=0;
   int uniqueCounter=0;
   while(t<10)
   {
      t++;
      //findPossibilities();

      for(int i=0; i<size; i++) // each row
      {
         for(int j=0; j<size; j++) // each column
         {

            for(int num=0; num<size; num++) // each number possibility
            {
               bool miniGridUnique = false;
               bool rowUnique = false;
               bool colUnique = false;

               if(scanBoard[i][j][num] == 1 && board[i][j] == 0) // if the number works and is unfilled
               {
                  //cout << i << j << num << "works" << endl;
                  miniGridUnique = true;
                  rowUnique = true;
                  colUnique = true;


                  int searchRow, searchCol;
                  if(i >= 6)
                     searchRow = 6;
                  else if(i >= 3)
                     searchRow = 3;
                  else
                     searchRow = 0;

                  if(j >= 6)
                     searchCol = 6;
                  else if(j >= 3)
                     searchCol = 3;
                  else
                     searchCol = 0;


                  for(int a=searchRow; a<searchRow+3; a++) // check in minigrid
                  {
                     for(int b=searchCol; b<searchCol+3; b++)
                     {
                        if((a != i | b != j) & board[a][b] == 0) // don't check self and make sure non-zero entries are not compared
                        {
                           if(scanBoard[a][b][num] == 1)
                           {
                              miniGridUnique = false;
                              //if(i==3 & j==8 & t==1)
                                 //cout << "not unique because: " << a << b << endl;
                           }
                        }
                     }
                  }

                  //check in row
                  for(int c=0; c<size; c++) // each column in row
                  {
                     if(c != j & board[i][c] == 0) // don't compare to itself
                     {
                        if(scanBoard[i][c][num] == 1)
                           rowUnique = false;
                     }
                  }

                  //check in column
                  for(int r=0; r<size; r++) // each row in column
                  {
                     if(r != i & board[r][j] == 0) // don't compare to itself
                     {
                        if(scanBoard[r][j][num] == 1)
                           colUnique = false;
                     }
                  }



                  if(miniGridUnique | rowUnique | colUnique)
                  {
                     //cout << "found unique: ";
                     //cout << miniGridUnique << rowUnique << colUnique << endl;
                     board[i][j] = num+1;
                     findPossibilities();
                     uniqueCounter++;
                     //if (uniqueCounter==7)
                       // return 0;
                  }
               }
            }


         }
      }


   }
   //return 0;

}


#endif
