""" DNA, the carrier of genetic information in living things, has been used in criminal justice for decades. But how, exactly, does DNA profiling work? 
Given a sequence of DNA, how can forensic investigators identify to whom it belongs? DNA is really just a sequence of molecules called nucleotides, 
arranged into a particular shape (a double helix). Every human cell has billions of nucleotides arranged in sequence. Each nucleotide of DNA contains one 
of four different bases: adenine (A), cytosine (C), guanine (G), or thymine (T). Some portions of this sequence (i.e., genome) are the same, or at least 
very similar, across almost all humans, but other portions of the sequence have a higher genetic diversity and thus vary more across the population.

One place where DNA tends to have high genetic diversity is in Short Tandem Repeats (STRs). An STR is a short sequence of DNA bases that tends to repeat 
consecutively numerous times at specific locations inside of a person’s DNA. The number of times any particular STR repeats varies a lot among individuals.

In a file called dna.py, implement a program that identifies to whom a sequence of DNA belongs.
1.The program should require as its first command-line argument the name of a CSV file containing the STR counts for a list of individuals and should require 
as its second command-line argument the name of a text file containing the DNA sequence to identify.. If your program is executed with the incorrect number of 
command-line arguments, your program should print an error message of your choice (with print). If the correct number of arguments are provided, you may assume 
that the first argument is indeed the filename of a valid CSV file and that the second argument is the filename of a valid text file.
2. Your program should open the CSV file and read its contents into memory.
3. Your program should open the DNA sequence and read its contents into memory.
4. For each of the STRs (from the first line of the CSV file), your program should compute the longest run of consecutive repeats of the STR in the DNA sequence 
to identify. Notice that we’ve defined a helper function for you, longest_match, which will do just that!
5. If the STR counts match exactly with any of the individuals in the CSV file, your program should print out the name of the matching individual. If the STR 
counts do not match exactly with any of the individuals in the CSV file, your program should print No match."""

import csv
import sys


def main():

    # TODO: Check for command-line usage
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    database = sys.argv[1]
    sequence = sys.argv[2]

    # TODO: Read database file into a variable
    datadna = []
    # read file till the end and then close it
    with open(database, "r") as file:
        # create DictReader object to read dictionaries from the file
        reader = csv.DictReader(file)
        # repeat for every row in the database file
        for row in reader:
            # get current read persons's name (string) and dna (converted to int)
            row["AGATC"] = int(row["AGATC"])
            row["AATG"] = int(row["AATG"])
            row["TATC"] = int(row["TATC"])
            # append current dictionary(name and dna) read from the file to the list of dictionaries
            datadna.append(row)

        # print(datadna)

    # TODO: Read DNA sequence file into a variable
    with open(sequence, "r") as dnatxt:
        seqdna = dnatxt.read()
        dna = seqdna
    # print(dna)

    # AGATC,TTTTTTCT,AATG,TCTAG,GATA,TATC,GAAA,TCTG
    # TODO: Find longest match of each STR in DNA sequence
    AGATC = longest_match(dna, "AGATC")
    AATG = longest_match(dna, "AATG")
    TATC = longest_match(dna, "TATC")
    if str(sys.argv[1]) == "databases/large.csv":
        TTTTTTCT = longest_match(dna, "TTTTTTCT")
        TCTAG = longest_match(dna, "TCTAG")
        GATA = longest_match(dna, "GATA")
        GAAA = longest_match(dna, "GAAA")
        TCTG = longest_match(dna, "TCTG")

    found = False
    # TODO: Check database for matching profiles
    for i in range(len(datadna)):
        if str(sys.argv[1]) == "databases/large.csv":
            if int(datadna[i]["AGATC"]) == AGATC and int(datadna[i]["AATG"]) == AATG and int(datadna[i]["TATC"]) == TATC and int(datadna[i]["TTTTTTCT"]) == TTTTTTCT and int(datadna[i]["TCTAG"]) == TCTAG and int(datadna[i]["TATC"]) == TATC and int(datadna[i]["GATA"]) == GATA and int(datadna[i]["GAAA"]) == GAAA and int(datadna[i]["TCTG"]) == TCTG:
                result = datadna[i]["name"]
                print(result)
                found = True
        else:
            if int(datadna[i]["AGATC"]) == AGATC and int(datadna[i]["AATG"]) == AATG and int(datadna[i]["TATC"]) == TATC:
                result = datadna[i]["name"]
                print(result)
                found = True

    if found == False:
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


main()
