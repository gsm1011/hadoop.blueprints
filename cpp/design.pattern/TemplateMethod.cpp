// The template method pattern is to define the skeleton of 
// an algorithm in an operation, deferring some steps to the
// derived classes. 
// This pattern let's subclasses redefine certain steps of an 
// algorithm without letting them to change the algorithm structure. 

#include <iostream> 

const double PI = 3.1415926;

enum Color {
  red, yellow, blue
}; 

class Shape {
public:
  Shape(Color c):color_(c) {}
  Shape() {
    color_ = red; 
  }
  virtual void draw() = 0; 
  virtual double area() = 0; 
  virtual void redraw() = 0;
  virtual void setColor(Color clr) {
    color_ = clr;
  }

private:
  Color color_;
};

class Rectangle : public Shape {
public:
  Rectangle(Color c, double l, double w):Shape(c),length_(l),width_(w) {}
  
  virtual void draw() {
    std::cout << "Drawing rectangle...." << std::endl; 
  }
  virtual double area() {
    return width_ * length_; 
  }
  virtual void redraw() {
    std::cout << "Redrawing the rectangle..." << std::endl; 
  }

private: 
  double length_; 
  double width_; 
};

class Square : public Rectangle {
public:
  Square(Color c, double side):Rectangle(c, side, side) {}
};

class Circle : public Shape {
public:
  Circle(Color c, double r):Shape(c),radius_(r) {}
  virtual void draw() {
    std::cout << "Drawing the circle ..." << std::endl; 
  }
  virtual double area() {
    return PI * radius_ * radius_; 
  }
  virtual void redraw() {
    std::cout << "Redrawing the circle..." << std::endl; 
  }
private:
  double radius_;
};

int main(int argc, char** argv) {
  Shape *shape = new Rectangle(red, 10.5, 21.2);
  shape->draw(); 

  shape = new Circle(blue, 22.4); 
  shape->redraw(); 

  shape = new Square(yellow, 20);
  std::cout << shape->area() << std::endl; 
  
  return 0; 
}

