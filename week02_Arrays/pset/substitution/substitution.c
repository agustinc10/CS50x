#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool only_alpha(string s);
bool repeated(string s);
char encipher(char c, string key);

int main(int argc, string argv[])
{
    // Validate key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (only_alpha(argv[1]) == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (repeated(argv[1]) == true)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else
    {
        string plaintext = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0; i < strlen(plaintext); i++)
        {
            char c = encipher(plaintext[i], argv[1]);
            printf("%c", c);
        }
        printf("\n");
        return 0;
    }
}
// Check for non-alphabetic characters
bool only_alpha(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        n = (isalpha(s[i])) ? n : 1;
    }
    bool b = (n == 0) ? true : false;
    return b;
}
// Check for repeated characters (case-insensitive)
bool repeated(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        s[i] = toupper(s[i]);
    }
    for (int i = 0; i < strlen(s) - 1; i++)
    {
        for (int j = i + 1; j < strlen(s); j++)
        {
            n = (s[j] == s[i]) ? 1 : n;
        }
    }
    bool b = (n == 0) ? false : true;
    return b;
}
char encipher(char c, string key)
{
    char ABC[26];
    char c1 = toupper(c);
    char c2 = c;

    for (int i = 0; i < 26; i++)
    {
        ABC[i] = 'A' + i;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (c1 == ABC[i])
        {
            c2 = key[i];
        }
    }
    if (islower(c))
    {
        c2 = tolower(c2);
    }
    return c2;
}
