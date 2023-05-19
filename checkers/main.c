#include "main.h"
#include "Trees.h"

////functions call
//void createBoard(Board board); 
//void copyBorad(Board board, Board copyBoard);
//SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
//SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar);
//SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,
//SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight);


//main function
void main()
{
    Board board;
    createBoard(board);
    checkersPos pos = { 'A',3 }; //testing

    //free if needed
}




//int checkPlayer()