#include "main.h"

//functions call
void createBoard(Board board); 
void copyBorad(Board board, Board copyBoard);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar);
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,
SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight);


//main function
void main()
{

    Board board;
    createBoard(board);
    checkersPos pos = { 'A',3 }; //testing

    //free if needed
}

//function to create the board
void createBoard(Board board) {

    int i,j;

    //create player T side of board
    for (i = 0; i < 3; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {

            if (i % 2 == 0) {//row is even number
                if (j % 2 != 0)
                    board[i][j] = 'T';
                else
                    board[i][j] = '\0';
            }
            else {//row is odd number
                if (j % 2 != 0)
                    board[i][j] = '\0';
                else
                    board[i][j] = 'T';
            }

        }//for2

    }//for1

    //two empty lines of the board in the middle
    for (i = 3; i < LIMIT_ROW; i++) {

        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '\0';
        }
    }

    //create player B side of board

    for (i = LIMIT_ROW; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (i % 2 == 0) {//row is even number
                if (j % 2 != 0)
                    board[i][j] = 'B';
                else
                    board[i][j] = '\0';
            }
            else {//row is odd number
                if (j % 2 != 0)
                    board[i][j] = '\0';
                else
                    board[i][j] = 'B';
            }
        }//for2
    }//for1
}


//function gets a board and a pointer to a checker pos, and returns a tree of every possible moves if there are any
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {

    int row = (src->row) - 'A'; //from letter to number
    int col = (src->col) - '0' - 1; //from char number to int number
    char player = board[row][col];
    unsigned short capturesSoFar = 0;
    SingleSourceMovesTree* res;

    res = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));

    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }

    //check if the checker pointer isnt null(empty)

    if (player == '\0')
        return NULL;

    //checkers pos isnt empty

    else {

        //creatng the tree root

        //res->source = createNewTNode(row, col, );

        res->source = buildTreeHelper(board, row, col, player, capturesSoFar);//recursive function to create the tree for the checkers pos

    }
    return res;
}

//This function is creating the tree for one move possibilities of the checkers pos
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar)
{
    SingleSourceMovesTreeNode* root;
    Board copyBoard;
    char left, right;
    int nRow, nCol; //next col and row

    //if we excced the board size we return

    root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

    copyBorad(board, copyBoard);
    //if the player is T
    if (player == 'T')
    {
        if (row >= BOARD_SIZE - 1) //bottom of board, no moves to do
            return root;

        //moving "forward" down

        if (col < BOARD_SIZE - 1)
        {
            right = board[col + 1][row + 1];
            //copyBorad(board, copyBoard);
            if (right == 'B')
            {
                if (col <= 5 && row <= 5) //if still can eat
                {
                    nRow = row + 2;
                    nCol = col + 2;
                    if (board[nRow][nCol] == NULL)
                    {
                        capturesSoFar++;
                        copyBoard[row][col] = '\0'; //changing current checkerPos
                        copyBoard[row + 1][col + 1] = '\0'; //eaten
                        copyBoard[nRow][nCol] = 'T'; //moving 'T' 2 cols right 2 rows down
                        root->next_move[RIGHT] = buildTreeHelper(copyBoard, nRow, nRow, player, capturesSoFar);
                    }
                    //else
                    //    root->next_move[RIGHT] = NULL;
                }
            }
            else if (right == '\0' && capturesSoFar == 0)
            {
                capturesSoFar = 0;
                nRow = row + 1;
                nCol = col + 1;
                copyBoard[row][col] = '\0'; //changing current checkerPos
                copyBoard[nRow][nCol] = 'T'; //moving 'T' right and down //create Tnode?
                root->next_move[RIGHT] = createNewTNode(copyBoard, nRow, nCol, capturesSoFar, NULL, NULL);
            }
        }

        if (col > 0)
        {
            left = board[col - 1][row + 1];
            //copyBorad(board, copyBoard);

            if (left == 'B')
            {
                if (col >= 2 && row <= 5) //if still can eat
                {
                    nRow = row + 2;
                    nCol = col - 2;
                    if (board[nRow][nCol] == NULL)
                    {
                        capturesSoFar++;
                        copyBoard[row][col] = '\0'; //changing current checkerPos
                        copyBoard[row + 1][col + 1] = '\0'; //eaten
                        copyBoard[nRow][nCol] = 'T'; //moving 'T' 2 cols right 2 rows down
                        root->next_move[LEFT] = buildTreeHelper(copyBoard, nRow, nRow, player, capturesSoFar);
                    }
                }

                //else

                //    root->next_move[LEFT] == NULL;

            }

            else if (left == '\0' && capturesSoFar == 0)
            {
                capturesSoFar = 0;
                nRow = row + 1;
                nCol = col - 1;
                root->next_move[LEFT] = createNewTNode(board, nRow, nCol, capturesSoFar, NULL, NULL);
                copyBoard[row][col] = '\0'; //changing current checkerPos
                copyBoard[nRow][nCol] = 'T'; //moving 'T' left and down
            }

        }

    }

    //if (right == 'T' && left == 'T')

    //    return root; //no moves to do

//if the data is B

    else 
    {
        if (row <= ROW_0)
            return root;
        root = createNewTNode(board, row, col, capturesSoFar, NULL, NULL);

    }
    return root;

}

SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,
    SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight)
{
    SingleSourceMovesTreeNode* res;
    checkersPos* pos;

    res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));

    if (res == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }

    pos = (checkersPos*)malloc(sizeof(checkersPos));

    if (pos == NULL)
    {
        printf("Error! Failed to allocate memory\n");
        exit(1);
    }
    pos->col = '0' + col;
    pos->row = 'A' + row;


    copyBorad(board, res->board);
    res->pos = pos;
    res->total_captures_so_far = captures;
    res->next_move[LEFT] = nextMoveLeft;
    res->next_move[RIGHT] = nextMoveRight;
    int a = 5;
}

void copyBorad(Board board, Board copyBoard)
{
    int i,j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            copyBoard[i][j] = board[i][j];
        }
    }
}
//int checkPlayer()