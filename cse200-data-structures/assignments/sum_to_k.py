import random


def remove_duplicate(L):
    ht = {}
    result = []

    for key, value in L:
        if (key not in ht) or (key in ht and ht[key] is not value):
            ht[key] = value
            result.append((key, value))

    return result


def sum2K(L, K):
    result = []
    ht = {}

    for el in L:
        if el in ht:
            if type(ht[el]) is list:
                ht[el].append(el)
            else:
                ht[el] = [el, el]
        else:
            ht[el] = el

    for num in L:
        target = K - num
        if target in ht:
            if type(ht[target]) is list:
                result.append((ht[target][0], num))
            elif K is not ht[target] * 2:
                result.append((ht[target], num))

    return remove_duplicate(result)


if __name__ == "__main__":
    count = 30
    L = []

    for i in range(count):
        L.append(random.randrange(1, 101))

    K = random.randrange(1, 101)

    print("L:", L)
    print("K:", K)

    print("Result:", sum2K(L, K))