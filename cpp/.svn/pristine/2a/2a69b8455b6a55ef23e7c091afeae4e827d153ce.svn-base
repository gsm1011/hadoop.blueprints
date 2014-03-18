#include<iostream> 
#include<string>

using namespace std; 

class Phone {
public: 
  virtual void call(string num) = 0; 
  virtual void message(string msg, string num) = 0; 
  virtual void poweron() = 0; 
  virtual void poweroff() = 0; 

  string getName() { return name; }
  int getLength() { return length; } 
  int getWidth() { return width; }
  int getBatteryLife() { return batterylife; }

  void setName(string n) { name = n; } 
  void setLength(int l) { length = l; } 
  void setWidth(int w) { width = w; } 
  void setBatteryLife(int bl) { batterylife = bl; } 
  
private: 
  string name; 
  int length; 
  int width; 
  int batterylife; 
}; 

class SumSungPhone : public Phone {
public: 
  void call(string num) {
    cout << " Samsung Calling " << num << endl; 
  }

  void message(string msg, string num) {
    cout << " Samsung --> Sending message " 
	 << msg << " to " << num << endl; 
  }

  void poweron() {
    cout << "SamSung turning on" << endl; 
  }

  void poweroff() {
    cout << "SamSung turning off" << endl; 
  }

};

class IPhone : public Phone {
public: 
  void call(string num) {
    cout << " IPhone Calling " << num << endl; 
  }

  void message(string msg, string num) {
    cout << " IPhone --> Sending message " 
	 << msg << " to " << num << endl; 
  }

  void poweron() {
    cout << "IPhone turning on" << endl; 
  }

  void poweroff() {
    cout << "IPhone turning off" << endl; 
  }

};

class Factory {
 public: 
  Phone* createPhone(string type) {
    if(type == "SumSung") {
      phone = new SumSungPhone(); 

    } else if (type == "IPhone") {
      phone = new IPhone(); 

    } else {
      cerr << "Sorry, not implemented yet. " << endl; 
    }

    if(NULL == phone) {
      cerr << "Error creating phone" << endl; 
    }
    return phone; 
  }

 private: 
  Phone *phone; 
  static int count; 
}; 

int Factory::count = 0; 

int main() {
  Factory* factory = new Factory(); 
  Phone* phone = factory->createPhone("IPhone"); 

  if(phone) {
    phone->poweron(); 
    phone->message("hello", "1234567"); 
    phone->call("123456"); 
    phone->poweroff();
  }

  cout << endl; 

  phone = factory->createPhone("SumSung"); 
  if(phone) {
    phone->poweron(); 
    phone->call("4566"); 
    phone->message("hello there, ", "325456"); 
    phone->poweroff(); 
  }

  return 0; 
}
