#include "Lists.h"
#include "Trees.h"



//This function gets a tree of one pos and creates an optimal move list
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {

	SingleSourceMovesList* res;									// the list
	unsigned short capturesOfRoute=0;							// saving the max route
	int row = (moves_tree->source->pos->row) - CHAR_A;			//convert from letter to number
	int col = (moves_tree->source->pos->col) - CHAR_0 - 1;		//convert from char number to int number
	char player = (moves_tree->source->board)[row][col];		//save the players char
	//allocate the list
	res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkAllocationList(res);									//check if allocation was successful
	makeEmptyList(res);											//put NULL in list

	//get the optimal list
	res->head = createOptimalListFromTree(moves_tree->source, player, &capturesOfRoute);
	res->tail = getTail(res, capturesOfRoute);					//update the tail

	freeTree(moves_tree);										//free the tree
	return res;													//return the list
}
//This function is creating the optimal list according to the rules of the game
SingleSourceMovesListCell* createOptimalListFromTree(SingleSourceMovesTreeNode* source, char player, unsigned short* capturesOfRoute)
{
	unsigned short captureRouteLeft, captureRouteRight;			//number of captures from left and right
	SingleSourceMovesListCell* root;							//the list head
	SingleSourceMovesListCell* leftListNode;					//the left list
	SingleSourceMovesListCell* rightListNode;					//the right list

	if (source == NULL) {										//if empty tree return
		*capturesOfRoute = 0;
		return NULL;
	}

	root = createNewListCell(source->pos, source->total_captures_so_far, NULL);		//create a new list node
	
	if ((source->next_move[LEFT] == NULL) && (source->next_move[RIGHT] == NULL)) {	//if its a leaf, we return the capture move in it
		*capturesOfRoute = source->total_captures_so_far;
		return root;
	}
	//recursive calls for lest and right lists
	leftListNode = createOptimalListFromTree(source->next_move[LEFT], player, &captureRouteLeft);
	rightListNode = createOptimalListFromTree(source->next_move[RIGHT], player, &captureRouteRight);

	if (captureRouteRight == captureRouteLeft) {//same number of captures
		//rule in page 2
		if (player == PLAYER_T) {
			if (rightListNode != NULL) {		//prioritizing right(higher col)
				root->next = rightListNode;
					freeRoute(leftListNode);	 //free the left route
			}
			else
				root->next=leftListNode;
		}
		else {//player is B
			if (leftListNode != NULL) {			//prioritizing left(lower col)
				root->next = leftListNode;
				freeRoute(rightListNode);		//free the right route
			}
			else
				root->next = rightListNode;
		}
		*capturesOfRoute = captureRouteRight;	//return the max number of capture(they are equal)
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
	return root;					//return list node
}
//This function is for updating the optimal move list tail
SingleSourceMovesListCell* getTail(SingleSourceMovesList* lst, unsigned short captures)
{
	SingleSourceMovesListCell* curr;			//curr to move on the list
	curr = lst->head;							//we return the head if there are no moves to do

	if (captures == 0&& curr->next!=NULL) {		//one move to do
		curr = lst->head->next;
	}
	//there are capture moves
	while (curr !=NULL && captures>0)
	{
		curr = curr->next;
		captures--;
	}
	return curr;								//return the tail
}
//This function is for creating a list of lists for each player in every single move they have
multipleSourceMoveList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	multipleSourceMoveList* res;					//the list of lists
	multipleSourceMoveListCell* tmpListCell;		//tmp cell
	SingleSourceMovesTree* tmpTree;					//the single move tree
	checkersPos* tmpPos;							//the position on board
	int i, j;
	//allocation for the list
	res = (multipleSourceMoveList*)malloc(sizeof(multipleSourceMoveList));
	checkAllocationMultipleList(res);													//check if allocated
	makeEmptyMultipleList(res);															//make empty list
	//going through the board and looking for the players on board so we create the list of lists for the player
	for (i = 0; i < BOARD_SIZE; i++)													//board rows
	{
		for (j = 0; j < BOARD_SIZE; j++)												//board cols
		{
			if (board[i][j] == player)													//if we found a player on the board
			{
				tmpPos = createPos(i, j);												//create the pos
				tmpTree = FindSingleSourceMoves(board, tmpPos);							//create the tree for the pos
				tmpListCell = (multipleSourceMoveListCell*)malloc(sizeof(multipleSourceMoveListCell));//allocating tmplist
				checkAllocationListNode(tmpListCell);									//check if allocated
				tmpListCell->single_source_moves_list =FindSingleSourceOptimalMove(tmpTree); //find the best route of captures from given position
				insertListToEndMultiplefList(res, tmpListCell);							//insert the route to the list
			}
		}
	}
	return res;																			//return the list of lists
}
//This function is for inserting the multiple list node to the end of the list of lists
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
//This function is for creating a pos 
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
//This function is for inserting data to the end of a single source list
void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures) {
	SingleSourceMovesListCell* newTail;
	newTail = createNewListCell(pos,captures, NULL);
	insertListNodeToEndList(lst, newTail);
}
//This function is for putting NULL in the head and tail for the multi list
void makeEmptyMultipleList(multipleSourceMoveList* res) {
	res->head = res->tail = NULL;
}
//This function is for putting NULL in the head and tail for the single list
void makeEmptyList(SingleSourceMovesList* res) {
	res->head = res->tail = NULL;
}
//This function is for checking allocation of a single source list
void checkAllocationList(SingleSourceMovesList* res) {
	if (res == NULL)
	{
		printf("Error! Failed to allocate memory\n");
		exit(1);
	}
}
//This function is for checking allocation of a multi list

void checkAllocationMultipleList(multipleSourceMoveList* res) {
	if (res == NULL)
	{
		printf("Error! Failed to allocate memory\n");
		exit(1);
	}
}
//This function is for checking allocation of a single source list cell
void checkAllocationListNode(SingleSourceMovesListCell* res) {
	if (res == NULL)
	{
		printf("Error! Failed to allocate memory\n");
		exit(1);
	}
}
//This function is for creating a new list cell
SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next) {
	SingleSourceMovesListCell* res;
	res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkAllocationListNode(res);
	
	res->position = pos;
	res->captures = captures;
	res->next = next;
	return res;
}
//This function is for inserting the list cell into the single source list
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
//This function is checking if the list is empty
bool isEmpty(SingleSourceMovesList* list) {
	if (list->head == NULL)
		return true;
	else
		return false;
}
//This function is freeing the lists
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
