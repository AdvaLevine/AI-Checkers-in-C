#include "Trees.h"


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
