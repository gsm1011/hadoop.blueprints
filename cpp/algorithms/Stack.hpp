#include<iostream> 

template <typename T>
class Stack {
public:
  virtual T& top() = 0; 
  // virtual T& top() const = 0; 

  virtual void pop() = 0; 
  virtual void push(const T& val) = 0; 

  virtual bool empty() const = 0; 
  virtual int size() const = 0; 

  virtual ~Stack() {}
};
