// g++ -o rpg rpg.cpp -lncurses
#include <iostream>
#include <fstream>
#include <ncurses.h>

using namespace std;

int player[2] = {1,5};
bool run = true;
const int WORLDWIDTH = 30;
const int WORLDHEIGHT = 20;
const char GRASS = '#';

int obstacles[3][2] = { {7,9}, {3,3}, {4,4} };
int grass[6][2] = { {5,5}, {5,6}, {5,7}, {6,5}, {6,6}, {6,7} };

void drawPlayer() {
	mvaddch (player[0], player[1], '@');
}

void drawMap() {
	// Draw upper and lower borders
	for(int i = 1; i <= WORLDWIDTH-2; i++) {
		mvaddch (0, i ,'_');
		mvaddch ((WORLDHEIGHT-1), i ,'_');
	}
	// Draw left and right borders
	for(int i = 1; i <= WORLDHEIGHT-1; i++) {
		mvaddch (i, 0 ,'|');
		mvaddch (i, (WORLDWIDTH-1) ,'|');
	}
	// Draw obstacles
	for(int obst = 0; obst < sizeof(obstacles) / sizeof(obstacles[0]); obst++) {
		mvaddch(obstacles[obst][0], obstacles[obst][1], 'O');
	}
	// Draw grass
	for(int i = 0; i < sizeof(grass) / sizeof(grass[0]); i++) {
		mvaddch(grass[i][0], grass[i][1], GRASS);
	}
	mvaddstr(1, (WORLDWIDTH+2), "Moving");
}

bool checkCollision(int xChange, int yChange) {
	for(int obst = 0; obst < sizeof(obstacles) / sizeof(obstacles[0]); obst++) {
		if(player[0] + xChange == obstacles[obst][0] && player[1] + yChange == obstacles[obst][1]) {
			return true;
		}
	}
	if(	   player[1] + yChange == WORLDWIDTH-1
		|| player[1] + yChange == 0
		|| player[0] + xChange == 0
		|| player[0] + xChange == WORLDHEIGHT) {
		return true;
	}
	return false;
}

void exitGame ()
{
	clear ();
	refresh ();
	endwin ();
}

void gameInput ()
{
	int input; // The input variable MUST be int to accept non-ascii characters

	input = getch ();

	switch (input)
	{
		case ERR:
			break;

		case KEY_UP:	case 'w':	case 'W':
			if(checkCollision(-1, 0) == false) {
				player[0]--;
			}
			break;

		case KEY_LEFT:	case 'a':	case 'A':
			if(checkCollision(0, -1) == false) {
				player[1]--;
			}
			break;

		case KEY_DOWN:	case 's':	case 'S':
			if(checkCollision(1, 0) == false) {
				player[0]++;
			}
			break;

		case KEY_RIGHT:	case 'd':	case 'D':
			if(checkCollision(0, 1) == false) {
				player[1]++;
			}
			break;

		case 'x':
			run = false;
			break;

		default:
			break;
	}
}

void drawScreen() {
	clear();
	drawMap();
	drawPlayer();
}

int main() {
	string dir;

	initscr();
	curs_set (0); // Makes the cursor disappear
	drawScreen();

	while(run == true) {
		gameInput();
		drawScreen();
		refresh();
	}
	endwin();
	return 0;
}
