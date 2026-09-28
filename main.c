#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
    //Реалізує підінтегральну функцію
    return x * pow(sin(x), 2);
}

//Метод лівих прямокутників
double rectangle(double a, double b, unsigned int N)
{
    double h;
    double x;
    double sum = 0.0;
    unsigned int i;

    h = (b - a)/ N;

    for (i = 0; i<N; i++)
    {
        x = a + i * h;
        sum = sum + f(x);
    }
    return sum * h;
}

//Метод трапецій
double trapezoid(double a, double b, unsigned int N)
{
    double h;
    double x;
    double sum;
    unsigned int i;

    h = (b - a)/ N;

    sum = (f(a) + f(b)) / 2.0;

    for (i = 1; i<N; i ++)
    {
        x = a + i * h;
        sum = sum + f(x);
    }
    return sum * h;
}

//Метод Сімпсона
double simpson(double a, double b, unsigned int N)
{
    double h;
    double x;
    double sum;
    unsigned int i;

    h = (b - a)/ N;

    sum = f(a) + f(b);

    for (i = 1; i<N; i++)
    {
        x = a + 1 * h;

        if (i % 2 == 0)
            sum = sum + 2 * f(x);
        else
            sum = sum + 4 * f(x);
    }
    return sum * h / 3.0;
}

int main()
{
    double a = 0.0; //Межі інтегрування
    double b = 1.0; //Межі інтегрування
    double result1;
    double result2;
    double result3;
    unsigned int N;

    printf("Variant 5\n");
    printf("integral: x * sin^2(x)\n");

    printf("Enter N: ");
    scanf("%u", &N);

    if (N % 2 != 0)
    {
        printf("N must be even!\n");
        return 1;
    }

    result1 = rectangle(a, b, N);
    result2 = trapezoid(a, b, N);
    result3 = simpson(a, b, N);

    printf("\nRectangle method = %.101f\n", result1);
    printf("Trapezoid method = %.101f\n", result2);
    printf("Simpson method = %.101f\n", result3);

    return 0;
}
