#include <cstdlib>
#include <iostream>
// p means the player, t means the target in comments
// l means the line connecting p and t
class car {
	int x, y;    //(x,y) = coordinate of car
	double slope, cpt;    // the slope of l, the y-intercept of l
	float elasticity, xrate, yrate;    

    public:
	float v;    // speed apply to car
	int d;    // direction of car
	car(int x2, int y2);
	int getx();
	int gety();
	void setx(int x2);
	void sety(int y2);
	void setv(float speed);
	float getv();
	double getSlope();
	int getelasticity();
	void setSlope();
	void get_direction(int dirc);
	double abs_sub(double a, double b);
	int collided(int carx, int cary);
	double intcpt();
	void convert();
	void convert(int i);
	float duration(float v, float a, float s);
	int move();
};
