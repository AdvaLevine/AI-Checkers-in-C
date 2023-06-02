#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS

//libraries
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "Lists.h"

//contants
#define BOARD_SIZE 8
#define ROW_0 0
#define LEFT 0
#define RIGHT 1
#define CHAR_A 'A'
#define CHAR_0 0
#define EMPTY_POS '\0'
#define CAPTURE_MOVE 2
#define MAX_ROW 5
#define MAX_COL 5
#define PLAYER_T 'T'
#define PLAYER_B 'B'
#define MAX_CAPTURES_FOR_SINGLE_MOVE 4
#define PLUS '+'
#define MINUS '-'
#define PLUS_MINUS_LINE_LEN 9
#define BOARD_PRINTING_SIZE 19
#define FIRST_COL 1
#define FIRST_ROW 'A'




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