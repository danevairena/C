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
