#include <cstdlib>
#include <car.h>
#include <cmath>
#include <iostream>
using namespace std;

// input two integers, no output
// set the primary characters for cars 
car::car(int x2, int y2)
{
	d = 0;
	v = 0;
	x = x2 + (rand() % 25);
	y = y2 + (rand() % 25);
	elasticity = rand() % 10 + 1;
	xrate = rand() % 100 + 1;
	yrate = rand() % 100 + 1;
	slope = 0;
}


// no input, output the x-coordinate 
// to get the x-coordinate
int car::getx()
{
	return x;
}


// no input, output the y-coordinate
// to get the y-coordinate 
int car::gety()
{
	return y;
}

// input the an integer, update the x-coordinate 
// to update the x-coordinate
void car::setx(int x2)
{
	x = x2;
}


// input the an integer, update the y-coordinate 
// to update the y-coordinate
void car::sety(int y2)
{
	y = y2;
}

// input the speed, update the primary speed of p
// to update the primary speed of p
void car::setv(float speed)
{
	v = speed;
}


// no input, output the elasticity
// to get the elasticity
int car::getelasticity()
{
	return elasticity;
}


// no input, no output 
// to update the slope of l
void car::setSlope()
{
	float i = 1.0;
	if (slope < 0)
		i = -1.0;
	slope = (i * yrate) / xrate;
}


// no input, output the primary speed of p
// to get the primary speed of p
float car::getv()
{
	return v;
}


// no input, output the slope of l
// to get the slope 
double car::getSlope()
{
	return slope;
}


// input the entered direction, no output
// update the direction 
void car::get_direction(int dirc)
{
	int d = 100;
	while (d > 90 || d < -90) {
		d = dirc - 22 + rand() % 45;
	}
}


// input two numbers, output their absolute value 
// to get the absolute value 
double car::abs_sub(double a, double b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}


// input the x,y coordinates of car, output the integer indicates whether it collided or not(1:collid, 0: not collided)
// to check whether collid successfully 
int car::collided(int carx, int cary)
{
	float distance =
	    sqrt((carx - x) * (carx - x) + (cary - y) * (cary - y));	
	return (distance <= 2);
}

// no input, output the y-intercept of l
// to get the y-intercept of l
double car::intcpt()
{
	return cpt;
}


// input the interger i, no output 
// update the y-intercept of l
void car::convert(int i)
{
	cpt = y - slope * x;
}


// no input, no output 
// to update the slope and y-intercept of l
void car::convert()
{
	double pii = 3.141592654;
	slope = tan(((double) (-d) / 180) * pii);
	cpt = y - slope * x;
}


// input the primary speed, decceleration and distance travelled, output the time it takes 
// to get the travelling time 
float car::duration(float v, float a, float s)
{
	float t1, t2, t, v2;
	v2 = sqrt(v * v + 2 * a * s);	
	t = (v - v2) / (-a);	
	return t;
}


// no input, output the truth value whether the car hits the edge 
// the car keeps moving until it hits the edge 
int car::move()
{
	x++;
	y = slope * x + intcpt();
	if (x > 80 || y > 40 || y < 0) {
		return 1;
	}
	return 0;

}
