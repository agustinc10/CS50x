#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int word_length = strlen(word);
    for (int i = 0; i < word_length - 1; i++)
    {
        // Check if NOT alphabetical (i.e., "ba")
        if (word[i] > word[i + 1])
        {
            printf("No\n");
            return 0; // Es necesario para terminar el programa y que no siga imprimiento "No"
        }
    }

    printf("Yes\n")
    return 0; // No es necesario
}