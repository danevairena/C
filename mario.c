#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    //ask how tall pyramid should be and check if number is between 1 and 8
    do
    {
        n = get_int("How tall the pyramid should be? ");
    }
    while (n < 1 || n > 8);

    //for each row
    for (int row = 0; row < n; row++)
    {
        //number of space tabs
        for (int spacetab = n; spacetab >= row; spacetab --)
        {
            printf(" ");
        }

        //number of sybols
        for (int rhash = 0; rhash <= row; rhash++)
        {
            printf("#");
        }
        printf("  ");
        for (int lhash = 0; lhash <= row; lhash++)
        {
            printf("#");
        }

        printf("\n");

    }

}