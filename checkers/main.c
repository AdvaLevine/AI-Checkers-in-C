#include "main.h"
#include "Trees.h"
#include "Lists.h"

//main function
void main()
{
    Player player;
    player = 'B';
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
   
   /* Board board = { {0,0,0,'T',0,0,0,0},
                    {0,0,'B',0,'B',0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,'B',0,'B',0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0} };*/

    //checkersPos pos = { 'H',4 }; //testing

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
    //SingleSourceMovesTree* TreeOfSingleMove;

    //SingleSourceMovesList* list;
    Board board = { {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0},
                   {0,0,'T',0,0,0,0,0},
                   {0,0,0,0,0,'T',0,0},
                   {0,0,'T',0,'B',0,0,0},
                   {0,0,0,'B',0,0,0,0} };

    //TreeOfSingleMove = FindSingleSourceMoves(board, &pos);

    //list = FindSingleSourceOptimalMove(TreeOfSingleMove);
    res = FindAllPossiblePlayerMoves(board, 'B');
    //Turn(board, player);
    //free if needed
    //free treeNodes and free tree source-> free insdie treenode- checkerspos
}
