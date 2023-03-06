#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// Helper functions for the blur filter
void copy_image(int height, int width, RGBTRIPLE source[height][width], RGBTRIPLE dest[height][width]);
RGBTRIPLE get_blurred_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width], int kernel_size);

// Helper functions for the edge filter
RGBGRADIENT get_col_gradient(int row, int col, int height, int width, RGBTRIPLE image[height][width]);
RGBGRADIENT get_row_gradient(int row, int col, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE get_edged_pixel(int row, int col, int height, int width, RGBTRIPLE image[height][width]);
BYTE cap_value(int value);
