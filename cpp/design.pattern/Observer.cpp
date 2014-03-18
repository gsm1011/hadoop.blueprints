// A subject keeps track of a list of observer
// objects and notify them when something happens.
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector> 
#include<random>
#include<algorithm>

class Observable {
public: 
  virtual void notify() = 0; 
}; 

class Ob1 : public Observable {
public: 
  void notify() {
    std::cout << "Ob1 notified" << std::endl; 
  }
}; 

class Ob2 : public Observable {
public: 
  void notify() {
    std::cout << "Ob2 notified" << std::endl;
  }
};

// the subject to observe. 
class Subject {
private:
  std::vector<Observable*> obs; 

public:
  Subject() {}

  void notifyAll() {
    for(std::vector<Observable*>::iterator it = obs.begin(); it != obs.end(); it++) {
      (*it)->notify(); 
    }
  }
  
  void registerOb(Observable* ob) {
    obs.push_back(ob); 
  }

  void shuffleAll() {
    random_shuffle(obs.begin(), obs.end());
  }
};

int main() {
  Subject *sub = new Subject(); 
  Observable *obsv = NULL;
  for(int i = 0; i < 100; ++i) {
    int rnd = rand() % 100; 
    if(rnd < 20) { 
      obsv = new Ob1(); 
      sub->registerOb(obsv); 
    } else {
      obsv = new Ob2(); 
      sub->registerOb(obsv);
    }
  }
  sub->shuffleAll();
  sub->notifyAll();
  return 0; 
}
