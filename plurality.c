#include <cs50.h>
#include <stdio.h>
#include <string.h>

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

    // In this place we already have vote count set to 0 and the name of the candidate

    int voter_count = get_int("Number of voters: ");

    // Here we have the number of voters - each one of them will vote for one candidate

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        // CZYLI: if vote returns false then it will print "Invalid vote",
        // otherwise (true) it will do nothing
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
        if (strcmp(candidates[i].name, name) == 0)
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
    // Declaring variables to store temporary information to use in a next loop
    int current_highest_votetotal = candidates[0].votes;

    // Starting from i=1 so that candidates[1].votes can be compared to [0] place in array (as is set in line above)
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > candidates[i - 1].votes)
        {
            current_highest_votetotal = candidates[i].votes;
        }
    }

    // If a given voter has equal number of votes to the highest one (which was established in the loop above)
    // print its name
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == current_highest_votetotal)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    
    return;
}