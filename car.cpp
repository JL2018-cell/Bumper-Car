#include <cstdlib>
#include <ctime>
#include "car.h"
#include <cmath>
#include <iostream>
using namespace std;


// no input, output the x coordinate of the car
// to get the x coordinate of the car
int car::getx(){
    return x;
}

// no input, output the y coordinate of the car
// to get the y coordinate of the car
int car::gety(){
    return y;
}


// input the primary direction from the player's input, no output
// to update the primary direction of p
void car::getdirec(double direc){direction=direc;}


// input the primary speed of p from the player's input, no output
// to update the primary speed of p
void car::getv0(double v0_c){v0=v0_c;}


// input the difficulty level from the player's input, no output
// to update the difficulty level
void car::getdiff(string diff){difficulty=diff;}


// no input, no output
// set the friction coefficient under different difficulty levels
void car::getu(){
    if(difficulty=="Easy") u=0;
    if(difficulty=="Medium" || difficulty=="Hard") u=0.4;
}


// no input, no output
// to generate the random starting positions for cars
void car::primary_position(){
    srand(time(NULL));
    x = rand()%77+2;
    y = rand()%37+2; // to avoid the primary positions for p and t to be on the boundaries
}


// input the target, output the slope
// to get the slope k, assume the line connecting p and t is y=k*x+b
double car::getk(car & t){
    if(t.x!=x)
    k=(t.y-y)/(t.x-x);
    return k;
}


//no input, output the y intercept of l
// to get the b
double car::getb(){
    b=y-k*x;
    return b;
}


// no input, no output
// to avoid the primary positions of p and t are same
void car::samepos(car & t){
    while(x==t.x && y==t.y){
        t.primary_position();
    }
}


// input the target, no output
// to get the primary distance between p and t
void car::distance(car & t){
    double dx = t.x - x;
    double dy = t.x - y;
    d1 = sqrt( dx * dx + dy * dy);
}


// input the target, output the truth value of the direction
// to check whether the direction is true or not
bool car::checkdirec(car & t){
    if(x==t.x){
        if(t.y<y) truedir=90;
        if(t.y>y) truedir=-90;
    }

    if(x!=t.x){
        double mytan = 2*(y-t.y)/(t.x-x);
        if(t.x>x) truedir = (atan(mytan))*180/pi;
        if(t.x<x){
            if(t.y>y) truedir = (atan(mytan) )*180/pi- 180;
            if(t.y==y) truedir = 180;
            if(t.y<y) truedir = (atan(mytan))*180/pi + 180;
        }
    }
    double err = direction-truedir;
    if(truedir>160){
        if(direction>=truedir-20 && direction<=180) return true;
        else return false;
    }
    if(truedir<-160){
        if(direction>-180 && direction<=truedir+20) return true;
        else return false;
    }

    if(truedir>=-160 && truedir<=160){
        if(abs(err)<=10) return true; // 20-degree error will be tolerated  
        else return false;
    }

}


// no input, output the truedir
// to get the true direction
double car::gettruedir(){
    return truedir;
}


// no input, output the speed of p before the moment of collision
// to get the speed of p before the moment of collision
double car::p_speed_beforecol(){
    if(difficulty=="Easy") v1=v0;
    if(difficulty=="Medium"||difficulty=="Medium"){
        if(0.5*v0*v0>u*d1) v1=sqrt(v0*v0-2*u*d1);
        else v1=0;
    }
    return v1;
}


//no input, output the speed of p after the moment of collsion
//to get the speed of p after the moment of collsion
double car::p_speed_aftercol(){
    if(difficulty=="Easy" || difficulty=="Medium") v2=0;
    if(difficulty=="Hard") v2=v1/4;
    return v2;
}


// no input, output the speed of t after the moment of collsion
// to get the speed of t after the moment of collsion
double car::t_speed_aftercol(){
    if(difficulty=="Easy" || difficulty=="Medium") v3=v1;
    if(difficulty=="Hard") v3==3*v1/4;
    return v3;
}


// no input, output the distance between t and q(the intersection point of the boundary and the extension of l(the line connects p and t))
// to get the distance between t and q
void car::dist_boundary(car & t){
    if(x==t.x){
        if(t.y>y) d2=40-t.y;
        if(t.y<y) d2=t.y;
    }
    if(y==t.y){
        if(t.x>x) d2=80-t.x;
        if(t.x<x) d2=t.x;
    }
    if(x!=t.x && y!=t.y){
        double bou_tan;
        double xq,yq; // the x,y coordinates of q

        if(t.x>x && t.y>y){
            bou_tan = (40-y)/(80-x);
            if(bou_tan==k) d2=sqrt((80-t.x)*(80-t.x)+(40-t.y)*(40-t.y));
            if(k>bou_tan){
                yq = 40;
                xq = (yq-b)/k;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
            if(k<bou_tan){
                xq=80;
                yq = k*xq+b;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
        }
        if(t.x>x && t.y<y){
            bou_tan = (0-y)/(80-x);
            if(bou_tan==k) d2=sqrt((80-t.x)*(80-t.x)+t.y*t.y);
            if(k>bou_tan){
                xq=80;
                yq = k*xq+b;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
            if(k<bou_tan){
                yq=0;
                xq = (yq-b)/k;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }

        }
        if(t.x<x && t.y>y){
            bou_tan = (40-y)/(0-x);
            if(bou_tan==k) d2=sqrt((40-t.y)*(40-t.y)+t.x*t.x);
            if(k>bou_tan){
                xq=0;
                yq = k*xq+b;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
            if(k<bou_tan){
                yq=40;
                xq = (yq-b)/k;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
        }
        if(t.x<x && t.y<y){
            bou_tan = y/x;
            if(bou_tan==k) d2=sqrt(t.x*t.x + t.y*t.y);
            if(k>bou_tan){
                yq=0;
                xq = (yq-b)/k;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
            if(k<bou_tan){
                xq=0;
                yq = k*xq+b;
                d2=sqrt((yq-t.y)*(yq-t.y)+(xq-t.x)*(xq-t.x));
            }
        }
    }
}


// no input, output the truth value of whether t will be bumped out of the arena or not after collision
// check whether t will be bumped out of the arena or not after collision
bool car::check_t_out(){
    if(0.5*v3*v3>u*d2) return true;
    else return false;
}


// no input, output the truth value of whether p will remain in the arena or not after collision
// check whether p will remain in the arena or not after collision
bool car::check_p_remain(){
    if(0.5*v2*v2<=u*d2) return true;
    else return false;
}

