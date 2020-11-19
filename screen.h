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
	void gotoxy(int x, int y);    //to place the cursor at column x and row y of the terminal
	void showcar_p(car p);    //display the player's point P on the screen
	void showcar_t(car t);    //display the target point T on the screen	
	void clrscr();    //to clear the screen after each round of game	
	void showrule();    //to show the game's guideline on the terminal 
	void trackRtoL(int i);    
	void plot(double k, double b, int x);    // to show the motion curve of cars	
	void arena();    //print out the rectangle arena on the screen
	
	
};
#endif
