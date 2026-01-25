class Binary_Search_Tree:

  class __BST_Node:

    def __init__(self, value):
      # O(1)
      self.value = value
      self.left = None
      self.right = None
      self.height = 1

  def __init__(self):
    # O(1)
    self.__root = None
  
  def __set_height(self, node):
    """Set Height of Called Node"""
    # O(n): this method traverses all n nodes of the left and right subtrees
    if not node:
      return 0
    return max(self.__set_height(node.left), self.__set_height(node.right)) + 1

  def __get_balance(self, node):
    """Return a Node's Balance"""
    # O(1): number of operations are independent of the number of nodes
    if not node:
      return 0
    l_height = node.left.height if node.left else 0
    r_height = node.right.height if node.right else 0
    return r_height - l_height
  
  def __rotate_left(self, node):
    """Rotate Tree Leftwards"""
    # O(1): number of operations are independent of the number of nodes
    new_root = node.right
    node.right = node.right.left
    new_root.left = node
    new_root.height = self.__set_height(new_root)
    node.height = self.__set_height(node)
    return new_root

  def __rotate_right(self, node):
    """Rotate Tree Rightwards"""
    # O(1): number of operations are independent of the number of nodes
    new_root = node.left
    node.left = node.left.right
    new_root.right = node
    new_root.height = self.__set_height(new_root)
    node.height = self.__set_height(node)
    return new_root

  def __balanced(self, node):
    """Balance the Called Node"""
    # O(1): for every case scenario, only constant-time operations are called
    if not node: # Base case
      return node
    balance = self.__get_balance(node)
    if balance in (-1, 0, 1): # Balanced case
      return node
    elif balance == -2: # Left-heavy
      l_balance = self.__get_balance(node.left)
      if l_balance in (-1, 0): # Left-Left --> right rotation
        new_root = self.__rotate_right(node)
      elif l_balance == 1: # Left-Right --> rotate left subtree left, rotate tree right
        node.left = self.__rotate_left(node.left)
        new_root = self.__rotate_right(node)
    elif balance == 2: # Right-heavy
      r_balance = self.__get_balance(node.right)
      if r_balance in (0, 1): # Right-Right --> left rotation
        new_root = self.__rotate_left(node)
      elif r_balance == -1: # Right-Left --> rotate right subtree right, rotate tree left
        node.right = self.__rotate_right(node.right)
        new_root = self.__rotate_left(node)
    # Ensure that the self.__root pointer still points to the top of the tree
    if node is self.__root:
      self.__root = new_root
    return new_root

  def __insert_rec(self, node, value):
    """Find BST Insert Position and Create a New Node at Position"""
    # O(log n): since the tree is balanced, every recursion to search for the
    # insert position cuts the remaining n items in half leading to logarithmic-time
    if node == None: # Base Case
      return self.__BST_Node(value)
    # Decide to go either left or right
    elif value < node.value:
      node.left = self.__insert_rec(node.left, value)
      node.height = self.__set_height(node)
    elif value > node.value:
      node.right = self.__insert_rec(node.right, value)
      node.height = self.__set_height(node)
    # BSTs cannot have duplicate values
    elif value == node.value:
      raise ValueError
    return self.__balanced(node)

  def insert_element(self, value):
    """Insert Element at Correct BST Position"""
    # O(log n): see __insert_rec() for details
    # This function holds the recursion control variables
    if self.__root == None:
      self.__root = self.__BST_Node(value)
    else:
      self.__insert_rec(self.__root, value)

  def __remove_element_rec(self, node, value):
    """Find Node Position and Remove"""
    # O(log n): since the tree is balanced, every recursion to search for the
    # insert position cuts the remaining n items in half leading to logarithmic-time
    if node == None: # Base Case
      return node
    # Decide to go either left or right
    elif value < node.value:
      node.left = self.__remove_element_rec(node.left, value)
      node.height = self.__set_height(node)
      return self.__balanced(node)
    elif value > node.value:
      node.right = self.__remove_element_rec(node.right, value)
      node.height = self.__set_height(node)
      return self.__balanced(node)
    # 1 child case: replace the node with its right child
    # 0 children case: if the node has no real children, replacing it with its child will replace the node with None anyways
    elif node.left is None:
      delete = node.right
      node = None
      return self.__balanced(delete)
    elif node.right is None:
      delete = node.left
      node = None
      return self.__balanced(delete)
    # 2 children case:
    elif node.left and node.right:
      replace = node.right
      while replace.left:
        replace = replace.left
      replace_val = replace.value
      node.right = self.__remove_element_rec(node.right, replace_val)
      node.value = replace_val
      node.height = self.__set_height(node)
      return self.__balanced(node)
    # If all else fails, then the value cannot be found
    else:
      raise ValueError

  def remove_element(self, value):
    """Find and Remove Element"""
    # O(log n): see __remove_rec() for details
    # This function holds the recursion control variables
    if self.__root == None:
      raise ValueError
    if value == self.__root.value:
      self.__root = self.__remove_element_rec(self.__root, value)
    else:
      self.__remove_element_rec(self.__root, value)

    # Handle an empty tree
    # Remove the value specified from the tree, raising a ValueError if the value isn't found.
    # When a replacement value is necessary, select the minimum value to the from the right as this element's replacement.
    # Take note of when to move a node reference and when to replace the value in a node instead. It is not necessary to
    # return the value (though it would reasonable to do so in some implementations). Your solution must be recursive. 
    # This will involve the introduction of additional private methods to support the recursion control variable.
    pass # TODO replace pass with your implementation

  def __in_order_rec(self, node, string):
    """Recursively add to in-order traversal string"""
    # O(n): this method traverses the entire tree
    # First go to the left child (if there is one)
    if node.left != None:
      string = self.__in_order_rec(node.left, string)
    # Then add the parent to the string
    string = string + str(node.value) + ", "
    # Finally go to the right child (if there is one)
    if node.right != None:
      string = self.__in_order_rec(node.right, string)
    return string
  
  def in_order(self):
    """Return a string of the in-order traversal of the tree"""
    # O(n): see __in_order_rec() for details
    # This function holds the recursion control variables
    if self.__root == None:
      return "[ ]"
    else:
      string = "[ "
      string = self.__in_order_rec(self.__root, string)
      string = string[:-2] + " ]"
      return string

  def __pre_order_rec(self, node, string):
    """Recursively add to pre-order traversal string"""
    # O(n): this method traverses the entire tree
    # First add the parent to the string
    string = string + str(node.value) + ", "
    # Then go to the left child (if there is one)
    if node.left != None:
      string = self.__pre_order_rec(node.left, string)
    # Finally go to the right child (if there is one)
    if node.right != None:
      string = self.__pre_order_rec(node.right, string)
    return string

  def pre_order(self):
    """Return a string of the pre-order traversal of the tree"""
    # O(n): see __pre_order_rec() for details
    # This function holds the recursion control variables
    if self.__root == None:
      return "[ ]"
    else:
      string = "[ "
      string = self.__pre_order_rec(self.__root, string)
      string = string[:-2] + " ]"
      return string

  def __post_order_rec(self, node, string):
    """Recursively add to post-order traversal string"""
    # O(n): this method traverses the entire tree
    # First go to the left child (if there is one)
    if node.left != None:
      string = self.__post_order_rec(node.left, string)
    # Then go to the right child (if there is one)
    if node.right != None:
      string = self.__post_order_rec(node.right, string)
    # Finally add the parent to the string
    string = string + str(node.value) + ", "
    return string

  def post_order(self):
    """Return a string of the post-order traversal of the tree"""
    # O(n): see __post_order_rec() for details
    # This function holds the recursion control variables
    if self.__root == None:
      return "[ ]"
    else:
      string = "[ "
      string = self.__post_order_rec(self.__root, string)
      string = string[:-2] + " ]"
      return string

  def __to_list_rec(self, node, arr):
    """Recursively add to in-order traversal python array"""
    # O(n): this method traverses the entire tree
    # First go to the left child (if there is one)
    if node.left != None:
      arr = self.__to_list_rec(node.left, arr)
    # Then add the parent to the array
    arr.append(node.value)
    # Finally go to the right child (if there is one)
    if node.right != None:
      arr = self.__to_list_rec(node.right, arr)
    return arr

  def to_list(self):
    """Return an array of the in-order traversal of the tree"""
    # O(n): see __to_list_rec() for details
    # This function holds the recursion control variables
    arr = []
    return self.__to_list_rec(self.__root, arr)

  def get_height(self):
    """Returns Height of the Entire Tree"""
    # O(1): number of operations are independent of the number of nodes
    if self.__root:
      return self.__root.height
    else:
      return 0

  def __str__(self):
    """Returns In-Order Traversal of Tree"""
    # O(n): see in_order() for details
    return self.in_order()
