#include<iostream> 
#include<string.h>

using std::ostream; 

class People {
private: 
  int age; 
  double weight; 
  char *name; 
  static int cnt; 

public: 
  int getAge() const { return age; }
  char * getName() const { return name; }
  double getWeight() const { return weight; }
  static int getCnt() { return cnt; }

  People() {
    age = 10; 
    weight = 153.4; 
    name = new char[10];
    strcpy(name, "UNKNOWN"); 
    cnt++; 
  }
  People(int a, char *n, double w) : age(a),weight(w){
    cnt++; 
    strcpy(name, n);
  }
  People(const People &p) {
    age = p.getAge(); 
    weight = p.getWeight(); 
    int len = strlen(p.getName()); 
    name = new char[len]; 
    strcpy(name, p.getName());
    cnt++; 
  }

  People & operator=(const People &p) {
    if(&p == this) return *this; 
    int len = strlen(p.getName()); 
    delete []name; 
    name = new char[len]; 
    strcpy(name, p.getName()); 
    age = p.getAge(); 
    weight = p.getWeight(); 
    return *this;
  }
  friend ostream & operator<<(ostream & os, const People &p); 
  
}; 

int People::cnt = 0; 

class Student : public People {
private: 
  int grade; 
  double score; 
  bool good;

public:
  Student():People(){
    grade = 3; 
    score = 98.00;
    good = true; 
  }
  Student(int age, char *name, double w, int g, double s, bool gd):
    People(age, name, w),grade(g),score(s),good(gd) {}
  int getGrade() const { return grade; } 
  double getScore() const { return score; } 
  bool getGood() const { return good; } 

  friend ostream & operator<<(ostream &os, const Student &s); 
}; 

ostream & operator<<(ostream &os, const People &p) {
  os << p.getAge() << " "
     << p.getName() << " "
     << p.getWeight() << std::endl; 
  return os; 
}

ostream & operator<<(ostream &os, const Student &s) {
  os << (People&)s; // output the baseclass first. 
  os << s.getGrade() << " " 
     << s.getScore() << " "
     << s.getGood() << std::endl; 
  return os; 
}
int main() {
  People *p = new People(); 
  People p1 = *p; 
  People p2 = p1; 
  People p3(p2); 
  std::cout << p->getName() << std::endl; 
  std::cout << p1.getAge() << std::endl; 
  std::cout << p1.getWeight() << std::endl; 
  std::cout << p2.getWeight() << std::endl;
  std::cout << p1; 
  std::cout << p2; 
  std::cout << p3; 
  std::cout << People::getCnt() << std::endl; 

  Student s;
  std::cout << s; 
}
