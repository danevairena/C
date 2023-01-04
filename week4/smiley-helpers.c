/* Open up helpers.c and notice that the colorize function is incomplete. Note that the image’s height, width and a two-dimensional array 
of pixels is set up as the input parameters for this function. You are to implement this function to change all the black pixels in the image 
to a color of your choosing. */

#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    //loop for height of image
    for (int i = 0; i < height; i++)
    {
        //loop for width of image
        for (int j = 0; j < width; j++)
        {
            //check if pixel is black and change it's values to pink color
            if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
            {
                image[i][j].rgbtBlue = 147;
                image[i][j].rgbtGreen = 112;
                image[i][j].rgbtRed = 219;
            }
        }
    }
}
