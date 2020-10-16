#include <iostream>
#include <string>
using namespace std;
int main() {
 char c='0';
 int d=0; //direction, true bearing.
 while (c!=32) {
   cout<<"current direction: "<<d<<endl;
   cin>>c;
   if (isalpha(c)) {
   }
   else break;
   switch (c) {
     case 'i':
       d=0;
       break;
     case 'k':
       d=180;
       break;
     case 'j':
       if (d>=180 && d<270)
         d+=5;
       else if ((d>270 && d<=360) || d==0) {
         if (d==0) {
	   d=360;
	 }
         d-=5;
       } 
       else if (d==270)
         d=270;
       else 
         cout<<"Please press l."<<endl;
       break;
     case 'l':
       if (d>90 && d<=180)
         d-=5;
       else if (d>=0 && d<90)
         d+=5;
       else if (d==90)
         d=90;
       else 
         cout<<"Please press j."<<endl;
       break;
     case ' ':
       cout<<"Input direction ends."<<endl;
       break;
   }
 }
}
