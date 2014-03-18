#include<iostream>
#include<string>
#include <fstream> 

using namespace std; 

class Employee {
public: 
  Employee() {}
  
  Employee(double rate, double hrs) {
    hourlyRate = rate; 
    hours = hrs; 
  }
  // getters. 
  double getRate() const { return hourlyRate; }
  double getHours() const { return hours; } 

  // setters. 
  void setRate(double r) { hourlyRate = r; } 
  void setHours (double h) { hours = h; } 

  // get gross pay. 
  double grossPay() {
    return hourlyRate * hours; 
  }

  // print employee info. 
  void printInfo() {
    cout << "Hourly Rate  : " << hourlyRate << endl
	 << "Hours worked : " << hours << endl
	 << "Gross pay    : " << grossPay() << endl << endl; 
  }

private: 
  double hourlyRate; 
  double hours; 
}; 

class PayRoll {
public: 
  // constructors. 
  PayRoll() { 
    cnt = 0; 
    dataFileName = ""; 
  }
 
  PayRoll(string file) {
    cnt = 0; 
    dataFileName = file; 
  }

  // getter. 
  string getDataFileName() { return dataFileName; } 

  // setters. 
  void setDataFileName(string n) { dataFileName = n; } 

  // read data from file. 
  void loadDataFromFile() {
    if(dataFileName == "") {
      cout << "Data file not given!" << endl; 
      return ; 
    }

    ifstream ifs(dataFileName, ifstream::in);  
    double r, h; 
    while (ifs.good()) {
      ifs >> r >> h; // similar to cin. 
      Employee *em = new Employee(r, h); 
      empl[cnt++] = *em; 
    }
    ifs.close(); 
  }

  void printEmployees() {
    for(int i = 0; i < cnt; i++) {
      empl[i].printInfo(); 
    }
  }

private: 
  string dataFileName; 
  int cnt; 
  Employee empl[7];
}; 

int main() {
  PayRoll *payroll = new PayRoll("payroll.dat");
  (*payroll).loadDataFromFile(); 
  (*payroll).printEmployees(); 

  // not using pointer
  PayRoll payroll1("payroll.dat");
  payroll1.loadDataFromFile(); 
  payroll1.printEmployees();  

  return 0; 
}
