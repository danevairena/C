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
