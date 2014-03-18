#include <iostream>
#include <string> 
#include <vector> 
#include <cstdlib> // for exit().
using namespace std; 

class Item {
public: 
  Item() {}
  Item(long num, string name, int q, double c): 
    itemNum(num), itemName(name), quantity(q), cost(c) {} 
  // getters. 
  long getNum() const { return itemNum; } 
  string getName() const { return itemName; } 
  int getQuantity() const { return quantity; } 
  double getCost() const { return cost; }

  // setters. 
  void setNum(long num) { itemNum = num; } 
  void setName(string n) { itemName = n; }
  void setQuantity(int q) { quantity = q; } 
  void setCost(double c) { cost = c; } 

  // output of item using operator <<.
  friend ostream& operator<<(ostream& os, const Item& item) {
    os << "Item Number : " << item.getNum() << endl
       << "Item Name   : " << item.getName() << endl
       << "Item quantity: " << item.getQuantity() << endl
       << "Item cost   : " << item.getCost() << endl
       << "Total cost  : " << item.getQuantity() * item.getCost() << endl; 
    return os;
  }

  // print item info. 
  void printItem() {
    cout << "Item Number : " << getNum() << endl
	 << "Item Name   : " << getName() << endl
	 << "Item quantity: " << getQuantity() << endl
	 << "Item cost   : " << getCost() << endl
	 << "Total cost  : " << getQuantity() * getCost() << endl << endl;
  }

private: 
  long itemNum; 
  string itemName; 
  int quantity;
  double cost; 
}; 

class Inventory {
public: 
  Inventory() {cnt = 0;}

  void insertItem(Item& item) {
    // inventoryList.push_back(item); 
    inventoryList[cnt++] = item; 
  }

  // use item number to retrieve item. 
  Item& getItem(long num) {
    for(int i = 0; i < cnt; ++i) {
      if(inventoryList[i].getNum() == num) return inventoryList[i]; 
    }
    cout << "Can't find the item with given number!" << endl;
    cout << "Exiting the program......" << endl; 
    exit(1); 
  }

  void changeItem(long num) {
    cout << "Which property do you want to change? " << endl; 
    cout << "Quantity (q)" << endl
	 << "Cost (c)" << endl; 
    Item& item = getItem(num); 
    char p; 
    int quantity; 
    double cost; 
    cout << "Your choice -->> "; 
    cin >> p; 
    switch(p) {
    case 'q':
      cout << "Current quantity of item " << item.getName() 
	   << " is " << item.getQuantity() << endl;

      do {
	cout << "Please enter new quantity: "; 
	cin >> quantity;
      } while (quantity < 0); 

      cout << "Changing the item quantity......"; 
      item.setQuantity(quantity); 
      cout << " done! " << endl; 
      break; 

    case 'c': 
      cout << "Current cost of item " << item.getName()
           << " is " << item.getCost() << endl;
      do {
      cout << "Please enter new cost: ";
      cin >> cost;
      } while ( cost < 0);
      
      cout << "Changing the item cost......";
      item.setCost(cost);
      cout << " done! " << endl;
      break;

    default: 
      cout << "We only support quantity and cost change now.";
    }
  }

  // show all items in the list. 
  void displayItems() {
    for(int i = 0; i < cnt; i++) {
      inventoryList[i].printItem(); 
    }
  }

  // print operations. 
  char printOps() {
    char op; // operations.
    cout << endl << "Select your operations from the following list: " << endl
	 << "Print items  (p): " << endl
	 << "Change items (c): " << endl 
	 << "Exit program (e): " << endl; 
    cout << "Your choice -->> " ;
    cin >> op; 
    if((op != 'c') && (op != 'p')) { 
      cout << "error option, exiting program." << endl;
      exit(1); 
    }
    return op; 
  }
  
private: 
  int cnt; 
  // vector<Item> inventoryList; 
  Item inventoryList[10]; 
};

int main() {
  Inventory inventory; 
  Item *item = new Item(12345, "Hammer", 10, 12.95); 
  inventory.insertItem(*item); 
  item = new Item(12367, "Wrench", 5, 6.49);
  inventory.insertItem(*item);

  char op; 
  while(true) {
    op = inventory.printOps(); 
    switch (op) {
    case ('p'): {
      inventory.displayItems(); 
      break; 
    }
    case('c'): {
      cout << "Changing item" << endl; 
      long num ; 
      cout << "Please enter the item number you want to change: "; 
      cin >> num; 
      inventory.changeItem(num); 

      break; 
    }

    case('e'): 
      return 0; 

    default: 
      cout << "No operation is done." << endl; 
    }
  }

  return 0; 
}
