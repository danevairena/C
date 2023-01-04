/* Supposedly, Caesar (yes, that Caesar) used to “encrypt” (i.e., conceal in a reversible way) confidential messages 
by shifting each letter therein by some number of places. For instance, he might write A as B, B as C, C as D, …, and, 
wrapping around alphabetically, Z as A. And so, to say HELLO to someone, Caesar might write IFMMP instead. 
Upon receiving such messages from Caesar, recipients would have to “decrypt” them by shifting letters 
in the opposite direction by the same number of places.
The secrecy of this “cryptosystem” relied on only Caesar and the recipients knowing a secret, the number of places 
by which Caesar had shifted his letters (e.g., 1). Not particularly secure by modern standards, but, hey, 
if you’re perhaps the first in the world to do it, pretty secure!
Unencrypted text is generally called plaintext. Encrypted text is generally called ciphertext. And the secret used is called a key.

Design and implement a program, caesar, that encrypts messages using Caesar’s cipher.
- Implement your program in a file called caesar.c in a directory called caesar.
- Your program must accept a single command-line argument, a non-negative integer. Let’s call it  for the sake of discussion.
- If your program is executed without any command-line arguments or with more than one command-line argument, 
your program should print an error message of your choice (with printf) and return from main a value 
of 1 (which tends to signify an error) immediately.
- If any of the characters of the command-line argument is not a decimal digit, your program should print the message 
Usage: ./caesar key and return from main a value of 1.
- Do not assume that  will be less than or equal to 26. Your program should work for all non-negative integral values of  less than . 
In other words, you don’t need to worry if your program eventually breaks if the user chooses a value for  that’s too big or 
almost too big to fit in an int. (Recall that an int can overflow.) But, even if  is greater than , alphabetical characters in your 
program’s input should remain alphabetical characters in your program’s output. For instance, if  is , A should not become \ even though \ 
is  positions away from A in ASCII, per asciichart.com; A should become B, since B is  positions away from A, provided you wrap around from Z to A.
- Your program must output plaintext: (with two spaces but without a newline) and then prompt the user for a string of plaintext (using get_string).
- Your program must output ciphertext: (with one space but without a newline) followed by the plaintext’s corresponding ciphertext, 
with each alphabetical character in the plaintext “rotated” by k positions; non-alphabetical characters should be outputted unchanged.
- Your program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, 
though rotated, must remain lowercase letters.
- After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main. */

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
