from Deque import Deque

class Array_Deque(Deque):

  def __init__(self):
    """Initialize"""
    # O(1). Capacity starts at 1; we will grow on demand.
    self.__capacity = 1
    self.__contents = [None] * self.__capacity
    self.len = 0
    self.front = 0
    self.back = self.len - 1
    
  def __str__(self):
    """Return String Representation of the Array"""
    # O(n): The method's loop must run once for every n item in len(d)
    if self.len == 0: # Case for an empty list
        string = "[ ]"
        return string
    # Open string "[", append string by looping through list length, close string "]"
    string = "[ "
    for index in range(self.front, self.back + 1):
      string = string + str(self.__contents[(index + self.__capacity) % self.__capacity]) + ", "
    string = string[:-2] + " ]"
    return string
    
  def __len__(self):
    """Return Length"""
    # Self-defined version of length. O(1)
    return self.len

  def __grow(self):
    """Doubles List Capacity"""
    # O(n): The method's loop must run once for every n item in len(deque)
    # Create a new array with double the previous array's capacity
    copy = [None] * (2 * self.__capacity)
    # Append previous array to ccopy starting at index 0 (represented by variable j)
    j = 0
    for index in range(self.front, self.back + 1):
      copy[j] = self.__contents[(index + self.len) % self.len]
      j += 1
    # Make the copy the new deque and redefine its qualities
    self.__contents = copy
    self.__capacity *= 2
    self.front = 0
    self.back = self.len - 1

  def push_front(self, val):
    """Create New Value at Front"""
    # O(1): this method can instantly find the front's index and insert the value
    if self.len == self.__capacity:
      self.__grow()
    self.len += 1
    self.front -= 1
    self.__contents[(self.front + self.__capacity) % self.__capacity] = val
    
  def pop_front(self):
    """Delete & Return Front Value"""
    # O(1): this method can instantly find the front's index and remove the value
    if  self.len == 0:
      return None
    pop = self.__contents[(self.front + self.__capacity) % self.__capacity]
    self.__contents[(self.front + self.__capacity) % self.__capacity] = None
    self.len -= 1
    self.front += 1
    return pop
    
  def peek_front(self):
    """Return Front Value"""
    # O(1): this method can instantly find the front's index and return the value
    if  self.len == 0:
      return None
    return self.__contents[(self.front + self.__capacity) % self.__capacity]
    
  def push_back(self, val):
    """Create New Value at Back"""
    # O(1): this method can instantly find the back's index and insert the value
    if self.len == self.__capacity:
      self.__grow()
    self.len += 1
    self.back += 1
    self.__contents[(self.back + self.__capacity) % self.__capacity] = val
  
  def pop_back(self):
    """Delete & Return Back Value"""
    # O(1): this method can instantly find the back's index and remove the value
    if  self.len == 0:
      return None
    pop = self.__contents[(self.back + self.__capacity) % self.__capacity]
    self.__contents[(self.back + self.__capacity) % self.__capacity] = None
    self.len -= 1
    self.back -= 1
    return pop

  def peek_back(self):
    """Return Back Value"""
    # O(1): this method can instantly find the back's index and return the value
    if  self.len == 0:
      return None
    return self.__contents[(self.back + self.__capacity) % self.__capacity]

# No main section is necessary. Unit tests take its place.
