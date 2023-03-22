import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print(f"Usage {sys.argv[0]} DB_FILENAME SEQUENCE_FILENAME")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as db_file:
        db_reader = csv.DictReader(db_file)

        # TODO: Read DNA sequence file into a variable
        with open(sys.argv[2], "r") as seq_file:
            seq_str = seq_file.read().rstrip()

            # TODO: Find longest match of each STR in DNA sequence
            str_repeats = {
                dna_str: longest_match(seq_str, dna_str)
                for dna_str in db_reader.fieldnames
                if dna_str != "name"
            }

            # TODO: Check database for matching profiles
            for row in db_reader:
                sub_row = {
                    key: int(value) for key, value in row.items() if key != "name"
                }
                if sub_row == str_repeats:
                    print(row["name"])
                    return

            print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
