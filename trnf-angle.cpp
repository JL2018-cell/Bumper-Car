
#include <cmath>

int transform_angle_tangent(int d) {
  if (d>0 && d<90)
    return tan(90+d);
  else if (d==90)
    return 0;
  else if (d>90 && d<180)
    return tan(d-90);
  else if (d>180 && d<270)
    return tan(d-90);
  else if (d==270)
    return 0;
  else if (d>270 && d<360)
    return tan(90-(360-d));


}

