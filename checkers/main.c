#include "main.h"
#include "Trees.h"

//main function
void main()
{
   Board board = { {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,'T',0,'T',0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,'T',0,'T',0,0,0},
                    {0,0,0,'B',0,0,0,0} };
    //Board board;
    //createBoard(board);
    SingleSourceMovesTree* res;
    checkersPos pos = {'H',4 }; //testing
    res = FindSingleSourceMoves(board, &pos);

    //free if needed
}
