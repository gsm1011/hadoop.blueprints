// This pattern provides a simplified interface to an underlying 
// implementation object. Thus it makes a complex library or tool 
// easier to use. 
#include <iostream> 

// the following example idea is from Wikipedia: 
// http://en.wikipedia.org/wiki/Facade_pattern

class CPU {
public: 
  void freeze() {
    std::cout << "CPU is being freezed..." << std::endl; 
  }
  void jump(long pos) {
    std::cout << "Jumping to location " << pos << std::endl; 
  }
  void execute() { 
    std::cout << "Executing program..." << std::endl; 
  }
}; 

class Memory {
public: 
  void load(long pos, char* data, int len) {
    std::cout << "Loading data at " << pos << std::endl; 
  }
}; 

class HardDrive {
public: 
  char* read(long lba, int& size) {
    std::cout << "Reading data from location " << lba << std::endl; 
    return NULL; 
  }
}; 

class ComputerFacade {
public: 
  ComputerFacade() {
    processor = new CPU(); 
    ram = new Memory(); 
    hd = new HardDrive(); 
  }

  // this method simplified the operation of 
  // starting a computer, which includes a few 
  // steps and is complicated. The start method
  // hides these complexity and makes it simple 
  // for clients to start a computer. 
  void start() {
    // freeze cpu. 
    processor->freeze(); 

    // load the memory. 
    long lba = 0x3456792A; 
    long pos = 0x00001000; 
    int size = 0x00100000; 
    char* dat = hd->read(lba, size); 

    ram->load(pos, dat, size); 

    // start execution. 
    processor->jump(pos); 
    processor->execute(); 
    std::cout << "Computer started successfully....." << std::endl; 
  }

private: 
  CPU* processor; 
  Memory* ram; 
  HardDrive* hd; 
}; 
  

int main( int argc, char** argv) {
  ComputerFacade* facade = new ComputerFacade(); 
  facade->start(); 
}
