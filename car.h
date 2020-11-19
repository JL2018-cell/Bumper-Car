#ifndef _CAR_H_
#define _CAR_H_
#include <string>
// p means player, t means target in comments 

class car {
    private:    
	int x, y;    // x-coordinate and y-coordinate
	double direction;    // starting direction of the p    
    double v0;    // primary speed of the p
    double v1;    // the speed of p before the moment of collision
	double v2,v3;    // v2 denotes the speed of p after collision, v3 denotes the speed of t after collision
    double d1;     // the primary distance between p and t
    double d2;    // the distance between t and q
    double u;    // the coefficient of friction    
    string difficulty;    // the difficulty level

    public:
    void getdirec(int direc);    // get the direction from the player's input 
    void getv0(int v0_i);    // get the primary speed from the player's input 
    void getdiff(string diff);    // get the difficulty level from the player's input
    void getu();    // set the friction coefficient
    
	void primary_position();    // set the primary positions for p and t 
    void samepos(car & t);    // to avoid the primary positions of p and t are same
    bool checkdirec(car & t);    //check whether the direction is true or not 
    void distance(car & p);    // update the distance between p and t 
    double p_speed_beforecol();    // output the speed of p before the moment of collision
    double p_speed_aftercol();    // output the speed of p after collision
    double t_speed_aftercol();    // output the speed of t after collision 
    void dist_boundary(car & t);    // output the distance between t and q
    bool check_t_out();    // check whether t will be bumped out of the arena or not after collision
    bool check_p_remain();    // check whether p will remain in the arena or not after collision 

    
	
	
};
#endif
