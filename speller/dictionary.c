// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Define node
typedef struct _node
{
    char letter; // Alternative impementation with bool is_word
    struct _node *children[28];
}
node;

// Declare trie root and travel pinter
node *root;
node **trav = &root;

// Initialize global dictcount
static unsigned int dictcount;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dictfile = fopen(dictionary, "r");
    if (!dictfile)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Initialize trie root
    root = calloc(1, sizeof(node));

    // Iterate through every word from dictionary
    char dictword[LENGTH + 1];
    while (fscanf(dictfile, "%s", dictword) != EOF)
    {
        // Add dictionary word to trie letter by letter
        for (int i = 0, index = 0, len = strlen(dictword); i <= len; i++)
        {
            // Create character index
            char c = tolower(dictword[i]);
            if (c == '\'')
                index = 26;
            else if (c == '\0')
                index = 27;
            else index = c - 'a';
            if (index < 0)
            {
                printf("index is %i\n", c);
                break;
            }

            // Create node if it does not exist
            if (!(*trav)->children[index])
            {
                node *n = calloc(1, sizeof(node));
                if (!n)
                {
                    fclose(dictfile);
                    return false;
                }

                // Write char to node, append
                n->letter = dictword[i];
                (*trav)->children[index] = n;
            }

            // Traverse
            if ((*trav)->children[index]->letter == dictword[i])
                trav = &(*trav)->children[index];
            else return false;
        }

        // Increment dictionary word count for every full word
        dictcount++;
        trav = &root;
    }
    fclose(dictfile);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Check each letter in word
    bool lettercheck = false;
    for (int i = 0, index = 0, len = strlen(word); i <= len; i++)
    {
        // Create character index
        char c = tolower(word[i]);
        if (c == '\'')
            index = 26;
        else if (c == '\0')
            index = 27;
        else index = c - 'a';

        // Compare letter with element in children
        if (!(*trav)->children[index])
        {
            trav = &root;
            return false;
        }
        else if ((*trav)->children[index]->letter != word[i])
            lettercheck = false;
        else if ((*trav)->children[index]->letter == word[i] || word[i] == '\0')
            lettercheck = true;

        // Traverse
        trav = &(*trav)->children[index];
    }
    trav = &root;
    return lettercheck;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (dictcount != 0)
        return dictcount;
    else return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Recursive unloading
    bool empty = false;
    node *n = *trav;

    // Check elements of pointer array for NULL
    for (int index = 0; index < 28; index++)
    {
        if (!n->children[index])
            empty = true;
        else
        {
            *trav = n->children[index];
            empty = unload(); // Recursive unloading
        }
    }
    // If all elements of array are NULL, free and backtrack
    if (empty)
    {
        free(n);
        return true;
    }
    return false;
}
