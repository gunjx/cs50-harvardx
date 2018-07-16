#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ALPHALEN 26

// Prototypes
void check(char *pw, char *hash, char *salt, int *index);
void crack(char *pw, char *hash, char *salt);

// Converting command line arguments and calling crack function
int main (int argc, char *argv[])
{
    // Check for command line argument
    if (argc != 2)
    {
        printf("Usage: ./crack hash.\nError Code: 1\n");
        return 1;
    }

    // Convert hash and salt from user input
    char *hash = argv[1];
    char salt[2];
    for (int i = 0; i < 2; i++)
        salt[i] = argv[1][i];

    // Create permutations of lower and uppercase a for password length 1 to 5
    // Permutations ordered by likelihood of user input and computing efficiency
    // Try to solve with iteration? char s[6] = {'\0'}; strcpy(s, "a");

    crack("a", hash, salt);
    crack("A", hash, salt);

    crack("aa", hash, salt);
    crack("AA", hash, salt);
    crack("Aa", hash, salt);

    crack("aaa", hash, salt);
    crack("AAA", hash, salt);
    crack("Aaa", hash, salt);

    crack("aaaa", hash, salt);
    crack("AAAA", hash, salt);
    crack("Aaaa", hash, salt);

    crack("aaaaa", hash, salt);
    crack("AAAAA", hash, salt);
    crack("Aaaaa", hash, salt);

    crack("aA", hash, salt);

    crack("AaA", hash, salt);
    crack("AAa", hash, salt);
    crack("aaA", hash, salt);
    crack("aAa", hash, salt);
    crack("aAA", hash, salt);

    crack("AaaA", hash, salt);
    crack("AaAa", hash, salt);
    crack("AaAA", hash, salt);
    crack("AAaa", hash, salt);
    crack("AAaA", hash, salt);
    crack("AAAa", hash, salt);
    crack("aaaA", hash, salt);
    crack("aaAa", hash, salt);
    crack("aaAA", hash, salt);
    crack("aAaa", hash, salt);
    crack("aAaA", hash, salt);
    crack("aAAa", hash, salt);
    crack("aAAA", hash, salt);

    crack("AAaaa", hash, salt);
    crack("AAaaA", hash, salt);
    crack("AAaAa", hash, salt);
    crack("AAaAA", hash, salt);
    crack("AAAaa", hash, salt);
    crack("AAAaA", hash, salt);
    crack("AAAAa", hash, salt);
    crack("AaaaA", hash, salt);
    crack("AaaAa", hash, salt);
    crack("AaaAA", hash, salt);
    crack("AaAaa", hash, salt);
    crack("AaAaA", hash, salt);
    crack("AaAAa", hash, salt);
    crack("AaAAA", hash, salt);

    crack("aAAAA", hash, salt);
    crack("aAaaa", hash, salt);
    crack("aAaaA", hash, salt);
    crack("aAaAa", hash, salt);
    crack("aAaAA", hash, salt);
    crack("aAAaa", hash, salt);
    crack("aAAaA", hash, salt);
    crack("aAAAa", hash, salt);
    crack("aaaaA", hash, salt);
    crack("aaaAa", hash, salt);
    crack("aaaAA", hash, salt);
    crack("aaAaa", hash, salt);
    crack("aaAaA", hash, salt);
    crack("aaAAa", hash, salt);
    crack("aaAAA", hash, salt);
}

// Compare user input hash with generated hash using crypt function
void check(char *pw, char *hash, char *salt, int *index)
{
    // Shift pw by loop's index number
    char key[6];
    for (int n = 0; pw[n] != '\0'; n++)
    {
        strcpy(&key[n], &pw[n]);
        key[n] = key[n] + index[n];
    }

    // Generate hash from shifted pw
    char *gen = crypt(key, salt);

    // Check values for shifted pw, index and generated hash
    // printf("%s, %i %i %i %i %i and %s\n", key, index[0], index[1], index[2], index[3], index[4], gen);
    // sleep(1);

    // Check if generated hash matches user input
    if (!strcmp(gen, hash))
    {
        printf("%s\n", key);
        exit(0);
    }
}

// Create nested loop and call check function
void crack(char *pw, char *hash, char *salt)
{
    int index[5] = {0};
    if (strlen(pw) >= 1)
        for (int i = 0; i < ALPHALEN; i++)
        {
            index[0] = i;
            if (strlen(pw) == 1)
                check(pw, hash, salt, index);

            if (strlen(pw) >= 2)
                for (int j = 0; j < ALPHALEN; j++)
                {
                    index[1] = j;
                    if (strlen(pw) == 2)
                        check(pw, hash, salt, index);

                    if (strlen(pw) >= 3)
                        for (int k = 0; k < ALPHALEN; k++)
                        {
                            index[2] = k;
                            if (strlen(pw) == 3)
                                check(pw, hash, salt, index);

                            if (strlen(pw) >= 4)
                                for (int l = 0; l < ALPHALEN; l++)
                                {
                                    index[3] = l;
                                    if (strlen(pw) == 4)
                                        check(pw, hash, salt, index);

                                    if (strlen(pw) >= 5)
                                        for (int m = 0; m < ALPHALEN; m++)
                                        {
                                            index[4] = m;
                                            if (strlen(pw) == 5)
                                                check(pw, hash, salt, index);
                                        }
                                }
                        }
                }
        }
}
