/*
FINAL PROJECT IN ADVANCED PROGRAMMING IN C 
- CHECKERS GAME-
Names of creators:       ID number:
Noa Halili
Adva Levine              319098133
*/
#include "main.h"
#include "Trees.h"
#include "Lists.h"


/*Checkers game!
This program is a simple version of the game "Chcekers" we all know and love,
the game is being played by the computer, it has a set of incoded rules it follows to accomplish its purpose.
In this version, we have two players- Player T and Player B,
Player T is at the top of the board, player B is at the bottom.
each player has 12 starting tools, and in each round every player gets one turn,
the board is being printed in each round with the update location of the tools on it and with the declartion on the move the player did
the goal is for a player to reach the other component's side: T needs to reach row 8, and B needs to reach row 0.
the other possibility to win is if the other player lost all its tools due to capture moves.
if the player has a move inwhich he can get a higher number of captures, then it'll proirities it.
else if its the same number of captures or there are no high captures and no equal captures-
if it's player T, it'll always choose the highest row, else the highest col
if it's player B, it'll always choose the lowest row, else the lowest col
when the game is done, the winner is declared and its number of moves, 
as well as the name of the player with the most captures and the amount of captures they did.
GOOD LUCK AND ENJOY! :)
*/
void main()
{
    Player player;
    player = PLAYER_B;
    Board board;
    createBoard(board);
    PlayGame(board, player);
}