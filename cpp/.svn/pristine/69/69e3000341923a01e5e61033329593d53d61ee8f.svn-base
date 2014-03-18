// This file container all kinds of c++ containers. 
#include<iostream> 
#include<string> 

// containers.
#include<array>
#include<vector>
#include<deque>
#include<list> 
#include<stack> 
#include<queue> // defined deque and priority_queue
#include<set>	// defined set and multiset
#include<map>	// defined map and multimap.

// others. 
#include<cstdlib>

class Person {
private: 
  std::string name; 
  int age; 
  bool sex; // 0 for male and 1 for female. 
  double height; // in cms. 

public:
  // constructors. 
  Person() {}
  Person(std::string n, int a, bool s, double h) : name(n), age(a), sex(s), height(h) {} 

  // getters. 
  std::string getName() const { return name; } 
  int getAge() const { return age; } 
  bool getSex() const { return sex; } 
  double getHeight() const { return height; } 

  // setters. 
  void setName(std::string n) { name = n; } 
  void setAge(int a) { age = a; } 
  void setSex(bool s) { sex = s; } 
  void setHeight(double h) { height = h; } 

  // other methods. 
  friend std::ostream& operator<<(std::ostream& os, const Person & person) {
    os << "Person info: " << std::endl
       << "Name   : " << person.getName() << std::endl
       << "Age    : " << person.getAge() << std::endl
       << "Sex    : " << person.getSex() << std::endl// ? " Male" : " Female"}
       << "Height : " << person.getHeight() << std::endl; 
    return os; 
  }
};

struct ComparePerson {
  bool operator()(const Person *a, const Person *b) {
    return a->getAge() > b->getAge();
  }
}; 

int main() {
  const int SIZE = 2; 
  std::array<Person*, SIZE> pArray; 
  std::vector<Person*> pVector; 
  std::stack<Person*, std::deque<Person*> > pStack; 
  std::queue<Person*, std::deque<Person*> > pQueue; 
  std::deque<Person*, std::allocator<Person*> > pDeque; 
  std::priority_queue<Person*, std::vector<Person*>, ComparePerson > pPq; 
  std::map<Person*, int, ComparePerson> pMap; 
  std::set<Person*, ComparePerson> pSet; 

  for( int i = 0; i < SIZE; i++) {
    std::string name("john"); 
    int age = rand() % 100; 
    bool sex = rand() % 100 > 50 ? 0 : 1; 
    double height = (double)(rand() % 100) + 100.00; 
    Person *p = new Person(name, age, sex, height); 

    if(NULL == p) { 
      std::cerr << "Error creating Person object." << std::endl; 
      return 1; 
    }

    pArray[i] = p;		// put to array. 
    pVector.push_back(p);	// put to vector. 
    pStack.push(p); 		// put to stack. 
    pQueue.push(p);		// put to queue.
    pDeque.push_back(p);	// put to deque.
    pPq.push(p);		// put to priority queue. 
    pMap.insert(std::pair<Person*, int>(p, 1));	// put to map. 
    pSet.insert(p); 		// put to set.
  }  

  // array. 
  std::cout << "Output using array." << std::endl; 
  for ( int i = 0; i < SIZE; ++i) {
    std::cout << *pArray[i] << std::endl;
  }

  // vector. 
  std::cout << "Output using Vector." << std::endl;
  std::vector<Person*>::iterator iterVector = pVector.begin(); 
  for(; iterVector != pVector.end(); iterVector++) {
    std::cout << **iterVector << std::endl; 
  }

  // stack. 
  std::cout << "Output using Stack." << std::endl;
  while(!pStack.empty()) {
    std::cout << *(pStack.top()) << std::endl;
    pStack.pop(); 
  }

  // queue. 
  std::cout << "Output using Queue." << std::endl;
  while(!pQueue.empty()) {

    std::cout << *(pQueue.front()) << std::endl;
    pQueue.pop(); 
  }

  // deque. 
  std::cout << "Output using Deque." << std::endl;
  std::deque<Person*>::iterator iterDeque = pDeque.begin();
  for(; iterDeque != pDeque.end(); iterDeque++) {
    std::cout << **iterDeque << std::endl;
  }

  // priority queue. 
  std::cout << "Output using Priority Queue." << std::endl;
  while(!pPq.empty()) {

    std::cout << *(pPq.top()) << std::endl;
    pPq.pop();
  }

  // map.
  std::cout << "Output using Map." << std::endl;
  std::map<Person*, int>::iterator iterMap = pMap.begin();
  for(; iterMap != pMap.end(); iterMap++) {
    std::cout << *(iterMap->first) << std::endl;
  }

  // set. 
  std::cout << "Output using Set." << std::endl;
  std::set<Person*>::iterator iterSet = pSet.begin();
  for(; iterSet != pSet.end(); iterSet++) {
    std::cout << **(iterSet) << std::endl;
  }
}
