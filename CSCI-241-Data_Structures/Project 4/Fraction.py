from Binary_Search_Tree import Binary_Search_Tree

class Fraction:

  def __init__(self, numerator, denominator):
    # Use caution here... In most languages, it is not a good idea to raise an exception from a constructor.
    # Python is a bit different and it shouldn't cause a problem here.
    if denominator == 0:
      raise ZeroDivisionError
    self.__n = numerator
    self.__d = denominator
    self.__reduce()

  @staticmethod
  def gcd(n, d):
    while d != 0:
      t = d
      d = n % d
      n = t
    return n

  def __reduce(self):
    if self.__n < 0 and self.__d < 0:
      self.__n = self.__n * -1
      self.__d = self.__d * -1

    divisor = Fraction.gcd(self.__n, self.__d)
    self.__n = self.__n // divisor
    self.__d = self.__d // divisor

  def __add__(self, addend):
    num = self.__n * addend.__d + self.__d * addend.__n
    den = self.__d * addend.__d
    return Fraction(num, den)

  def __sub__(self, subtrahend):
    num = self.__n * subtrahend.__d - self.__d * subtrahend.__n
    den = self.__d * subtrahend.__d
    return Fraction(num, den)

  def __mul__(self, multiplicand):
    num = self.__n * multiplicand.__n
    den = self.__d * multiplicand.__d
    return Fraction(num, den)

  def __truediv__(self, divisor):
    if divisor.__n == 0:
      raise ZeroDivisionError
    num = self.__n * divisor.__d
    den = self.__d * divisor.__n
    return Fraction(num, den)

  def __lt__(self, other):
    return self.__n * other.__d < other.__n * self.__d
    # Return True if self is less than other and False otherwise.
    # Recall that floating-point representation is imprecise.
    # Use cross-multiplication to remain in the integer domain.

  def __gt__(self, other):
    return True if self.__n * other.__d > other.__n * self.__d else False
    # Return True if self is greater than other and False otherwise.
    # Recall that floating-point representation is imprecise.
    # Use cross-multiplication to remain in the integer domain.

  def __eq__(self, other):
    return self.__n * other.__d == other.__n * self.__d
    # Return True if self equal to other and False otherwise.
    # Note that fractions are stored in reduced form.
    # Recall that floating-point representation is imprecise.
    # Use cross-multiplication to remain in the integer domain.

  def to_float(self):
    # This is safe because we don't allow a zero denominator
    return self.__n / self.__d

  def __str__(self):
    return str(self.__n) + '/' + str(self.__d)

  # the __repr__ method is similar to __str__, but is called when Python wants to display these objects in a container like a Python list.
  def __repr__(self):
    return str(self)

if __name__ == '__main__':
  first = Fraction(1, 5)
  second = Fraction(7, 3)
  third = Fraction(20, 2)
  fourth = Fraction(25, 1000)
  fifth = Fraction(10000, 1)
  sixth = Fraction(5, 2)
  seventh = Fraction(4, 2)
  array = [first, second, third, fourth, fifth, sixth, seventh]
  fraction_tree = Binary_Search_Tree()
  for x in array:
    fraction_tree.insert_element(x)
  print("Original Array:", array)
  print("In-order traversal of array:", fraction_tree.in_order())
  # TODO create a bunch of fraction objects and store them in an array.
  # Then insert each item from the array into a balanced BST.
  # Then get the in-order array representation of the BST using the new to_list() method, which you must implement.
  # Print the original and in-order traversal arrays to show that the fractions have been sorted.
