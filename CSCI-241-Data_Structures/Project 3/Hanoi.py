import timeit
from Stack import Stack

def Hanoi_rec(n, s, a, d):
  # O(2^n): Two recursion calls are made giving the runtime a base of two, and this recursion follows exponential time
  print(n, s, a, d)
  if n == 0: # BASE CASE
    # Whenever the stack or substack is done recursing, move disc to destination.
    d.push(s.pop())
  # The first recursion call starts by building an activation record for every n disc so that every ring will
  # be able to recurse through every "substack" (the rings above a base) which is done with the second recurssion call.
  # The dest and aux are switched so that the largest current substack moves its rings between
  # the aux and the dest until finally the largest substack (the entire original stack) is put onto the dest.
  else:
    Hanoi_rec(n-1, s, d, a)
    # The stack operators move a disc from the current source to the current destination.
    # This operation stays consistent with n=1.
    d.push(s.pop())
    # The second recursion call moves each base ring of a substack between the source and aux so that
    # the substack can be moved without putting a larger disc on top of a smaller one. This second call
    # also calls the first recursion reccursively to move all discs above the base of the substack.
    Hanoi_rec(n-1, a, s, d)
  print(n, s, a, d)
  print()

def Hanoi(n):
  source = Stack()
  dest = Stack()
  aux = Stack()
  i = n-1
  while i >= 0:
    source.push(i)
    i = i - 1
  Hanoi_rec(n-1, source, aux, dest)

if __name__ == "__main__":
  n=12
  runtime = timeit.timeit("Hanoi(n)", setup="from __main__ import Hanoi,n", number=1)
  print("computed Hanoi(" + str(n) + ") in " + str(runtime) + " seconds.")
