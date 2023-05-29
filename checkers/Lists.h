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
void checkAllocationMultipleList(multipleSourceMoveList* res);
SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);
void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures);
void insertListNodeToEndList(SingleSourceMovesList* list, SingleSourceMovesListCell* res);
bool isEmpty(SingleSourceMovesList* list);
SingleSourceMovesListCell* getTail(SingleSourceMovesList* lst, unsigned short captures);
SingleSourceMovesListCell* createOptimalListFromTree(SingleSourceMovesTreeNode* source, char player, unsigned short* capturesOfRoute);
void freeRoute(SingleSourceMovesListCell* route);
void makeEmptyMultipleList(multipleSourceMoveList* res);
multipleSourceMoveList* FindAllPossiblePlayerMoves(Board board, Player player);
void insertListToEndMultiplefList(multipleSourceMoveList* multipleList, multipleSourceMoveListCell* newList);
//from others
void RemoveSingleSourceMovesList(multipleSourceMoveList* list);
void makeMove(Board board, SingleSourceMovesList* move,Player player);
SingleSourceMovesList* getSingleSourceMovesListByIndex(multipleSourceMoveList* list, int index);
#endif //LIST_H