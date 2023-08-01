#include <stdio.h>

double squareRoot(double n) 
{
    double i = 1;
    double precision = 0.00001;

    while (i*i <= n)
    {
        ++i;
    }
    --i;
    for(; i*i < n; i+= precision)
    {

    }

    return i;
}

double Root(double x)
{   
    double presicion = 0.0001;
    double tmp = 1;

    while (tmp * tmp <= x)
    {
        ++tmp;
    }
    
    --tmp;

    for(tmp; tmp * tmp < x; tmp += presicion)
    {

    }
    
    printf("%f\n", tmp); 

}
















int main() 
{
   double n = 9.138;
   Root(n);

//    printf("Square root of %f = %f", n, squareRoot(n));

   return 0;
}
