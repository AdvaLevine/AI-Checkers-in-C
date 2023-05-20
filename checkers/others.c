#include "main.h"





//function to create the board
void createBoard(Board board) {

    int i, j;

    //create player T side of board
    for (i = 0; i < 3; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {

            if (i % 2 == 0) {//row is even number
                if (j % 2 != 0)
                    board[i][j] = PLAYER_T;
                else
                    board[i][j] = EMPTY_POS;
            }
            else {//row is odd number
                if (j % 2 != 0)
                    board[i][j] =EMPTY_POS;
                else
                    board[i][j] = PLAYER_T;
            }

        }//for2

    }//for1

    //two empty lines of the board in the middle
    for (i = 3; i < MAX_ROW; i++) {

        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY_POS;
        }
    }

    //create player B side of board

    for (i = MAX_ROW; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (i % 2 == 0) {//row is even number
                if (j % 2 != 0)
                    board[i][j] = PLAYER_B;
                else
                    board[i][j] = EMPTY_POS;
            }
            else {//row is odd number
                if (j % 2 != 0)
                    board[i][j] = EMPTY_POS;
                else
                    board[i][j] = PLAYER_B;
            }
        }//for2
    }//for1
}

void copyBorad(Board board, Board copyBoard)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            copyBoard[i][j] = board[i][j];
        }
    }
}