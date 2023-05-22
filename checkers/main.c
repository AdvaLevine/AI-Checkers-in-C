#include "main.h"
#include "Trees.h"

//main function
void main()
{
    Board board = { {0,0,0,'T',0,0,0,0},
                    {0,0,'B',0,'B',0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,'B',0,'B',0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0} };
    //Board board;
    SingleSourceMovesTree* res;
    //createBoard(board);
    checkersPos pos = {'A',4 }; //testing
    res = FindSingleSourceMoves(board, &pos);

    //free if needed
}
