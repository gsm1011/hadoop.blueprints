#include<iostream>
#include<cstdlib>
#include<queue> 

template<typename T>
class BinarySearchTree {

public: 
  // The tree node class. 
  class BSTreeNode {
  public: 
    BSTreeNode* left; 
    BSTreeNode* right; 

    // constructors. 
    BSTreeNode() { left = NULL; right = NULL; } 
    BSTreeNode(T& val) { 
      left = NULL; 
      right = NULL; 
      value = val; 
    }

    // getters. 
    //T& getValue() { return value; }
    T getValue() { return value; } 
    void setValue(T& val) { value = val; } 
    void setValue(T val) { value = val; }

  private: 
    T value; 
  };

  // constructors. 
  BinarySearchTree() {
    root = NULL;
    cnt = 0; 
  }

  // getters. 
  BSTreeNode*& getRoot() { return root; }
  int getSize() { return cnt; }

  // insert
  void insert(BSTreeNode*& node, T val) {
    // when root is NULL; 
    if(!node) {
      node = new BSTreeNode(val); 
      cnt++; 
    } else {
      if(val < node->getValue()) {
	insert(node->left, val); 
      } else {
	insert(node->right, val); 
      }
    }
  }

  // delete 
  //bool delete(T& val) {
  //  return false; 
  //}
  
  // find 
  BSTreeNode* find(BSTreeNode* rt, T& val) {
    if(NULL == rt) {
      return NULL; 
    }

    if(val == rt->getValue()) return rt;
    
    if(val < rt->getValue()) {
      return find(rt->left, val); 
    } else {
      return find(rt->right, val);
    }
  }

  // breadth first tranverse. 
  void BFSTraverse() {
    BSTreeNode* node = NULL; 
    std::queue<BSTreeNode*> bstQueue; 
    bstQueue.push(root); 
    
    while(!bstQueue.empty()) {
      node = bstQueue.top(); 
      std::cout << node->getValue() << std::endl; 
      if(NULL != node->left) bstQueue.push(node->left); 
      if(NULL != node->right) bstQueue.push(node->right); 
      bstQueue.pop(); 
    }
  }

  // depth first tranverse. 
  void DFSTraverse() {
    
  }

  // preorder tranverse()
  void preOrder(BSTreeNode*& node) {
    // root. 
    if(NULL == node) return; 
    else std::cout << node->getValue() << " "; // << std::endl;

    preOrder(node->left); 
    preOrder(node->right); 
  }

  // in order. 
  void inOrder(BSTreeNode*& node) {
    if(NULL == node) return; 
    else inOrder(node->left); 
    
    std::cout << node->getValue() << " "; // << std::endl; 
    inOrder(node->right); 
  }

  // post order. 
  void postOrder(BSTreeNode*& node) {
    if(NULL == node) return;
    else postOrder(node->left);

    postOrder(node->right); 
    std::cout << node->getValue() << " "; // << std::endl;
  }

private: 
  BSTreeNode* root; 
  int cnt; 
};

// test
int main() {
  BinarySearchTree<int>* bsTree = new BinarySearchTree<int>();
  for(int i = 0; i < 100; ++i) {
    bsTree->insert(bsTree->getRoot(), i); // rand() % 1000);
  }

  // traverses. 
  bsTree->inOrder(bsTree->getRoot()); 
  std::cout << std::endl; 
  bsTree->preOrder(bsTree->getRoot()); 
  std::cout << std::endl; 
  bsTree->postOrder(bsTree->getRoot()); 
  std::cout << std::endl; 
}
