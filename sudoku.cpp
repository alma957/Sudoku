#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include<string>
#include "sudoku.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
       cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */


/*function returns true if all  cells occupied by a digit between '1' and '9' otherwise return false */

bool is_complete(char board[][9])
{

	int i, j;
	for (i=0;i<9;i++)
	{
		for (j=0; j<9; j++)
		{
			if (!isdigit(board[i][j]) || board[i][j]=='0')
				return false;      /* if for any row and column combination a digit between '1' and '9' is missing then return false*/
		}
	}
	return true;
}
			



/*function returns true if digit to be inserted at position does not result in two copies in same column. returns false also if digit at position equal the one to be inserted*/

bool col_clear(const char position[2], char digit, char board[][9])
{	
	int j, m;
        char c1=position[0];  
	char c2=position[1];
      	m=c1 - 65;    /* to find row number in which we want to insert the digit we use ASCII conversion table */
         

       if (c1>='A' && c1<='I' && c2>='1' && c2<='9' && digit>='1' && digit<='9') /* if insert wrong coordinateas or digit, 
                                                                                  function returns false and move not valid */
       {	
	for (j=0; j<9 ; j++)
	{
	     if (digit==board[m][j])
	     {
			return false; /* return false if digit equal a cell in some column j given row m */
	     }
	}
	return true; /* if loops finished without returning false then return true*/
        } else {
       return false;
       }       
}

/*same as above but for rows*/

bool Row_clear(const char position[2], char digit, char board[][9])
{	
	int i, n;
	char c1=position[0];
        char c2=position[1];
        n=c2 -49; /* to find column number in which we want to insert the digit we use ASCII conversion table */
         

       if (c1>='A' && c1<='I' && c2>='1' && c2<='9' && digit>='1' && digit<='9') 
       {	
	for (i=0; i<9 ; i++)
	{
		if (digit==board[i][n])
		{
		    return false;
		}
	}
         return true;
	} else {
       return false;	       
       } 
}

/* same as above but for 3*3 boxes  */
bool box_clear(const char position[2], char digit, char board[][9])
{	
	int i, j, m, n;
        char c1=position[0];
        char c2=position[1];
     	m=c1 - 65;
        n=c2 -49;
         

       if (c1>='A' && c1<='I' && c2>='1' && c2<='9' && digit>='1' && digit<='9') 
       {
       for (i=0;i<3;i++)
       {
     	       for (j=0;j<3;j++)
	       {
		       if(digit==board[i+(m-m % 3)][j + (n - n % 3)])   /* test against appropriate box */
		       {
			        return false;
		       }
	       }
       }
       return true;
       } else {
	       return false;
       }
}

				  




/* unifies the three conditions above  and return true if all three are true and the position is empty*/

bool make_move(const char position[2], char digit, char board[][9])
{
	int m, n;
        char c1=position[0];
        char c2=position[1];
       	m=c1 - 65;   
        n=c2 -49;
        if (board[m][n]>='1' && board[m][n]<='9')
	{
		return false; /* if digit present at position we restrict move*/
	
        }  else	if (box_clear(position,digit,board)==1 && Row_clear(position, digit, board)==1 && col_clear(position, digit, board)==1) 
	{
		board[m][n]=digit;
		return true;
	} else {
		return false;
	}
}

            
/*save board to a file and return true if successfully written */

bool save_board(const char* filename ,char  board[][9])
{
	int i,j;
        char copied_board[9][9];	
	ofstream outstream;
	outstream.open(filename);
	if (outstream.fail())	
	{
		cout<<"Outputfile not loaded correctly"<<endl;
		return false;
	}
	
	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
			{
				outstream<<board[i][j];
			}
			outstream<<endl; 
	}
	outstream.close();
        
	load_board(filename, copied_board);

	for (i=0; i<9; i++)
	{
		for (j=0;j<9;j++)
		{
			if (board[i][j]!=copied_board[i][j])
					return false;
		}
	}
	return true;
}

bool solve_board(char board[][9])
{
	int count=0;
	if (solve_board_count(board, count))
	{
	  /*  cout<<"Number of recursive calls to find solution: " <<count<<endl;*/ 
		return true;
	} else {
		return false;
	}
}

/*solve the board with recursive call*/
bool solve_board_count(char board[][9],int &count)   
{
     
     int digit, i, j; 
     if (is_complete(board))
     {       
	     return true; /*once complete return true*/
     } else {
      for (i=0; i<9;i++)
      {
	      for (j=0;j<9;j++)
	      { 
		     char c1;
		     char c2;
		     c1=i+65;
		     c2=j+49;
		     const char position[2]={c1,c2}; 
		     if (cell_is_empty(board, i, j))  /* if cell is empty get in*/
		     { 
	                  for (digit='1';digit<='9';digit++)  
		          {	
            			if (make_move(position,digit, board))
	    			{	
	                                count++;  /*number of times the  function is recursively called*/
              				board[i][j]=digit;   
              				if (solve_board_count(board, count ))
              					return true;
              				board[i][j]='.';/* if once function recursively called finds no solution for next digit then we go back and assign it
							   '.' so that it is no longer a digit between 1 and 9 and we go back to the for loops digit*/
				 } 
			  } 
			  return false; /*for backtracking*/
		     }
	      }
      } 
      return false;  /*no solution*/
}
}


/*check if a cell is empty and returns true if it is*/		
bool cell_is_empty(char board[][9], int i, int j)
{ 
  	       if (!isdigit(board[i][j]) || board[i][j]=='0')
			return true;
		return false;
	    
}
