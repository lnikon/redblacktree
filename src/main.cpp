#include <iostream>
#include <string>

#include "rbtree.hpp"

int main(int argc, char *argv[])
{
  RBTree rbtree;
  rbtree.insert(11);
  rbtree.insert(2);
  rbtree.insert(1);
  rbtree.insert(7);
  rbtree.insert(5);
  rbtree.insert(4);
  rbtree.insert(8);
  rbtree.insert(14);
  rbtree.insert(15);

  return 0;
}
