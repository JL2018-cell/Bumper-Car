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

/* input the x,y coordinates, no output */
/* to place the cursor at column x and row y of the terminal */
void screen::gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
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
/* display the target point T on the screen */
void screen::showcar_t(car t){
	gotoxy(t.x,t.y);
	printf("T");
	fflush(stdout);
}


/* no input, no output */
/* to clear the screen after each time of game */
void screen::clrscr()
{
	printf("\033[8;40;120t");
	fflush(stdout);
	system("clear");
}


/* no input, no output */
/* to show the game's guideline on the terminal */
void screen::showrule()
{
	this->gotoxy(83, 3);
	printf("Game Rules:");
	this->gotoxy(83, 4);
	printf("Bump the target out of the arena by setting the bumping direction and primary speed");
	this->gotoxy(83, 5);
	printf("Two points in the arena, \"P\" is controlled by you, \"T\" is the target");
	this->gotoxy(83, 6);
	printf("Set the direction by inputting \"+ number\" or \"- number\", the number can be any integers from 0 to 180 inclusive (but -0 and -180 are not supported)");
	this->gotoxy(83, 7);
	printf("\"+\" means rotate counterclockwise, \"-\" means rotate clockwise");
	this->gotoxy(83, 8);
	printf("Set the primary speed by \"a number\", the number can be any integer from 1 to 15(inclusive)");
	this->gotoxy(83, 9);
	printf("Only the case T is bumped out of the arena and P remains in the arena will be regarded as WIN");
	this->gotoxy(83, 10);
	printf("Five rounds of game in total, WIN for at least 3 rounds is regarded success");
	
}


/*input, no output*/
/*print the motion curve of the cars*/
void screen::trackRtoL(int i)
{
	switch (i) {
	case 0:
		wcout << ' ';
		break;
	case 1:
		wcout << L'\u2591'; /* print light shade */
		break;
	case 2:
		wcout << L'\u2592'; /* print medium shade */
		break;
	case 3:
		wcout << L'\u2593'; /* print dark shade */
		break;
	}
}


/*input the slope k of the line connecting p and t, the intercept and the x coordinate of the car(p or t), no ouput */
/*plot the motion curve of p and t*/
void screen::plot(double k, double b, int x)
{
	int x_s= x - 1;
	int x, y, i = 0;
	for (; x_s < col && x_tick < x + 3; ++x_s) {
		x = x_s;
		y = k* x + b;
		gotoxy(x, y);
		trackRtoL(i);
		i++;
	}
	fflush(stdout);
}


/* no input, no output */
/* print out the rectangle arena on the screen*/
void screen::arena()
{
	gotoxy(0, 0);
	for (int i = 0; i < col; i++) {
		cout << "-";
	}
	for (int j = 0; j < row; j++) {
		gotoxy(0, j);
		cout << "|";
		gotoxy(col, j);
		cout << "|";
	}
	gotoxy(0, row);
	for (int i = 0; i < Columns; i++) {
		cout << "-";
	}
	fflush(stdout);		

}



