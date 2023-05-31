#include "main.h"
#include "Trees.h"


//function gets a board and a pointer to a checker pos, and returns a tree of every possible moves if there are any
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {

    int row = (src->row) - CHAR_A; //from letter to number
    int col = (src->col) - CHAR_0 -1; //from char number to int number
    char player = board[row][col];
    unsigned short capturesSoFar = 0;
    SingleSourceMovesTree* res;
    //checker pos is empty
    if (player == EMPTY_POS)
        return NULL;

    //checkers pos isnt empty
    else {
        res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));

        //memory allocation check
        memoryAllocationCheckTree(res);
        res->source = buildTreeHelper(board, row, col, player, capturesSoFar);//recursive function to create the tree for the checkers pos moves

    }
    return res;

}
//This function is creating the tree for one move possibilities of the checkers pos
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar)
{
    SingleSourceMovesTreeNode* root;
    Board copyBoardRight, copyBoardLeft;//new board each rec call
    char left, right;
    int nRow, nCol; //next new col and row


    root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

    //copyBorad(board, copyBoard);
    //if the player is T he's moving downwards
    if (player == PLAYER_T)
    {
        if (row >= BOARD_SIZE - 1) //bottom of the board, no moves to do
            return root;

        if (col < BOARD_SIZE-1) //can go right
        {
            right = board[row + 1][col + 1];
            copyBorad(board, copyBoardRight); //לבדוק אחכ אם אפשר להכניס לבפנים, שלא יעתיק סתם אם לא צריך
            if (right == PLAYER_B)
            {
                if (col <= MAX_COL && row <= MAX_ROW) //if still can eat
                {
                    unsigned short tempCaptures = capturesSoFar;
                    nRow = row ;
                    nCol = col;
                    //if (board[nRow][nCol] == NULL)
                    //{
                    //    capturesSoFar++;
                    //    copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                    //    copyBoard[row + 1][col + 1] = EMPTY_POS; //eaten
                    //    copyBoard[nRow][nCol] = PLAYER_T; //moving 'T' 2 cols right 2 rows down
                    captureMove(player, RIGHT, board,row , col,&nRow,&nCol, &tempCaptures, copyBoardRight);
                    root->next_move[RIGHT] = buildTreeHelper(copyBoardRight, nRow, nCol, player, tempCaptures);
                    /*}*/
                    //else
                    //    root->next_move[RIGHT] = NULL;
                }
            }
            else if (right == EMPTY_POS && capturesSoFar == 0) //no captures, one move to go
            {
                nRow = row;
                nCol = col;
                //capturesSoFar = 0;
                //copyBoardRight[row][col] = EMPTY_POS; //changing current checkerPos
                //copyBoardRight[nRow][nCol] = PLAYER_T; //moving 'T' right and down //create Tnode?
                //root->next_move[RIGHT] = createNewTNode(copyBoardRight, nRow, nCol, capturesSoFar, NULL, NULL);
                singleMove(root, player, RIGHT, copyBoardRight, row, col, &nRow, &nCol, &capturesSoFar);
            }
        }

        if (col >0)
        {
            
            left = board[row + 1][col - 1];
            copyBorad(board, copyBoardLeft);

            if (left == PLAYER_B)
            {
                if (col >= 2 && row <= MAX_ROW) //if still can eat
                {
                    //nRow = row + 2;
                    //nCol = col - 2;
                    //if (board[nRow][nCol] == NULL)
                    //{
                    //    capturesSoFar++;
                    //    copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                    //    copyBoard[row+1][col + 1] = EMPTY_POS; //eaten
                    //    copyBoard[nRow][nCol] = PLAYER_T; //moving 'T' 2 cols right 2 rows down
                    unsigned short tempCaptures = capturesSoFar;
                    captureMove(player, LEFT, board, row, col,&nRow,&nCol, &tempCaptures, copyBoardLeft);
                    root->next_move[LEFT] = buildTreeHelper(copyBoardLeft, nRow, nCol, player, tempCaptures);
                    //}
                }

                //else

                //root->next_move[LEFT] == NULL;

            }

            else if (left == EMPTY_POS && capturesSoFar == 0) //no captures, one move to go
            {
                nRow = row;
                nCol = col;
                //capturesSoFar = 0;
                //copyBoardLeft[row][col] = EMPTY_POS; //changing current checkerPos
                //copyBoardLeft[nRow][nCol] = PLAYER_T; //moving 'T' left and down
                //root->next_move[LEFT] = createNewTNode(copyBoardLeft, nRow, nCol, capturesSoFar, NULL, NULL);
                singleMove(root, player, LEFT, copyBoardLeft, row, col, &nRow, &nCol, &capturesSoFar);

            }

        }

    }//player one check

    //if (right == 'T' && left == 'T')
    //    return root; //no moves to do

     //if the data is B
    if (player == PLAYER_B) {

        if (row < 0) //top of the board, no moves to do
            return root;
        if (col < BOARD_SIZE - 1) {
            right = board[row - 1][col + 1];
            copyBorad(board, copyBoardRight);
            //capture move for B
            if (right == PLAYER_T)
            {
                if (col <= MAX_COL && row >= 2) //if still can eat
                {
                    nRow = row;
                    nCol = col;
                    //if (board[nRow][nCol] == NULL)
                    //{
                    //    capturesSoFar++;
                    //    copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                    //    copyBoard[row + 1][col + 1] = EMPTY_POS; //eaten
                    //    copyBoard[nRow][nCol] = PLAYER_B; //moving 'T' 2 cols right 2 rows down
                    unsigned short tempCaptures = capturesSoFar;
                    captureMove(player, RIGHT, board, row, col, &nRow, &nCol, &tempCaptures, copyBoardRight);
                    root->next_move[RIGHT] = buildTreeHelper(copyBoardRight, nRow, nCol, player, tempCaptures);
                    //}
                    //else
                    //    root->next_move[RIGHT] = NULL;
                }
            }
            else if (right == EMPTY_POS && capturesSoFar == 0)
            {
                nRow = row;
                nCol = col;
                //capturesSoFar = 0;
                //copyBoardRight[row][col] = EMPTY_POS; //changing current checkerPos
                //copyBoardRight[nRow][nCol] = PLAYER_B; //moving 'B' right and up 
                //root->next_move[RIGHT] = createNewTNode(copyBoardRight, nRow, nCol, capturesSoFar, NULL, NULL);
                singleMove(root, player, RIGHT, copyBoardRight, row, col, &nRow, &nCol, &capturesSoFar);
                
            }
        }
        if (col > 0)
        {
            left = board[row -1 ][col - 1];
            copyBorad(board, copyBoardLeft);

            if (left == PLAYER_T)
            {
                if (col >= 2 && row >=2) //if still can eat
                {
                    nRow = row;
                    nCol = col;
                    //if (board[nRow][nCol] == NULL)
                    //{
                    //    capturesSoFar++;
                    //    copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                    //    copyBoard[row+1][col + 1] = EMPTY_POS; //eaten
                    //    copyBoard[nRow][nCol] = PLAYER_T; //moving 'T' 2 cols right 2 rows down
                    unsigned short tempCaptures = capturesSoFar;
                    captureMove(player, LEFT, board, row, col, &nRow, &nCol, &tempCaptures, copyBoardLeft);
                    root->next_move[LEFT] = buildTreeHelper(copyBoardLeft, nRow, nCol, player, tempCaptures);
                    //}
                }

                //else
                //root->next_move[LEFT] == NULL;

            }

            else if (left == EMPTY_POS && capturesSoFar == 0)
            {
                nRow = row;
                nCol = col ;
                //capturesSoFar = 0;
                //copyBoardLeft[row][col] = EMPTY_POS; //changing current checkerPos
                //copyBoardLeft[nRow][nCol] = PLAYER_B; //moving 'B' left and down
                //root->next_move[LEFT] = createNewTNode(copyBoardLeft, nRow, nCol, capturesSoFar, NULL, NULL);
                singleMove(root, player, LEFT, copyBoardLeft, row, col, &nRow, &nCol, &capturesSoFar);
            }

        }
    }

   ///* else
   // {
   //     if (row <= ROW_0)
   //         return root;
   //     root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

   //}*/
    return root;

}
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight)
{
    SingleSourceMovesTreeNode* res;
    checkersPos* pos;

    res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));

    memoryAllocationCheckTreeNode(res);

    pos = (checkersPos*)malloc(sizeof(checkersPos));

    if (pos == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
    pos->col = CHAR_0 + col+1;
    pos->row = CHAR_A + row;


    copyBorad(board, res->board);
    res->pos = pos;
    res->total_captures_so_far = captures;
    res->next_move[LEFT] = nextMoveLeft;
    res->next_move[RIGHT] = nextMoveRight;
    return res;
}

