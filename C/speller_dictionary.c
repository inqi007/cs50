// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
//Counter
int count_words = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Obtains the hash value
    int y = hash(word);
    //Iterates over the hash table
    for (node *tmp = table[y]; tmp != NULL; tmp = tmp->next)
    {
        //Compares word in dictionary with linked list
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    
    //Changes word to lowercase
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Make an array to store word in text
    char words[LENGTH + 1];
    
    //Open dictionary 
    FILE *reference = fopen(dictionary, "r");
    if (reference == NULL)
    {
        return false;
    }
    //Scans words from dictionary into array words
    while (fscanf(reference, "%s", words) != EOF)
    {
        //Allocates memory for a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //Copies word from dictionary into linked list
        strcpy(n->word, words);
        int x = hash(n->word);
        
        if (table[x] == NULL)
        {
            //Connects the first node with the head of the hash table
            table[x] = n;
            n->next = NULL;
        }
        else
        {
            //Adds a new node into the hashtable
            n->next = table[x];
            table[x] = n;
        }
        //Counts the number of words in the dictionary
        count_words++;
    }
    fclose(reference);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Number of words in the dictionary
    return count_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Iterates over all the nodes in the hashtable to free the node 
    for (int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
