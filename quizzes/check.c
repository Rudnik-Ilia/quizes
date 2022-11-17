#include <stdio.h>

double squareRoot(double n) {
   double i, precision = 0.00001;

   for(i = 1; i*i <=n; ++i);           

   for(--i; i*i < n; i += precision);  

   return i;
}

int main() {
   double n = 12.138;

   printf("Square root of %f = %lf", n, squareRoot(n));

   return 0;
}
