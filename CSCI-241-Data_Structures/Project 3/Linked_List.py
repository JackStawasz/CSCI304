
class Linked_List:
    
    class __Node:
        
        def __init__(self, val):
            # Initialize the value, next alias, and previous alias of the Node class
            self.val = val
            self.next = None
            self.prev = None
            # PERFORMANCE: O(1) constant amount of objects to initialize

    def __init__(self):
        # Initialize the Linked List class by defining header, trailer, len, and connecting the header/trailer with aliases
        self.header = Linked_List.__Node(None)
        self.trailer = Linked_List.__Node(None)
        self.header.next = self.trailer
        self.trailer.prev = self.header
        self.len = 0
        # PERFORMANCE: O(1) constant amount of objects to initialize

    def __len__(self):
        # Ensure that the returned length is my custom length, not python's automated one
        return self.len
        # PERFORMANCE: O(1) returns an already known value

    def append_element(self, val):
        # Create a new node, link it to the end of the list, and increase the list length
        new_node = Linked_List.__Node(val)
        cur = self.trailer.prev
        new_node.next = self.trailer
        cur.next = new_node
        new_node.prev = cur
        self.trailer.prev = new_node
        self.len += 1
        # PERFORMANCE: O(1) constant time, the program knows where the trailer is and therefore
        # it takes the same number of steps to run regardless of the input

    def remove_tail(self):
        # NON-SKELETON METHOD: allows removal of tail in constant time
        remove = self.trailer.prev
        remove.prev.next = self.trailer
        self.trailer.prev = remove.prev
        self.len -= 1
        return remove.val

    def get_tail(self):
        # NON-SKELETON METHOD: allows retrieval of tail value in constant time
        return self.trailer.prev.val

    def insert_element_at(self, val, index):
        # This function must not work on an empty list
        if self.len == 0 and index == 0:
            raise IndexError
        # Index cannot be outside the list or the tail position
        elif not 0 <= index < self.len:
            raise IndexError
        # Create a new node, the head (not header) is indexed 0 then find the indexed node
        new_node = Linked_List.__Node(val)
        cur = self.header.next
        for j in range(0, index):
            cur = cur.next
        # Alias the new node at the index and increase the list length
        new_node.next = cur
        new_node.prev = cur.prev
        cur.prev.next = new_node
        cur.prev = new_node
        self.len += 1
        # PERFORMANCE: O(n) linear time, the further the index is from the header the longer it takes to find
        # that index, so the program must iterate over the list one time until reaching the inputed index

    def remove_element_at(self, index):
        # This function must not work on an empty list
        if self.len == 0 and index == 0:
            raise IndexError
        # Index cannot be outside the list
        elif not 0 <= index < self.len:
            raise IndexError
        # The head (not header) is indexed 0 then find the indexed node
        cur = self.header.next
        for j in range(0, index):
            cur = cur.next
        # Realias the nodes before and after to each other and decrease the list length
        cur.prev.next = cur.next
        cur.next.prev = cur.prev
        self.len -= 1
        # Return the deleted node's value before it gets garbage collected by the system
        return cur.val
        # PERFORMANCE: O(n) linear time, the further the index is from the header the longer it takes to find
        # that index, so the program must iterate over the list one time until reaching the inputed index

    def get_element_at(self, index):
        # This function must not work on an empty list
        if self.len == 0 and index == 0:
            raise IndexError
        # Index cannot be outside the list
        elif not 0 <= index < self.len:
            raise IndexError
        # The head (not header) is indexed 0 then find the indexed node
        cur = self.header.next
        for j in range(0, index):
            cur = cur.next
        # Return the node's value to the user
        return cur.val
        # PERFORMANCE: O(n) linear time, the further the index is from the header the longer it takes to find
        # that index, so the program must iterate over the list one time until reaching the inputed index
        
    def rotate_left(self):
        # Copy the head value and put it as a new tail node
        self.append_element(self.header.next.val)
        # Remove the "old" head to "shift" the next node to the front
        self.remove_element_at(0)
        # PERFORMANCE: O(n) linear time, both the append and remove functions run in O(n) and
        # two linear times added together will still result in linear time

    def __str__(self):
        # Case for an empty list
        if self.len == 0:
            string = "[ ]"
            return string
        # Modify a string to return by starting it with an open bracket, adding each value of the list to
        # the string which are separated by commas, then splicing the final comma of and closing the bracket
        string = "[ "
        cur = self.header.next
        for index in range(0, self.len):
            string = string + str(cur.val) + ", "
            cur = cur.next
        string = string[:-2] + " ]"
        return string
        # PERFORMANCE: O(n) linear time, this method needs to iterate over the entire list when it is run and
        # therefore the run time linearly depends on the number of items in the list

    def __iter__(self):
        # When a for loop is called, it will start with my custom iteration starting index
        self.iter_index = self.header
        return self
        # PERFORMANCE: O(1) because two steps are taken rergardless of any external parameters

    def __next__(self):
        # Prevent a for loop from moving past the list's length
        if self.iter_index.next == self.trailer or self.len == 0:
            raise StopIteration
        # Otherwise, move to the next index and return its value
        else:
            self.iter_index = self.iter_index.next
            return self.iter_index.val
        # PERFORMANCE: O(1) because a constant number of steps are taken for each if/else case scenario

    def __reversed__(self):
        # Create a new Linked_List object for the reversed list and initialize loop variables
        reverse_list = Linked_List()
        x = self.len
        cur = self.trailer.prev
        # Take each value of the original list (self) going right to left (using a decreasing x)
        # and alias them to the reverse_list by going left to right (using the append function)
        while x > 0:
            reverse_list.append_element(cur.val)
            cur = cur.prev
            x -= 1
        return reverse_list
        # PERFORMANCE: O(n) linear time, the run time to append values to reverse_list linearly
        # depends on the number of items in the original list

if __name__ == '__main__':
    """Test Cases"""
    # Start with a decently sized list AND test that the append/insert methods work
    the_list = Linked_List() # Create a linked list object
    the_list.append_element(0)
    the_list.append_element(1)
    the_list.append_element(3)
    the_list.append_element(4)
    the_list.insert_element_at(2, 2)
    #  Test the __len__/__str__methods that are implicitly run through len() and print()
    print("Starting list: ", the_list)
    print("List length =", len(the_list))
    # Test the get_element/remove_element methods and print the_list to prove they worked
    print("Item at index three =", the_list.get_element_at(3))
    the_list.remove_element_at(4)
    print(the_list)
    # Compare a newly created reversed list to the original list
    print("\nOriginal list: ", the_list)
    print("Reversed list: ", reversed(the_list))
    # Test the rotate_left() method
    print("\nOriginal list: ", the_list)
    the_list.rotate_left()
    print("Newly rotated list: ", the_list)
    # Verify list length after the changes
    print("List length =", len(the_list))
