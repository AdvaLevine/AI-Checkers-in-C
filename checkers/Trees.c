#include "main.h"
#include "Trees.h"


//function gets a board and a pointer to a checker pos, and returns a tree of every possible moves if there are any
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {

    int row = (src->row) - CHAR_A;                  //convert from letter to number
    int col = (src->col) - CHAR_0 -1;               //convert from char number to number
    char player = board[row][col];                  //the char of the player
    unsigned short capturesSoFar = 0;               //counter for the captures
    SingleSourceMovesTree* res;                     //tree 

    //checker pos is empty then no need for a tree
    if (player == EMPTY_POS)
        return NULL;

    //checkers pos isnt empty=>need to bulid a tree
    else {
        res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));            //create a tree
        //memory allocation check
        memoryAllocationCheckTree(res);
        //recursive function to create the tree for the checkers pos moves
        res->source = buildTreeHelper(board, row, col, player, capturesSoFar);

    }
    return res;                             //return the tree

}
//This function is creating the tree for one move possibilities of the checkers pos
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar)
{
    SingleSourceMovesTreeNode* root;                //tree root
    Board copyBoardRight, copyBoardLeft;            //new board each rec call
    char left, right;                               //for the next moves
    int nRow, nCol;                                 //next new col and row

    //creating the root
    root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

  
    //if the player is T he's moving downwards
    if (player == PLAYER_T)
    {
        if (row >= BOARD_SIZE - 1) //bottom of the board, no moves to do
            return root;

        if (col < BOARD_SIZE-1) //can go right
        {
            right = board[row + 1][col + 1];                //update the right
            copyBorad(board, copyBoardRight);               //copy the board to its node
            if (right == PLAYER_B)                          //if on the right theres a possible capture move
            {
                if (col <= MAX_COL && row <= MAX_ROW)       //if still can eat(wont excceed board size)
                {
                    unsigned short tempCaptures = capturesSoFar;        //save the captures
                    nRow = row ;                                        //to update the board we need to change the row so we copy it to a different variable
                    nCol = col;                                         //to update the board we need to change the col so we copy it to a different variable
                    //if there was a capture move we create a new node and add it to the tree
                    if(captureMove(player, RIGHT, board,row , col,&nRow,&nCol, &tempCaptures, copyBoardRight))
                        root->next_move[RIGHT] = buildTreeHelper(copyBoardRight, nRow, nCol, player, tempCaptures);
                    else                                                //there wasnt a possible capture move=> we leave the child as null
                        root->next_move[RIGHT] = NULL;
                }
            }
            else if (right == EMPTY_POS && capturesSoFar == 0) //no captures, one move to go
            {
                nRow = row;                                             //to update the board we need to change the row so we copy it to a different variable
                nCol = col;                                             //to update the board we need to change the col so we copy it to a different variable
                //we make one move on the board(theres no capture move to do)
                singleMove(root, player, RIGHT, copyBoardRight, row, col, &nRow, &nCol, &capturesSoFar);
            }
        }
        
        if (col >0)//if the player can go left
        {
            
            left = board[row + 1][col - 1];                     //save the char thats on its left
            copyBorad(board, copyBoardLeft);                    //create a copy board for its node

            if (left == PLAYER_B)                               //if the player on the left is player B
            {
                if (col >= 2 && row <= MAX_ROW)                 //if still can eat(wont excceed board size)
                {
                    nRow = row;                                 //to update the board we need to change the row so we copy it to a different variable
                    nCol = col;                                 //to update the board we need to change the col so we copy it to a different variable
                    unsigned short tempCaptures = capturesSoFar;//save the current number of captures
                    //if there was a capture move we create a new node and add it to the tree
                    if(captureMove(player, LEFT, board, row, col,&nRow,&nCol, &tempCaptures, copyBoardLeft))
                        root->next_move[LEFT] = buildTreeHelper(copyBoardLeft, nRow, nCol, player, tempCaptures);
                    else                                        //there wasnt a possible capture move=> we leave the child as null
                        root->next_move[LEFT] == NULL;

                }

            }

            else if (left == EMPTY_POS && capturesSoFar == 0) //no captures, one move to go
            {
                nRow = row; //to update the board we need to change the row so we copy it to a different variable
                nCol = col;//to update the board we need to change the col so we copy it to a different variable
                //we make one move on the board(theres no capture move to do)
                singleMove(root, player, LEFT, copyBoardLeft, row, col, &nRow, &nCol, &capturesSoFar);

            }

        }

    }//player one check

     //if the player is B
    if (player == PLAYER_B) {

        if (row < 0) //top of the board, no moves to do
            return root;
        if (col < BOARD_SIZE - 1) {                             //if it has a possbility to move right
            right = board[row - 1][col + 1];                    //update the char to be the char on its right
            copyBorad(board, copyBoardRight);                   //copy the board to its node
            //capture move for B
            if (right == PLAYER_T)//if it has the enemy's player on the riight
            {
                if (col <= MAX_COL && row >= 2) //if still can eat (wont excceed board size)
                {
                    nRow = row;                                //to update the board we need to change the row so we copy it to a different variable
                    nCol = col;                                //to update the board we need to change the col so we copy it to a different variable
                    unsigned short tempCaptures = capturesSoFar;        //save the capture number 
                    //if there was a capture move we create a new node and add it to the tree
                    if(captureMove(player, RIGHT, board, row, col, &nRow, &nCol, &tempCaptures, copyBoardRight)) 
                        root->next_move[RIGHT] = buildTreeHelper(copyBoardRight, nRow, nCol, player, tempCaptures);
                    else  //there wasnt a possible capture move=> we leave the child as null
                        root->next_move[RIGHT] = NULL;
                }
            }

            else if (right == EMPTY_POS && capturesSoFar == 0)//no captures, one move to go
            {
                nRow = row;                                   //to update the board we need to change the row so we copy it to a different variable
                nCol = col;                                   //to update the board we need to change the col so we copy it to a different variable
                //we make one move on the board(theres no capture move to do)
                singleMove(root, player, RIGHT, copyBoardRight, row, col, &nRow, &nCol, &capturesSoFar);  
            }
        }
        if (col > 0)//if it has moves to the left (not the edge of the board)
        {
            left = board[row -1 ][col - 1];                 //save the char on its left
            copyBorad(board, copyBoardLeft);                //copy the board to its node

            if (left == PLAYER_T)                           //a possible capture move for player B ( has its enemy on the left)
            {
                if (col >= 2 && row >=2) //if still can eat(wont excceed board size)
                {
                    nRow = row;                             //to update the board we need to change the row so we copy it to a different variable
                    nCol = col;                             //to update the board we need to change the col so we copy it to a different variable
                    unsigned short tempCaptures = capturesSoFar;        //save the number of captures
                    //if there was a capture move we create a new node and add it to the tree
                    if(captureMove(player, LEFT, board, row, col, &nRow, &nCol, &tempCaptures, copyBoardLeft))
                        root->next_move[LEFT] = buildTreeHelper(copyBoardLeft, nRow, nCol, player, tempCaptures);
                    else                         //there wasnt a possible capture move=> we leave the child as null
                        root->next_move[LEFT] == NULL;
                }
            }

            else if (left == EMPTY_POS && capturesSoFar == 0)//no captures, one move to go
            {
                nRow = row;                                 //to update the board we need to change the row so we copy it to a different variable
                nCol = col;                                 //to update the board we need to change the col so we copy it to a different variable
                //we make one move on the board(theres no capture move to do)
                singleMove(root, player, LEFT, copyBoardLeft, row, col, &nRow, &nCol, &capturesSoFar);
            }
        }
    }
    return root;//return thr tree node
}
//This function creates a SingleSourceMovesTreeNode for each and every pos we give it, it inserts the pos and board to the tree node
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight)
{
    SingleSourceMovesTreeNode* res;                 //initilize the tree node
    checkersPos* pos;                               //initilize the pos of the node
    //allocating  the node
    res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
    //check if memmory was allocated
    memoryAllocationCheckTreeNode(res);
    //allocating the pos
    pos = (checkersPos*)malloc(sizeof(checkersPos));
    //checking if pos was allocated
    if (pos == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
    //put the row and col in the pos 
    pos->col = CHAR_0 + col+1;
    pos->row = CHAR_A + row;
    //copy the board to res
    copyBorad(board, res->board);
    res->pos = pos;                                     //putting the pos in res
    res->total_captures_so_far = captures;              //putting the number of captures in res
    res->next_move[LEFT] = nextMoveLeft;                //puting next move in left in res
    res->next_move[RIGHT] = nextMoveRight;              //putting next move in right in res

    return res;                                         //return tree node
}
//This function checks if the tree node was allocated
void memoryAllocationCheckTreeNode(SingleSourceMovesTreeNode* res) {
    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
}
//This function checkes if the trree was allocated
void memoryAllocationCheckTree(SingleSourceMovesTree* res) {
    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
}
//function for caprute moves of T an B, gets the board and checks if theres a possible move to capture, if so it changes the board
bool captureMove(char player,int direction,Board board, int row, int col,int* nRow,int*nCol, unsigned short* capturesSoFar,Board copyBoard) {

    bool res =true;
    if (player == PLAYER_T) {
        if (direction == RIGHT) {                   //possible capture on the right
            *nRow = row + 2;                        //where its going to be after the capture move is done
            *nCol = col + 2;
           
        }
        else if(direction==LEFT) {                  //possible capture on the left
            *nRow = row + 2;                        //where its going to be after the capture move is done
            *nCol = col - 2;
        }
        //if theres an empty space after the B=>its a possible move to do
        if (board[*nRow][*nCol] == NULL)
        {
            (*capturesSoFar)++;                     //add the capture move
            copyBoard[row][col] = EMPTY_POS;        //changing current checkerPos
            copyBoard[*nRow][*nCol] = PLAYER_T;     //moving 'T' 2 cols (right or left) 2 rows down

            if (direction == RIGHT)
                copyBoard[row + 1][col + 1] = EMPTY_POS; //eaten the right B
            if (direction == LEFT)
                copyBoard[row + 1][col - 1] = EMPTY_POS; //eat the left B
        }
        else
            res = false;                            //wasnt a possible move
       
    }
    else {                                          //player==PLAYER_B

        if (direction == RIGHT) {                   //possible capture on the right
            *nRow = row - 2;                        //where its going to be after the capture move is done
            *nCol = col + 2;

        }
        else if (direction == LEFT) {               //possible capture on the lesft
            *nRow = row - 2;                        //where its going to be after the capture move is done
            *nCol = col - 2;
        }
        //if theres an empty space after the T=>its a possible move to do
        if (board[*nRow][*nCol] == NULL)
        {
            (*capturesSoFar)++;                     //adds up the captures
            copyBoard[row][col] = EMPTY_POS;        //changing current checkerPos
            copyBoard[*nRow][*nCol] = PLAYER_B;     //moving 'B' 2 cols (right or left) 2 rows up

            if (direction == RIGHT)
                copyBoard[row - 1][col + 1] = EMPTY_POS; //eaten the right T
            if (direction == LEFT)
                copyBoard[row - 1][col - 1] = EMPTY_POS; //eat the left T
        }
        else
            res = false;                            //wasnt a possible capture move
    }
    return res;                                     //returns if there was or wasnt a possible capture move
}
//this function is for one move only if there are no cature moves available
void singleMove(SingleSourceMovesTreeNode* root, char player, int direction, Board board, int row, int col, int* nRow, int* nCol, unsigned short* capturesSoFar) {

    if (player == PLAYER_T) {
        *capturesSoFar = 0;                         //set captures to 0
        if (direction == RIGHT) {
            *nRow = row + 1;                         //where its going to be after the capture move is done
            *nCol = col + 1;
        }
        if (direction == LEFT) {
            *nRow = row + 1;                         //where its going to be after the capture move is done
            *nCol = col - 1;
        }

        //update the board
        board[row][col] = EMPTY_POS;                //changing current checkerPos
        board[*nRow][*nCol] = PLAYER_T;             //moving 'T' left/right and down the board

        if (direction == RIGHT)
            root->next_move[RIGHT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);//create node for the one move
        if (direction == LEFT)
            root->next_move[LEFT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);//create node for the one move

    }
    else { //player B
        *capturesSoFar = 0;                          //set captures to 0
        if (direction == RIGHT) {
            *nRow = row - 1;                         //where its going to be after the capture move is done
            *nCol = col + 1;
        }
        if (direction == LEFT) {
            *nRow = row - 1;                         //where its going to be after the capture move is done
            *nCol = col - 1;
        }
        board[row][col] = EMPTY_POS;                //changing current checkerPos
        board[*nRow][*nCol] = PLAYER_B;             //moving 'B' left/right and up
        if (direction==RIGHT)
            root->next_move[RIGHT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);//create node for the one move
        if(direction==LEFT)
            root->next_move[LEFT] = createNewTNode(board, *nRow, *nCol, *capturesSoFar, NULL, NULL);//create node for the one move
    }
}
//This function is for dreeing the tree
void freeTree(SingleSourceMovesTree *tr)
{
    freeTreeHelper(tr->source);
}
//This function is freeing the tree nodes and then the tree root
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
