#include <stdio.h>
#include <cs50.h>
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
{
    // Iterating through each candidate index in the struct
    for (int i = 0; i < candidate_count; i++)
    {
       if (strcmp(candidates[i].name, name) == 0)
       {
           // Dzięki przypisaniu tego indexu, będzie można potem się do niego dostać dzięki iterowaniu po tablicy --> przyda się w porównywaniu potem
           preferences[voter][rank] = i;
           return true;
       }
    }
   return false;
}

// Tabulate (arrange) votes for non-eliminated candidates
void tabulate(void)
{
    // i represents each voter (czyli rzędy w dwuwymiarowej tablicy preferencji)
    for (int i = 0; i < voter_count; i++)
    {
        // Iterujemy normalnie przez każdego votera (i) i potem przez każdy jego vote od topowego aż do break'a, czyli napotkania kogoś kto nie jest wyeliminowany
        // (j = 0 --> Rank 1)
        // Mając wypełnioną tablicę dwuwymiarową preferences w powyższej funkcji "vote" możemy od razu dostać się do indexu w struct'cie kandydatów

        for (int j = 0; j < candidate_count; j++)
        {
            // Po napotkaniu pierwszej osoby, która nie jest wyeliminowana dodajemy jej jeden vote i wychodzimy z pętli przechodząc do następnego voter'a
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
    // Total votes = voter_count ---> we are looking for number that is bigger than half
    for (int i = 0; i < candidate_count; i++)
    {
       if (candidates[i].votes > (voter_count / 2))
       {
           printf("%s", candidates[i].name);
           return true;
       }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Przypisujesz pierwszą wartość do liczby napewno większej niż każda ilość vote'ówinnej zmiennej i potem cały czas porównujesz ze wszystkimi (bubble sort chyba)
    // i wtedy masz najniższą
    int min = voter_count + 1;

    // Consider only candidates that has not yet been eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].eliminated == false) && (candidates[i].votes < min))
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between ALL (NON-eliminated) candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // It takes only one non-eliminated candidate to have different number of votes than the min
        if ((candidates[i].eliminated == false) && (candidates[i].votes != min))
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // Eliminating anyone still in the race that has min number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].eliminated == false) && (candidates[i].votes = min))
        {
            candidates[i].eliminated = true;
        }
    }
}
