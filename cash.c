/* When making change, odds are you want to minimize the number of coins you’re dispensing for each customer, 
lest you run out (or annoy the customer!). Fortunately, computer science has given cashiers everywhere ways 
to minimize numbers of coins due: greedy algorithms.
Specifically, complete the implementation of those functions as follows:
- Implement get_cents in such a way that the function prompts the user for a number of cents using get_int 
and then returns that number as an int. If the user inputs a negative int, your code should prompt the user again. 
(But you don’t need to worry about the user inputting, e.g., a string, as get_int will take care of that for you.) 
Odds are you’ll find a do while loop of help, as in mario.c!
- Implement calculate_quarters in such a way that the function calculates (and returns as an int) how many quarters 
a customer should be given if they’re owed some number of cents. For instance, if cents is 25, 
then calculate_quarters should return 1. If cents is 26 or 49 (or anything in between, then calculate_quarters should also return 1. 
If cents is 50 or 74 (or anything in between), then calculate_quarters should return 2. And so forth.
- Implement calculate_dimes in such a way that the function calculates the same for dimes.
- Implement calculate_nickels in such a way that the function calculates the same for nickels.
- Implement calculate_pennies in such a way that the function calculates the same for pennies. */

#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i quarters, %i dimes, %i nickels and %i pennies\n", quarters, dimes, nickels, pennies);
    printf("Total %i\n", coins);
}

int get_cents(void)
{
    // TODO
    int cents;
    do
    {
        cents = get_int("How many cents you own? ");
    }
    while (cents < 0);
    return cents;
}

//calc functions
int calculate_quarters(int cents)
{
    // TODO
    int quarters = cents / 25;
    return quarters;
}

int calculate_dimes(int cents)
{
    // TODO
    int dimes = cents / 10;
    return dimes;
}

int calculate_nickels(int cents)
{
    // TODO
    int nickels = cents / 5;
    return nickels;
}

int calculate_pennies(int cents)
{
    // TODO
    int pennies = cents / 1;
    return pennies;
}
