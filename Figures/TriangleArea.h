/* function to calculate area of triangle formed by (x1, y1), 
   (x2, y2) and (x3, y3) */

#include<math.h> // abs

float area(int x1, int y1, int x2, int y2, int x3, int y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0f); //f : float
}