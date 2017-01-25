#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

/* DEFINEs*/
/* -------------------------------------------------------- */

/* MAX_EXPRESSION_LENGTH does not include the terminating null character */
#define MAX_EXPRESSION_LENGTH 255


/* FUNCTIONS */
char* SplitExpression(char* expression);
void OperandCopy(char *source, char *destination);
unsigned int ExtractIntFromStr(char* string);
bool ContainsParentheses(char* string);
bool PerformArithmetic(unsigned long long val_1, unsigned long long val_2,
              char operation, unsigned int modulus, unsigned int* result);
bool GetNumbersFromExpression(char* left, char* right,
                              unsigned long long* left_val_ptr,
                              unsigned long long* right_val_ptr);
void Func(unsigned int modulus, char* left, char* right,
          unsigned long long* left_val_ptr,
          unsigned long long* right_val_ptr,
          unsigned int* expression_result);
/* -------------------------------------------------------- */

/*
   calculate_modular_expression - calculates a modular expression in the form
   MODULUS (A [OPERATOR] B).
*/
bool calculate_modular_expression(unsigned int modulus,
                                  char* expression,
                                  unsigned int* expression_result)
{
    char left[MAX_EXPRESSION_LENGTH+1] = {0};
    char right[MAX_EXPRESSION_LENGTH+1] = {0};
    char* operation = SplitExpression(expression+1);
    unsigned long long left_val = 0, right_val = 0;
    while (*operation == '(')
    {
        operation--;
    }
    while (*operation == ')')
    {
        operation++;
    }

    OperandCopy((expression+1), left);
    OperandCopy((operation+1), right);

    if (!GetNumbersFromExpression(left, right, &left_val, &right_val))
    {
        return false;
    }

    Func(modulus, left, right, &left_val, &right_val, expression_result);

    return PerformArithmetic(left_val, right_val, *operation, modulus,
                             expression_result);
}



void Func(unsigned int modulus, char* left, char* right,
          unsigned long long* left_val_ptr,
          unsigned long long* right_val_ptr,
          unsigned int* expression_result)
{
    if (*left_val_ptr == 0)
    {
        calculate_modular_expression(modulus, left, expression_result);
        *left_val_ptr = *expression_result;
    }

    if (*right_val_ptr == 0)
    {
        calculate_modular_expression(modulus, right, expression_result);
        *right_val_ptr = *expression_result;
    }
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

/*This function, given pointers to the left and right operands of an
expression and pointers to the corresponding value variables, checks if
each operand is a single number. If an operand is a single number,
its value is extracted from the string and saved to the value variable.
The function returns false if the operand is not a number. If the operand
is a legal integer (positive), the function returns true.*/
bool GetNumbersFromExpression(char* left, char* right,
                              unsigned long long* left_val_ptr,
                              unsigned long long* right_val_ptr)
{
    if (ContainsParentheses(left) == false)
    {
        *left_val_ptr = ExtractIntFromStr(left);
        if (*left_val_ptr == 0)
        {
            return false;
        }
    }

    if (ContainsParentheses(right) == false)
    {
        *right_val_ptr = ExtractIntFromStr(right);
        if (*right_val_ptr == 0)
        {
            return false;
        }
    }

    return true;
}


/*This function, given a source string and a destination string, copies
a single operand (left or right) from the source to the destination.*/
void OperandCopy(char *source, char *destination)
{
    int parentheses_counter = 0;
    do
    {
        if (*source == '(')
        {
            parentheses_counter++;
        }

        if (*source == ')')
        {
            parentheses_counter--;
        }

        *destination = *source;

        source++;
        destination++;
    }
    while (parentheses_counter != 0 || (*source >= '0' && *source <= '9'));

    *(destination) = '\0';
}

/*This function, given an expression with two operands separated by an
operator, finds the address of the operator (the "middle" of the
expression) and returns it.*/
char* SplitExpression(char* expression)
{
    int parentheses_counter = 0;
    while (*expression != '\0')
    {

        if (*(expression) >= '0' && *(expression) <= '9')
        {
            expression++;
        }

        if (*expression == '(')
        {
            parentheses_counter++;
        }
        else if (*expression == ')')
        {
            parentheses_counter--;
        }

        if (parentheses_counter == 0 && !(*(expression) >= '0' &&
                                          *(expression) <= '9'))
        {
            return expression;
        }

        expression++;
    }

    return expression;
}

/*This function, given a string, extracts an unsigned integer from the
string and returns it. If no integer is found, the function returns 0.
(Returning 0 is based on the assumption that all numbers handled will be
 positive.)*/
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


/*This function, given a string, reads through it and checks whether or not
it contains parentheses.*/
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

/*This function, given two positive values, the operator between them,
the modulus, and a pointer to the result, calculates the result of the
mathematical operation and stores it in the result variable.
The function returns false if the operator is not '+' or '*'.
Otherwise, it returns true. */
bool PerformArithmetic(unsigned long long val_1, unsigned long long val_2,
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

    *result = (unsigned int)raw_result;

    return true;
}
