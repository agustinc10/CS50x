#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
//argv is an array of strings (the words you type at the prompt). argc is the argument count (how many words, the length of the array)
{
    if (argc == 2)
    {
    printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, world\n");
    }

}