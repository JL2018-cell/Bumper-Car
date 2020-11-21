#ifndef _CAR_H_
#define _CAR_H_
#include <string>
using namespace std;
// p means player, t means target in comments
// l is the line connecting p and t, q is the intersection point of l and the boundary

class car {
    private:
	int x, y;    // x-coordinate and y-coordinate
	double direction;    // starting direction of the p inputted
    double truedir;    // true dirction
    double v0;    // primary speed of the p
    double v1;    // the speed of p before the moment of collision
	double v2,v3;    // v2 denotes the speed of p after collision, v3 denotes the speed of t after collision
    double d1;     // the primary distance between p and t
    double d2;    // the distance between t and q
    double u;    // the coefficient of friction
    double k;    // the slope the line l
    double b;    // the y-intercept of l 
    string difficulty;    // the difficulty level
    double pi=3.1415926535; // the pi 

    public:
    int getx();    // to get the x coordinate of the car
    int gety();    // to get the y coordinate of the car
    void getdirec(double direc);    // get the direction from the player's input
    void getv0(double v0_i);    // get the primary speed from the player's input
    void getdiff(string diff);    // get the difficulty level from the player's input
    void getu();    // set the friction coefficient

	void primary_position();    // set the primary positions for p and t
    void samepos(car & t);    // to avoid the primary positions of p and t are same
    double getk(car & t);    // to get the slope of l
    double getb();    // to get the y intercept of l    
    bool checkdirec(car & t);    //check whether the direction is true or not
    double gettruedir();    // to get the true direction (for testing)
    void distance(car & t);    // update the distance between p and t
    void dist_boundary(car & t);    // update the distance between t and q
    double p_speed_beforecol();    // output the speed of p before the moment of collision
    double p_speed_aftercol();    // output the speed of p after collision
    double t_speed_aftercol();    // output the speed of t after collision    
    bool check_t_out();    // check whether t will be bumped out of the arena or not after collision
    bool check_p_remain();    // check whether p will remain in the arena or not after collision




};
#endif
