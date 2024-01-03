#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int x = 0;
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            x = round((image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue) / 3.0);
            image[row][col].rgbtRed = x;
            image[row][col].rgbtGreen = x;
            image[row][col].rgbtBlue = x;
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int find_min(int a, int b);

    int r = 0;
    int g = 0;
    int b = 0;

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            r = round(.393 * image[row][col].rgbtRed + .769 * image[row][col].rgbtGreen + .189 * image[row][col].rgbtBlue);
            g = round(.349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen + .168 * image[row][col].rgbtBlue);
            b = round(.272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen + .131 * image[row][col].rgbtBlue);

            image[row][col].rgbtRed = find_min(r, 255);
            image[row][col].rgbtGreen = find_min(g, 255);
            image[row][col].rgbtBlue = find_min(b, 255);
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width / 2; col++)
        {
            copy[row][col] = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = copy[row][col];
        }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    int r, g, b;
    float count;
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            r = 0;
            g = 0;
            b = 0;
            count = 0;
            for (int i = row - 1; i <= row + 1; i++)
                for (int j = col - 1; j <= col + 1; j++)
                    if (i >= 0 && j >= 0 && i < height && j < width)
                    {
                        r += copy[i][j].rgbtRed;
                        g += copy[i][j].rgbtGreen;
                        b += copy[i][j].rgbtBlue;
                        count++;
                    }
            image[row][col].rgbtRed = round(r / count);
            image[row][col].rgbtGreen = round(g / count);
            image[row][col].rgbtBlue = round(b / count);
        }
    return;
}

int find_min(int a, int b)
{
    if (a <= b)
        return a;
    else
        return b;
}