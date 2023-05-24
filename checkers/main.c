#include "main.h"
#include "Trees.h"
#include "Lists.h"

//main function
void main()
{
 
   /* Board board = { {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,'T',0,'T',0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,'T',0,'T',0,0},
                     {0,0,0,0,'B',0,0,0} };*/
   
    Board board = { {0,0,0,'T',0,0,0,0},
                    {0,0,'B',0,'B',0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,'B',0,'B',0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0} };

    /*Board board = { {0,0,0,'T',0,0,0,0},
                    {0,0,'B',0,'B',0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,'B',0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0} };*/
    //Board board;
    //createBoard(board);
    SingleSourceMovesTree* TreeOfSingleMove;
    checkersPos pos = {'A',4 }; //testing
    SingleSourceMovesList* list;

    TreeOfSingleMove = FindSingleSourceMoves(board, &pos);

    list = FindSingleSourceOptimalMove(TreeOfSingleMove);


    //free if needed
    //free treeNodes and free tree source-> free insdie treenode- checkerspos
}
