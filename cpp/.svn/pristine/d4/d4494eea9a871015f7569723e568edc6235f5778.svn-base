// This pattern is useful when a lot of similiar objects are 
// needed. So, we can use one prototypical object to clone multiple 
// objects with minimal changes. 
#include <iostream>

class Clonable {
public:
  virtual Clonable* clone() = 0;
};

class Person : public Clonable {
public: 
  Person() {}
  Person(double h, std::string n, int a):height_(h),name_(n),age_(a) {}
  Person(Person& p) {
    height_ = p.getHeight(); 
    name_= p.getName();
    age_ = p.getAge(); 
  }

  // getters. 
  double getHeight() const { return height_; }
  std::string getName() const { return name_; }
  int getAge() { return age_; }
  
  // setters.
  void setAge(int a) { age_ = a; } 
  void setName(std::string n) { name_ = n; }
  void setHeight(double h) { height_ = h; }

  virtual Clonable* clone() {
    return new Person(*this);
  }

  friend std::ostream& operator<<(std::ostream& os, Person& p) {
    os << p.getName() << std::endl
       << p.getHeight() << std::endl
       << p.getAge() << std::endl; 
    return os; 
  }

private: 
  double height_; 
  std::string name_; 
  int age_; 
}; 

int main(int argc, char** argv) {
  Person *p1 = new Person(10, "simon", 32); 
  Clonable *p2 = p1->clone(); 

  Person *p3 = (Person *)p2; 
  p3->setName("Min"); 
  std::cout << (*p3) << std::endl;
}
