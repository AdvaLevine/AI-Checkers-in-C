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

//function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
void makeEmptyList(SingleSourceMovesList* res);
void checkAllocationList(SingleSourceMovesList* res);
void checkAllocationListNode(SingleSourceMovesListCell* res);
void FindMaxRoute(SingleSourceMovesTreeNode* source, char player, unsigned short* capturesOfRoute,
	int arr[],int size, int level);
SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);
void insertListNodeToEndList(SingleSourceMovesList* list, SingleSourceMovesListCell* res);
bool isEmpty(SingleSourceMovesList* list);

#endif //LIST_H