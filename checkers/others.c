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

    //checking if we can still continue in the game
    if (isGameFinished(board, player)) {
        return;//game finished
    }

    //game continues
    unsigned short maxCaptures = -1;
    int chosenMoveIndex = -1; //chosen list move
    int i;
    int count = 0;
    multipleSourceMoveList* res;//create the list of lists
    res = (multipleSourceMoveList*)malloc(sizeof(multipleSourceMoveList));
    if (res == NULL) {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }

    makeEmptyMultipleList(res);//initilize list of lists
    res = FindAllPossiblePlayerMoves(board, player);//get the list of lists

    //find the num of lists in the list of lists
    multipleSourceMoveListCell* curr=res->head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    //if theres only one list return it
    if (count == 1) {
        chosenMoveIndex = 0;
        SingleSourceMovesList* chosenMove =res->head;
        makeMove(board, chosenMove); //change the board
    }
    //more then one list
    else {

        //checking if theres a max capture move
        for (i = 0; i < count; i++) {
            SingleSourceMovesList* currentMove = res->head->single_source_moves_lists;
        //checking the captures in the tail to see if its the maximum
            if (currentMove->tail->captures > maxCaptures) {
                maxCaptures = currentMove->tail->captures;
                chosenMoveIndex = i;//found the best move list
            }
            res = res->head->next;
        }
        if (chosenMoveIndex != -1) {
            SingleSourceMovesList* chosenMove = SingleSourceMovesListByIndex(res, chosenMoveIndex);
            makeMove(board, chosenMove); //change the board
        }
    }
    //left to do-
        // חישוב השורה והעמודה הגבוהות או הנמוכות ביותר במסלולים האופטימליים
    //אם אין קאפצרים מקסימלים



    //free
    RemoveSingleSourceMovesList(res);
}
//function to check if the game is finished
int isGameFinished(Board board, Player player) {
    int i, j;
    int playerBPieces = 0;
    int playerTPieces = 0;

   //counting the players tools 
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == player) {
                playerTPieces++;
            }
            else if (board[i][j] != ' ') {
                playerBPieces++;
            }
        }
    }

//checking if everyone still has game pieces
    if (playerBPieces == 0 || playerTPieces == 0) {
        return 1;  //game over
    }

//checking if player B is in the first row
    if (player == 'B') {
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[0][i] == player) {
                return 1; //B won-game over
            }
        }
    }
    //checking if player T is in the last row
    else if (player == 'T') {
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[BOARD_SIZE - 1][i] == player) {
                return 1; //T won-game over
            }
        }
    }

    return 0; //game ont over yet
}
//gets the index for where the list is and then looks out for the list in the lists of mult lists
SingleSourceMovesList* getSingleSourceMovesListByIndex(multipleSourceMoveList* list, int index) {

    multipleSourceMoveListCell* currentCell = list->head;
    int currentIndex = 0;

    //looking for the list of the best move (we found the index in Turn func
    while (currentCell != NULL && currentIndex < index) {
        currentCell = currentCell->next;
        currentIndex++;
    }
    //if thr cell isnt empty
    if (currentCell != NULL) {
        return currentCell->single_source_moves_lists;
    }

    return NULL; //index not found

}
//change the board
void makeMove(Board board, SingleSourceMovesList* move) {
   
    //moving the player from the stating point to end point and making the starting point empty
    board[move->tail->position->row][move->tail->position->col] = board[move->head->position->row][move->head->position->col];
    board[move->head->position->row][move->head->position->col] = EMPTY_POS;

    //checking for any capture moves if so, makes empty where it captures 
    if (move->tail->captures != 0) {
        SingleSourceMovesListCell* currentPos = move->head->next;
        while (currentPos != NULL) {
            board[currentPos->position->row][currentPos->position->col] = EMPTY_POS;
            currentPos = currentPos->next;
        }
    }
}
//free func
void RemoveSingleSourceMovesList(multipleSourceMoveList* list) {

    multipleSourceMoveListCell* largeList = list->head;
    multipleSourceMoveListCell* nextLargeList;
    SingleSourceMovesList* smallList;
    SingleSourceMovesListCell* curr;
    SingleSourceMovesListCell* nextMove;


    while (largeList != NULL) {
        smallList = largeList->single_source_moves_lists;
        nextLargeList = largeList->next;
        curr = smallList->head;

        while (curr != NULL) {
            nextMove = curr->next;
            free(curr->position->row);
            free(curr->position->col);
            free(curr->position);
            free(curr);
            curr = nextMove;
        }
        free(largeList);
        largeList = nextLargeList;
    }

}


