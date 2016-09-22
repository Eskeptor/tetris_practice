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
	BLACK,      /*  0 : ��� */
	DARK_BLUE,    /*  1 : ��ο� �Ķ� */
	DARK_GREEN,    /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
	DARK_RED,    /*  4 : ��ο� ���� */
	DARK_VOILET,  /*  5 : ��ο� ���� */
	DARK_YELLOW,  /*  6 : ��ο� ��� */
	GRAY,      /*  7 : ȸ�� */
	DARK_GRAY,    /*  8 : ��ο� ȸ�� */
	BLUE,      /*  9 : �Ķ� */
	GREEN,      /* 10 : �ʷ� */
	SKY_BLUE,    /* 11 : �ϴ� */
	RED,      /* 12 : ���� */
	VOILET,      /* 13 : ���� */
	YELLOW,      /* 14 : ��� */
	WHITE,      /* 15 : �Ͼ� */
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
