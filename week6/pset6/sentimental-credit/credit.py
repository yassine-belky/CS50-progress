import cs50


def main():
    number = -1
    while number <= 0:
        number = cs50.get_int("Number : ")

    digits = []
    tmp = number
    while tmp != 0:
        digits.append(tmp % 10)
        tmp = tmp // 10

    every_other_sum = sum(
        2 * digit if digit < 5 else (2 * digit) % 10 + (2 * digit) // 10
        for digit in digits[1::2]
    )

    remaining_sum = sum(digits[::2])

    luhn_sum = every_other_sum + remaining_sum

    if luhn_sum % 10 != 0:
        print("INVALID")
    elif len(digits) == 13:
        print("VISA")
    elif len(digits) == 15:
        print("AMEX")
    elif len(digits) == 16 and digits[-1] == 4:
        print("VISA")
    else:
        print("MASTERCARD")


if __name__ == "__main__":
    main()
