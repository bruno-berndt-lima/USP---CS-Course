from posixpath import split


def main():
    sprinklers = []
    x = input()
    n, lenght, width = x.split(" ")

    for i in range(int(n)):
        y = input()
        pos, radius = y.split(" ")
        sprinklers.append([int(pos), int(radius)])

    print(sprinklers)


main()  