#include<iostream>

// const int const * const func(const int const * const &p) const; 
// the function can be reduced to ==>>
// int const * const func(int const * const &p) const; 
// from left to right, 
// const 1: return value can not be changed. 
// const 2: return pointer can not be changed.
// const 3: parameter can not be changed. 
// const 4: pointer p can not be changed. 
// const 5: does not make sense for non-member functions. 

int main(){ 
  // const value. 
  const int i = 100; 
  i = 200; // fails, i is const. 
  const_cast<int&> (i) = 20; // good, const is cast away. 
  
  // const pointer. 
  int x = 10; 
  int * const p = &i; 
  *p = 20; // ok, value that p is pointing to can be changed. 
  p++; // fail, pointer p is const.

  static_cast<const int&> (x) = 20; // fail, x is const now. 
  

  // const pointer + const values. 
  int x1 = 10; 
  const int * const p = & x1; 
  *p = 20; // fail, value is const. 
  p++; // fail, pointer is also const. 

}
