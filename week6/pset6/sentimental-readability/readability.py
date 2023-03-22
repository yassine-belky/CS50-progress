import cs50
import math


def main():
    text = cs50.get_string("Text : ")
    words = text.split(" ")
    sentences = [
        sentence
        for sentence in text.replace("?", ".").replace("!", ".").split(".")
        if sentence
    ]
    letters = [letter for letter in text if letter.isalpha()]
    grade_level = math.ceil(
        5.88 * len(letters) / len(words) - 29.6 * len(sentences) / len(words) - 15.8
    )
    if grade_level < 1:
        print("Before Grade 1")
    elif grade_level >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade_level}")


if __name__ == "__main__":
    main()
