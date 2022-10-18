#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

bool only_digits(string key);
int sum_key(string key);
string rotate_text(string plaint, string chiphert, int key);

/*At the time the user executes the program, they should decide, by providing a command-line argument,
what the key should be in the secret message they’ll provide at runtime.
We shouldn’t necessarily assume that the user’s key is going to be a number;
though you may assume that, if it is a number, it will be a positive integer. Your program must preserve case: .
After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.*/

int main(int argc, string argv[])
{

    // Make sure program was run with just one command-line argument.If a user doesn’t cooperate the program should remind the user how to use the program
    if (argc != 2)
    {
        printf("Error - nmber of arguments\nUsage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    int result = only_digits(argv[1]);
    if (result != true)
    {
        printf("Command-Line arguments error.\nUsage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    string key = argv[1];
    int keynum = sum_key(key);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // rotate_text iterates over every char in the user’s plaintext, calling rotate on each, and printing the return value thereof
    string ciphertext = 0;
    strcpy(ciphertext, plaintext);
    strcpy(ciphertext, rotate_text(plaintext, ciphertext, keynum));
    printf("chiphertext: %s", ciphertext);

    //print new line and return 0 for success
    printf("\n");
    return 0;
}




bool only_digits(string key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (isdigit(key[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

string rotate_text(string plaint, string ciphert, int key)
{
    int temp = 0;
    //checks every character in the string and if alhabetical converts it
    for (int i = 0; ciphert[i] != '\0'; i++)
    {
        if (isalpha(ciphert[i]) != 0)
        {
            temp = atoi(&ciphert[i]);
            temp = temp + key;
            ciphert[i] = temp + '0';
        }
    }
    //checking upper and lowercase
    for (int i = 0; plaint[i] != '\0'; i++)
    {
        if (isalpha(plaint[i]) != 0)
        {
            if (isupper(plaint[i]) != 0)
            {
                ciphert[i] = toupper(ciphert[i]);
            }
            else
            {
                ciphert[i] = tolower(ciphert[i]);
            }
        }
    }
    return ciphert;
}
int sum_key(string key)
{
    int count = 0;
    int i = 0;
    for (i = 0; key[i] != '\0'; i++)
    {
        count++;
    }
    int sum = key[i - 1];
    for (int j = 1; key[j] != '\0'; i++)
    {
        sum = sum + key[j] * pow(10, (double)count);
        count--;
    }
    return sum;
}
