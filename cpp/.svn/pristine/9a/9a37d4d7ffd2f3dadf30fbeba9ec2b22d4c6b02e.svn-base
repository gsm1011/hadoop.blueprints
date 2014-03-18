#ifndef _LIST_H_
#define _LIST_H_
#include"Object.hpp"
namespace ADT {
  template<typename T> 
  class List : public Object {
  public: 
    // test if list is empty. 
    virtual bool isEmpty() = 0; 

    // test if list if full; 
    virtual bool isFull() = 0; 

    // get the element at idx; 
    virtual T& get(int idx) = 0; 

    // append an element to the end of the list; 
    virtual void append(T o) = 0; 

    // count the number of elements in the list.
    virtual int count() = 0; 

    // delete the element at i. 
    virtual bool deleteElement(int i) = 0; 

    // delete all the elements. 
    virtual bool purge() = 0; 

    // operator []. 
    T& operator[](int i); 

  }; 
}
#endif
