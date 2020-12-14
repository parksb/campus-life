"""
Anagram Generator
Department of Digital Media 201700000 박성범
2018.4.2
"""


def generate_anagram(S):
    length = len(S)

    if length <= 1:
        return S
    else:
        L = []

        for S2 in generate_anagram(S[1:]):
            for i in range(length):
                newS = S2[:i] + S[:1] + S2[i:]
                if not (newS in L):
                    L.append(newS)

        return L


def main():
    string  = "abc"

    list = generate_anagram(string)

    for i in range(len(list)):
        print("{0} : {1}".format(i + 1, list[i]))


if __name__ == "__main__":
    main()