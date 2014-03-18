#include<iostream> 
#include<map>

using namespace std; 

class Static {
public: 
  Static(int a, int h) : age(a),height(h){
    id = cnt++; 
  } 
  
  void setAge(int a) { age = a; } 
  void setHeight(int h) { height = h; }

  int getAge() { return age; } 
  int getHeight() { return height; } 
  int getId() { return id; } 
  static int getCnt() { return cnt; } 

private:
  int age; 
  int height; 
  int id; 
  static int cnt; 
}; 

int Static::cnt = 0; 

int main() {
  Static * s = new Static(30, 178); 
  map<int, Static*> m; 

  if( NULL == s) {
    cerr << "Error allocating memory for object." << endl; 
    return 1; 
  }

  int h = 158; 
  for(int i = 0; i < 10; i++) {
    s = new Static(30, h); 
    h += 20; 
    m[s->getId()] = s; 
  }
  
  map<int, Static*>::iterator iter; 
  for(iter = m.begin(); iter != m.end(); ++iter) {
    cout << iter->first << " " << iter->second->getHeight() << endl;
  }

  cout << "total instances: " << Static::getCnt() << endl; 
}
