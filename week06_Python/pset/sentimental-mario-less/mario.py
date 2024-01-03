# TODO
def main():
    height = get_height()
    for i in range(height):
        for j in range(height, i + 1, -1):
            print(" ", end="")
        for j in range(i + 1):
            print("#", end="")
        print("")


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            pass


main()

