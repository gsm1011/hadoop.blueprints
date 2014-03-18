#include<iostream> 
#include"functor.cpp"

using namespace std; 

template <typename T, typename ARG>
class SpecificFunctor : public Functor<ARG> {
public:
  SpecificFunctor(T* p, int (T::*_pmi)(ARG arg)){
    m_p = p; 
    m_pmi = _pmi; 
  }

  int operator() (ARG arg) {
    (*m_p.*m_pmi)(arg); 
  }

private:
  int (T::*m_pmi)(ARG arg); 
  T* m_p; 
}; 

int main() {
  string *str = new string("hello world"); 
  int x = 100; 
  SpecificFunctor<string, int> *functor = new SpecificFunctor<string, int>(str, x); 
  functor->test(); 
}
