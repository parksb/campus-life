"""
CSE200 Data Structures
Author: Department of Digital Media 201700000 박성범
Date: 2018.3.16
"""

def gcd(m, n):
    while m % n != 0:
        m, n = n, m % n
    return n

class Fraction:
    """Fraction and its relevant operations"""
    def __init__(self, numerator, denominator):
        self._num = numerator
        self._denom = denominator

    def __repr__(self):
        return str(self)

    def __str__(self):
        return str(self._num) + "/" + str(self._denom)

    def __add__(self, other):
        """Addition"""
        new_num = self._num * other._denom + self._denom * other._num
        new_denom = self._denom * other._denom
        common = gcd(new_num, new_denom)

        return Fraction(new_num // common, new_denom // common)

    def __sub__(self, other):
        """Subtraction"""
        new_num = self._num * other._denom - self._denom * other._num
        new_denom = self._denom * other._denom
        common = gcd(new_num, new_denom)

        if (new_num // common) == 0:
            return 0
        else:
            return Fraction(new_num // common, new_denom // common)

    def __mul__(self, other):
        """Multiplication"""
        new_num = self._num * other._num
        new_denom = self._denom * other._denom
        common = gcd(new_num, new_denom)

        return Fraction(new_num // common, new_denom // common)

    def __truediv__(self, other):
        """Division"""
        new_num = self._num * other._denom
        new_denom = self._denom * other._num
        common = gcd(new_num, new_denom)

        return Fraction(new_num // common, new_denom // common)

    def __eq__(self, other):
        """Equal to"""
        return (self._num * other._denom) == (other._num * self._denom)

    def __ne__(self, other):
        """Not equal to"""
        return (self._num * other._denom) != (other._num * self._denom)

    def __lt__(self, other):
        """Less than"""
        return (self._num * other._denom) < (other._num * self._denom)

    def __gt__(self, other):
        """Greater than"""
        return (self._num * other._denom) > (other._num * self._denom)

    def __le__(self, other):
        """Less than or equal to"""
        return (self._num * other._denom) <= (other._num * self._denom)

    def __ge__(self, other):
        """Greater than or equal to"""
        return (self._num * other._denom) >= (other._num * self._denom)

if __name__ == "__main__":
    my_fraction = Fraction(3, 5)
    print("Fraction(3,5) will be", my_fraction)
    print("I ate", my_fraction, "of the pizza.")

    f1 = Fraction(1, 4)
    f2 = Fraction(1, 2)
    print("1/4 + 1/2 =", f1 + f2)
    print("1/4 - 1/2 =", f1 - f2)
    print("1/4 * 1/2 =", f1 * f2)
    print("1/4 / 1/2 =", f1 / f2)

    f1 = Fraction(1, 2)
    f2 = f1
    print("Is f1 identical to f2?", f1 is f2)
    print("Is f1 equal to f2?", f1 == f2)
    print("Is f1 not equal to f2?", f1 != f2)
    print("Is f1 is greater than f2?", f1 > f2)
    print("Is f1 is less than f2?", f1 < f2)
    print("Is f1 is greater than or equal to f2?", f1 >= f2)
    print("Is f1 is less than or equal to f2?", f1 <= f2)

    f2 = Fraction(1, 3)
    print("Is f1 identical to f2?", f1 is f2)
    print("Is f1 equal to f2?", f1 == f2)
    print("Is f1 not equal to f2?", f1 != f2)
    print("Is f1 is greater than f2?", f1 > f2)
    print("Is f1 is less than f2?", f1 < f2)
    print("Is f1 is greater than or equal to f2?", f1 >= f2)
    print("Is f1 is less than or equal to f2?", f1 <= f2)