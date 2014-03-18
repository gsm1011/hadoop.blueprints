#include<iostream>
#include<ctime>

class Singleton {
private: 
  time_t timer; 
  static Singleton* instance; 

  // make the constructor private.
  Singleton() {
    time(&timer); 
    //instance = NULL; // not work as instance is static.
  }

public: 
  static Singleton* newInstance() {
    // take special care for multithreaded 
    // environments. 
    if(NULL == instance) {
      instance = new Singleton(); 
    }
    return instance; 
  }

  time_t getTime() const {
    return timer; 
  }

}; 

// This is important!!!
Singleton* Singleton::instance = NULL; 

int main() {
  Singleton* inst = NULL;
  for(int i = 0; i < 10; ++i) {
    inst = Singleton::newInstance(); 
    std::cout << inst << " " << inst->getTime() << std::endl; 
  }
}
