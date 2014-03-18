#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_ 
#include<iostream>
#include"Object.hpp"
#include"List.hpp"

using namespace std; 
namespace ADT { 
  template <typename T> 
  class LinkedList : public List<T> {
  public: 
    //template<typename N> 
    class LinkedNode : public Object {
    private: 
      T element; 
    public:
      LinkedNode *pre, *next; 

    public: 
      LinkedNode() { pre = next = NULL; }
      LinkedNode(T e) : element(e) {} 
      T& getElement() { return element; }
      void setElement(T& e) { element = e; }
    }; 

    // a ctors 
    LinkedList<T>(LinkedNode *n)
    : listHead(n), capacity(100) {} 
    LinkedList<T>() 
    : listHead(NULL),capacity(100) {} 

    // getters. 
    LinkedNode * getListHead() { return listHead; }

    // methods. 
    virtual bool isEmpty(); 
    virtual bool isFull(); 
    virtual T& get(int idx); 
    virtual void append(T o); 
    virtual int count() { return numElements; }
    virtual bool deleteElement(int i); 
    virtual bool purge(); 
    virtual T& operator[](int i);
  
    template <typename U>
    friend ostream& operator<<(ostream & os, const LinkedList<U> & list);
    // alternatively. 
    //template<>
    // friend ostream& operator<< <T>(ostream& os, const LinkedList<T>& list); 

  private: 
    LinkedNode *listHead;
    int numElements;
    int capacity; 
  }; 

template <typename U>
ostream& operator<<(ostream & os, const LinkedList<U> & list);
    
}
#endif
