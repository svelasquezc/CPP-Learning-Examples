#include <iostream>
#include <string>
#include <array>

#include <tuple>

int main(){
    
    using namespace std::string_literals;
    //auto [x,y] = {1, 2};
    //auto result = x+y;
    std::array<std::string, 3> arr{"Using "s, "structured "s, "binding"s};
    auto [first, next, last] = arr;

    std::cout << first << next <<last<<std::endl;
    
    //Deduction guides -- C++17
    auto mytuple = std::make_tuple("Yes", 50.0);

    //Structured Binding -- C++17
    auto [val1,val2] = mytuple;

    std::cout << val1 << " " << val2 << std::endl;
    
}
