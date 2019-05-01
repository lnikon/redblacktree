#pragma once

struct RBTree final
{
  enum class Color 
  {
    RED = 0,
    BLACK = 1
  };

  struct Node 
  {
    Node *mp_left{nullptr};
    Node *mp_right{nullptr};
    Node *mp_parent{nullptr};
    Color m_color{Color::BLACK};
  };

  void leftRotate(Node *pNode, Node* pLeft);
  void rightRotate(Node *pNode, Node* pRight);
  void insert(int value);

  private:
  Node* mp_root {nullptr};

  void leftRotateHelper(Node *pNode, Node* pLeft);
  void rightRotateHelper(Node *pNode, Node* pRight);
  void insertHelper(Node *pNode, int value);
};

void RBTree::leftRotate(Node *pNode, Node* pLeft)
{ 
  leftRotateHelper(pNode, pLeft);
}

void RBTree::rightRotate(Node *pNode, Node* pRight)
{ 
  rightRotateHelper(pNode, pRight);
}

void RBTree::insert(int value) 
{ 
  insertHelper(mp_root, value);
}

void RBTree::leftRotateHelper(Node *pRoot, Node* pNode)
{ 
  Node* rightNode = pNode->mp_right;
  pNode->mp_right = rightNode->mp_left;

  if(rightNode->mp_left != nullptr) {
    rightNode->mp_left->mp_parent = pNode;
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

  if(pNode->mp_left == nullptr) {
    pNode->mp_left->mp_parent = pNode;
  }

  pLeft->mp_parent = pNode->mp_parent;

  if(pNode->mp_parent == nullptr) {
    pRoot = pLeft;
  } else if(pNode == pNode->mp_parent->mp_left) {
    pNode->mp_parent->mp_left = pNode;
  } else {
    pNode->mp_parent->mp_right = pLeft;
  }

  pLeft->mp_right = pLeft;
  pNode->mp_parent = pLeft;
}

void RBTree::insertHelper(Node *pNode, int value)
{ }
