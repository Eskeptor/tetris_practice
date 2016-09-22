#include "tetris.h"


int blocks[7][4][4][4] = {
	// ㄴ
	0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,	0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,	0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,	0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,
	// ㄴ반대
	0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,	0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,	0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,	0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,
	// ㅁ
	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,	0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
	// ㅡ
	0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,	0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,	0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
	// ㅗ
	0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,	0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,	0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,	0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,
	// ㄱㄴ
	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
	// ㄱㄴ반대
	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,	0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,	0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,	0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0
};

void removeCursor() {
	CONSOLE_CURSOR_INFO curinfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
	curinfo.bVisible = 0;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void setCursor(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void init(Tetris *t) {
	t->absX = 5; //16
	t->absY = 1; //3
	t->gameover = 0;
	t->level = 1;
	t->score = 0;
	t->curblock = -1;
	t->nextblock = -1;
	t->curX = 5;
	t->curY = -3;
	t->rotation = 0;
	srand((unsigned)time(NULL));
	for (int y = 0; y < FRAME_HEIGHT; y++) {
		for (int x = 0; x < FRAME_WIDTH; x++) {
			if ((x == 0) || (x == FRAME_WIDTH - 1))
				gameboard[y][x] = 1;
			else if (y == FRAME_HEIGHT - 1)
				gameboard[y][x] = 1;
			else
				gameboard[y][x] = 0;
		}
	}
}

void showCurrentBlock(Tetris t)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((j + t.curY) < 0)
				continue;
			if (blocks[t.curblock][t.rotation][j][i] == 1)
			{
				setCursor((i + t.curX) * 2 + t.absX, j + t.curY + t.absY);
				printf("■");
			}
		}
	}
	setCursor(77, 23);
}

void removeCurrentBlock(Tetris t)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (blocks[t.curblock][t.rotation][j][i] == 1)
			{
				setCursor((i + t.curX) * 2 + t.absX, j + t.curY + t.absY);
				printf("  ");
			}
}

void showTable(Tetris t)
{
	for (int y = 0; y < FRAME_HEIGHT; y++)
	{
		for (int x = 0; x < FRAME_WIDTH; x++)
		{
			setCursor((x * 2) + t.absX, y + t.absY);
			if (gameboard[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}
	setCursor(77, 23);
}

void newBlock(Tetris *t)
{
	int rot = rand() % 7;
	if (t->curblock == -1) {
		t->curblock = rot;
		rot = rand() % 7;
		t->nextblock = rot;
	}
	else
		t->nextblock = rot;
	nextBlockTable(*t);
}

void nextBlockTable(Tetris t)
{
	Tetris tmp = t;
	tmp.rotation = 0;
	tmp.curX = 14;
	tmp.curY = 1;
	tmp.curblock = tmp.nextblock;
	for (int i = 0; i < 6; i++)
	{
		setCursor(31, i + 1);
		for (int j = 0; j < 6; j++)
		{
			if (i == 0 || i == 5 || j == 0 || j == 5)
				printf("■");
			else
				printf("  ");
		}
	}
	showCurrentBlock(tmp);
}

int collisionCheck(Tetris t)
{
	int dat = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (((t.curX + j) == 0) || ((t.curX + j) == FRAME_WIDTH - 1))
				dat = 1;
			else
				dat = gameboard[t.curY + i][t.curX + j];
			if ((blocks[t.curblock][t.rotation][i][j] == 1) && (dat == 1))
				return 1;
		}
	}
	return 0;
}

void mergeBlock(Tetris t)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gameboard[t.curY + i][t.curX + j] |= blocks[t.curblock][t.rotation][i][j];
		}
	}
	lineCheck(t);
	showTable(t);
}

int moveBlock(Tetris *t)
{
	removeCurrentBlock(*t);

	t->curY++;	//블럭을 한칸 아래로 내림
	if (collisionCheck(*t) == 1)
	{
		if (t->curY <= 0)
			return 1;
		t->curY--;
		mergeBlock(*t);
		t->curblock = t->nextblock;
		newBlock(t);
		t->curX = 5;
		t->curY = -3;
		t->rotation = 0;
		nextBlockTable(*t);
		return 2;
	}
	return 0;
}

void lineCheck(Tetris t)
{
	int i, j, k;
	for (i = 0; i < FRAME_HEIGHT - 1; i++)
	{
		for (j = 1; j < FRAME_WIDTH - 1; j++)
		{
			if (gameboard[i][j] == 0)
				break;
		}
		if (j == FRAME_WIDTH - 1)	//한줄이 다 채워졌음
		{
			showTable(t);
			setCursor(1 * 2 + t.absX, i + t.absY);
			for (j = 1; j < FRAME_WIDTH - 1; j++)
			{
				printf("□");
				Sleep(10);
			}
			setCursor(1 * 2 + t.absX, i + t.absY);
			for (j = 1; j < FRAME_WIDTH - 1; j++)
			{
				printf("  ");
				Sleep(10);
			}
			for (k = i; k > 0; k--)
			{
				for (j = 1; j < FRAME_WIDTH - 1; j++)
					gameboard[k][j] = gameboard[k - 1][j];
			}
			for (j = 1; j < FRAME_WIDTH - 1; j++)
				gameboard[0][j] = 0;
			t.score += 100 + (t.level * 10) + (rand() % 10);
		}
	}
}
