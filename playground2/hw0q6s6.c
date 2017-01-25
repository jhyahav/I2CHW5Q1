/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
char* SplitMainExpression(char* expression);
unsigned int Compute(char* expression, unsigned int* result);
unsigned int ExtractIntFromStr(char* string);
/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    char string[] = "(1+2)+(3+4)";
    unsigned int result = 0;

    printf("%u\n", Compute(string, &result));


  return 0;
}

char* SplitMainExpression(char* expression) {
    int parenthesis_counter = 0;
    while (*expression != '\0') {
        if (*expression == '(') {
            parenthesis_counter++;
        }
        else if (*expression == ')') {
            parenthesis_counter--;
        }

        if (parenthesis_counter == 0) {
            return expression + 1;
        }

        expression++;
    }

    return '\0';
}

unsigned int Compute(char* expression, unsigned int* result) {
    printf("Original string: %s\n", expression);
    char* mid_ptr = SplitMainExpression(expression + 1);
    if (*mid_ptr == '\0')
    {
        mid_ptr = expression;
    }


    /*while (*mid_ptr == '(' || *mid_ptr == ')')
    {
        mid_ptr++;
    }*/

    if (*mid_ptr != '+' && *mid_ptr != '*')
    {
        if (*mid_ptr >= '0' && *mid_ptr <= '9')
        {
            unsigned int operand = ExtractIntFromStr(mid_ptr);
            //printf("%u", operand);
            return operand;
        }
        else
        {
            ///Need to exit or something
            printf("Error: invalid mid, %c\n", *mid_ptr);
            return 0;
        }
    }

    char* right_ptr = (mid_ptr);
    printf("RIGHT: %s\n", right_ptr);
    printf("TEST: %c\n", *right_ptr);
    char* left_ptr = expression + 1;

    unsigned int left_operand, right_operand;

    right_operand = Compute(right_ptr, result);
    left_operand = Compute(left_ptr, result);

    /*if (right_operand == 0 || left_operand == 0)
    {
        return 0;
    }*/


    printf("%u and %u\n", left_operand, right_operand);

    *result = (*mid_ptr == '+') ? left_operand + right_operand : left_operand * right_operand;

    return *result;
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


//This function calculates the length of a given string.
int StringLength(char *string_ptr)
{
    int length = 0;
    while (*string_ptr != '\0')
    {
        length++;
        string_ptr++;
    }

    return length;
}

//This function copies the contents of one string to another.
void StringCopy(char *source, char *destination)
{
    for (; *source != ')'; source++, destination++)
    {
        *destination = *source;
    }

    *(destination) = ')';
    *(++destination) = '\0';



}
