import cs50


def main():
    height = -1
    while height <= 0:
        height = cs50.get_int("Height : ")

    for i in range(1, height + 1):
        print(f"{' '*(height - i)}{'#'*i}  {'#'*i}{' '*(height - i)}")


if __name__ == "__main__":
    main()
