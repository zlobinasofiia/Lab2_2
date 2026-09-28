#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x)
{
    //Реалізує підінтегральну функцію
    return x * pow(sin(x), 2);
}

//Метод лівих прямокутників
double leftrectangle(double a, double b, unsigned int n)
{
    //Обчислюємо крок розбиття відрізка
    double h = (b - a)/ n;

    //У цій змінній накопичується сума значень функції
    double sum = 0.0;

    double x;
    unsigned int i;

// Проходимо по всіх проміжках
//Для обчислення беремо ліву точку кожного проміжку
    for (i = 0; i<n; i++)
    {
        //Знаходимо координату поточної точки
        x = a + i * h;

        //Додаємо значення функції до суми
        sum += f(x);
    }
// Множимо суму на ширину прямокутника Н
    return sum * h;
}

//Метод правих прямокутників
double rightrectangle(double a, double b, unsigned int n)
{
    //Обчислюємо крок
    double h = (b - a)/ n;

    double sum = 0.0;
    double x;
    unsigned int i;

    //Починаємо з 1, тому що використовуємо праву точку кожного проміжку
    for (i = 1; i <= n; i++)
    {
        //Знаходимо праву точку проміжку
        x = a + i * h;

        //Додаємо значення функції до суми
        sum += f(x);
    }
    //Отримуємо наближене значення інтеграла
    return sum * h;
}

//Метод трапецій
double trapezoid(double a, double b, unsigned int n)
{
    //Крок розбиття
    double h = (b - a)/ n;

    //Значення функції на початку і в кінці відрізка враховуються з коефіцієнтом 1/2
    double sum = (f(a) + f(b)) / 2.0;

    double x;
    unsigned int i;

    //Додаємо значення функціїї у внутрішніх точках
    for (i = 1; i<n; i ++)
    {
        x = a + i * h;
        sum += f(x);
    }
    //Множимо отриману суму на крок
    return sum * h;
}

//Метод Сімпсона
double simpson(double a, double b, unsigned int n)
{
    //Обчислюємо крок
    double h = (b - a)/ n;

    //Спочатку додаємо значення функції на початку і в кінці відрізка
    double sum = f(a) + f(b);

    double x;
    unsigned int i;

    //Для методу Сімпсона кількість проміжків н повинна бути парною
    for (i = 1; i<n; i++)
    {
        x = a + i * h;

        //Для парних точок коефіцієнт дорівнює 2
        if (i % 2 == 0)
        {
            sum += 2.0 * f(x);
        }

        //Для непарних точок коефіцієнт дорівнює 4
        else
            {
                sum += 4.0 * f(x);
            }
                    }
    //Формула методу Сімпсона
    return sum * h / 3.0;
}

//Функція вибору метода
double calculate(int method, double a, double b, unsigned int n)
{
    switch (method)
    {
    case 1:
        return leftrectangle(a, b, n);

    case 2:
        return rightrectangle(a, b, n);

    case 3:
        return trapezoid(a, b, n);

    case 4:
        return simpson(a, b, n);

    default:
        return 0.0;
    }
}

