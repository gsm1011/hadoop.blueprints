// A way for an object to change its behavior at runtime without
// resorting to large monolithic conditional statements. 
#include <iostream> 

class State {
public: 
  virtual void handle() = 0; 
}; 

class StateA : public State {
public: 
  virtual void handle() {
    std::cout << "In state A......" << std::endl; 
  }
}; 


class StateB : public State {
public:
  void handle() {
    std::cout << "In state B......" << std::endl; 
  }
}; 

class StateContext { 
public: 
  StateContext(State* state):state_(state) {}
  void request() {
    state_->handle(); 
  }; 

private: 
  State* state_; 
};

int main(int argc, char** argv) {
  State* state = new StateA(); 
  StateContext* context = new StateContext(state); 
  context->request(); 

  state = new StateB(); 
  context = new StateContext(state);
  context->request();

  return 0; 
}
