from Deque_Generator import get_deque

class Stack:

  def __init__(self):
    """Initialize"""
    # O(1): one step taken
    self.__dq = get_deque()

  def __str__(self):
    """Return String"""
    # O(n): the deque string methods are explained in their files
    return str(self.__dq)

  def __len__(self):
    """Return Length"""
    # O(1): length is a stored value
    return len(self.__dq)

  def push(self, val):
    """Create New Value at Front"""
    # O(1): push_front() can instantly find the front's location and insert the value
    self.__dq.push_front(val)

  def pop(self):
    """Delete & Return Front Value"""
    # O(1): pop_front() can instantly find the front's location and remove the value
    return self.__dq.pop_front()

  def peek(self):
    """Return Front Value"""
    # O(1): peek_front() can instantly find the front's location and return the value
    return self.__dq.peek_front()

# Unit tests make the main section unneccessary.
