// This file is the self practice of coding interview questions. 

//////////////////////////////////////////////////////////////////////////////
// put odd numbers in front of even numbers. 
bool reorderOddEven(int num[], unsigned int len) {
  if (NULL == num || len <= 1) {
    printf("Wrong input. \n");
    return false; 
  }

  int *pFront = num; 
  int *pEnd = num + len - 1; 

  while(pFront < pEnd) {
    while(pFront < pEnd && *pFront & 0x1 == 1) ++pFront; // odd number.
    while(pFront < pEnd && *pEnd & 0x1 == 0) --pEnd;	 // even number. 

    if(pFront > pEnd) {
      // exchange pFront and pEnd values.
      int tmp = *pFront; 
      *pFront++ = *pEnd; 
      *pEnd-- = tmp; 
    }
  }

  return true; 
}

// a generic solution. 
bool reorder(int num[], unsigned int len, bool (*func)(int)) {
  if (NULL == num || len <= 1) {
    printf("Input error. "); 
    return false; 
  }

  int *pFront = num; 
  int *pEnd = num + len - 1; 

  while(pFront < pEnd) {
    while (pFront < pEnd && func(*pFront)) ++pFront; 
    while (pFron < pEnd && !func(*pEnd)) --pEnd; 

    if(pFront < pEnd) {
      int tmp = *pFront; 
      *pFront++ = *pEnd; 
      *pEnd-- = tmp; 
    }    
  }
  return true; 
}

bool isOdd(int val) {
  return (val & 1) == 1; 
}

bool isNegative(int val) {
  return val < 0; 
}

bool isDivisibleBy3(int val) {
  return (val % 3) == 0; 
}

bool reorderOddEven2(int num[], unsigned int len) {
  return reorder(num, len, isOdd); 
}


//////////////////////////////////////////////////////
// print the k-th last element of a linked list. 
struct ListNode{
  int val; 
  ListNode *next; 
};

bool returnKthLast(ListNode *listHead, unsigned int k, int &val) {
  if (NULL == listHead || k == 0) {
    printf("Input error."); 
    return false; 
  }
  
  ListNode *pre = listHead; 
  ListNode *lst = listHead; 

  unsigned int cnt = 0; 
  while(lst->next && cnt < k) {
    lst = lst->next; 
    ++cnt; 
  }

  // if the list of shorter than k, then failed. 
  if(cnt < k) return false; 

  // otherwise, go to the end of the list. 
  while(lst->next) {
    lst = lst->next; 
    pre = pre->next; 
  }

  val = pre->val; 
  return true; 
}


/////////////////////////////////////////////////////////
// reverse a list. 
/////////////////////////////////////////////////////////
struct ListNode {
  int val; 
  ListNode * next; 
};

// use stack. 
ListNode *reverseList(ListNode *listHead) {
  if(NULL == listHead || NULL == listHead->next) return listHead; 

  // use stack to store the nodes and pop back and link them. 
  ListNode *node = listHead;
  stack<ListNode*> nodeStack; 

  while(!node->next) {
    nodeStack.push(node); 
    node = node->next;
  }

  if(nodeStack.empty()) return listHead; 

  listHead = nodeStack.top(); 
  node = listHead; 

  while(!nodeStack.empty()) {
    nodeStack.pop(); 
    nodeNew = nodeStack.top();
    node->next = nodeNew; 
    node = nodeNew; 
  }

  return listHead; 
}

// use two pointers. 
ListNode *reverseListRecursive(ListNode *listHead) {
  if(NULL == listHead || NULL == listHead->next) return listHead; 

  ListNode *pAhead = listHead->next->next; 
  ListNode *pMid = listHead->next; 
  ListNode *pBehind = listHead; 
  
  // let head head to nothing.
  pBehind->next = NULL; 

  // do the reverse till pAhead is NULL; 
  do {
    pMid->next = pBehind; 
    if(NULL == pAhead) return pMid; 
    pBehind = pMid; 
    pMid = pAhead; 
    pAhead = pAhead->next; 
  } while(true);
}


