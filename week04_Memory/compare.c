#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("i: ");
    string t = get_string("j: ");

    printf("%p\n", s);
    printf("%p\n", t);

}