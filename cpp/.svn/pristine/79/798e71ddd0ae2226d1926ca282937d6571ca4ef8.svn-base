// This pattern helps decouple the interface from implementation so 
// that they can vary independently. 
// Some use cases include implementation using different techniques. 
#include <iostream> 

// Implementation.
class SmartPhoneImpl {
public: 
  virtual void call(std::string num) = 0; 
  virtual void message(std::string msg) = 0; 
}; 

class SmartPhoneImplA : public SmartPhoneImpl {
public: 
  virtual void call(std::string num) {
    std::cout << "Calling number: " << num 
	      << " by A." << std::endl;
  }
  virtual void message(std::string msg) {
    std::cout << "Sending message from A " << msg << std::endl; 
  }
};

class SmartPhoneImplB : public SmartPhoneImpl {
public:
  virtual void call(std::string num) {
    std::cout << "Calling number: " << num
              << " by B." << std::endl;
  }
  virtual void message(std::string msg) {
    std::cout << "Sending message from B " << msg << std::endl;
  }
}; 

// abstraction. 
class SmartPhone {
private:
  SmartPhoneImpl* impl_ = NULL; 

public: 
  SmartPhone(SmartPhoneImpl* impl):impl_(impl) {}

  void call(std::string num) {
    impl_->call(num); 
  }

  void message(std::string msg) {
    impl_->message(msg);
  }
};


int main( int argc, char** argv) {
  SmartPhone* phone = new SmartPhone(new SmartPhoneImplA()); 
  phone->call("12345");
  phone->message("hi there");

  return 0; 
}
