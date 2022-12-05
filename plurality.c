/* Elections come in all shapes and sizes. In the UK, the Prime Minister is officially appointed by the monarch, who generally chooses the 
leader of the political party that wins the most seats in the House of Commons. The United States uses a multi-step Electoral College process 
where citizens vote on how each state should allocate Electors who then elect the President.
Perhaps the simplest way to hold an election, though, is via a method commonly known as the “plurality vote” (also known as “first-past-the-post” 
or “winner take all”). In the plurality vote, every voter gets to vote for one candidate. At the end of the election, whichever candidate has the greatest 
number of votes is declared the winner of the election.

Complete the implementation of plurality.c in such a way that the program simulates a plurality vote election.
- Complete the vote function - vote takes a single argument, a string called name, representing the name of the candidate who was voted for.
If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. 
The vote function in this case should return true to indicate a successful ballot.
If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return 
false to indicate an invalid ballot. You may assume that no two candidates will have the same name.
- Complete the print_winner function - The function should print out the name of the candidate who received the most votes in the election, 
and then print a newline. It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes. 
In that case, you should output the names of each of the winning candidates, each on a separate line. */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string temp_name = candidates[0].name;
    int temp_votes = candidates[0].votes;
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (candidates[i].votes < candidates[j].votes)
            {
                temp_name = candidates[i].name;
                temp_votes = candidates[i].votes;
                candidates[i].name = candidates[j].name;
                candidates[i].votes = candidates[j].votes;
                candidates[j].name = temp_name;
                candidates[j].votes = temp_votes;
            }
        }
    }
    if (candidates[0].votes == candidates[1].votes && candidates[1].votes == candidates[2].votes)
    {
        printf("%s\n%s\n%s\n", candidates[0].name, candidates[1].name, candidates[2].name);
    }
    else if (candidates[0].votes == candidates[1].votes)
    {
        printf("%s\n%s\n", candidates[0].name, candidates[1].name);
    }
    else
    {
        printf("%s\n", candidates[0].name);
    }
    return;
}
