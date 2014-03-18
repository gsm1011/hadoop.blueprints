#include<iostream>

using namespace std; 

int main() {
  int a = 1024; 
  int b = a & (1 << 10); 
  cout << a << " " << b << endl; 

  return 0; 
}
