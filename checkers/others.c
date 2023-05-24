#include "main.h"
#include "Lists.h"





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
void Turn(Board board, Player player) {
    int numOfTPlayers = 12;
    int numOfBPlayers = 12;
    unsigned short maxCaptures=0;
    multipleSourceMoveList* res;//create the list of lists
    res = (multipleSourceMoveList*)malloc(sizeof(multipleSourceMoveList));
    if (res == NULL) {
        exit(1);
    }

    makeEmptyMultipleList(res);//initilize list of lists
    res = FindAllPossiblePlayerMoves(board, player);//get the list of lists 

    multipleSourceMoveListCell* curr=NULL;
    multipleSourceMoveListCell* optimal = NULL;
    curr = res->head;
    //looking for the most optimal list from them all
    while (curr != NULL) {
        //player T turn
        if (player == PLAYER_T) {
            //last move- if the number of captures is the same as the nember of players- T wins
            if (curr->single_source_moves_lists->tail->captures == numOfBPlayers){
                optimal = curr->single_source_moves_lists->head;//found the best move
            }
            //last move- if the T player is one list of finishing the  game
            else if (curr->single_source_moves_lists->tail->position->row == BOARD_SIZE - 1) {
                optimal = curr->single_source_moves_lists->head;//found the best move
            }
            //max captures or exercise 4 law
        }
        else {//player is B

        }
        curr = curr->next;
    }


}