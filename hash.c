// #include <stdbool.h>
// #include <strings.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define LENGTH 45

// unsigned int hash(const char *word)
// {
//     unsigned long hash = 5381;
//     int c;
//     while ((c =* word++))
//     hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
//     return hash;
// }

// // TESTING IF FUNCTION WORKS PROPERLY
// // dokończyć pisać na dole ładniej
// // STESTOWAĆ KURWE i implementować dalsze funkcje


// // Represents a node in a hash table
// typedef struct node
// {
//     char word[LENGTH + 1];
//     struct node *next;
// }
// node;

// // to BĘDZIE pewnie TRZEBA ZMIENIĆ
// const unsigned int BUCKETS = 1000;

// // Hash table
// node *table[BUCKETS];


// node *createNode(char *word)
// {
//     // add comment later
//     node *n = malloc(sizeof(node));
//     strcpy(n->word, word);
//     n->next = NULL;

//     return n;
// }


// int getBucketIndex(char *word)
// {
//     return hash(word) % BUCKETS;
// }

// void setInHashtable(char *word)
// {
//     int bucketIndex = getBucketIndex(word);

//     node *n = createNode(word);

//     // table is a header (AKA bucket) of each linked list
//     // n->next points to the same thing that table points to (that is NULL - if it's the first element inserted to the list)
//     n->next = table[bucketIndex];
//     table[bucketIndex] = n;
// }


// // AKA check function
// char* findInHashtable(char* word)
// {
//     return table[getBucketIndex(word)]->word;
// }

// int main() {
//     setInHashtable("jacek");

//     printf("%s", findInHashtable("jacek")); // prints 1 if exists
//     printf("%s", findInHashtable("marlena")); // prints 0
// }