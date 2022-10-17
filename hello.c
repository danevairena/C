#include <stdio.h>
#include<cs50.h>

int main(void)
{
    //prompts user for name
    string name = get_string("Name: ");

    //prints the result
    printf("Hello, %s!\n", name);
}