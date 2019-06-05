#pragma once
#include <iostream>
#include <ostream>

struct RBTree final
{
  ~RBTree();

  enum class Color 
  {
    RED     = 0,
    BLACK   = 1
  };

  struct Node 
  {
    Node    *mp_left{nullptr};
    Node    *mp_right{nullptr};
    Node    *mp_parent{nullptr};
    int     m_value{};
    Color   m_color{Color::BLACK};
  };

  void    leftRotate(Node* pLeft);
  void    rightRotate(Node* pRight);
  Node*   insert(int value);
  Node*   remove(Node* pNode);

  void print(std::ostream &out = std::cout);

  private:
  Node* mp_root {nullptr};

  void leftRotateHelper(Node *pNode, Node* pLeft);
  void rightRotateHelper(Node *pNode, Node* pRight);
  void insertHelper(Node* pRoot, Node *pNode);
  void insertFixup(Node* pNode);
  Node* removeHelper(Node* pRoot, Node* pNode);
  Node* successor(Node *pNode);
  void  removeFixup(Node* pRoot, Node* pNode);

  void printHelper(Node* pNode, std::ostream &out = std::cout);
};

RBTree::~RBTree()
{
}

void RBTree::leftRotate(Node* pLeft)
{ 
  leftRotateHelper(mp_root, pLeft);
}

void RBTree::rightRotate(Node* pRight)
{ 
  rightRotateHelper(mp_root, pRight);
}

RBTree::Node* RBTree::insert(int value) 
{ 
  Node *pNode = new Node;
  pNode->m_value = value;

  insertHelper(mp_root, pNode);

  return pNode;
}

RBTree::Node* RBTree::remove(Node* pNode)
{
  return removeHelper(mp_root, pNode);
}

void RBTree::print(std::ostream &out)
{
  if(mp_root == nullptr)
  {
    return;
  }

  printHelper(mp_root, out);
}

RBTree::Node* RBTree::removeHelper(Node* pRoot, Node* pNode)
{
  Node* yNode = nullptr;
  if(pNode->mp_left == nullptr 
      || pNode->mp_right == nullptr)
  {
    yNode = pNode;
  }
  else
  {
    yNode = successor(pNode); 
  }

  Node* xNode = nullptr;
  if(yNode->mp_left != nullptr)
  {
    xNode = yNode->mp_left;
  } 
  else
  {
    xNode = yNode->mp_right;
  }

  xNode->mp_parent = yNode->mp_parent;

  if(yNode->mp_parent == nullptr)
  {
    mp_root = xNode;
  }
  else if(yNode == yNode->mp_parent->mp_left)
  {
    yNode->mp_parent->mp_left = xNode;
  }
  else
  {
    yNode->mp_parent->mp_right = xNode;
  }

  if(yNode != pNode)
  {
    pNode->m_value = yNode->m_value;
  }

  if(yNode->m_color == Color::BLACK)
  {
    removeFixup(pRoot, pNode);
  }

  return yNode;
}

RBTree::Node* RBTree::successor(Node *pNode)
{
  Node* pTemp = pNode;

  while(pTemp->mp_left != nullptr) {
    pTemp = pTemp->mp_left;
  }

  return pTemp;
}

void RBTree::removeFixup(Node* pRoot, Node* pNode)
{
  while(pNode != pRoot && pNode->m_color == Color::BLACK)
  {
    Node* wNode = nullptr;
    if(pNode == pNode->mp_parent->mp_right)
    {
      wNode = pNode->mp_parent->mp_right;
      if(wNode->m_color == Color::RED)
      {
        wNode->m_color = Color::BLACK;
        wNode->mp_parent->m_color = Color::RED;
        leftRotate(pNode->mp_parent);
        wNode = pNode->mp_parent->mp_right;
      }

      if(wNode->mp_left->m_color == Color::BLACK 
          && wNode->mp_right->m_color == Color::BLACK)
      {
        wNode->m_color = Color::RED;
        pNode = pNode->mp_parent;
      }
      else if(wNode->mp_right->m_color == Color::BLACK)
      {
        wNode->mp_left->m_color = Color::BLACK;
        wNode->m_color = Color::RED;
        rightRotate(wNode);
        wNode = pNode->mp_parent->mp_right;
      }

      wNode->m_color = pNode->mp_parent->m_color;
      pNode->mp_parent->m_color = Color::BLACK;
      wNode->mp_right->m_color = Color::BLACK;
      leftRotate(pNode->mp_parent);
      pNode = pRoot;
    } 
    else
    {
      wNode = pNode->mp_parent->mp_left;
      if(wNode->m_color == Color::RED)
      {
        wNode->m_color = Color::BLACK;
        wNode->mp_parent->m_color = Color::RED;
        rightRotate(pNode->mp_parent);
        wNode = pNode->mp_parent->mp_left;
      }

      if(wNode->mp_right->m_color == Color::BLACK 
          && wNode->mp_left->m_color == Color::BLACK)
      {
        wNode->m_color = Color::RED;
        pNode = pNode->mp_parent;
      }
      else if(wNode->mp_left->m_color == Color::BLACK)
      {
        wNode->mp_right->m_color = Color::BLACK;
        wNode->m_color = Color::RED;
        leftRotate(wNode);
        wNode = pNode->mp_parent->mp_left;
      }

      wNode->m_color = pNode->mp_parent->m_color;
      pNode->mp_parent->m_color = Color::BLACK;
      wNode->mp_left->m_color = Color::BLACK;
      rightRotate(pNode->mp_parent);
      pNode = pRoot;
    }
  }

  pNode->m_color = Color::BLACK;
}