/////////////////////////////////////////////////////////////////
// merge two sorted linked list. 
/////////////////////////////////////////////////////////////////
ListNode *mergeTwoList(ListNode *list1, ListNode *list2) {
  if(NULL == list1) return list2; 
  if(NULL == list2) return list1;

  ListNode *newListHead; 
  ListNode *node1 = list1; 
  ListNode *node2 = list2; 

  // determine the new list head. 
  if(node1->val < node2->val) {
    newListHead = node1;
    node1 = node1->next; 
  } else {
    newListHead = node2; 
    node2 = node2->next; 
  }

  // continue to merge. 
  while(true) {
    if(!node1 || !node2) break; 

    ListNode *tmpNode = NULL; 
    if(node1->val < node2->val) {
      tmpNode = node1->next; 
      node1->next = node2; 
      node1 = tmpNode; 

    } else {
      tmpNode = node2->next; 
      node2->next = node1; 
      node2 = tmpNode; 
    }
  }

  return newListHead; 
}

// recursively do this. 
ListNode *mergeRecursive(ListNode *list1, ListNode *list2) {
  if(NULL == list1) {
    return list2; 
  } else if (NULL == list2) {
    return list1; 
  }

  NodeList *newListHead = NULL; 

  if(list1->val < list2->val) {
    newListHead = list1; 
    newListHead->next = mergeRecursively(list1->next, list2); 
  } else {
    newListHead = list2; 
    newListHead->next = mergerecursively(list1, list2->next); 
  }
  
  return newListHead; 
}


////////////////////////////////////////////////////////////
// subtree of another tree. 
////////////////////////////////////////////////////////////
struct BTreeNode {
  int val; 
  BTreeNode *left; 
  BTreeNode *right; 
};

bool isSubTree(BTreeNode *tree1, BTreeNode *tree2) {
  // find a node in tree1 with the same value as the root of tree2 ; 
  bool isASubTree = false; 

  if(NULL != tree1 && NULL != tree2) {
    if(rootVal == node->val) {
      isASubTree = testMatch(node, tree2); 
    }

    if(!isASubTree) {
      isASubTree = isSubTree(node->left, tree2);  
    }

    if(!isASubTree) {
      isASubTree = isSubTree(node->right, tree2); 
    }
  }

  return isASubTree; 
}

// test the matching of tree rooted with the given pointers. 
bool testMatch(BTreeNode *tr1, BTreeNode *tr2) {
  bool match = false; 
  
  if(NULL == tr2) 
    return true; 

  if(NULL == tr1) 
    return false; 

  if(tr1->val == tr2->val) match = true; 
  else return false; 

  return testMatch(tr1->left, tr2->left) && testMatch(tr1->right, tr2->right); 
}


//////////////////////////////////////////////////////////////
// mirror a tree. 
//////////////////////////////////////////////////////////////
struct BTreeNode {
  int val; 
  BTreeNode *left; 
  BTreeNode *right; 
};

// to mirror a tree, we mirror the left and right child recursively. 
bool mirrorTree(BTreeNode *tree) {
  if(NULL == tree) return true; 

  // exchange the left and right subtree. 
  BTreeNode *tmpNode = tree->left; 
  tree->left = tree->right; 
  tree->right = tmpNode; 

  // mirror recursively the subtrees. 
  mirrorTree(tree->left); 

  mirrorTree(tree->right); 

  return true; 
}


//////////////////////////////////////////////////////////////
// Stack with a min value. 
/////////////////////////////////////////////////////////////
template<typename T>
class StackwithMin {
private:
  stack<T> dataStk;
  stack<T> minStk; 

public:
  void push(const T& val); 
  T& pop(); 
  T& min(); 
};

template<typename T> void StackwithMin<T>::push(const T& val) {
  dataStk.push(val); 
  if(minStk.size() == 0 || minStk.top() < val) {
    minStk.push(minStk.top()); 
  } else {
    minStk.push(val); 
  }
}

template<typename T> T& StackwithMin<T>::pop() {
  assert(dataStk.size() > 0 && minStk.size() > 0); 
  
  dataStk.pop(); 
  minStk.pop(); 
}

template<typename T> const T& StackwithMin<T>::min() const {
  assert(StackwithMin::dataStk.size() > 0 && StackwithMin::minStk.size()); 

  return minStk.top(); 
}

/////////////////////////////////////////////////////////////////
// print a tree in level order. 
/////////////////////////////////////////////////////////////////
struct BTreeNode {
  int val; 
  BTreeNode *left; 
  BTreeNode *right; 
};

