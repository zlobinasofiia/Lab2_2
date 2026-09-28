#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
    //Реалізує підінтегральну функцію
    return x * pow(sin(x), 2);
}

int main()
{
    double a = 0.0; //Межі інтегрування
    double b = 1.0; //Межі інтегрування
    double h;
    unsigned int N;

    printf("Variant 5\n");
    printf("integral: x * sin^2(x)\n");

    printf("Enter N: ");
    scanf("%u", &N);

    h = (b - a)/N;

    printf("a = %.21f\n", a);
    printf("b = %.21f\n", b);
    printf("h = %.61f\n", h);

    return 0;
}
