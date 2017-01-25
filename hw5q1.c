#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/* DEFINEs*/
/* -------------------------------------------------------- */

/* MAX_EXPRESSION_LENGTH does not include the terminating null character */
#define MAX_EXPRESSION_LENGTH 255


/* FUNCTIONS */
char* SplitMainExpression(char* expression);
bool calculate(char* expression,
               unsigned int modulus, unsigned int* result);
void StringCopy(char *source, char *destination);
unsigned int ExtractIntFromStr(char* string);
bool ContainsParentheses(char* string);
bool MathFunc(unsigned long long val_1, unsigned long long val_2,
              char operation, unsigned int modulus, unsigned int* result);
/* -------------------------------------------------------- */

/*
   calculate_modular_expression - calculates a modular expression in the form
   (
*/
bool calculate_modular_expression(unsigned int modulus,
                                  char* expression,
                                  unsigned int* expression_result)
{

    return calculate(expression, modulus, expression_result);
}


/*
   get_input - Gets program input (modulus, expression) from standard input.
   This function prints a message to the standard output and gets the input
   (modulus, expression) from standard input.
   This function does not validate the inputs other than basic validation.
   Inputs: modulus_ptr - pointer where the function stores the modulus.
           expression - pointer to an array of character where the function
           stores the expression string.
   Returns true if and only if the function gets the inputs successfully.
*/
bool get_input(unsigned int* modulus_ptr, char* expression)
{
    printf("Please enter the modulus and an expression (separated by a space).\n");
    return (scanf("%u%s", modulus_ptr, expression) == 2);
}


/*
   validate_input - Validates program input (modulus).
   Returns true if and only if the input is valid.
*/
bool validate_input(unsigned int modulus)
{
    /* The modulus must be greater than 1 */
    return (modulus > 1);
}


/*
   main function.
   Inputs: none.
   Returns 0 when the program run successfully.
   Any other value indicates an error.
*/
int main()
{
    unsigned int modulus; /* modulus */
    char expression[MAX_EXPRESSION_LENGTH+1];
    unsigned int expression_result;

    if (!get_input(&modulus, expression))
    {
        printf("ERROR: could not get input\n");
        return 1;
    }

    if (!validate_input(modulus))
    {
        printf("ERROR: modulus is out of range\n");
        return 2;
    }

    if (!calculate_modular_expression(modulus, expression, &expression_result))
    {
        printf("ERROR: the modular expression is invalid\n");
        return 3;
    }

    printf("%u\n", expression_result);

    return 0;
}


bool calculate(char* expression, unsigned int modulus,
               unsigned int* result)
{
    char left[MAX_EXPRESSION_LENGTH] = {0};
    char right[MAX_EXPRESSION_LENGTH] = {0};
    char* op = SplitMainExpression(expression+1);
    unsigned long long left_val = 0, right_val = 0;
    while (*op == '(')
    {
        op--;
    }
    while (*op == ')')
    {
        op++;
    }

    StringCopy((expression+1), left);
    StringCopy((op+1), right);

    if (ContainsParentheses(left) == false)
    {
        left_val = ExtractIntFromStr(left);
    }

    if (ContainsParentheses(right) == false)
    {
        right_val = ExtractIntFromStr(right);
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

    return MathFunc(left_val, right_val, *op, modulus, result);
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
    }
    while (paren_ctr != 0 || (*source >= '0' && *source <= '9'));

    *(destination) = '\0';
}

char* SplitMainExpression(char* expression)
{
    int parenthesis_counter = 0;
    while (*expression != '\0')
    {

        if (*(expression) >= '0' && *(expression) <= '9')
        {
            expression++;
        }

        if (*expression == '(')
        {
            parenthesis_counter++;
        }
        else if (*expression == ')')
        {
            parenthesis_counter--;
        }

        if (parenthesis_counter == 0 && !(*(expression) >= '0' &&
                                           *(expression) <= '9'))
        {
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


bool MathFunc(unsigned long long val_1, unsigned long long val_2,
              char operation, unsigned int modulus, unsigned int* result)
{
    val_1 = val_1%modulus;
    val_2 = val_2%modulus;

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
        return false;
    }

    raw_result = raw_result%modulus;

    if (raw_result > UINT_MAX)
    {
        printf("Error: result exceeds range of unsigned int.\n");
        return false;
    }

    *result = (unsigned int)raw_result;

    return true;
}
