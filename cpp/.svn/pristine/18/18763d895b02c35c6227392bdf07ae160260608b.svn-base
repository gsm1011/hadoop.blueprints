#include<boost/variant.hpp>
#include<iostream>
#include<vector> 
#include<string>

int main() {

    typedef boost::variant<int, const char*, std::string> my_var_t; 
    std::vector<my_var_t> values; 
    values.push_back(10); 
    values.push_back("Hello world"); 
    values.push_back(std::string("wow!"));
    std::string & s = boost::get<std::string> (values.back());
    s += " that's great!\n"; 
    std::cout << s; 
    return 0; 
    
}
