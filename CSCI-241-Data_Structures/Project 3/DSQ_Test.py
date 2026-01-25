import unittest
from Deque_Generator import get_deque
from Stack import Stack
from Queue import Queue

class DSQTester(unittest.TestCase):
  
  def setUp(self):
    self.__deque = get_deque()
    self.__stack = Stack()
    self.__queue = Queue()
  #----------------------------------
  """STACK TESTING"""
  #----------------------------------
  def test_stack_empty_string(self):
    # An empty stack should return this string
    self.assertEqual("[ ]", str(self.__stack))
  
  def test_stack_empty_length(self):
    # An empty stack should return a length of zero
    self.assertEqual(0, len(self.__stack))

  def test_stack_empty_pop(self):
    # Popping an empty stack should return None
    self.assertEqual(None, self.__stack.pop())

  def test_stack_empty_peek(self): 
    # Peeking an empty stack should return None
    self.assertEqual(None, self.__stack.peek())

  def test_stack_length_one(self):
    # A stack with one node should have length=1
    self.__stack.push("Hey")
    self.assertEqual(1, len(self.__stack))

  def test_stack_length_large(self):
    # A stack with five nodes should have length=5
    self.__stack.push("Hey")
    self.__stack.push("Hiya")
    self.__stack.push("Howdy")
    self.__stack.push("Hi")
    self.__stack.push("Heyo")
    self.assertEqual(5, len(self.__stack))

  def test_stack_push(self):
    # After pushing a node onto a stack, the stack's string should only hold that node in a list
    self.__stack.push("Hey")
    self.assertEqual("[ Hey ]", str(self.__stack))

  def test_stack_multiple_push(self):
    # After pushing multiple nodes onto a stack, the stack's string should hold all of the nodes in a list
    # (Note that push() pushes to the front of the list)
    self.__stack.push("Hey")
    self.__stack.push("Hiya")
    self.__stack.push("Howdy")
    self.assertEqual("[ Howdy, Hiya, Hey ]", str(self.__stack))

  def test_stack_pop(self):
    # A stack that is popped after having two nodes should only show the first node in its string
    self.__stack.push("Hey")
    self.__stack.push("Hiya")
    self.__stack.pop()
    self.assertEqual("[ Hey ]", str(self.__stack))

  def test_stack_multiple_pop(self):
    # A stack that is popped twice after having three nodes should only show the first node in its string
    self.__stack.push("Hey")
    self.__stack.push("Hiya")
    self.__stack.push("Howdy")
    self.__stack.pop()
    self.__stack.pop()
    self.assertEqual("[ Hey ]", str(self.__stack))

  def test_stack_peek(self):
    # A stack with one item should return that item upon peeking
    self.__stack.push("Hey")
    self.assertEqual("Hey", self.__stack.peek())

  def test_stack_multiple_peek(self):
    # A stack with multiple items should only return the last inputted item upon peeking
    self.__stack.push("Hey")
    self.__stack.push("Hiya")
    self.__stack.push("Howdy")
    self.assertEqual("Howdy", self.__stack.peek())

  def test_stack_combined_testing(self):
    # This test is a complex combination of stack methods that should all work
    self.__stack.push("Hey")
    self.__stack.push("Hiya")
    self.__stack.push("Howdy")
    self.assertEqual("Howdy", self.__stack.peek())
    self.__stack.pop()
    self.assertEqual(2, len(self.__stack))
    self.assertEqual("Hiya", self.__stack.peek())
    self.__stack.pop()
    self.assertEqual("Hey", self.__stack.peek())
    self.assertEqual("[ Hey ]", str(self.__stack))
    self.__stack.pop()
    self.assertEqual("[ ]", str(self.__stack))
  #----------------------------------
  """Queue Testing"""
  #----------------------------------
  def test_queue_empty_string(self):
    # An empty queue should return this string
    self.assertEqual("[ ]", str(self.__queue))

  def test_queue_empty_length(self):
    # An empty queue should return a length of zero
    self.assertEqual(0, len(self.__queue))

  def test_queue_empty_dequeue(self):
    # Popping an empty queue should return None
    self.assertEqual(None, self.__queue.dequeue())

  def test_queue_empty_peek(self):
    # Peeking an empty queue should return None
    self.assertEqual(None, self.__queue.peek())

  def test_queue_length_one(self):
    # A queue with one node should have length=1
    self.__queue.enqueue("Hey")
    self.assertEqual(1, len(self.__queue))

  def test_queue_length_large(self):
    # A queue with five nodes should have length=5
    self.__queue.enqueue("Hey")
    self.__queue.enqueue("Hiya")
    self.__queue.enqueue("Howdy")
    self.__queue.enqueue("Hi")
    self.__queue.enqueue("Heyo")
    self.assertEqual(5, len(self.__queue))

  def test_queue_enqueue(self):
    # After enqueueing a node onto a queue, the queue's string should only hold that node in a list
    self.__queue.enqueue("Hey")
    self.assertEqual("[ Hey ]", str(self.__queue))

  def test_queue_multiple_enqueue(self):
    # After enqueueing multiple nodes onto a queue, the queue's string should hold all of the nodes in a list
    # (Note that enqueue() pushes to the back of the list)
    self.__queue.enqueue("Hey")
    self.__queue.enqueue("Hiya")
    self.__queue.enqueue("Howdy")
    self.assertEqual("[ Hey, Hiya, Howdy ]", str(self.__queue))

  def test_queue_dequeue(self):
    # A queue that is dequeued after having two nodes should only show the first node in its string
    self.__queue.enqueue("Hey")
    self.__queue.enqueue("Hiya")
    self.__queue.dequeue()
    self.assertEqual("[ Hiya ]", str(self.__queue))

  def test_queue_multiple_dequeue(self):
    # A queue that is dequeued twice after having three nodes should only show the first node in its string
    self.__queue.enqueue("Hey")
    self.__queue.enqueue("Hiya")
    self.__queue.enqueue("Howdy")
    self.__queue.dequeue()
    self.__queue.dequeue()
    self.assertEqual("[ Howdy ]", str(self.__queue))

  def test_queue_peek(self):
    # A queue with one item should return that item upon peeking
    self.__queue.enqueue("Hey")
    self.assertEqual("Hey", self.__queue.peek())

  def test_queue_multiple_peek(self):
    # A queue with multiple items should only return the first inputted item upon peeking
    self.__queue.enqueue("Hey")
    self.__queue.enqueue("Hiya")
    self.__queue.enqueue("Howdy")
    self.assertEqual("Hey", self.__queue.peek())

  def test_queue_combined_testing(self):
    # This test is a complex combination of queue methods that should all work
    self.__queue.enqueue("Hey")
    self.__queue.enqueue("Hiya")
    self.__queue.enqueue("Howdy")
    self.assertEqual("Hey", self.__queue.peek())
    self.__queue.dequeue()
    self.assertEqual(2, len(self.__queue))
    self.assertEqual("Hiya", self.__queue.peek())
    self.__queue.dequeue()
    self.assertEqual("Howdy", self.__queue.peek())
    self.assertEqual("[ Howdy ]", str(self.__queue))
    self.__queue.dequeue()
    self.assertEqual("[ ]", str(self.__queue))
  #----------------------------------
  """Deque Testing"""
  #----------------------------------
  def test_deque_empty_string(self):
    # An empty deque should return this string
    self.assertEqual("[ ]", str(self.__deque))

  def test_deque_(self):
    # An empty deque should return a length of zero
    self.assertEqual(0, len(self.__deque))

  def test_deque_empty_pop_front(self):
    # Popping the front of an empty deque should return None
    self.assertEqual(None, self.__deque.pop_front())

  def test_deque_empty_pop_back(self):
    # Popping the back of an empty deque should return None
    self.assertEqual(None, self.__deque.pop_back())

  def test_deque_empty_peek_front(self):
    # Peeking the front of an empty deque should return None
    self.assertEqual(None, self.__deque.peek_front())

  def test_deque_empty_peek_back(self):
    # Peeking the back of an empty deque should return None
    self.assertEqual(None, self.__deque.peek_back())

  def test_deque_length_one(self):
    # A deque with one node should have length=1
    self.__deque.push_front("Hey")
    self.assertEqual(1, len(self.__deque))
  
  def test_deque_length_large(self):
    # A deque with five nodes should have length=5
    self.__deque.push_front("Hey")
    self.__deque.push_front("Hiya")
    self.__deque.push_front("Howdy")
    self.__deque.push_front("Hi")
    self.__deque.push_front("Heyo")
    self.assertEqual(5, len(self.__deque))

  def test_deque_push_front(self):
    # After pushing a node to the front of a deque, the deque's string should only hold that node in a list
    self.__deque.push_front("Hey")
    self.assertEqual("[ Hey ]", str(self.__deque))

  def test_deque_push_front_multiple(self):
    # After pushing multiple nodes to the front of a deque, the deque's string should hold all of the nodes in a list
    self.__deque.push_front("Hey")
    self.__deque.push_front("Hiya")
    self.__deque.push_front("Howdy")
    self.assertEqual("[ Howdy, Hiya, Hey ]", str(self.__deque))

  def test_deque_push_back(self):
    # After pushing a node to the back of a deque, the deque's string should only hold that node in a list
    self.__deque.push_back("Hey")
    self.assertEqual("[ Hey ]", str(self.__deque))

  def test_deque_push_back_multiple(self):
    # After pushing multiple nodes to the back of a deque, the deque's string should hold all of the nodes in a list
    self.__deque.push_back("Hey")
    self.__deque.push_back("Hiya")
    self.__deque.push_back("Howdy")
    self.assertEqual("[ Hey, Hiya, Howdy ]", str(self.__deque))

  def test_deque_pop_front(self):
    # A deque that is popped from the front after having two nodes should only show the first node in its string
    self.__deque.push_front("Hey")
    self.__deque.push_front("Hiya")
    self.__deque.pop_front()
    self.assertEqual("[ Hey ]", str(self.__deque))

  def test_deque_pop_front_multiple(self):
    # A deque that is popped from the front twice after having three nodes should only show the first node in its string
    self.__deque.push_front("Hey")
    self.__deque.push_front("Hiya")
    self.__deque.push_front("Howdy")
    self.__deque.pop_front()
    self.__deque.pop_front()
    self.assertEqual("[ Hey ]", str(self.__deque))

  def test_deque_pop_back(self):
    # A deque that is popped from the back after having two nodes should only show the first node in its string
    self.__deque.push_back("Hey")
    self.__deque.push_back("Hiya")
    self.__deque.pop_back()
    self.assertEqual("[ Hey ]", str(self.__deque))

  def test_deque_pop_back_multiple(self):
    # A deque that is popped from the back twice after having three nodes should only show the first node in its string
    self.__deque.push_back("Hey")
    self.__deque.push_back("Hiya")
    self.__deque.push_back("Howdy")
    self.__deque.pop_back()
    self.__deque.pop_back()
    self.assertEqual("[ Hey ]", str(self.__deque))

  def test_deque_peek_front(self):
    # A deque with one item should return that item upon peeking the front
    self.__deque.push_front("Hey")
    self.assertEqual("Hey", self.__deque.peek_front())

  def test_deque_peek_front_multiple(self):
    # A deque with multiple items should only return the first inputted item upon peeking the front
    self.__deque.push_front("Hey")
    self.__deque.push_front("Hiya")
    self.__deque.push_front("Howdy")
    self.assertEqual("Howdy", self.__deque.peek_front())

  def test_deque_peek_back(self):
    # A deque with one item should return that item upon peeking the back
    self.__deque.push_back("Hey")
    self.assertEqual("Hey", self.__deque.peek_back())

  def test_deque_peek_back_multiple(self):
    # A deque with multiple items should only return the first inputted item upon peeking the back
    self.__deque.push_back("Hey")
    self.__deque.push_back("Hiya")
    self.__deque.push_back("Howdy")
    self.assertEqual("Howdy", self.__deque.peek_back())

  def test_deque_combined_testing(self):
    # This test is a complex combination of deque methods that should all work
    self.__deque.push_front("Hey")
    self.__deque.push_front("Hiya")
    self.__deque.push_front("Howdy")
    self.assertEqual("Hey", self.__deque.peek_back())
    self.__deque.pop_back()
    self.assertEqual(2, len(self.__deque))
    self.assertEqual("Howdy", self.__deque.peek_front())
    self.__deque.pop_back()
    self.assertEqual("Howdy", self.__deque.peek_back())
    self.assertEqual("[ Howdy ]", str(self.__deque))
    self.__deque.pop_front()
    self.assertEqual("[ ]", str(self.__deque))


if __name__ == '__main__':
  unittest.main()
