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
unsigned int calculate(char* expression, char* left, char* right, char* op);
void StringCopy(char *source, char *destination);
unsigned int ExtractIntFromStr(char* string);
bool ContainsParentheses(char* string);



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/
int main()
{
    char* expression = "(999+((55+66)+(77+88))";
    char left[255];
    char right[255];
    char op;

    calculate(expression, left, right, &op);

  return 0;
}


unsigned int calculate(char* expression, char* left, char* right, char* op)
{
    *left = 0;
    *right = 0;
    unsigned int left_val = 0, right_val = 0;
    op = SplitMainExpression(expression+1);
    printf("Operator: %c\n", *op);
    StringCopy((expression+1), left);
    printf("Left: %s\n", left);
    StringCopy((op+1), right);
    printf("Right: %s\n", right);

    if (ContainsParentheses(left) == false)
    {
        left_val = ExtractIntFromStr(left);
        printf("Left val: %u\n", left_val);
    }

    if (ContainsParentheses(right) == false)
    {
        right_val = ExtractIntFromStr(right);
        printf("Right val: %u\n", right_val);
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

        if (*(expression+1) >= '0' && *(expression+1) <= '9')
        {
            expression++;
        }

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
