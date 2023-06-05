//This header is for the structs and function calls in List.c
#ifndef LIST_H
#define LIST_H
#include "Trees.h"
#include "main.h"

//struct for a single move list node
typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

//struct for a single move list
typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMovesList;

//struct for a multi moves list cell
typedef struct _multipleSourceMoveListCell {
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMoveListCell* next;
}multipleSourceMoveListCell;

//struct for a multi moves list
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
//from others.c
void RemoveSingleSourceMovesList(multipleSourceMoveList* list);
void makeMove(Board board, SingleSourceMovesList* move,Player player);
#endif //LIST_H