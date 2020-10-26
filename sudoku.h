#ifndef SUDOKU_H
#define SUDOKU_H
void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/*function returns true if all  cells occupied by a digit between '1' and '9' otherwise return false */
bool is_complete(char board[][9]);

/*function returns true if digit to be inserted at position does not result in two copies in same column. */
bool col_clear(const char position[2], char digit, char board[][9]);

/*same as above but for rows*/
bool Row_clear(const char position[2], char digit, char board[][9]);

/* same as above but for 3*3 boxes  */
bool box_clear(const char position[2], char digit, char board[][9]);

/* unifies the three conditions above  and return true if all three are true and the position is empty*/
bool make_move(const char position[2], char digit, char board[][9]);

/*save board to a file and return true if successfully written */
bool save_board(const char* filename_1 ,char  board[][9]);

/* returs true if board is solved else false*/
bool solve_board(char board[][9]);

/* returs true if board is solved else false and keeps count how many times the function is recursively called*/
bool solve_board_count(char board[][9],int &count);

/*check if a cell is empty and returns true if cell is empty*/
bool cell_is_empty(char board[][9], int i, int j);

#endif





