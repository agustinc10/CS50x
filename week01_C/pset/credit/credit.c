#include <cs50.h>
#include <math.h>
#include <stdio.h>

int checksum(long n);
int count(long n);

int main(void)
{
    long n = get_long("Number: ");
    long x = pow(10, count(n) - 1);
    long y = pow(10, count(n) - 2);

    if (checksum(n) == 0)
    {
        if (count(n) == 15 && (n / y == 34 || n / y == 37))
        {
            printf("AMEX\n");
        }

        else if ((count(n) == 13 || count(n) == 16) && n / x == 4)
        {
            printf("VISA\n");
        }
        else if (count(n) == 16 && (n / y == 51 || n / y == 52 || n / y == 53 || n / y == 54 || n / y == 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Count digits in number
int count(long n)
{
    int c = 0;
    while (n > 0)
    {
        c++;
        n = n / 10;
    }
    return c;
}

// Calculate checksum
int checksum(long n)
{
    int r = 0;
    int t = 0;
    for (int i = count(n); i > 0; i = i - 2)
    {
        r += n % 10;
        n /= 10;
        int s = (n % 10) * 2;
        t += s / 10 + s % 10;
        n /= 10;
    }
    int u = (r + t) % 10;
    return u;
}