//This header is for the structs, constant, function calls of the whole program
#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS

//libraries
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//contants
#define BOARD_SIZE 8                            //the size of the checkers boaard is 8x8 (64 positions)
#define ROW_0 0                                 //first row
#define LEFT 0                                  //left index (left son in three)
#define RIGHT 1                                 //right index(right son in tree)
#define CHAR_A 'A'                              //char A for conversion to a number from a char
#define CHAR_0 0                                //char 0 for conversion to a number from a char
#define EMPTY_POS '\0'                          //empty board position
#define MAX_ROW 5                               //max row for captures
#define MAX_COL 5                               //max col for captures
#define PLAYER_T 'T'                            // game player 
#define PLAYER_B 'B'                            //game player
#define PLUS '+'                                //plus in the print of the board
#define MINUS '-'                               //minus in the print of the board
#define PLUS_MINUS_LINE_LEN 9                   //the line of the puls minus in the board print
#define BOARD_PRINTING_SIZE 19                  //the size of the printing board
#define FIRST_COL 1                             //the first col in the printing board
#define FIRST_ROW 'A'                           //the first row in the printing board

//structs
//checkers tool position on board
typedef struct _checkersPos {
    char row;
    char col;
}checkersPos;

//board 2d array
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

//player char T\B
typedef unsigned char Player;


//functions
void createBoard(Board board);
void copyBorad(Board board, Board copyBoard);
checkersPos* createPos(int row, int col);
void Turn(Board board, Player player);
bool isGameNotFinished(Board board, Player player);
void PlayGame(Board board, Player starting_player);
void printBoard(Board board);
void printMidLine();

////constant int for max captures in game
//extern int maxGameCaptures = 0;
//extern char maxcapturePlayer = EMPTY_POS;
//extern int countCapturesT = 0;
//extern int countCapturesB = 0;

#endif //MAIN_H