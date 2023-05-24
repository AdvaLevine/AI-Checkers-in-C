#ifndef LIST_H
#define LIST_H
#include "Trees.h"
#include "main.h"

typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMovesList;

typedef struct _multipleSourceMoveListCell {
	SingleSourceMovesList* single_source_moves_lists;
	struct _multipleSourceMoveListCell* next;
}multipleSourceMoveListCell;

typedef struct _multipleSourceMoveList {
	multipleSourceMoveListCell* head;
	multipleSourceMoveListCell* tail;
}multipleSourceMoveList;

//function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
void makeEmptyList(SingleSourceMovesList* res);
void checkAllocationList(SingleSourceMovesList* res);
void checkAllocationListNode(SingleSourceMovesListCell* res);
SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);
void insertListNodeToEndList(SingleSourceMovesList* list, SingleSourceMovesListCell* res);
bool isEmpty(SingleSourceMovesList* list);
SingleSourceMovesListCell* getTail(SingleSourceMovesList* lst, unsigned short captures);
SingleSourceMovesListCell* createOptimalListFromTree(SingleSourceMovesTreeNode* source, char player, unsigned short* capturesOfRoute);
void freeRoute(SingleSourceMovesListCell* route);
void makeEmptyMultipleList(multipleSourceMoveList* res);
multipleSourceMoveList* FindAllPossiblePlayerMoves(Board board, Player player);
#endif //LIST_H