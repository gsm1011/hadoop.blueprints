#include<iostream>
#include<string> 

using namespace std; 

class Date {
public: 
  static string monthStrs[12]; 
  static int daysInMonth[12]; 

  // constructors and destructor. 
  Date() { day = 1, month = 1, year = 2001; }
  Date(int d, int m, int y) {
    day = d; 
    month = m; 
    year = y; 
  }
  ~Date() {}

  // getters. 
  int getDay() { return day; } 
  int getMonth() { return month; } 
  int getYear() { return year; } 

  // setters. 
  void setDay(int d) { day = d; } 
  void setMonth(int m) { month = m; } 
  void setYear(int y) { year = y; } 

  // print functions. 
  void print1() {
    cout << month << "/" << day << "/" << year << endl; 
  }  
  void print2() {
    cout << getMonthStr(month) << " " << day << ", " << year << endl;
  }

  void print3() {
    cout << day << " " << getMonthStr(month) << ", " << year << endl; 
  }

  string getMonthStr(int m) {
    if(m > 12 || m < 1) return "INVALID"; 
    return monthStrs[m]; 
  }

  // test if a given year is valid. 
  bool validYear(int y) {
    return y >= 0; 
  }

  // test if a given month is valid. 
  bool validMonth(int m) {
    return (m >= 1) && (m <= 12); 
  }

  // test if a given day is valid. 
  // note that the validity of the day should 
  // also depend on the month and the year (leap?). 
  bool validDay(int d, int m, int y) {
    cout << d << " " << m << " " << y << endl; 
    int minDay = 1, maxDay; 
    if(validYear(y) && validMonth(m)) {
      if (2 == m) { // special check for feburary.
	if (y % 100 == 0) { 
	  maxDay = ((y % 400 == 0) ? 29 : 28); 
	} else {
	  maxDay = ((y % 4 == 0) ? 29 : 28);
	}
      } else maxDay = daysInMonth[m]; // all other months.
    } else return false; 

    return (d >= minDay) && (d <= maxDay); 
  }

private: 
  int day, month, year; 
};

string Date::monthStrs[12] = {"January", "Feburary", "March", "April", "May", "June", 
		       "July", "August", "September", "October", "November", "December"}; 
int Date::daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};


int main(int argc, char** argv) {
  Date date; 
  int day, year, month; 
  // get year. 
  while(true) {
    cout << "Please enter year: "; 
    cin >> year; 
    if(date.validYear(year)) break; 
  }

  // get month. 
  while(true) {
    cout << "Please enter month: "; 
    cin >> month; 
    if(date.validMonth(month)) break; 
  }
  
  // get day. 
  while(true) {
    cout << "Please enter day: "; 
    cin >> day; 
    if(date.validDay(day, month, year)) break; 
  }
  
  Date date1(day, month, year); 
  date1.print1(); 
  date1.print2(); 
  date1.print3(); 
}
