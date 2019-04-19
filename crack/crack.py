import crypt
import sys
import itertools

# Magic numbers
ALPHALEN = 26


def main():
    """Converting command line arguments and calling crack function"""
    if len(sys.argv) != 2:
        print("Usage: python crack hash")
        sys.exit(1)

    # Convert hash and salt from user input
    var_salt = "".join(sys.argv[1][:2])
    var_hash = "".join(sys.argv[1])

    # Call last permutation first for efficiency reasons
    crack("AAAAA", var_hash, var_salt)

    # Create permutations of lower and uppercase a for password length 1 to 5
    for i in range(1, 6):
        perm = list(itertools.product("aA", repeat=i))
        for s in perm:
            crack("".join(s), var_hash, var_salt)


def check(pw, var_hash, var_salt, index):
    """Compare user input hash with generated hash using crypt function"""

    # Shift pw by loop's index number
    tmp = list(pw).copy()
    for n in range(len(tmp)):
        tmp[n] = chr(ord(tmp[n]) + index[n])
    key = "".join(tmp)

    # Gemerate hash from shifted password
    gen = "".join(crypt.crypt(key, var_salt))

    # Check if hash generated matches user input
    if gen == var_hash:
        print(key)
        sys.exit(0)


def crack(pw, var_hash, var_salt):
    """Create nested loop and call check function"""

    index = [0, 0, 0, 0, 0]
    if len(pw) >= 1:
        for i in range(ALPHALEN):
            index[0] = i
            if len(pw) == 1:
                check(pw, var_hash, var_salt, index)

            if len(pw) >= 2:
                for j in range(ALPHALEN):
                    index[1] = j
                    if len(pw) == 2:
                        check(pw, var_hash, var_salt, index)

                    if len(pw) >= 3:
                        for k in range(ALPHALEN):
                            index[2] = k
                            if len(pw) == 3:
                                check(pw, var_hash, var_salt, index)

                            if len(pw) >= 4:
                                for l in range(ALPHALEN):
                                    index[3] = l
                                    if len(pw) == 4:
                                        check(pw, var_hash, var_salt, index)

                                    if len(pw) >= 5:
                                        for m in range(ALPHALEN):
                                            index[4] = m
                                            if len(pw) == 5:
                                                check(pw, var_hash, var_salt, index)


if __name__ == "__main__":
    main()
