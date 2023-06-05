#include "main.h"
#include "Trees.h"
#include "Lists.h"


//main function
void main()
{
    Player player;
    player = 'B';
    Board board;
    createBoard(board);
    PlayGame(board, player);
    //Board board = { {0,'T',0,'T',0,'T',0,'T'},
    //               {'T',0,'T',0,0,0,'T',0},
    //               {0,'B',0,0,0,0,0,0},
    //               {0,0,0,0,'B',0,0,0},
    //               {0,0,0,0,0,0,0,'B'},
    //               {0,0,0,0,'T',0,0,0},
    //               {0,'B',0,0,0,0,0,'B'},
    //               {'B',0,'B',0,'B',0,'B',0} };

    //PlayGame(board, player);
    //Turn(board, PLAYER_T);
    //free if needed
    //free treeNodes and free tree source-> free insdie treenode- checkerspos
}
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

   /* Board board = { {0,0,0,'T',0,0,0,0},
                    {0,0,'B',0,'B',0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,'B',0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0} };*/