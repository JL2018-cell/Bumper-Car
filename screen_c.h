#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <clocale>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <math.h>
#include <fstream>
using namespace std;

class screen {

    public:
	int col = 80, row = 40;
	void showcar(car p);
	void saveGame(car bumper, int i);

	void gotoxy(int x, int y);
	void clrscr(void);
	void set_conio_terminal_mode();
	void trackRtoL(int i);
	void plot(double f, int w, int t);
	int kbhit();
	int getch();
	void arena();
	
	void showRule();
	
	int gcd(int a, int b);
	 screen();
};
#endif