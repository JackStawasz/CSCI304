import sys # for sys.argv, the command-line arguments
from Stack import Stack

def delimiter_check(filename):
  """Check for balanced delimiters"""
  # Returns True if the delimiters (), [], and {} are balanced and False otherwise.
  stack = Stack
  for delimiter in filename:
    # Push open delimiters onto the stack
    if delimiter == "(" or delimiter == "[" or delimiter == "{":
      stack.push(delimiter)
    # Remove closing delimiters if they corresppond with the previous opening delimiter.
    elif delimiter == ")":
      if stack.peek() == "(":
        stack.pop()
      else:
        return False
    elif delimiter == "]":
      if stack.peek() == "[":
        stack.pop()
      else:
        return False
    elif delimiter == "}":
      if stack.peek() == "{":
        stack.pop()
      else:
        return False
  # If the loop makes it through the whole string, then the delimiters are balanced
  return True

if __name__ == '__main__':
  # The list sys.argv contains everything the user typed on the command line after the word python. For example, if the user types
  # python Delimiter_Check.py file_to_check.py then printing the contents of sys.argv shows
  # ['Delimiter_Check.py', 'file_to_check.py']
  if len(sys.argv) < 2:
    # This means the user did not provide the filename to check. Show the correct usage.
    print('Usage: python Delimiter_Check.py file_to_check.py')
  else:
    if delimiter_check(sys.argv[1]):
      print('The file contains balanced delimiters.')
    else:
      print('The file contains IMBALANCED DELIMITERS.')
