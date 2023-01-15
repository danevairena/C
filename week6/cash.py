""" When making change, odds are you want to minimize the number of coins you’re dispensing for each customer, 
lest you run out (or annoy the customer!). Fortunately, computer science has given cashiers everywhere ways 
to minimize numbers of coins due: greedy algorithms.
1. Prompt the user for a cash owned
and then returns that number as an float. If the user inputs a negative or not not numerical value, your code should prompt the user again. 
2. How many quarters a customer should be given if they’re owed some number of dollars. 
3. Calculate dimes.
4. Calculate nickels.
5. Calculate pennies in such a way that the function calculates the same for pennies.
6. Output minimun number of coins """

def main():
    # prompt user for cash owned
    cash = 0.0
    while cash <= 0:
        cash = get_cash()
    # TODO

    # Calculate the number of quarters to give the customer
    quarters = int(cash / 0.25)
    cash = round(cash - quarters * 0.25, 2)
    # Calculate the number of dimes to give the customer
    dimes = int(cash / 0.10)
    cash = round(cash - dimes * 0.10, 2)
    # Calculate the number of nickels to give the customer
    nickels = int(cash / 0.05)
    cash = round(cash - nickels * 0.05, 2)
    # Calculate the number of pennies to give the customer
    pennies = round(cash / 0.01)
    # Sum coins
    coins = int(quarters + dimes + nickels + pennies)
    # Print minimum number of coins
    print(coins)


def get_cash():
    cash = 0
    while cash <= 0:
        userinput = input("Change owed: ")
        # checks if string before and after "." is numeric
        # keep prompting for cash while user not entered floating point number
        while not (userinput.find(".") > - 1 and userinput[:userinput.find(".")].isnumeric() and
                   userinput[userinput.find(".") + 1:].isnumeric()):
            if userinput.isnumeric():
                break
            else:
                userinput = input("Change owed: ")
        # convert user input's string to integer and return it's value
        cash = float(userinput)
    return cash


main()
