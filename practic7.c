#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

#define ESC 27

int verify_int(int *), verify_choise_case(int), verify_float(float *), verify_bounds(float, float, float *, float *), verify_accuracy(float *);
float equation1(float, float), equation2(float, float), root1(float (*)(float, float), float, float, float, float), root2(float (*)(float, float), float, float t, float), calculation(float, float, float, int, int, float);
void clear();

int main()
{
    char key;
    do
    {

        float lower_bound, upper_bound, first_bound, second_bound, accuracy, result, dependent_variable;
        int choise_equation, choise_method, e;

        system("cls");

        do
        {
            printf("Enter 1 to calculate first equation or 2 to calculate the second one: ");
        } while ((verify_int(&choise_equation) == 1) || (verify_choise_case(choise_equation) == 1));
        do
        {
            printf("Enter the first bound: ");
        } while ((verify_float(&first_bound) == 1));
        do
        {
            printf("Enter the second bound: ");
        } while ((verify_float(&second_bound) == 1) || (verify_bounds(first_bound, second_bound, &lower_bound, &upper_bound)));
        do
        {
            printf("Enter dependent variable y: ");
        } while ((verify_float(&dependent_variable) == 1));
        do
        {
            printf("Enter accuracy: ");
        } while ((verify_float(&accuracy) == 1) || (verify_accuracy(&accuracy) == 1));
        do
        {
            printf("Enter 1 to use half division method or 2 to use Newton's method: ");
        } while ((verify_int(&choise_method) == 1) || (verify_choise_case(choise_method) == 1));

        result = calculation(lower_bound, upper_bound, dependent_variable, choise_method, choise_equation, accuracy);

        if (result != 0)
        {
            e = (log(1 / accuracy) / log(10));
            printf("x = %.*f \n", e, result);
        }

        printf("Press any button to keep going or escape to quit.");
        key = getch();

    } while (key != ESC);
}

//---calculation start---//

float equation1(float x, float t)
{
    return (cos(t / x) - 2 * sin(1.0 / x) + 1.0 / x);
}

float equation2(float x, float t)
{
    return sin(log(x)) - cos(log(x)) + t * log(x);
}

float calculation(float lower_bound, float upper_bound, float dependent_variable, int method, int choise_equation, float accuracy)
{
    float result;
    if (method == 1)
    {
        if (choise_equation == 1)
        {
            result = root1(equation1, lower_bound, upper_bound, dependent_variable, accuracy);
            return result;
        }
        result = root1(equation2, lower_bound, upper_bound, dependent_variable, accuracy);
        return result;
    }
    if (choise_equation == 1)
    {
        result = root2(equation1, upper_bound, dependent_variable, accuracy);
        return result;
    }
    result = root2(equation2, upper_bound, dependent_variable, accuracy);
    return result;
}

float root1(float (*func)(float, float), float low, float top, float t, float e)
{
    float x, fLow, fx;

    do
    {
        x = (low + top) / 2;
        fLow = (*func)(low, t);
        fx = (*func)(x, t);
        if (isnan(fLow) || isnan(fx))
        {
            printf("Value doesn't belong to the domain of function");
            return 0;
        }
        if (fLow * fx > 0)
        {
            low = x;
        }
        else
        {
            top = x;
        }
    } while (fabs(top - low) > e);

    if (fabs((*func)(x, t)) > 1)
    {
        printf("There is no roots in this range");
        return 0;
    }
    return x;
}

float root2(float (*func)(float, float), float top, float t, float e)
{
    float b, delta, x = top, der;

    do
    {
        b = (*func)(x, t);
        der = ((*func)(x + pow(10, -6), t) - b) / pow(10, -6); // derivative
        if (isnan(b) || isnan(der))
        {
            printf("Value doesn't belong to the domain of function");
            return 0;
        }
        delta = b / der;
        x -= delta;
    } while (fabs(delta) > e);

    if (fabs((*func)(x, t)) > 1)
    {
        printf("There is no roots in this range!\n");
        return 0;
    }
    return x;
}

//---calculation end---//

//---verefications start---//
int verify_int(int *variable_int)
{
    char ch;
    scanf("%d%c", variable_int, &ch);
    if (ch == '\n')
    {
        return 0;
    }
    printf("Invalid number. Try again!\n");
    clear();
    return 1;
}

int verify_choise_case(int var_choise_case)
{
    if ((var_choise_case == 1) || (var_choise_case == 2))
    {
        return 0;
    }
    printf("Invalid choise of equation or method. Try again!\n");
    return 1;
}

int verify_float(float *variable_float)
{
    char ch;
    scanf("%f%c", variable_float, &ch);
    if (ch == '\n')
    {
        return 0;
    }
    printf("Invalid number. Try again!\n");
    clear();
    return 1;
}

int verify_bounds(float var_first, float var_second, float *var_low, float *var_top)
{
    if (var_first < var_second)
    {
        *var_low = var_first;
        *var_top = var_second;
        return 0;
    }
    else if (var_first > var_second)
    {
        *var_top = var_first;
        *var_low = var_second;
        return 0;
    }
    printf("Invalid borders. Try again!\n");
    return 1;
}

int verify_accuracy(float *var_accuracy)
{
    int i;
    float result;
    if (*var_accuracy >= 1 && *var_accuracy <= 6)
    {
        *var_accuracy = 1 / (pow(10, *var_accuracy));
        return 0;
    }
    else if ((*var_accuracy < 1) && (*var_accuracy > (1e-7)))
    {
        for (i = 1; i < 8; i++)
        {
            result = (1 / (pow(10, i)));
            if (*var_accuracy == result)
            {
                return 0;
            }
            if (i == 8)
            {
                printf("Invalid accuracy. Try again!\n");
                return 1;
            }
        }
    }
    printf("Invalid accuracy. Try again!\n");
    return 1;
}

//---verefications end---//

void clear()
{
    int character;
    while ((character = getchar()) != '\n' && character != EOF) // end of file
        ;
}
