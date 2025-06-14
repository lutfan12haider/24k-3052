#include<stdio.h>
#include<math.h>
struct point{
	float x;
	float y;
};
int main(){

struct point p1,p2;
printf("enter the value for (x1,y1):");
scanf ("%f %f",&p1.x,&p1.y);
printf("enter the value for (x2,y2):");
scanf ("%f %f",&p2.x,&p2.y);
float distance=sqrt(pow(p2.x-p1.x,2)+pow(p2.y-p2.y,2));
printf("\n--the distance between two point is %f--\n",distance);
return 0;
}