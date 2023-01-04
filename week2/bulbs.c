/* Light bulbs can only be on or off. In other words, light bulbs represent two possible states; either the bulb is on, or the bulb is off, 
just as binary numbers are either 1 or 0. We’ll have to find a way to encode text as a sequence of binary numbers.

Let’s write a program called bulbs that takes a message and converts it to a set of bulbs that we could show 
to an unsuspecting audience. We’ll do it in two steps:
- The first step consists of turning the text into decimal numbers. Let’s say we want to encode the message HI!. Luckily, we already have a 
convention in place for how to do this, ASCII. Notice that H is represented by the decimal number 72, I is represented by 73, and ! is represented by 33.
- The next step involves taking our decimal numbers (like 72, 73, and 33) and converting them into equivalent binary numbers, which only use 0s and 1s. 
For the sake of having a consistent number of bits in each of our binary numbers, assume that each decimal is represented with 8 bits. 
72 is 01001000, 73 is 01001001, and 33 is 00100001.
- Lastly, we’ll interpret these binary numbers as instructions for the light bulbs on stage; 0 is off, 1 is on. (You’ll find that bulbs.c includes 
a print_bulb function that’s been implemented for you, which takes in a 0 or 1 and outputs emoji representing light bulbs.)*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    //get message from user
    char *message = get_string("Message: ");
    //loop though every character in the message
    for (int i = 0; message[i] != '\0'; i++)
    {
        //char to ascii value
        int n = (int) message[i];

        //array to store binary number
        int bulbs[BITS_IN_BYTE];

        //setting all bulbs to 0
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            bulbs[j] = 0;
        }

        // counter for binary array
        for (int j = BITS_IN_BYTE - 1; n > 0; j--)
        {
            // storing remainder in binary array
            int tmp = n % 2;
            bulbs[j] = tmp;
            n = n / 2;
        }

        //loop for printing
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(bulbs[j]);
        }
        //then print new line
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
