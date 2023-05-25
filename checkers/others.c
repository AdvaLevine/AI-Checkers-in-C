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

    //update the board
    updateBoard(board, player, optimal, maxCaptures);

    //update the number of players
    if (maxCaptures > 0) {
        updateNumOfPlayers(maxCaptures, player, &numOfBPlayers, &numOfTPlayers);
    }
   

   
    free(curr);
    free(optimal);
    //free lists?
}
void updateBoard(Board board, Player player, multipleSourceMoveListCell* optimal, unsigned short maxCaptures) {
    int nRow = 0;
    int nCol = 0;
    int oldRow = 0, oldCol = 0;

    //initilize the rows to the position
    oldRow = optimal->single_source_moves_lists->head->position->row - CHAR_A;
    oldCol = optimal->single_source_moves_lists->head->position->col - CHAR_A;

    //update the board according to the chosen optimal move
    while (optimal != NULL) {
        //initilize the new row and col to the list of moves to the next move
        nRow = optimal->single_source_moves_lists->head->next->position->row - CHAR_A;
        nCol = optimal->single_source_moves_lists->head->next->position->col - CHAR_A;
        //need to check if its corerect because might not exist

        //single move
        if (maxCaptures == 0) {
            board[oldRow][oldCol] = EMPTY_POS;//remove the old position
            board[nRow][nCol] = player;//update the new position
        }

        //if we had a capture move
        else//captures>0
        {
            if (player == PLAYER_T) {
                if (oldCol < nCol) {//we moved right
                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
                    board[nRow - 1][nCol - 1] = EMPTY_POS;//remove the enemies player
                    board[nRow][nCol] = player;//update the new position on board
                }
                else {//oldCol>ncol meaning moved left
                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
                    board[nRow - 1][nCol + 1] = EMPTY_POS;//remove the enemies player
                    board[nRow][nCol] = player;//update the new position on board
                }
            }
            else {//if (player==PLAYER_B
                if (oldCol < nCol) {//we moved right
                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
                    board[nRow + 1][nCol - 1] = EMPTY_POS;//remove the enemies player
                    board[nRow][nCol] = player;//update the new position on board
                }
                else {//oldCol>ncol meaning moved left
                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
                    board[nRow + 1][nCol + 1] = EMPTY_POS;//remove the enemies player
                    board[nRow][nCol] = player;//update the new position on board
                }
            }
            oldCol = nCol;
            oldRow = nRow;
        }
        //go to the next node in the chosen list
        optimal = optimal->single_source_moves_lists->head->next;
    }
}
void updateNumOfPlayers(unsigned short maxCaptures, Player player,int * numOfBPlayers, int* numOfTPlayers) {
  
    if (player == PLAYER_T) {//if T made a capture
          *numOfBPlayers = *numOfBPlayers - maxCaptures;
    }
    else {//if B made a capture
           *numOfTPlayers = *numOfTPlayers - maxCaptures;
    }
   
}