#include<stdio.h>

int add(int a, int b) {
  printf("Addition -- "); 
  return a + b; 
}

int sub(int a, int b) {
  printf("Subtraction -- ");  
  return a - b; 
}

int mul(int a, int b) {
  printf("Multiplication -- "); 
  return a * b; 
}

int div(int a, int b) {
  printf("Division -- "); 
  return a / b; 
}

// compare two integer values. 
int compare(int a, int b) {
  return a - b; 
}

void bubbleSort(int list[], int size) {
  int i, j; 
  for (i = 0; i < size; i++) {
    for(j = i; j < size; j++) {
      if (compare(list[i], list[j])) {
	int tmp = list[i]; 
	list[i] = list[j];
	list[j] = tmp; 
      }
    }
  }
}

void sortAndDisplay(int x[], int s, void (*_method_ptr)(int[], int)) {
  _method_ptr(x, s); 
  for (int i = 0; i < s; i++) {
    printf("%d ", x[i]); 
  }
  printf("\n"); 
}

void display(int a, int b, int (*op)(int, int)) {
  printf("Operator 1: %d, operator 2: %d --> Result is: %d\n", a, b, op(a, b)); 
}

int main() {
  display(10, 3, add); 
  display(20, 10, sub);
  display(100,2,mul); 
  display(200,5,div); 

  // operation on arraies. 
  int a[] = {-12, 3, 5, 90, -75}; 
  sortAndDisplay(a, 5, bubbleSort); 
}
