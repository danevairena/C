""" Toward the beginning of World 1-1 in Nintendo’s Super Mario Brothers, Mario must hop over adjacent pyramids of blocks.
Let’s recreate those pyramids in C, albeit in text, using hashes (#) for bricks, a la the below. 
Each hash is a bit taller than it is wide, so the pyramids themselves will also be taller than they are wide.

   #  #
  ##  ##
 ###  ###
####  ####

Allow the user to decide just how tall the pyramids should be by first prompting them for a positive integer between, say, 1 and 8, inclusive. """

# TODO
def main():
    # set n to 0 and get input from the user while not entered number between 1 and 8 inclusive
    n = 0
    while n < 1 or n > 8:
        n = get_input()

    # loop for printing every row
    for row in range(n):
        # import spaces before printing left pyramid, so to be right side aligned
        # loop starting from spacetab = n while spacetab >= row, decreasing by one on every cycle
        for spacetab in range(n, row + 1, -1):
            print(" ", end="")
        # loop for printing right pyramid's hashes
        for rhash in range(row + 1):
            print("#", end="")
        # print double space in between the two pyramids
        print("  ", end="")
        # loop for printing left pyramid's hashes
        for lhash in range(row + 1):
            print("#", end="")
        # go to new line
        print()


def get_input():
    # get input from user
    userinput = input("How tall the pyramid should be? ")
    # check if user entered only numbers
    while not userinput.isnumeric():
        # keep prompting
        userinput = input("How tall the pyramid should be? ")
    # convert user input's string to integer and return it's value
    n = int(userinput)
    return n


main()
