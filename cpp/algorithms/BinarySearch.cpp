#include<iostream> 
#include<cstdlib> 
#include<ctime>
#include"Commons.hpp"

template<typename T> 
int linearSearch(T vals[], int size, T tofind) {
  for (int i = 0; i < size; i++) {
    if(tofind == vals[i]) return i; 
  }
  return -1; 
}

template<typename T> 
int binarySearch(T vals[], int size, T tofind) {
  
  int start = 0, end = size - 1; 
  int mid = end / 2; 

  while (start < end) {
    if(tofind == vals[mid]) return mid; 
    else if(tofind < vals[mid]) {
      end = mid; mid = (start + end) / 2; 
    } else {
      start = mid; mid = (start + end) / 2; 
    }
  }
  return -1; 
}

int main() {
  srand(time(NULL)); 
  const int SIZE = 10; 
  int vals[SIZE]; 
  
  genRandom(vals, SIZE); 

  int tofind = 23; 
  int idx = binarySearch(vals, SIZE, tofind); 

  if(-1 != idx) {
    std::cout << "Find value at: " << idx << std::endl; 
  } else {
    std::cerr << "Value not found! " << std::endl; 
  }
}
