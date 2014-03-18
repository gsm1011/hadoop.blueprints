#include<iostream>
#include<thread> 
#include<vector> 

using namespace std; 

class threadcls {
private: 
  int id; 

public: 
  static int threadId; 

  threadcls() { id = threadId++; }
  void func() {
    int i = 0; 
    while (true) {
      cout << "Thread: " << id << " " << i++ << endl; 
    }
  }
};

int threadcls::threadId = 0;

int main() {
  vector<thread *> threads; 
  threadcls * cls = NULL; 
  for(int i = 0; i < 10; i++) {
    cls = new threadcls(); 
    thread * th = new thread(&threadcls::func, *cls); 
    threads.push_back(th); 
  }


  for(int i = 0; i < 10; i++) {
    threads[i]->join(); 
  }
  return 0; 
}
