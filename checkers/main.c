#include "main.h"
#include "Trees.h"
#include "Lists.h"

//main function
void main()
{
    multipleSourceMoveList* res;
    //Board board = { {0,0,0,0,0,0,0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,'T',0,'T',0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,'T',0,'T',0,0},
    //                 {0,0,0,0,'B',0,0,0} };
    //checkersPos pos = { 'H',5 }; //testing

    //Board board = { {0,0,0,0,0,0,0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,'T',0,'T',0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,'T',0,'T',0,0},
    //                 {0,0,0,0,0,0,0,0},
    //                 {0,0,0,'T',0,'T',0,0},
    //                 {0,0,0,0,'B',0,0,0} };
    //checkersPos pos = { 'H',5 }; //testing
   
    Board board = { {0,0,0,'T',0,0,0,0},
                    {0,0,'B',0,'B',0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,'B',0,'B',0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0} };
    //checkersPos pos = { 'A',4 }; //testing

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

    SingleSourceMovesList* list;

    //TreeOfSingleMove = FindSingleSourceMoves(board, &pos);

    //list = FindSingleSourceOptimalMove(TreeOfSingleMove);
    res = FindAllPossiblePlayerMoves(board, 'B');

    //free if needed
    //free treeNodes and free tree source-> free insdie treenode- checkerspos
}
