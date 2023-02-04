#include <cs50.h>
#include <stdio.h>

void print_credit_card_name(long number);
int get_updated_luhn_sum(int luhn_sum, int remainder, int digits_counter);
void print_valid_credit_card_name(int start_digit, int nbr_digits);

int main(void)
{
    long number = get_long("Number : ");
    print_credit_card_name(number);
}

void print_credit_card_name(long number)
{
    long quotient = number;
    int remainder;
    int luhn_sum = 0;
    int digits_counter = 0;

    do
    {
        remainder = quotient % 10;
        luhn_sum = get_updated_luhn_sum(luhn_sum, remainder, digits_counter);
        quotient /= 10;
        digits_counter++;
    } while (quotient != 0);

    if (luhn_sum % 10)
    {
        printf("INVALID\n");
    }
    else
    {
        print_valid_credit_card_name(remainder, digits_counter);
    }
}

int get_updated_luhn_sum(int luhn_sum, int remainder, int digits_counter)
{
    if (digits_counter % 2)
    {
        int prod = 2 * remainder;
        luhn_sum = luhn_sum + prod / 10 + prod % 10;
    }
    else
    {
        luhn_sum = luhn_sum + remainder;
    }
    return luhn_sum;
}

void print_valid_credit_card_name(int start_digit, int nbr_digits)
{
    if ((nbr_digits == 13) || ((nbr_digits == 16) && (start_digit == 4)))
    {
        printf("VISA\n");
    }
    else if (nbr_digits == 15)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("MASTERCARD\n");
    }
}
