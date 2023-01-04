/* Perhaps the simplest way to represent an image is with a grid of pixels (i.e., dots), each of which can be of a different color. 
For black-and-white images, we thus need 1 bit per pixel, as 0 could represent black and 1 could represent white.
In this sense, then, is an image just a bitmap (i.e., a map of bits). For more colorful images, you simply need more bits per pixel. 
A file format (like BMP, JPEG, or PNG) that supports “24-bit color” uses 24 bits per pixel. (BMP actually supports 1-, 4-, 8-, 16-, 24-, and 32-bit color.)
A 24-bit BMP uses 8 bits to signify the amount of red in a pixel’s color, 8 bits to signify the amount of green in a pixel’s color, 
and 8 bits to signify the amount of blue in a pixel’s color. If you’ve ever heard of RGB color, well, there you have it: red, green, blue.
If the R, G, and B values of some pixel in a BMP are, say, 0xff, 0x00, and 0x00 in hexadecimal, that pixel is purely red, as 0xff 
(otherwise known as 255 in decimal) implies “a lot of red,” while 0x00 and 0x00 imply “no green” and “no blue,” respectively.

What does it even mean to filter an image? You can think of filtering an image as taking the pixels of some original image, 
and modifying each pixel in such a way that a particular effect is apparent in the resulting image.
Implement the functions in helpers.c such that a user can apply grayscale, reflection, blur, or edge detection filters to their images.
- grayscale function should take an image and turn it into a black-and-white version of the same image. To convert a pixel to grayscale, 
we can take the average of the red, green, and blue values to determine what shade of grey to make the new pixel. If you apply that to each pixel 
in the image, the result will be an image converted to grayscale.
- reflect function should take an image and reflect it horizontally. Some filters might also move pixels around. Reflecting an image, for example, 
is a filter where the resulting image is what you would get by placing the original image in front of a mirror. So any pixels on the left side of 
the image should end up on the right, and vice versa.
- blur function should take an image and turn it into a box-blurred version of the same image. There are a number of ways to create the effect 
of blurring or softening an image. For this problem, we’ll use the “box blur,” which works by taking each pixel and, for each color value, 
giving it a new value by averaging the color values of neighboring pixels. The new value of each pixel would be the average of the values of 
all of the pixels that are within 1 row and column of the original pixel (forming a 3x3 box).
- The edges function should take an image and highlight the edges between objects, according to the Sobel operator. In artificial intelligence 
algorithms for image processing, it is often useful to detect edges in an image: lines in the image that create a boundary between one object and another. 
One way to achieve this effect is by applying the Sobel operator to the image.nLike image blurring, edge detection also works by taking each pixel, 
and modifying it based on the 3x3 grid of pixels that surrounds that pixel. But instead of just taking the average of the nine pixels, the Sobel operator 
computes the new value of each pixel by taking a weighted sum of the values for the surrounding pixels. And since edges between objects could take 
place in both a vertical and a horizontal direction, you’ll actually compute two weighted sums: one for detecting edges in the x direction, and one 
for detecting edges in the y direction. In particular, you’ll use the following two “kernels”: Sobel kernels - google it */

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
