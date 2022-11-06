#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //height - row / width - column
    //loop for every row
    for (int i = 0; i < height; i++)
    {
        //loop for every column
        for (int j = 0; j < width; j++)
        {
            //converting pixel's values to float
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            //computing avg value
            int average = round((red + green + blue) / 3.0);

            //updating values
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop for every row
    for (int i = 0; i < height; i++)
    {
        //loop for every column
        for (int j = 0; j < width; j++)
        {
            //computing new values
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            //checking new values
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            //updating values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop for every row
    for (int i = 0; i < height; i++)
    {
        //checking if width is dividable to 2 parts without remainder
        if (width % 2 == 0)
        {
            //loop for every column
            for (int j = 0; j < width / 2; j++)
            {
                //creating temporary pixel to store values for swapping
                RGBTRIPLE temp[height][width];

                //pixels swap
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }

        //dividing width with remainder
        else
        {
            //loop for every column
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                //new temporary pixel to store values for swapping
                RGBTRIPLE temp[height][width];

                //pixels swap
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = temp[i][j];
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //new array to store new pixels's values
    RGBTRIPLE newimage[height][width];

    //loop for every row
    for (int i = 0; i < height; i++)
    {
        //loop for every column
        for (int j = 0; j < width; j++)
        {
            //temporary values to store average sum
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;

            //sum numbers counter
            int counter = 0;

            //inner loop for surrounding pixels
            //height
            for (int h = -1; h <= 1; h++)
            {
                //width
                for (int w = -1; w <= 1; w++)
                {
                    //check if surrounding pixel is out of range
                    if (i + h >= 0 && i + h <= height - 1 && j + w >= 0 && j + w <= width - 1)
                    {
                        //sum values
                        sumBlue += image[i + h][j + w].rgbtBlue;
                        sumGreen += image[i + h][j + w].rgbtGreen;
                        sumRed += image[i + h][j + w].rgbtRed;
                        counter++;
                    }
                }
            }

            //computing new avg value to temp image
            newimage[i][j].rgbtBlue = round(sumBlue / counter);
            newimage[i][j].rgbtGreen = round(sumGreen / counter);
            newimage[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise ints
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;
            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}
