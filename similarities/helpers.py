from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Split each string into lines, remove duplicates, find lines in common
    return list(set(a.splitlines()) & set(b.splitlines()))


def sentences(a, b):
    """Return sentences in both a and b"""

    # Split each string into sentences, remove duplicates, find sentences in common
    return list(set(sent_tokenize(a)) & set(sent_tokenize(b)))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # Split each string into sentences, remove duplicates, find sentences in common
    set_a = {a[i : i + n] for i in range(len(a) - (n - 1))}
    set_b = {b[i : i + n] for i in range(len(b) - (n - 1))}
    return list(set_a & set_b)
