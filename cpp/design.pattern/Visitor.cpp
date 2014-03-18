// Visitor pattern is a way of separating an algorithm from an object
// structure on which it operates. So, we can add new operations to
// existing object structures without modifying those structures. 
#include <iostream>

class Visitor;

class Element {
public: 
  Element(std::string n):name_(n) {}
  virtual void accept(Visitor* visitor) = 0 ; 
  virtual void whoami() = 0; 

  std::string getName() const { return name_; }

protected: 
  std::string name_;
}; 

class Visitor {
public: 
  virtual void visit(Element* element) = 0; 
}; 

class ElementA : public Element {
public: 
  ElementA(std::string n):Element(n) {}
  virtual void accept(Visitor* visitor) {
    visitor->visit(this); 
  }
  virtual void whoami() {
    std::cout << "I am element ......" << getName() << std::endl;
  }
};

class ElementB : public Element {
public: 
  ElementB(std::string n):Element(n) {}
  virtual void accept(Visitor* visitor) {
    visitor->visit(this); 
  }
  virtual void whoami() {
    std::cout << "I am element ......" << getName() << std::endl;
  }
}; 

class ElementVisitor : public Visitor {
public: 
  virtual void visit(Element* e) {
    e->whoami(); 
  }
}; 

int main(int argc, char** argv) {
  Visitor* v = new ElementVisitor(); 
  Element* e = new ElementA("elementA"); 
  e->accept(v); 

  e = new ElementB("elementB"); 
  e->accept(v); 

  return 0; 
}
