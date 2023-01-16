"""  A credit (or debit) card, of course, is a plastic card with which you can pay for goods and services. 
Printed on that card is a number that’s also stored in a database somewhere, so that when your card is used to buy something, 
the creditor knows whom to bill. There are a lot of people with credit cards in this world, so those numbers are pretty long: 
American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. 
And those are decimal numbers (0 through 9), not binary, which means, for instance, that American Express could print as many 
as 10^15 = 1,000,000,000,000,000 unique cards! (That’s, um, a quadrillion.)
Actually, that’s a bit of an exaggeration, because credit card numbers actually have some structure to them. 
All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55 
(they also have some other potential starting numbers which we won’t concern ourselves with for this problem); 
and all Visa numbers start with 4. But credit card numbers also have a “checksum” built into them, a mathematical relationship 
between at least one number and others. That checksum enables computers (or humans who like math) to detect typos (e.g., transpositions), 
if not fraudulent numbers, without having to query a database, which can be slow. Of course, a dishonest mathematician could certainly 
craft a fake number that nonetheless respects the mathematical constraint, so a database lookup is still necessary for more rigorous checks. 
Most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you can determine if a credit card number 
is (syntactically) valid as follows:

1.Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
2.Add the sum to the sum of the digits that weren’t multiplied by 2.
3.If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid! 

Write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, 
MasterCard, or Visa card number, per the definitions of each’s format herein. So that we can automate some tests of your code, 
we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n, nothing more, nothing less. For simplicity, 
you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card) 
and that it won’t have leading zeroes. But do not assume that the user’s input will fit in an int! """

from math import floor
import sys


def main():
    # get card number from user
    cardnumber = get_input()
    # get card number length and transform to integer
    length = len(cardnumber)
    cardnumber = int(cardnumber)
    # copy original card number
    copy = cardnumber

    # check for valid length
    if length == 13 or length == 15 or length == 16:
        i = 0
        multisum = 0
        oddsum = 0

        # validate card using Luhn’s algorithm
        while cardnumber > 0:
            digit = cardnumber % 10
            if i % 2 == 1:
                # Multiply every other digit by 2, starting with the number’s second-to-last digit,
                # and then add those products’ digits together.
                digitmult = digit * 2
                if digitmult >= 10:
                    add = digitmult % 10
                    digitmult = floor(digitmult / 10)
                    add = add + digitmult
                    multisum = floor(multisum + add)
                else:
                    multisum = floor(multisum + digitmult)
            else:
                # Add the sum to the sum of the digits that weren’t multiplied by 2.
                oddsum = floor(oddsum + digit)
            cardnumber = floor(cardnumber / 10)
            i += 1
        digitsum = multisum + oddsum
        # If the total’s last digit is 0 the number is valid!
        if not digitsum % 10 == 0:
            print("INVALID")
            sys.exit(1)

        # reverse card number with its original and get the first number of the card
        cardnumber = copy
        first_digit = get_first_digit(cardnumber)
        # reverse card number with its original and get the second number of the card
        cardnumber = copy
        second_digit = get_second_digit(cardnumber)

        # check card type
        if first_digit == 4 and 13 <= length <= 16:
            print("VISA")
        elif first_digit == 5 and (second_digit == 1 or second_digit == 5) and length == 16:
            print("MASTERCARD")
        elif first_digit == 3 and (second_digit == 4 or second_digit == 7) and length == 15:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")
        sys.exit(1)


def get_input():
    # get input from user
    userinput = input("Number: ")
    # check if user entered only numbers
    while not userinput.isnumeric():
        # keep prompting
        userinput = input("Number: ")
    # convert user input's string to integer and return it's value
    return userinput


def get_first_digit(cardnumber):
    temp = 0
    while cardnumber > 0:
        temp = cardnumber % 10
        cardnumber = floor(cardnumber / 10)
    digit = temp
    return digit


def get_second_digit(cardnumber):
    digit = 0
    while cardnumber > 10:
        digit = cardnumber % 10
        cardnumber = floor(cardnumber / 10)
    return digit


main()
