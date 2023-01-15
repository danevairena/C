""" Complete the implementation of tournament.py, such that it simulates a number of tournaments and outputs each team’s probability of winning.

1. First, in main, read the team data from the CSV file into your program’s memory, and add each team to the list teams.
2. Next, implement the simulate_tournament function. This function should accept as input a list of teams and should repeatedly simulate rounds until you’re left with one team. The function should the return the name of that team.
3. Finally, back in the main function, run N tournament simulations, and keep track of how many times each team wins in the counts dictionary. """

# Simulate a sports tournament

import csv
import sys
import random

# Number of simulations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # read file till the end and then close it
    with open(sys.argv[1], "r") as file:
        # create DictReader object to read dictionaries from the file
        reader = csv.DictReader(file)
        # repeat for every row in the teams file
        for row in reader:
            # get current read team's name (string) and rating (converted to int)
            row["rating"] = int(row["rating"])
            # append current dictionary(name and rating) read from the file to the list of dictionaries
            teams.append(row)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # simulate N tournaments
    for i in range(N):
        winner = simulate_tournament(teams)
        # check if winner of tournament is in counts list and update it's value with 1
        if winner in counts:
            counts[winner] += 1
        else:
            # if winner is not in counts append it with value of 1
            counts[winner] = 1
    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # using recursion simulate round and update teams list
    # until there is only one team in the list
    while len(teams) > 1:
        teams = simulate_round(teams)
    # return winner team's name
    return teams[0]["team"]


if __name__ == "__main__":
    main()
