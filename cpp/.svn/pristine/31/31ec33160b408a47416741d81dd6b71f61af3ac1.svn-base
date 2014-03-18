// Allow behavior to be added to an individual objects.

#include <iostream>
#include <string>

class Window {
public: 
  virtual void draw() = 0; 
  virtual std::string desc() = 0;
};

class SimpleWindow : public Window {
public:
  virtual void draw() {
    std::cout << "Drawing simple window..." << std::endl; 
  }
  virtual std::string desc() {
    return "simple window"; 
  }
};

class WindowDecorator : public Window {
protected: 
  Window *win_ = NULL; // the decorated window.

public:
  WindowDecorator(Window* w) : win_(w) {}
  void draw() {
    win_->draw(); 
  }
  std::string desc() {
    return win_->desc(); 
  }
}; 

class ScrollbarWindowDecorator : public WindowDecorator {
public:
  ScrollbarWindowDecorator(Window* win) : WindowDecorator(win) {}
  void draw() {
    win_->draw(); 
    drawScrollBar(); 
  }
  void drawScrollBar() {
    std::cout << "Drawing scroll bar......" << std::endl; 
  }
  std::string desc() {
    return win_->desc() + " scroll bar"; 
  }
}; 

class MenuWindowDecorator : public WindowDecorator {
public:
  MenuWindowDecorator(Window* win) : WindowDecorator(win) {}
  void draw() {
    win_->draw();
    drawMenu();
  }
  void drawMenu() {
    std::cout << "Drawing menu... " << std::endl;
  }
  std::string desc() {
    return win_->desc() + " menu ";
  }
};

int main(int argc, char** argv) {
  Window* win = new SimpleWindow();
  WindowDecorator * decoratorWin = new MenuWindowDecorator(win); 
  decoratorWin->draw();
  decoratorWin = new ScrollbarWindowDecorator(win);
  decoratorWin->draw(); 
  std::cout << decoratorWin->desc() << std::endl; 
  return 0;
}
