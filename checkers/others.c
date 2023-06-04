#include "main.h"
#include "Lists.h"

//constant int for max captures in game
extern int maxGameCaptures = 0;
extern char maxcapturePlayer = EMPTY_POS;
extern int countCapturesT = 0;
extern int countCapturesB = 0;

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
    ////checking if we can still continue in the game
    //if (isGameFinished(board, player)) {
    //    return;//game finished
    //}

    //game continues
    unsigned short maxCaptures = 0;
    int chosenMoveIndex = -1; //chosen list move
    int count = 0;
    int i = 0;

    //find max and min cols and rows
    //int minRow = BOARD_SIZE;//size that doesnt exist in board
    //int minCol = BOARD_SIZE;//size that doesnt exist in board
    //int maxRow = -1;//size that doesnt exist in board
    //int maxCol = -1;//size that doesnt exist in board
    SingleSourceMovesList* currentMove = NULL;//current place in single list
    SingleSourceMovesList* chosenMove = NULL;//the list of moves wee choose
    multipleSourceMoveListCell* numOfListsCurr = NULL;//number of list curr
    multipleSourceMoveListCell* currentListCell = NULL;
    int currentIndex = 0;


    multipleSourceMoveList* res;//create the list of lists
    res = (multipleSourceMoveList*)malloc(sizeof(multipleSourceMoveList));
    if (res == NULL) {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }

    makeEmptyMultipleList(res);//initilize list of lists
    res = FindAllPossiblePlayerMoves(board, player);//get the list of lists

    //find the num of lists in the list of lists
    numOfListsCurr = res->head;
    while (numOfListsCurr != NULL) {
        count++;
        numOfListsCurr = numOfListsCurr->next;
    }
    //if theres only one list return it
    if (count == 1) {
        chosenMoveIndex = 0;
        chosenMove = res->head->single_source_moves_lists;
        makeMove(board, chosenMove, player); //change the board
    }
    //more then one list
    else {

        //checking if theres a max capture move
        //for (i = 0; i < count; i++) {

        //    currentMove = res->head->single_source_moves_lists;
        ////checking the captures in the tail to see if its the maximum
        //    if (currentMove->tail->captures > maxCaptures) {
        //        maxCaptures = currentMove->tail->captures;
        //        chosenMoveIndex = i;//found the best move list
        //    }
        //    res = res-next;
        //}
        currentListCell = res->head;
        while (currentListCell != NULL) {
            currentMove = currentListCell->single_source_moves_lists;
            //checking the captures in the tail to see if it's the maximum
            if (currentMove->tail != NULL) {
                if (currentMove->tail->captures > maxCaptures) {
                    maxCaptures = currentMove->tail->captures;
                    chosenMoveIndex = currentIndex; //found the best move list
                }
            }
            currentListCell = currentListCell->next;
            currentIndex++;
        }
        if (chosenMoveIndex != -1) {
            chosenMove = getSingleSourceMovesListByIndex(res, chosenMoveIndex);
            makeMove(board, chosenMove, player); //change the board
        }
        else//there wasnt a max capture move- we'll use rule number 4
        {

        }

        //looking for the min and max rows and cols so we can choose the best move
       /* currentListCell = res->head;*/

        //while (currentListCell != NULL) {//as long as we have lists
        //    currentMove = currentListCell->single_source_moves_lists;
        //    if ((currentMove->head->position->row)-CHAR_A < minRow)//if its a smaller row
        //        minRow = (currentMove->head->position->row)-CHAR_A;//update min row

        //    if ((currentMove->head->position->row)-CHAR_A > maxRow)//if its a higer row
        //        maxRow = (currentMove->head->position->row)-CHAR_A;//update high row

        //    if ((currentMove->head->position->col)-CHAR_0 < minCol)//if its a smaller col
        //        minCol = (currentMove->head->position->col)-CHAR_0;//update min col

        //    if ((currentMove->head->position->col)-CHAR_0 > maxCol)//if its a max col
        //        maxCol = (currentMove->head->position->col)-CHAR_0;//update max col

            //go to the next list
        //    currentListCell = currentListCell->next;
        //}

        ////currentMove = res->head->single_source_moves_lists;//first list of moves
        //currentListCell = res->head;
        //bool bestMove = false;//boolian for checking if best move was found

        ////rule in exercise 4- when theres no max number of captures
        //while (currentListCell != NULL && !bestMove) {//looking for the best move  
        //    currentMove = currentListCell->single_source_moves_lists;
        ////if its player B we choose lowest row and then if there are equal rows then lowest cols
        //    if (player == PLAYER_B) {
        //        if ((currentMove->head->position->row) - CHAR_A == minRow ) {
        //            if ((currentMove->head->position->col) - CHAR_0 == minCol)
        //                bestMove = true;//found best move
        //            chosenMove = currentMove;//found best move
        //        }
        //        if ((currentMove->head->position->row) - CHAR_A > minRow) {
        //            bestMove=true;
        //        }
        //    }
        //if its player T we choose highest row and then if there are equal rows then highest cols
//else if (player == PLAYER_T) {

//    if ((currentMove->head->position->row) - CHAR_A == maxRow && (currentMove->head->position->col) - CHAR_0 == maxCol) {
//        bestMove = true;//found best move
//    }
//    else if ((currentMove->head->position->row) - CHAR_A == maxRow) {
//        chosenMove = currentMove;//found best move
//    }
//}
////found best move=>update the list to be the list we just found
//if (bestMove) {
//    chosenMove = currentMove;
//}
//else {
//    //next list
//    currentListCell = currentListCell->next;
//}
//    }//while

    ////do the best move
    //    if (bestMove != NULL) {
    //         makeMove(board,chosenMove ,player);
    //    }

//else no large captures
//else more than 1 list

//update the max capture in the whole game
    }
    if (maxGameCaptures < maxCaptures) {
        maxGameCaptures = maxCaptures;
        if (player == PLAYER_B)
            maxcapturePlayer = PLAYER_B;
        else
            maxcapturePlayer = PLAYER_T;
    }

    //free
    RemoveSingleSourceMovesList(res);
}
//function to check if the game is finished
bool isGameNotFinished(Board board, Player player) {
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
        return false;  //game over
    }

