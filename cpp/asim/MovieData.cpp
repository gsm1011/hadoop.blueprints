#include<iostream>
#include<string> 

using namespace std; 

class MovieData {
private: 
  string title, director; 
  int yearRelease; 
  int runningTime; 

public: 
  //Movie(string t, string d, int y, int r) : 
  //  title(t),director(d),yearRelease(y),runningTime(r){}
  MovieData(string t, string d, int y, int r) {
    title = t, director = d, yearRelease = y, runningTime = r; 
  }

  // getters. 
  string getTitle() { return title; }
  string getDirector() { return director; } 
  int getYear() { return yearRelease; } 
  int getTime() { return runningTime; }

  // setters. 
  void setTitle(string t) { title = t; } 
  void setDirector( string d) { director = d; } 
  void setYear(int y) { yearRelease = y; }
  void setRunningTime(int r) { runningTime = r; }
};

void displayMovieInfo(MovieData m) {
  cout << "Movie Title    : " << m.getTitle() << endl
       << "Movie Director : " << m.getDirector() << endl
       << "Movie Year Made: " << m.getYear() << endl
       << "Movie Run Time : " << m.getTime() << endl << endl; 
} 

int main() {

  MovieData m1("title1", "director1", 2010, 95); 
  MovieData m2("title2", "director2", 2012, 120); 
  displayMovieInfo(m1);
  displayMovieInfo(m2);   
}
