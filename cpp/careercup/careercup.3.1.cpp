#include <iostream>

using namespace std; 

// using an array to implement 3 stacks. 
class ArrayStack {
private:
  int start; 
  int end; 
  int mid1 = end / 3; 
  int mid2 = end - end / 3; 
  int p1, p2, p3;
  int * array ; 

public: 
  ArrayStack(int size) { 
    start = 0; 
    end = size; 
    array = new int[size]; 

    // initialize the stack indices.
    mid1 = end / 3;
    mid2 = end - end / 3; 
    p1 = mid1; 
    p2 = mid2; 
    p3 = end - 1; 
  } 
  
  void push(int val) { 
    // push a val into the stack arrays. 
    if(p1 >= 0) array[p1--] = val; 
    else if(p2 >= mid1) array[p2--] = val; 
    else if(p3 >= mid2) array[p3--] = val; 
  }

  int pop() {
    if(p3 < end - 1) return array[p3]; 
    else if(p2 < mid2 - 1) return array[p2]; 
    else if(p1 < mid1 - 1) return array[p1]; 
    else return -1; 
  }

  // push a value into an indexed stack. 
  void push(int val, int idx) {
    if (idx < 1 || idx > 3) return ; 

    switch(idx) {
    case 1: {
      if(p1 < 0) { 
	cout << "Stack one overflows." << endl; 
	return; 
      } 
      array[p1--] = val; break; 
    }
    case 2: { 
      if(p2 <= mid1) {
	cout << "Stack two overflows." << endl; 
	return ; 
      } 
      array[p2--] = val; break; 
    }
    case 3: {
      if(p3 <= mid2) {
	cout << "Stack three overflows. " << endl; 
      }
      array[p3++] = val; break; 
    }
    default: void; 
    }
  }
}; 

int main() {

}
