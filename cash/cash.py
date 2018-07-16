from cs50 import get_float

Q = 25
D = 10
N = 5
P = 1

change = 0

# Ask user for non-negative float input
while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

# Convert dollar value into cents
cent = round(100 * change)

# Defining values for coin size
size = [Q, D, N, P]

# Calculate number of coins until amount is zero
coin, i = 0, 0
while cent:

    # Start fitting largest coin size, increment coin number
    coin = coin + (cent // size[i])
    cent = cent % size[i]
    i += 1

print(coin)
