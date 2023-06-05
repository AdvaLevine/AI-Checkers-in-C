#include "main.h"
#include "Lists.h"

//constant int for max captures in game
extern int maxGameCaptures = 0;
extern char maxcapturePlayer = EMPTY_POS;

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
//function to copy the board
void copyBorad(Board board, Board copyBoard)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            copyBoard[i][j] = board[i][j];
        }
    }
}
/*This function gets the board in its most updated form, the player thats abount to make the move
and i creates the list of the most optimal moves for each tools of this player, 
then it chooses the best move out of all pos, depending on which player it is:
first it makes sure to do the move with the most captures, else theres no such-
if it's player T, it'll always choose the highest row, else the highest col
if it's player B, it'll always choose the lowest row, else the lowest col
it updates the board acccording to the chosen move,
then it updates the max captures external varible and frees the lists of moves 
*/
void Turn(Board board, Player player) {

    unsigned short maxCaptures = 0, currentCaptures =0;
    int chosenMoveIndex = -1;                                           //chosen list move
    int count = 0;
    int i = 0;
    int chosenRow, currentRow, chosenCol, currentCol;
    SingleSourceMovesList* currentMove = NULL;                          //current move- single list
    SingleSourceMovesList* chosenMove = NULL;                           //the list of move we choose
    multipleSourceMoveListCell* numOfListsCurr = NULL;                  //number of list curr
    multipleSourceMoveListCell* currentMultipleListCell = NULL;         //the current multiple list cell                         
    multipleSourceMoveList* res;                                        //multi list res

    res = (multipleSourceMoveList*)malloc(sizeof(multipleSourceMoveList));//create the list of lists
    checkAllocationMultipleList(res);
  
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
        chosenMove = res->head->single_source_moves_list;
        makeMove(board, chosenMove, player); //change the board
    }
    //more then one list
    else
    {
        currentMultipleListCell = res->head;
        chosenMove = currentMultipleListCell->single_source_moves_list; //initializing best move to the first route
        //check if the first one is available move
        while (chosenMove->head->next == NULL)
        {
            currentMultipleListCell = currentMultipleListCell->next;
            chosenMove = currentMultipleListCell->single_source_moves_list;
        }
        //once its found an availble list
        chosenRow = (chosenMove->head->position->row)- CHAR_A;                  //update  chosen row
        chosenCol = (chosenMove->head->position->col) - CHAR_0;                 //update chosen col
        currentMove = chosenMove;                                               //current list of moves
        maxCaptures = currentMove->tail->captures;                              //initializing with the captures of the first move list.
        if (player == PLAYER_T)                                                 //if its player T
        {
            while (currentMultipleListCell != NULL)                             //find max captures
            {
                currentMove = currentMultipleListCell->single_source_moves_list;
                if (currentMove->head->next != NULL)
                { 
                    currentCaptures = currentMove->tail->captures;
                    currentRow = (currentMove->head->position->row) - CHAR_A;   //current route cell start row
                    currentCol = (currentMove->head->position->col) - CHAR_0;   //current route cell start col
                    if (currentCaptures > maxCaptures)                          //if current move has more captures=> update capture and chosen move
                    {
                        chosenMove = currentMove;
                        maxCaptures = currentCaptures;
                        chosenRow = currentRow;
                        chosenCol = currentCol;
                    }
                    else if (currentCaptures == maxCaptures) //if both routes have the same captures number
                    {
                        if (currentRow > chosenRow) //current row is bigger - chosen by the rules for player T
                        {
                            //update the new best chosen route
                            chosenMove = currentMove;
                            maxCaptures = currentCaptures;
                            chosenRow = currentRow;
                            chosenCol = currentCol;
                        }
                        else if ((currentRow == chosenRow) && currentCol > chosenCol) //in the same row but current has the best col
                        {
                            chosenMove = currentMove;
                            maxCaptures = currentCaptures;
                            chosenRow = currentRow;
                            chosenCol = currentCol;
                        }
                        //else, current isn't the best move
                    }
                }
                currentMultipleListCell = currentMultipleListCell->next;
            }
        }
        if (player == PLAYER_B)                                                     //if its player B
        {
            while (currentMultipleListCell != NULL)
            {
                currentMove = currentMultipleListCell->single_source_moves_list;
                if (currentMove->head->next != NULL)
                { 
                    currentCaptures = currentMove->tail->captures;
                    currentRow = (currentMove->head->position->row) - CHAR_A;       //current route cell start row
                    currentCol = (currentMove->head->position->col) - CHAR_0;       //current route cell start col
                    if (currentCaptures > maxCaptures)                               //if current move has more captures=> update capture and chosen move
                    {
                        chosenMove = currentMove;
                        maxCaptures = currentCaptures;
                        chosenRow = currentRow;
                        chosenCol = currentCol;
                    }
                    else if (currentCaptures == maxCaptures) //if both routes have the same captures number
                    {
                        if (currentRow < chosenRow) //current row is smaller - chosen by the rules for player B
                        {
                            //update the new best chosen route
                            chosenMove = currentMove;
                            maxCaptures = currentCaptures;
                            chosenRow = currentRow;
                            chosenCol = currentCol;
                        }
                        else if ((currentRow == chosenRow) && currentCol < chosenCol) //in the same row but current has the best col
                        {
                            chosenMove = currentMove;
                            maxCaptures = currentCaptures;
                            chosenRow = currentRow;
                            chosenCol = currentCol;
                        }
                        //else, current isn't the best move
                    }
                }
                currentMultipleListCell = currentMultipleListCell->next;//move to next list
            }
        }
    }
        makeMove(board, chosenMove, player); //change the board

        //update the max capture in the whole game
        if (maxGameCaptures < maxCaptures) {
            maxGameCaptures = maxCaptures;
            if (player == PLAYER_B)
                maxcapturePlayer = PLAYER_B;
            else
                maxcapturePlayer = PLAYER_T;
        }
 
        //free lists
        RemoveSingleSourceMovesList(res);
       
}
//function to check if the game is finished also prints who won
bool isGameNotFinished(Board board, Player player) {
    int i, j;
    int playerBPieces = 0;          //counter for the player B pieces
    int playerTPieces = 0;          //counter for player T pieces
   
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
    if (playerBPieces == 0 ){
        printf("T wins!\n");
        return false;  //game over
    }
    if (playerTPieces == 0) {
        printf("B wins!\n");
        return false;  //game over
    }
    

//checking if player B is in the first row
    for (i = 0; i < BOARD_SIZE; i++) {
         if (board[0][i] == PLAYER_B) {
             printf("B wins!\n");
             return false; //B won-game over
         }
    }
    
    //checking if player T is in the last row
     for (i = 0; i < BOARD_SIZE; i++) {
         if (board[BOARD_SIZE - 1][i] == PLAYER_T) {
             printf("T wins!\n");
              return false; //T won-game over
         }
     }
   

    return true; //game ont over yet
}

