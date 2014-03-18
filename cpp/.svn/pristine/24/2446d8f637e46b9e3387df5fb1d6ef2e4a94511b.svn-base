// this pattern is used to evaluate sentences in a given language. The
// basic idea is to parse the sentence as a syntax tree. 

//expression ::= plus | minus | variable | number
//  plus ::= expression expression '+'
//  minus ::= expression expression '-'
//  variable  ::= 'a' | 'b' | 'c' | ... | 'z'
//digit = '0' | '1' | ... | '9'
//  number ::= digit | digit number

// The example is from :
// http://en.wikipedia.org/wiki/Interpreter_pattern
#include <string> 
#include <iostream>
#include <map>
#include <stack>

class Expr {
public: 
  virtual int interpret(map<std::string, Expr*> vars) = 0; 
};

class Number : public Expr {
public: 
  Number() {} 
  Number(int n):num_(n) {}
  virtual int interpret(Map<std::string, Expr*> vars) { return num_; }

private: 
  int num_; 
}; 

class Plus : public Expr {
public: 
  Plus(Expr* left, Expr* right) {
    leftOperand = left; 
    rightOperand = right; 
  }

  int interpret(std::map<std::string, Expr*> vars) {
    return leftOperand->interpret(vars) + rightOperand->interpret(vars); 
  }

private: 
  Expr* leftOperand; 
  Expr* rightOperand;
};

class Minus : public Expr {
public: 
  Minus(Expr* left, Expr* right) {
    leftOperand = left; 
    rightOperand = right; 
  }

  int interpret(std::map<std::string, Expr*> vars) {
    return leftOperand->interpret(vars) - rightOperand->interpret(vars); 
  }

private: 
  Expr* leftOperand; 
  Expr* rightOperand;
};

class Variable : public Expr {
public: 
  Variable(std::string n):name_(n) {}
  virtual int interpret(std::map<std::string, Expr*> vars) {
    if(NULL == vars.get(name_)) return 0; 
    return vars.get(name).interpret(vars);
  }

private: 
  std::string name_; 
}; 

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elements; 
  std::stringstream ss(s); 
  std::string item; 
  while(std::getline(ss, item, delim)) {
    elements.push_back(item); 
  }
  return elements; 
}

class Evaluator : public Expr {
public: 
  Evaluator(std::string expr) {
    std::stack<Expr*> exprStack = new Stack<Expr>();
    std::vector<std::string> tokens = split(expr, ' '); 
    std::vector<std::string>::iterator token = tokens.begin(); 
    for(; token != tokens.end(); token++) {
      if(token->compare("+") == 0) {
	Expr* subExpr = new Plus(exprStack.pop(), exprStack.pop()); 
	exprStack.push(subExpr); 
      } else if (token->compare("-")) {
	Expr* right = exprStack.pop(); 
	Expr* subExpr = new Minus(left, right); 
	exprStack.push(subExpr);
      } else {
	exprStack.push(new Variable(token)); 
      }
    }
    syntaxTree = exprStack.pop(); 
  }

  int interpret(std::map<std::string, Expr*> context) {
    return syntaxTree->interpret(context); 
  }

private: 
  Expr* syntaxTree; 
}; 

int main(int argc, char** argv) {
  std::string expr = "w x z - +"; 
  Evaluator* sentence = new Evaluator(expr); 
  std::map<std::string, Expr*> variables = new std::map<std::string, Expr*>(); 
  variables.put("w", new Number(5)); 
  variables.put("x", new Number(10)); 
  variables.put("z", new Number(32)); 
  int result = sentence->interpret(variables); 

  std::cout << "Computation result: " << result << std::endl; 
}
