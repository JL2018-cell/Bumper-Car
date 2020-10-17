#include <cmath>

bool judge_collion() {
  bool collide=false;
  For (int i=0;i<s_x_1;i++) { 
  //s_x_1 = horizontal distance that player 1 moves
    Pos1[0]+=1;   
    Pos1[1]+=tan(given angle)*1
    If (round(Pos1[0])== round(Pos2[0]) && round(Pos1[1])== round(Pos2[1])) collide = true;
  }
  return collide; //there is collision: true. Otherwise, false.
}
