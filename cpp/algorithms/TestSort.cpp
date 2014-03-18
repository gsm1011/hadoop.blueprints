#include<iostream> 
#include<cstdlib> 
#include<ctime>
#include<thread>
#include"Commons.hpp"
#include"Sort.hpp"

// main
int main() {
  const int LEN = 20; 
  const int SECONDS = 0;
  int array[LEN]; 
  Sort<int> *sort = new Sort<int>();

  // bubble sort. 
  std::cout << std::endl << "Bubble sort......" << std::endl;
  genRandom(array, LEN); 
  sort->bubbleSort(array, LEN); 

  // selection sort. 
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS)); 
  std::cout << std::endl << "Selection sort ...... " << std::endl;
  genRandom(array, LEN); 
  sort->selectionSort(array, LEN); 

  // insertion sort. 
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS)); 
  std::cout << std::endl << "Insertion sort ...... " << std::endl; 
  genRandom(array, LEN); 
  printArray(array, LEN); 
  sort->insertionSort(array, LEN); 

  // merge sort. 
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Merge sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->mergeSort(array, LEN);

  // heap sort. 
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Heap sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->heapSort(array, LEN);
  printArray(array, LEN); 

  // quick sort.
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Quick sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->quickSort(array, LEN);
  printArray(array, LEN);

  // shell sort. 
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Shell sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->shellSort(array, LEN);
  printArray(array, LEN);

  // comb sort.
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Comb sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->combSort(array, LEN);
  printArray(array, LEN);

  // counting sort.
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Counting sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->countingSort(array, LEN);
  printArray(array, LEN);

  // Bucket sort.
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Bucket sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->bucketSort(array, LEN, 5);
  printArray(array, LEN);

  // Radix sort.
  std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
  std::cout << std::endl << "Radix sort ...... " << std::endl;
  genRandom(array, LEN);
  printArray(array, LEN);
  sort->radixSort(array, LEN);
  printArray(array, LEN);

  return 0; 
}
