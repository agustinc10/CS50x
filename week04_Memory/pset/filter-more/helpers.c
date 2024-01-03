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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int find_min(int a, int b);

    int kx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int ky[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int Gxr, Gxg, Gxb;
    int Gyr, Gyg, Gyb;
    int r, g, b;

    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            copy[row][col] = image[row][col];

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
        {
            Gxr = 0;
            Gxg = 0;
            Gxb = 0;
            Gyr = 0;
            Gyg = 0;
            Gyb = 0;
            r = 0;
            g = 0;
            b = 0;

            for (int i = -1; i < 2; i++)
                for (int j = -1; j < 2; j++)
                    if (row + i >= 0 && col + j >= 0 && row + i < height && col + j < width)
                    {
                        Gxr += copy[row + i][col + j].rgbtRed * kx[i + 1][j + 1];
                        Gxg += copy[row + i][col + j].rgbtGreen * kx[i + 1][j + 1];
                        Gxb += copy[row + i][col + j].rgbtBlue * kx[i + 1][j + 1];

                        Gyr += copy[row + i][col + j].rgbtRed * ky[i + 1][j + 1];
                        Gyg += copy[row + i][col + j].rgbtGreen * ky[i + 1][j + 1];
                        Gyb += copy[row + i][col + j].rgbtBlue * ky[i + 1][j + 1];
                    }

            r = round(sqrt(pow(Gxr, 2) + pow(Gyr, 2)));
            g = round(sqrt(pow(Gxg, 2) + pow(Gyg, 2)));
            b = round(sqrt(pow(Gxb, 2) + pow(Gyb, 2)));

            image[row][col].rgbtRed = find_min(r, 255);
            image[row][col].rgbtGreen = find_min(g, 255);
            image[row][col].rgbtBlue = find_min(b, 255);
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
