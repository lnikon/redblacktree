#pragma once
#include <stack>

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

    void leftRotate(Node* pLeft);
    void rightRotate(Node* pRight);
    void insert(int value);
    void transplant(Node* u, Node* v);

    private:
    Node* mp_root {nullptr};

    void leftRotateHelper(Node *pNode, Node* pLeft);
    void rightRotateHelper(Node *pNode, Node* pRight);
    void insertHelper(Node* pRoot, Node *pNode);

    void insertFixup(Node* pNode);
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

void RBTree::insert(int value) 
{ 
    Node *pNode = new Node;
    pNode->m_value = value;

    insertHelper(mp_root, pNode);
}

void RBTree::transplant(Node* u, Node* v)
{
    if(u->mp_parent == nullptr) {
        mp_root = v;
    } else if(u == u->mp_parent->mp_left) {
        u->mp_parent->mp_left = v;
    } else {
        u->mp_parent->mp_right = v;
    }

    v->mp_parent = u->mp_parent;
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

    // Do insertion
    pNode->mp_parent = y;
    if(y == nullptr) {
        mp_root = pNode;
  } else if(pNode->m_value < y->m_value) {
    y->mp_left = pNode;
  } else {
    y->mp_right = pNode;
  }

  pNode->mp_left = nullptr;
  pNode->mp_right = nullptr;
  pNode->m_color = Color::RED;

  insertFixup(pNode);
}

void RBTree::insertFixup(Node* pNode)
{
  Node* parent = nullptr;
  Node* grandParent = nullptr;

  while(pNode != mp_root && pNode->m_color == Color::RED && pNode->mp_parent->m_color == Color::RED) {
    parent = pNode->mp_parent;
    grandParent = parent->mp_parent;

    if(grandParent != nullptr && parent == grandParent->mp_left) {
      Node* otherNode = grandParent->mp_right;

      if(otherNode != nullptr && otherNode->m_color == Color::RED) {
        pNode->mp_parent->m_color = Color::BLACK;
        otherNode->m_color = Color::BLACK;
        pNode->mp_parent->mp_parent->m_color = Color::RED;
        pNode = pNode->mp_parent->mp_parent;
      } else { 
        if(pNode == pNode->mp_parent->mp_right) {
          pNode = pNode->mp_parent;
          leftRotate(pNode);
        }

        pNode->mp_parent->m_color = Color::BLACK;
        pNode->mp_parent->mp_parent->m_color = Color::RED;
        rightRotate(pNode->mp_parent->mp_parent);
      }
    } else {
      Node* otherNode = pNode->mp_parent->mp_parent->mp_left;
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
  mp_root->m_color = Color::BLACK;
}