void printTreeLevelOrder(BtreeNode *tree) {
  if(NULL == tree) return ; 
  queue<BTreeNode *> nodeQueue; 

  nodeQueue.enqueue(tree); 

  while(nodeQueue.size() > 0) {
    BTreeNode *node = nodeQueue.dequeue(); 

    if(NULL != node) {
      printf("Node:%d\n", node->val); 
      nodeQueue.enqueue(node->left); 
      nodeQueue.enqueue(node->right); 
    }
  }
}


////////////////////////////////////////////////////////////////
// test if a tree is BST. 
////////////////////////////////////////////////////////////////
// the property of a binary search tree is that its left subtree 
// is smaller than its root and right subtree is bigger than root. 
////////////////////////////////////////////////////////////////
// suppose we use the same node as the previous one.
bool checkBST(BTreeNode *head) {
  if(NULL == head) return true; 

  // traverse the tree inorder. 
  vector<int> inorderVals; 
  traverseInorder(head, inorderVals); 

  int len = inorderVals.size(); 
  for(int i = 0; i < len - 1; ++i) {
    if(inorderVals[i] > inorderVals[i+1]) return false; 
  }
  return true; 
}

// in order traversal of a tree. 
void traverseInorder(BTreeNode *head, vector<int> &vals) {
  if(NULL == head) return ;

  traverseInorder(head->left, vals); 

  vals.push_back(head->val); 

  traverseInorder(head->right, vals); 
}

// traverse pre-order of a tree.
void traversePreorder(BTreeNode *head, vector<int> &vals) {
  if(NULL == head) return; 

  vals.push_back(head->val); 

  traversePreorder(head->left); 

  traversePostorder(head->right);
}

// post order traversal. 
void traversePostorder(BTreeNode *head, vector<int> &vals) {
  if(NULL == head) return; 

  traversePreorder(head->left); 
  traversePostorder(head->right);
  vals.push_back(head->val); 
}

///////////////////////////////////////////////////////////////
// Division without using divide operator. 
//////////////////////////////////////////////////////////////
bool division (int nominator, int denominator, int &result) {
  if(0 == denominator) return false; 

  if(nominator < denominator) {
    result = 0; 
    return false; 
  }

  result= 0; 
  while(nominator >= denominator) {
    nominator -= denominator; 
    ++result; 
  }

  return true; 
}

/////////////////////////////////////////////////////////////
// throwing java exception. 
/////////////////////////////////////////////////////////////
public static int getLargest(int []input) {
  if(null == input || input.length == 0) {
    throw new Exception("Input error."); 
  }

  int largest = input[0]; 
  int len = input.length; 

  for(int i = 1; i < len; i++) {
    if(largest < input[i]) largest = input[i]; 
  }

  return largest;
}

///////////////////////////////////////////////////////////////
// HashMap with linked list hashing. 
///////////////////////////////////////////////////////////////
// use vector to store the main table, and each node has a pointer 
// pointing the a possible list. 
struct Node {
  int key; 
  char *value; 
  Node *next; 
}; 

class HashMap {
private: 
  Node *nodes = (Node *) malloc(sizeof(Node) * 100); 

public:

  HashMap() {
    memset(nodes, 0, 100); 
  }
  
  // the hash function. 
  int hashFunc(int val) {
    return val % 100; 
  }

  // insert an element into the hash function. 
  void put(int key, char *value) {
    int hashVal = hashFunc(key); 

    Node *n = new Node(); 
    n.key = key; 
    strcpy(&(n->value), value); 
    n->next = NULL; 

    if(NULL == nodes[hashVal]) {
      nodes[hashVal] = *n; 
    } else {
      Node *nd = nodes[hashVal]; 
      while(!nd->next) nd = nd->next; 

      nd->next = n; 
    }
  }

  // get the value of a given key.
  char* get(int key) {
    int hashVal = hashFunc(key);
    if(NULL == nodes[hashVal]) return NULL; 

    Node *nd = nodes[hashVal];  
    while(!nd->next) {
      if(nd->key == key) return &(nd->val); 
    }
    return NULL; 
  }

  // test if a key is in the hash map.
  bool contains(int key) {
    int hashVal = hashFunc(key);
    if(NULL == nodes[hashVal]) return NULL; 

    Node *nd = nodes[hashVal];  
    while(!nd->next) {
      if(nd->key == key) return true; 
    }
    return false; 
  }
};
