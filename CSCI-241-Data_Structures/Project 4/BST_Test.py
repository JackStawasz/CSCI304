import unittest
from Binary_Search_Tree import Binary_Search_Tree

class DSQTester(unittest.TestCase):
  
  def setUp(self):
    self.__tree = Binary_Search_Tree()

  def test_empty_string(self):
    self.assertEqual("[ ]", str(self.__tree))
  
  def test_insert_root(self):
    self.__tree.insert_element(5)
    self.assertEqual("[ 5 ]", str(self.__tree))

  def test_insert_multiple(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    self.assertEqual("[ 1, 2, 3, 4, 5, 6, 7 ]", str(self.__tree))
    
  def test_duplicate_entry(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    try:
      self.__tree.insert_element(7)
    except:
      ValueError
    self.assertEqual("[ 1, 6, 7 ]", str(self.__tree))

  def test_remove_only_root(self):
    self.__tree.insert_element(9)
    self.__tree.remove_element(9)
    self.assertEqual("[ ]", str(self.__tree))

  def test_remove_tree_root(self):
    # Inserts
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    # Removal of the root (after balancing)
    self.__tree.remove_element(5)
    self.assertEqual("[ 1, 2, 3, 4, 6, 7 ]", str(self.__tree))

  def test_remove_multiple(self):
    # Inserts
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    # Removals
    self.__tree.remove_element(7)
    self.__tree.remove_element(2)
    self.__tree.remove_element(5)
    self.assertEqual("[ 1, 3, 4, 6 ]", str(self.__tree))

  def test_remove_unfound_element(self):
    # Inserts
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    # Removal
    try:
      self.__tree.remove_element(42)
    except:
      ValueError
    self.assertEqual("[ 1, 2, 3, 4, 5, 6, 7 ]", str(self.__tree))

  def get_height_empty(self):
    self.assertEqual(0, Binary_Search_Tree.get_height(self.__tree))

  def get_height_root_only(self):
    self.__tree.insert_element(7)
    self.assertEqual(1, Binary_Search_Tree.get_height(self.__tree))

  def test_get_height_large(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    self.assertEqual(4, Binary_Search_Tree.get_height(self.__tree))

  def test_in_order(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    self.assertEqual("[ 1, 2, 3, 4, 5, 6, 7 ]", Binary_Search_Tree.in_order(self.__tree))

  def test_pre_order(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    self.assertEqual("[ 5, 2, 1, 3, 4, 6, 7 ]", Binary_Search_Tree.pre_order(self.__tree))

  def test_post_order(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    self.assertEqual("[ 1, 4, 3, 2, 7, 6, 5 ]", Binary_Search_Tree.post_order(self.__tree))

  def test_to_list(self):
    self.__tree.insert_element(7)
    self.__tree.insert_element(1)
    self.__tree.insert_element(6)
    self.__tree.insert_element(2)
    self.__tree.insert_element(5)
    self.__tree.insert_element(3)
    self.__tree.insert_element(4)
    self.assertEqual([ 1, 2, 3, 4, 5, 6, 7 ], Binary_Search_Tree.to_list(self.__tree))

if __name__ == '__main__':
  unittest.main()