void memoryAllocationCheckTreeNode(SingleSourceMovesTreeNode* res) {
    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
}

void memoryAllocationCheckTree(SingleSourceMovesTree* res) {
    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
}
//function for caprute moves of T an B
void captureMove(char player,int direction,Board board, int row, int col,int* nRow,int*nCol, unsigned short* capturesSoFar,Board copyBoard) {

    
    if (player == PLAYER_T) {
        if (direction == RIGHT) {
            *nRow = row + 2;
            *nCol = col + 2;
           
        }
        else if(direction==LEFT) {
            *nRow = row + 2;
            *nCol = col - 2;
        }
        //if theres an empty space afetr the B
        if (board[*nRow][*nCol] == NULL)
        {
          (*capturesSoFar)++;
          copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
          copyBoard[*nRow][*nCol] = PLAYER_T; //moving 'T' 2 cols (right or left) 2 rows down
          
          if (direction ==RIGHT)
            copyBoard[row + 1][col + 1] = EMPTY_POS; //eaten the right B
          if (direction ==LEFT)
            copyBoard[row + 1][col - 1] = EMPTY_POS; //eat the left B
        }
       
    }
    else {//player==PLAYER_B

        if (direction == RIGHT) {
            *nRow = row - 2;
            *nCol = col + 2;

        }
        else if (direction == LEFT) {
            *nRow = row - 2;
            *nCol = col - 2;
        }
        if (board[*nRow][*nCol] == NULL)
        {
            (*capturesSoFar)++;
            copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
            copyBoard[*nRow][*nCol] = PLAYER_B; //moving 'B' 2 cols (right or left) 2 rows up

            if (direction == RIGHT)
                copyBoard[row - 1][col + 1] = EMPTY_POS; //eaten the right A
            if (direction == LEFT)
                copyBoard[row - 1][col - 1] = EMPTY_POS; //eat the left A
        }
    }
}
//this function is for one move only if there are no cature moves available
void singleMove(SingleSourceMovesTreeNode* root, char player, int direction, Board board, int row, int col, int* nRow, int* nCol, unsigned short* capturesSoFar) {

    if (player == PLAYER_T) {
        *capturesSoFar = 0;
        if (direction == RIGHT) {
            *nRow = row + 1;
            *nCol = col + 1;
        }
        if (direction == LEFT) {
            *nRow = row + 1;
            *nCol = col - 1;
        }

        //update the board
        board[row][col] = EMPTY_POS; //changing current checkerPos
        board[*nRow][*nCol] = PLAYER_T; //moving 'T' left/right and down the board

        if (direction == RIGHT)
            root->next_move[RIGHT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);
        if (direction == LEFT)
            root->next_move[LEFT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);

    }
    else { //player B
        *capturesSoFar = 0;
        if (direction == RIGHT) {
            *nRow = row - 1;
            *nCol = col + 1;
        }
        if (direction == LEFT) {
            *nRow = row - 1;
            *nCol = col - 1;
        }
        board[row][col] = EMPTY_POS; //changing current checkerPos
        board[*nRow][*nCol] = PLAYER_B; //moving 'B' left/right and up
        if (direction==RIGHT)
            root->next_move[RIGHT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);
        if(direction==LEFT)
            root->next_move[LEFT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);
    }
}

void freeTree(SingleSourceMovesTree *tr)
{
    freeTreeHelper(tr->source);
}

void freeTreeHelper(SingleSourceMovesTreeNode* root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeHelper(root->next_move[LEFT]);
        freeTreeHelper(root->next_move[RIGHT]);
        free(root);
    }
}
