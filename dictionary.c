// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// to BĘDZIE pewnieTRZEBA ZMIENIĆ
const unsigned int BUCKETS = 10000;

// Variable for size function
int nodesInHashtable = 0;

// Hash table
node *table[BUCKETS];

// Lower every character in a string
void strtolower(char * dest, const char * src, int n)
{
    for(int i = 0; i < n; i++)
    {
        dest[i] = tolower(src[i]);
    }
}

// Get index between 1 and BUCKETS
unsigned int getBucketIndex(const char *word)
{
    return hash(word) % BUCKETS;
}

// Copy the word into the node
node* createNode(const char *word)
{
    // add comment later
    node* n = malloc(sizeof(node));
    strcpy(n->word, word);
    n->next = NULL;

    return n;
}


// Setting word in the hash table
void setInHashtable(char *word)
{
    // Store the index into the variable
    int bucketIndex = getBucketIndex(word);

    // Create node
    node *n = createNode(word);

    // Insert the node into the hash table
    n->next = table[bucketIndex]; /* n->next points to the same thing that table points to (that is NULL - if it's the first element inserted to the list)*/
    table[bucketIndex] = n; /* table is a header (AKA bucket) of each linked list*/
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file (store the adress of the dictionary in d)
    FILE *d = fopen(dictionary, "r"); /* d = adress of dictionary */
    if (d == NULL)
    {
        return false;
    }

    // Array of characters for later access
    char tmp_word[45];

    // Read file
    while(fscanf(d, "%s", tmp_word) != EOF)
    {

        setInHashtable(tmp_word);
        nodesInHashtable++;

    }

    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char* wordLowerCase = malloc(strlen(word));
    strtolower(wordLowerCase, word, strlen(word));

    // char* wordInLowerCase = toLowerCase(word)
    int bucket = getBucketIndex(wordLowerCase);

    node* cursor = table[bucket];

    // Traverse through the linked list at a given bucket
    while(cursor != NULL)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    free(wordLowerCase);

    return false;
}

// Hashes word to a number
// Dan Bernstein, djb2, comp.lang.c.
// SOURCE: http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return nodesInHashtable;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Free every linked-list individually
    for (int i = 0; i < BUCKETS; i++)
    {
        // Both cursor and tmp point to the same node (the one which table points to)
        node* cursor = table[i];
        node* tmp = cursor;
        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
