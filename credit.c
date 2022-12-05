/* A credit (or debit) card, of course, is a plastic card with which you can pay for goods and services. 
Printed on that card is a number that’s also stored in a database somewhere, so that when your card is used to buy something, 
the creditor knows whom to bill. There are a lot of people with credit cards in this world, so those numbers are pretty long: 
American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. 
And those are decimal numbers (0 through 9), not binary, which means, for instance, that American Express could print as many 
as 10^15 = 1,000,000,000,000,000 unique cards! (That’s, um, a quadrillion.)
Actually, that’s a bit of an exaggeration, because credit card numbers actually have some structure to them. 
All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 
(they also have some other potential starting numbers which we won’t concern ourselves with for this problem); 
and all Visa numbers start with 4. But credit card numbers also have a “checksum” built into them, a mathematical relationship 
between at least one number and others. That checksum enables computers (or humans who like math) to detect typos (e.g., transpositions), 
if not fraudulent numbers, without having to query a database, which can be slow. Of course, a dishonest mathematician could certainly 
craft a fake number that nonetheless respects the mathematical constraint, so a database lookup is still necessary for more rigorous checks. 

Most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you can determine if a credit card number 
is (syntactically) valid as follows:
1.Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
2.Add the sum to the sum of the digits that weren’t multiplied by 2.
3.If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid! 

Write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, 
MasterCard, or Visa card number, per the definitions of each’s format herein. So that we can automate some tests of your code, 
we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n, nothing more, nothing less. For simplicity, 
you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card) 
and that it won’t have leading zeroes. But do not assume that the user’s input will fit in an int! */

#include <cs50.h>
#include <stdio.h>

bool check_valid(long long card_number); //done
void check_type(long long card_number); //done
int find_lenght(long long card_number); //done
bool check_sum(long long card_number); //done

int main(void)
{
    //prompt for card number
    long long cardnumber;
    do
    {
        cardnumber = get_long_long("Enter your card number: ");
    }
    while (cardnumber < 0);

    if (check_valid(cardnumber) == true)
    {
        check_type(cardnumber);
    }
    else
    {
        (printf("INVALID\n"));
    }

}


bool check_valid(long long card_number)
{
    int lenght = find_lenght(card_number);
    return (lenght == 13 || lenght == 15 || lenght == 16) && check_sum(card_number);
}

int find_lenght(long long card_number)
{
    int n;
    for (n = 0; card_number != 0; card_number /= 10, n++);
    return n;
}

bool check_sum(long long card_number)
{
    int sum = 0, i;
    for (i = 0; card_number != 0; card_number /= 10, i++)
    {
        if (i % 2 == 1)
        {
            //Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together
            int digit = 2 * (card_number % 10);
            sum += (digit / 10 + digit % 10);
        }

        //Add the sum to the sum of the digits that weren’t multiplied by 2
        else
        {
            sum += card_number % 10;
        }

    }

    //If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid
    return (sum % 10 == 0);
}


void check_type(long long card_number)
{
    //American Express numbers start with 34 or 37 & uses 15-digit numbers
    if ((card_number >= 34e13 && card_number < 35e13) || (card_number >= 37e13 && card_number < 38e13))
    {
        printf("AMEX\n");
    }

    //MasterCard numbers start with 51, 52, 53, 54, or 55 & uses 16-digit numbers
    else if (card_number >= 51e14 && card_number < 56e14)
    {
        printf("MASTERCARD\n");
    }

    //Visa numbers start with 4 & uses 13- and 16-digit numbers
    else if ((card_number >= 4e12 && card_number < 5e12) || (card_number >= 4e15 && card_number < 5e15))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}
