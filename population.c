/* We have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away.
For example, if we were to start with n = 1200 llamas, then in the first year, 1200 / 3 = 400 new llamas would be born 
and 1200 / 4 = 300 llamas would pass away. At the end of that year, we would have 1200 + 400 - 300 = 1300 llamas.

Your program should first prompt the user for a starting and end population size.
- If the user enters a number less than 9 (the minimum allowed population size), the user should be re-prompted
- If the user enters a number less than the starting population size, the user should be re-prompted to enter an ending population size
Your program should then calculate the (integer) number of years required for the population to reach at least the size of the end value.
Finally, your program should print the number of years required for the llama population to reach that end size, as 
by printing to the terminal Years: n, where n is the number of years. */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    //If the user enters a number less than 9 (the minimum allowed population size), the user should be re-prompted
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    //If the user enters a number less than the starting population size, the user should be re-prompted
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    // We have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away.
    int years = 0;
    int population = start_size;

    while (population < end_size)
    {
        int born = population / 3;
        int passed = population / 4;
        population = population + born - passed;
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", years);
}
