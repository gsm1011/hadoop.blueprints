#include<iostream>
#include<unistd.h>
#include<iomanip>

using namespace std; 
// Asim problem II 2/19/2014
class Clock {
private:
  int hour, minute, second; 

public:
  Clock():hour(0),minute(0),second(0){}
  Clock(int h, int m, int s):hour(h),minute(m),second(s){}

  // setters. 
  void setHour(int h) { hour = h; } 
  void setSecond(int s) { second = s; } 
  void setMinute(int m) { minute = m; }

  // getters. 
  int getHour() { return hour; }
  int getMinute() { return minute; } 
  int getSecond() { return second; } 

  // incrementers. 
  void incrementHour() { 
    hour++; 
    hour %= 24; 
  }
  void incrementMinute() {
    minute++; 
    if (minute >= 60) incrementHour(); 
    minute %= 60; 
  }
  void incrementSecond() {
    second++; 
    if (second >= 60) incrementMinute(); 
    second %= 60; 
  }

  // print time. 
  void printCurrentTime() {
    cout << setfill('0');
    cout << "Current Time is: " << setw(2) << hour 
    	 << ":" << setw(2) << minute 
    	 << ":" << setw(2) << second << endl;
  }

  void incrementSomeSeconds() {
    int ss; 
    cout << "How many seconds you want to increment: "; 
    cin >> ss; 
    if (ss < 0) {
      cout << "Wrong number! Can not be negative." << endl; 
      return; 
    }
    for(int i = 0; i < ss; i++) {
      incrementSecond(); 
    }
  }
}; 

int main() {
  // Clock *clock = new Clock(10, 10, 10); 
  // clock->printCurrentTime(); 
  // clock->incrementSecond(); 
  // clock->printCurrentTime();

  // while(1) {
  //   clock->incrementSecond(); 
  //   clock->printCurrentTime(); 
  //   usleep(2000); 
  // }
  Clock clock; 
  clock.printCurrentTime(); 
  clock.incrementSomeSeconds(); 
  clock.printCurrentTime();

  return 0; 
}
