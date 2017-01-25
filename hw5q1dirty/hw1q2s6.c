/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
char* SplitMainExpression(char* expression);
unsigned int calculate(char* expression, unsigned int modulus, unsigned int* result);
void StringCopy(char *source, char *destination);
unsigned int ExtractIntFromStr(char* string);
bool ContainsParentheses(char* string);
bool MathFunc(unsigned int val_1, unsigned int val_2, char operation, unsigned int modulus, unsigned int* result);



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    unsigned int modulus = 100;
    char* expression = "(((100000*100000)*(100000*100000))+1)";
    unsigned int result = 0;

    calculate(expression, modulus, &result);

    printf("Result: %u\n", result);

  return 0;
}


unsigned int calculate(char* expression, unsigned int modulus, unsigned int* result)
{
    char left[255] = {0};
    char right[255] = {0};
    char* op = SplitMainExpression(expression+1);
    unsigned int left_val = 0, right_val = 0;
    while (*op == '(')
    {
        op--;
    }
    while (*op == ')')
    {
        op++;
    }
    printf("Operator: %c\n", *op);
    StringCopy((expression+1), left);
    printf("Left: %s\n", left);
    StringCopy((op+1), right);
    printf("Right: %s\n", right);

    if (ContainsParentheses(left) == false)
    {
        left_val = ExtractIntFromStr(left);
        //printf("Left val: %u\n", left_val);
    }

    if (ContainsParentheses(right) == false)
    {
        right_val = ExtractIntFromStr(right);
       // printf("Right val: %u\n", right_val);
    }

    if (left_val == 0)
    {
        calculate(left, modulus, result);
        left_val = *result;
    }

    if (right_val == 0)
    {
        calculate(right, modulus, result);
        right_val = *result;
    }

    if (left_val != 0 && right_val != 0)
    {
        MathFunc(left_val, right_val, *op, modulus, result);
    }

    return 0;
}



void StringCopy(char *source, char *destination)
{
    int paren_ctr = 0;
    do
    {
        if (*source == '(')
        {
            paren_ctr++;
        }

        if (*source == ')')
        {
            paren_ctr--;
        }

        *destination = *source;

        source++;
        destination++;
    } while (paren_ctr != 0 || (*source >= '0' && *source <= '9'));

    *(destination) = '\0';
}

char* SplitMainExpression(char* expression) {
    int parenthesis_counter = 0;
    while (*expression != '\0') {

        if (*(expression) >= '0' && *(expression) <= '9')
        {
            expression++;
        }

        if (*expression == '(') {
            parenthesis_counter++;
        }
        else if (*expression == ')') {
            parenthesis_counter--;
        }

        if (parenthesis_counter == 0 && !(*(expression) >= '0' && *(expression) <= '9')) {
            return expression;
        }

        expression++;
    }

    return expression;
}

unsigned int ExtractIntFromStr(char* string)
{
    unsigned int number = 0;
    while (*string >= '0' && *string <= '9')
    {
        number = number * 10 + (*string - '0');
        string++;
    }

    return number;
}

bool ContainsParentheses(char* string)
{
    while (*string != '\0')
    {
        if (*string == '(' || *string == ')')
        {
            return true;
        }

        string++;
    }

    return false;
}


bool MathFunc(unsigned int val_1, unsigned int val_2, char operation, unsigned int modulus, unsigned int* result)
{
    val_1 = val_1%modulus;
    printf("Val 1: %u\n", val_1);
    val_2 = val_2%modulus;
    printf("Val 2: %u\n", val_2);

    unsigned long long raw_result;

    if (operation == '+')
    {
        raw_result = val_1 + val_2;
    }

    else if (operation == '*')
    {
        raw_result = val_1 * val_2;
    }

    else
    {
        printf("Error: invalid operator. Only + and * are supported.\n");
        return false;
    }

    printf("%llu\n", raw_result);

    raw_result = raw_result%modulus;

    if (raw_result > UINT_MAX)
    {
        printf("Error: result exceeds range of unsigned int.\n");
        return false;
    }

    *result = (unsigned int)raw_result;

    return true;
}
