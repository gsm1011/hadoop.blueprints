#include<iostream>

using namespace std; 

class WidgetFactory {
private: 
  static const int numHours = 16; 
  static const int cntPerHour = 10; 

public:
  WidgetFactory() { }
  void getOrders() {
    int widgetCnt, days; 
    int widgetsPerDay = cntPerHour * numHours; 

    cout << "How many widgets do you want to create: "; 
    cin >> widgetCnt; 
    
    days = widgetCnt / widgetsPerDay; 
    if(days * widgetsPerDay < widgetCnt) days++; 

    cout << "Your order will take " << days << " days to finish." << endl;
  }
}; 

int main() {
  WidgetFactory factory; // = new WidgetFactory(); 

  factory.getOrders(); 

  return 0; 
}
