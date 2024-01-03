#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int i =rm 0;
    long num = 0;

    while (input[i] != '\0')
    {
        i++;
    }
    if (i < 0)
    {
        return 0;
    }
    else
    {
        num = input[i] - '0'
    }


    for (int j = i; j < 0; j--)
    {
        num = num +

    }



}
