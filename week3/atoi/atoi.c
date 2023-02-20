#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int length = strlen(input);
    if (length == 1)
    {
        return input[0] - '0';
    }
    else
    {
        char last_char = input[length - 1];
        int last_digit = last_char - '0';
        char remainder[length - 1];
        for (int i = 0; i < length - 1; i++)
        {
            remainder[i] = input[i];
        }
        return last_digit + 10 * convert(remainder);
    }
}