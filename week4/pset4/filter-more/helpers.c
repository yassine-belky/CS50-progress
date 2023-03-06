#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE avg_tmp;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            avg_tmp = (image[row][col].rgbtBlue + image[row][col].rgbtRed + image[row][col].rgbtGreen) / 3;
            image[row][col].rgbtBlue = avg_tmp;
            image[row][col].rgbtRed = avg_tmp;
            image[row][col].rgbtGreen = avg_tmp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap_tmp;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            swap_tmp = image[row][col];
            image[row][col] = image[row][width - col];
            image[row][width - col] = swap_tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*image_cp)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image_cp[row][col] = get_blurred_pixel(row, col, height, width, image, 3);
        }
    }

    copy_image(height, width, image_cp, image);
    free(image_cp);
    return;
}

void copy_image(int height, int width, RGBTRIPLE source[height][width], RGBTRIPLE dest[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            dest[row][col] = source[row][col];
        }
    }
}

RGBTRIPLE get_blurred_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width], int kernel_size)
{
    RGBTRIPLE res;
    res.rgbtBlue = res.rgbtGreen = res.rgbtRed = 0x00;

    for (int row_eps = -1; row_eps <= 1; row_eps++)
    {
        for (int col_eps = -1; col_eps <= 1; col_eps++)
        {
            res.rgbtBlue += image[row + row_eps][col + col_eps].rgbtBlue / (kernel_size * kernel_size);
            res.rgbtGreen += image[row + row_eps][col + col_eps].rgbtGreen / (kernel_size * kernel_size);
            res.rgbtRed += image[row + row_eps][col + col_eps].rgbtRed / (kernel_size * kernel_size);
        }
    }

    return res;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*image_cp)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image_cp[row][col] = get_edged_pixel(row, col, height, width, image);
        }
    }

    copy_image(height, width, image_cp, image);
    free(image_cp);
    return;
}

RGBTRIPLE get_edged_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edged_pixel;
    RGBGRADIENT col_grad = get_col_gradient(row, col, height, width, image);
    RGBGRADIENT row_grad = get_row_gradient(row, col, height, width, image);

    edged_pixel.rgbtBlue = cap_value((int)sqrt(col_grad.rgbtBlue * col_grad.rgbtBlue + row_grad.rgbtBlue * row_grad.rgbtBlue));
    edged_pixel.rgbtGreen = cap_value((int)sqrt(col_grad.rgbtGreen * col_grad.rgbtGreen + row_grad.rgbtGreen * row_grad.rgbtGreen));
    edged_pixel.rgbtRed = cap_value((int)sqrt(col_grad.rgbtRed * col_grad.rgbtRed + row_grad.rgbtRed * row_grad.rgbtRed));

    return edged_pixel;
}

RGBGRADIENT get_col_gradient(int row, int col, int height, int width, RGBTRIPLE image[height][width])
{
    RGBGRADIENT col_grad;

    col_grad.rgbtBlue = (image[row - 1][col + 1].rgbtBlue - image[row - 1][col - 1].rgbtBlue) + 2 * (image[row][col + 1].rgbtBlue - image[row][col - 1].rgbtBlue) + (image[row + 1][col + 1].rgbtBlue - image[row + 1][col - 1].rgbtBlue);
    col_grad.rgbtGreen = (image[row - 1][col + 1].rgbtGreen - image[row - 1][col - 1].rgbtGreen) + 2 * (image[row][col + 1].rgbtGreen - image[row][col - 1].rgbtGreen) + (image[row + 1][col + 1].rgbtGreen - image[row + 1][col - 1].rgbtGreen);
    col_grad.rgbtRed = (image[row - 1][col + 1].rgbtRed - image[row - 1][col - 1].rgbtRed) + 2 * (image[row][col + 1].rgbtRed - image[row][col - 1].rgbtRed) + (image[row + 1][col + 1].rgbtRed - image[row + 1][col - 1].rgbtRed);

    return col_grad;
}

RGBGRADIENT get_row_gradient(int row, int col, int height, int width, RGBTRIPLE image[height][width])
{
    RGBGRADIENT row_grad;
    row_grad.rgbtBlue = (image[row + 1][col - 1].rgbtBlue - image[row - 1][col - 1].rgbtBlue) + 2 * (image[row + 1][col].rgbtBlue - image[row - 1][col].rgbtBlue) + (image[row + 1][col + 1].rgbtBlue - image[row - 1][col + 1].rgbtBlue);
    row_grad.rgbtGreen = (image[row + 1][col - 1].rgbtBlue - image[row - 1][col - 1].rgbtBlue) + 2 * (image[row + 1][col].rgbtBlue - image[row - 1][col].rgbtBlue) + (image[row + 1][col + 1].rgbtBlue - image[row - 1][col + 1].rgbtBlue);
    row_grad.rgbtRed = (image[row + 1][col - 1].rgbtBlue - image[row - 1][col - 1].rgbtBlue) + 2 * (image[row + 1][col].rgbtBlue - image[row - 1][col].rgbtBlue) + (image[row + 1][col + 1].rgbtBlue - image[row - 1][col + 1].rgbtBlue);

    return row_grad;
}

BYTE cap_value(int value)
{
    if (value > 255)
    {
        return 0x11;
    }
    else
    {
        return (BYTE)value;
    }
}
