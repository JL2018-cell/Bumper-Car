#include <cstdlib>
#include <car.h>
#include <cmath>
#include <iostream>
using namespace std;
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

int car::getx()
{
	return x;
}

int car::gety()
{
	return y;
}

void car::setx(int x2)
{
	x = x2;
}

void car::sety(int y2)
{
	y = y2;
}

void car::setv(float speed)
{
	v = speed;
}

int car::getelasticity()
{
	return elasticity;
}

void car::setSlope()
{
	float i = 1.0;
	if (slope < 0)
		i = -1.0;
	slope = (i * yrate) / xrate;
}

float car::getv()
{
	return v;
}

double car::getSlope()
{
	return slope;
}

void car::get_direction(int dirc)
{
	int d = 100;
	while (d > 90 || d < -90) {
		d = dirc - 22 + rand() % 45;
	}
}

double car::abs_sub(double a, double b)
{
	if (a > b)
		return a - b;
	else
		return b - a;
}

int car::collided(int carx, int cary)
{
	float distance =
	    sqrt((carx - x) * (carx - x) + (cary - y) * (cary - y));
	// We set a default collid area as it's a text screen
	//1: collided, 0:not collided
	return (distance <= 2);
}

double car::intcpt()
{
	return cpt;
}

void car::convert(int i)
{
	cpt = y - slope * x;
}

void car::convert()
{
	double pii = 3.141592654;
	slope = tan(((double) (-d) / 180) * pii);
	cpt = y - slope * x;
}

float car::duration(float v, float a, float s)
{
	float t1, t2, t, v2;
	v2 = sqrt(v * v + 2 * a * s);
	//speed after travelling for distance s, decceleration = a, initial speed = v
	t = (v - v2) / (-a);
	//time spent during the journey of the bumper car.
	return t;
}

// car move on, if it hit edge return 1 else 0
int car::move()
{
	x++;
	y = slope * x + intcpt();
	if (x > 80 || y > 40 || y < 0) {
		return 1;
	}
	return 0;

}
