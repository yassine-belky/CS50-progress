// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void unload_node(node *node);
bool mystrcmp(char word1[LENGTH + 1], const char *word);

// TODO: Choose number of buckets in hash table
const unsigned int N = 25 * LENGTH;

// Hash table
node *table[N];

bool mystrcmp(char dict_word[LENGTH + 1], const char *word)
{
    if (strlen(dict_word) != strlen(word))
    {
        return false;
    }

    for (int i = 0; i < strlen(dict_word); i++)
    {
        if (tolower(dict_word[i]) != tolower(word[i]))
        {
            return false;
        }
    }

    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_ = hash(word);
    node *cursor = table[hash_];

    while (cursor != NULL)
    {
        if (mystrcmp(cursor->word, word))
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_ = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            hash_ += tolower(word[i]) - 'a';
        }
    }

    return hash_;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *infile = fopen(dictionary, "r");
    if (!infile)
    {
        printf("Could not read file %s\n", dictionary);
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(infile, "%s", word) == 1)
    {
        unsigned int word_hash = hash(word);

        node *new = malloc(sizeof(node));
        if (!new)
        {
            printf("Not enough memory\n");
            return false;
        }

        strncpy(new->word, word, LENGTH + 1);
        new->next = table[word_hash];
        table[word_hash] = new;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        if (!cursor)
        {
            continue;
        }

        while (cursor->next)
        {
            size += strlen(cursor->word);
            cursor = cursor->next;
        }
    }

    return size;
}

void unload_node(node *node)
{
    if (!node)
    {
        return;
    }
    else
    {
        unload_node(node->next);
        free(node);
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        unload_node(table[i]);
    }
    return true;
}
