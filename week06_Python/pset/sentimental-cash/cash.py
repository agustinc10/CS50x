# TODO
from cs50 import get_float


def main():
    cents = get_cents()
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickels + pennies
    print(f'{coins}')


def get_cents():
    n = -1
    while n < 0:
        n = 100 * get_float("Change owed: ")
    return n


def calculate_quarters(cents):
    n = int(cents / 25)
    return n


def calculate_dimes(cents):
    n = int(cents / 10)
    return n


def calculate_nickels(cents):
    n = int(cents / 5)
    return n


def calculate_pennies(cents):
    return cents


main()
