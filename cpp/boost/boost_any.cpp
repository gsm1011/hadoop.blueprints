#include<boost/any.hpp>
#include<iostream>
#include<vector> 
#include<string>

int main() {
    std::vector<boost::any> values; 
    values.push_back(10); 
    const char* c_str = "hello world!";
    values.push_back(c_str); 
    values.push_back(std::string("Wow!")); 
    std::string & s = boost::any_cast<std::string&> (values.back());
    s += " that's great!\n"; 
    std::cout << s; 
    return 0; 
    
}
