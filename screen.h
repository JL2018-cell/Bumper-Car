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
	int Columns = 80, row = 40;
	void gotoxy(int x, int y);
	void clrscr(void);
	void set_conio_terminal_mode();
	void trackRtoL(int i);
	void plot(double f, int w, int t);
	int kbhit();
	int getch();
	void arena();
	void showcar(car A);
	void showRule();
	void saveGame(car bumper, int i);
	int gcd(int a, int b);
	screen();
};
