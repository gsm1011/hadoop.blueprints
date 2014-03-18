// This pattern encapsulate a request in an object. And allows the
// parameterization of clients with different requests. And allows
// saving the requests in a queue. 
// The command pattern requires that the receiver knows how to
// actually do the work. The agent is responsible for delegating the
// request actions to the receiver.
// In this way, the command pattern decouples the object that invokes
// the operation from the one that knows how to perform it. The
// invoker should be only aware about the abstract command class.

// This example is from http://www.oodesign.com/command-pattern.html
#include <iostream> 
#include <queue> 

class StockTrade {
public: 
  void buy () {
    std::cout << "Buying stock....." << std::endl; 
  }
  void sell() {
    std::cout << "Selling stock......" << std::endl; 
  }
}; 

class Order {
protected:
  StockTrade* stock_; 

public: 
  Order(StockTrade* st) : stock_(st) {} 
  virtual void execute() = 0; 
}; 

class BuyOrder : public Order {
public: 
  BuyOrder(StockTrade* s) : Order(s) {}

  void execute() {
    stock_->buy();
  }
}; 

class SellOrder : public Order {
public:
  SellOrder(StockTrade* st):Order(st) {}
  void execute() {
    stock_->sell();
  }
}; 

class Agent {
private: 
  std::queue<Order*> orders; 

public: 
  Agent() {} 
  void placeOrder(Order* od) {
    orders.push(od); 
    Order* order = orders.front(); 
    order->execute(); 
    orders.pop(); 
    // order.execute(
  }
}; 

int main( int argc, char** argv) {
  StockTrade* stock = new StockTrade(); 
  Agent* agent = new Agent(); 
  BuyOrder* buy = new BuyOrder(stock); 
  SellOrder* sell = new SellOrder(stock); 

  agent->placeOrder(buy); 
  agent->placeOrder(sell); 
}
