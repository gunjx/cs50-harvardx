#include <math.h>
#include <cs50.h>
#include <stdio.h>
#define Q 25
#define D 10
#define N 5
#define P 1

int main(void)
{
    float change;

    // Ask user for non-negative float input
    do
    {
        printf("Change owed: ");
        change = get_float();
    }
    while (change < 0);

    // Convert dollar value into cents
    int cent = round(100 * change);

    // Define values for coin size
    int size[4] = {Q, D, N, P};

    // Calculate number of coins until amount is zero
    int coin = 0, i = 0;
    while (cent)
    {
        // Start fitting largest coin size, increment coin number
        coin = coin + floor(cent / size[i]);
        cent = cent % size[i];
        i++;
    }
    printf("%i\n", coin);
}
