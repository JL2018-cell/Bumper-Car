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

// input car A, no output 
// to display the car on the screen
void screen::showcar(car A)
{
	gotoxy(A.getx(), A.gety());
	cout << "A";
	fflush(stdout);
}


// input the car and i(stands for command), i=1: clear the file before write, i=0: append content to file
// to save the game progress
void screen::saveGame(car bumper, int i)
{				
	
	if (i) {
		fstream MyFile;
		MyFile.open("Temp.txt", ios::out);
		MyFile << bumper.getx();
		MyFile << endl;
		MyFile << bumper.gety();
		MyFile << endl;
		MyFile.close();
	} else {
		fstream MyFile;
		MyFile.open("Temp.txt", ios::app);
		MyFile << bumper.getx();
		MyFile << endl;
		MyFile << bumper.gety();
		MyFile << endl;
		MyFile.close();
	}
}


// input two integers x,y ,no output 
// place the cursor on the 
void screen::gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}


// no input, no output 
// to clear the screen after each time of game 
void screen::clrscr(void)
{

	printf("\033[8;40;120t");
	fflush(stdout);
	system("clear");

}


// no input, no output 
// to show the game's guideline on the terminal 
void screen::showRule()
{
	this->gotoxy(83, 3);
	cout << "Game Rule:";
	this->gotoxy(83, 4);
	cout << "Random positions friction";
	this->gotoxy(83, 5);
	cout << "Random collided speed direction";
	this->gotoxy(83, 6);
	cout << "----------";
	this->gotoxy(83, 7);
	cout << "Press \"q\":";
	this->gotoxy(83, 8);
	cout << "Turn pointer anti-clockwise.";
	this->gotoxy(83, 9);
	cout << "Press \"z\":";
	this->gotoxy(83, 10);
	cout << "Turn pointer anti-clockwise.";
	this->gotoxy(83, 11);
	cout << "Press \"a\":";
	this->gotoxy(83, 12);
	cout << "Increase speed by 1 unit.";
	this->gotoxy(83, 13);
	cout << "Press \"x\" twice:";
	this->gotoxy(83, 14);
	cout << "Exit and save.";
	this->gotoxy(83, 15);
	cout << "Press \"s\":";
	this->gotoxy(83, 16);
	cout << "To start";
}


struct termios orig_termios;
void reset_terminal_mode()
{
	tcsetattr(0, TCSANOW, &orig_termios);
}


// no input, no output 
// set the terminal so that it is in charater-at-a-time mode 
void screen::set_conio_terminal_mode()
{
	struct termios new_termios;

	/* take two copies - one for now, one for later */
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));

	/* register cleanup handler, and set the new terminal mode */
	atexit(reset_terminal_mode);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}


// input integer i, no output 
// help to plot the motion curve 
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


// input the slope f, intercept w, and x-coordinate of car, no output 
// plot the motion curve of the car 
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


// no input, if a key has been pressed, output a nonzero value, otherwise, output 0
// to determine whether a key has been pressed or not 
int screen::kbhit()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}


// no input, output the ASCII value of the key pressed
// to reads a single character from the keyboard 
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


// no input, no output 
// print out the rectangle arena on the screen
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
	fflush(stdout);//output immediately
}


//input two integers, output their great common divisor
//to get the great common divisor from two integers
int screen::gcd(int a, int b)
{
	 
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	
	if (a == b)
		return a;
	
	if (a > b)
		return gcd(a - b, b);
	return gcd(a, b - a);
}


// no input, no output 
// set terminal mode, set the locale, clear the screen and display the arena
screen::screen()
{
	set_conio_terminal_mode();
	setlocale(LC_ALL, "");
	clrscr();
	arena();
}
