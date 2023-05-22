#ifndef TREE_H
#define TREE_H
#include "main.h"

//struct for the game tool tree nodes
typedef struct _SingleSourceMovesTreeNode {
    Board board;
    checkersPos* pos;
    unsigned short total_captures_so_far;
    struct _SingleSourceMovesTreeNode* next_move[2];
}SingleSourceMovesTreeNode;

//struct for the game tool tree
typedef struct _SingleSourceMovesTree {
    SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

//functions 
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
void memoryAllocationCheckTreeNode(SingleSourceMovesTreeNode* res);
void memoryAllocationCheckTree(SingleSourceMovesTree* res);
SingleSourceMovesTreeNode* buildTreeHelper(Board board, int row, int col, char player, unsigned short capturesSoFar);
SingleSourceMovesTreeNode* createNewTNode(Board board, int row, int col, unsigned short captures,
    SingleSourceMovesTreeNode* nextMoveLeft, SingleSourceMovesTreeNode* nextMoveRight);
void captureMove(char player, int direction, Board board, int row, int col, int* nRow, int* nCol, unsigned short* capturesSoFar, Board copyBoard);
#endif //TREE_H
