/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Terminate program (error code 1) and print correct usage of function syntax if user doesn't use exactly 1 or 2 command-line arguments
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Convert first user input (command-line argument) from string to integer data type and store in variable n
    int n = atoi(argv[1]);

    // If user inputs seed as second command-line argument, call function srand48 with that seed, else call srand48 with seconds passed since Epoch
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    // Print as many random (integer) numbers as the user specified as command-line argument
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // Success
    return 0;
}
