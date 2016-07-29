/* Write a C program to classify a given triangle as equilateral, isosceles or scalene */

/***********************************************************
* You can use all the programs on www.c-program-example.com
* for personal and learning purposes. For permissions to use the
* programs for commercial purposes,
* contact info@c-program-example.com
* To find more C programs, do visit www.c-program-example.com
* and browse!
* This program was originally published at
* http://www.c-program-example.com/2011/09/c-program-to-classify-triangle-as.html
* Happy Coding
***********************************************************/

#include<stdio.h>
#include<math.h>

int main() {
int a, b, c;
float s, area;

printf("Enter the values of the sides of the triangle: \n");
scanf("%d %d %d", &a, &b, &c);
if ((a + b > c && a + c > b && b + c > a) && (a > 0 && b > 0 && c > 0)) {
s = (a + b + c) / 2.0;
area = sqrt((s * (s - a) * (s - b) * (s - c)));
if (a == b && b == c) {
printf("Equilateral Triangle. \n");
printf("Area of Equilateral Triangle is: %f", area);
}
else if (a == b || b == c || a == c) {
printf("Isosceles Triangle. \n");
printf("Area of an Isosceles Triangle: %f", area);
}
else {
printf("Scalene Triangle. \n");
printf("Area of Scalene Triangle: %f", area);
}
}
else {
printf("Triangle formation not possible");
}

return 0;
}

