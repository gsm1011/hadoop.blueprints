// An adapter design pattern provides a different 
// interface using existing implementations. So, 
// it should compose of object of existing code. 
// It is similar like an agent translate the call 
// to a method of class A to the actual method. 
#include<iostream>
#include<string>

using namespace std; 

class Phone {
private:
  string name; 
  double price; 
  bool smart; 

public: 
  Phone() {
    name = "Plain Phone"; 
    price = 200; 
    smart = false; 
  }

  // getters.
  string getName() const { return name; }
  double getPrice() const { return price; }
  bool getSmart() const { return smart; }

  // setters. 
  void setName(string n) { name = n; }
  void setPrice(double p) { price = p; }
  void setSmart(bool s) { smart = s; }
}; 

class GalaxyS4 : public Phone {
public: 
  GalaxyS4():Phone() {
    setName("Sum Sung GalaxyS4."); 
    setSmart(true); 
    setPrice(532.34); 
  }
}; 

class IPhone5 : public Phone {
public: 
  IPhone5():Phone() {
    setName("IPhone 5."); 
    setSmart(true); 
    setPrice(645.60); 
  }
}; 

class PhoneOperator {
public: 
  virtual string phoneName() = 0;
  virtual double phonePrice() = 0; 
  virtual bool phoneSmart() = 0; 
};

class PhoneAdapter : public PhoneOperator {
private: 
  Phone* phone; // adaptee.

public: 
  PhoneAdapter(Phone* p) {
    phone = p; 
  }

  string phoneName() {
    return phone->getName(); 
  }

  double phonePrice() {
    return phone->getPrice(); 
  }

  bool phoneSmart() {
    return phone->getSmart(); 
  }
}; 

// test the adapater. 
int main() {
  PhoneOperator* op = new PhoneAdapter(new GalaxyS4()); 

  cout << "Name: " << op->phoneName() << endl; 
  cout << "Price:" << op->phonePrice() << endl; 
  cout << "Smart:" << op->phoneSmart() << endl; 

  return 0; 
}
