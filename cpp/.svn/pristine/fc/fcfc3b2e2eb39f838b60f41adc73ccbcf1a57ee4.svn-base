#include<iostream>
#include<string> 

using namespace std; 

class MovieProfit {
private: 
  string title, director; 
  int yearRelease; 
  int runningTime;
  double productionCost, firstYearRevenue; 

public: 
  //Movie(string t, string d, int y, int r) : 
  //  title(t),director(d),yearRelease(y),runningTime(r){}
  MovieProfit(string t, string d, int y, int r, double p, double f) {
    title = t, director = d, yearRelease = y, runningTime = r; 
    productionCost = p, firstYearRevenue = f; 
  }

  // getters. 
  string getTitle() const { return title; }
  string getDirector() const { return director; } 
  int getYear() const { return yearRelease; } 
  int getTime() const { return runningTime; }
  double getProductionCost() const { return productionCost; } 
  double getFirstYearRevenue() const { return firstYearRevenue; } 

  // setters. 
  void setTitle(string t) { title = t; } 
  void setDirector( string d) { director = d; } 
  void setYear(int y) { yearRelease = y; }
  void setRunningTime(int r) { runningTime = r; }
  void setProductionCost(double pc) { productionCost = pc; } 
  void setFirstYearRevenue ( double fr) { firstYearRevenue = fr; } 
};

void displayMovieInfo(const MovieProfit& m) {
  cout << "Movie Title    : " << m.getTitle() << endl
       << "Movie Director : " << m.getDirector() << endl
       << "Movie Year Made: " << m.getYear() << endl
       << "Movie Run Time : " << m.getTime() << endl; 
  if(m.getProductionCost() > m.getFirstYearRevenue()) 
    cout << "Movie is not profitable." << endl;
  else 
    cout << "Movie is profitable." << endl; 
  cout << endl;
} 

int main() {
  MovieProfit m1("title1", "director1", 2010, 95, 2000000, 3000000); 
  MovieProfit m2("title2", "director2", 2012, 120, 1000000, 500000); 

  MovieProfit profits[2] = {m1, m2}; 
  //profits[0] = m1; 
  //profits[1] = m2; 
  displayMovieInfo(profits[0]);
  displayMovieInfo(profits[1]);   
}
