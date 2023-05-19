#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS

//libraries
#include<stdio.h>
#include <stdlib.h>
#include "Trees.h"
//contants
#define BOARD_SIZE 8
#define ROW_0 0
#define LEFT 0
#define RIGHT 1
#define CHAR_A 'A'
#define CHAR_0 0
#define EMPTY_POS '\0'
#define CAPTURE_MOVE 2
#define LIMIT_ROW 5
#define LIMIT_COL 5
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

#endif //MAIN_H