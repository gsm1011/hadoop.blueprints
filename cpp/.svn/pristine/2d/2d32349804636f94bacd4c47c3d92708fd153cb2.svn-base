// This design pattern provides an interface
// for creating families of related or dependent 
// objects without specifying their concrete 
// classes. 
///////////////////////////////////////////////
#include<iostream>

using namespace std; 

// Example in this design pattern is to create 
// buttons and menus for windows, linux and mac os. 
// In such a case, we have three families of widgets
// depending on different operating systems. 

enum Color {
  BLUE, GREEN, RED, YELLOW
}; 

class Button {
public: 
  virtual void onExposed() = 0; 
  virtual void onClicked() = 0; 

  int getLen() { return len; } 
  int getWidth() { return width; }
  Color getColor() { return clr; }

  void setLen(int l) { len = l; }
  void setWidth(int w) { width = w; } 
  void setColor(Color c) { clr = c; } 

private: 
  int len;
  int width; 
  Color clr; 
}; 

class Menu {
public: 
  virtual void onSelected() = 0; 

  int getSize() { return size; }
  void setSize(int s) { size = s; }
  
private: 
  int size;
};

class WinButton : public Button {
public: 
  WinButton() {
    cout << "Windows button created." << endl; 
  }
  void onExposed() {
    cout << "Windows button exposed." << endl; 
  }
  void onClicked() {
    cout << "Windows button clicked." << endl; 
  }
}; 

class LinuxButton : public Button {
public: 
  LinuxButton() {
    cout << "Linux button created." << endl; 
  }
  void onExposed() {
    cout << "Linux button exposed." << endl; 
  }
  void onClicked() {
    cout << "Linux button clicked." << endl; 
  }
}; 

class WinMenu : public Menu {
public: 
  void onSelected() {
    cout << "Windows menu selected." << endl; 
  }
}; 

class LinuxMenu : public Menu {
  void onSelected() {
    cout << "Linux menu selected." << endl; 
  }
};

class Factory {
public: 
  virtual Button* createButton() = 0; 
  virtual Menu* createMenu() = 0; 

private: 
  Button* button; 
  Menu* menu; 
};

class WinFactory : public Factory {
public: 
  Button* createButton() {
    return new WinButton(); 
  }

  Menu* createMenu() {
    return new WinMenu(); 
  }
};

class LinuxFactory : public Factory {
public: 
  Button* createButton() {
    return new LinuxButton(); 
  }

  Menu* createMenu() {
    return new LinuxMenu(); 
  }
};

int main() {
  Factory* factory = new WinFactory(); 
  Button* btn = factory->createButton(); 
  Menu* mn = factory->createMenu(); 

  btn->onClicked(); 
  btn->onExposed(); 

  mn->onSelected(); 

  cout << endl; 
  factory = new LinuxFactory(); 
  btn = factory->createButton();
  btn->onClicked();
  btn->onExposed();
  btn->setColor(YELLOW); 
  cout << "Button color: " << btn->getColor() << endl; 

  return 0; 
} 
