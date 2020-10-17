#include <cstdlib>
#include <camth>
//trigonometric functions in <cmath> use radians as input.
//Pos1[0] = x coordinate of player 1
//Pos1[1] = y coordinate of player 1

void Toenemy (double Pos1[], double Pos2[]) {
  double pi=3.141592653589;
  int i; //direction in degree.
  double angle=atan((Pos[1]-Pos2[1])/(Pos1[0]-Pos2[0]))+pi-(pi/4);
  i=(angle/pi)*180+(rand()%90);
  return (i/180)*pi; //angle of collided car.
}

