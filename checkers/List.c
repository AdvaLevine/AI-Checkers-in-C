#include "Lists.h"
#include "Trees.h"




SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {

	SingleSourceMovesList* res;
	unsigned short capturesOfRoute=0;// saving the max route
	int row = (moves_tree->source->pos->row) - CHAR_A; //from letter to number
	int col = (moves_tree->source->pos->col) - CHAR_0 - 1; //from char number to int number
	char player = (moves_tree->source->board)[row][col];
	//int level = 0;
	//int arr[MAX_CAPTURES_FOR_SINGLE_MOVE] = { 0 };//maybe initilize
	//int colsArr[MAX_CAPTURES_FOR_SINGLE_MOVE] = { 0 };
	res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAllocationList(res);
	/*makeEmptyList(&res);*/
	
	res->head = createOptimalListFromTree(moves_tree->source, player, &capturesOfRoute);
	res->tail = getTail(res, capturesOfRoute);

	//maxRouteList(res,capturesOfRoute,arr)
	

	return res;
}

SingleSourceMovesListCell* createOptimalListFromTree(SingleSourceMovesTreeNode* source, char player, unsigned short* capturesOfRoute)
{
	unsigned short captureRouteLeft, captureRouteRight;
	SingleSourceMovesListCell* root; //change to node
	SingleSourceMovesListCell* leftListNode;
	SingleSourceMovesListCell* rightListNode;
	if (source == NULL) {//if empty tree return
		*capturesOfRoute = 0;
		return NULL;
	}
	root = createNewListCell(source->pos, source->total_captures_so_far, NULL);
	//if its a leaf, we return the capture move in it
	if ((source->next_move[LEFT] == NULL) && (source->next_move[RIGHT] == NULL)) {
		*capturesOfRoute = source->total_captures_so_far;
		return root;
	}
	
	leftListNode = createOptimalListFromTree(source->next_move[LEFT], player, &captureRouteLeft);
	rightListNode = createOptimalListFromTree(source->next_move[RIGHT], player, &captureRouteRight);

	if (captureRouteRight == captureRouteLeft) {//same number of captures
		//rule in page 2
		if (player == PLAYER_T) {
			root->next = rightListNode;
			freeRoute(leftListNode); //free the left route
		}
		else {//player is B
			root->next = leftListNode;
			freeRoute(rightListNode); //free the right route
		}
		*capturesOfRoute = captureRouteRight;//return the max number of capture(they are equal)
	}
	//if the captures on the right are more than on left
	else if (captureRouteRight > captureRouteLeft) {
		root->next = rightListNode;
		*capturesOfRoute = captureRouteRight;
		freeRoute(leftListNode); //free the left route

	}
	else {//if the captures on the left are more than on right
		root->next = leftListNode;
		*capturesOfRoute = captureRouteLeft;
		freeRoute(rightListNode); //free the left route

	}
	return root;
}

SingleSourceMovesListCell* getTail(SingleSourceMovesList* lst, unsigned short captures)
{
	SingleSourceMovesListCell* curr;
	curr = lst->head;
	while (curr !=NULL && captures>0)
	{
		curr = curr->next;
		captures--;
	}
	return curr;
}



multipleSourceMoveList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	multipleSourceMoveList* res;
	multipleSourceMoveListCell* tmpListCell;
	SingleSourceMovesTree* tmpTree;
	checkersPos* tmpPos;
	//SingleSourceMovesList* tmpList;
	int i, j;
	res = (multipleSourceMoveList*)malloc(sizeof(multipleSourceMoveList));
	checkAllocationMultipleList(res);
	makeEmptyMultipleList(res);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				tmpPos = createPos(i, j);
				tmpTree = FindSingleSourceMoves(board, tmpPos);
				tmpListCell = (multipleSourceMoveListCell*)malloc(sizeof(multipleSourceMoveListCell));
				checkAllocationListNode(tmpListCell);
				tmpListCell->single_source_moves_lists =FindSingleSourceOptimalMove(tmpTree);
				insertListToEndMultiplefList(res, tmpListCell);
			}
		}
	}
	return res;
}
//void FindMaxRoute(SingleSourceMovesTreeNode* source, char player,unsigned short* capturesOfRoute) {
//	unsigned short captureRouteLeft, captureRouteRight;
//
//	if (source == NULL) {//if empty tree return
//		*capturesOfRoute = 0;
//		return;
//	}
	//if its a leaf, we return the capture move in it
	//else if ((source->next_move[LEFT] == NULL) && (source->next_move[RIGHT] == NULL)) {
	//	*capturesOfRoute = source->total_captures_so_far;
	//	return;
	//}
//	//create list node
//	//adding the col to compare later to get the best route
//	//colsArr[level] = (source->pos->col)-CHAR_0;
//
//	FindMaxRoute(source->next_move[LEFT], player,&captureRouteLeft);
//	FindMaxRoute(source->next_move[RIGHT], player,&captureRouteRight);
//	
	//if (captureRouteRight == captureRouteLeft) {//same number of captures
	//	//rule in page 2
	//	if (player == PLAYER_T) {
	//	
	//	}
	//	else {//player is B
	//		
	//	}
	//	*capturesOfRoute = captureRouteRight;//return the max number of capture(they are equal)
	//}
	//if the captures on the right are more than on left
	//else if (captureRouteRight > captureRouteLeft) {
void insertListToEndMultiplefList(multipleSourceMoveList* multipleList, multipleSourceMoveListCell* newList)
{
	if (multipleList->head == NULL)
		multipleList->head = multipleList->tail = newList;

	else
	{
		multipleList->tail->next = newList;
		multipleList->tail = newList;
	}

	newList->next = NULL;
}
	//	*capturesOfRoute = captureRouteRight;
	//
	//}
	//else {//if the captures on the left are more than on right
	//	*capturesOfRoute = captureRouteLeft;
	//	
	//}
//
//}
checkersPos* createPos(int row, int col)
{
	checkersPos* pos;
	pos = (checkersPos*)malloc(sizeof(checkersPos));
	if (pos == NULL)
	{
		printf("Error! Failed to allocate memory\n");
		exit(1);
	}
	pos->col = CHAR_0 + col + 1;
	pos->row = CHAR_A + row;
	return pos;
}

void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures) {
	SingleSourceMovesListCell* newTail;
	newTail = createNewListCell(pos,captures, NULL);
	insertListNodeToEndList(lst, newTail);
}

void makeEmptyMultipleList(multipleSourceMoveList* res) {
	res->head = res->tail = NULL;
}
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
void checkAllocationMultipleList(multipleSourceMoveList* res) {
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

void insertListNodeToEndList(SingleSourceMovesList* list, SingleSourceMovesListCell* res) {
	if (isEmpty(list) == true) {
		list->head = list->tail = res;
	}
	else {
		list->tail->next = res;
		list->tail = res;
	}
	res->next = NULL;
}

bool isEmpty(SingleSourceMovesList* list) {
	if (list->head == NULL)
		return true;
	else
		return false;
}

void freeRoute(SingleSourceMovesListCell* route)
{
	SingleSourceMovesListCell* curr, * next;
	curr = route; 
	next = NULL;
	while (curr!=NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}
