#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the length of the array from the user
    int length;
    do
    {
        length = get_int("Length: ");
    }
    while (length < 1);

    // Declare our array
    int twice[length];

    // Set first value
    twice[0] = 1;
    printf("%i\n", twice[0]);

    // Make  the current element twice the previous and print current element
    for (int i = 1; i < length; i++)
    {
        twice[i] = 2 * twice[i-1];
        printf("%i\n", twice[i]);
    }




}