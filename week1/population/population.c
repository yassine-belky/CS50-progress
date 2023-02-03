#include <cs50.h>
#include <stdio.h>

int get_nbr_years(int start_size, int end_size);

int main(void)
{
    int start_size = get_int("Start Size : ");
    int end_size = get_int("End Size : ");
    int nbr_years = get_nbr_years(start_size, end_size);
    printf("Years : %i\n", nbr_years);
}

int get_nbr_years(int start_size, int end_size)
{
    int current_size = start_size;
    int nbr_years = 0;
    do
    {
        current_size = current_size + (current_size / 3) - (current_size / 4);
        nbr_years++;
    } while (current_size < end_size);
    return nbr_years;
}