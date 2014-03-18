#include<iostream>
#include<string>

using namespace std; 

class Tips {
public: 
  Tips() : taxRate(0.065) {} 
  Tips(double tr) : taxRate(tr) {} 

  double computeTip(double billAmount, double tipRate) {
    //double costBeforeTax = billAmount * ( 1 + tipRate); 
    return billAmount * tipRate; 
  }

private: 
  double taxRate; 
  
}; 

int main() {
  Tips tips;
  double bill, tpRate; 
  while(true) {
    cout << "Please enter bill amount: " ;
    cin >> bill; 

    cout << "Please enter tip rate (%): ";
    cin >> tpRate; 

    cout << "Tip Amount: " << tips.computeTip(bill,tpRate/100) << endl; 
  }
}
