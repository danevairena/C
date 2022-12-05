/* In a substitution cipher, we “encrypt” (i.e., conceal in a reversible way) a message by replacing every letter with another letter. 
To do so, we use a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when we encrypt it. 
To “decrypt” the message, the receiver of the message would need to know the key, so that they can reverse the process: 
translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).
A key, for example, might be the string NQXPOMAFTRHLZGECYJIUWSKDVB. This 26-character key means that A (the first letter of the alphabet) 
should be converted into N (the first character of the key), B (the second letter of the alphabet) should be converted 
into Q (the second character of the key), and so forth.
A message like HELLO, then, would be encrypted as FOLLE, replacing each of the letters according to the mapping determined by the key.

Let’s write a program called substitution that enables you to encrypt messages using a substitution cipher. 
At the time the user executes the program, they should decide, by providing a command-line argument, on what the key should be 
in the secret message they’ll provide at runtime.
- If your program is executed without any command-line arguments or with more than one command-line argument, your program should 
print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
- If the key is invalid (as by not containing 26 characters, containing any character that is not an alphabetic character, or not containing 
each letter exactly once), your program should print an error message of your choice (with printf) and return from main a value of 1 immediately.
- Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
- Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical 
character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
- Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
- After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main. */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include<ctype.h>

bool key_check(string key);
string inicialize_alphabet(void);
string swap_letters(string text, string alphabet, string key);
bool key_uniq(string key);
string toupcase(string key);

int main(int argc, string argv[])
{
    // Your program must accept a single command-line argument, the key to use for the substitution
    if (argc != 2)
    {
        printf("Command-Line arguments error.\nUsage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //checking the key and convert all letters to uppercase
    int result = key_check(key);
    if (result != true)
    {
        return 1;
    }

    //check if key contains only unique characters
    result = key_uniq(key);
    if (result != true)
    {
        return 1;
    }
    key = toupcase(key);

    //inicializing string for the alphabet ABSDEFGHIJKLMNOPRSTUVWXYZ
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //check if alphabet and kay have the same lenght
    if (strlen(alphabet) != strlen(key))
    {
        printf("Error - invalid key.");
        return 1;
    }

    //prompt the user for a string of plaintext
    string plaintext = get_string("plaintext: ");

    //swap the letters of the plaintext with keyletters and print the resut
    string ciphertext = swap_letters(plaintext, alphabet, key);
    printf("\nciphertext: %s\n", ciphertext);

    return 0;
}

bool key_check(string key)
{
   //check if key contains 26 character, else printing error message
    for (int i = 0; key[i] < 26; i++)
    {
        printf("Keycheck\n");
        if (key[i] == '\0')
        {
            printf("Error - Key must contain 26 characters.");
            return false;
        }
        //check if key contains only alphabetical characters
        else if (isalpha(key[i]) == 0)
        {
            printf("Error - Key must contain 26 characters.");
            return false;
        }
        else  if (key[i] != '\0')
        {
            return false;
        }
    }
    return true;
}

bool key_uniq(string key)
{
    int i = 0, j = 0;
    //takes the firs letter and compares it to the rest of the key, then moves to the second letter and ect.
    for (i = 0; key[i] != '\0'; i++)
    {
        for (j = i + 1; key[j] != '\0'; j++)
        {
            //uppercases both of the checked letters. Not to be keysensitive fot upper and lower case
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Error - Key must contain 26 unique characters.");
                return false;
            }
        }
    }
    return true;
}

string swap_letters(string text, string alphabet, string key)
{
    //checks plaintext character by character.
    int i = 0, j = 0;
    for (i = 0; text[i] != '\0'; i++)
    {
        //Checks if char is alphabetical.
        if (isalpha(text[i]) != 0)
        {
            //is lower or upper letter
            if (isupper(text[i]) == 0)
            {
                //Compares the letter to alphabet to find letter's position and replaes it with the keyletter.
                for (j = 0; alphabet[j] != toupper(text[i]); j++);
                text[i] = key[j];
                text[i] = tolower(text[i]);
            }
            else
            {
                //Compares the letter to alphabet to find letter's position and replaes it with the keyletter.
                for (j = 0; alphabet[j] != text[i]; j++);
                text[i] = key[j];
            }
        }
    }
    return text;
}
string toupcase(string key)
{
    //uppercase every letter of the key
    int i = 0;
    for (i = 0; key[i] != '\0'; i++)
    {
        key[i] = toupper(key[i]);
    }
    return key;
}
