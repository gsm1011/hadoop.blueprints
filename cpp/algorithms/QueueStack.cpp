#include<iostream>
#include<queue>
#include<cstdlib>
#include<ctime>
#include"Stack.hpp"

template<typename T> 
class QueueStack : public Stack<T> {
private: 
  // use deque to implement the stack. 
  std::deque<T> qStack; 

public: 
  QueueStack() {}
  ~QueueStack() {} 

  T& top() { return qStack.front() ; }
  //T& top() const { return qStack.front(); } 

  void pop() { qStack.pop_front(); }
  void push(const T& val) { qStack.push_front(val); }
 
  bool empty() const { return qStack.empty(); } 
  int size() const { return qStack.size(); } 

};

int main() {
  Stack<int> *stack = new QueueStack<int>(); 
  srand (time(NULL));
  for(int i = 0; i < 10; i++) {
    stack->push(rand() % 100); 
  }

  while (!stack->empty()) {
    std::cout << stack->top() << std::endl; 
    stack->pop(); 
  }
  return 0 ;
}
