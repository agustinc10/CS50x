// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace (string word);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Must enter a single word\n");
        return 1;
    }
    else
    {
        replace (argv[1]);
    }
}

string replace (string word)
{
    int length = strlen (word);
    for (int i = 0; i < length; i++)
    {
        switch (word[i])
        {
        case 'a':
            printf("6");
            break;
        case 'e':
            printf("3");
            break;
        case 'i':
            printf("1");
            break;
        case 'o':
            printf("0");
            break;
        default:
            printf("%c", word[i]);
        }
    }
    printf("\n");
    return word;
}

