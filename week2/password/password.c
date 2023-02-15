#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
    bool has_uppercase_char = false;
    bool has_lowercase_char = false;
    bool has_number_char = false;
    bool has_symbol_char = false;
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (islower(password[i]))
        {
            has_lowercase_char = true;
        }
        else if (isupper(password[i]))
        {
            has_uppercase_char = true;
        }
        else if (isdigit(password[i]))
        {
            has_number_char = true;
        }
        else
        {
            has_symbol_char = true;
        }
    }

    return (has_lowercase_char && has_uppercase_char && has_number_char && has_symbol_char);
}