int main()
{
    double a = 0.0; //Межі інтегрування
    double b = 1.0; //Межі інтегрування

    //І1 інтеграл при кількості проміжків Н
    //І2 інтеграл при кількості проміжків Н+2
    double I1, I2;
    double Delta; //Різниця між І1 та І2
    double eps; //Задана точність обчислення

    unsigned int N; //Кіл-ть проміжків розбиття
    unsigned int nValues[4] = {10, 100, 1000, 10000}; //Значення Н, для яких будуємо таблицю

    int method;
    int i;

    printf("============================================================\n");
    printf("          LABORATORY WORK 2 - PART 2\n");
    printf("                    VARIANT 5\n");
    printf("============================================================\n");
    printf("Integral: x * sin^2(x)\n");
    printf("Limits:   [0; 1]\n");

    //Табло для різних n
    printf("\nRESULTS FOR DIFFERENT n\n");
    printf("--------------------------------------------------------------------------\n");
    printf("%-8s %-14s %-14s %-14s %-14s\n",
           "n", "Left rect.", "Right rect.", "Trapezoid", "Simpson");
    printf("--------------------------------------------------------------------------\n");

    //По черзі беремо н = 10, 100, 1000, 10000
    for ( i = 0; i<4; i++)
    {
        unsigned int n = nValues[i];

        //Для кожного н обчислюємо інтеграл усіма 4 методами
        printf("%-8u %-14.10f %-14.10f %-14.10f %-14.10f\n",
               n,
               leftrectangle(a, b, n),
               rightrectangle(a, b, n),
               trapezoid(a, b, n),
               simpson(a, b, n));
    }

    printf("--------------------------------------------------------------------------\n");

    //Вибір методу
    printf("\nChoose integration method:\n");
    printf("1 - Left rectangles\n");
    printf("2 - Right rectangles\n");
    printf("3 - Trapezoid\n");
    printf("4 - Simpson\n");

    //Повторюємо мвведення, поки користувая не введе число від 1 до 4
    do
    {
        printf("\nMetod: ");
        scanf("%d", &method);

        if (method < 1 || method > 4)
        {
            printf("Error! Choose method from 1 to 4. \n");
        }
    } while (method < 1 || method > 4);

    //Введіть N
    do
    {
       printf("Enter N: ");
       scanf("%u", &N);

       //Н не може дорівнювати 0
       if (N == 0)
       {
        printf("N must be greater than 0.\n");
       }

       //Для методу Сімпсона Н повинно бути парним
       if (method == 4 && N % 2 != 0)
       {
           printf("For simson method N musst be even.\n");
       }

    } while (N == 0 || (method == 4 && N % 2 != 0));

   //Введіть точність epsilon
   do
   {
       // За умовою лабораторної роботи epsilon вибирається від 0.00001 до 0.001
       printf("Enter epsilon (0.00001 - 0.001): ");
       scanf("%lf", &eps);

       //Перевіряємо правильність введеної точності
       if (eps < 0.00001 || eps > 0.001)
       {
           printf("Incorrect epsilion!\n");
       }
   } while (eps < 0.00001 || eps > 0.001);

   //Розрахунок I1, I2 ta Delta
   printf("\nCALCULATION\n");
   printf("--------------------------------------------------------------\n");
   printf("%-8s %-15s %-15s %-15s\n",
           "N", "I1", "I2", "Delta");
printf("--------------------------------------------------------------\n");

//Обчислення повторюються, поки різниця між І1 та І2 більша за задану точність
   do
   {
       I1 = calculate(method, a, b, N); //Інтеграл для Н проміжків
       I2 = calculate(method, a, b, N + 2); //Інтеграл для н+2 проміжків

       Delta = fabs(I1 - I2); //Знаходимо абсолютну різницю між двома значеннями інтеграла

       printf("%-8u %-15.10f %-15.10f %-15.10f\n",
              N, I1, I2, Delta); //Виводимо результат поточної інтеграції

    //Якщо потрібна точність ще не досягнута, збільшуємо кількість проміжків на 2
    if (Delta > eps)
    {
        N+= 2;
    }
   } while (Delta > eps);

    printf("--------------------------------------------------------------\n");

    //Кінцевий результат
   printf("\nFinal result:\n");
   printf("N = %u\n", N);
   printf("I1 = %.101f\n", I1);
   printf("I2 = %.101f\n", I2);
   printf("Delta = %.101f\n", Delta);
   printf("Epsilon = %.101f\n", eps);

   // Перевірка основної умови лабораторної роботи: Delta повинна бути меншою або дорівнювати epsilon
    printf("\nCondition: Delta <= Epsilon\n");
    printf("%.10f <= %.10f\n", Delta, eps);

    printf("\nCalculation completed successfully.\n");

 return 0;
}
