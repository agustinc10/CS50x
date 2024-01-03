# TODO
import re


def main():
    n = input("Number: ")
    pattern_AMEX = r'^(34|37)\d{13}$'
    pattern_VISA = r'^4\d{12,15}$'
    pattern_MASTER = r'^5[1-5]\d{14}$'

    if checksum(n) == 0:
        if re.match(pattern_AMEX, n):
            print('AMEX')
        elif re.match(pattern_VISA, n):
            print('VISA')
        elif re.match(pattern_MASTER, n):
            print('MASTERCARD')
        else:
            print('INVALID')
    else:
        print('INVALID')


def checksum(n):
    ni = int(n)
    r = s = t = 0
    for i in range(len(n), 0, -2):
        r += ni % 10
        ni //= 10
        s = (ni % 10) * 2
        t += int(s / 10) + int(s % 10)
        ni //= 10
    u = (r + t) % 10
    return u


main()
