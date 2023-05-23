#include "Lists.h"
#include "Trees.h"




SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {

	SingleSourceMovesList* res;
	unsigned short capturesOfRoute=0;// saving the max route
	int row = (moves_tree->source->pos->row) - CHAR_A; //from letter to number
	int col = (moves_tree->source->pos->col) - CHAR_0 - 1; //from char number to int number
	char player = (moves_tree->source->board)[row][col];
	int level = 0;
	int arr[MAX_CAPTURES_FOR_SINGLE_MOVE];//maybe initilize

	res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAllocationList(res);
	/*makeEmptyList(&res);*/
	FindMaxRoute(moves_tree->source,player,&capturesOfRoute,arr, level);



	return res;
}
void FindMaxRoute(SingleSourceMovesTreeNode* source, char player,unsigned short* capturesOfRoute,
	int* arr ,int level) {
	unsigned short captureRouteLeft, captureRouteRight;

	if (source == NULL) {//if empty tree return
		*capturesOfRoute = 0;
		return;
	}
	//if its a leaf, we return the capture move in it
	else if ((source->next_move[LEFT] == NULL) && (source->next_move[RIGHT] == NULL)) {
		*capturesOfRoute = source->total_captures_so_far;
	}

	FindMaxRoute(source->next_move[LEFT], player,&captureRouteLeft,arr, level+1);
	FindMaxRoute(source->next_move[RIGHT], player,&captureRouteRight, arr, level+1);
	
	if (captureRouteRight == captureRouteLeft) {//same number of captures
		//rule in page 2
		if (player == PLAYER_T) {
			*capturesOfRoute = captureRouteRight;
			arr[level] = RIGHT;
		}
		else {//player is B
			*capturesOfRoute = captureRouteLeft;
			arr[level] = LEFT;
		}
	}
	//if the captures on the right are more than on left
	else if (captureRouteRight > captureRouteLeft) {
		*capturesOfRoute = captureRouteRight;
		arr[level] = RIGHT;
	}
	else {//if the captures on the left are more than on right
		*capturesOfRoute = captureRouteLeft;
		arr[level] = LEFT;
	}

}
//insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures) {
//	SingleSourceMovesListCell* newTail;
//	newTail = createNewListCell(pos,captures, NULL);
//	insertListNodeToEndList(lst, newTail);
//}
void makeEmptyList(SingleSourceMovesList* res) {
	res->head = res->tail = NULL;
}
void checkAllocationList(SingleSourceMovesList* res) {
	if (res == NULL)
	{
		printf("Error! Failed to allocate memory\n");
		exit(1);
	}
}
void checkAllocationListNode(SingleSourceMovesListCell* res) {
	if (res == NULL)
	{
		printf("Error! Failed to allocate memory\n");
		exit(1);
	}
}
SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next) {
	SingleSourceMovesListCell* res;
	res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAllocationListNode(res);
	
	res->position = pos;
	res->captures = captures;
	res->next = next;
	return res;
}