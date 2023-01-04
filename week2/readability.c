/* According to Scholastic, E.B. White’s Charlotte’s Web is between a second- and fourth-grade reading level, and Lois Lowry’s The Giver is 
between an eighth- and twelfth-grade reading level. What does it mean, though, for a book to be at a particular reading level?
Well, in many cases, a human expert might read a book and make a decision on the grade (i.e., year in school) for which they think the book is 
most appropriate. But an algorithm could likely figure that out too!
So what sorts of traits are characteristic of higher reading levels? Well, longer words probably correlate with higher reading levels. 
Likewise, longer sentences probably correlate with higher reading levels, too.

A number of “readability tests” have been developed over the years that define formulas for computing the reading level of a text. 
One such readability test is the Coleman-Liau index. The Coleman-Liau index of a text is designed to output that (U.S.) grade level 
that is needed to understand some text. The formula is
index = 0.0588 * L - 0.296 * S - 15.8
where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

Design and implement a program, readability, that computes the Coleman-Liau index of text.
- Your program must prompt the user for a string of text using get_string.
- Your program should count the number of letters, words, and sentences in the text. You may assume that a letter is any lowercase character 
from a to z or any uppercase character from A to Z, any sequence of characters separated by spaces should count as a word, and that any occurrence 
of a period, exclamation point, or question mark indicates the end of a sentence.
- Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
- If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), 
your program should output "Grade 16+" instead of giving the exact index number. 
- If the index number is less than 1, your program should output "Before Grade 1". */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string txt);
int count_words(string txt);
int count_sentences(string txt);
void calc_grade(float letters, float words, float sentences);

/*Your program should count the number of letters, words, and sentences in the text.
Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+"
instead of giving the exact index number. If the index number is less than 1, your program should output "Before Grade 1".*/

int main(void)
{
    string text = get_string("Enter your text here: ");
    int num_letters = count_letters(text);
    int num_words = count_words(text);
    int num_sentences = count_sentences(text);
    calc_grade(num_letters, num_words, num_sentences);

}

int count_letters(string txt)
{
    //You may assume that a letter is any lowercase character from a to z or any uppercase character from A to Z
    int i, count = 0;
    for (i = 0; txt[i] != '\0'; i++)
    {
        if ((txt[i] >= 97 && txt[i] <= 122) || (txt[i] >= 65 && txt[i] <= 90))
        {
            count++;
        }

    }
    printf("%i letters\n", count);
    return count;

}

int count_words(string txt)
{
    //any sequence of characters separated by spaces should count as a word
    int i, count = 0;
    for (i = 0; txt[i] != '\0'; i++)
    {
        //check for spaces in between
        if (txt[i] == 32)
        {
            count++;
        }

    }

    //check if the last word of the string is not ending with space
    if (txt[i - 1] != 32)
    {
        count++;
    }

    printf("%i words\n", count);


    return count;

}

int count_sentences(string txt)
{
    //any occurrence of a period, exclamation point, or question mark indicates the end of a sentence
    int i, count = 0;
    for (i = 0; txt[i] != '\0'; i++)
    {
        //check for period, exclamation point, or question mark as end of a sentence
        if ((txt[i] == 46) || (txt[i] == 33) || (txt[i] == 63))
        {
            count++;
        }

    }

    //checking last character for possible ending without punctuation
    if ((txt[i - 1] != 46) && (txt[i - 1] != 33) && (txt[i - 1] != 63))
    {
        count++;
    }

    //checking last second character from back to front for possible double punctuation
    if ((txt[i - 2] == 46) || (txt[i - 2] == 33) || (txt[i - 2] == 63))
    {
        count--;
    }


    printf("%i sentences\n", count);
    return count;
}

void calc_grade(float letters, float words, float sentences)
{
    float L = 0, S = 0, index;
    int grade;

    //calculating average values
    //where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    L = (letters / words) * 100;
    S = (sentences / words) * 100;

    //calculating index using the formula index = 0.0588 * L - 0.296 * S - 15.8
    index = 0.0588 * L - 0.296 * S - 15.8;
    printf("index %f\n", index);

    //round the resulting index number to the nearest int
    grade = round(index);

    //print grade result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
