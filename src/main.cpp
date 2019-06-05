#include <iostream>
#include <string>

#include "rbtree.hpp"

int main(int argc, char *argv[])
{
  RBTree rbtree;
  rbtree.insert(11);
  rbtree.insert(15);
  rbtree.insert(13);
  rbtree.insert(14);
  
  rbtree.print();

  return 0;
}
