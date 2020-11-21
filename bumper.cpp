#include <clocale>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <cstdlib>
#include "car.h"
#include "screen.h"
#include <math.h>
#include <fstream>
using namespace std;

// input the cars and screen, no output
// load the saved game 
void reloadgame(car * b1, car * b2, screen bscreen)
{
	ifstream fin;
	fin.open("Temp.txt");
	if (!fin.fail()) {
		char c;
		bscreen.gotoxy(83, 18);
		cout << "Reload game? [Y]es/[N]o";
		fflush(stdout);
		cin >> c;
		if (c == 'Y' || c == 'y') {
			bscreen.gotoxy(b1->getx(), b1->gety());
			cout << " ";
			bscreen.gotoxy(b2->getx(), b2->gety());
			cout << " ";
			fflush(stdout);
			int b1_x, b1_y, b2_x, b2_y;
			fin >> b1_x >> b1_y >> b2_x >> b2_y;
			b1->setx(b1_x);
			b1->sety(b1_y);
			b2->setx(b2_x);
			b2->sety(b2_y);
			fin.close();
		}
		bscreen.gotoxy(83, 18);
		cout << "                       ";
		fflush(stdout);
	}
}


int main(int argc, char *argv[])
{
	char c, x = 1, y = 5;
	int reload = 0;    //adjustment of direction of car.
	int out1, out2;
	//a = decceleration of car, t = time, s = distance, v = initial speed.
	float v, a, s, t, v1, v2, t1, t2;
	car *bumper1, *bumper2;
	screen bumperscreen;    //Declare class containing information of each car, and draw arena on screen.
	a = -(rand() % 3 + 1);
	//v=10,a=-1,s=5 works.

      again:
	srand(time(NULL));	//return current time such that sequences of random numbers are different in different time.
	bumper1 = new car(3, 5);
	bumper2 = new car(45, 5);	//generate random position for car 1 and 2.
	bumperscreen.showcar(*bumper1);	//display car 1 on screen
	bumperscreen.showcar(*bumper2);	//display car 2 on screen
	bumperscreen.showRule();	//display rule of game on right hand side.
	if (reload == 0) {
		reloadgame(bumper1, bumper2, bumperscreen);
		bumperscreen.showcar(*bumper1);	//display car 1 on screen
		bumperscreen.showcar(*bumper2);	//display car 2 on screen
		reload = 1;
	}
	c = 1;
	fflush(stdout);
	while (c) {
		if (bumperscreen.kbhit()) {
			switch (bumperscreen.getch()) {
			case 'q':	//increace angle by 5 degree
				if (bumper1->d <= 85)
					bumper1->d += 1;	//Direction cannot point to left.
				break;
			case 'z':	//decrease angle by 5 degree;
				if (bumper1->d >= (-85))
					bumper1->d -= 1;	//Direction cannot point to left.
				break;
			case 'a':
				if (bumper1->v <= 30)
					bumper1->v += 2;	//upper bound of speed = 30
				break;
			case 'x':	//Quit and save the game if "X" is pressed.
				c = 0;
				bumperscreen.saveGame(*bumper1, 1);
				bumperscreen.saveGame(*bumper2, 0);
				bumperscreen.gotoxy(83, 2);
				cout << "Game is saved in Temp.txt";
				fflush(stdout);
				goto gameexit;
			case 's':	//finish input
				c = 0;
				if (bumper1->v == 0)
					bumper1->v = 1;
				break;
			default:
				break;
			}
			bumperscreen.gotoxy(bumper1->getx(),
					    bumper1->gety() - 1);
			if (bumper1->d >= 0) {
				cout << "E" << bumper1->d << "N Speed" <<
				    bumper1->v;
			} else {
				cout << "E" << (-bumper1->d) << "S Speed"
				    << bumper1->v;
			}
			fflush(stdout);
		}
	}
	bumperscreen.gotoxy(bumper1->getx(), bumper1->gety() - 1);
	cout << "                     ";
	fflush(stdout);
	//calculate the slope of straight line, which is motion path of bumper car.
	bumper1->convert();
	v = bumper1->v;
	s = v / (rand() % 20 + 10);
	//car 1 goes.
	while (v > 0) {
		t = bumper1->duration(v, a, s);
		v = v + a * t;
		usleep(500000 * t);
		bumperscreen.plot(bumper1->getSlope(), bumper1->intcpt(),
				  bumper1->getx());
		if (bumper1->move() == 1 || v <= 0.001 || isnan(v)) {
			bumperscreen.gotoxy(20, 30);
			cout << "You Lost! Press a key to play again!!!";
			fflush(stdout);
			bumperscreen.getch();
			goto tryagain;
		}
		if (bumper2->collided(bumper1->getx(), bumper1->gety())) {
			bumper1->setv(v);
			bumperscreen.gotoxy(83, 23);
			cout << "Collided!";
			fflush(stdout);
			break;
		}
	}
	// cars collide  and recaculate speed/direction 
	// simplify this two car has same speed but different direction
	bumper1->setv(v * (100 - bumper1->getelasticity()) / 100);
	bumper2->setv(bumper1->getv());
	bumper1->setSlope();
	bumper2->setSlope();
	bumper1->convert(1);
	bumper2->convert(1);
/* for testing
        bumper1->setv(30);
        bumper2->setv(30);
        bumper1->setx(30);
        bumper1->sety(20);;
        bumper2->setx(30);
        bumper2->sety(20);;
	bumper1->setSlope();
	bumper2->setSlope();
        bumper1->convert(1);
        bumper2->convert(1);
        s=10;
*/
	v1 = bumper1->getv();
	v2 = bumper2->getv();
	out1 = out2 = 0;
	while (1) {
		t1 = bumper1->duration(v1, a, s);
		v1 = v1 + a * t1;
		t2 = bumper2->duration(v2, a, s);
		v2 = v2 + a * t2;
		usleep(1000000 * t1);
		if (!out1 && v1) {
			bumperscreen.plot(bumper1->getSlope(),
					  bumper1->intcpt(),
					  bumper1->getx());
		}
		if (!out2 && v2) {
			bumperscreen.plot(bumper2->getSlope(),
					  bumper2->intcpt(),
					  bumper2->getx());
		}
		// If one car arrives at edge then you win
		out1 = bumper1->move();
		out2 = bumper2->move();
		if (out1 && out2) {
			bumperscreen.gotoxy(20, 30);
			cout << "You Win!, Press a key to play again!";
			fflush(stdout);
			bumperscreen.getch();
			goto tryagain;
		}

	}

      tryagain:
	free(bumper1);
	free(bumper2);
	bumperscreen.clrscr();	//Clear screen after game is over.
	bumperscreen.arena();
	goto again;
      gameexit:
	bumperscreen.clrscr();
	return 1;
}
