#include <clocale>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>
#include "car.h"
#include "screen.h"
#include <fstream>
using namespace std;



void reset_terminal_mode()
{
	struct termios orig_termios;
	tcsetattr(0, TCSANOW, &orig_termios);
}

/* input car p, output nothing */
/* display the player's point P on the screen */
void screen::showcar_p(car p)
{
	gotoxy(p.x, p.y);
	printf("P");
	fflush(stdout);
}

/* input car t, output nothing */ 
/* display the player's point T on the screen */
void screen::showcar_t(car t){
	gotoxy(t.x,t.y);
	printf("T");
	fflush(stdout);
}

/* input car bumper and int i, output nothing */
/* to save the game progress(the positions for p and t) in "Temp.txt" */
void screen::saveGame(car bumper, int i)
{				
	/* i=1: clear file before write */
	/* i=0: append content to file */
	if (i) {
		fstream MyFile;
		MyFile.open("Temp.txt", ios::out);
		MyFile << bumper.x;
		MyFile << endl;
		MyFile << bumper.y;
		MyFile << endl;
		MyFile.close();
	} else {
		fstream MyFile;
		MyFile.open("Temp.txt", ios::app);
		MyFile << bumper.x;
		MyFile << endl;
		MyFile << bumper.y;
		MyFile << endl;
		MyFile.close();
	}
}

/* input the x,y coordinates, no output */
/* to place the cursor at column x and row y of the terminal */
void screen::gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}

/* no input, no output */
/* to clear the screen after each time of game */
void screen::clrscr(void)
{

	printf("\033[8;40;120t");
	fflush(stdout);
	system("clear");

}

/* no input, no output */
/* to show the game's guideline on the terminal */
void screen::showRule()
{
	this->gotoxy(83, 3);
	printf("Game Rules:");
	this->gotoxy(83, 4);
	printf("Bump the target out of the arena by setting the bumping direction and primary speed");
	this->gotoxy(83, 5);
	printf("Two points in the arena, \"P\" is controlled by you, \"T\" is the target");
	this->gotoxy(83, 6);
	printf("Set the direction by inputting \"+ number\" or \"- number\", the number can be from 0 to 180 inclusive (but -0 and -180 are not supported)");
	this->gotoxy(83, 7);
	printf("\"+\" means rotate counterclockwise, \"-\" means rotate clockwise");
	this->gotoxy(83, 8);
	printf("Set the primary speed by \"a number\", the number can be any integer from 1 to 15(inclusive)");
	this->gotoxy(83, 9);
	printf("Only the case T is bumped out of the arena and P remains in the arena will be regarded as WIN");
	this->gotoxy(83, 10);
	printf("Three rounds of game in total, WIN for at least 2 rounds is regarded success");
	this->gotoxy(83, 11);
	printf("Useful Commands:");
	this->gotoxy(83, 12);
	printf("\"Save\": save the file containing the current game status");
	this->gotoxy(83, 13);
	printf("\"Log\": restore a saved game, return to the saved status");
	this->gotoxy(83, 14);
	printf("\"Quit\": end the game");
	this->gotoxy(83, 15);
	printf("\"New\": start a new round");
	
}

/* no input, no output */

void screen::set_conio_terminal_mode()
{
	struct termios new_termios;

	/* take two copies - one for now, one for later */
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));

	/* register cleanup handler, and set the new terminal mode */
	atexit(reset_terminal_mode());
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}

void screen::trackRtoL(int i)
{
	switch (i) {
	case 0:
		wcout << ' ';
		break;
	case 1:
		wcout << L'\u2591';
		break;
	case 2:
		wcout << L'\u2592';
		break;
	case 3:
		wcout << L'\u2593';
		break;
	}
}

void screen::plot(double f, int w, int t)
{
	int x_tick = t - 1;
	int x, y, i = 0;
	for (; x_tick < Columns && x_tick < t + 3; ++x_tick) {
		x = x_tick;
		y = f * x_tick + w;
		gotoxy(x, y);
		trackRtoL(i);
		i++;
	}
	fflush(stdout);
}


int screen::kbhit()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int screen::getch()
{
	int r;
	unsigned char c;
	if ((r = read(0, &c, sizeof(c))) < 0) {
		return r;
	} else {
		return c;
	}
}

void screen::arena()
{

	gotoxy(1, 1);
	for (int i = 0; i < Columns; i++) {
		cout << "-";
	}
	for (int j = 0; j < row; j++) {
		gotoxy(1, j);
		cout << "|";
		gotoxy(Columns, j);
		cout << "|";
	}
	gotoxy(1, row);
	for (int i = 0; i < Columns; i++) {
		cout << "-";
	}
	fflush(stdout);		//output immediately

}

int screen::gcd(int a, int b)
{
	// Everything divides 0 
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	// base case
	if (a == b)
		return a;

	// a is greater
	if (a > b)
		return gcd(a - b, b);
	return gcd(a, b - a);
}

screen::screen()
{
	set_conio_terminal_mode();
	setlocale(LC_ALL, "");
	clrscr();
	arena();
}
