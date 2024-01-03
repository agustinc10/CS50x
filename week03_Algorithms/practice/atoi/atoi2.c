#include <stdio.h>
#include <string.h>

// Recursive function to implement `atoi()` function in C
long atoi(const char *S, int n)
{
    // base case – the end of the string is reached, or the
    // current character is non-numeric
    if (n < 0 || (S[n] < '0' || S[n] > '9'))
    {
        return 0;
    }

    // recur for remaining digits and append the current digit
    // to result of recursion multiplied by 10
    return (10 * atoi(S, n - 1) + (S[n] - '0'));
}

// Implement `atoi()` function in C
int main(void)
{
    char S[] = "12345";

    printf("%ld", atoi(S, strlen(S) - 1));
    printf("\n");

    return 0;
}