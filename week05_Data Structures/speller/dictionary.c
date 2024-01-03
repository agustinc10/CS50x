// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// const unsigned int N = 26;
const unsigned int N = LENGTH * 'Z';

// Hash table
node *table[N];

// Counter for size of file
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    if (table[index] == NULL)
        return false;
    node *cursor = table[index];
    if (cursor == NULL)
        return 1;
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
            cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int n = toupper(word[0]);
    int i = 1;

    while (word[i] != '\0')
    {
        n += toupper(word[i]);
        i++;
    }
    return n % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    // Read Strings from File
    char buffer[LENGTH + 1];
    int index;
    while (fscanf(infile, "%s", buffer) != EOF)
    {
        // Create new node
        node *new = malloc(sizeof(node));
        if (new == NULL)
            return false;
        strcpy(new->word, buffer);
        index = hash(new->word);
        new->next = table[index];
        table[index] = new;
        counter++;
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = table[0];
    node *tmp = cursor;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
