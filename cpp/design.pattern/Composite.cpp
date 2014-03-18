// A group of objects are to be treated in the same way 
// as a single instance of an object. The intent is to 
// compose objects into tree structures to represent part-
// whole hierarchies. One example is the directories and 
// files under a directory.
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <vector>

class Item {
public: 
  virtual void print() = 0; 
};

class Directory : public Item {
public: 
  Directory(std::string name):name_(name) {}
  virtual void print() {
    std::cout << "directory: " << name_ << std::endl;
    std::vector<Item*>::iterator iter = items_.begin(); 
    for(; iter != items_.end(); iter++) {
      (*iter)->print(); 
    }
  }

  void add(Item *item) {
    items_.push_back(item); 
  }

private: 
  std::vector<Item*> items_; 
  std::string name_; 
}; 

class File : public Item {
public:
  File(std::string name):name_(name) {}
  virtual void print() {
    srand(time(NULL)); 
    std::cout << "file: " << name_
	      << std::endl; 
  }

private: 
  std::string name_; 
};

int main (int argc, char ** argv) { 
  Directory *dir0 = new Directory("/"); 
  Directory *dir1 = new Directory("etc/"); 
  Directory *dir2 = new Directory("usr/");
  dir0->add(dir1); 
  dir0->add(dir2); 

  File* f1 = new File("my.cnf"); 
  File* f2 = new File("httpd.conf"); 
  File* f3 = new File("libboost.so.1");

  dir1->add(f1); 
  dir1->add(f2); 
  dir2->add(f3); 

  dir0->print(); 

  return 0; 

}