//    multipleSourceMoveListCell* curr=NULL;
//    multipleSourceMoveListCell* optimal = NULL;
//    curr = res->head;
//
//    //looking for the most optimal list from them all
//    while (curr != NULL) {
//        //player T turn
//        if (player == PLAYER_T) {
//            //last move- if the number of captures is the same as the number of players- T wins
//            if (curr->single_source_moves_lists->tail->captures == numOfBPlayers){
//                optimal = curr->single_source_moves_lists->head;//found the best move
//            }
//            //last move- if the T player is one move of finishing the game
//            else if (curr->single_source_moves_lists->tail->position->row == BOARD_SIZE - 1) {
//                optimal = curr->single_source_moves_lists->head;//found the best move
//            }
//            //max captures 
//            else if (curr->single_source_moves_lists->tail->captures > maxCaptures) {
//                maxCaptures = curr->single_source_moves_lists->tail->captures;
//                optimal = curr->single_source_moves_lists->head;//found the best move
//            }
//            // law 4
//            else {
//              
//            }
//        }
//        else {//player is B
//
//        }
//        curr = curr->next;
//    }
//
//    //update the board
//    //updateBoard(board, player, optimal, maxCaptures);
//
//    //update the number of players
//    if (maxCaptures > 0) {
//        //updateNumOfPlayers(maxCaptures, player, &numOfBPlayers, &numOfTPlayers);
//    }
//   
//
//   
//    free(curr);
//    free(optimal);
//    //free lists?
//}
//void updateBoard(Board board, Player player, multipleSourceMoveListCell* optimal, unsigned short maxCaptures) {
//    int nRow = 0;
//    int nCol = 0;
//    int oldRow = 0, oldCol = 0;
//
//    //initilize the rows to the position
//    oldRow = optimal->single_source_moves_lists->head->position->row - CHAR_A;
//    oldCol = optimal->single_source_moves_lists->head->position->col - CHAR_A;
//
//    //update the board according to the chosen optimal move
//    while (optimal != NULL) {
//        //initilize the new row and col to the list of moves to the next move
//        nRow = optimal->single_source_moves_lists->head->next->position->row - CHAR_A;
//        nCol = optimal->single_source_moves_lists->head->next->position->col - CHAR_A;
//        //need to check if its corerect because might not exist
//
//        //single move
//        if (maxCaptures == 0) {
//            board[oldRow][oldCol] = EMPTY_POS;//remove the old position
//            board[nRow][nCol] = player;//update the new position
//        }
//
//        //if we had a capture move
//        else//captures>0
//        {
//            if (player == PLAYER_T) {
//                if (oldCol < nCol) {//we moved right
//                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
//                    board[nRow - 1][nCol - 1] = EMPTY_POS;//remove the enemies player
//                    board[nRow][nCol] = player;//update the new position on board
//                }
//                else {//oldCol>ncol meaning moved left
//                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
//                    board[nRow - 1][nCol + 1] = EMPTY_POS;//remove the enemies player
//                    board[nRow][nCol] = player;//update the new position on board
//                }
//            }
//            else {//if (player==PLAYER_B
//                if (oldCol < nCol) {//we moved right
//                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
//                    board[nRow + 1][nCol - 1] = EMPTY_POS;//remove the enemies player
//                    board[nRow][nCol] = player;//update the new position on board
//                }
//                else {//oldCol>ncol meaning moved left
//                    board[oldRow][oldCol] = EMPTY_POS;//remove the old position
//                    board[nRow + 1][nCol + 1] = EMPTY_POS;//remove the enemies player
//                    board[nRow][nCol] = player;//update the new position on board
//                }
//            }
//            oldCol = nCol;
//            oldRow = nRow;
//        }
//        //go to the next node in the chosen list
//        optimal = optimal->single_source_moves_lists->head->next;
//    }
//}
//void updateNumOfPlayers(unsigned short maxCaptures, Player player,int * numOfBPlayers, int* numOfTPlayers) {
//  
//    if (player == PLAYER_T) {//if T made a capture
//          *numOfBPlayers = *numOfBPlayers - maxCaptures;
//    }
//    else {//if B made a capture
//           *numOfTPlayers = *numOfTPlayers - maxCaptures;
//    }
//   
//}