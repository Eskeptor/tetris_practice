#pragma once
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define FRAME_HEIGHT 22
#define FRAME_WIDTH 14
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32

enum {
	BLACK,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE,      /* 15 : 하양 */
};

typedef struct _tetris {
	int level;
	int gameover;
	int score;
	int rotation;
	int absX, absY;
	int curX, curY;
	int curblock;
	int nextblock;
}Tetris;
int gameboard[FRAME_HEIGHT + 2][FRAME_WIDTH + 2];

void removeCursor();
void setCursor(int x, int y);
void init(Tetris *t);
void showCurrentBlock(Tetris t);
void removeCurrentBlock(Tetris t);
void showTable(Tetris t);
void nextBlockTable(Tetris t);
void newBlock(Tetris *t);
int collisionCheck(Tetris t);
void mergeBlock(Tetris t);
int moveBlock(Tetris *t);
void gameoverCheck();
void lineCheck(Tetris t);
