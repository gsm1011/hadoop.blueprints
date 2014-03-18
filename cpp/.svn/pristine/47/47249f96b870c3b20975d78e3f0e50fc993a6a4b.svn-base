#include<iostream>

using std::cin; 
using std::cout; 

namespace simon1 {
  const int h = 100; 
  namespace simon3 {
    const int h = 300; 
  }; 

  namespace simon4 {
    const int h = 400; 
  }; 

  double toFarenheit ( double celcuis) {
    return celcuis * 9 / 5 + 32;
  }

  double toCelcuis( double farenheit) {
    return (farenheit - 32) * 5 / 9;   }
}; 

namespace simon2 {
  const int h = 200; 
};


int main() {
  cout << simon1::simon4::h << std::endl; 
  cout << simon1::toFarenheit(0) << std::endl; 
  cout << simon1::toCelcuis(-20) << std::endl; 
}
