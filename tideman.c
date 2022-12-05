/* There’s another kind of voting system known as a ranked-choice voting system. In a ranked-choice system, voters can vote for 
more than one candidate. Instead of just voting for their top choice, they can rank the candidates in order of preference.
Here, each voter, in addition to specifying their first preference candidate, has also indicated their second and third choices. 
And now, what was previously a tied election could now have a winner.
Ranked choice voting can also solve yet another potential drawback of plurality voting.
The Tideman voting method (also known as “ranked pairs”) is a ranked-choice voting method that’s guaranteed to produce the Condorcet 
winner of the election if one exists. Generally speaking, the Tideman method works by constructing a “graph” of candidates, where 
an arrow (i.e. edge) from candidate A to candidate B indicates that candidate A wins against candidate B in a head-to-head matchup.
Looking at this graph, the Tideman method says the winner of the election should be the “source” of the graph 
(i.e. the candidate that has no arrow pointing at them).
Put more formally, the Tideman voting method consists of three parts:
- Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred 
candidate is and by what margin they are preferred.
- Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number 
of voters who prefer the preferred candidate.
- Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, 
so long as locking in that pair does not create a cycle in the graph.
Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!

Complete the implementation of tideman.c in such a way that it simulates a Tideman election.
- vote - The function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate, then you should update the 
ranks array to indicate that the voter has the candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)
Recall that ranks[i] here represents the user’s ith preference. The function should return true if the rank was successfully recorded, and false otherwise 
(if, for instance, name is not the name of one of the candidates). You may assume that no two candidates will have the same name.
- record_preferences - The function is called once for each voter, and takes as argument the ranks array, (recall that ranks[i] is the voter’s ith preference, 
where ranks[0] is the first preference). The function should update the global preferences array to add the current voter’s preferences. 
Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j. 
You may assume that every voter will rank each of the candidates.
- add_pairs - The function should add all pairs of candidates where one candidate is preferred to the pairs array. A pair of candidates who are tied 
(one is not preferred over the other) should not be added to the array. The function should update the global variable pair_count to be the number 
of pairs of candidates. (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).
- sort_pairs - The function should sort the pairs array in decreasing order of strength of victory, where strength of victory is defined to be the 
number of voters who prefer the preferred candidate. If multiple pairs have the same strength of victory, you may assume that the order does not matter.
- lock_pairs - The function should create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.
- print_winner function - The function should print out the name of the candidate who is the source of the graph. */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int find_winner(int arr[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    //setting all preferences to 0
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
        }
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //valide vote
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        preferences[ranks[i]][ranks[i + 1]]++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //temporary variable for sorting
    pair temp;
    //loop for the first element
    for (int i = 0; i < pair_count - 1; i++)
    {
        //loop for the second element
        for (int j = i + 1; j < pair_count; j++)
        {
            //comparing firs and second element and if needed - swap their positions
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                temp.winner = pairs[i].winner;
                temp.loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = temp.winner;
                pairs[j].loser = temp.loser;
            }
        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // locked[i][j] means i is locked in over j
    //bool locked[MAX][MAX];
    for (int i = 0; i < pair_count; i++)
    {
        //Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph,
        //so long as locking in that pair does not create a cycle in the graph
        if (locked[pairs[i].loser][pairs[i].winner] == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //inicializing array for storing number of arrows pointing towards each candidate
    int arr[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        arr[i] = 0;
    }
    //check each candidates how much arrows are pointed towards him
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                arr[i]++;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (arr[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
