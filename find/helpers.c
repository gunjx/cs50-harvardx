/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

#define MAX 65536

/**
 * Recursive binary search.
 */
bool bisearch(int value, int values[], int left, int right, int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Return false for non-negative integers
    if (n < 1)
        return false;
    int left = 0, right = n-1;

    // Call and return value of recursive binary serach function
    return bisearch(value, values, left, right, n);

    /*// Backup: linear search function
    for(int i = 0; i < n; i++)
    {
        if (value == values[i])
            return true;
    }*/
}

/**
 * Recursive binary search.
 */
bool bisearch(int value, int values[], int left, int right, int n)
{
    // Fail condition ending the recursive search function: value not found in array
    if (left > right)
        return false;

    // Calculate middle of the array
    int middle = (right + left) / 2;

    // Divide and conquer
    if (values[middle] == value) // Success condition: value found in array
        return true;
    else if (values[middle] > value) // Else search left or right half of middle value
        right = --middle;
    else
        left = ++middle;

    // Recursive call
    return bisearch(value, values, left, right, n);
}


/**
 * Sorts array of n values with selection sort.
 */
void sort(int values[], int n)
{
    // Specify maximum size of count array
    int count[MAX] = {0};

    // Increment count array position by one for every value in values
    for (int i = 0; i < n; i++)
    {
        count[values[i]]++;
    }

    // Overwrite values with count array positions and decrementing count values until every array position has value 0
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for ( ; k < MAX; k++)
        {
            if (count[k] > 0)
            {
                values[i] = k;
                count[k]--;
                k--;
                break;
            }
        }
    }
    return;
}
