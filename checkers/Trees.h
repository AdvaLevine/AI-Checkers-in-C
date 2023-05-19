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

#endif //TREE_H
