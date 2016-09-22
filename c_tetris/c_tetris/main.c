#include "tetris.h"

#define SPEED 600

int main() {
	Tetris t, tmpT;
	char key;
	init(&t);
	while (1) {
		removeCursor();
		showTable(t);
		newBlock(&t);
		nextBlockTable(t);
		while (1) {
			//for (int i = 0; 1; i++) {
			while (kbhit()) {
				removeCursor();
				key = getch();
				switch (key) {
				case UP:
					tmpT = t;
					tmpT.rotation = (tmpT.rotation + 1) % 4;
					if (collisionCheck(tmpT) == 0) {
						removeCurrentBlock(t);
						t.rotation = tmpT.rotation;
						showCurrentBlock(t);
					}
					break;
				case DOWN:
					t.gameover = moveBlock(&t);
					showCurrentBlock(t);
					break;
				case LEFT:
					if (t.curX > 0) {
						removeCurrentBlock(t);
						t.curX--;
						if (collisionCheck(t) == 1)
							t.curX++;
						showCurrentBlock(t);
					}
					break;
				case RIGHT:
					if (t.curX < FRAME_WIDTH) {
						removeCurrentBlock(t);
						t.curX++;
						if (collisionCheck(t) == 1)
							t.curX--;
						showCurrentBlock(t);
					}
					break;
				}
				if (key == SPACEBAR) {
					while (t.gameover == 0)
						t.gameover = moveBlock(&t);
					showCurrentBlock(t);
				}

			}
			if (t.gameover == 1) {
				return 0;
			}
			while (!kbhit()) {
				showCurrentBlock(t);
				removeCursor();
				Sleep(SPEED - (t.level * 10));
				t.gameover = moveBlock(&t);
			}
		}
		init(&t);
	}
	system("pause");
	return 0;
}

//°¡¿îµ¥ 17