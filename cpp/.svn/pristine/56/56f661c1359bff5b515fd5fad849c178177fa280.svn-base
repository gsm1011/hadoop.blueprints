#include<iostream>
#include<time.h>

using namespace std; 

class Base1 {
private: 
  string hostname; 

public: 
  Base1() {
    hostname = "localhost"; 
    cout << "Base1 class constructor." << endl; 
  }
  virtual void printCurrentTime() = 0; 
  virtual void printHostName() = 0; 

  string getHostName() {
    return hostname; 
  }

  virtual ~Base1() {
    cout << "Base1 class destructor." << endl; 
  }
}; 

class Base2 {
public: 
  Base2() {
    areYouHappy = true; 
    areYouMale = true; 

    cout << "Base2 class constructor" << endl; 
  }
  bool getHappy() { return areYouHappy; }
  bool getMale() { return areYouMale; }

  virtual bool isHappy() = 0; 
  virtual bool isMale() = 0; 

  ~Base2() {
    cout << "Base2 class destructor called. " << endl; 
  }
private: 
  bool areYouHappy; 
  bool areYouMale; 
}; 

class Derived : public Base1, Base2 {
public: 
  Derived() {
    cout << "Derived class constructor" << endl; 
  }

  void printCurrentTime() {
    time_t timer; 
    time(&timer); 

    cout << "Current time in milliseconds: " << timer << endl; 
  }

  void printHostName() {
    cout << "Host name is: " << getHostName() << endl; 
  }

  // methods from base2. 
  bool isHappy() { return getHappy(); }
  bool isMale() { return getMale(); }

  ~Derived() {
    cout << "Derived destructor called. " << endl;
  }
private: 
  bool isSheHappy; 
};

int main() {
  Base1 * bp = new Derived(); 

  if(NULL == bp) {
    cerr << "Error creating derived class instance." << endl; 
    return 1; 
  }
  cout << "Hostname of super class: "  << bp->getHostName() << endl; 
  bp->printHostName();
  bp->printCurrentTime(); 

  delete bp; 
  return 0; 
}
