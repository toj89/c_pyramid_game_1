/* YOUR WORK GOES HERE!
 * 
 * STUDENT_ID: 2326956
 * 
 * COMMENTS (if any):
 */

#include "my_pyramid_game.h"
#include "pyramid_helpers.h"
#include <string.h>
#define total_moves 36
#define total_pegs 15

int moves[][36] = {
    {0, 0, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 14, 14},
    {1, 2, 4, 3, 4, 5, 1, 4, 7, 6, 8, 7, 2, 9, 8, 4, 3, 7, 4, 8, 4, 7, 5, 8, 6, 11, 7, 12, 7, 8, 13, 11, 12, 8, 9, 13},
    {3, 5, 8, 6, 7, 9, 0, 5, 12, 10, 13, 11, 0, 14, 12, 3, 1, 8, 2, 9, 1, 6, 2, 7, 3, 12, 4, 13, 3, 5, 14, 10, 11, 4, 5, 12}
};

/*
 * (Copied from 'my_pyramid_solver.h')
 * 
 * THIS FUNCTION WILL BE CALLED DURING TEST ASSESSMENTS.
 * 
 * solve: This is the game 'engine', in which the logic is based.
 *        It takes a board in any valid state, and determines
 *        if the game is solvable.
 * 
 * Parameters:
 *        board - an integer array of size 15, with contents either 0 or 1.
 * 
 * Returns:
 *        1  -  If the board is solvable;
 *        0  -  otherwise.
 */

int solve(int temp_board[]) 
{

    int sum_pegs = 0; //holds the total amount of pegs currently on the board
    int legal_moves = 0; //holds the total amount of legal moves currently possible
    int board[15];
    
    for(int i = 0; i < total_pegs; i++)  //takes a copy of the original board and saves it into an array called temp_board
    {
        board[i] = temp_board[i];
    }
    int jumpStart;  //start position of any given legal move
    int jumpAcross; //position that is being jumped across if legal move is possible
    int jumpEnd; //position in which the peg from the start position lands, if the move was legal 
    int counter = 0; //counter variable to see if all 36 possible moves have been checked

    for (int i = 0; i < total_pegs; i++) //for loop to count all pegs, currently on the board
    {
        if (board[i] == 1) 
        {
            sum_pegs++;
        }
    }
          
    for (int i = 0; i < total_moves; i++) //for loop to count all legal moves, currently possible 
    {
        jumpStart = moves[0][i];
        jumpAcross = moves[1][i];
        jumpEnd = moves[2][i];
            
        if (board[jumpStart] == 1 && board[jumpAcross] == 1 && board[jumpEnd] == 0) 
        {
            legal_moves++;
        }
    }

    if(sum_pegs == 1) 
    //if only one peg remains on the board, the board is solved and returns 1
    {
        return 1;
    }
    else if(legal_moves == 0  && sum_pegs > 1) 
    //if no legal moves are possible anymore and there is more than one peg remaining, board is not solvable and returns 0
    {
        return 0;
    }
    else
    //if non of the above is true, the program attempts to further solve the puzzle by recursively going through all possible moves
    //until it solves the board and prints out the solution process    
    {
        for (int i = 0; i < total_moves; i++)     
        {
            jumpStart = moves[0][i];
            jumpAcross = moves[1][i];
            jumpEnd = moves[2][i];
            
            if (board[jumpStart] == 1 && board[jumpAcross] == 1 && board[jumpEnd] == 0) 
            {
            
                board[jumpStart] = 0;
                board[jumpAcross] = 0;
                board[jumpEnd] = 1;
                
                if(solve(board))
                //solve function recursively calls itself    
                {   
                    printf("Peg (%d) jumps over peg (%d) to (%d).\n", jumpStart, jumpAcross, jumpEnd);
                    //prints out the winning moves after the board is solved
                    return 1;
                }
                else
                //undoes a move if it didn't solve the board    
                {
                    board[jumpStart] = 1;
                    board[jumpAcross] = 1;
                    board[jumpEnd] = 0;
                }
            }            
            counter++;
        }
        if(counter == total_moves)
        {
            return 0;
        }
    }
}

/* 
 * main_pyramid:  This is the entry point to your pyramid game implementation.
 * 
 * Pretend this is the main() function as you are use to writing,
 * i.e. the function where your program logic begins and terminates.
 */

int main_pyramid() 
{
    int board[15];

    pyramid_input(board);
    printf("Here is the board you entered:\n");
    pyramid_print(board);
    printf("\n");
    
    if(solve(board))
    {
        printf("Board solved!\n");
    } 
    else
    {
        printf("Board not solvable!\n");
    }
    return 0;
}