void RBTree::printHelper(Node* pNode, std::ostream &out)
{
  if(pNode == nullptr)
  {
    return;
  }

  out << pNode->m_value << ' ';
  printHelper(pNode->mp_left);
  printHelper(pNode->mp_right);
}

void RBTree::leftRotateHelper(Node *pRoot, Node* pNode)
{ 
  Node* rightNode = pNode->mp_right;
  pNode->mp_right = rightNode->mp_left;

  if(rightNode->mp_right != nullptr) {
    rightNode->mp_right->mp_parent = pNode;
  }

  rightNode->mp_parent = pNode->mp_parent;
  if(pNode->mp_parent == nullptr) {
    pRoot = rightNode;
  } else if(pNode == pNode->mp_parent->mp_left) {
    pNode->mp_parent->mp_left = rightNode;
  } else {
    pNode->mp_parent->mp_right = rightNode;
  }

  rightNode->mp_left = pNode;

  pNode->mp_parent = rightNode;
}

void RBTree::rightRotateHelper(Node *pRoot, Node* pNode)
{ 
  Node *pLeft = pNode->mp_left; 
  pNode->mp_left = pLeft->mp_right;

  if(pNode->mp_left != nullptr) {
    pNode->mp_left->mp_parent = pNode;
  }

  pLeft->mp_parent = pNode->mp_parent;

  if(pNode->mp_parent == nullptr) {
    pRoot = pLeft;
  } else if(pNode == pNode->mp_parent->mp_left) {
    pNode->mp_parent->mp_left = pLeft;
  } else {
    pNode->mp_parent->mp_right = pLeft;
  }

  pLeft->mp_right = pNode;
  pNode->mp_parent = pLeft;
}

void RBTree::insertHelper(Node* pRoot, Node *pNode)
{ 
  Node* y = nullptr;
  Node* x = pRoot;

  // Find place to insert
  while(x != nullptr) {
    y = x;
    if(pNode->m_value < x->m_value) {
      x = x->mp_left;
    } else {
      x = x->mp_right;
    }
  }

  // Do Insertion
  pNode->mp_parent = y;

  pNode->mp_left = nullptr;
  pNode->mp_right = nullptr;
  pNode->m_color = Color::RED;

  if(y == nullptr) {
    mp_root = pNode;
    return;
  } else if(pNode->m_value < y->m_value) {
    y->mp_left = pNode;
  } else {
    y->mp_right = pNode;
  }

  insertFixup(pNode);
}

void RBTree::insertFixup(Node* pNode)
{
  if(pNode == mp_root)
  {
    pNode->m_color = Color::BLACK;
    return;
  }

  Node* parent = nullptr;
  Node* grandParent = nullptr;

  while(pNode->m_color == Color::RED && pNode->mp_parent->m_color == Color::RED) {
    parent = pNode->mp_parent;
    grandParent = parent->mp_parent;

    if(parent->m_color != Color::BLACK) {
    if(grandParent != nullptr && parent == grandParent->mp_left) 
    {
      std::cout << "in left branch\n";
      Node* otherNode = grandParent->mp_right;

      if(otherNode != nullptr && otherNode->m_color == Color::RED) 
      {
        pNode->mp_parent->m_color = Color::BLACK;
        otherNode->m_color = Color::BLACK;
        pNode->mp_parent->mp_parent->m_color = Color::RED;
        pNode = pNode->mp_parent->mp_parent;
      } 
      else 
      { 
        if(pNode == pNode->mp_parent->mp_right) 
        {
          pNode = pNode->mp_parent;
          leftRotate(pNode);
        }

        pNode->mp_parent->m_color = Color::BLACK;
        pNode->mp_parent->mp_parent->m_color = Color::RED;
        rightRotate(pNode->mp_parent->mp_parent);
      }
    } 
    else if(grandParent != nullptr)
    {
      std::cout << "in right branch\n";
      Node* otherNode = grandParent->mp_left;
      if(otherNode != nullptr && otherNode->m_color == Color::RED) {
        pNode->mp_parent->m_color = Color::BLACK;
        otherNode->m_color = Color::BLACK;
        pNode->mp_parent->mp_parent->m_color = Color::RED;
        pNode = pNode->mp_parent->mp_parent;
      } else { 
        if(pNode == pNode->mp_parent->mp_left) {
          pNode = pNode->mp_parent;
          rightRotate(pNode);
        }

        pNode->mp_parent->m_color = Color::BLACK;
        pNode->mp_parent->mp_parent->m_color = Color::RED;
        leftRotate(pNode->mp_parent->mp_parent);
      }
    }
    }
  }
  mp_root->m_color = Color::BLACK;
}
