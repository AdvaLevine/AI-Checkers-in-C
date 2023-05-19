#include "main.h"
#include "Trees.h"


//function gets a board and a pointer to a checker pos, and returns a tree of every possible moves if there are any
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {

    int row = (src->row) - CHAR_A; //from letter to number
    int col = (src->col) - CHAR_0; //from char number to int number
    char player = board[row][col];
    unsigned short capturesSoFar = 0;
    SingleSourceMovesTree* res;

    res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));

    //memory allocation check
    memoryAllocationCheckTree(res);

    //checker pos is empty
    if (player == EMPTY_POS)
        return NULL;

    //checkers pos isnt empty
    else {
        res->source = buildTreeHelper(board, row, col, player, capturesSoFar);//recursive function to create the tree for the checkers pos moves

    }
    return res;
}
//This function is creating the tree for one move possibilities of the checkers pos
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar)
{
    SingleSourceMovesTreeNode* root;
    Board copyBoard;//new board each rec call
    char left, right;
    int nRow, nCol; //next new col and row


    root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

    copyBorad(board, copyBoard);
    //if the player is T he's moving downwards
    if (player == PLAYER_ONE)
    {
        if (row >= BOARD_SIZE - 1) //bottom of the board, no moves to do
            return root;

        if (col < BOARD_SIZE - 1)
        {
            right = board[col + 1][row + 1];
            //copyBorad(board, copyBoard);
            if (right == PLAYER_TWO)
            {
                if (col <= MAX_COL && row <= MAX_ROW) //if still can eat
                {
                    nRow = row + 2;
                    nCol = col + 2;
                    if (board[nRow][nCol] == NULL)
                    {
                        capturesSoFar++;
                        copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                        copyBoard[row + 1][col + 1] = EMPTY_POS; //eaten
                        copyBoard[nRow][nCol] = PLAYER_ONE; //moving 'T' 2 cols right 2 rows down
                        root->next_move[RIGHT] = buildTreeHelper(copyBoard, nRow, nRow, player, capturesSoFar);
                    }
                    //else
                    //    root->next_move[RIGHT] = NULL;
                }
            }
            else if (right == EMPTY_POS && capturesSoFar == 0)
            {
                capturesSoFar = 0;
                nRow = row + 1;
                nCol = col + 1;
                copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                copyBoard[nRow][nCol] = PLAYER_ONE; //moving 'T' right and down //create Tnode?
                root->next_move[RIGHT] = createNewTNode(copyBoard, nRow, nCol, capturesSoFar, NULL, NULL);
            }
        }

        if (col > 0)
        {
            left = board[col - 1][row + 1];
            //copyBorad(board, copyBoard);

            if (left == PLAYER_TWO)
            {
                if (col >= 2 && row <= MAX_ROW) //if still can eat
                {
                    nRow = row + 2;
                    nCol = col - 2;
                    if (board[nRow][nCol] == NULL)
                    {
                        capturesSoFar++;
                        copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                        copyBoard[row+1][col + 1] = EMPTY_POS; //eaten
                        copyBoard[nRow][nCol] = PLAYER_ONE; //moving 'T' 2 cols right 2 rows down
                        root->next_move[LEFT] = buildTreeHelper(copyBoard, nRow, nRow, player, capturesSoFar);
                    }
                }

                //else

                //root->next_move[LEFT] == NULL;

            }

            else if (left == EMPTY_POS && capturesSoFar == 0)
            {
                capturesSoFar = 0;
                nRow = row + 1;
                nCol = col - 1;
                root->next_move[LEFT] = createNewTNode(board, nRow, nCol, capturesSoFar, NULL, NULL);
                copyBoard[row][col] = EMPTY_POS; //changing current checkerPos
                copyBoard[nRow][nCol] = PLAYER_ONE; //moving 'T' left and down
            }

        }

    }//player one check

    //if (right == 'T' && left == 'T')

    //    return root; //no moves to do

     //if the data is B

   /* else
    {
        if (row <= ROW_0)
            return root;
        root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

    }*/
    return root;

}
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight)
{
    SingleSourceMovesTreeNode* res;
    checkersPos* pos;

    res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));

    memoryAllocationCheckTree(res);

    pos = (checkersPos*)malloc(sizeof(checkersPos));

    if (pos == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
    pos->col = CHAR_0 + col;
    pos->row = CHAR_A + row;


    copyBorad(board, res->board);
    res->pos = pos;
    res->total_captures_so_far = captures;
    res->next_move[LEFT] = nextMoveLeft;
    res->next_move[RIGHT] = nextMoveRight;
    return res;
}

void memoryAllocationCheckTree(SingleSourceMovesTree* res) {
    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
}