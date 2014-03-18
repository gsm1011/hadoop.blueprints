#include<iostream> 
#include<cstdlib> 
#include<ctime>

typedef unsigned int size_t; 

void genRandom(int array[], size_t size);

template<typename T> 
void bubbleSort(T array[], size_t size); 

template<typename T>
void selectionSort(T array[], size_t size); 

template<typename T> 
void printArray(T array[], size_t size); 

// main
int main() {
  const int LEN = 20; 
  int array[LEN]; 

  // bubble sort. 
  std::cout << "Bubble sort......" << std::endl;
  genRandom(array, LEN); 
  //printArray(array, LEN); 
  bubbleSort(array, LEN); 
  //printArray(array, LEN); 

  // selection sort. 
  std::cout << "Selection sort ...... " << std::endl;
  genRandom(array, LEN); 
  //printArray(array, LEN); 
  selectionSort(array, LEN); 
  //printArray(array, LEN); 

  return 0; 
}

void genRandom(int array[], size_t size) {
  srand(time(NULL)); 
  // generate random array for testing. 

  for(size_t i = 0; i < size; i++) {
    array[i] = rand() % 100; 
  }
}

template<typename T> 
void bubbleSort(T array[], size_t size) {
  for(size_t i = 0; i < size; i++) {
    for(size_t j = 0; j < size; j++) {
      if(array[i] < array[j]) {

	T tmp = array[i]; 
	array[i] = array[j]; 
	array[j] = tmp; 
      }
    }
    printArray(array, size); 
  }
}

template<typename T>
void selectionSort(T array[], size_t size) {
  bool sorted = false; 
  T maxVal; 
  int maxIndex; 
  for(size_t i = 0; i < size && !sorted; i++) {
    maxVal = array[0]; 
    maxIndex = 0; 
    sorted = true; 
    for(size_t j = 1; j < size - i; j++) {
      if(array[j] >= maxVal) {
	maxVal = array[j]; 
	maxIndex = j; 
      } else sorted = false; 
    }
    array[maxIndex] = array[size - i - 1]; 
    array[size - i - 1] = maxVal; 

    printArray(array, size); 
  }
}

template<typename T> 
void printArray(T array[], size_t size) {
  for( int i = 0; i < size; i++) {
    std::cout << array[i] << " "; 
  }
  std::cout << std::endl; 
}
