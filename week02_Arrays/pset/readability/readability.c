#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float L = (float) count_letters(text) * 100 / count_words(text);
    float S = (float) count_sentences(text) * 100 / count_words(text);
    float ind = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(ind);

    if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Count letters
int count_letters(string text)
{
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        n = (isalpha(text[i])) ? n + 1 : n;
    }
    return n;
}
// Count words
int count_words(string text)
{
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        n = (isblank(text[i])) ? n + 1 : n;
    }
    return n + 1;
}
// Count sentences
int count_sentences(string text)
{
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            n++;
        }
    }
    return n;
}