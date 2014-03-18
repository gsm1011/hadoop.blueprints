// This file collects some examples of template in C++. 
// For example, template classes and template functions.
// It should be noted that the *template* here is different
// from the template method.
#include<stdio.h>
#include<string.h> 
#include<iostream> 
#include<stdlib.h> 

using namespace std; 

int checkInt(int in);

template <typename T> void printArray(T [], int s); 

struct student {
  int age : 8; 
  char name[100];
  float height; 
}; 

union id {
  int idd; 
  char idds[4]; 
}; 

enum cls {
  cls1, cls2, cls3
}; 

template <typename T> void swapIt(T &a, T &b); 

template <typename T> void swapIt(T *a, T *b, int s); 

int main() {
  checkInt(0); 
  //  int x[] = {2}; 
  int y[] = {1,2,3,4,5};
  // int z[10] = {0};
  int *p = new int;  
  // int *p1 = y; 
  char ss[100] = "hello there"; 
  student s = {
    10, "shumin", 10.2
  };
  cout << s.age << "\t" << s.name << "\t" << s.height << endl; 
  // ss[2] ='\0';

  id id1; 
  id1.idd = 100; 
  // strcpy(id1.idds, "hi");
  cout << id1.idd << " " << id1.idds << " Size: " << sizeof(id1) << endl; 

  cls c1; 
  c1 = cls2; 
  cout << c1 << " size: " << sizeof(c1) << endl; 
  
  string name; 
  cout << "please enter your name: ";
  cin >> name; 
  cin.getline(ss, 100); 

  *p = 100l; 
  cout << "my name is: " << name << endl; 
  cout << ss << endl; 
  cout << *p << " " << p << endl; 
  /* value from array. */
  p = y; 
  for(int i = 0; i < 5; ++i) {
    cout << *(p+i) << "\t" << endl; 
  }

  // printArray(y, 20); 
  // printArray(z, 10); 
  printf("String : %s, Length: %d\n", ss, strlen(ss));

  // arrays. 
  int *p2 = new int[100];
  for(int i = 0; i < 100; i++) {
    *(p2+1) = rand() % 100; 
  }
  for(int i = 1; i < 100; i++) {
    cout << *(p2+1) << endl; 
  }

  cout << "Test function templates: " << endl;
  // function template
  double m, n; 
  m = 1111; 
  n = 2222; 
  cout << m << " " << n << endl; 
  swapIt(m, n); 
  cout << m << " " << n << endl; 

  cout << "Overloaded function template: " << endl; 
  double m1[] = {2.3,3.4,5.6}; 
  double n1[] = {1.1,2.2,3.3}; 
  printArray(m1, 3), printArray(n1, 3);  
  swapIt(m1, n1, 3); 
  cout << endl; 
  printArray(n1, 3), printArray(m1, 3); 
  
  return 0; 
}

int checkInt(int in) {
  if(in) return 1; 
  return 0; 
}

template <typename T>
void printArray(T x[], int s) {
  for( int i = 0 ; i < s; i++) {
    cout << x[i] << endl; 
  }
}

template<typename T>
void swapIt(T &a, T &b) {
  T tmp; 
  tmp = b; 
  b = a; 
  a = tmp; 
}

template <typename T> 
void swapIt(T a[], T b[], int s) {
  T tmp; 
  for( int i = 0; i < s; i++) {
    tmp = b[i]; 
    b[i] = a[i]; 
    a[i] = tmp; 
  }
}
