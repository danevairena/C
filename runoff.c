/* You already know about plurality elections, which follow a very simple algorithm for determining the winner of an election: 
every voter gets one vote, and the candidate with the most votes wins.
But the plurality vote does have some disadvantages. What happens, for instance, in an election with three candidates, and the ballots below are cast?
A plurality vote would here declare a tie between Alice and Bob, since each has two votes. But is that the right outcome?
There’s another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for more than one candidate. 
Instead of just voting for their top choice, they can rank the candidates in order of preference.
Here, each voter, in addition to specifying their first preference candidate, has also indicated their second and third choices. 
And now, what was previously a tied election could now have a winner.
One such ranked choice voting system is the instant runoff system. In an instant runoff election, voters can rank as many candidates as they wish. 
If any candidate has a majority (more than 50%) of the first preference votes, that candidate is declared the winner of the election.
If no candidate has more than 50% of the vote, then an “instant runoff” occurrs. The candidate who received the fewest number of votes 
is eliminated from the election, and anyone who originally chose that candidate as their first preference now has their second preference considered. 
Why do it this way? Effectively, this simulates what would have happened if the least popular candidate had not been in the election to begin with.
The process repeats: if no candidate has a majority of the votes, the last place candidate is eliminated, and anyone who voted for them will instead 
vote for their next preference (who hasn’t themselves already been eliminated). Once a candidate has a majority, that candidate is declared the winner.

Complete the implementation of runoff.c in such a way that it simulates a runoff election. 
- vote - The function takes arguments voter, rank, and name. If name is a match for the name of a valid candidate, then you should 
update the global preferences array to indicate that the voter voter has that candidate as their rank preference (where 0 is the first preference, 1 is 
the second preference, etc.). If the preference is successfully recorded, the function should return true; the function should return false otherwise 
(if, for instance, name is not the name of one of the candidates). You may assume that no two candidates will have the same name.
- tabulate - The function should update the number of votes each candidate has at this stage in the runoff.
Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.
- print_winner - If any candidate has more than half of the vote, their name should be printed and the function should return true.
If nobody has won the election yet, the function should return false.
- find_min - The function should return the minimum vote total for any candidate who is still in the election.
- is_tie - The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
The function should return true if every candidate remaining in the election has the same number of votes, and should return false otherwise.
- eliminate - The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
The function should eliminate the candidate (or candidates) who have min number of votes. */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
//preferences[i][j] here will store the index of the candidate who is the jth preference for voter i
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //loop for voter's number
    for (int i = 0; i < voter_count; i++)
    {
        //loop for rank number
        for (int j = 0; j < candidate_count; j++)
        {
            //checks if candidate is not eliminated to update his vote and exit from the loop for rank number
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority = voter_count / 2 + 1;
    //loop for checking if there is a candidate with more than half of the votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            //print winner's name and exit
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int remaining = 0;
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            remaining++;
        }
        if (candidates[i].votes == min)
        {
            count++;
        }
    }
    if (remaining == count)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
