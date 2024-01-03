#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //Propt for user's name
    string name = get_string("What's your name? ");

    //Count number of characters up until '\0' (aka NUL)
    int n = strlen(name);
    printf("%i\n",n);
}