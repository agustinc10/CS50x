#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Make sure every character in argv[1] is a digit
    else if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // Convert argv[1] from a `string` to an `int`
        int n = atoi(argv[1]);
        string plaintext = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plaintext); i++)
        {
            char c = rotate(plaintext[i], n);
            printf("%c", c);
        }
        printf("\n");
        return 0;
    }
}

bool only_digits(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        n = (isdigit(s[i])) ? n : 1;
    }
    bool b = (n == 0) ? true : false;
    return b;
}
// Rotate the character if it's a letter
char rotate(char c, int n)
{
    int alphabet = 26;
    int x = n % alphabet;
    int y = c + x;
    if (isalpha(c))
    {
        if (isupper(c))
        {
            c = (y < 'Z') ? y : y - alphabet;
        }
        if (islower(c))
        {
            c = (y < 'z') ? y : y - alphabet;
        }
    }
    return c;
}

