/* Design and implement a program, wordle, that completes the implementation of our Wordle50 clone of the game. You’ll notice that some 
large pieces of this program have already been written for you–you are not allowed to modify any of those parts of the program. 
Instead, your work should be constrained to the seven TODOs we’ve left behind for you to fill in. Each one of those parts solves a specific problem, 
and we recommend you tackle them in order from 1 to 7. Each numbered TODO corresponds to the same item in the below list.

1. In the first TODO, you should ensure the program accepts a single command-line argument. If the program was not run with a single command-line argument, 
you should print the error message as we demonstrate above and return 1, ending the program.
2. In the second TODO, you should make sure that  is one of the acceptable values (5, 6, 7, or 8), and store that value in wordsize; we’ll need to make 
use of that later. If the value of  is not one of those four values exactly, you should print the error message and return 1, ending the program.
3. For the third TODO, you should help defend against stubborn users by making sure their guess is the correct length. A user should be prompted 
(as via get_string) to type in a -letter word (remember, that value is passed in as a parameter to get_guess) and if they supply a guess of the wrong length, 
they should be re-prompted until they provide exactly the value you expect from them. All guesses in this game should be in lowercase characters. 
Once a legitimate guess has been obtained, it can be returned.
4. Next, for the fourth TODO, we need to keep track of a user’s “score” in the game. We do this both on a per-letter basis—by assigning a score of 2 
(which we #defined as EXACT) to a letter in the correct place, 1 (which we #defined as CLOSE) to a letter that’s in the word but in the wrong place, or 0 
(which we #defined as WRONG)—and a per-word basis, to help us detect when we’ve potentially triggered the end of the game by winning. 
We’ll use the individual letter scores when we color-code the printing. In order to store those scores, we need an array, which we’ve called status. 
At the start of the game, with no guesses having taken place, it should contain all 0s.
This is another good place to stop and test your code, particularly as it pertains to item 3, above! You’ll notice that at this point, when you finally enter a legitimate guess (that is to say, one that’s the correct length), your program will likely look something like the below:

Input a 5-letter word: computer
Input a 5-letter word: games
Guess 1:
Input a 5-letter word:
That’s normal, though! Implementing print_word is TODO number 6, so we should not expect the program to do any processing of that guess at this time. Of course, you can always add additional printf calls (just make sure to remove them before you submit) as part of your debugging strategy!

The fifth TODO is definitely the largest and probably most challenging. Inside of the check_word function, it’s up to you to compare each of the letters of the guess with each of the letters of the choice (which, recall, is the “secret word” for this game), and assign scores. If the letters match, award EXACT (2) points and break out of the loop—there’s no need to continue looping if you already determined the letter is in the right spot. Technically, if that letter appears in the word twice, this could result in a bit of a bug, but fixing that bug overcomplicates this problem a bit more than we want to now, so we’re going to accept that as a feature of our version! If you find that the letter is in the word but not in the right spot, award CLOSE (1) points but don’t break! After all, that letter might later show up in the right spot in the choice word, and if we break too soon, the user would never know it! You don’t actually need to explicitly set WRONG (0) points here, since you handled that early in Step 4. Ultimately though, you should also be summing up the total score of the word when you know it, because that’s what this function is supposed to ultimately return. Again, don’t be afraid to use debug50 and/or printfs as necessary in order to help you figure out what the values of different variables are at this point – until you implement print_word, below, the program won’t be offering you much in the way of a visual checkpoint!
For the sixth TODO you will complete the implementation of print_word. That function should look through the values you populated the status array with and print out, character by character, each letter of the guess with the correct color code. You may have noticed some (scary-looking!) #defines at the top of the file wherein we provide a simpler way of representing what’s called an ANSI color code, which is basically a command to change the font color of the terminal. You don’t need to worry about how to implement those four values (GREEN, YELLOW, RED, and RESET, the latter of which simply returns to the terminal’s default font) or exactly what they mean; instead, you can just use them (the power of abstraction!). Note as well that we provide an example in the distribution code up where we print some green text and then reset the color, as part of the game’s introduction. Accordingly, you should feel free to use the below line of code for inspiration as to how you might try to toggle colors:
printf(GREEN"This is WORDLE50"RESET"\n");
Of course, unlike our example, you probably don’t want to print a newline after each character of the word (instead, you just want one newline at the end, also resetting the font color!), lest it end up looking like the below:


Input a 5-letter word: games
Guess 1: g
a
m
e
s
Input a 5-letter word:
Finally, the seventh TODO is just a bit of tidying up before the program terminates. Whether the main for loop has ended normally, by the user running out of guesses, or because we broke out of it by getting the word exactly right, it’s time to report to the user on the game’s outcome. If the user did win the game, a simple You won! suffices to print here. Otherwise, you should print a message telling the user what the target word was, so they know the game was being honest with them (and so that you have a means to debug if you look back and realize your code was providing improper clues along the way!)
*/

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2
    int k = atoi(argv[1]);
    if (k != 5 && k != 6 && k != 7 && k != 8)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }
    wordsize = k;

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7
    if (won == true)
    {
        printf("You won!\n");
    }
    else
    {
        printf("Target word: %s\n", choice);
    }

    // that's all folks!
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";

    // ensure users actually provide a guess that is the correct length
    // TODO #3
    do
    {
        guess = get_string("Input a %i-letter word:", wordsize);
    }
    while (strlen(guess) != wordsize);

    // All guesses in this game should be in lowercase characters
    //lowercase the answer if needed
    for (int i = 0; i < wordsize; i++)
    {
        guess[i] = tolower(guess[i]);
    }
    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5

    // iterate over each letter of the guess
    for (int i = 0; i < wordsize; i++)
    {
        // iterate over each letter of the choice
        for (int j = 0; j < wordsize; j++)
        {
            // if current guess letter is in the choice word, but not the right spot, score CLOSE point (yellow)
            if (guess[i] == choice[j] && i != j)
            {
                status[i] = CLOSE;
                score += CLOSE;
            }

            // current guess letter and current choice if they're the same position in the word, score EXACT points (green)
            if (i == j && guess[i] == choice[j])
            {
                status[i] = EXACT;
                score += EXACT;
            }
        }
    }

    // keep track of the total score by adding each individual letter's score from above
    return score;
}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    for (int i = 0; i < wordsize; i++)
    {
        switch (status[i])
        {
            case 0:
            {
                printf(RED"%c"RESET, guess[i]);
                break;
            }
            case CLOSE:
            {
                printf(YELLOW"%c"RESET, guess[i]);
                break;
            }
            case EXACT:
            {
                printf(GREEN"%c"RESET, guess[i]);
                break;
            }
        }
    }

    printf("\n");
    return;
}
