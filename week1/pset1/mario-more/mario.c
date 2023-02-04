#include <cs50.h>
#include <stdio.h>

void print_pyramid(int height);
void print_single_line(int depth, int height);

int main(void)
{
    int height = get_int("Height : ");
    if (1 <= height && height <= 8)
    {
        print_pyramid(height);
    }
    else
    {
        main();
    }
}

void print_pyramid(int height)
{
    for (int depth = 1; depth <= height; depth++)
    {
        print_single_line(depth, height);
    }
}

void print_single_line(int depth, int height)
{
    bool is_in_left, is_in_middle, is_in_right;
    for (int pos = 1; pos <= 2 * height + 2; pos++)
    {
        is_in_left = ((1 <= pos) && (pos <= height - depth));
        is_in_middle = ((height < pos) && (pos <= height + 2));
        is_in_right = ((height + depth + 3 <= pos) && (pos <= 2 * height + 2));
        if (is_in_left || is_in_middle || is_in_right)
        {
            printf(" ");
        }
        else
        {
            printf("#");
        }
    }
    printf("\n");
}