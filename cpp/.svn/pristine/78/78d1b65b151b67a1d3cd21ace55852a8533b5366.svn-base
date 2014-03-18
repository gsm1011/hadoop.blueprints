#include<iostream>

// by putting the const keyword in front of 
// int, we are able to pass integer numbers 
// to the function. 
int square(const int& i) { return i * i; } 

int main() {
  int i = 9; 
  // int &j = i; will also work. 
  const int &j = i; 

  // j = k; // fail, j ref is const. 
  const int &m = 100; 
  std::cout << square(j) << std::endl;
  std::cout << square(5) << std::endl; 
  std::cout << square(m) << std::endl; 

  return 0; 
}
