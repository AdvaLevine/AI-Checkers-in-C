#ifndef LIST_H
#define LIST_H
//#include "Trees.h"
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

#endif //LIST_H