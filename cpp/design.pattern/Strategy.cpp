// The strategy pattern defines a family of algorithms, encapsulates
// each one, and make them interchangable. It let's the algorithm vary
// independently form clients that use it. 
#include <iostream> 

class Compositor {
public: 
  virtual void compose() = 0;
};

class SimpleCompositor : public Compositor {
public: 
  virtual void compose() {
    std::cout << "Composing with the simple compositor......" << std::endl; 
  }
};

class TexCompositor : public Compositor {
public: 
  virtual void compose() {
    std::cout << "Composing with tex compositor......" << std::endl; 
  }
}; 

class ArrayCompositor : public Compositor {
public: 
  virtual void compose() {
    std::cout << "Composing with the array compositor......" << std::endl; 
  }
};

class Composition {
public: 
  Composition(Compositor* comp) : compositor_(comp) {} 

  void doit() {
    compositor_->compose(); 
  }

  void setCompositor(Compositor* comp) {
    compositor_ = comp;
  }

private: 
  Compositor* compositor_; 
}; 

int main(int argc, char** argv) {
  Compositor* compositor = new SimpleCompositor(); 
  Composition* composition = new Composition(compositor); 
  composition->doit(); 

  composition->setCompositor(new TexCompositor()); 
  composition->doit(); 
  return 0; 
} 
