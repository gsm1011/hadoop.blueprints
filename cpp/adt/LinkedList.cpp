#include<exception>
#include"LinkedList.hpp" 

template<typename T>
bool ADT::LinkedList<T>::isEmpty() {
  return 0 == numElements; 
}

template<typename T>
bool ADT::LinkedList<T>::isFull() {
  return numElements >= capacity; 
}

// idx is 0..numElements-1
template<typename T>
T& ADT::LinkedList<T>::get(int idx) {
  if(numElements <= idx) {
    throw std::exception::exception("Out of range."); 
  }
  LinkedNode * ptr = listHead; 
  while(idx >= 0) ptr = ptr->next; 

  return ptr->getElement(); 
}
template<typename T>
void ADT::LinkedList<T>::append(T o) {
  LinkedNode *ptr = listHead; 
  LinkedNode *node = new LinkedNode(o);
  if(NULL == node) return; 

  if (NULL == ptr) {
    listHead = node;
  } else {
    while(ptr->next) ptr = ptr->next; 
    
    ptr->next = node; 
    node->pre = ptr; 
  }
  numElements++; 
}

template<typename T>
bool ADT::LinkedList<T>::deleteElement(int i) {
  if(i >= count()) {
    cout << "Out of range!" << endl;
    return false; 
  }
  LinkedNode *ptr = listHead; 
  while(0 < i--) ptr = ptr->next; 
  ptr->pre->next = ptr->next; 
  ptr->next->pre = ptr->pre; 
  numElements--; 
  delete ptr; 
  return true; 
}
template<typename T>
bool ADT::LinkedList<T>::purge() {
  LinkedNode *node; 
  while(listHead) {
    node = listHead;
    listHead = node->next; 
    delete node; 
  }
  numElements = 0; 
  return true; 
}

template<typename T>
T& ADT::LinkedList<T>::operator[] (int i) {
  return get(i);
}

// operator <<. 
template<typename T>
ostream& ADT::operator<<(ostream & os, const ADT::LinkedList<T> & list) {
  os << "Linked List: " << endl
     << "Number of elemetns: " << list.count() << endl; 
  
  typename ADT::LinkedList<T>::LinkedNode * node = list.getListHead(); 
  while(node) {
    cout << node->getElement() << endl;
    node = node->next; 
  }
  return os; 
}

//template class LinkedList<int>;