//checking if player B is in the first row
    if (player == PLAYER_B) {
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[0][i] == player) {
                return false; //B won-game over
            }
        }
    }
    //checking if player T is in the last row
    else if (player == PLAYER_T) {
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[BOARD_SIZE - 1][i] == player) {
                return false; //T won-game over
            }
        }
    }

    return true; //game ont over yet
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
void makeMove(Board board, SingleSourceMovesList* move, Player player) {
   
    //moving the player from the stating point to end point and making the starting point empty
    int col = (move->head->position->col) - CHAR_0 - 1;
    int row = (move->head->position->row) - CHAR_A;
    board[(move->tail->position->row)-CHAR_A][(move->tail->position->col)-CHAR_0-1] = board[(move->head->position->row)-CHAR_A][(move->head->position->col)-CHAR_0-1];
    board[(move->head->position->row) - CHAR_A][(move->head->position->col) - CHAR_0 - 1] = EMPTY_POS;
     
    printf("%c%d->%c%d\n", move->head->position->row, move->head->position->col, move->tail->position->row, move->tail->position->col);
    // Checking for any capture moves and removing the captured positions
    if (move->tail->captures != 0) {
        SingleSourceMovesListCell* currentPos = move->head->next;
        while (currentPos != NULL) {
            int captureRow = (currentPos->position->row) - CHAR_A;
            int captureCol = (currentPos->position->col) - CHAR_0 - 1;

            if (player == PLAYER_T) {
                if (col < captureCol)
                    board[captureRow - 1][captureCol - 1] = EMPTY_POS;
                else if (col > captureCol)
                    board[captureRow - 1][captureCol + 1] = EMPTY_POS;
            }
            else if (player == PLAYER_B) {
                if (col < captureCol)
                    board[captureRow + 1][captureCol - 1] = EMPTY_POS;
                else if (col > captureCol)
                    board[captureRow + 1][captureCol + 1] = EMPTY_POS;
            }
            col = captureCol;
            row = captureRow;
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
            free(curr->position);
            free(curr);
            curr = nextMove;
        }
        free(largeList);
        largeList = nextLargeList;
    }

}

void PlayGame(Board board, Player starting_player)
{
    ////constant int for max captures in game
    //int maxGameCaptures = 0;
    //char maxcapturePlayer = EMPTY_POS;
    //int countCapturesT = 0;
    //int countCapturesB = 0;
    printBoard(board);
    Player currentPlayer = starting_player;
    while (isGameNotFinished(board,currentPlayer)) {//while game isnt finished

        printf("%c's turn:\n",currentPlayer);
        Turn(board, currentPlayer);





        printBoard(board);

        //change players
        if (currentPlayer == PLAYER_B)
            currentPlayer = PLAYER_T;
        else
            currentPlayer = PLAYER_B;
    }

}

void printBoard(Board board)
{
    int i,j,value;
    int row=0, col=0;
    char letter = FIRST_ROW;;
    for (i = 0; i < BOARD_PRINTING_SIZE; i++)
    {
        if (i == 1) {//print the line of line numbers
            printf("%c ", PLUS);
            for (value = FIRST_COL; value <= BOARD_SIZE; value++)
                printf("|%d", value);
        printf("|\n");
        }
        else if (i % 2 == 0)//print the plus and minus line
        {
            printMidLine();
        }
        
        else//print the board
        {
            printf("|%c", letter);
            col = 0;
            for (j = 0; j < BOARD_SIZE; j++) {
                if (board[row][col] == NULL) 
                    printf("| ");
                else
                    printf("|%c", board[row][col]);
                col++;
            }
            printf("|\n");
            letter++; 
            row++;

        }
    }

}

void printMidLine()
{
    int i;
    for (i = 0; i < PLUS_MINUS_LINE_LEN; i++)
        printf("%c%c", PLUS, MINUS);
    printf("%c\n", PLUS); //last plus in the line
}