//This function is getting the board and a list of moves and changes it according to the list
void makeMove(Board board, SingleSourceMovesList* move, Player player) {
   
    int col = (move->head->position->col) - CHAR_0 - 1;                     //saving the first row
    int row = (move->head->position->row) - CHAR_A;                         //saving the first col
    //moving the player from the stating point to end point and making the starting point empty
    board[(move->tail->position->row)-CHAR_A][(move->tail->position->col)-CHAR_0-1] = board[(move->head->position->row)-CHAR_A][(move->head->position->col)-CHAR_0-1];
    board[(move->head->position->row) - CHAR_A][(move->head->position->col) - CHAR_0 - 1] = EMPTY_POS;

     //prints the players move positions
    printf("%c%d->%c%d\n", move->head->position->row, move->head->position->col, move->tail->position->row, move->tail->position->col);

    // Checking for any capture moves and removing the captured positions
    if (move->tail->captures != 0) {
        SingleSourceMovesListCell* currentPos = move->head->next;
        while (currentPos != NULL) {
            int captureRow = (currentPos->position->row) - CHAR_A;
            int captureCol = (currentPos->position->col) - CHAR_0 - 1;

            if (player == PLAYER_T) {                                   //if its a capture of player T
                if (col < captureCol)
                    board[captureRow - 1][captureCol - 1] = EMPTY_POS;  //update the board
                else if (col > captureCol)
                    board[captureRow - 1][captureCol + 1] = EMPTY_POS;  //update the board
            }
            else if (player == PLAYER_B) {                              //if its a capture of player B
                if (col < captureCol)
                    board[captureRow + 1][captureCol - 1] = EMPTY_POS;  //update the board
                else if (col > captureCol)
                    board[captureRow + 1][captureCol + 1] = EMPTY_POS;  //update the board
            }
            col = captureCol;                                           //old col is current col
            row = captureRow;                                           //old row is current row
            currentPos = currentPos->next;                              //next list cell
        }
    }
   
}
//This function frees all the lists and the multi list
void RemoveSingleSourceMovesList(multipleSourceMoveList* list) {

    multipleSourceMoveListCell* largeList = list->head;
    multipleSourceMoveListCell* nextLargeList;
    SingleSourceMovesList* smallList;
    SingleSourceMovesListCell* curr;
    SingleSourceMovesListCell* nextMove;


    while (largeList != NULL) {
        smallList = largeList->single_source_moves_list;
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
/*This function is the main function of the game, it checks using other function to make sure the game isnt finished,
it calls a function to always choose and make the best move and then it switches between each player at a time, 
it print the board in each round and at the end it prints who made the most capture moves*/
void PlayGame(Board board, Player starting_player)
{
    int countBMoves = 0;                                    //counter for players moves
    int countTMoves = 0;
    printBoard(board);                                      //prints the starting board
    Player currentPlayer = starting_player;
    
    while (isGameNotFinished(board,currentPlayer)) {        //while game isnt finished
        printf("%c's turn:\n",currentPlayer);               //print who's turn it is
        Turn(board, currentPlayer);                         //chose and make a move

        printBoard(board);                                  //print the board

        //change players
         if (currentPlayer == PLAYER_B) {
            countBMoves++;
            currentPlayer = PLAYER_T;
        }
        else {
            countTMoves++;
            currentPlayer = PLAYER_B;
        }
    }
    //the other way around because when we leave the loop we change the players
    //printing the winning player preformence
    if (currentPlayer == PLAYER_B)
        printf("T preformed %d moves.\n",countTMoves);
    else
        printf("B preformed %d moves.\n", countBMoves);
    //prints the most capture moves
    printf("%c preformed the highest number of captures in a single move - %d", maxcapturePlayer, maxGameCaptures);

}
//This function gets a board and prints it out 
void printBoard(Board board)
{
    int i,j,value;
    int row=0, col=0;
    char letter = FIRST_ROW;;
    for (i = 0; i < BOARD_PRINTING_SIZE; i++)
    {
        if (i == 1) {                                               //print the line of line numbers
            printf("%c ", PLUS);
            for (value = FIRST_COL; value <= BOARD_SIZE; value++)
                printf("|%d", value);
        printf("|\n");
        }
        else if (i % 2 == 0)                                        //print the plus and minus line
        {
            printMidLine();
        }
        
        else                                                        //print the board
        {
            printf("|%c", letter);                                  //prints the beggining letters in each row
            col = 0;
            for (j = 0; j < BOARD_SIZE; j++) {
                if (board[row][col] == NULL) 
                    printf("| ");
                else
                    printf("|%c", board[row][col]);                 //prints the board
                col++;
            }
            printf("|\n");
            letter++;                                               //next letter
            row++;                                                  //next row
        }
    }
}
//This function is for printing the line inbetween with the plus and minus
void printMidLine()
{
    int i;
    for (i = 0; i < PLUS_MINUS_LINE_LEN; i++)
        printf("%c%c", PLUS, MINUS);
    printf("%c\n", PLUS); //last plus in the line
}